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
 *
 * ECOMP is a trademark and service mark of AT&T Intellectual Property.
 ****************************************************************************/
/**************************************************************************//**
 * @file
 * Unit tests for JSON encoding and throttling.
 *
 * This software is intended to show the essential elements of the library's
 * use.
 *
 ****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#include "evel.h"
#include "evel_internal.h"
#include "evel_throttle.h"
#include "metadata.h"

typedef enum {
  SERVICE_NONE,
  SERVICE_CODEC,
  SERVICE_TRANSCODING,
  SERVICE_RTCP,
  SERVICE_EOC_VQM,
  SERVICE_MARKER
} SERVICE_TEST;

/*****************************************************************************/
/* Local prototypes.                                                         */
/*****************************************************************************/
static void test_encode_heartbeat();
static void test_encode_fault();
static void test_encode_measurement();
//static void test_encode_mobile_mand();
static void test_encode_mobile_opts();
static void test_encode_other();
static void test_encode_pnfreg();
static void test_encode_tca();
static void test_encode_signaling();
static void test_encode_voiceQ();
static void test_encode_notif();
static void test_encode_state_change();
static void test_encode_syslog();
static void test_encode_header_overrides();
static void compare_strings(char * expected,
                            char * actual,
                            int max_size,
                            char * description);

/**************************************************************************//**
 * Main function.
 *
 * Runs all unit test cases, and fails hard on the first failure.
 *
 * @param[in] argc  Argument count.
 * @param[in] argv  Argument vector - for usage see usage_text.
 *****************************************************************************/
int main(int argc, char ** argv)
{
  char * fqdn = "127.0.0.1";
  int port = 30000;
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

  /**************************************************************************/
  /* Initialize                                                             */
  /**************************************************************************/
  if(evel_initialize(fqdn,                         /* FQDN                  */
                     port,                         /* Port                  */
                     NULL,                         /* Backup FQDN           */
                     0,                            /* Backup port           */
                     NULL,                         /* optional path         */
                     NULL,                         /* optional topic        */
                     100,                          /* Ring Buffer size      */
                     0,                            /* HTTPS?                */
                     NULL,                         /* cert file             */
                     NULL,                         /* key  file             */
                     NULL,                         /* ca   info             */
                     NULL,                         /* ca   file             */
                     0,                            /* verify peer           */
                     0,                            /* verify host           */
                     "sample1",                    /* Username              */
                     "sample1",                    /* Password              */
                     "",                           /* Username2             */
                     "",                           /* Password2             */
                     NULL,                         /* Source ip             */
                     NULL,                         /* Source ip2            */
                     EVEL_SOURCE_VIRTUAL_MACHINE,  /* Source type           */
                     "UNIT Test",                  /* Role                  */
                     1))                           /* Verbosity             */
  {
    fprintf(stderr, "\nFailed to initialize the EVEL library!!!\n");
    exit(-1);
  }
  else
  {
    printf("\nInitialization completed\n");
  }

  /***************************************************************************/
  /* Test each encoder.                                                      */
  /***************************************************************************/
  test_encode_heartbeat();
  test_encode_header_overrides();
  test_encode_fault(); 
  test_encode_measurement();
//  test_encode_mobile_mand();
  test_encode_mobile_opts(); 
  test_encode_notif(); 
  test_encode_other();
  test_encode_pnfreg();
  test_encode_signaling();
  test_encode_state_change();
  test_encode_syslog(); 
  test_encode_tca();
  test_encode_voiceQ();
  printf ("\n************ All Tests Passed ************\n\n");
  evel_terminate();
  return 0;
}

/*****************************************************************************/
/* We link with this gettimeofday so that we get a fixed result              */
/*****************************************************************************/
int gettimeofday(struct timeval *tv,
                 struct timezone *tz __attribute__((unused)))
{
  tv->tv_sec = 1;
  tv->tv_usec = 2;
  return 0;
}

void test_encode_heartbeat()
{
 char * expected =
"{\"event\": {\"commonEventHeader\": {\"domain\": \"heartbeat\", \"eventId\": \"1\", \"eventName\": \"Heartbeat\", \"vesEventListenerVersion\": \"7.1\", \"lastEpochMicrosec\": 1000002, \"priority\": \"Normal\", \"reportingEntityName\": \"VM-VirtualBox\", \"sequence\": 0, \"sourceName\": \"VM-VirtualBox\", \"startEpochMicrosec\": 1000002, \"version\": \"4.1\", \"eventType\": \"Autonomous heartbeat\"}}}";

  size_t json_size = 0;
  char json_body[EVEL_MAX_JSON_BODY];
  /***************************************************************************/
  /* Test the VM name/uuid once.                                             */
  /***************************************************************************/
//  evel_set_next_event_sequence(121);

  EVENT_HEADER * heartbeat = evel_new_heartbeat();
  assert(heartbeat != NULL);
  evel_source_name_set(heartbeat, "VM-VirtualBox");
  evel_reporting_entity_name_set(heartbeat, "VM-VirtualBox");

  json_size = evel_json_encode_event(
    json_body, EVEL_MAX_JSON_BODY, (EVENT_HEADER *) heartbeat);
  compare_strings(expected, json_body, EVEL_MAX_JSON_BODY, "Heartbeat");
  assert((json_size == strlen(json_body)) && "Bad size returned");

  if(evel_post_event(heartbeat) == EVEL_SUCCESS)
  {
    printf("HB Message sent to Collector successfully\n");
  }
  else
  {
    printf("Message sending Error\n");
  }

//  evel_free_event(heartbeat);
}

void test_encode_header_overrides()
{
  char * expected =
"{\"event\": {\"commonEventHeader\": {\"domain\": \"heartbeat\", \"eventId\": \"2\", \"eventName\": \"Heartbeat\", \"vesEventListenerVersion\": \"7.1\", \"lastEpochMicrosec\": 1000, \"priority\": \"Normal\", \"reportingEntityName\": \"entity_name_override\", \"sequence\": 121, \"sourceName\": \"VM-VirtualBox\", \"startEpochMicrosec\": 1001, \"version\": \"4.1\", \"eventType\": \"Autonomous heartbeat\", \"reportingEntityId\": \"entity_id_override\", \"sourceId\": \"Source_ID\", \"nfcNamingCode\": \"NFC_Name\", \"nfNamingCode\": \"NF_Name\", \"timeZoneOffset\": \"UTC+5:30\", \"nfVendorName\": \"Vendor_Name\"}}}";

  size_t json_size = 0;
  char json_body[EVEL_MAX_JSON_BODY];

  /***************************************************************************/
  /* Test the VM name/uuid once.                                             */
  /***************************************************************************/
//  evel_set_next_event_sequence(121);

  EVENT_HEADER * heartbeat = evel_new_heartbeat();
  assert(heartbeat != NULL);

  evel_start_epoch_set(heartbeat, 1001);
  evel_last_epoch_set(heartbeat, 1000);
  evel_reporting_entity_name_set(heartbeat, "entity_name_override");
  evel_reporting_entity_id_set(heartbeat, "entity_id_override");
  evel_event_sequence_set(heartbeat, 121);
  evel_source_name_set(heartbeat, "VM-VirtualBox");
  evel_time_zone_offset_set(heartbeat, "UTC+5:30");
  evel_nfcnamingcode_set(heartbeat, "NFC_Name");
  evel_nfnamingcode_set(heartbeat, "NF_Name");
  evel_source_id_set(heartbeat, "Source_ID");
  evel_nf_vendor_name_set(heartbeat, "Vendor_Name");

  json_size = evel_json_encode_event(
    json_body, EVEL_MAX_JSON_BODY, (EVENT_HEADER *) heartbeat);
  compare_strings(expected, json_body, EVEL_MAX_JSON_BODY, "Heartbeat");
  assert((json_size == strlen(json_body)) && "Bad size returned");

  if(evel_post_event(heartbeat) == EVEL_SUCCESS)
  {
    printf("HB Message sent to Collector successfully\n");
  }
  else
  {
    printf("Message sending Error\n");
  }

//  evel_free_event(heartbeat);
}

