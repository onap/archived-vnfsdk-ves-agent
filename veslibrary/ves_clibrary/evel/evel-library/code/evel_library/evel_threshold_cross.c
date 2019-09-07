/*************************************************************************//**
 *
 * Copyright © 2017 AT&T Intellectual Property. All rights reserved.
 *
 * Unless otherwise specified, all software contained herein is
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and 
 * limitations under the License.
 * ECOMP is a trademark and service mark of AT&T Intellectual Property.
 ****************************************************************************/
/**************************************************************************//**
 * @file
 * Implementation of EVEL functions relating to the Threshold Cross Alerts.
 *
 *****************************************************************************/
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "evel.h"	
#include "evel_internal.h"	
#include "evel_throttle.h"	


/**************************************************************************//**
 * Create a new Threshold Crossing Alert event.
 *
 * @note    The mandatory fields on the TCA must be supplied to this factory
 *          function and are immutable once set.  Optional fields have explicit
 *          setter functions, but again values may only be set once so that the
 *          TCA has immutable properties.
 *
 * @param event_name  Unique Event Name confirming Domain AsdcVnfModel Description
 * @param event_id    A universal identifier of the event for: troubleshooting correlation, analysis, etc
 * @param EVEL_EVENT_ACTION talertAction   Alert set continue or clear
 * @param char*  talertDescription
 * @param EVEL_ALERT_TYPE     talertType    Kind of anamoly
 * @param char* tcollectionTimestamp time at which alert was collected
 * @param EVEL_SEVERITIES     teventSeverity  Severity of Alert
 * @param char* teventStartTimestamp Time when this alert started
 *
 * @returns pointer to the newly manufactured ::EVENT_THRESHOLD_CROSS.  If the
 *          event is not used it must be released using
 *          ::evel_free_threshold_cross
 * @retval  NULL  Failed to create the event.
 *****************************************************************************/
EVENT_THRESHOLD_CROSS * evel_new_threshold_cross(const char * ev_name, const char * ev_id,
                           EVEL_ALERT_ACTIONS talertAction,
                           char *             talertDescription, 
                           EVEL_ALERT_TYPE    talertType,
                           char *  tcollectionTimestamp, 
                           EVEL_SEVERITIES     teventSeverity,
                           char *  teventStartTimestamp )
{
        EVENT_THRESHOLD_CROSS * event = NULL;

        EVEL_ENTER();

	assert( talertDescription != NULL );
	assert( talertAction < EVEL_MAX_ALERT_ACTIONS );
	assert( talertType < EVEL_MAX_ANOMALY );
	assert( teventSeverity < EVEL_MAX_SEVERITIES );
		

/***************************************************************************/
/* Allocate the Threshold crossing event.                                  */
/***************************************************************************/
	event = malloc(sizeof(EVENT_THRESHOLD_CROSS));
	if (event == NULL)
	{
	    log_error_state("Out of memory");
	    goto exit_label;
	}
	memset(event, 0, sizeof(EVENT_THRESHOLD_CROSS));
	EVEL_DEBUG("New Threshold Cross event is at %lp", event);

  /***************************************************************************/
  /* Initialize the header & the threshold crossing fields.                  */
  /***************************************************************************/
  evel_init_header_nameid(&event->header,ev_name,ev_id);
  event->header.event_domain = EVEL_DOMAIN_THRESHOLD_CROSS;
  event->major_version = EVEL_THRESHOLD_CROSS_MAJOR_VERSION;
  event->minor_version = EVEL_THRESHOLD_CROSS_MINOR_VERSION;

  event->alertAction      =  talertAction;
  event->alertDescription =  strdup(talertDescription); 
  event->alertType        =  talertType;
  event->collectionTimestamp =   strdup(tcollectionTimestamp); 
  event->eventSeverity       =   teventSeverity;
  event->eventStartTimestamp =   strdup(teventStartTimestamp);

  evel_init_option_string(&event->alertValue);
  evel_init_option_string(&event->dataCollector);
  evel_init_option_string(&event->elementType);
  evel_init_option_string(&event->interfaceName);
  evel_init_option_string(&event->networkService);
  evel_init_option_string(&event->possibleRootCause);
  event->additional_info = ht_create();
  dlist_initialize(&event->alertidList);
  dlist_initialize(&event->additionalParameters);

exit_label:

  EVEL_EXIT();
  return event;

}

