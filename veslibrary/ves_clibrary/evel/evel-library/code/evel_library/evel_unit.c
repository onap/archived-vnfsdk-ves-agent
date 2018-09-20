#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/time.h>

#include "evel.h"
#include "evel_internal.h"
#include "evel_throttle.h"
#include "metadata.h"

static void test_encode_heartbeat();
static void test_encode_header_overrides();
static void compare_strings(char * expected,
                            char * actual,
                            int max_size,
                            char * description);

int main(int argc, char ** argv)
{
  assert(argc >= 0);
  assert(argv != NULL);

  /***************************************************************************/
  /* Fix our timezone to UTC.                                                */
  /***************************************************************************/
  putenv("TZ=UTC");

  /***************************************************************************/
  /* Initialize metadata.                                                    */
  /***************************************************************************/
  openstack_metadata_initialize();

  /***************************************************************************/
  /* Minimal initialisation to exercise the encoders.                        */
  /***************************************************************************/
  functional_role = "UNIT TEST";
  log_initialize(EVEL_LOG_DEBUG, "EVEL");
  /***************************************************************************/
  /* Test each encoder.                                                      */
  /***************************************************************************/
  test_encode_heartbeat();
  test_encode_header_overrides();
 printf ("\nAll Tests Passed\n");

  return 0;
}


void test_encode_heartbeat()
{
  char * expected =
    "{\"event\": {"
    "\"commonEventHeader\": {"
    "\"domain\": \"heartbeat\", "
    "\"eventId\": \"121\", "
    "\"functionalRole\": \"UNIT TEST\", "
    "\"lastEpochMicrosec\": 1000002, "
    "\"priority\": \"Normal\", "
    "\"reportingEntityName\": \"Dummy VM name - No Metadata available\", "
    "\"sequence\": 121, "
    "\"sourceName\": \"Dummy VM name - No Metadata available\", "
    "\"startEpochMicrosec\": 1000002, "
    "\"version\": 1.2, "
    "\"eventType\": \"Autonomous heartbeat\", "
    "\"reportingEntityId\": \"Dummy VM UUID - No Metadata available\", "
    "\"sourceId\": \"Dummy VM UUID - No Metadata available\""
    "}}}";

  size_t json_size = 0;
  char json_body[EVEL_MAX_JSON_BODY];

  /***************************************************************************/
  /* Test the VM name/uuid once.                                             */
  /***************************************************************************/
  evel_set_next_event_sequence(121);

  EVENT_HEADER * heartbeat = evel_new_heartbeat();
  assert(heartbeat != NULL);

  json_size = evel_json_encode_event(
    json_body, EVEL_MAX_JSON_BODY, (EVENT_HEADER *) heartbeat);
  compare_strings(expected, json_body, EVEL_MAX_JSON_BODY, "Heartbeat");
  assert((json_size == strlen(json_body)) && "Bad size returned");

  evel_free_event(heartbeat);
}

void test_encode_header_overrides()
{
  char * expected =
    "{\"event\": {"
    "\"commonEventHeader\": {"
    "\"domain\": \"heartbeat\", "
    "\"eventId\": \"121\", "
    "\"functionalRole\": \"UNIT TEST\", "
    "\"lastEpochMicrosec\": 1000, "
    "\"priority\": \"Normal\", "
    "\"reportingEntityName\": \"entity_name_override\", "
    "\"sequence\": 121, "
    "\"sourceName\": \"Dummy VM name - No Metadata available\", "
    "\"startEpochMicrosec\": 1001, "
    "\"version\": 1.2, "
    "\"eventType\": \"Autonomous heartbeat\", "
    "\"reportingEntityId\": \"entity_id_override\", "
    "\"sourceId\": \"Dummy VM UUID - No Metadata available\""
    "}}}";

  size_t json_size = 0;
  char json_body[EVEL_MAX_JSON_BODY];

  /***************************************************************************/
  /* Test the VM name/uuid once.                                             */
  /***************************************************************************/
  evel_set_next_event_sequence(121);

  EVENT_HEADER * heartbeat = evel_new_heartbeat();
  assert(heartbeat != NULL);

  evel_start_epoch_set(heartbeat, 1001);
  evel_last_epoch_set(heartbeat, 1000);
  evel_reporting_entity_name_set(heartbeat, "entity_name_override");
  evel_reporting_entity_id_set(heartbeat, "entity_id_override");

  json_size = evel_json_encode_event(
    json_body, EVEL_MAX_JSON_BODY, (EVENT_HEADER *) heartbeat);
  compare_strings(expected, json_body, EVEL_MAX_JSON_BODY, "Heartbeat");
  assert((json_size == strlen(json_body)) && "Bad size returned");

  evel_free_event(heartbeat);
}