void test_encode_fault()
{
  char * expected =
"{\"event\": {\"commonEventHeader\": {\"domain\": \"fault\", \"eventId\": \"fault000000001\", \"eventName\": \"fault_eNodeB_alarm\", \"vesEventListenerVersion\": \"7.1\", \"lastEpochMicrosec\": 1000002, \"priority\": \"Normal\", \"reportingEntityName\": \"VM-VirtualBox\", \"sequence\": 1, \"sourceName\": \"VM-VirtualBox\", \"startEpochMicrosec\": 1000002, \"version\": \"4.1\", \"eventType\": \"Bad things happen...\"}, \"faultFields\": {\"alarmCondition\": \"My alarm condition\", \"eventCategory\": \"link\", \"eventSeverity\": \"MAJOR\", \"eventSourceType\": \"host\", \"specificProblem\": \"It broke very badly\", \"vfStatus\": \"Ready to terminate\", \"faultFieldsVersion\": \"4.0\", \"alarmAdditionalInformation\": {\"name1\": \"value1\", \"name2\": \"value2\"}, \"alarmInterfaceA\": \"My Interface Card\"}}}";

  size_t json_size = 0;
  char json_body[EVEL_MAX_JSON_BODY];
//  evel_set_next_event_sequence(122);
  EVENT_FAULT * fault = evel_new_fault("fault_eNodeB_alarm", 
                                       "fault000000001", 
                                       "My alarm condition",
                                       "It broke very badly",
                                       EVEL_PRIORITY_NORMAL,
                                       EVEL_SEVERITY_MAJOR,
					EVEL_SOURCE_HOST,
                             EVEL_VF_STATUS_READY_TERMINATE);
  assert(fault != NULL);
  evel_fault_type_set(fault, "Bad things happen...");
  evel_fault_interface_set(fault, "My Interface Card");
  evel_fault_addl_info_add(fault, "name1", "value1");
  evel_fault_addl_info_add(fault, "name2", "value2");
  evel_source_name_set(&fault->header, "VM-VirtualBox");
  evel_reporting_entity_name_set(&fault->header, "VM-VirtualBox");
  evel_fault_category_set(fault, "link");

  json_size = evel_json_encode_event(
    json_body, EVEL_MAX_JSON_BODY, (EVENT_HEADER *) fault);
  compare_strings(expected, json_body, EVEL_MAX_JSON_BODY, "Fault");
  assert((json_size == strlen(json_body)) && "Bad size returned");

  if(evel_post_event((EVENT_HEADER *)fault) == EVEL_SUCCESS)
  {
    printf("Message sent to Collector successfully\n");
  }
  else
  {
    printf("Message sending Error\n");
  }

 // evel_free_event(fault);
}
void test_encode_measurement()
{
  char * expected =
"{\"event\": {\"commonEventHeader\": {\"domain\": \"measurement\", \"eventId\": \"mvfs000000001\", \"eventName\": \"mvfs_perfUnit_issue\", \"vesEventListenerVersion\": \"7.1\", \"lastEpochMicrosec\": 3000, \"priority\": \"Normal\", \"reportingEntityName\": \"entity_name\", \"sequence\": 0, \"sourceName\": \"VM-VirtualBox\", \"startEpochMicrosec\": 2000, \"version\": \"4.1\", \"eventType\": \"Perf management...\", \"reportingEntityId\": \"entity_id\"}, \"measurementFields\": {\"measurementInterval\": 5, \"ipmi\": {\"exitAirTemperature\": 98.400000, \"frontPanelTemperature\": 98.400000, \"ioModuleTemperature\": 98.400000, \"systemAirflow\": 98.400000, \"ipmiBaseboardTemperatureArray\": [{\"baseboardTemperatureIdentifier\": \"BBTEMP1\", \"baseboardTemperature\": 99.800000}, {\"baseboardTemperatureIdentifier\": \"BBTEMP2\", \"baseboardTemperature\": 79.800000}], \"ipmiBaseboardVoltageRegulatorArray\": [{\"baseboardVoltageRegulatorIdentifier\": \"BBVOLT1\", \"voltageRegulatorTemperature\": 88.900000}, {\"baseboardVoltageRegulatorIdentifier\": \"BBVOLT2\", \"voltageRegulatorTemperature\": 68.900000}], \"ipmiBatteryArray\": [{\"batteryIdentifier\": \"BBBATTERY1\", \"batteryVoltageLevel\": 230.000000, \"batteryType\": \"BattType\"}, {\"batteryIdentifier\": \"BBBATTERY2\", \"batteryVoltageLevel\": 110.000000, \"batteryType\": \"BattType2\"}], \"ipmiFanArray\": [{\"fanIdentifier\": \"FAN1\", \"fanSpeed\": 300.000000}, {\"fanIdentifier\": \"FAN2\", \"fanSpeed\": 200.000000}], \"ipmiHsbpArray\": [{\"hsbpIdentifier\": \"BBHSBP1\", \"hsbpTemperature\": 100.000000}, {\"hsbpIdentifier\": \"BBHSBP2\", \"hsbpTemperature\": 200.000000}], \"ipmiGlobalAggregateTemperatureMarginArray\": [{\"globalAggregateTemperatureMarginIdentifier\": \"BBGLOBAL\", \"globalAggregateTemperatureMargin\": 22.500000}, {\"globalAggregateTemperatureMarginIdentifier\": \"BBGLOBAL2\", \"globalAggregateTemperatureMargin\": 32.500000}], \"ipmiNicArray\": [{\"nicIdentifier\": \"NIC_1\", \"nicTemperature\": 33.500000}, {\"nicIdentifier\": \"NIC_2\", \"nicTemperature\": 43.500000}], \"ipmiPowerSupplyArray\": [{\"powerSupplyIdentifier\": \"POWERSupply1\", \"powerSupplyCurrentOutputPercent\": 50.400000, \"powerSupplyInputPower\": 200.500000, \"powerSupplyTemperature\": 100.500000}, {\"powerSupplyIdentifier\": \"POWERSupply2\", \"powerSupplyCurrentOutputPercent\": 60.400000, \"powerSupplyInputPower\": 300.500000, \"powerSupplyTemperature\": 200.500000}], \"ipmiProcessorArray\": [{\"processorIdentifier\": \"PROCESSOR1\", \"processorDtsThermalMargin\": 29.800000, \"processorThermalControlPercent\": 10.900000, \"processorDimmAggregateThermalMarginArray\": [{\"processorDimmAggregateThermalMarginIdentifier\": \"DIMM1\", \"thermalMargin\": 15.800000}, {\"processorDimmAggregateThermalMarginIdentifier\": \"DIMM2\", \"thermalMargin\": 25.800000}]}, {\"processorIdentifier\": \"PROCESSOR2\", \"processorDtsThermalMargin\": 39.800000, \"processorThermalControlPercent\": 30.900000, \"processorDimmAggregateThermalMarginArray\": [{\"processorDimmAggregateThermalMarginIdentifier\": \"DIMM1\", \"thermalMargin\": 35.800000}, {\"processorDimmAggregateThermalMarginIdentifier\": \"DIMM2\", \"thermalMargin\": 55.800000}]}]}, \"hugePagesArray\": [{\"hugePagesIdentifier\": \"HUGEPage1\", \"bytesUsed\": 100.000000, \"bytesFree\": 200.000000, \"vmPageNumberUsed\": 300.000000, \"vmPageNumberFree\": 400.000000, \"percentUsed\": 100.000000, \"percentFree\": 100.000000}, {\"hugePagesIdentifier\": \"HUGEPage2\", \"bytesUsed\": 180.000000, \"bytesFree\": 280.000000, \"vmPageNumberUsed\": 380.000000, \"vmPageNumberFree\": 480.000000, \"percentUsed\": 180.000000, \"percentFree\": 180.000000}], \"machineCheckExceptionArray\": [{\"vmIdentifier\": \"ProcessID1\", \"correctedMemoryErrors\": 110.100000, \"correctedMemoryErrorsIn1Hr\": 210.100000, \"uncorrectedMemoryErrors\": 310.100000, \"uncorrectedMemoryErrorsIn1Hr\": 410.100000}, {\"vmIdentifier\": \"ProcessID2\", \"correctedMemoryErrors\": 410.100000, \"correctedMemoryErrorsIn1Hr\": 510.100000, \"uncorrectedMemoryErrors\": 610.100000, \"uncorrectedMemoryErrorsIn1Hr\": 710.100000}], \"loadArray\": [{\"shortTerm\": 22.500000, \"midTerm\": 33.600000, \"longTerm\": 44.800000}], \"processStatsArray\": [{\"processIdentifier\": \"Process1\", \"forkRate\": 10.100000, \"psStateBlocked\": 20.100000, \"psStatePaging\": 30.100000, \"psStateRunning\": 40.100000, \"psStateSleeping\": 50.100000, \"psStateStopped\": 60.100000, \"psStateZombie\": 70.100000}, {\"processIdentifier\": \"Process2\", \"forkRate\": 110.100000, \"psStateBlocked\": 120.100000, \"psStatePaging\": 230.100000, \"psStateRunning\": 340.100000, \"psStateSleeping\": 450.100000, \"psStateStopped\": 560.100000, \"psStateZombie\": 670.100000}], \"additionalFields\": {\"name2\": \"value2\", \"name3\": \"value3\", \"name1\": \"value1\", \"name4\": \"value4\"}, \"concurrentSessions\": 1, \"configuredEntities\": 2, \"cpuUsageArray\": [{\"cpuIdentifier\": \"cpu1\", \"cpuIdle\": 22.220000, \"cpuUsageInterrupt\": 33.330000, \"cpuUsageNice\": 44.440000, \"cpuUsageSoftIrq\": 55.550000, \"cpuUsageSteal\": 66.660000, \"cpuUsageSystem\": 77.770000, \"cpuUsageUser\": 88.880000, \"cpuWait\": 99.990000, \"percentUsage\": 11.110000, \"cpuCapacityContention\": 12.200000, \"cpuDemandAvg\": 14.400000, \"cpuDemandMhz\": 15.400000, \"cpuDemandPct\": 16.400000, \"cpuLatencyAvg\": 17.400000, \"cpuOverheadAvg\": 18.400000, \"cpuSwapWaitTime\": 19.400000}, {\"cpuIdentifier\": \"cpu2\", \"cpuIdle\": 12.220000, \"cpuUsageInterrupt\": 33.330000, \"cpuUsageNice\": 44.440000, \"cpuUsageSoftIrq\": 55.550000, \"cpuUsageSteal\": 66.660000, \"cpuUsageSystem\": 77.770000, \"cpuUsageUser\": 88.880000, \"cpuWait\": 19.990000, \"percentUsage\": 22.220000, \"cpuCapacityContention\": 22.200000, \"cpuDemandAvg\": 24.400000, \"cpuDemandMhz\": 25.400000, \"cpuDemandPct\": 26.400000, \"cpuLatencyAvg\": 27.400000, \"cpuOverheadAvg\": 28.400000, \"cpuSwapWaitTime\": 29.400000}], \"diskUsageArray\": [{\"diskIdentifier\": \"Disk1\", \"diskIoTimeAvg\": 11.100000, \"diskIoTimeLast\": 12.100000, \"diskIoTimeMax\": 13.100000, \"diskIoTimeMin\": 14.100000, \"diskMergedReadAvg\": 15.100000, \"diskMergedReadLast\": 16.100000, \"diskMergedReadMax\": 17.100000, \"diskMergedReadMin\": 18.100000, \"diskMergedWriteAvg\": 30.100000, \"diskMergedWriteLast\": 19.100000, \"diskMergedWriteMax\": 20.100000, \"diskMergedWriteMin\": 40.100000, \"diskOctetsReadAvg\": 50.100000, \"diskOctetsReadLast\": 60.100000, \"diskOctetsReadMax\": 70.100000, \"diskOctetsReadMin\": 80.100000, \"diskOctetsWriteAvg\": 90.100000, \"diskOctetsWriteLast\": 110.100000, \"diskOctetsWriteMax\": 120.100000, \"diskOctetsWriteMin\": 130.100000, \"diskOpsReadAvg\": 140.100000, \"diskOpsReadLast\": 150.100000, \"diskOpsReadMax\": 160.100000, \"diskOpsReadMin\": 170.100000, \"diskOpsWriteAvg\": 180.100000, \"diskOpsWriteLast\": 190.100000, \"diskOpsWriteMax\": 210.100000, \"diskOpsWriteMin\": 310.100000, \"diskPendingOperationsAvg\": 410.100000, \"diskPendingOperationsLast\": 610.100000, \"diskPendingOperationsMax\": 710.100000, \"diskPendingOperationsMin\": 810.100000, \"diskTimeReadAvg\": 910.100000, \"diskTimeReadLast\": 10.200000, \"diskTimeReadMax\": 10.330000, \"diskTimeReadMin\": 10.400000, \"diskTimeWriteAvg\": 10.500000, \"diskTimeWriteLast\": 10.600000, \"diskTimeWriteMax\": 10.700000, \"diskTimeWriteMin\": 10.800000, \"diskBusResets\": 10.900000, \"diskCommandsAborted\": 10.100000, \"diskTime\": 10.100000, \"diskFlushRequests\": 10.100000, \"diskFlushTime\": 10.100000, \"diskCommandsAvg\": 10.100000, \"diskReadCommandsAvg\": 10.100000, \"diskWriteCommandsAvg\": 10.100000, \"diskTotalReadLatencyAvg\": 10.100000, \"diskTotalWriteLatencyAvg\": 10.100000, \"diskWeightedIoTimeAvg\": 10.100000, \"diskWeightedIoTimeLast\": 10.100000, \"diskWeightedIoTimeMax\": 10.100000, \"diskWeightedIoTimeMin\": 10.100000}, {\"diskIdentifier\": \"Disk2\", \"diskIoTimeAvg\": 71.100000, \"diskIoTimeLast\": 72.100000, \"diskIoTimeMax\": 73.100000, \"diskIoTimeMin\": 74.100000}], \"filesystemUsageArray\": [{\"filesystemName\": \"00-11-22\", \"blockConfigured\": 100.110000, \"blockIops\": 33.000000, \"blockUsed\": 100.220000, \"ephemeralConfigured\": 200.110000, \"ephemeralIops\": 44.000000, \"ephemeralUsed\": 200.220000}, {\"filesystemName\": \"33-44-55\", \"blockConfigured\": 300.110000, \"blockIops\": 55.000000, \"blockUsed\": 300.220000, \"ephemeralConfigured\": 400.110000, \"ephemeralIops\": 66.000000, \"ephemeralUsed\": 400.220000}], \"latencyDistribution\": [{\"lowEndOfLatencyBucket\": 50.000000, \"highEndOfLatencyBucket\": 60.000000, \"countsInTheBucket\": 20}, {\"lowEndOfLatencyBucket\": 10.000000, \"highEndOfLatencyBucket\": 20.000000, \"countsInTheBucket\": 30}, {\"lowEndOfLatencyBucket\": 70.000000, \"highEndOfLatencyBucket\": 90.000000, \"countsInTheBucket\": 40}], \"meanRequestLatency\": 4.400000, \"requestRate\": 7.000000, \"nicPerformanceArray\": [{\"administrativeState\": \"outOfService\", \"operationalState\": \"inService\", \"receivedPercentDiscard\": 222.330000, \"receivedPercentError\": 222.330000, \"receivedUtilization\": 222.330000, \"speed\": 222.330000, \"transmittedPercentDiscard\": 222.330000, \"transmittedPercentError\": 222.330000, \"transmittedUtilization\": 222.330000, \"receivedBroadcastPacketsAccumulated\": 222.330000, \"receivedBroadcastPacketsDelta\": 222.330000, \"receivedDiscardedPacketsAccumulated\": 222.330000, \"receivedDiscardedPacketsDelta\": 222.330000, \"receivedErrorPacketsAccumulated\": 222.330000, \"receivedErrorPacketsDelta\": 222.330000, \"receivedMulticastPacketsAccumulated\": 222.330000, \"receivedMulticastPacketsDelta\": 222.330000, \"receivedOctetsAccumulated\": 222.330000, \"receivedOctetsDelta\": 222.330000, \"receivedTotalPacketsAccumulated\": 222.330000, \"receivedTotalPacketsDelta\": 222.330000, \"receivedUnicastPacketsAccumulated\": 222.330000, \"receivedUnicastPacketsDelta\": 222.330000, \"transmittedBroadcastPacketsAccumulated\": 222.330000, \"transmittedBroadcastPacketsDelta\": 222.330000, \"transmittedDiscardedPacketsAccumulated\": 222.330000, \"transmittedDiscardedPacketsDelta\": 222.330000, \"transmittedErrorPacketsAccumulated\": 222.330000, \"transmittedErrorPacketsDelta\": 222.330000, \"transmittedMulticastPacketsAccumulated\": 222.330000, \"transmittedMulticastPacketsDelta\": 222.330000, \"transmittedOctetsAccumulated\": 222.330000, \"transmittedOctetsDelta\": 222.330000, \"transmittedTotalPacketsAccumulated\": 222.330000, \"transmittedTotalPacketsDelta\": 222.330000, \"transmittedUnicastPacketsAccumulated\": 222.330000, \"transmittedUnicastPacketsDelta\": 222.330000, \"valuesAreSuspect\": \"true\", \"nicIdentifier\": \"eth0\"}, {\"administrativeState\": \"inService\", \"operationalState\": \"outOfService\", \"receivedPercentDiscard\": 11.660000, \"receivedPercentError\": 11.660000, \"receivedUtilization\": 11.660000, \"speed\": 11.660000, \"transmittedPercentDiscard\": 11.660000, \"transmittedPercentError\": 11.660000, \"transmittedUtilization\": 11.660000, \"receivedBroadcastPacketsAccumulated\": 11.660000, \"receivedBroadcastPacketsDelta\": 11.660000, \"receivedDiscardedPacketsAccumulated\": 11.660000, \"receivedDiscardedPacketsDelta\": 11.660000, \"receivedErrorPacketsAccumulated\": 11.660000, \"receivedErrorPacketsDelta\": 11.660000, \"receivedMulticastPacketsAccumulated\": 11.660000, \"receivedMulticastPacketsDelta\": 11.660000, \"receivedOctetsAccumulated\": 11.660000, \"receivedOctetsDelta\": 11.660000, \"receivedTotalPacketsAccumulated\": 11.660000, \"receivedTotalPacketsDelta\": 11.660000, \"receivedUnicastPacketsAccumulated\": 11.660000, \"receivedUnicastPacketsDelta\": 11.660000, \"transmittedBroadcastPacketsAccumulated\": 11.660000, \"transmittedBroadcastPacketsDelta\": 11.660000, \"transmittedDiscardedPacketsAccumulated\": 11.660000, \"transmittedDiscardedPacketsDelta\": 11.660000, \"transmittedErrorPacketsAccumulated\": 11.660000, \"transmittedErrorPacketsDelta\": 11.660000, \"transmittedMulticastPacketsAccumulated\": 11.660000, \"transmittedMulticastPacketsDelta\": 11.660000, \"transmittedOctetsAccumulated\": 11.660000, \"transmittedOctetsDelta\": 11.660000, \"transmittedTotalPacketsAccumulated\": 11.660000, \"transmittedTotalPacketsDelta\": 11.660000, \"transmittedUnicastPacketsAccumulated\": 11.660000, \"transmittedUnicastPacketsDelta\": 11.660000, \"valuesAreSuspect\": \"false\", \"nicIdentifier\": \"ens03\"}], \"memoryUsageArray\": [{\"memoryCached\": 121.700000, \"memoryConfigured\": 122.700000, \"memoryFree\": 120.000000, \"memorySlabRecl\": 123.700000, \"memorySlabUnrecl\": 124.700000, \"memoryUsed\": 150.000000, \"vmIdentifier\": \"VMID\", \"memoryDemand\": 125.700000, \"memoryLatencyAvg\": 126.700000, \"memorySharedAvg\": 127.700000, \"memorySwapInAvg\": 128.700000, \"memorySwapInRateAvg\": 129.700000, \"memorySwapOutAvg\": 130.700000, \"memorySwapOutRateAvg\": 131.700000, \"memorySwapUsedAvg\": 132.700000, \"percentMemoryUsage\": 133.700000}, {\"memoryBuffered\": 100.400000, \"memoryCached\": 221.700000, \"memoryConfigured\": 222.700000, \"memoryFree\": 220.000000, \"memorySlabRecl\": 223.700000, \"memorySlabUnrecl\": 224.700000, \"memoryUsed\": 250.000000, \"vmIdentifier\": \"VMID2\", \"memoryDemand\": 225.700000, \"memoryLatencyAvg\": 226.700000, \"memorySharedAvg\": 227.700000, \"memorySwapInAvg\": 228.700000, \"memorySwapInRateAvg\": 229.700000, \"memorySwapOutAvg\": 230.700000, \"memorySwapOutRateAvg\": 231.700000, \"memorySwapUsedAvg\": 232.700000, \"percentMemoryUsage\": 233.700000}], \"numberOfMediaPortsInUse\": 55, \"nfcScalingMetric\": 66, \"featureUsageArray\": {\"FeatureA\": \"123\", \"FeatureB\": \"567\"}, \"codecUsageArray\": [{\"codecIdentifier\": \"G711a\", \"numberInUse\": 91}, {\"codecIdentifier\": \"G729ab\", \"numberInUse\": 92}], \"additionalMeasurements\": [{\"name\": \"hmNam1\", \"hashMap\": {\"hmkey1\": \"hmVal1\", \"hmkey4\": \"hmVal4\", \"hmkey2\": \"hmVal2\", \"hmkey3\": \"hmVal3\"}}, {\"name\": \"hmNam2\", \"hashMap\": {\"hmkey24\": \"hmVal24\", \"hmkey22\": \"hmVal22\", \"hmkey23\": \"hmVal23\", \"hmkey21\": \"hmVal21\"}}], \"measurementFieldsVersion\": \"4.0\"}}}";


  size_t json_size = 0;
  char json_body[EVEL_MAX_JSON_BODY];
  EVENT_MEASUREMENT * measurement = NULL;
  MEASUREMENT_LATENCY_BUCKET * bucket = NULL;
  MEASUREMENT_CPU_USE *cpu_use;
  MEASUREMENT_MEM_USE * mem_use;
  MEASUREMENT_DISK_USE * disk_use;
//  evel_set_next_event_sequence(123);
  measurement = evel_new_measurement(5.5,"mvfs_perfUnit_issue", "mvfs000000001");
  assert(measurement != NULL);
  evel_measurement_type_set(measurement, "Perf management...");
  evel_measurement_addl_info_add(measurement, "name1", "value1");

  evel_measurement_addl_info_add(measurement, "name2", "value2");
  evel_measurement_addl_info_add(measurement, "name3", "value3");
  evel_measurement_addl_info_add(measurement, "name4", "value4");

  evel_measurement_conc_sess_set(measurement, 1);
  evel_measurement_cfg_ents_set(measurement, 2);

  evel_measurement_mean_req_lat_set(measurement, 4.4);
  evel_measurement_request_rate_set(measurement, 7);

  cpu_use = evel_measurement_new_cpu_use_add(measurement, "cpu1", 11.11);
  evel_measurement_cpu_use_idle_set(cpu_use,22.22);
  evel_measurement_cpu_use_interrupt_set(cpu_use,33.33);
  evel_measurement_cpu_use_nice_set(cpu_use,44.44);
  evel_measurement_cpu_use_softirq_set(cpu_use,55.55);
  evel_measurement_cpu_use_steal_set(cpu_use,66.66);
  evel_measurement_cpu_use_system_set(cpu_use,77.77);
  evel_measurement_cpu_use_usageuser_set(cpu_use,88.88);
  evel_measurement_cpu_use_wait_set(cpu_use,99.99);
  evel_measurement_cpu_use_cpuCapacityContention_set(cpu_use,12.2);
  evel_measurement_cpu_use_cpuDemandAvg_set(cpu_use,14.4);
  evel_measurement_cpu_use_cpuDemandMhz_set(cpu_use,15.4);
  evel_measurement_cpu_use_cpuDemandPct_set(cpu_use,16.4);
  evel_measurement_cpu_use_cpuLatencyAvg_set(cpu_use,17.4);
  evel_measurement_cpu_use_cpuOverheadAvg_set(cpu_use,18.4);
  evel_measurement_cpu_use_cpuSwapWaitTime_set(cpu_use,19.4);


  cpu_use = evel_measurement_new_cpu_use_add(measurement, "cpu2", 22.22);
  evel_measurement_cpu_use_idle_set(cpu_use,12.22);
  evel_measurement_cpu_use_interrupt_set(cpu_use,33.33);
  evel_measurement_cpu_use_nice_set(cpu_use,44.44);
  evel_measurement_cpu_use_softirq_set(cpu_use,55.55);
  evel_measurement_cpu_use_steal_set(cpu_use,66.66);
  evel_measurement_cpu_use_system_set(cpu_use,77.77);
  evel_measurement_cpu_use_usageuser_set(cpu_use,88.88);
  evel_measurement_cpu_use_wait_set(cpu_use,19.99);
  evel_measurement_cpu_use_cpuCapacityContention_set(cpu_use,22.2);
  evel_measurement_cpu_use_cpuDemandAvg_set(cpu_use,24.4);
  evel_measurement_cpu_use_cpuDemandMhz_set(cpu_use,25.4);
  evel_measurement_cpu_use_cpuDemandPct_set(cpu_use,26.4);
  evel_measurement_cpu_use_cpuLatencyAvg_set(cpu_use,27.4);
  evel_measurement_cpu_use_cpuOverheadAvg_set(cpu_use,28.4);
  evel_measurement_cpu_use_cpuSwapWaitTime_set(cpu_use,29.4);

  mem_use = evel_measurement_new_mem_use_add(measurement, "VMID", 120, 150);
  evel_measurement_mem_use_memcache_set(mem_use, 121.7);
  evel_measurement_mem_use_memconfig_set(mem_use, 122.7);
  evel_measurement_mem_use_slab_reclaimed_set(mem_use, 123.7);
  evel_measurement_mem_use_slab_unreclaimable_set(mem_use, 124.7);
  evel_measurement_mem_use_memoryDemand_set(mem_use, 125.7);
  evel_measurement_mem_use_memoryLatencyAvg_set(mem_use, 126.7);
  evel_measurement_mem_use_memorySharedAvg_set(mem_use, 127.7);
  evel_measurement_mem_use_memorySwapInAvg_set(mem_use, 128.7);
  evel_measurement_mem_use_memorySwapInRateAvg_set(mem_use, 129.7);
  evel_measurement_mem_use_memorySwapOutAvg_set(mem_use, 130.7);
  evel_measurement_mem_use_memorySwapOutRateAvg_set(mem_use, 131.7);
  evel_measurement_mem_use_memorySwapUsedAvg_set(mem_use, 132.7);
  evel_measurement_mem_use_percentMemoryUsage_set(mem_use, 133.7);
  

  mem_use = evel_measurement_new_mem_use_add(measurement, "VMID2", 220, 250);
  evel_measurement_mem_use_mem_buffered_set(mem_use, 100.4);
  evel_measurement_mem_use_memcache_set(mem_use, 221.7);
  evel_measurement_mem_use_memconfig_set(mem_use, 222.7);
  evel_measurement_mem_use_slab_reclaimed_set(mem_use, 223.7);
  evel_measurement_mem_use_slab_unreclaimable_set(mem_use, 224.7);
  evel_measurement_mem_use_memoryDemand_set(mem_use, 225.7);
  evel_measurement_mem_use_memoryLatencyAvg_set(mem_use, 226.7);
  evel_measurement_mem_use_memorySharedAvg_set(mem_use, 227.7);
  evel_measurement_mem_use_memorySwapInAvg_set(mem_use, 228.7);
  evel_measurement_mem_use_memorySwapInRateAvg_set(mem_use, 229.7);
  evel_measurement_mem_use_memorySwapOutAvg_set(mem_use, 230.7);
  evel_measurement_mem_use_memorySwapOutRateAvg_set(mem_use, 231.7);
  evel_measurement_mem_use_memorySwapUsedAvg_set(mem_use, 232.7);
  evel_measurement_mem_use_percentMemoryUsage_set(mem_use, 233.7);

  disk_use = evel_measurement_new_disk_use_add(measurement, "Disk1");
  evel_measurement_disk_use_iotimeavg_set(disk_use, 11.1);
  evel_measurement_disk_use_iotimelast_set(disk_use, 12.1);
  evel_measurement_disk_use_iotimemax_set(disk_use, 13.1);
  evel_measurement_disk_use_iotimemin_set(disk_use, 14.1);
  evel_measurement_disk_use_mergereadavg_set(disk_use, 15.1);
  evel_measurement_disk_use_mergereadlast_set(disk_use, 16.1);
  evel_measurement_disk_use_mergereadmax_set(disk_use, 17.1);
  evel_measurement_disk_use_mergereadmin_set(disk_use, 18.1);
  evel_measurement_disk_use_mergewritelast_set(disk_use, 19.1);
  evel_measurement_disk_use_mergewritemax_set(disk_use, 20.1);
  evel_measurement_disk_use_mergewriteavg_set(disk_use, 30.1);
  evel_measurement_disk_use_mergewritemin_set(disk_use, 40.1);
  evel_measurement_disk_use_octetsreadavg_set(disk_use, 50.1);
  evel_measurement_disk_use_octetsreadlast_set(disk_use, 60.1);
  evel_measurement_disk_use_octetsreadmax_set(disk_use, 70.1);
  evel_measurement_disk_use_octetsreadmin_set(disk_use, 80.1);
  evel_measurement_disk_use_octetswriteavg_set(disk_use, 90.1);
  evel_measurement_disk_use_octetswritelast_set(disk_use,110.1);
  evel_measurement_disk_use_octetswritemax_set(disk_use, 120.1);
  evel_measurement_disk_use_octetswritemin_set(disk_use, 130.1);
  evel_measurement_disk_use_opsreadavg_set(disk_use, 140.1);
  evel_measurement_disk_use_opsreadlast_set(disk_use, 150.1);
  evel_measurement_disk_use_opsreadmax_set(disk_use, 160.1);
  evel_measurement_disk_use_opsreadmin_set(disk_use, 170.1);
  evel_measurement_disk_use_opswriteavg_set(disk_use, 180.1);
  evel_measurement_disk_use_opswritelast_set(disk_use, 190.1);
  evel_measurement_disk_use_opswritemax_set(disk_use, 210.1);
  evel_measurement_disk_use_opswritemin_set(disk_use, 310.1);
  evel_measurement_disk_use_pendingopsavg_set(disk_use, 410.1);
  evel_measurement_disk_use_pendingopslast_set(disk_use, 610.1);
  evel_measurement_disk_use_pendingopsmax_set(disk_use, 710.1);
  evel_measurement_disk_use_pendingopsmin_set(disk_use, 810.1);
  evel_measurement_disk_use_timereadavg_set(disk_use, 910.1);
  evel_measurement_disk_use_timereadlast_set(disk_use, 10.2);
  evel_measurement_disk_use_timereadmax_set(disk_use, 10.33);
  evel_measurement_disk_use_timereadmin_set(disk_use, 10.4);
  evel_measurement_disk_use_timewriteavg_set(disk_use, 10.5);
  evel_measurement_disk_use_timewritelast_set(disk_use, 10.6);
  evel_measurement_disk_use_timewritemax_set(disk_use, 10.7);
  evel_measurement_disk_use_timewritemin_set(disk_use, 10.8);
  evel_measurement_disk_use_diskBusResets_set(disk_use, 10.9);
  evel_measurement_disk_use_diskCommandsAborted_set(disk_use, 10.1);
  evel_measurement_disk_use_diskTime_set(disk_use, 10.1);
  evel_measurement_disk_use_diskFlushRequests_set(disk_use, 10.1);
  evel_measurement_disk_use_diskFlushTime_set(disk_use, 10.1);
  evel_measurement_disk_use_diskCommandsAvg_set(disk_use, 10.1);
  evel_measurement_disk_use_diskReadCommandsAvg_set(disk_use, 10.1);
  evel_measurement_disk_use_diskWriteCommandsAvg_set(disk_use, 10.1);
  evel_measurement_disk_use_diskTotalReadLatencyAvg_set(disk_use, 10.1);
  evel_measurement_disk_use_diskTotalWriteLatencyAvg_set(disk_use, 10.1);
  evel_measurement_disk_use_diskWeightedIoTimeAvg_set(disk_use, 10.1);
  evel_measurement_disk_use_diskWeightedIoTimeLast_set(disk_use, 10.1);
  evel_measurement_disk_use_diskWeightedIoTimeMax_set(disk_use, 10.1);
  evel_measurement_disk_use_diskWeightedIoTimeMin_set(disk_use, 10.1);

  disk_use = evel_measurement_new_disk_use_add(measurement, "Disk2");
  evel_measurement_disk_use_iotimeavg_set(disk_use, 71.1);
  evel_measurement_disk_use_iotimelast_set(disk_use, 72.1);
  evel_measurement_disk_use_iotimemax_set(disk_use, 73.1);
  evel_measurement_disk_use_iotimemin_set(disk_use, 74.1);

  evel_measurement_fsys_use_add(measurement,"00-11-22",100.11, 100.22, 33,
                                200.11, 200.22, 44);

  evel_measurement_fsys_use_add(measurement,"33-44-55",300.11, 300.22, 55,
                                400.11, 400.22, 66);

  evel_measurement_feature_use_add(measurement, "FeatureA", "123");

  evel_measurement_feature_use_add(measurement, "FeatureB", "567");

  HASHTABLE_T *ht1;
  ht1 = evel_measurement_new_addl_measurement(measurement, "hmNam1");
  evel_measurement_addl_measurement_set(ht1, "hmkey1", "hmVal1");

   evel_measurement_addl_measurement_set(ht1, "hmkey2", "hmVal2");
  evel_measurement_addl_measurement_set(ht1, "hmkey3", "hmVal3");
  evel_measurement_addl_measurement_set(ht1, "hmkey4", "hmVal4");

  ht1 = evel_measurement_new_addl_measurement(measurement, "hmNam2");
  evel_measurement_addl_measurement_set(ht1, "hmkey21", "hmVal21");
  evel_measurement_addl_measurement_set(ht1, "hmkey22", "hmVal22");
  evel_measurement_addl_measurement_set(ht1, "hmkey23", "hmVal23");
  evel_measurement_addl_measurement_set(ht1, "hmkey24", "hmVal24");

  evel_measurement_codec_use_add(measurement, "G711a", 91);
  evel_measurement_codec_use_add(measurement, "G729ab", 92);
  
  evel_measurement_media_port_use_set(measurement, 55);
  evel_measurement_vnfc_scaling_metric_set(measurement, 66);

  bucket = evel_new_meas_latency_bucket(20);
  evel_meas_latency_bucket_low_end_set(bucket, 50.0);
  evel_meas_latency_bucket_high_end_set(bucket, 60.0);
  evel_meas_latency_bucket_add(measurement, bucket);

  bucket = evel_new_meas_latency_bucket(30);
  evel_meas_latency_bucket_low_end_set(bucket, 10.0);
  evel_meas_latency_bucket_high_end_set(bucket, 20.0);
  evel_meas_latency_bucket_add(measurement, bucket);

  evel_measurement_latency_add(measurement, 70.0, 90.0, 40);

  MEASUREMENT_NIC_PERFORMANCE * nic_per;
  nic_per = evel_measurement_new_nic_performance("eth0", "true");
  evel_nic_performance_administrativeState_set(nic_per, EVEL_OPER_STATE_OUT_OF_SERVICE);
  evel_nic_performance_operationalState_set(nic_per, EVEL_OPER_STATE_IN_SERVICE);
  evel_nic_performance_receivedPercentDiscard_set(nic_per, 222.33); 
  evel_nic_performance_receivedPercentError_set(nic_per, 222.33);
  evel_nic_performance_receivedUtilization_set(nic_per, 222.33);
  evel_nic_performance_speed_set(nic_per, 222.33);
  evel_nic_performance_transmittedPercentDiscard_set(nic_per, 222.33);
  evel_nic_performance_transmittedPercentError_set(nic_per, 222.33);
  evel_nic_performance_transmittedUtilization_set(nic_per, 222.33);
  evel_nic_performance_rx_bcast_pkt_acc_set(nic_per, 222.33);
  evel_nic_performance_rx_bcast_pkt_delta_set(nic_per, 222.33);
  evel_nic_performance_rx_discard_pkt_acc_set(nic_per, 222.33);
  evel_nic_performance_rx_discard_pkt_delta_set(nic_per, 222.33);
  evel_nic_performance_rx_error_pkt_acc_set(nic_per, 222.33);
  evel_nic_performance_rx_error_pkt_delta_set(nic_per, 222.33);
  evel_nic_performance_rx_mcast_pkt_acc_set(nic_per, 222.33);
  evel_nic_performance_rx_mcast_pkt_delta_set(nic_per, 222.33);
  evel_nic_performance_rx_octets_acc_set(nic_per, 222.33);
  evel_nic_performance_rx_octets_delta_set(nic_per, 222.33);
  evel_nic_performance_rx_total_pkt_acc_set(nic_per, 222.33);
  evel_nic_performance_rx_total_pkt_delta_set(nic_per, 222.33);
  evel_nic_performance_rx_ucast_pkt_acc_set(nic_per, 222.33);
  evel_nic_performance_rx_ucast_pkt_delta_set(nic_per, 222.33);
  evel_nic_performance_tx_bcast_pkt_acc_set(nic_per, 222.33);
  evel_nic_performance_tx_bcast_pkt_delta_set(nic_per, 222.33);
  evel_nic_performance_tx_discarded_pkt_acc_set(nic_per, 222.33);
  evel_nic_performance_tx_discarded_pkt_delta_set(nic_per, 222.33);
  evel_nic_performance_tx_error_pkt_acc_set(nic_per, 222.33);
  evel_nic_performance_tx_error_pkt_delta_set(nic_per, 222.33);
  evel_nic_performance_tx_mcast_pkt_acc_set(nic_per, 222.33);
  evel_nic_performance_tx_mcast_pkt_delta_set(nic_per, 222.33);
  evel_nic_performance_tx_octets_acc_set(nic_per, 222.33);
  evel_nic_performance_tx_octets_delta_set(nic_per, 222.33);
  evel_nic_performance_tx_total_pkt_acc_set(nic_per, 222.33);
  evel_nic_performance_tx_total_pkt_delta_set(nic_per, 222.33);
  evel_nic_performance_tx_ucast_pkt_acc_set(nic_per, 222.33);
  evel_nic_performance_tx_ucast_pkt_delta_set(nic_per, 222.33);

  evel_meas_nic_performance_add(measurement, nic_per);


  evel_measurement_nic_performance_add(measurement, "ens03", "false",
    EVEL_OPER_STATE_IN_SERVICE, EVEL_OPER_STATE_OUT_OF_SERVICE,
    11.66,  11.66, 11.66, 11.66, 11.66, 11.66, 11.66, 11.66, 11.66, 11.66,
    11.66, 11.66, 11.66, 11.66, 11.66, 11.66, 11.66, 11.66, 11.66, 11.66,
    11.66, 11.66, 11.66, 11.66, 11.66, 11.66, 11.66, 11.66, 11.66, 11.66,
    11.66, 11.66, 11.66, 11.66, 11.66);

  MEASUREMENT_IPMI *ipmi;
  ipmi = evel_measurement_new_ipmi_add(measurement);
  evel_measurement_ipmi_exitAirTemperature_set(ipmi, 98.4);
  evel_measurement_ipmi_frontPanelTemperature_set(ipmi, 98.4);
  evel_measurement_ipmi_ioModuleTemperature_set(ipmi, 98.4);
  evel_measurement_ipmi_systemAirflow_set(ipmi, 98.4);

  MEASUREMENT_IPMI_BB_TEMPERATURE *temp;
  temp = evel_measurement_new_base_board_temp_add(ipmi, "BBTEMP1");
  evel_measurement_ipmi_bb_temp_set(ipmi, temp, 99.8);
  temp = evel_measurement_new_base_board_temp_add(ipmi, "BBTEMP2");
  evel_measurement_ipmi_bb_temp_set(ipmi, temp, 79.8);

  MEASUREMENT_IPMI_BB_VOLTAGE * volt;
  volt = evel_measurement_new_base_board_volt_add(ipmi, "BBVOLT1");
  evel_measurement_ipmi_bb_volt_set(ipmi, volt, 88.9);
  volt = evel_measurement_new_base_board_volt_add(ipmi, "BBVOLT2");
  evel_measurement_ipmi_bb_volt_set(ipmi, volt, 68.9);

  MEASUREMENT_IPMI_BATTERY *batt;
  batt = evel_measurement_new_ipmi_battery_add(ipmi, "BBBATTERY1");  
  evel_measurement_ipmi_battery_type_set(ipmi, batt, "BattType");
  evel_measurement_ipmi_battery_voltage_set(ipmi, batt, 230);
  batt = evel_measurement_new_ipmi_battery_add(ipmi, "BBBATTERY2");  
  evel_measurement_ipmi_battery_type_set(ipmi, batt, "BattType2");
  evel_measurement_ipmi_battery_voltage_set(ipmi, batt, 110);
  
  MEASUREMENT_IPMI_FAN * fan;
  fan = evel_measurement_new_ipmi_fan_add(ipmi, "FAN1"); 
  evel_measurement_ipmi_fan_speed_set(ipmi, fan, 300);
  fan = evel_measurement_new_ipmi_fan_add(ipmi, "FAN2"); 
  evel_measurement_ipmi_fan_speed_set(ipmi, fan, 200);

  MEASUREMENT_IPMI_HSBP * hsbp;
  hsbp = evel_measurement_new_ipmi_hsbp_add(ipmi, "BBHSBP1");
  evel_measurement_ipmi_hsbp_temp_set(ipmi, hsbp, 100);
  hsbp = evel_measurement_new_ipmi_hsbp_add(ipmi, "BBHSBP2");
  evel_measurement_ipmi_hsbp_temp_set(ipmi, hsbp, 200);

  MEASUREMENT_IPMI_GLOBAL_AGG_TEMP_MARGIN *glob;
  glob = evel_measurement_new_ipmi_global_temp_add(ipmi, "BBGLOBAL");
  evel_measurement_ipmi_global_temp_margin_set(ipmi, glob, 22.5);
  glob = evel_measurement_new_ipmi_global_temp_add(ipmi, "BBGLOBAL2");
  evel_measurement_ipmi_global_temp_margin_set(ipmi, glob, 32.5);

  MEASUREMENT_IPMI_NIC * nic;
  nic = evel_measurement_new_ipmi_nic_add(ipmi, "NIC_1");
  evel_measurement_ipmi_nic_temp_set(ipmi, nic, 33.5);
  nic = evel_measurement_new_ipmi_nic_add(ipmi, "NIC_2");
  evel_measurement_ipmi_nic_temp_set(ipmi, nic, 43.5);

  MEASUREMENT_IPMI_POWER_SUPPLY * pwr;
  pwr = evel_measurement_new_ipmi_power_add(ipmi, "POWERSupply1");
  evel_measurement_ipmi_power_inputpwr_set(ipmi, pwr, 200.5);
  evel_measurement_ipmi_power_current_op_set(ipmi, pwr, 50.4);
  evel_measurement_ipmi_power_temp_set(ipmi, pwr, 100.5);
  pwr = evel_measurement_new_ipmi_power_add(ipmi, "POWERSupply2");
  evel_measurement_ipmi_power_inputpwr_set(ipmi, pwr, 300.5);
  evel_measurement_ipmi_power_current_op_set(ipmi, pwr, 60.4);
  evel_measurement_ipmi_power_temp_set(ipmi, pwr, 200.5);
   
  MEASUREMENT_IPMI_PROCESSOR * proc;
  proc = evel_measurement_new_ipmi_processor_add(ipmi, "PROCESSOR1");
  evel_measurement_ipmi_processor_theralCtrl_set(ipmi, proc, 10.9);
  evel_measurement_ipmi_processor_theralMargin_set(ipmi, proc, 29.8);
  
  MEASUREMENT_IPMI_PROCESSOR_DIMMAGG_THERM * dimm;
  dimm = evel_measurement_ipmi_processor_new_dimmAggThermalMargin_add(ipmi, proc, "DIMM1", 15.8);
  assert(dimm != NULL);
  dimm = evel_measurement_ipmi_processor_new_dimmAggThermalMargin_add(ipmi, proc, "DIMM2", 25.8);
  assert(dimm != NULL);

  proc = evel_measurement_new_ipmi_processor_add(ipmi, "PROCESSOR2");
  evel_measurement_ipmi_processor_theralCtrl_set(ipmi, proc, 30.9);
  evel_measurement_ipmi_processor_theralMargin_set(ipmi, proc, 39.8);
 
  dimm = evel_measurement_ipmi_processor_new_dimmAggThermalMargin_add(ipmi, proc, "DIMM1", 35.8);
  assert(dimm != NULL);
  dimm = evel_measurement_ipmi_processor_new_dimmAggThermalMargin_add(ipmi, proc, "DIMM2", 55.8);
  assert(dimm != NULL);     

  MEASUREMENT_LOAD * load;
  load = evel_measurement_new_loads_add(measurement);
  evel_measurement_load_shortTerm_set(load, 22.5);
  evel_measurement_load_midTerm_set(load, 33.6);
  evel_measurement_load_longTerm_set(load, 44.8);
  
  MEASUREMENT_PROCESS_STATS * pstat;
  pstat = evel_measurement_new_process_stats_add(measurement, "Process1");
  evel_measurement_process_stat_forkRate_set(pstat, 10.1);
  evel_measurement_process_stat_psStateBlocked_set(pstat, 20.1);
  evel_measurement_process_stat_psStatePaging_set(pstat, 30.1);
  evel_measurement_process_stat_psStateRunning_set(pstat, 40.1);
  evel_measurement_process_stat_psStateSleeping_set(pstat, 50.1);
  evel_measurement_process_stat_psStateStopped_set(pstat, 60.1);
  evel_measurement_process_stat_psStateZombie_set(pstat, 70.1);
  evel_measurement_process_stat_psStateZombie_set(pstat, 80.1);

  pstat = evel_measurement_new_process_stats_add(measurement, "Process2");
  evel_measurement_process_stat_forkRate_set(pstat, 110.1);
  evel_measurement_process_stat_psStateBlocked_set(pstat, 120.1);
  evel_measurement_process_stat_psStatePaging_set(pstat, 230.1);
  evel_measurement_process_stat_psStateRunning_set(pstat, 340.1);
  evel_measurement_process_stat_psStateSleeping_set(pstat, 450.1);
  evel_measurement_process_stat_psStateStopped_set(pstat, 560.1);
  evel_measurement_process_stat_psStateZombie_set(pstat, 670.1);
  evel_measurement_process_stat_psStateZombie_set(pstat, 780.1);

  MACHINE_CHECK_EXCEPTION * mcheck;
  mcheck = evel_measurement_new_machine_check_exception_add(measurement, "ProcessID1");
  evel_measurement_machine_check_cor_mem_err_set(mcheck, 110.1);
  evel_measurement_machine_check_cor_mem_err_1hr_set(mcheck, 210.1);
  evel_measurement_machine_check_uncor_mem_err_set(mcheck, 310.1);
  evel_measurement_machine_check_uncor_mem_err_1hr_set(mcheck, 410.1);

  mcheck = evel_measurement_new_machine_check_exception_add(measurement, "ProcessID2");
  evel_measurement_machine_check_cor_mem_err_set(mcheck, 410.1);
  evel_measurement_machine_check_cor_mem_err_1hr_set(mcheck, 510.1);
  evel_measurement_machine_check_uncor_mem_err_set(mcheck, 610.1);
  evel_measurement_machine_check_uncor_mem_err_1hr_set(mcheck, 710.1);

  MEASUREMENT_HUGE_PAGE * hugep;
  hugep = evel_measurement_new_huge_page_add(measurement, "HUGEPage1");
  evel_measurement_huge_page_bytesUsed_set(hugep, 100);
  evel_measurement_huge_page_bytesFree_set(hugep, 200);
  evel_measurement_huge_page_vmPageNumberUsed_set(hugep, 300);
  evel_measurement_huge_page_vmPageNumberFree_set(hugep, 400);
  evel_measurement_huge_page_percentUsed_set(hugep, 500);
  evel_measurement_huge_page_percentFree_set(hugep, 600);

  hugep = evel_measurement_new_huge_page_add(measurement, "HUGEPage2");
  evel_measurement_huge_page_bytesUsed_set(hugep, 180);
  evel_measurement_huge_page_bytesFree_set(hugep, 280);
  evel_measurement_huge_page_vmPageNumberUsed_set(hugep, 380);
  evel_measurement_huge_page_vmPageNumberFree_set(hugep, 480);
  evel_measurement_huge_page_percentUsed_set(hugep, 580);
  evel_measurement_huge_page_percentFree_set(hugep, 680);

  evel_source_name_set(&measurement->header, "VM-VirtualBox");
  evel_start_epoch_set(&measurement->header, 2000);
  evel_last_epoch_set(&measurement->header, 3000);
  evel_reporting_entity_name_set(&measurement->header, "entity_name");
  evel_reporting_entity_id_set(&measurement->header, "entity_id");

  json_size = evel_json_encode_event(
    json_body, EVEL_MAX_JSON_BODY, (EVENT_HEADER *) measurement);
  compare_strings(expected, json_body, EVEL_MAX_JSON_BODY, "Measurement");
  assert((json_size == strlen(json_body)) && "Bad size returned");

  if(evel_post_event((EVENT_HEADER *)measurement) == EVEL_SUCCESS)
  {
    printf("Message sent to Collector successfully\n");
  }
  else
  {
    printf("Message sending Error\n");
  }

//  evel_free_event(measurement);
}