/**************************************************************************//**
 * Add the TCA additional performance counter
 *
 * @param tcp                     Pointer to the ::EVENT_THRESHOLD_CROSS.
 * @param char* tcriticality      Performance Counter criticality
 * @param char* tthresholdCrossed Performance Counter Threshold name 
 *****************************************************************************/
PERF_COUNTER * evel_threshold_cross_add_addl_parameters(
                                  EVENT_THRESHOLD_CROSS * const event,
			          char *  tcriticality,
                                  char *  tthresholdCrossed)
{
  PERF_COUNTER *perf_ctr = NULL;

  EVEL_ENTER();

  /***************************************************************************/
  /* Check assumptions.                                                      */
  /***************************************************************************/
  assert(event != NULL);
  assert(event->header.event_domain == EVEL_DOMAIN_THRESHOLD_CROSS);
  assert(tcriticality!= NULL);
  assert(tthresholdCrossed != NULL);

  /***************************************************************************/
  /* Allocate a container for the value and push onto the list.              */
  /***************************************************************************/
  EVEL_DEBUG("Adding criticality=%s, thresholdCrossed=%s", tcriticality, tthresholdCrossed);
  perf_ctr = malloc(sizeof(PERF_COUNTER));
  assert(perf_ctr != NULL);
  perf_ctr->criticality = strdup(tcriticality);
  perf_ctr->thresholdCrossed = strdup(tthresholdCrossed);
  perf_ctr->hashmap = ht_create();

  dlist_push_last(&event->additionalParameters, perf_ctr);

  EVEL_EXIT();
  return perf_ctr; 
}

/**************************************************************************//**
 * Set the TCA name / Value for additional performance counter
 *                                
 * @param PERF_COUNTER perf_ctr Pointer to additional Parameter array element
 * @param char* name          Performance Counter Threshold name
 * @param char* value         Performance Counter actual value
 *****************************************************************************/
void evel_threshold_cross_addl_parameters_hashmap_set(
                                  PERF_COUNTER * perf_ctr,
			          char *  name,
                                  char *  value)
{
  char * nam = NULL;
  char * val = NULL;

  EVEL_ENTER();
  
  /***************************************************************************/
  /* Check assumptions.                                                      */
  /***************************************************************************/
  assert(perf_ctr != NULL);
  assert(name != NULL);
  assert(value != NULL);

  nam = strdup(name);
  val = strdup(value);
  ht_insert(perf_ctr->hashmap, nam, val);

  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the Event Type property of the TC Alert.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param type        The Event Type to be set. ASCIIZ string. The caller
 *                    does not need to preserve the value once the function
 *                    returns.
 *****************************************************************************/
void evel_threshold_cross_type_set(EVENT_THRESHOLD_CROSS * const event,char *  type)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions and call evel_header_type_set.                      */
  /***************************************************************************/
  assert(type!=NULL);
  assert(event->header.event_domain == EVEL_DOMAIN_THRESHOLD_CROSS);
  evel_header_type_set(&event->header, type);

  EVEL_EXIT();
}

/**************************************************************************//**
 * Add an optional additional alertid value to Alert.
 *
 *****************************************************************************/
void evel_threshold_cross_alertid_add(EVENT_THRESHOLD_CROSS * const event,char *  alertid)
{
  char *alid=NULL;
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(event != NULL);
  assert(event->header.event_domain == EVEL_DOMAIN_THRESHOLD_CROSS);
  assert(alertid != NULL);

  EVEL_DEBUG("Adding AlertId=%s", alertid);
  alid = strdup(alertid);
  assert(alid != NULL);

  dlist_push_last(&event->alertidList, alid);

  EVEL_EXIT();
}
	
/**************************************************************************//**
 * Add an optional additional value name/value pair to the Alert.
 *
 * The name and value are NULL delimited ASCII strings.  The library takes
 * a copy so the caller does not have to preserve values after the function
 * returns.
 * @param name      ASCIIZ string with the attribute's name.  The caller
 *                  does not need to preserve the value once the function
 *                  returns.
 * @param value     ASCIIZ string with the attribute's value.  The caller
 *                  does not need to preserve the value once the function
 *                  returns.
 *****************************************************************************/