/**********
void test_encode_mobile_mand()
{
  char * expected =
    "{\"event\": "
    "{\"commonEventHeader\": {"
    "\"domain\": \"mobileFlow\", "
    "\"eventId\": \"mobileFlow000000001\", "
    "\"eventName\": \"mobileFlow_error\", "
    "\"functionalRole\": \"UNIT TEST\", "
    "\"lastEpochMicrosec\": 1000002, "
    "\"priority\": \"Normal\", "
    "\"reportingEntityName\": \"VM-VirtualBox\", "
    "\"sequence\": 1241, "
    "\"sourceName\": \"VM-VirtualBox\", "
    "\"startEpochMicrosec\": 1000002, "
    "\"version\": 1.2, "
    "\"reportingEntityId\": \"Dummy VM UUID - No Metadata available\", "
    "\"sourceId\": \"Dummy VM UUID - No Metadata available\""
    "}, "
    "\"mobileFlowFields\": {"
    "\"flowDirection\": \"Outbound\", "
    "\"gtpPerFlowMetrics\": {"
    "\"avgBitErrorRate\": 12.300000, "
    "\"avgPacketDelayVariation\": 3.120000, "
    "\"avgPacketLatency\": 100, "
    "\"avgReceiveThroughput\": 2100, "
    "\"avgTransmitThroughput\": 500, "
    "\"flowActivationEpoch\": 1470409421, "
    "\"flowActivationMicrosec\": 987, "
    "\"flowDeactivationEpoch\": 1470409431, "
    "\"flowDeactivationMicrosec\": 11, "
    "\"flowDeactivationTime\": \"Fri, 05 Aug 2016 15:03:51 +0000\", "
    "\"flowStatus\": \"Working\", "
    "\"maxPacketDelayVariation\": 87, "
    "\"numActivationFailures\": 3, "
    "\"numBitErrors\": 17, "
    "\"numBytesReceived\": 123654, "
    "\"numBytesTransmitted\": 4561, "
    "\"numDroppedPackets\": 0, "
    "\"numL7BytesReceived\": 12, "
    "\"numL7BytesTransmitted\": 10, "
    "\"numLostPackets\": 1, "
    "\"numOutOfOrderPackets\": 3, "
    "\"numPacketErrors\": 7, "
    "\"numPacketsReceivedExclRetrans\": 899, "
    "\"numPacketsReceivedInclRetrans\": 901, "
    "\"numPacketsTransmittedInclRetrans\": 302, "
    "\"numRetries\": 6, "
    "\"numTimeouts\": 2, "
    "\"numTunneledL7BytesReceived\": 0, "
    "\"roundTripTime\": 110, "
    "\"timeToFirstByte\": 225"
    "}, "
    "\"ipProtocolType\": \"TCP\", "
    "\"ipVersion\": \"IPv4\", "
    "\"otherEndpointIpAddress\": \"2.3.4.1\", "
    "\"otherEndpointPort\": 2341, "
    "\"reportingEndpointIpAddr\": \"4.2.3.1\", "
    "\"reportingEndpointPort\": 4321"
    "}}}";

  size_t json_size = 0;
  char json_body[EVEL_MAX_JSON_BODY];
  MOBILE_GTP_PER_FLOW_METRICS * metrics = NULL;
  EVENT_MOBILE_FLOW * mobile_flow = NULL;

//  evel_set_next_event_sequence(1241);

  metrics = evel_new_mobile_gtp_flow_metrics(12.3,
                                             3.12,
                                             100,
                                             2100,
                                             500,
                                             1470409421,
                                             987,
                                             1470409431,
                                             11,
                                             (time_t)1470409431,
                                             "Working",
                                             87,
                                             3,
                                             17,
                                             123654,
                                             4561,
                                             0,
                                             12,
                                             10,
                                             1,
                                             3,
                                             7,
                                             899,
                                             901,
                                             302,
                                             6,
                                             2,
                                             0,
                                             110,
                                             225);
  assert(metrics != NULL);
  mobile_flow = evel_new_mobile_flow("mobileFlow_error", 
                                     "mobileFlow000000001", 
                                     "Outbound",
                                     metrics,
                                     "TCP",
                                     "IPv4",
                                     "2.3.4.1",
                                     2341,
                                     "4.2.3.1",
                                     4321);
  assert(mobile_flow != NULL);
  evel_source_name_set(&mobile_flow->header, "VM-VirtualBox");
  evel_reporting_entity_name_set(&mobile_flow->header, "VM-VirtualBox");

  json_size = evel_json_encode_event(
    json_body, EVEL_MAX_JSON_BODY, (EVENT_HEADER *) mobile_flow);
  compare_strings(expected, json_body, EVEL_MAX_JSON_BODY, "Mobile");
  assert((json_size == strlen(json_body)) && "Bad size returned");

  if(evel_post_event((EVENT_HEADER *)mobile_flow) == EVEL_SUCCESS)
  {
    printf("Message sent to Collector successfully\n");
  }
  else
  {
    printf("Message sending Error\n");
  }

  //evel_free_event(mobile_flow);
}
*******************/