void evel_threshold_cross_addl_info_add(EVENT_THRESHOLD_CROSS * const event, const char *  name, const char *  value)
{
  char *nam=NULL;
  char *val=NULL;

  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(event != NULL);
  assert(event->header.event_domain == EVEL_DOMAIN_THRESHOLD_CROSS);
  assert(name != NULL);
  assert(value != NULL);

  nam = strdup(name);
  val = strdup(value);
  EVEL_DEBUG("Adding name=%s value=%s", name, value);
  ht_insert(event->additional_info, nam, val);

  EVEL_EXIT();
}


/**************************************************************************//**
 * Free a Signaling event.
 *
 * Free off the event supplied.  Will free all the contained allocated memory.
 *
 * @note It does not free the event itself, since that may be part of a larger
 * structure.
 *****************************************************************************/
void evel_free_threshold_cross(EVENT_THRESHOLD_CROSS * const event)
{
  HASHTABLE_T *ht;
  char *ptr;
  PERF_COUNTER * perf_ctr = NULL;

  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.  As an internal API we don't allow freeing NULL    */
  /* events as we do on the API.                                      */
  /***************************************************************************/
  assert(event != NULL);
  assert(event->header.event_domain == EVEL_DOMAIN_THRESHOLD_CROSS);

  /***************************************************************************/
  /* Free all internal strings then the header itself.                       */
  /***************************************************************************/
  ht = event->additional_info;
  if( ht != NULL )
  {
     ht_destroy(ht);
  }

  ptr = dlist_pop_last(&event->alertidList);
  while (ptr != NULL)
  {
    free(ptr);
    ptr = dlist_pop_last(&event->alertidList);
  }

  perf_ctr = dlist_pop_last(&event->additionalParameters);
  while (perf_ctr != NULL)
  {
    EVEL_DEBUG("Freeing Other performance counter");
    ht_destroy(perf_ctr->hashmap);
    free(perf_ctr->criticality);
    free(perf_ctr->thresholdCrossed);
    free(perf_ctr);
    perf_ctr = dlist_pop_last(&event->additionalParameters);
  }

  free(event->alertDescription); 

  evel_free_option_string(&event->alertValue);
  evel_free_option_string(&event->dataCollector);
  evel_free_option_string(&event->elementType);
  evel_free_option_string(&event->interfaceName);
  evel_free_option_string(&event->networkService);
  evel_free_option_string(&event->possibleRootCause);
  evel_free_header(&event->header);

  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the TCA probable Root cause.
 *
 * @param sheader     Possible root cause to Threshold
 *****************************************************************************/
void evel_threshold_cross_possible_rootcause_set(EVENT_THRESHOLD_CROSS * const event, char *  sheader)
{
   EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(event->header.event_domain == EVEL_DOMAIN_THRESHOLD_CROSS);
  assert(sheader != NULL);

  evel_set_option_string(&event->possibleRootCause,
                        sheader,
                        "Rootcause value");

  EVEL_EXIT();
}
    
/**************************************************************************//**
 * Set the TCA networking cause.
 *
 * @param sheader     Possible networking service value to Threshold
 *****************************************************************************/
void evel_threshold_cross_networkservice_set(EVENT_THRESHOLD_CROSS * const event, char *  sheader)
{
    EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(event->header.event_domain == EVEL_DOMAIN_THRESHOLD_CROSS);
  assert(sheader != NULL);

  evel_set_option_string(&event->networkService,
                        sheader,
                        "Networking service value");

  EVEL_EXIT();
}
    
 /**************************************************************************//**
  * Set the TCA Interface name.
  *
  * @param sheader     Interface name to threshold
  *****************************************************************************/
void evel_threshold_cross_interfacename_set(EVENT_THRESHOLD_CROSS * const event,char *  sheader)
{
    EVEL_ENTER();

   /***************************************************************************/
   /* Check preconditions.                                                    */
   /***************************************************************************/
   assert(event->header.event_domain == EVEL_DOMAIN_THRESHOLD_CROSS);
   assert(sheader != NULL);

    evel_set_option_string(&event->interfaceName,
                           sheader,
                           "TCA Interface name");
    EVEL_EXIT();
}
    
/**************************************************************************//**
 * Set the TCA Data element type.
 *
 * @param sheader     element type of Threshold
 *****************************************************************************/
void evel_threshold_cross_data_elementtype_set(EVENT_THRESHOLD_CROSS * const event,char *  sheader)
{
    EVEL_ENTER();

   /***************************************************************************/
   /* Check preconditions.                                                    */
   /***************************************************************************/
   assert(event->header.event_domain == EVEL_DOMAIN_THRESHOLD_CROSS);
   assert(sheader != NULL);

   evel_set_option_string(&event->elementType,
                           sheader,
                           "TCA Element type value");
    EVEL_EXIT();
}

/**************************************************************************//**
 * Set the TCA Data collector value.
 *
 * @param sheader     Data collector value
 *****************************************************************************/
void evel_threshold_cross_data_collector_set(EVENT_THRESHOLD_CROSS * const event,char *  sheader)
{
    EVEL_ENTER();

/***************************************************************************/
/* Check preconditions.                                                    */
/***************************************************************************/
    assert(event->header.event_domain == EVEL_DOMAIN_THRESHOLD_CROSS);
    assert(sheader != NULL);

    evel_set_option_string(&event->dataCollector,
                           sheader,
                           "Datacollector value");
    EVEL_EXIT();
}
    
    
    
/**************************************************************************//**
 * Set the TCA alert value.
 *
 * @param sheader     Possible alert value
 *****************************************************************************/
void evel_threshold_cross_alertvalue_set(EVENT_THRESHOLD_CROSS * const event,char *  sheader)
{
   EVEL_ENTER();

   /***************************************************************************/
   /* Check preconditions.                                                    */
   /***************************************************************************/
   assert(event->header.event_domain == EVEL_DOMAIN_THRESHOLD_CROSS);
   assert(sheader != NULL);

   evel_set_option_string(&event->alertValue,
                           sheader,
                           "Alert value");
   EVEL_EXIT();
}

/**************************************************************************//**
 * Encode the performance counter as a JSON object.
 *
 * @param jbuf          Pointer to working ::EVEL_JSON_BUFFER.
 * @param pcounter      Pointer to the performance counter to encode.
 *****************************************************************************/
void evel_json_encode_perf_counter( EVEL_JSON_BUFFER * jbuf, PERF_COUNTER *pcounter)
{
  HASHTABLE_T *ht;
  ENTRY_T *entry;

  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(jbuf != NULL);
  assert(pcounter != NULL);

  evel_json_open_object(jbuf);
  /***************************************************************************/
  /* Mandatory parameters.                                                   */
  /***************************************************************************/
  evel_enc_kv_string(jbuf, "criticality", pcounter->criticality);
  evel_enc_kv_string(jbuf, "thresholdCrossed", pcounter->thresholdCrossed);
  ht = pcounter->hashmap;
  if( ht != NULL )
  {
    if( ht->size > 0)
    {
      if (evel_json_open_opt_named_object(jbuf, "hashMap"))
      {
        unsigned int idx = 0;
        for(; idx < ht->size; idx++ )
        {
          /*****************************************************************/
          /* Get the first entry of a particular Key and loop through the  */
          /* remaining if any. Then proceed to next key.                   */
          /*****************************************************************/
          entry =  ht->table[idx];
          while( entry != NULL && entry->key != NULL)
          {
            EVEL_DEBUG("Encoding TCAFields %s %s",(char *) (entry->key), entry->value);
            //evel_json_open_object(jbuf);
            evel_enc_kv_string(jbuf, entry->key, entry->value);
            //evel_json_close_object(jbuf);
            entry = entry->next;
          }
        }
      }
      evel_json_close_object(jbuf);
    }
  }
  evel_json_close_object(jbuf);

  EVEL_EXIT();
}

/**************************************************************************//**
 * Encode the Signaling in JSON according to AT&T's schema for the
 * event type.
 *
 * @param jbuf          Pointer to the ::EVEL_JSON_BUFFER to encode into.
 * @param event         Pointer to the ::EVENT_HEADER to encode.
 *****************************************************************************/
void evel_json_encode_threshold_cross(EVEL_JSON_BUFFER * const jbuf,
                                EVENT_THRESHOLD_CROSS * const event)
{
  HASHTABLE_T *ht;
  ENTRY_T *entry;
  char * alert_action = NULL;
  char * alert_type = NULL;
  char * event_sev = NULL;
  DLIST_ITEM * item  = NULL;
  char * alert_id = NULL;
  PERF_COUNTER * perf_ctr = NULL;

  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(event != NULL);
  assert(event->header.event_domain == EVEL_DOMAIN_THRESHOLD_CROSS);

  evel_json_encode_header(jbuf, &event->header);
  evel_json_open_named_object(jbuf, "thresholdCrossingAlertFields");

  /***************************************************************************/
  /* Mandatory fields                                                        */
  /***************************************************************************/

  evel_json_open_named_list(jbuf, "additionalParameters");

  item = dlist_get_first(&event->additionalParameters);
  while (item != NULL)
  {
    perf_ctr = (PERF_COUNTER *) item->item;
    assert(perf_ctr != NULL);
    evel_json_encode_perf_counter(jbuf, perf_ctr);
    item = dlist_get_next(item);
  }
  evel_json_close_list(jbuf);

  alert_action = evel_alert_action(event->alertAction);
  evel_enc_kv_string(jbuf, "alertAction", alert_action);
  evel_enc_kv_string(jbuf, "alertDescription", event->alertDescription);

  alert_type = evel_alert_type(event->alertType);
  evel_enc_kv_string(jbuf, "alertType", alert_type);

  evel_enc_kv_string(
    jbuf, "collectionTimestamp", event->collectionTimestamp);

  event_sev = evel_severity(event->eventSeverity);
  evel_enc_kv_string(jbuf, "eventSeverity", event_sev);

  evel_enc_kv_string(
    jbuf, "eventStartTimestamp", event->eventStartTimestamp);

  /***************************************************************************/
  /* Optional fields                                                         */
  /***************************************************************************/
  evel_enc_kv_opt_string(jbuf, "alertValue", &event->alertValue);
  evel_enc_kv_opt_string(jbuf, "dataCollector", &event->dataCollector);
  evel_enc_kv_opt_string(jbuf, "elementType", &event->elementType);
  evel_enc_kv_opt_string(jbuf, "interfaceName", &event->interfaceName);
  evel_enc_kv_opt_string(jbuf, "networkService", &event->networkService);
  evel_enc_kv_opt_string(jbuf, "possibleRootCause", &event->possibleRootCause);

  evel_json_checkpoint(jbuf);
  evel_json_open_named_list(jbuf, "associatedAlertIdList");
  bool added = false;
  item = dlist_get_first(&event->alertidList);
  while (item != NULL)
  {
    alert_id = (char *)item->item;
    evel_enc_list_item(jbuf, "\"%s\"", alert_id);
    added = true;
    item = dlist_get_next(item);
  }
  evel_json_close_list(jbuf);
  if (!added)
  {
    evel_json_rewind(jbuf);
  }

  /***************************************************************************/
  /* Checkpoint, so that we can wind back if all fields are suppressed.      */
  /***************************************************************************/
  evel_json_checkpoint(jbuf);
  ht = event->additional_info;
  if( ht != NULL )
  {
    bool added = false;
    if( ht->size > 0)
    {
      evel_json_checkpoint(jbuf);
      if (evel_json_open_opt_named_object(jbuf, "additionalFields"))
      {
        unsigned int idx = 0;
        for(; idx < ht->size; idx++ )
        {
          /*****************************************************************/
          /* Get the first entry of a particular Key and loop through the  */
          /* remaining if any. Then proceed to next key.                   */
          /*****************************************************************/
          entry =  ht->table[idx];
          while( entry != NULL && entry->key != NULL)
          {
            EVEL_DEBUG("Encoding TCA Fields %s %s",(char *) (entry->key), entry->value);
            if (!evel_throttle_suppress_nv_pair(jbuf->throttle_spec,
                                              "additionalFields",
                                              entry->key))
            {

              //evel_json_open_object(jbuf);
              evel_enc_kv_string(jbuf, entry->key, entry->value);
              //evel_json_close_object(jbuf);
              added = true;
            }
            entry = entry->next;
          }
        }
      }
    }
    evel_json_close_object(jbuf);

    /*************************************************************************/
    /* If we've not written anything, rewind to before we opened the list.   */
    /*************************************************************************/
    if (!added)
    {
      evel_json_rewind(jbuf);
    }
  }

  evel_enc_version(jbuf,
                   "thresholdCrossingFieldsVersion",
                   event->major_version,
                   event->minor_version);

  evel_json_close_object(jbuf);

  EVEL_EXIT();
}