void test_encode_mobile_opts()
{
  char * expected =
"{\"event\": {\"commonEventHeader\": {\"domain\": \"mobileFlow\", \"eventId\": \"mobileFlow000000001\", \"eventName\": \"mobileFlow_error\", \"vesEventListenerVersion\": \"7.1\", \"lastEpochMicrosec\": 1000002, \"priority\": \"Normal\", \"reportingEntityName\": \"VM-VirtualBox\", \"sequence\": 0, \"sourceName\": \"VM-VirtualBox\", \"startEpochMicrosec\": 1000002, \"version\": \"4.1\", \"eventType\": \"Mobile flow...\"}, \"mobileFlowFields\": {\"additionalFields\": {\"Mkey1\": \"MValue1\", \"Mkey2\": \"MValue2\"}, \"flowDirection\": \"Inbound\", \"gtpPerFlowMetrics\": {\"avgBitErrorRate\": 132.000100, \"avgPacketDelayVariation\": 31.200000, \"avgPacketLatency\": 101, \"avgReceiveThroughput\": 2101, \"avgTransmitThroughput\": 501, \"flowActivationEpoch\": 1470409422, \"flowActivationMicrosec\": 988, \"flowDeactivationEpoch\": 1470409432, \"flowDeactivationMicrosec\": 12, \"flowDeactivationTime\": \"Fri, 05 Aug 2016 15:03:52 +0000\", \"flowStatus\": \"Inactive\", \"maxPacketDelayVariation\": 88, \"numActivationFailures\": 4, \"numBitErrors\": 18, \"numBytesReceived\": 123655, \"numBytesTransmitted\": 4562, \"numDroppedPackets\": 1, \"numL7BytesReceived\": 13, \"numL7BytesTransmitted\": 11, \"numLostPackets\": 2, \"numOutOfOrderPackets\": 4, \"numPacketErrors\": 8, \"numPacketsReceivedExclRetrans\": 900, \"numPacketsReceivedInclRetrans\": 902, \"numPacketsTransmittedInclRetrans\": 303, \"numRetries\": 7, \"numTimeouts\": 3, \"numTunneledL7BytesReceived\": 1, \"roundTripTime\": 111, \"timeToFirstByte\": 226, \"durConnectionFailedStatus\": 12, \"durTunnelFailedStatus\": 13, \"flowActivatedBy\": \"Remote\", \"flowActivationTime\": \"Fri, 05 Aug 2016 15:03:43 +0000\", \"flowDeactivatedBy\": \"Remote\", \"gtpConnectionStatus\": \"Connected\", \"gtpTunnelStatus\": \"Not tunneling\", \"largePacketRtt\": 80, \"largePacketThreshold\": 600.000000, \"maxReceiveBitRate\": 1357924680, \"maxTransmitBitRate\": 235711, \"numGtpEchoFailures\": 1, \"numGtpTunnelErrors\": 4, \"numHttpErrors\": 2, \"ipTosCountList\": {\"17\": \"1\", \"1\": \"13\", \"4\": \"99\"}, \"ipTosList\": [\"17\", \"1\", \"4\"], \"mobileQciCosCountList\": {\"65\": \"122\", \"conversational\": \"11\"}, \"mobileQciCosList\": [\"65\", \"conversational\"], \"tcpFlagCountList\": {\"CWR\": \"10\", \"URG\": \"121\"}, \"tcpFlagList\": [\"CWR\", \"URG\"]}, \"ipProtocolType\": \"UDP\", \"ipVersion\": \"IPv6\", \"otherEndpointIpAddress\": \"2.3.4.2\", \"otherEndpointPort\": 2342, \"reportingEndpointIpAddr\": \"4.2.3.2\", \"reportingEndpointPort\": 4322, \"applicationType\": \"Demo application\", \"appProtocolType\": \"GSM\", \"appProtocolVersion\": \"1\", \"cid\": \"65535\", \"connectionType\": \"S1-U\", \"ecgi\": \"e65535\", \"gtpProtocolType\": \"GTP-U\", \"gtpVersion\": \"1\", \"httpHeader\": \"http://www.something.com\", \"imei\": \"209917614823\", \"imsi\": \"355251/05/850925/8\", \"lac\": \"1\", \"mcc\": \"410\", \"mnc\": \"04\", \"msisdn\": \"6017123456789\", \"otherFunctionalRole\": \"MME\", \"rac\": \"514\", \"radioAccessTechnology\": \"LTE\", \"sac\": \"1\", \"samplingAlgorithm\": 1, \"tac\": \"2099\", \"tunnelId\": \"Tunnel 1\", \"vlanId\": \"15\", \"mobileFlowFieldsVersion\": \"4.0\"}}}";

  size_t json_size = 0;
  char json_body[EVEL_MAX_JSON_BODY];
  MOBILE_GTP_PER_FLOW_METRICS * metrics = NULL;
  EVENT_MOBILE_FLOW * mobile_flow = NULL;

  /***************************************************************************/
  /* Mobile.                                                                 */
  /***************************************************************************/
//  evel_set_next_event_sequence(1242);

  metrics = evel_new_mobile_gtp_flow_metrics(132.0001,
                                             31.2,
                                             101,
                                             2101,
                                             501,
                                             1470409422,
                                             988,
                                             1470409432,
                                             12,
                                             (time_t)1470409432,
                                             "Inactive",
                                             88,
                                             4,
                                             18,
                                             123655,
                                             4562,
                                             1,
                                             13,
                                             11,
                                             2,
                                             4,
                                             8,
                                             900,
                                             902,
                                             303,
                                             7,
                                             3,
                                             1,
                                             111,
                                             226);
  assert(metrics != NULL);

  evel_mobile_gtp_metrics_dur_con_fail_set(metrics, 12);
  evel_mobile_gtp_metrics_dur_tun_fail_set(metrics, 13);
  evel_mobile_gtp_metrics_act_by_set(metrics, "Remote");
  evel_mobile_gtp_metrics_act_time_set(metrics, (time_t)1470409423);
  evel_mobile_gtp_metrics_deact_by_set(metrics, "Remote");
  evel_mobile_gtp_metrics_con_status_set(metrics, "Connected");
  evel_mobile_gtp_metrics_tun_status_set(metrics, "Not tunneling");

//  evel_mobile_gtp_metrics_iptos_set(metrics, 1, 13);
//  evel_mobile_gtp_metrics_iptos_set(metrics, 17, 1);
//  evel_mobile_gtp_metrics_iptos_set(metrics, 4, 99);

  evel_mobile_gtp_metrics_ip_tos_count_list_add(metrics, "1", "13");
  evel_mobile_gtp_metrics_ip_tos_count_list_add(metrics, "17", "1");
  evel_mobile_gtp_metrics_ip_tos_count_list_add(metrics, "4", "99");

  evel_mobile_gtp_metrics_large_pkt_rtt_set(metrics, 80);
  evel_mobile_gtp_metrics_large_pkt_thresh_set(metrics, 600.0);
  evel_mobile_gtp_metrics_max_rcv_bit_rate_set(metrics, 1357924680);
  evel_mobile_gtp_metrics_max_trx_bit_rate_set(metrics, 235711);
  evel_mobile_gtp_metrics_num_echo_fail_set(metrics, 1);
  evel_mobile_gtp_metrics_num_tun_fail_set(metrics, 4);
  evel_mobile_gtp_metrics_num_http_errors_set(metrics, 2);

//  evel_mobile_gtp_metrics_tcp_flag_count_add(metrics, EVEL_TCP_CWR, 10);
//  evel_mobile_gtp_metrics_tcp_flag_count_add(metrics, EVEL_TCP_URG, 121);


  evel_mobile_gtp_metrics_tcp_flag_count_list_add(metrics, EVEL_TCP_CWR, "10");
  evel_mobile_gtp_metrics_tcp_flag_count_list_add(metrics, EVEL_TCP_URG, "121");

//  evel_mobile_gtp_metrics_qci_cos_count_add( metrics, EVEL_QCI_COS_UMTS_CONVERSATIONAL, 11);
//  evel_mobile_gtp_metrics_qci_cos_count_add( metrics, EVEL_QCI_COS_LTE_65, 122);

  evel_mobile_gtp_metrics_qci_cos_count_list_add(metrics, EVEL_QCI_COS_UMTS_CONVERSATIONAL, "11");
  evel_mobile_gtp_metrics_qci_cos_count_list_add(metrics, EVEL_QCI_COS_LTE_65, "122");

  mobile_flow = evel_new_mobile_flow("mobileFlow_error",
                                     "mobileFlow000000001",
                                     "Inbound",
                                     metrics,
                                     "UDP",
                                     "IPv6",
                                     "2.3.4.2",
                                     2342,
                                     "4.2.3.2",
                                     4322);
  assert(mobile_flow != NULL);

  evel_source_name_set(&mobile_flow->header, "VM-VirtualBox");
  evel_reporting_entity_name_set(&mobile_flow->header, "VM-VirtualBox");
  evel_mobile_flow_type_set(mobile_flow, "Mobile flow...");
  evel_mobile_flow_app_type_set(mobile_flow, "Demo application");
  evel_mobile_flow_app_prot_type_set(mobile_flow, "GSM");
  evel_mobile_flow_app_prot_ver_set(mobile_flow, "1");
  evel_mobile_flow_cid_set(mobile_flow, "65535");
  evel_mobile_flow_con_type_set(mobile_flow, "S1-U");
  evel_mobile_flow_ecgi_set(mobile_flow, "e65535");
  evel_mobile_flow_gtp_prot_type_set(mobile_flow, "GTP-U");
  evel_mobile_flow_gtp_prot_ver_set(mobile_flow, "1");
  evel_mobile_flow_http_header_set(mobile_flow,
                                   "http://www.something.com");
  evel_mobile_flow_imei_set(mobile_flow, "209917614823");
  evel_mobile_flow_imsi_set(mobile_flow, "355251/05/850925/8");
  evel_mobile_flow_lac_set(mobile_flow, "1");
  evel_mobile_flow_mcc_set(mobile_flow, "410");
  evel_mobile_flow_mnc_set(mobile_flow, "04");
  evel_mobile_flow_msisdn_set(mobile_flow, "6017123456789");
  evel_mobile_flow_other_func_role_set(mobile_flow, "MME");
  evel_mobile_flow_rac_set(mobile_flow, "514");
  evel_mobile_flow_radio_acc_tech_set(mobile_flow, "LTE");
  evel_mobile_flow_sac_set(mobile_flow, "1");
  evel_mobile_flow_samp_alg_set(mobile_flow, 1);
  evel_mobile_flow_tac_set(mobile_flow, "2099");
  evel_mobile_flow_tunnel_id_set(mobile_flow, "Tunnel 1");
  evel_mobile_flow_vlan_id_set(mobile_flow, "15");
  evel_mobile_flow_addl_field_add(mobile_flow, "Mkey1", "MValue1");
  evel_mobile_flow_addl_field_add(mobile_flow, "Mkey2", "MValue2");

  json_size = evel_json_encode_event(
    json_body, EVEL_MAX_JSON_BODY, (EVENT_HEADER *) mobile_flow);
  compare_strings(expected, json_body, EVEL_MAX_JSON_BODY, "Mobile");
  assert((json_size == strlen(json_body)) && "Bad size returned");

  if(evel_post_event((EVENT_HEADER *)mobile_flow) == EVEL_SUCCESS)
  {
    printf("Message sent to Collector successfully\n");
  }
  else
  {
    printf("Message sending Error\n");
  }
//  evel_free_event(mobile_flow);
}

void test_encode_signaling()
{
  char * expected =
"{\"event\": {\"commonEventHeader\": {\"domain\": \"sipSignaling\", \"eventId\": \"sipSignal0000000001\", \"eventName\": \"sipSignal_err\", \"vesEventListenerVersion\": \"7.1\", \"lastEpochMicrosec\": 1000002, \"priority\": \"Normal\", \"reportingEntityName\": \"VM-VirtualBox\", \"sequence\": 0, \"sourceName\": \"VM-VirtualBox\", \"startEpochMicrosec\": 1000002, \"version\": \"4.1\", \"eventType\": \"Signaling\"}, \"sipSignalingFields\": {\"compressedSip\": \"compressed_sip\", \"correlator\": \"correlator\", \"localIpAddress\": \"1.0.3.1\", \"localPort\": \"1234\", \"remoteIpAddress\": \"192.168.1.3\", \"remotePort\": \"3456\", \"sipSignalingFieldsVersion\": \"3.0\", \"summarySip\": \"summary_sip\", \"vendorNfNameFields\": {\"vendorName\": \"vendor_x_id\", \"nfModuleName\": \"vendor_x_module\", \"nfName\": \"vendor_x_vnf\"}, \"additionalInformation\": {\"name2\": \"value2\", \"name3\": \"value3\", \"name1\": \"value1\", \"name4\": \"value4\"}}}}";

  size_t json_size = 0;
  char json_body[EVEL_MAX_JSON_BODY];
  EVENT_SIGNALING * event = NULL;
//  evel_set_next_event_sequence(2001);
  event = evel_new_signaling("sipSignal_err",
           "sipSignal0000000001", "vendor_x_id",
           "correlator", "1.0.3.1", "1234", "192.168.1.3","3456");
  assert(event != NULL);
  evel_source_name_set(&event->header, "VM-VirtualBox");
  evel_reporting_entity_name_set(&event->header, "VM-VirtualBox");

  evel_signaling_addl_info_add(event, "name1", "value1");
  evel_signaling_addl_info_add(event, "name2", "value2");
  evel_signaling_addl_info_add(event, "name3", "value3");
  evel_signaling_addl_info_add(event, "name4", "value4");

  evel_signaling_type_set(event, "Signaling");
  evel_signaling_local_ip_address_set(event, "1.0.3.1");
  evel_signaling_local_port_set(event, "1031");
  evel_signaling_remote_ip_address_set(event, "5.3.3.0");
  evel_signaling_remote_port_set(event, "5330");
  evel_signaling_vnfmodule_name_set(event, "vendor_x_module");
  evel_signaling_vnfname_set(event, "vendor_x_vnf");
  evel_signaling_compressed_sip_set(event, "compressed_sip");
  evel_signaling_summary_sip_set(event, "summary_sip");
  evel_signaling_correlator_set(event, "vendor_x_correlator");


  json_size = evel_json_encode_event(
    json_body, EVEL_MAX_JSON_BODY, (EVENT_HEADER *) event);
  compare_strings(expected, json_body, EVEL_MAX_JSON_BODY, "Signaling");
  assert((json_size == strlen(json_body)) && "Bad size returned");

  if(evel_post_event((EVENT_HEADER *)event) == EVEL_SUCCESS)
  {
    printf("Message sent to Collector successfully\n");
  }
  else
  {
    printf("Message sending Error\n");
  }

//  evel_free_event(event);
}

void test_encode_notif()
{
  char * expected = 
"{\"event\": {\"commonEventHeader\": {\"domain\": \"notification\", \"eventId\": \"Notification0000000001\", \"eventName\": \"notif_err\", \"vesEventListenerVersion\": \"7.1\", \"lastEpochMicrosec\": 1000002, \"priority\": \"Normal\", \"reportingEntityName\": \"VM-VirtualBox\", \"sequence\": 0, \"sourceName\": \"VM-VirtualBox\", \"startEpochMicrosec\": 1000002, \"version\": \"4.1\", \"eventType\": \"Event_type\"}, \"notificationFields\": {\"changeIdentifier\": \"ChangeId\", \"changeType\": \"ChangeType\", \"newState\": \"maintenance\", \"oldState\": \"outOfService\", \"changeContact\": \"ChangeContact\", \"stateInterface\": \"STInterface\", \"additionalFields\": {\"name2\": \"value2\", \"name3\": \"value3\", \"name1\": \"value1\", \"name4\": \"value4\"}, \"arrayOfNamedHashMap\": [{\"name\": \"hmNam1\", \"hashMap\": {\"hmnap1\": \"hmvalue1\", \"hmnap3\": \"hmvalue3\", \"hmnap2\": \"hmvalue2\", \"hmnap4\": \"hmvalue4\"}}, {\"name\": \"hmNam2\", \"hashMap\": {\"hmnap24\": \"hmvalue24\", \"hmnap21\": \"hmvalue21\", \"hmnap22\": \"hmvalue22\", \"hmnap23\": \"hmvalue23\"}}], \"notificationFieldsVersion\": \"2.0\"}}}";

  HASHTABLE_T * ht1 = NULL;
  size_t json_size = 0;
  char json_body[EVEL_MAX_JSON_BODY];
  EVENT_NOTIFICATION * event = NULL;
  event = evel_new_notification("notif_err",
           "Notification0000000001", "ChangeId",
           "ChangeType");

  assert(event != NULL);
  evel_source_name_set(&event->header, "VM-VirtualBox");
  evel_reporting_entity_name_set(&event->header, "VM-VirtualBox");

  evel_notification_type_set(event, "Event_type");
  evel_notification_changeContact_set(event, "ChangeContact");
  evel_notification_state_interface_set(event, "STInterface");
  evel_notification_new_state_set(event, EVEL_ENTITY_STATE_MAINTENANCE);
  evel_notification_old_state_set(event, EVEL_ENTITY_STATE_OUT_OF_SERVICE);
  
  evel_notification_addl_field_add(event, "name1", "value1");
  evel_notification_addl_field_add(event, "name2", "value2");
  evel_notification_addl_field_add(event, "name3", "value3");
  evel_notification_addl_field_add(event, "name4", "value4");

  ht1 = evel_notification_add_new_named_hashmap(event, "hmNam1");
  evel_notification_named_hashmap_set(ht1, "hmnap1", "hmvalue1");
  evel_notification_named_hashmap_set(ht1, "hmnap2", "hmvalue2");
  evel_notification_named_hashmap_set(ht1, "hmnap3", "hmvalue3");
  evel_notification_named_hashmap_set(ht1, "hmnap4", "hmvalue4");
  ht1 = evel_notification_add_new_named_hashmap(event, "hmNam2");
  evel_notification_named_hashmap_set(ht1, "hmnap21", "hmvalue21");
  evel_notification_named_hashmap_set(ht1, "hmnap22", "hmvalue22");
  evel_notification_named_hashmap_set(ht1, "hmnap23", "hmvalue23");
  evel_notification_named_hashmap_set(ht1, "hmnap24", "hmvalue24");


  json_size = evel_json_encode_event(
    json_body, EVEL_MAX_JSON_BODY, (EVENT_HEADER *) event);
  compare_strings(expected, json_body, EVEL_MAX_JSON_BODY, "Notification");
  assert((json_size == strlen(json_body)) && "Bad size returned");

  if(evel_post_event((EVENT_HEADER *)event) == EVEL_SUCCESS)
  {
    printf("Message sent to Collector successfully\n");
  }
  else
  {
    printf("Message sending Error\n");
  }

//  evel_free_event(event);
}

void test_encode_voiceQ()
{
  char * expected =
"{\"event\": {\"commonEventHeader\": {\"domain\": \"voiceQuality\", \"eventId\": \"VoiceQuality0000000001\", \"eventName\": \"voiceQ_err\", \"vesEventListenerVersion\": \"7.1\", \"lastEpochMicrosec\": 1000002, \"priority\": \"Normal\", \"reportingEntityName\": \"VM-VirtualBox\", \"sequence\": 0, \"sourceName\": \"VM-VirtualBox\", \"startEpochMicrosec\": 1000002, \"version\": \"4.1\"}, \"voiceQualityFields\": {\"calleeSideCodec\": \"Callee_cdc1\", \"callerSideCodec\": \"Caller_cdc1\", \"correlator\": \"CorrNew\", \"midCallRtcp\": \"RTCPNew\", \"vendorNfNameFields\": {\"vendorName\": \"Vendor_x\", \"nfModuleName\": \"vendor_x_module\", \"nfName\": \"vendor_x_vnf\"}, \"voiceQualityFieldsVersion\": \"4.0\", \"phoneNumber\": \"1234567890\", \"additionalInformation\": {\"name2\": \"value2\", \"name3\": \"value3\", \"name1\": \"value1\", \"name4\": \"value4\"}, \"endOfCallVqmSummaries\": {\"adjacencyName\": \"Adj_name\", \"endpointDescription\": \"Callee\", \"localRtpOctetsLost\": 1, \"endpointRtpOctetsDiscarded\": 2, \"endpointRtpOctetsReceived\": 3, \"endpointRtpOctetsSent\": 4, \"endpointRtpPacketsDiscarded\": 5, \"endpointRtpPacketsReceived\": 6, \"endpointRtpPacketsSent\": 7, \"localMaxJitterBufferDelay\": 8, \"localRtpOctetsDiscarded\": 9, \"localRtpOctetsReceived\": 10, \"localRtpOctetsSent\": 11, \"localRtpPacketsDiscarded\": 12, \"localRtpPacketsReceived\": 1, \"localRtpPacketsSent\": 2, \"mosCqe\": 3, \"localRtpPacketsLost\": 16, \"packetLossPercent\": 17, \"rFactor\": 18, \"roundTripDelay\": 19, \"endpointAverageJitter\": 20, \"endpointMaxJitter\": 21, \"endpointRtpOctetsLost\": 22, \"endpointRtpPacketsLost\": 23, \"localAverageJitter\": 24, \"localAverageJitterBufferDelay\": 25, \"localMaxJitter\": 26, \"oneWayDelay\": 27}}}}";

  size_t json_size = 0;
  char json_body[EVEL_MAX_JSON_BODY];
  EVENT_VOICE_QUALITY * event = NULL;
//  evel_set_next_event_sequence(2001);
  event = evel_new_voice_quality("voiceQ_err",
           "VoiceQuality0000000001", "Called_Codec",
           "Caller_codec", "Correlator", "RTCP", "Vendor_x");
  assert(event != NULL);
  evel_source_name_set(&event->header, "VM-VirtualBox");
  evel_reporting_entity_name_set(&event->header, "VM-VirtualBox");

  evel_voice_quality_addl_info_add(event, "name1", "value1");
  evel_voice_quality_addl_info_add(event, "name2", "value2");
  evel_voice_quality_addl_info_add(event, "name3", "value3");
  evel_voice_quality_addl_info_add(event, "name4", "value4");

  evel_voice_quality_callee_codec_set(event, "Callee_cdc1");
  evel_voice_quality_caller_codec_set(event, "Caller_cdc1");
  
  evel_voice_quality_correlator_set(event, "CorrNew");
  evel_voice_quality_rtcp_data_set(event, "RTCPNew");
  evel_voice_quality_vnfmodule_name_set(event, "vendor_x_module");
  evel_voice_quality_vnfname_set(event, "vendor_x_vnf");
  evel_voice_quality_phone_number_set(event, "1234567890");
  evel_voice_quality_end_metrics_add(event, "Adj_name", EVEL_SERVICE_ENDPOINT_CALLEE, 1,2,3,4,5,6,7,8,9,10,11,12,1,2,3,16,17,18,19,20,21,22,23,24,25,26,27);

  json_size = evel_json_encode_event(
    json_body, EVEL_MAX_JSON_BODY, (EVENT_HEADER *) event);
  compare_strings(expected, json_body, EVEL_MAX_JSON_BODY, "VoiceQuality");
  assert((json_size == strlen(json_body)) && "Bad size returned");

  if(evel_post_event((EVENT_HEADER *)event) == EVEL_SUCCESS)
  {
    printf("Message sent to Collector successfully\n");
  }
  else
  {
    printf("Message sending Error\n");
  }

//  evel_free_event(event);
}

void test_encode_state_change()
{
  char * expected =
"{\"event\": {\"commonEventHeader\": {\"domain\": \"stateChange\", \"eventId\": \"stateChange000000001\", \"eventName\": \"stateChange_err\", \"vesEventListenerVersion\": \"7.1\", \"lastEpochMicrosec\": 1000002, \"priority\": \"Normal\", \"reportingEntityName\": \"VM-VirtualBox\", \"sequence\": 0, \"sourceName\": \"VM-VirtualBox\", \"startEpochMicrosec\": 1000002, \"version\": \"4.1\", \"eventType\": \"SC Type\"}, \"stateChangeFields\": {\"newState\": \"inService\", \"oldState\": \"maintenance\", \"stateInterface\": \"An Interface\", \"additionalFields\": {\"Name2\": \"Value2\", \"Name1\": \"Value1\"}, \"stateChangeFieldsVersion\": \"4.0\"}}}";

  size_t json_size = 0;
  char json_body[EVEL_MAX_JSON_BODY];
  EVENT_STATE_CHANGE * state_change = NULL;
//  evel_set_next_event_sequence(128);
  state_change = evel_new_state_change("stateChange_err",
                                       "stateChange000000001",
                                       EVEL_ENTITY_STATE_IN_SERVICE,
                                       EVEL_ENTITY_STATE_MAINTENANCE,
                                       "An Interface");
  assert(state_change != NULL);
  evel_source_name_set(&state_change->header, "VM-VirtualBox");
  evel_reporting_entity_name_set(&state_change->header, "VM-VirtualBox");
  evel_state_change_type_set(state_change, "SC Type");
  evel_state_change_addl_field_add(state_change, "Name1", "Value1");
  evel_state_change_addl_field_add(state_change, "Name2", "Value2");

  json_size = evel_json_encode_event(
    json_body, EVEL_MAX_JSON_BODY, (EVENT_HEADER *) state_change);
  compare_strings(expected, json_body, EVEL_MAX_JSON_BODY, "StateChange");
  assert((json_size == strlen(json_body)) && "Bad size returned");

  if(evel_post_event((EVENT_HEADER *)state_change) == EVEL_SUCCESS)
  {
    printf("Message sent to Collector successfully\n");
  }
  else
  {
    printf("Message sending Error\n");
  }

//  evel_free_event(state_change);
}

void test_encode_syslog()
{
  char * expected =
"{\"event\": {\"commonEventHeader\": {\"domain\": \"syslog\", \"eventId\": \"syslog000000001\", \"eventName\": \"syslog_err\", \"vesEventListenerVersion\": \"7.1\", \"lastEpochMicrosec\": 1000002, \"priority\": \"Normal\", \"reportingEntityName\": \"VM-VirtualBox\", \"sequence\": 0, \"sourceName\": \"VM-VirtualBox\", \"startEpochMicrosec\": 1000002, \"version\": \"4.1\", \"eventType\": \"SL Type\"}, \"syslogFields\": {\"additionalFields\": {\"Name2\": \"Value2\", \"Name4\": \"Value4\", \"Name5\": \"Value5\", \"Name3\": \"Value3\", \"Name1\": \"Value1\"}, \"eventSourceType\": \"virtualNetworkFunction\", \"syslogMsg\": \"SL Message\", \"syslogTag\": \"SL Tag\", \"syslogFieldsVersion\": \"4.0\", \"eventSourceHost\": \"SL Host\", \"syslogFacility\": 6, \"syslogPri\": 15, \"syslogProc\": \"SL Proc\", \"syslogProcId\": 2, \"syslogSData\": \"SL SDATA\", \"syslogSdId\": \"ourSDID@12345\", \"syslogSev\": \"Alert\", \"syslogVer\": 1, \"syslogMsgHost\": \"hostName123\", \"syslogTs\": \"12-DEC-2018\"}}}";

  size_t json_size = 0;
  char json_body[EVEL_MAX_JSON_BODY];
  EVENT_SYSLOG * syslog = NULL;
//  evel_set_next_event_sequence(126);
  syslog = evel_new_syslog("syslog_err", "syslog000000001", 
                           EVEL_SOURCE_VIRTUAL_NETWORK_FUNCTION,
                           "SL Message",
                           "SL Tag");
  assert(syslog != NULL);
  evel_source_name_set(&syslog->header, "VM-VirtualBox");
  evel_reporting_entity_name_set(&syslog->header, "VM-VirtualBox");
  evel_syslog_type_set(syslog, "SL Type");
  evel_syslog_event_source_host_set(syslog, "SL Host");
  evel_syslog_facility_set(syslog, EVEL_SYSLOG_FACILITY_LINE_PRINTER);
  evel_syslog_proc_set(syslog, "SL Proc");
  evel_syslog_proc_id_set(syslog, 2);
  evel_syslog_version_set(syslog, 1);
  evel_syslog_s_data_set(syslog, "SL SDATA");
  evel_syslog_sdid_set(syslog, "ourSDID@12345");
  evel_syslog_severity_set(syslog, "Alert");
  evel_syslog_timeStamp_set(syslog, "12-DEC-2018");
  evel_syslog_MsgHost_set(syslog, "hostName123");
  evel_syslog_priority_set(syslog, 15);
  
  evel_syslog_addl_fields_set(syslog, "Name1", "Value1");
  evel_syslog_addl_fields_set(syslog, "Name2", "Value2");
  evel_syslog_addl_fields_set(syslog, "Name3", "Value3");
  evel_syslog_addl_fields_set(syslog, "Name4", "Value4");
  evel_syslog_addl_fields_set(syslog, "Name5", "Value5");

  json_size = evel_json_encode_event(
    json_body, EVEL_MAX_JSON_BODY, (EVENT_HEADER *) syslog);
  compare_strings(expected, json_body, EVEL_MAX_JSON_BODY, "Syslog");
  assert((json_size == strlen(json_body)) && "Bad size returned");

  if(evel_post_event((EVENT_HEADER *)syslog) == EVEL_SUCCESS)
  {
    printf("Message sent to Collector successfully\n");
  }
  else
  {
    printf("Message sending Error\n");
  }

 // evel_free_event(syslog);
}

void test_encode_other()
{
  char * expected =
"{\"event\": {\"commonEventHeader\": {\"domain\": \"other\", \"eventId\": \"other000000001\", \"eventName\": \"other_err\", \"vesEventListenerVersion\": \"7.1\", \"lastEpochMicrosec\": 1000002, \"priority\": \"Normal\", \"reportingEntityName\": \"VM-VirtualBox\", \"sequence\": 0, \"sourceName\": \"VM-VirtualBox\", \"startEpochMicrosec\": 1000002, \"version\": \"4.1\", \"eventType\": \"Other Type\"}, \"otherFields\": {\"hashMap\": {\"Name2\": \"Value2\", \"Name4\": \"Value4\", \"Name5\": \"Value5\", \"Name3\": \"Value3\", \"Name1\": \"Value1\"}, \"arrayOfNamedHashMap\": [{\"name\": \"hmap1\", \"hashMap\": {\"Name14\": \"Value14\", \"Name11\": \"Value11\", \"Name12\": \"Value12\", \"Name13\": \"Value13\"}}, {\"name\": \"hmap2\", \"hashMap\": {\"Name21\": \"Value21\", \"Name22\": \"Value22\", \"Name23\": \"Value23\", \"Name24\": \"Value24\"}}], \"otherFieldsVersion\": \"3.0\"}}}";

  size_t json_size = 0;
  char json_body[EVEL_MAX_JSON_BODY];
  EVENT_OTHER * other = NULL;
  HASHTABLE_T * ht1 = NULL;
  HASHTABLE_T * ht2 = NULL;

//  evel_set_next_event_sequence(129);
  other = evel_new_other("other_err", "other000000001");
  assert(other != NULL);
  evel_source_name_set(&other->header, "VM-VirtualBox");
  evel_reporting_entity_name_set(&other->header, "VM-VirtualBox");
  evel_other_type_set(other, "Other Type");

  ht1 = evel_other_add_new_hashmap_to_hmarray(other, "hmap1");
  ht2 = evel_other_add_new_hashmap_to_hmarray(other, "hmap2");

  evel_other_set_hashmap_in_hmarray(ht1, "Name11", "Value11");
  evel_other_set_hashmap_in_hmarray(ht2, "Name21", "Value21");
  evel_other_set_hashmap_in_hmarray(ht1, "Name12", "Value12");
  evel_other_set_hashmap_in_hmarray(ht2, "Name22", "Value22");
  evel_other_set_hashmap_in_hmarray(ht1, "Name13", "Value13");
  evel_other_set_hashmap_in_hmarray(ht2, "Name23", "Value23");
  evel_other_set_hashmap_in_hmarray(ht1, "Name14", "Value14");
  evel_other_set_hashmap_in_hmarray(ht2, "Name24", "Value24");

  evel_other_field_add_hashmap(other, "Name1", "Value1");
  evel_other_field_add_hashmap(other, "Name2", "Value2");
  evel_other_field_add_hashmap(other, "Name3", "Value3");
  evel_other_field_add_hashmap(other, "Name4", "Value4");
  evel_other_field_add_hashmap(other, "Name5", "Value5");

  json_size = evel_json_encode_event(
    json_body, EVEL_MAX_JSON_BODY, (EVENT_HEADER *) other);
  compare_strings(expected, json_body, EVEL_MAX_JSON_BODY, "Other");
  assert((json_size == strlen(json_body)) && "Bad size returned");

  if(evel_post_event((EVENT_HEADER *)other) == EVEL_SUCCESS)
  {
    printf("Message sent to Collector successfully\n");
  }
  else
  {
    printf("Message sending Error\n");
  }

//  evel_free_event(other);
}

void test_encode_pnfreg()
{
  char * expected =
"{\"event\": {\"commonEventHeader\": {\"domain\": \"pnfRegistration\", \"eventId\": \"pnfreg000000001\", \"eventName\": \"pnfreg_err\", \"vesEventListenerVersion\": \"7.1\", \"lastEpochMicrosec\": 1000002, \"priority\": \"Normal\", \"reportingEntityName\": \"VM-VirtualBox\", \"sequence\": 0, \"sourceName\": \"VM-VirtualBox\", \"startEpochMicrosec\": 1000002, \"version\": \"4.1\"}, \"pnfRegistrationFields\": {\"lastServiceDate\": \"10FEB2019\", \"macAddress\": \"FF:28:22:34:45:56\", \"manufactureDate\": \"FEB2011\", \"modelNumber\": \"FE934567\", \"oamV4IpAddress\": \"10.255.1.254\", \"oamV6IpAddress\": \"::20\", \"serialNumber\": \"1234567890\", \"softwareVersion\": \"SW1234\", \"unitFamily\": \"Unit_Fam_123\", \"unitType\": \"Unit_type_123\", \"vendorName\": \"Vend_nam_123\", \"additionalFields\": {\"Name2\": \"Value2\", \"Name4\": \"Value4\", \"Name5\": \"Value5\", \"Name3\": \"Value3\", \"Name1\": \"Value1\"}, \"pnfRegistrationFieldsVersion\": \"2.0\"}}}";

  size_t json_size = 0;
  char json_body[EVEL_MAX_JSON_BODY];
  EVENT_PNF_REGISTRATION * pnfreg = NULL;

  pnfreg = evel_new_pnf_registration("pnfreg_err", "pnfreg000000001");
  assert(pnfreg != NULL);
  evel_source_name_set(&pnfreg->header, "VM-VirtualBox");
  evel_reporting_entity_name_set(&pnfreg->header, "VM-VirtualBox");

  evel_pnf_registration_addl_field_add(pnfreg, "Name1", "Value1");
  evel_pnf_registration_addl_field_add(pnfreg, "Name2", "Value2");
  evel_pnf_registration_addl_field_add(pnfreg, "Name3", "Value3");
  evel_pnf_registration_addl_field_add(pnfreg, "Name4", "Value4");
  evel_pnf_registration_addl_field_add(pnfreg, "Name5", "Value5");

  evel_pnfRegistration_last_service_date_set(pnfreg, "10FEB2019");
  evel_pnfRegistration_mac_address_set(pnfreg, "FF:28:22:34:45:56");
  evel_pnfRegistration_manufacture_date_set(pnfreg, "FEB2011");
  evel_pnfRegistration_model_number_set(pnfreg, "FE934567");
  evel_pnfRegistration_oam_v4_ipaddress_set(pnfreg, "10.255.1.254");
  evel_pnfRegistration_oam_v6_ipaddress_set(pnfreg, "::20");
  evel_pnfRegistration_serial_number_set(pnfreg, "1234567890");
  evel_pnfRegistration_sw_version_set(pnfreg, "SW1234");
  evel_pnfRegistration_unit_family_set(pnfreg, "Unit_Fam_123");
  evel_pnfRegistration_unit_type_set(pnfreg, "Unit_type_123");
  evel_pnfRegistration_vendor_name_set(pnfreg, "Vend_nam_123");
  

  json_size = evel_json_encode_event(
    json_body, EVEL_MAX_JSON_BODY, (EVENT_HEADER *) pnfreg);
  compare_strings(expected, json_body, EVEL_MAX_JSON_BODY, "PNFRegistration");
  assert((json_size == strlen(json_body)) && "Bad size returned");

  if(evel_post_event((EVENT_HEADER *)pnfreg) == EVEL_SUCCESS)
  {
    printf("Message sent to Collector successfully\n");
  }
  else
  {
    printf("Message sending Error\n");
  }

//  evel_free_event(pnfreg);
}

void test_encode_tca()
{

  char * expected = 
"{\"event\": {\"commonEventHeader\": {\"domain\": \"thresholdCrossingAlert\", \"eventId\": \"tca000000001\", \"eventName\": \"tca_err\", \"vesEventListenerVersion\": \"7.1\", \"lastEpochMicrosec\": 1000002, \"priority\": \"Normal\", \"reportingEntityName\": \"VM-VirtualBox\", \"sequence\": 0, \"sourceName\": \"VM-VirtualBox\", \"startEpochMicrosec\": 1000002, \"version\": \"4.1\", \"eventType\": \"node\"}, \"thresholdCrossingAlertFields\": {\"additionalParameters\": [{\"criticality\": \"CRIT\", \"thresholdCrossed\": \"LastThresh\", \"hashMap\": {\"key1\": \"value1\", \"key2\": \"value2\"}}, {\"criticality\": \"CRIT\", \"thresholdCrossed\": \"LastThresh\", \"hashMap\": {\"key4\": \"value4\", \"key3\": \"value3\"}}], \"alertAction\": \"CLEAR\", \"alertDescription\": \"NE-CPUMEM\", \"alertType\": \"CARD-ANOMALY\", \"collectionTimestamp\": \"1234567\", \"eventSeverity\": \"CRITICAL\", \"eventStartTimestamp\": \"8765432\", \"alertValue\": \"AlertVal\", \"dataCollector\": \"dataCollector\", \"elementType\": \"elementtype\", \"interfaceName\": \"ens04\", \"networkService\": \"nwservice\", \"possibleRootCause\": \"prootcause\", \"associatedAlertIdList\": [\"Alert1\", \"Alert2\", \"Alert3\"], \"additionalFields\": {\"addnam3\": \"addval3\", \"addnam1\": \"addval1\", \"addnam2\": \"addval2\"}, \"thresholdCrossingFieldsVersion\": \"4.0\"}}}";

  size_t json_size = 0;
  char json_body[EVEL_MAX_JSON_BODY];
  EVENT_THRESHOLD_CROSS * tca = NULL;
  PERF_COUNTER * perf = NULL;

  tca = evel_new_threshold_cross("tca_err", "tca000000001", EVEL_EVENT_ACTION_SET, "NE-CPUMEM", EVEL_CARD_ANOMALY, "1234567", EVEL_SEVERITY_CRITICAL, "8765432" );
  assert(tca != NULL);
  evel_source_name_set(&tca->header, "VM-VirtualBox");
  evel_reporting_entity_name_set(&tca->header, "VM-VirtualBox");

  perf = evel_threshold_cross_add_addl_parameters(tca, "CRIT", "LastThresh");
  evel_threshold_cross_addl_parameters_hashmap_set(perf, "key1", "value1");
  evel_threshold_cross_addl_parameters_hashmap_set(perf, "key2", "value2");
  perf = evel_threshold_cross_add_addl_parameters(tca, "CRIT", "LastThresh");
  evel_threshold_cross_addl_parameters_hashmap_set(perf, "key3", "value3");
  evel_threshold_cross_addl_parameters_hashmap_set(perf, "key4", "value4");

  evel_threshold_cross_type_set(tca, "node");
  evel_threshold_cross_alertid_add(tca, "Alert1");
  evel_threshold_cross_alertid_add(tca, "Alert2");
  evel_threshold_cross_alertid_add(tca, "Alert3");

  evel_threshold_cross_addl_info_add(tca, "addnam1", "addval1");
  evel_threshold_cross_addl_info_add(tca, "addnam2", "addval2");
  evel_threshold_cross_addl_info_add(tca, "addnam3", "addval3");

  evel_threshold_cross_possible_rootcause_set(tca, "prootcause");
  evel_threshold_cross_networkservice_set(tca, "nwservice");

  evel_threshold_cross_interfacename_set(tca, "ens04");
  evel_threshold_cross_data_elementtype_set(tca, "elementtype");
  evel_threshold_cross_data_collector_set(tca, "dataCollector");
  evel_threshold_cross_alertvalue_set(tca, "AlertVal");

  json_size = evel_json_encode_event(
    json_body, EVEL_MAX_JSON_BODY, (EVENT_HEADER *) tca);
  compare_strings(expected, json_body, EVEL_MAX_JSON_BODY, "TCA");
  assert((json_size == strlen(json_body)) && "Bad size returned");

  if(evel_post_event((EVENT_HEADER *)tca) == EVEL_SUCCESS)
  {
    printf("Message sent to Collector successfully\n");
  }
  else
  {
    printf("Message sending Error\n");
  }
//  evel_free_event(tca);
}

void compare_strings(char * expected,
                     char * actual,
                     int max_size,
                     char * description)
{
  sleep(2);
  if (strncmp(expected, actual, max_size) != 0)
  {
    int diff = 0;
    while (diff < max_size)
    {
      if (expected[diff] != actual[diff])
      {
        break;
      }
      diff++;
    }

    printf("Description: %s\n", description);
    printf("Comparison Failure at Offset %d\n\n", diff);
    printf("Expected:\n%s\n", expected);
    printf("Actual:\n%s\n\n\n", actual);
    assert(0);
  }
  else
  {
    printf("Description: %s\n", description);
    printf("Comparison Success \n");
    printf("Actual:\n%s\n\n\n", actual);
  }
}

/**************************************************************************//**
 * Copy a json string to a ::MEMORY_CHUNK for testing.
 *
 * @param chunk         The memory chunk.
 * @param string        The json string.
 *****************************************************************************/
void copy_string_to_chunk(MEMORY_CHUNK * chunk, char * string)
{
  int mem_size;

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(chunk != NULL);
  assert(string != NULL);

  mem_size = strlen(string) + 1;
  chunk->memory = malloc(mem_size);
  memcpy(chunk->memory, string, mem_size);
  chunk->size = mem_size;
}

/**************************************************************************//**
 * Copy a json string to a ::MEMORY_CHUNK for testing.
 *
 * @param json          The JSON string.
 * @param post          Memory chunk to post a response.
 *****************************************************************************/
void handle_json_response(char * json, MEMORY_CHUNK * post)
{
  MEMORY_CHUNK chunk;
  post->memory = NULL;
  post->size = 0;
  copy_string_to_chunk(&chunk, json);
  evel_handle_event_response(&chunk, post);
  free(chunk.memory);
}

