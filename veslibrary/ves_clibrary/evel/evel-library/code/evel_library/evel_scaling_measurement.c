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
 * Implementation of EVEL functions relating to the Measurement.
 *
 ****************************************************************************/

#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include "evel.h"
#include "evel_internal.h"
#include "evel_throttle.h"

/**************************************************************************//**
 * Create a new Measurement event.
 *
 * @note    The mandatory fields on the Measurement must be supplied to this
 *          factory function and are immutable once set.  Optional fields have
 *          explicit setter functions, but again values may only be set once so
 *          that the Measurement has immutable properties.
 *
 * @param   measurement_interval
 * @param event_name  Unique Event Name confirming Domain AsdcModel Description
 * @param event_id    A universal identifier of the event for: troubleshooting correlation, analysis, etc
 *
 * @returns pointer to the newly manufactured ::EVENT_MEASUREMENT.  If the
 *          event is not used (i.e. posted) it must be released using
 *          ::evel_free_event.
 * @retval  NULL  Failed to create the event.
 *****************************************************************************/
EVENT_MEASUREMENT * evel_new_measurement(double measurement_interval, const char* ev_name, const char *ev_id)
{
  EVENT_MEASUREMENT * measurement = NULL;

  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(measurement_interval >= 0.0);

  /***************************************************************************/
  /* Allocate the measurement.                                               */
  /***************************************************************************/
  measurement = malloc(sizeof(EVENT_MEASUREMENT));
  if (measurement == NULL)
  {
    log_error_state("Out of memory for Measurement");
    goto exit_label;
  }
  memset(measurement, 0, sizeof(EVENT_MEASUREMENT));
  EVEL_DEBUG("New measurement is at %lp", measurement);

  /***************************************************************************/
  /* Initialize the header & the measurement fields.                         */
  /***************************************************************************/
  evel_init_header_nameid(&measurement->header,ev_name,ev_id);
  measurement->header.event_domain = EVEL_DOMAIN_MEASUREMENT;
  measurement->measurement_interval = measurement_interval;
  measurement->additional_info = ht_create();
  measurement->feature_usage = ht_create();
  dlist_initialize(&measurement->additional_measurements);
  dlist_initialize(&measurement->additional_objects);
  dlist_initialize(&measurement->cpu_usage);
  dlist_initialize(&measurement->disk_usage);
  dlist_initialize(&measurement->mem_usage);
  dlist_initialize(&measurement->filesystem_usage);
  dlist_initialize(&measurement->latency_distribution);
  dlist_initialize(&measurement->nic_performance);
  dlist_initialize(&measurement->codec_usage);
  dlist_initialize(&measurement->huge_pages);
  dlist_initialize(&measurement->ipmis);
  dlist_initialize(&measurement->loads);
  dlist_initialize(&measurement->machine_check_exception);
  dlist_initialize(&measurement->process_stats);

  evel_init_option_double(&measurement->mean_request_latency);
  evel_init_option_int(&measurement->vnfc_scaling_metric);
  evel_init_option_int(&measurement->concurrent_sessions);
  evel_init_option_int(&measurement->configured_entities);
  evel_init_option_int(&measurement->media_ports_in_use);
  evel_init_option_double(&measurement->request_rate);
  measurement->major_version = EVEL_MEASUREMENT_MAJOR_VERSION;
  measurement->minor_version = EVEL_MEASUREMENT_MINOR_VERSION;

exit_label:
  EVEL_EXIT();
  return measurement;
}

/**************************************************************************//**
 * Set the Event Type property of the Measurement.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param measurement Pointer to the Measurement.
 * @param type        The Event Type to be set. ASCIIZ string. The caller
 *                    does not need to preserve the value once the function
 *                    returns.
 *****************************************************************************/
void evel_measurement_type_set(EVENT_MEASUREMENT * measurement,
                               const char * const type)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions and call evel_header_type_set.                      */
  /***************************************************************************/
  assert(measurement != NULL);
  assert(measurement->header.event_domain == EVEL_DOMAIN_MEASUREMENT);
  evel_header_type_set(&measurement->header, type);

  EVEL_EXIT();
}

/**************************************************************************//**
 * Add an additional value name/value pair to the Measurement.
 *
 * The name and value are null delimited ASCII strings.  The library takes
 * a copy so the caller does not have to preserve values after the function
 * returns.
 *
 * @param measurement     Pointer to the measurement.
 * @param name      ASCIIZ string with the attribute's name.  The caller
 *                  does not need to preserve the value once the function
 *                  returns.
 * @param value     ASCIIZ string with the attribute's value.  The caller
 *                  does not need to preserve the value once the function
 *                  returns.
 *****************************************************************************/
void evel_measurement_addl_info_add(EVENT_MEASUREMENT * measurement, char * name, char * value)
{
  char *nam=NULL;
  char *val=NULL;

  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(measurement != NULL);
  assert(measurement->header.event_domain == EVEL_DOMAIN_MEASUREMENT);
  assert(name != NULL);
  assert(value != NULL);
  
  EVEL_DEBUG("Adding name=%s value=%s", name, value);

  nam = strdup(name);
  val = strdup(value);

  ht_insert(measurement->additional_info, nam, val);

  EVEL_EXIT();
}

/**************************************************************************//**
 * Add a json object to jsonObject list.
 *
 * The name and value are null delimited ASCII strings.  The library takes
 * a copy so the caller does not have to preserve values after the function
 * returns.
 *
 * @param measurement     Pointer to the ScalingMeasurement
 * @param jsonobj   Pointer to json object
 *****************************************************************************/
void evel_measurement_addl_object_add(EVENT_MEASUREMENT * measurement, EVEL_JSON_OBJECT *jsonobj)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(measurement != NULL);
  assert(measurement->header.event_domain == EVEL_DOMAIN_MEASUREMENT);
  assert(jsonobj != NULL);

  EVEL_DEBUG("Adding jsonObject %p",jsonobj);

  dlist_push_last(&measurement->additional_objects, jsonobj);

  EVEL_EXIT();
}


/**************************************************************************//**
 * Set the Concurrent Sessions property of the Measurement.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param measurement         Pointer to the Measurement.
 * @param concurrent_sessions The Concurrent Sessions to be set.
 *****************************************************************************/
void evel_measurement_conc_sess_set(EVENT_MEASUREMENT * measurement,
                                    int concurrent_sessions)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(measurement != NULL);
  assert(measurement->header.event_domain == EVEL_DOMAIN_MEASUREMENT);
  assert(concurrent_sessions >= 0);

  evel_set_option_int(&measurement->concurrent_sessions,
                      concurrent_sessions,
                      "Concurrent Sessions");
  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the Configured Entities property of the Measurement.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param measurement         Pointer to the Measurement.
 * @param configured_entities The Configured Entities to be set.
 *****************************************************************************/
void evel_measurement_cfg_ents_set(EVENT_MEASUREMENT * measurement,
                                   int configured_entities)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(measurement != NULL);
  assert(measurement->header.event_domain == EVEL_DOMAIN_MEASUREMENT);
  assert(configured_entities >= 0);

  evel_set_option_int(&measurement->configured_entities,
                      configured_entities,
                      "Configured Entities");
  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the Mean Request Latency property of the Measurement.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param measurement          Pointer to the Measurement.
 * @param mean_request_latency The Mean Request Latency to be set.
 *****************************************************************************/
void evel_measurement_mean_req_lat_set(EVENT_MEASUREMENT * measurement,
                                       double mean_request_latency)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(measurement != NULL);
  assert(measurement->header.event_domain == EVEL_DOMAIN_MEASUREMENT);
  assert(mean_request_latency >= 0.0);

  evel_set_option_double(&measurement->mean_request_latency,
                         mean_request_latency,
                         "Mean Request Latency");
  EVEL_EXIT();
}


/**************************************************************************//**
 * Set the Request Rate property of the Measurement.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param measurement  Pointer to the Measurement.
 * @param request_rate The Request Rate to be set.
 *****************************************************************************/
void evel_measurement_request_rate_set(EVENT_MEASUREMENT * measurement,
                                       double request_rate)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(measurement != NULL);
  assert(measurement->header.event_domain == EVEL_DOMAIN_MEASUREMENT);
  assert(request_rate >= 0);

  evel_set_option_double(&measurement->request_rate,
                      request_rate,
                      "Request Rate");
  EVEL_EXIT();
}

/**************************************************************************//**
 * Add an additional CPU usage value name/value pair to the Measurement.
 *
 * The name and value are null delimited ASCII strings.  The library takes
 * a copy so the caller does not have to preserve values after the function
 * returns.
 *
 * @param measurement   Pointer to the measurement.
 * @param id            ASCIIZ string with the CPU's identifier.
 * @param usage         CPU utilization.
 *****************************************************************************/
MEASUREMENT_CPU_USE *evel_measurement_new_cpu_use_add(EVENT_MEASUREMENT * measurement,
                                 char * id, double usage)
{
  MEASUREMENT_CPU_USE * cpu_use = NULL;
  EVEL_ENTER();

  /***************************************************************************/
  /* Check assumptions.                                                      */
  /***************************************************************************/
  assert(measurement != NULL);
  assert(measurement->header.event_domain == EVEL_DOMAIN_MEASUREMENT);
  assert(id != NULL);
  assert(usage >= 0.0);

  /***************************************************************************/
  /* Allocate a container for the value and push onto the list.              */
  /***************************************************************************/
  EVEL_DEBUG("Adding id=%s usage=%lf", id, usage);
  cpu_use = malloc(sizeof(MEASUREMENT_CPU_USE));
  assert(cpu_use != NULL);
  memset(cpu_use, 0, sizeof(MEASUREMENT_CPU_USE));
  cpu_use->id    = strdup(id);
  cpu_use->usage = usage;
  evel_init_option_double(&cpu_use->idle);
  evel_init_option_double(&cpu_use->intrpt);
  evel_init_option_double(&cpu_use->nice);
  evel_init_option_double(&cpu_use->softirq);
  evel_init_option_double(&cpu_use->steal);
  evel_init_option_double(&cpu_use->sys);
  evel_init_option_double(&cpu_use->user);
  evel_init_option_double(&cpu_use->wait);
  evel_init_option_double(&cpu_use->cpuCapacityContention);
  evel_init_option_double(&cpu_use->cpuDemandAvg);
  evel_init_option_double(&cpu_use->cpuDemandMhz);
  evel_init_option_double(&cpu_use->cpuDemandPct);
  evel_init_option_double(&cpu_use->cpuLatencyAvg);
  evel_init_option_double(&cpu_use->cpuOverheadAvg);
  evel_init_option_double(&cpu_use->cpuSwapWaitTime);

  dlist_push_last(&measurement->cpu_usage, cpu_use);

  EVEL_EXIT();
  return cpu_use;
}

/**************************************************************************//**
 * Set the CPU Idle value in measurement interval
 *   percentage of CPU time spent in the idle task
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param cpu_use      Pointer to the CPU Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_cpu_use_idle_set(MEASUREMENT_CPU_USE *const cpu_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&cpu_use->idle, val, "CPU idle time");
  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the percentage of time spent servicing interrupts
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param cpu_use      Pointer to the CPU Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_cpu_use_interrupt_set(MEASUREMENT_CPU_USE * const cpu_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&cpu_use->intrpt, val, "CPU interrupt value");
  EVEL_EXIT();
}


/**************************************************************************//**
 * Set the percentage of time spent running user space processes that have been niced
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param cpu_use      Pointer to the CPU Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_cpu_use_nice_set(MEASUREMENT_CPU_USE * const cpu_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&cpu_use->nice, val, "CPU nice value");
  EVEL_EXIT();
}


/**************************************************************************//**
 * Set the percentage of time spent handling soft irq interrupts
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param cpu_use      Pointer to the CPU Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_cpu_use_softirq_set(MEASUREMENT_CPU_USE * const cpu_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&cpu_use->softirq, val, "CPU Soft IRQ value");
  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the percentage of time spent in involuntary wait
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param cpu_use      Pointer to the CPU Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_cpu_use_steal_set(MEASUREMENT_CPU_USE * const cpu_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&cpu_use->steal, val, "CPU involuntary wait");
  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the percentage of time spent on system tasks running the kernel
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param cpu_use      Pointer to the CPU Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_cpu_use_system_set(MEASUREMENT_CPU_USE * const cpu_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&cpu_use->sys, val, "CPU System load");
  EVEL_EXIT();
}


/**************************************************************************//**
 * Set the percentage of time spent running un-niced user space processes
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param cpu_use      Pointer to the CPU Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_cpu_use_usageuser_set(MEASUREMENT_CPU_USE * const cpu_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&cpu_use->user, val, "CPU User load value");
  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the percentage of CPU time spent waiting for I/O operations to complete
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param cpu_use      Pointer to the CPU Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_cpu_use_wait_set(MEASUREMENT_CPU_USE * const cpu_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&cpu_use->wait, val, "CPU Wait IO value");
  EVEL_EXIT();
}

void evel_measurement_cpu_use_cpuCapacityContention_set(MEASUREMENT_CPU_USE * const cpu_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&cpu_use->cpuCapacityContention, val, "time the CPU cannot run due to contention");
  EVEL_EXIT();
}

void evel_measurement_cpu_use_cpuDemandAvg_set(MEASUREMENT_CPU_USE * const cpu_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&cpu_use->cpuDemandAvg, val, "The total CPU time that the NF NFC VM could use");
  EVEL_EXIT();
}

void evel_measurement_cpu_use_cpuDemandMhz_set(MEASUREMENT_CPU_USE * const cpu_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&cpu_use->cpuDemandMhz, val, "CPU demand in MHz");
  EVEL_EXIT();
}

void evel_measurement_cpu_use_cpuDemandPct_set(MEASUREMENT_CPU_USE * const cpu_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&cpu_use->cpuDemandPct, val, "CPU demand PCT");
  EVEL_EXIT();
}

void evel_measurement_cpu_use_cpuLatencyAvg_set(MEASUREMENT_CPU_USE * const cpu_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&cpu_use->cpuLatencyAvg, val, "time the VM is unable to run");
  EVEL_EXIT();
}

void evel_measurement_cpu_use_cpuOverheadAvg_set(MEASUREMENT_CPU_USE * const cpu_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&cpu_use->cpuOverheadAvg, val, "The overhead demand");
  EVEL_EXIT();
}

void evel_measurement_cpu_use_cpuSwapWaitTime_set(MEASUREMENT_CPU_USE * const cpu_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&cpu_use->cpuSwapWaitTime, val, "Swap wait time");
  EVEL_EXIT();
}

/**************************************************************************//**
 * Add an additional Memory usage value name/value pair to the Measurement.
 *
 * The name and value are null delimited ASCII strings.  The library takes
 * a copy so the caller does not have to preserve values after the function
 * returns.
 *
 * @param measurement   Pointer to the measurement.
 * @param vmidentifier  ASCIIZ string with the VM's identifier.
 * @param memfree       Memory Free
 * @param memused       Memory Used
 *
 * @return  Returns pointer to memory use structure in measurements
 *****************************************************************************/
MEASUREMENT_MEM_USE * evel_measurement_new_mem_use_add(
                                 EVENT_MEASUREMENT * measurement, 
                                 char *vmidentifier,  
                                 double memfree,
                                 double memused)
{
  MEASUREMENT_MEM_USE * mem_use = NULL;
  EVEL_ENTER();

  /***************************************************************************/
  /* Check assumptions.                                                      */
  /***************************************************************************/
  assert(measurement != NULL);
  assert(measurement->header.event_domain == EVEL_DOMAIN_MEASUREMENT);
  assert(vmidentifier != NULL);

  /***************************************************************************/
  /* Allocate a container for the value and push onto the list.              */
  /***************************************************************************/
  EVEL_DEBUG("Adding vmid=%s", vmidentifier);
  mem_use = malloc(sizeof(MEASUREMENT_MEM_USE));
  assert(mem_use != NULL);
  memset(mem_use, 0, sizeof(MEASUREMENT_MEM_USE));
  mem_use->vmid  = strdup(vmidentifier);
  mem_use->memfree = memfree;
  mem_use->memused = memused;
  evel_init_option_double(&mem_use->membuffsz);
  evel_init_option_double(&mem_use->memcache);
  evel_init_option_double(&mem_use->memconfig);
  evel_init_option_double(&mem_use->slabrecl);
  evel_init_option_double(&mem_use->slabunrecl);
  evel_init_option_double(&mem_use->memoryDemand);
  evel_init_option_double(&mem_use->memoryLatencyAvg);
  evel_init_option_double(&mem_use->memorySharedAvg);
  evel_init_option_double(&mem_use->memorySwapInAvg);
  evel_init_option_double(&mem_use->memorySwapInRateAvg);
  evel_init_option_double(&mem_use->memorySwapOutAvg);
  evel_init_option_double(&mem_use->memorySwapOutRateAvg);
  evel_init_option_double(&mem_use->memorySwapUsedAvg);
  evel_init_option_double(&mem_use->percentMemoryUsage);

  assert(mem_use->vmid != NULL);

  dlist_push_last(&measurement->mem_usage, mem_use);

  EVEL_EXIT();
  return mem_use;
}

/**************************************************************************//**
 * Set kilobytes of memory used for cache
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param mem_use      Pointer to the Memory Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_mem_use_memcache_set(MEASUREMENT_MEM_USE * const mem_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&mem_use->memcache, val, "Memory cache value");
  EVEL_EXIT();
}

/**************************************************************************//**
 * Set kilobytes of memory Buffered
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param mem_use      Pointer to the Memory Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_mem_use_mem_buffered_set(MEASUREMENT_MEM_USE * const mem_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&mem_use->membuffsz, val, "Memory Buffered value");
  EVEL_EXIT();
}

/**************************************************************************//**
 * Set kilobytes of memory configured in the virtual machine on which the VNFC reporting
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param mem_use      Pointer to the Memory Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_mem_use_memconfig_set(MEASUREMENT_MEM_USE * const mem_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&mem_use->memconfig, val, "Memory configured value");
  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the part of the slab that can be reclaimed such as caches measured in kilobytes
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param mem_use      Pointer to the Memory Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_mem_use_slab_reclaimed_set(MEASUREMENT_MEM_USE * const mem_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&mem_use->slabrecl, val, "Memory reclaimable slab set");
  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the part of the slab that cannot be reclaimed such as caches measured in kilobytes
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param mem_use      Pointer to the Memory Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_mem_use_slab_unreclaimable_set(MEASUREMENT_MEM_USE * const mem_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&mem_use->slabunrecl, val, "Memory unreclaimable slab set");
  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the Host demand in kibibytes 
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param mem_use      Pointer to the Memory Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_mem_use_memoryDemand_set(MEASUREMENT_MEM_USE * const mem_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&mem_use->memoryDemand, val, "Host demand in kibibytes");
  EVEL_EXIT();
}

void evel_measurement_mem_use_memoryLatencyAvg_set(MEASUREMENT_MEM_USE * const mem_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&mem_use->memoryLatencyAvg, val, "Percentage of time the VM is waiting");
  EVEL_EXIT();
}

void evel_measurement_mem_use_memorySharedAvg_set(MEASUREMENT_MEM_USE * const mem_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&mem_use->memorySharedAvg, val, "Shared memory in kilobytes");
  EVEL_EXIT();
}

void evel_measurement_mem_use_memorySwapInAvg_set(MEASUREMENT_MEM_USE * const mem_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&mem_use->memorySwapInAvg, val, "Amount of memory swapped-in");
  EVEL_EXIT();
}

void evel_measurement_mem_use_memorySwapInRateAvg_set(MEASUREMENT_MEM_USE * const mem_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&mem_use->memorySwapInRateAvg, val, "Rate at which memory is swapped");
  EVEL_EXIT();
}

void evel_measurement_mem_use_memorySwapOutAvg_set(MEASUREMENT_MEM_USE * const mem_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&mem_use->memorySwapOutAvg, val, "Amount of memory swapped-out");
  EVEL_EXIT();
}

void evel_measurement_mem_use_memorySwapOutRateAvg_set(MEASUREMENT_MEM_USE * const mem_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&mem_use->memorySwapOutRateAvg, val, "Rate at which memory is being swapped out");
  EVEL_EXIT();
}

void evel_measurement_mem_use_memorySwapUsedAvg_set(MEASUREMENT_MEM_USE * const mem_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&mem_use->memorySwapUsedAvg, val, "Space used for caching swapped pages");
  EVEL_EXIT();
}

void evel_measurement_mem_use_percentMemoryUsage_set(MEASUREMENT_MEM_USE * const mem_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&mem_use->percentMemoryUsage, val, "Percentage of memory usage");
  EVEL_EXIT();
}

/**************************************************************************//**
 * Add an additional Disk usage value name/value pair to the Measurement.
 *
 * The name and value are null delimited ASCII strings.  The library takes
 * a copy so the caller does not have to preserve values after the function
 * returns.
 *
 * @param measurement   Pointer to the measurement.
 * @param id            ASCIIZ string with the CPU's identifier.
 * @param usage         Disk utilization.
 *****************************************************************************/
MEASUREMENT_DISK_USE * evel_measurement_new_disk_use_add(EVENT_MEASUREMENT * measurement, char * id)
{
  MEASUREMENT_DISK_USE * disk_use = NULL;
  EVEL_ENTER();

  /***************************************************************************/
  /* Check assumptions.                                                      */
  /***************************************************************************/
  assert(measurement != NULL);
  assert(measurement->header.event_domain == EVEL_DOMAIN_MEASUREMENT);
  assert(id != NULL);

  /***************************************************************************/
  /* Allocate a container for the value and push onto the list.              */
  /***************************************************************************/
  EVEL_DEBUG("Adding id=%s disk usage", id);
  disk_use = malloc(sizeof(MEASUREMENT_DISK_USE));
  assert(disk_use != NULL);
  memset(disk_use, 0, sizeof(MEASUREMENT_DISK_USE));
  disk_use->id    = strdup(id);
  assert(disk_use->id != NULL);
  dlist_push_last(&measurement->disk_usage, disk_use);

  evel_init_option_double(&disk_use->iotimeavg );
  evel_init_option_double(&disk_use->iotimelast );
  evel_init_option_double(&disk_use->iotimemax );
  evel_init_option_double(&disk_use->iotimemin );
  evel_init_option_double(&disk_use->mergereadavg );
  evel_init_option_double(&disk_use->mergereadlast );
  evel_init_option_double(&disk_use->mergereadmax );
  evel_init_option_double(&disk_use->mergereadmin );
  evel_init_option_double(&disk_use->mergewriteavg );
  evel_init_option_double(&disk_use->mergewritelast );
  evel_init_option_double(&disk_use->mergewritemax );
  evel_init_option_double(&disk_use->mergewritemin );
  evel_init_option_double(&disk_use->octetsreadavg );
  evel_init_option_double(&disk_use->octetsreadlast );
  evel_init_option_double(&disk_use->octetsreadmax );
  evel_init_option_double(&disk_use->octetsreadmin );
  evel_init_option_double(&disk_use->octetswriteavg );
  evel_init_option_double(&disk_use->octetswritelast );
  evel_init_option_double(&disk_use->octetswritemax );
  evel_init_option_double(&disk_use->octetswritemin );
  evel_init_option_double(&disk_use->opsreadavg );
  evel_init_option_double(&disk_use->opsreadlast );
  evel_init_option_double(&disk_use->opsreadmax );
  evel_init_option_double(&disk_use->opsreadmin );
  evel_init_option_double(&disk_use->opswriteavg );
  evel_init_option_double(&disk_use->opswritelast );
  evel_init_option_double(&disk_use->opswritemax );
  evel_init_option_double(&disk_use->opswritemin );
  evel_init_option_double(&disk_use->pendingopsavg );
  evel_init_option_double(&disk_use->pendingopslast );
  evel_init_option_double(&disk_use->pendingopsmax );
  evel_init_option_double(&disk_use->pendingopsmin );
  evel_init_option_double(&disk_use->timereadavg );
  evel_init_option_double(&disk_use->timereadlast );
  evel_init_option_double(&disk_use->timereadmax );
  evel_init_option_double(&disk_use->timereadmin );
  evel_init_option_double(&disk_use->timewriteavg );
  evel_init_option_double(&disk_use->timewritelast );
  evel_init_option_double(&disk_use->timewritemax );
  evel_init_option_double(&disk_use->timewritemin );
  evel_init_option_double(&disk_use->diskBusResets );
  evel_init_option_double(&disk_use->diskCommandsAborted );
  evel_init_option_double(&disk_use->diskTime );
  evel_init_option_double(&disk_use->diskFlushRequests );
  evel_init_option_double(&disk_use->diskFlushTime );
  evel_init_option_double(&disk_use->diskCommandsAvg );
  evel_init_option_double(&disk_use->diskReadCommandsAvg );
  evel_init_option_double(&disk_use->diskWriteCommandsAvg );
  evel_init_option_double(&disk_use->diskTotalReadLatencyAvg );
  evel_init_option_double(&disk_use->diskTotalWriteLatencyAvg );
  evel_init_option_double(&disk_use->diskWeightedIoTimeAvg );
  evel_init_option_double(&disk_use->diskWeightedIoTimeLast );
  evel_init_option_double(&disk_use->diskWeightedIoTimeMax );
  evel_init_option_double(&disk_use->diskWeightedIoTimeMin );

  EVEL_EXIT();
  return disk_use;
}

/**************************************************************************//**
 * Set milliseconds spent doing input/output operations over 1 sec; treat
 * this metric as a device load percentage where 1000ms  matches 100% load;
 * provide the average over the measurement interval
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param disk_use     Pointer to the Disk Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_disk_use_iotimeavg_set(MEASUREMENT_DISK_USE * const disk_use,
                                    const double val) 
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->iotimeavg, val, "Disk ioload set");
  EVEL_EXIT();
}

/**************************************************************************//**
 * Set milliseconds spent doing input/output operations over 1 sec; treat
 * this metric as a device load percentage where 1000ms  matches 100% load;
 * provide the last value within the measurement interval
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param disk_use     Pointer to the Disk Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_disk_use_iotimelast_set(MEASUREMENT_DISK_USE * const disk_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->iotimelast, val, "Disk ioloadlast set");
  EVEL_EXIT();
}

/**************************************************************************//**
 * Set milliseconds spent doing input/output operations over 1 sec; treat
 * this metric as a device load percentage where 1000ms  matches 100% load;
 * provide the maximum value within the measurement interval
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param disk_use     Pointer to the Disk Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_disk_use_iotimemax_set(MEASUREMENT_DISK_USE * const disk_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->iotimemax, val, "Disk ioloadmax set");
  EVEL_EXIT();
}

/**************************************************************************//**
 * Set milliseconds spent doing input/output operations over 1 sec; treat
 * this metric as a device load percentage where 1000ms  matches 100% load;
 * provide the minimum value within the measurement interval
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param disk_use     Pointer to the Disk Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_disk_use_iotimemin_set(MEASUREMENT_DISK_USE * const disk_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->iotimemin, val, "Disk ioloadmin set");
  EVEL_EXIT();
}

/**************************************************************************//**
 * Set number of logical read operations that were merged into physical read
 * operations, e.g., two logical reads were served by one physical disk access;
 * provide the average measurement within the measurement interval
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param disk_use     Pointer to the Disk Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_disk_use_mergereadavg_set(MEASUREMENT_DISK_USE * const disk_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->mergereadavg, val, "Disk Merged read average set");
  EVEL_EXIT();
}
/**************************************************************************//**
 * Set number of logical read operations that were merged into physical read
 * operations, e.g., two logical reads were served by one physical disk access;
 * provide the last measurement within the measurement interval
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param disk_use     Pointer to the Disk Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_disk_use_mergereadlast_set(MEASUREMENT_DISK_USE * const disk_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->mergereadlast, val, "Disk mergedload last set");
  EVEL_EXIT();
}
/**************************************************************************//**
 * Set number of logical read operations that were merged into physical read
 * operations, e.g., two logical reads were served by one physical disk access;
 * provide the maximum measurement within the measurement interval
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param disk_use     Pointer to the Disk Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_disk_use_mergereadmax_set(MEASUREMENT_DISK_USE * const disk_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->mergereadmax, val, "Disk merged loadmax set");
  EVEL_EXIT();
}

/**************************************************************************//**
 * Set number of logical read operations that were merged into physical read
 * operations, e.g., two logical reads were served by one physical disk access;
 * provide the minimum measurement within the measurement interval
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param disk_use     Pointer to the Disk Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_disk_use_mergereadmin_set(MEASUREMENT_DISK_USE * const disk_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->mergereadmin, val, "Disk merged loadmin set");
  EVEL_EXIT();
}
/**************************************************************************//**
 * Set number of logical write operations that were merged into physical read
 * operations, e.g., two logical writes were served by one physical disk access;
 * provide the last measurement within the measurement interval
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param disk_use     Pointer to the Disk Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_disk_use_mergewritelast_set(MEASUREMENT_DISK_USE * const disk_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->mergewritelast, val, "Disk merged writelast set");
  EVEL_EXIT();
}
/**************************************************************************//**
 * Set number of logical write operations that were merged into physical read
 * operations, e.g., two logical writes were served by one physical disk access;
 * provide the maximum measurement within the measurement interval
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param disk_use     Pointer to the Disk Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_disk_use_mergewritemax_set(MEASUREMENT_DISK_USE * const disk_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->mergewritemax, val, "Disk writemax set");
  EVEL_EXIT();
}
/**************************************************************************//**
 * Set number of logical write operations that were merged into physical read
 * operations, e.g., two logical writes were served by one physical disk access;
 * provide the average measurement within the measurement interval
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param disk_use     Pointer to the Disk Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_disk_use_mergewriteavg_set(MEASUREMENT_DISK_USE * const disk_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->mergewriteavg, val, "Disk writeavg set");
  EVEL_EXIT();
}
/**************************************************************************//**
 * Set number of logical write operations that were merged into physical read
 * operations, e.g., two logical writes were served by one physical disk access;
 * provide the maximum measurement within the measurement interval
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param disk_use     Pointer to the Disk Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_disk_use_mergewritemin_set(MEASUREMENT_DISK_USE * const disk_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->mergewritemin, val, "Disk writemin set");
  EVEL_EXIT();
}

/**************************************************************************//**
 * Set number of octets per second read from a disk or partition;
 * provide the average measurement within the measurement interval
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param disk_use     Pointer to the Disk Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_disk_use_octetsreadavg_set(MEASUREMENT_DISK_USE * const disk_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->octetsreadavg, val, "Octets readavg set");
  EVEL_EXIT();
}

/**************************************************************************//**
 * Set number of octets per second read from a disk or partition;
 * provide the last measurement within the measurement interval
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param disk_use     Pointer to the Disk Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_disk_use_octetsreadlast_set(MEASUREMENT_DISK_USE * const disk_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->octetsreadlast, val, "Octets readlast set");
  EVEL_EXIT();
}

/**************************************************************************//**
 * Set number of octets per second read from a disk or partition;
 * provide the maximum measurement within the measurement interval
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param disk_use     Pointer to the Disk Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_disk_use_octetsreadmax_set(MEASUREMENT_DISK_USE * const disk_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->octetsreadmax, val, "Octets readmax set");
  EVEL_EXIT();
}
/**************************************************************************//**
 * Set number of octets per second read from a disk or partition;
 * provide the minimum measurement within the measurement interval
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param disk_use     Pointer to the Disk Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_disk_use_octetsreadmin_set(MEASUREMENT_DISK_USE * const disk_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->octetsreadmin, val, "Octets readmin set");
  EVEL_EXIT();
}
/**************************************************************************//**
 * Set number of octets per second written to a disk or partition;
 * provide the average measurement within the measurement interval
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param disk_use     Pointer to the Disk Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_disk_use_octetswriteavg_set(MEASUREMENT_DISK_USE * const disk_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->octetswriteavg, val, "Octets writeavg set");
  EVEL_EXIT();
}
/**************************************************************************//**
 * Set number of octets per second written to a disk or partition;
 * provide the last measurement within the measurement interval
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param disk_use     Pointer to the Disk Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_disk_use_octetswritelast_set(MEASUREMENT_DISK_USE * const disk_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->octetswritelast, val, "Octets writelast set");
  EVEL_EXIT();
}
/**************************************************************************//**
 * Set number of octets per second written to a disk or partition;
 * provide the maximum measurement within the measurement interval
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param disk_use     Pointer to the Disk Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_disk_use_octetswritemax_set(MEASUREMENT_DISK_USE * const disk_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->octetswritemax, val, "Octets writemax set");
  EVEL_EXIT();
}
/**************************************************************************//**
 * Set number of octets per second written to a disk or partition;
 * provide the minimum measurement within the measurement interval
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param disk_use     Pointer to the Disk Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_disk_use_octetswritemin_set(MEASUREMENT_DISK_USE * const disk_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->octetswritemin, val, "Octets writemin set");
  EVEL_EXIT();
}

/**************************************************************************//**
 * Set number of read operations per second issued to the disk;
 * provide the average measurement within the measurement interval
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param disk_use     Pointer to the Disk Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_disk_use_opsreadavg_set(MEASUREMENT_DISK_USE * const disk_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->opsreadavg, val, "Disk read operation average set");
  EVEL_EXIT();
}
/**************************************************************************//**
 * Set number of read operations per second issued to the disk;
 * provide the last measurement within the measurement interval
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param disk_use     Pointer to the Disk Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_disk_use_opsreadlast_set(MEASUREMENT_DISK_USE * const disk_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->opsreadlast, val, "Disk read operation last set");
  EVEL_EXIT();
}
/**************************************************************************//**
 * Set number of read operations per second issued to the disk;
 * provide the maximum measurement within the measurement interval
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param disk_use     Pointer to the Disk Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_disk_use_opsreadmax_set(MEASUREMENT_DISK_USE * const disk_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->opsreadmax, val, "Disk read operation maximum set");
  EVEL_EXIT();
}
/**************************************************************************//**
 * Set number of read operations per second issued to the disk;
 * provide the minimum measurement within the measurement interval
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param disk_use     Pointer to the Disk Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_disk_use_opsreadmin_set(MEASUREMENT_DISK_USE * const disk_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->opsreadmin, val, "Disk read operation minimum set");
  EVEL_EXIT();
}
/**************************************************************************//**
 * Set number of write operations per second issued to the disk;
 * provide the average measurement within the measurement interval
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param disk_use     Pointer to the Disk Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_disk_use_opswriteavg_set(MEASUREMENT_DISK_USE * const disk_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->opswriteavg, val, "Disk write operation average set");
  EVEL_EXIT();
}
/**************************************************************************//**
 * Set number of write operations per second issued to the disk;
 * provide the last measurement within the measurement interval
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param disk_use     Pointer to the Disk Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_disk_use_opswritelast_set(MEASUREMENT_DISK_USE * const disk_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->opswritelast, val, "Disk write operation last set");
  EVEL_EXIT();
}

/**************************************************************************//**
 * Set number of write operations per second issued to the disk;
 * provide the maximum measurement within the measurement interval
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param disk_use     Pointer to the Disk Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_disk_use_opswritemax_set(MEASUREMENT_DISK_USE * const disk_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->opswritemax, val, "Disk write operation maximum set");
  EVEL_EXIT();
}
/**************************************************************************//**
 * Set number of write operations per second issued to the disk;
 * provide the average measurement within the measurement interval
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param disk_use     Pointer to the Disk Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_disk_use_opswritemin_set(MEASUREMENT_DISK_USE * const disk_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->opswritemin, val, "Disk write operation minimum set");
  EVEL_EXIT();
}

/**************************************************************************//**
 * Set queue size of pending I/O operations per second;
 * provide the average measurement within the measurement interval
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param disk_use     Pointer to the Disk Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_disk_use_pendingopsavg_set(MEASUREMENT_DISK_USE * const disk_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->pendingopsavg, val, "Disk pending operation average set");
  EVEL_EXIT();
}
/**************************************************************************//**
 * Set queue size of pending I/O operations per second;
 * provide the last measurement within the measurement interval
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param disk_use     Pointer to the Disk Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_disk_use_pendingopslast_set(MEASUREMENT_DISK_USE * const disk_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->pendingopslast, val, "Disk pending operation last set");
  EVEL_EXIT();
}
/**************************************************************************//**
 * Set queue size of pending I/O operations per second;
 * provide the maximum measurement within the measurement interval
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param disk_use     Pointer to the Disk Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_disk_use_pendingopsmax_set(MEASUREMENT_DISK_USE * const disk_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->pendingopsmax, val, "Disk pending operation maximum set");
  EVEL_EXIT();
}
/**************************************************************************//**
 * Set queue size of pending I/O operations per second;
 * provide the minimum measurement within the measurement interval
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param disk_use     Pointer to the Disk Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_disk_use_pendingopsmin_set(MEASUREMENT_DISK_USE * const disk_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->pendingopsmin, val, "Disk pending operation min set");
  EVEL_EXIT();
}

/**************************************************************************//**
 * Set milliseconds a read operation took to complete;
 * provide the average measurement within the measurement interval
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param disk_use     Pointer to the Disk Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_disk_use_timereadavg_set(MEASUREMENT_DISK_USE * const disk_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->timereadavg, val, "Disk read time average set");
  EVEL_EXIT();
}
/**************************************************************************//**
 * Set milliseconds a read operation took to complete;
 * provide the last measurement within the measurement interval
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param disk_use     Pointer to the Disk Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_disk_use_timereadlast_set(MEASUREMENT_DISK_USE * const disk_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->timereadlast, val, "Disk read time last set");
  EVEL_EXIT();
}
/**************************************************************************//**
 * Set milliseconds a read operation took to complete;
 * provide the maximum measurement within the measurement interval
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param disk_use     Pointer to the Disk Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_disk_use_timereadmax_set(MEASUREMENT_DISK_USE * const disk_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->timereadmax, val, "Disk read time maximum set");
  EVEL_EXIT();
}
/**************************************************************************//**
 * Set milliseconds a read operation took to complete;
 * provide the minimum measurement within the measurement interval
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param disk_use     Pointer to the Disk Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_disk_use_timereadmin_set(MEASUREMENT_DISK_USE * const disk_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->timereadmin, val, "Disk read time minimum set");
  EVEL_EXIT();
}
/**************************************************************************//**
 * Set milliseconds a write operation took to complete;
 * provide the average measurement within the measurement interval
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param disk_use     Pointer to the Disk Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_disk_use_timewriteavg_set(MEASUREMENT_DISK_USE * const disk_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->timewriteavg, val, "Disk write time average set");
  EVEL_EXIT();
}

/**************************************************************************//**
 * Set milliseconds a write operation took to complete;
 * provide the last measurement within the measurement interval
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param disk_use     Pointer to the Disk Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_disk_use_timewritelast_set(MEASUREMENT_DISK_USE * const disk_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->timewritelast, val, "Disk write time last set");
  EVEL_EXIT();
}
/**************************************************************************//**
 * Set milliseconds a write operation took to complete;
 * provide the maximum measurement within the measurement interval
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param disk_use     Pointer to the Disk Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_disk_use_timewritemax_set(MEASUREMENT_DISK_USE * const disk_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->timewritemax, val, "Disk write time max set");
  EVEL_EXIT();
}
/**************************************************************************//**
 * Set milliseconds a write operation took to complete;
 * provide the average measurement within the measurement interval
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param disk_use     Pointer to the Disk Use.
 * @param val          double
 *****************************************************************************/
void evel_measurement_disk_use_timewritemin_set(MEASUREMENT_DISK_USE * const disk_use,
                                    const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->timewritemin, val, "Disk write time min set");
  EVEL_EXIT();
}

void evel_measurement_disk_use_diskBusResets_set(
                                   MEASUREMENT_DISK_USE * const disk_use, 
                                   const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->diskBusResets, val, "diskBusResets");
  EVEL_EXIT();
}

void evel_measurement_disk_use_diskCommandsAborted_set(
                                   MEASUREMENT_DISK_USE * const disk_use, 
                                   const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->diskCommandsAborted, val, "diskCommandsAborted");
  EVEL_EXIT();
}

void evel_measurement_disk_use_diskTime_set(
                                   MEASUREMENT_DISK_USE * const disk_use, 
                                   const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->diskTime, val, "diskTime");
  EVEL_EXIT();
}

void evel_measurement_disk_use_diskFlushRequests_set(
                                   MEASUREMENT_DISK_USE * const disk_use, 
                                   const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->diskFlushRequests, val, "diskFlushRequests");
  EVEL_EXIT();
}

void evel_measurement_disk_use_diskFlushTime_set(
                                   MEASUREMENT_DISK_USE * const disk_use, 
                                   const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->diskFlushTime, val, "diskFlushTime");
  EVEL_EXIT();
}

void evel_measurement_disk_use_diskCommandsAvg_set(
                                   MEASUREMENT_DISK_USE * const disk_use, 
                                   const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->diskCommandsAvg, val, "diskCommandsAvg");
  EVEL_EXIT();
}

void evel_measurement_disk_use_diskReadCommandsAvg_set(
                                   MEASUREMENT_DISK_USE * const disk_use, 
                                   const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->diskReadCommandsAvg, val, "diskReadCommandsAvg");
  EVEL_EXIT();
}

void evel_measurement_disk_use_diskWriteCommandsAvg_set(
                                   MEASUREMENT_DISK_USE * const disk_use, 
                                   const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->diskWriteCommandsAvg, val, "diskWriteCommandsAvg");
  EVEL_EXIT();
}

void evel_measurement_disk_use_diskTotalReadLatencyAvg_set(
                                   MEASUREMENT_DISK_USE * const disk_use, 
                                   const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->diskTotalReadLatencyAvg, val, "diskTotalReadLatencyAvg");
  EVEL_EXIT();
}

void evel_measurement_disk_use_diskTotalWriteLatencyAvg_set(
                                   MEASUREMENT_DISK_USE * const disk_use, 
                                   const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->diskTotalWriteLatencyAvg, val, "diskTotalWriteLatencyAvg");
  EVEL_EXIT();
}

void evel_measurement_disk_use_diskWeightedIoTimeAvg_set(
                                   MEASUREMENT_DISK_USE * const disk_use, 
                                   const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->diskWeightedIoTimeAvg, val, "diskWeightedIoTimeAvg");
  EVEL_EXIT();
}

void evel_measurement_disk_use_diskWeightedIoTimeLast_set(
                                   MEASUREMENT_DISK_USE * const disk_use, 
                                   const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->diskWeightedIoTimeLast, val, "diskWeightedIoTimeLast");
  EVEL_EXIT();
}

void evel_measurement_disk_use_diskWeightedIoTimeMax_set(
                                   MEASUREMENT_DISK_USE * const disk_use, 
                                   const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->diskWeightedIoTimeMax, val, "diskWeightedIoTimeMax");
  EVEL_EXIT();
}

void evel_measurement_disk_use_diskWeightedIoTimeMin_set(
                                   MEASUREMENT_DISK_USE * const disk_use, 
                                   const double val)
{
  EVEL_ENTER();
  evel_set_option_double(&disk_use->diskWeightedIoTimeMin, val, "diskWeightedIoTimeMin");
  EVEL_EXIT();
}

/**************************************************************************//**
 * Add an additional File System usage value name/value pair to the
 * Measurement.
 *
 * The filesystem_name is null delimited ASCII string.  The library takes a
 * copy so the caller does not have to preserve values after the function
 * returns.
 *
 * @param measurement     Pointer to the measurement.
 * @param filesystem_name   ASCIIZ string with the file-system's UUID.
 * @param block_configured  Block storage configured.
 * @param block_used        Block storage in use.
 * @param block_iops        Block storage IOPS.
 * @param ephemeral_configured  Ephemeral storage configured.
 * @param ephemeral_used        Ephemeral storage in use.
 * @param ephemeral_iops        Ephemeral storage IOPS.
 *****************************************************************************/
void evel_measurement_fsys_use_add(EVENT_MEASUREMENT * measurement,
                                   char * filesystem_name,
                                   double block_configured,
                                   double block_used,
                                   double block_iops,
                                   double ephemeral_configured,
                                   double ephemeral_used,
                                   double ephemeral_iops)
{
  MEASUREMENT_FSYS_USE * fsys_use = NULL;
  EVEL_ENTER();

  /***************************************************************************/
  /* Check assumptions.                                                      */
  /***************************************************************************/
  assert(measurement != NULL);
  assert(measurement->header.event_domain == EVEL_DOMAIN_MEASUREMENT);
  assert(filesystem_name != NULL);
  assert(block_configured >= 0.0);
  assert(block_used >= 0.0);
  assert(block_iops >= 0.0);
  assert(ephemeral_configured >= 0.0);
  assert(ephemeral_used >= 0.0);
  assert(ephemeral_iops >= 0.0);

  /***************************************************************************/
  /* Allocate a container for the value and push onto the list.              */
  /***************************************************************************/
  EVEL_DEBUG("Adding filesystem_name=%s", filesystem_name);
  fsys_use = malloc(sizeof(MEASUREMENT_FSYS_USE));
  assert(fsys_use != NULL);
  memset(fsys_use, 0, sizeof(MEASUREMENT_FSYS_USE));
  fsys_use->filesystem_name = strdup(filesystem_name);
  fsys_use->block_configured = block_configured;
  fsys_use->block_used = block_used;
  fsys_use->block_iops = block_iops;
  fsys_use->ephemeral_configured = ephemeral_configured;
  fsys_use->ephemeral_used = ephemeral_used;
  fsys_use->ephemeral_iops = ephemeral_iops;

  dlist_push_last(&measurement->filesystem_usage, fsys_use);

  EVEL_EXIT();
}

/**************************************************************************//**
 * Add a Feature usage value name/value pair to the Measurement.
 *
 * The name is null delimited ASCII string.  The library takes
 * a copy so the caller does not have to preserve values after the function
 * returns.
 *
 * @param measurement     Pointer to the measurement.
 * @param feature         ASCIIZ string with the feature's name.
 * @param utilization     Utilization of the feature.
 *****************************************************************************/
void evel_measurement_feature_use_add(EVENT_MEASUREMENT * measurement,
                                      char * feature,
                                      char * utilization)
{
  char *nam=NULL;
  char *val=NULL;

  EVEL_ENTER();

  /***************************************************************************/
  /* Check assumptions.                                                      */
  /***************************************************************************/
  assert(measurement != NULL);
  assert(measurement->header.event_domain == EVEL_DOMAIN_MEASUREMENT);
  assert(feature != NULL);
  assert(utilization != 0);

  /***************************************************************************/
  /* Allocate a container for the value and push onto the list.              */
  /***************************************************************************/
  EVEL_DEBUG("Adding Feature=%s Use=%s", feature, utilization);
  nam = strdup(feature);
  val = strdup(utilization);

  ht_insert(measurement->feature_usage, nam, val);

  EVEL_EXIT();
}
/**************************************************************************//**
 * Add a new Additional Measurement hashmap to the Measurement.
 *
 * The name is null delimited ASCII string.  The library takes
 * a copy so the caller does not have to preserve values after the function
 * returns.
 *
 * @param measurement   Pointer to the Measurement.
 * @param name     ASCIIZ string containing the hashmap name
 *****************************************************************************/
HASHTABLE_T * evel_measurement_new_addl_measurement(
                                             EVENT_MEASUREMENT * measurement,
                                             const char * const name)
{
  HASHTABLE_T *ht;
  char *nam=NULL;

  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(measurement != NULL);
  assert(measurement->header.event_domain == EVEL_DOMAIN_MEASUREMENT);
  assert(name != NULL);

  EVEL_DEBUG("Adding HashMapName to additional_measurements = %s", name);

  nam = strdup(name);

  ht = nht_create( nam );

  if (ht != NULL)
  {
    dlist_push_last(&measurement->additional_measurements, ht);
  }

  EVEL_EXIT();

  return ht;
}

/**************************************************************************//**
 * Add a new Additional Measurement hashmap to the Measurement.
 *
 * The name is null delimited ASCII string.  The library takes
 * a copy so the caller does not have to preserve values after the function
 * returns.
 *
 * @param ht       Pointer hashmap.
 * @param name     ASCIIZ string containing the measurement's name.
 * @param Value    ASCIIZ string containing the measurement's value.
 *****************************************************************************/
void evel_measurement_addl_measurement_set (
                                      HASHTABLE_T * const ht,
                                      const char * const name,
                                      const char * const value)
{
  char *nam=NULL;
  char *val=NULL;

  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(ht != NULL);
  assert(name != NULL);
  assert(value != NULL);

  EVEL_DEBUG("Adding name=%s value=%s", name, value);

  nam = strdup(name);
  val = strdup(value);

  ht_insert(ht, nam, val);

  EVEL_EXIT();
}

/**************************************************************************//**
 * Add a Codec usage value name/value pair to the Measurement.
 *
 * The name is null delimited ASCII string.  The library takes
 * a copy so the caller does not have to preserve values after the function
 * returns.
 *
 * @param measurement     Pointer to the measurement.
 * @param codec           ASCIIZ string with the codec's name.
 * @param utilization     Number of codecs in use.
 *****************************************************************************/
void evel_measurement_codec_use_add(EVENT_MEASUREMENT * measurement,
                                    char * codec,
                                    int utilization)
{
  MEASUREMENT_CODEC_USE * codec_use = NULL;
  EVEL_ENTER();

  /***************************************************************************/
  /* Check assumptions.                                                      */
  /***************************************************************************/
  assert(measurement != NULL);
  assert(measurement->header.event_domain == EVEL_DOMAIN_MEASUREMENT);
  assert(codec != NULL);
  assert(utilization >= 0.0);

  /***************************************************************************/
  /* Allocate a container for the value and push onto the list.              */
  /***************************************************************************/
  EVEL_DEBUG("Adding Codec=%s Use=%d", codec, utilization);
  codec_use = malloc(sizeof(MEASUREMENT_CODEC_USE));
  assert(codec_use != NULL);
  memset(codec_use, 0, sizeof(MEASUREMENT_CODEC_USE));
  codec_use->codec_id = strdup(codec);
  assert(codec_use->codec_id != NULL);
  codec_use->number_in_use = utilization;

  dlist_push_last(&measurement->codec_usage, codec_use);

  EVEL_EXIT();
}


/**************************************************************************//**
 * Set the Media Ports in Use property of the Measurement.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param measurement         Pointer to the measurement.
 * @param media_ports_in_use  The media port usage to set.
 *****************************************************************************/
void evel_measurement_media_port_use_set(EVENT_MEASUREMENT * measurement,
                                         int media_ports_in_use)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(measurement != NULL);
  assert(measurement->header.event_domain == EVEL_DOMAIN_MEASUREMENT);
  assert(media_ports_in_use >= 0);

  evel_set_option_int(&measurement->media_ports_in_use,
                      media_ports_in_use,
                      "Media Ports In Use");
  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the VNFC Scaling Metric property of the Measurement.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param measurement     Pointer to the measurement.
 * @param scaling_metric  The scaling metric to set.
 *****************************************************************************/
void evel_measurement_vnfc_scaling_metric_set(EVENT_MEASUREMENT * measurement,
                                              int scaling_metric)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(measurement != NULL);
  assert(measurement->header.event_domain == EVEL_DOMAIN_MEASUREMENT);
  assert(scaling_metric >= 0.0);

  evel_set_option_int(&measurement->vnfc_scaling_metric,
                         scaling_metric,
                         "VNFC Scaling Metric");
  EVEL_EXIT();
}

/**************************************************************************//**
 * Create a new Latency Bucket to be added to a Measurement event.
 *
 * @note    The mandatory fields on the ::MEASUREMENT_LATENCY_BUCKET must be
 *          supplied to this factory function and are immutable once set.
 *          Optional fields have explicit setter functions, but again values
 *          may only be set once so that the ::MEASUREMENT_LATENCY_BUCKET has
 *          immutable properties.
 *
 * @param count         Count of events in this bucket.
 *
 * @returns pointer to the newly manufactured ::MEASUREMENT_LATENCY_BUCKET.
 *          If the structure is not used it must be released using free.
 * @retval  NULL  Failed to create the Latency Bucket.
 *****************************************************************************/
MEASUREMENT_LATENCY_BUCKET * evel_new_meas_latency_bucket(const int count)
{
  MEASUREMENT_LATENCY_BUCKET * bucket;

  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(count >= 0);

  /***************************************************************************/
  /* Allocate, then set Mandatory Parameters.                                */
  /***************************************************************************/
  EVEL_DEBUG("Creating bucket, count = %d", count);
  bucket = malloc(sizeof(MEASUREMENT_LATENCY_BUCKET));
  assert(bucket != NULL);

  /***************************************************************************/
  /* Set Mandatory Parameters.                                               */
  /***************************************************************************/
  bucket->count = count;

  /***************************************************************************/
  /* Initialize Optional Parameters.                                         */
  /***************************************************************************/
  evel_init_option_double(&bucket->high_end);
  evel_init_option_double(&bucket->low_end);

  EVEL_EXIT();

  return bucket;
}

/**************************************************************************//**
 * Set the High End property of the Measurement Latency Bucket.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param bucket        Pointer to the Measurement Latency Bucket.
 * @param high_end      High end of the bucket's range.
 *****************************************************************************/
void evel_meas_latency_bucket_high_end_set(
                                     MEASUREMENT_LATENCY_BUCKET * const bucket,
                                     const double high_end)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(high_end >= 0.0);
  evel_set_option_double(&bucket->high_end, high_end, "High End");

  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the Low End property of the Measurement Latency Bucket.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param bucket        Pointer to the Measurement Latency Bucket.
 * @param low_end       Low end of the bucket's range.
 *****************************************************************************/
void evel_meas_latency_bucket_low_end_set(
                                     MEASUREMENT_LATENCY_BUCKET * const bucket,
                                     const double low_end)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(low_end >= 0.0);
  evel_set_option_double(&bucket->low_end, low_end, "Low End");
  EVEL_EXIT();
}

/**************************************************************************//**
 * Add an additional Measurement Latency Bucket to the specified event.
 *
 * @param measurement   Pointer to the Measurement event.
 * @param bucket        Pointer to the Measurement Latency Bucket to add.
 *****************************************************************************/
void evel_meas_latency_bucket_add(EVENT_MEASUREMENT * const measurement,
                                  MEASUREMENT_LATENCY_BUCKET * const bucket)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(measurement != NULL);
  assert(measurement->header.event_domain == EVEL_DOMAIN_MEASUREMENT);
  assert(bucket != NULL);
  dlist_push_last(&measurement->latency_distribution, bucket);

  EVEL_EXIT();
}

/**************************************************************************//**
 * Add an additional Latency Distribution bucket to the Measurement.
 *
 * This function implements the previous API, purely for convenience.
 *
 * @param measurement   Pointer to the measurement.
 * @param low_end       Low end of the bucket's range.
 * @param high_end      High end of the bucket's range.
 * @param count         Count of events in this bucket.
 *****************************************************************************/
void evel_measurement_latency_add(EVENT_MEASUREMENT * const measurement,
                                  const double low_end,
                                  const double high_end,
                                  const int count)
{
  MEASUREMENT_LATENCY_BUCKET * bucket = NULL;

  EVEL_ENTER();

  /***************************************************************************/
  /* Trust the assertions in the underlying methods.                         */
  /***************************************************************************/
  bucket = evel_new_meas_latency_bucket(count);
  evel_meas_latency_bucket_low_end_set(bucket, low_end);
  evel_meas_latency_bucket_high_end_set(bucket, high_end);
  evel_meas_latency_bucket_add(measurement, bucket);

  EVEL_EXIT();
}

/**************************************************************************//**
 * Create a new NIC Use to be added to a Measurement event.
 *
 * @note    The mandatory fields on the ::MEASUREMENT_NIC_PERFORMANCE must be supplied
 *          to this factory function and are immutable once set. Optional
 *          fields have explicit setter functions, but again values may only be
 *          set once so that the ::MEASUREMENT_NIC_PERFORMANCE has immutable
 *          properties.
 *
 * @param nic_id               ASCIIZ string with the NIC's ID.
 * @param val_suspect           True or false confidence in data.
 *
 * @returns pointer to the newly manufactured ::MEASUREMENT_NIC_PERFORMANCE.
 *          If the structure is not used it must be released using
 *          ::evel_measurement_free_nic_performance.
 * @retval  NULL  Failed to create the NIC Use.
 *****************************************************************************/
MEASUREMENT_NIC_PERFORMANCE * evel_measurement_new_nic_performance(char * const nic_id,
                                                     char * const val_suspect)
{
  MEASUREMENT_NIC_PERFORMANCE * nic_performance;

  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(nic_id != NULL);
  assert(!strcmp(val_suspect,"true") || !strcmp(val_suspect,"false"));

  /***************************************************************************/
  /* Allocate, then set Mandatory Parameters.                                */
  /***************************************************************************/
  EVEL_DEBUG("Adding NIC ID=%s", nic_id);
  nic_performance = malloc(sizeof(MEASUREMENT_NIC_PERFORMANCE));
  assert(nic_performance != NULL);
  nic_performance->nic_id = strdup(nic_id);
  nic_performance->valuesaresuspect = strdup(val_suspect);

  /***************************************************************************/
  /* Initialize Optional Parameters.                                         */
  /***************************************************************************/
  evel_init_option_op_state(&nic_performance-> administrativeState);
  evel_init_option_op_state(&nic_performance-> operationalState);
  evel_init_option_double(&nic_performance-> receivedPercentDiscard);
  evel_init_option_double(&nic_performance-> receivedPercentError);
  evel_init_option_double(&nic_performance-> receivedUtilization);
  evel_init_option_double(&nic_performance-> speed);
  evel_init_option_double(&nic_performance-> transmittedPercentDiscard);
  evel_init_option_double(&nic_performance-> transmittedPercentError);
  evel_init_option_double(&nic_performance-> transmittedUtilization);
  evel_init_option_double(&nic_performance-> recvd_bcast_packets_acc);
  evel_init_option_double(&nic_performance-> recvd_bcast_packets_delta);
  evel_init_option_double(&nic_performance-> recvd_discarded_packets_acc);
  evel_init_option_double(&nic_performance-> recvd_discarded_packets_delta);
  evel_init_option_double(&nic_performance-> recvd_error_packets_acc);
  evel_init_option_double(&nic_performance-> recvd_error_packets_delta);
  evel_init_option_double(&nic_performance-> recvd_mcast_packets_acc);
  evel_init_option_double(&nic_performance-> recvd_mcast_packets_delta);
  evel_init_option_double(&nic_performance-> recvd_octets_acc);
  evel_init_option_double(&nic_performance-> recvd_octets_delta);
  evel_init_option_double(&nic_performance-> recvd_total_packets_acc);
  evel_init_option_double(&nic_performance-> recvd_total_packets_delta);
  evel_init_option_double(&nic_performance-> recvd_ucast_packets_acc);
  evel_init_option_double(&nic_performance-> recvd_ucast_packets_delta);
  evel_init_option_double(&nic_performance-> tx_bcast_packets_acc);
  evel_init_option_double(&nic_performance-> tx_bcast_packets_delta);
  evel_init_option_double(&nic_performance-> tx_discarded_packets_acc);
  evel_init_option_double(&nic_performance-> tx_discarded_packets_delta);
  evel_init_option_double(&nic_performance-> tx_error_packets_acc);
  evel_init_option_double(&nic_performance-> tx_error_packets_delta);
  evel_init_option_double(&nic_performance-> tx_mcast_packets_acc);
  evel_init_option_double(&nic_performance-> tx_mcast_packets_delta);
  evel_init_option_double(&nic_performance-> tx_octets_acc);
  evel_init_option_double(&nic_performance-> tx_octets_delta);
  evel_init_option_double(&nic_performance-> tx_total_packets_acc);
  evel_init_option_double(&nic_performance-> tx_total_packets_delta);
  evel_init_option_double(&nic_performance-> tx_ucast_packets_acc);
  evel_init_option_double(&nic_performance-> tx_ucast_packets_delta);

  EVEL_EXIT();

  return nic_performance;
}

/**************************************************************************//**
 * Free a NIC Use.
 *
 * Free off the ::MEASUREMENT_NIC_PERFORMANCE supplied.  Will free all the contained
 * allocated memory.
 *
 * @note It does not free the NIC Use itself, since that may be part of a
 * larger structure.
 *****************************************************************************/
void evel_measurement_free_nic_performance(MEASUREMENT_NIC_PERFORMANCE * const nic_performance)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(nic_performance != NULL);
  assert(nic_performance->nic_id != NULL);
  assert(nic_performance->valuesaresuspect != NULL);

  /***************************************************************************/
  /* Free the duplicated string.                                             */
  /***************************************************************************/
  free(nic_performance->nic_id);
  free(nic_performance->valuesaresuspect);
  nic_performance->nic_id = NULL;

  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the administrative State of the NIC performance.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param nic_performance      Pointer to the NIC Use.
 * @param state
 *****************************************************************************/
void evel_nic_performance_administrativeState_set(MEASUREMENT_NIC_PERFORMANCE * const nic_performance,
                                    const EVEL_OPER_STATE state) 
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(nic_performance != NULL);
  assert(state < EVEL_MAX_OPER_STATES);

  evel_set_option_op_state(&nic_performance->administrativeState, state, "Administrative State");

  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the operational state of the NIC performance.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param nic_performance      Pointer to the NIC Use.
 * @param state
 *****************************************************************************/
void evel_nic_performance_operationalState_set(MEASUREMENT_NIC_PERFORMANCE * const nic_performance,
                                    const EVEL_OPER_STATE state) 
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(nic_performance != NULL);
  assert(state < EVEL_MAX_OPER_STATES);

  evel_set_option_op_state(&nic_performance->operationalState, state, "Operational State");

  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the Percentage of discarded packets received of the NIC performance.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param nic_performance      Pointer to the NIC Use.
 * @param receivedPercentDiscard
 *****************************************************************************/
void evel_nic_performance_receivedPercentDiscard_set(MEASUREMENT_NIC_PERFORMANCE * const nic_performance,
                                    const double receivedPercentDiscard)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(receivedPercentDiscard >= 0.0);

  evel_set_option_double(&nic_performance->receivedPercentDiscard,
                      receivedPercentDiscard,
                      "Percentage of discarded packets received");

  EVEL_EXIT();
}
/**************************************************************************//**
 * Set the Percentage of error packets received of the NIC performance.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param nic_performance      Pointer to the NIC Use.
 * @param receivedPercentError
 *****************************************************************************/
void evel_nic_performance_receivedPercentError_set(MEASUREMENT_NIC_PERFORMANCE * const nic_performance,
                                    const double receivedPercentError)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(receivedPercentError >= 0.0);

  evel_set_option_double(&nic_performance->receivedPercentError,
                      receivedPercentError,
                      "Percentage of error packets received");

  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the Percentage of utilization received of the NIC performance.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param nic_performance      Pointer to the NIC Use.
 * @param receivedUtilization
 *****************************************************************************/
void evel_nic_performance_receivedUtilization_set(MEASUREMENT_NIC_PERFORMANCE * const nic_performance,
                                    const double receivedUtilization)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(receivedUtilization >= 0.0);

  evel_set_option_double(&nic_performance->receivedUtilization,
                      receivedUtilization,
                      "Percentage of utilization received");

  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the Speed configured in mbps of the NIC performance.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param nic_performance      Pointer to the NIC Use.
 * @param Speed
 *****************************************************************************/
void evel_nic_performance_speed_set(MEASUREMENT_NIC_PERFORMANCE * const nic_performance,
                                    const double speed)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(speed >= 0.0);

  evel_set_option_double(&nic_performance->speed,
                      speed,
                      "Speed configured in mbps");

  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the Percentage of discarded packets transmitted of the NIC performance.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param nic_performance      Pointer to the NIC Use.
 * @param transmittedPercentDiscard
 *****************************************************************************/
void evel_nic_performance_transmittedPercentDiscard_set(MEASUREMENT_NIC_PERFORMANCE * const nic_performance,
                                    const double transmittedPercentDiscard)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(transmittedPercentDiscard >= 0.0);

  evel_set_option_double(&nic_performance->transmittedPercentDiscard,
                      transmittedPercentDiscard,
                      "Percentage of discarded packets transmitted");

  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the Percentage of error packets received of the NIC performance.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param nic_performance      Pointer to the NIC Use.
 * @param transmittedPercentError
 *****************************************************************************/
void evel_nic_performance_transmittedPercentError_set(MEASUREMENT_NIC_PERFORMANCE * const nic_performance,
                                    const double transmittedPercentError)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(transmittedPercentError >= 0.0);

  evel_set_option_double(&nic_performance->transmittedPercentError,
                      transmittedPercentError,
                      "Percentage of error packets received");

  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the Percentage of utilization transmitted of the NIC performance.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param nic_performance      Pointer to the NIC Use.
 * @param transmittedUtilization
 *****************************************************************************/
void evel_nic_performance_transmittedUtilization_set(MEASUREMENT_NIC_PERFORMANCE * const nic_performance,
                                    const double transmittedUtilization)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(transmittedUtilization >= 0.0);

  evel_set_option_double(&nic_performance->transmittedUtilization,
                      transmittedUtilization,
                      "Percentage of utilization transmitted");

  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the Accumulated Broadcast Packets Received in measurement interval
 * property of the NIC performance.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param nic_performance      Pointer to the NIC Use.
 * @param recvd_bcast_packets_acc
 *****************************************************************************/
void evel_nic_performance_rx_bcast_pkt_acc_set(MEASUREMENT_NIC_PERFORMANCE * const nic_performance,
                                    const double recvd_bcast_packets_acc)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(recvd_bcast_packets_acc >= 0.0);

  evel_set_option_double(&nic_performance->recvd_bcast_packets_acc,
                      recvd_bcast_packets_acc,
                      "Broadcast Packets accumulated");

  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the Delta Broadcast Packets Received in measurement interval
 * property of the NIC performance.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param nic_performance      Pointer to the NIC Use.
 * @param recvd_bcast_packets_delta
 *****************************************************************************/
void evel_nic_performance_rx_bcast_pkt_delta_set(MEASUREMENT_NIC_PERFORMANCE * const nic_performance,
                                    const double recvd_bcast_packets_delta)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(recvd_bcast_packets_delta >= 0.0);

  evel_set_option_double(&nic_performance->recvd_bcast_packets_delta,
                      recvd_bcast_packets_delta,
                      "Delta Broadcast Packets recieved");

  EVEL_EXIT();
}


/**************************************************************************//**
 * Set the Discarded Packets Received in measurement interval
 * property of the NIC performance.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param nic_performance      Pointer to the NIC Use.
 * @param recvd_discard_packets_acc
 *****************************************************************************/
void evel_nic_performance_rx_discard_pkt_acc_set(MEASUREMENT_NIC_PERFORMANCE * const nic_performance,
                                    const double recvd_discard_packets_acc)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(recvd_discard_packets_acc >= 0.0);

  evel_set_option_double(&nic_performance->recvd_discarded_packets_acc,
                      recvd_discard_packets_acc,
                      "Discarded Packets accumulated");

  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the Delta Discarded Packets Received in measurement interval
 * property of the NIC performance.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param nic_performance      Pointer to the NIC Use.
 * @param recvd_discard_packets_delta
 *****************************************************************************/
void evel_nic_performance_rx_discard_pkt_delta_set(MEASUREMENT_NIC_PERFORMANCE * const nic_performance,
                                    const double recvd_discard_packets_delta)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(recvd_discard_packets_delta >= 0.0);

  evel_set_option_double(&nic_performance->recvd_discarded_packets_delta,
                      recvd_discard_packets_delta,
                      "Delta Discarded Packets recieved");

  EVEL_EXIT();
}


/**************************************************************************//**
 * Set the Error Packets Received in measurement interval
 * property of the NIC performance.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param nic_performance      Pointer to the NIC Use.
 * @param recvd_error_packets_acc
 *****************************************************************************/
void evel_nic_performance_rx_error_pkt_acc_set(MEASUREMENT_NIC_PERFORMANCE * const nic_performance,
                                    const double recvd_error_packets_acc)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(recvd_error_packets_acc >= 0.0);

  evel_set_option_double(&nic_performance->recvd_error_packets_acc,
                      recvd_error_packets_acc,
                      "Error Packets received accumulated");

  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the Delta Error Packets Received in measurement interval
 * property of the NIC performance.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param nic_performance      Pointer to the NIC Use.
 * @param recvd_error_packets_delta
 *****************************************************************************/
void evel_nic_performance_rx_error_pkt_delta_set(MEASUREMENT_NIC_PERFORMANCE * const nic_performance,
                                    const double recvd_error_packets_delta)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(recvd_error_packets_delta >= 0.0);

  evel_set_option_double(&nic_performance->recvd_error_packets_delta,
                      recvd_error_packets_delta,
                      "Delta Error Packets recieved");

  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the Accumulated Multicast Packets Received in measurement interval
 * property of the NIC performance.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param nic_performance      Pointer to the NIC Use.
 * @param recvd_mcast_packets_acc
 *****************************************************************************/
void evel_nic_performance_rx_mcast_pkt_acc_set(MEASUREMENT_NIC_PERFORMANCE * const nic_performance,
                                    const double recvd_mcast_packets_acc)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(recvd_mcast_packets_acc >= 0.0);

  evel_set_option_double(&nic_performance->recvd_mcast_packets_acc,
                      recvd_mcast_packets_acc,
                      "Multicast Packets accumulated");

  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the Delta Multicast Packets Received in measurement interval
 * property of the NIC performance.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param nic_performance      Pointer to the NIC Use.
 * @param recvd_mcast_packets_delta
 *****************************************************************************/
void evel_nic_performance_rx_mcast_pkt_delta_set(MEASUREMENT_NIC_PERFORMANCE * const nic_performance,
                                    const double recvd_mcast_packets_delta)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(recvd_mcast_packets_delta >= 0.0);

  evel_set_option_double(&nic_performance->recvd_mcast_packets_delta,
                      recvd_mcast_packets_delta,
                      "Delta Multicast Packets recieved");

  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the Accumulated Octets Received in measurement interval
 * property of the NIC performance.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param nic_performance      Pointer to the NIC Use.
 * @param recvd_octets_acc
 *****************************************************************************/
void evel_nic_performance_rx_octets_acc_set(MEASUREMENT_NIC_PERFORMANCE * const nic_performance,
                                    const double recvd_octets_acc)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(recvd_octets_acc >= 0.0);

  evel_set_option_double(&nic_performance->recvd_octets_acc,
                      recvd_octets_acc,
                      "Octets received accumulated");

  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the Delta Octets Received in measurement interval
 * property of the NIC performance.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param nic_performance      Pointer to the NIC Use.
 * @param recvd_octets_delta
 *****************************************************************************/
void evel_nic_performance_rx_octets_delta_set(MEASUREMENT_NIC_PERFORMANCE * const nic_performance,
                                    const double recvd_octets_delta)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(recvd_octets_delta >= 0.0);

  evel_set_option_double(&nic_performance->recvd_octets_delta,
                      recvd_octets_delta,
                      "Delta Octets recieved");

  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the Accumulated Total Packets Received in measurement interval
 * property of the NIC performance.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param nic_performance      Pointer to the NIC Use.
 * @param recvd_total_packets_acc
 *****************************************************************************/
void evel_nic_performance_rx_total_pkt_acc_set(MEASUREMENT_NIC_PERFORMANCE * const nic_performance,
                                    const double recvd_total_packets_acc)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(recvd_total_packets_acc >= 0.0);

  evel_set_option_double(&nic_performance->recvd_total_packets_acc,
                      recvd_total_packets_acc,
                      "Total Packets accumulated");

  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the Delta Total Packets Received in measurement interval
 * property of the NIC performance.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param nic_performance      Pointer to the NIC Use.
 * @param recvd_total_packets_delta
 *****************************************************************************/
void evel_nic_performance_rx_total_pkt_delta_set(MEASUREMENT_NIC_PERFORMANCE * const nic_performance,
                                    const double recvd_total_packets_delta)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(recvd_total_packets_delta >= 0.0);

  evel_set_option_double(&nic_performance->recvd_total_packets_delta,
                      recvd_total_packets_delta,
                      "Delta Total Packets recieved");

  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the Accumulated Unicast Packets Received in measurement interval
 * property of the NIC performance.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param nic_performance      Pointer to the NIC Use.
 * @param recvd_ucast_packets_acc
 *****************************************************************************/
void evel_nic_performance_rx_ucast_pkt_acc_set(MEASUREMENT_NIC_PERFORMANCE * const nic_performance,
                                    const double recvd_ucast_packets_acc)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(recvd_ucast_packets_acc >= 0.0);

  evel_set_option_double(&nic_performance->recvd_ucast_packets_acc,
                      recvd_ucast_packets_acc,
                      "Unicast Packets received accumulated");

  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the Delta Unicast packets Received in measurement interval
 * property of the NIC performance.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param nic_performance      Pointer to the NIC Use.
 * @param recvd_ucast_packets_delta
 *****************************************************************************/
void evel_nic_performance_rx_ucast_pkt_delta_set(MEASUREMENT_NIC_PERFORMANCE * const nic_performance,
                                    const double recvd_ucast_packets_delta)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(recvd_ucast_packets_delta >= 0.0);

  evel_set_option_double(&nic_performance->recvd_ucast_packets_delta,
                      recvd_ucast_packets_delta,
                      "Delta Unicast packets recieved");

  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the Transmitted Broadcast Packets in measurement interval
 * property of the NIC performance.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param nic_performance      Pointer to the NIC Use.
 * @param tx_bcast_packets_acc
 *****************************************************************************/
void evel_nic_performance_tx_bcast_pkt_acc_set(MEASUREMENT_NIC_PERFORMANCE * const nic_performance,
                                    const double tx_bcast_packets_acc)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(tx_bcast_packets_acc >= 0.0);

  evel_set_option_double(&nic_performance->tx_bcast_packets_acc,
                      tx_bcast_packets_acc,
                      "Transmitted Broadcast Packets accumulated");

  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the Delta Broadcast packets Transmitted in measurement interval
 * property of the NIC performance.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param nic_performance      Pointer to the NIC Use.
 * @param tx_bcast_packets_delta
 *****************************************************************************/
void evel_nic_performance_tx_bcast_pkt_delta_set(MEASUREMENT_NIC_PERFORMANCE * const nic_performance,
                                    const double tx_bcast_packets_delta)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(tx_bcast_packets_delta >= 0.0);

  evel_set_option_double(&nic_performance->tx_bcast_packets_delta,
                      tx_bcast_packets_delta,
                      "Delta Transmitted Broadcast packets ");

  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the Transmitted Discarded Packets in measurement interval
 * property of the NIC performance.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param nic_performance      Pointer to the NIC Use.
 * @param tx_discarded_packets_acc
 *****************************************************************************/
void evel_nic_performance_tx_discarded_pkt_acc_set(MEASUREMENT_NIC_PERFORMANCE * const nic_performance,
                                    const double tx_discarded_packets_acc)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(tx_discarded_packets_acc >= 0.0);

  evel_set_option_double(&nic_performance->tx_discarded_packets_acc,
                      tx_discarded_packets_acc,
                      "Transmitted Discarded Packets accumulated");

  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the Delta Discarded packets Transmitted in measurement interval
 * property of the NIC performance.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param nic_performance      Pointer to the NIC Use.
 * @param tx_discarded_packets_delta
 *****************************************************************************/
void evel_nic_performance_tx_discarded_pkt_delta_set(MEASUREMENT_NIC_PERFORMANCE * const nic_performance,
                                    const double tx_discarded_packets_delta)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(tx_discarded_packets_delta >= 0.0);

  evel_set_option_double(&nic_performance->tx_discarded_packets_delta,
                      tx_discarded_packets_delta,
                      "Delta Transmitted Discarded packets ");

  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the Transmitted Errored Packets in measurement interval
 * property of the NIC performance.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param nic_performance      Pointer to the NIC Use.
 * @param tx_error_packets_acc
 *****************************************************************************/
void evel_nic_performance_tx_error_pkt_acc_set(MEASUREMENT_NIC_PERFORMANCE * const nic_performance,
                                    const double tx_error_packets_acc)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(tx_error_packets_acc >= 0.0);

  evel_set_option_double(&nic_performance->tx_error_packets_acc,
                      tx_error_packets_acc,
                      "Transmitted Error Packets accumulated");

  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the Delta Errored packets Transmitted in measurement interval
 * property of the NIC performance.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param nic_performance      Pointer to the NIC Use.
 * @param tx_error_packets_delta
 *****************************************************************************/
void evel_nic_performance_tx_error_pkt_delta_set(MEASUREMENT_NIC_PERFORMANCE * const nic_performance,
                                    const double tx_error_packets_delta)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(tx_error_packets_delta >= 0.0);

  evel_set_option_double(&nic_performance->tx_error_packets_delta,
                      tx_error_packets_delta,
                      "Delta Transmitted Error packets ");

  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the Transmitted Multicast Packets in measurement interval
 * property of the NIC performance.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param nic_performance      Pointer to the NIC Use.
 * @param tx_mcast_packets_acc
 *****************************************************************************/
void evel_nic_performance_tx_mcast_pkt_acc_set(MEASUREMENT_NIC_PERFORMANCE * const nic_performance,
                                    const double tx_mcast_packets_acc)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(tx_mcast_packets_acc >= 0.0);

  evel_set_option_double(&nic_performance->tx_mcast_packets_acc,
                      tx_mcast_packets_acc,
                      "Transmitted Multicast Packets accumulated");

  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the Delta Multicast packets Transmitted in measurement interval
 * property of the NIC performance.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param nic_performance      Pointer to the NIC Use.
 * @param tx_mcast_packets_delta
 *****************************************************************************/
void evel_nic_performance_tx_mcast_pkt_delta_set(MEASUREMENT_NIC_PERFORMANCE * const nic_performance,
                                    const double tx_mcast_packets_delta)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(tx_mcast_packets_delta >= 0.0);

  evel_set_option_double(&nic_performance->tx_mcast_packets_delta,
                      tx_mcast_packets_delta,
                      "Delta Transmitted Multicast packets ");

  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the Transmitted Octets in measurement interval
 * property of the NIC performance.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param nic_performance      Pointer to the NIC Use.
 * @param tx_octets_acc
 *****************************************************************************/
void evel_nic_performance_tx_octets_acc_set(MEASUREMENT_NIC_PERFORMANCE * const nic_performance,
                                    const double tx_octets_acc)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(tx_octets_acc >= 0.0);

  evel_set_option_double(&nic_performance->tx_octets_acc,
                      tx_octets_acc,
                      "Transmitted Octets accumulated");

  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the Delta Octets Transmitted in measurement interval
 * property of the NIC performance.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param nic_performance      Pointer to the NIC Use.
 * @param tx_octets_delta
 *****************************************************************************/
void evel_nic_performance_tx_octets_delta_set(MEASUREMENT_NIC_PERFORMANCE * const nic_performance,
                                    const double tx_octets_delta)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(tx_octets_delta >= 0.0);

  evel_set_option_double(&nic_performance->tx_octets_delta,
                      tx_octets_delta,
                      "Delta Transmitted Octets ");

  EVEL_EXIT();
}


/**************************************************************************//**
 * Set the Transmitted Total Packets in measurement interval
 * property of the NIC performance.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param nic_performance      Pointer to the NIC Use.
 * @param tx_total_packets_acc
 *****************************************************************************/
void evel_nic_performance_tx_total_pkt_acc_set(MEASUREMENT_NIC_PERFORMANCE * const nic_performance,
                                    const double tx_total_packets_acc)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(tx_total_packets_acc >= 0.0);

  evel_set_option_double(&nic_performance->tx_total_packets_acc,
                      tx_total_packets_acc,
                      "Transmitted Total Packets accumulated");

  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the Delta Total Packets Transmitted in measurement interval
 * property of the NIC performance.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param nic_performance      Pointer to the NIC Use.
 * @param tx_total_packets_delta
 *****************************************************************************/
void evel_nic_performance_tx_total_pkt_delta_set(MEASUREMENT_NIC_PERFORMANCE * const nic_performance,
                                    const double tx_total_packets_delta)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(tx_total_packets_delta >= 0.0);

  evel_set_option_double(&nic_performance->tx_total_packets_delta,
                      tx_total_packets_delta,
                      "Delta Transmitted Total Packets ");

  EVEL_EXIT();
}


/**************************************************************************//**
 * Set the Transmitted Unicast Packets in measurement interval
 * property of the NIC performance.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param nic_performance      Pointer to the NIC Use.
 * @param tx_ucast_packets_acc
 *****************************************************************************/
void evel_nic_performance_tx_ucast_pkt_acc_set(MEASUREMENT_NIC_PERFORMANCE * const nic_performance,
                                    const double mtx_ucast_packets_acc)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(mtx_ucast_packets_acc >= 0.0);

  evel_set_option_double(&nic_performance->tx_ucast_packets_acc,
                      mtx_ucast_packets_acc,
                      "Transmitted Unicast Packets accumulated");

  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the Delta Octets Transmitted in measurement interval
 * property of the NIC performance.
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param nic_performance      Pointer to the NIC Use.
 * @param tx_ucast_packets_delta
 *****************************************************************************/
void evel_nic_performance_tx_ucast_pkt_delta_set(MEASUREMENT_NIC_PERFORMANCE * const nic_performance,
                                    const double tx_ucast_packets_delta)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(tx_ucast_packets_delta >= 0.0);

  evel_set_option_double(&nic_performance->tx_ucast_packets_delta,
                      tx_ucast_packets_delta,
                      "Delta Transmitted Unicast Packets ");

  EVEL_EXIT();
}


/**************************************************************************//**
 * Add an additional NIC Use to the specified Measurement event.
 *
 * @param measurement   Pointer to the measurement.
 * @param nic_performance      Pointer to the NIC Use to add.
 *****************************************************************************/
void evel_meas_nic_performance_add(EVENT_MEASUREMENT * const measurement,
                            MEASUREMENT_NIC_PERFORMANCE * const nic_performance)
{
  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(measurement != NULL);
  assert(measurement->header.event_domain == EVEL_DOMAIN_MEASUREMENT);
  assert(nic_performance != NULL);

  dlist_push_last(&measurement->nic_performance, nic_performance);

  EVEL_EXIT();
}

/**************************************************************************//**
 * Add an additional NIC usage record Measurement.
 *
 * This function implements the previous API, purely for convenience.
 *
 * The ID is null delimited ASCII string.  The library takes a copy so the
 * caller does not have to preserve values after the function returns.
 *
 * @param measurement           Pointer to the measurement.
 * @param nic_id               ASCIIZ string with the NIC's ID.
 * @param valset                true or false confidence level
 * @param admin_state               Administrative state
 * @param op_state                  Operational state
 * @param receivedPercentDiscard    Percentage of discarded packets received;
 * @param receivedPercentError      Percentage of error packets received
 * @param receivedUtilization       Percentage of utilization received
 * @param speed                     Speed configured in mbps
 * @param transmittedPercentDiscard Percentage of discarded packets transmitted
 * @param transmittedPercentError   Percentage of error packets received
 * @param transmittedUtilization    Percentage of utilization transmitted
 * @param recvd_bcast_packets_acc         Recieved broadcast packets
 * @param recvd_bcast_packets_delta       Received delta broadcast packets
 * @param recvd_discarded_packets_acc     Recieved discarded packets
 * @param recvd_discarded_packets_delta   Received discarded delta packets
 * @param recvd_error_packets_acc         Received error packets
 * @param recvd_error_packets_delta,      Received delta error packets
 * @param recvd_mcast_packets_acc         Received multicast packets
 * @param recvd_mcast_packets_delta       Received delta multicast packets
 * @param recvd_octets_acc                Received octets
 * @param recvd_octets_delta              Received delta octets
 * @param recvd_total_packets_acc         Received total packets
 * @param recvd_total_packets_delta       Received delta total packets
 * @param recvd_ucast_packets_acc         Received Unicast packets
 * @param recvd_ucast_packets_delta       Received delta unicast packets
 * @param tx_bcast_packets_acc            Transmitted broadcast packets
 * @param tx_bcast_packets_delta          Transmitted delta broadcast packets
 * @param tx_discarded_packets_acc        Transmitted packets discarded
 * @param tx_discarded_packets_delta      Transmitted delta discarded packets
 * @param tx_error_packets_acc            Transmitted error packets
 * @param tx_error_packets_delta          Transmitted delta error packets
 * @param tx_mcast_packets_acc            Transmitted multicast packets accumulated
 * @param tx_mcast_packets_delta          Transmitted delta multicast packets
 * @param tx_octets_acc                   Transmitted octets
 * @param tx_octets_delta                 Transmitted delta octets
 * @param tx_total_packets_acc            Transmitted total packets
 * @param tx_total_packets_delta          Transmitted delta total packets
 * @param tx_ucast_packets_acc            Transmitted Unicast packets
 * @param tx_ucast_packets_delta          Transmitted delta Unicast packets
 *****************************************************************************/
void evel_measurement_nic_performance_add(EVENT_MEASUREMENT * const measurement,
                               char * const nic_id,
                               char * valset,
                               EVEL_OPER_STATE admin_state,
                               EVEL_OPER_STATE op_state,
                               double receivedPercentDiscard,
                               double receivedPercentError,
                               double receivedUtilization,
                               double speed,
                               double transmittedPercentDiscard,
                               double transmittedPercentError,
                               double transmittedUtilization,
                               double recvd_bcast_packets_acc,
                               double recvd_bcast_packets_delta,
                               double recvd_discarded_packets_acc,
                               double recvd_discarded_packets_delta,
                               double recvd_error_packets_acc,
                               double recvd_error_packets_delta,
                               double recvd_mcast_packets_acc,
                               double recvd_mcast_packets_delta,
                               double recvd_octets_acc,
                               double recvd_octets_delta,
                               double recvd_total_packets_acc,
                               double recvd_total_packets_delta,
                               double recvd_ucast_packets_acc,
                               double recvd_ucast_packets_delta,
                               double tx_bcast_packets_acc,
                               double tx_bcast_packets_delta,
                               double tx_discarded_packets_acc,
                               double tx_discarded_packets_delta,
                               double tx_error_packets_acc,
                               double tx_error_packets_delta,
                               double tx_mcast_packets_acc,
                               double tx_mcast_packets_delta,
                               double tx_octets_acc,
                               double tx_octets_delta,
                               double tx_total_packets_acc,
                               double tx_total_packets_delta,
                               double tx_ucast_packets_acc,
                               double tx_ucast_packets_delta)
{
  MEASUREMENT_NIC_PERFORMANCE * nic_performance = NULL;
  EVEL_ENTER();

  /***************************************************************************/
  /* Trust the assertions in the underlying methods.                         */
  /***************************************************************************/
  nic_performance = evel_measurement_new_nic_performance(nic_id, valset);
                                           
  evel_nic_performance_administrativeState_set(nic_performance, admin_state);
  evel_nic_performance_operationalState_set(nic_performance, op_state);
  evel_nic_performance_receivedPercentDiscard_set(nic_performance, receivedPercentDiscard);
  evel_nic_performance_receivedPercentError_set(nic_performance, receivedPercentError);
  evel_nic_performance_receivedUtilization_set(nic_performance, receivedUtilization);
  evel_nic_performance_speed_set(nic_performance, speed);
  evel_nic_performance_transmittedPercentDiscard_set(nic_performance, transmittedPercentDiscard);
  evel_nic_performance_transmittedPercentError_set(nic_performance, transmittedPercentError);
  evel_nic_performance_transmittedUtilization_set(nic_performance, transmittedUtilization);
  evel_nic_performance_rx_bcast_pkt_acc_set(nic_performance, recvd_bcast_packets_acc);
  evel_nic_performance_rx_bcast_pkt_delta_set(nic_performance, recvd_bcast_packets_delta);
  evel_nic_performance_rx_discard_pkt_acc_set(nic_performance, recvd_discarded_packets_acc);
  evel_nic_performance_rx_discard_pkt_delta_set(nic_performance, recvd_discarded_packets_delta);
  evel_nic_performance_rx_error_pkt_acc_set(nic_performance, recvd_error_packets_acc);
  evel_nic_performance_rx_error_pkt_delta_set(nic_performance, recvd_error_packets_delta);
  evel_nic_performance_rx_mcast_pkt_acc_set(nic_performance, recvd_mcast_packets_acc);
  evel_nic_performance_rx_mcast_pkt_delta_set(nic_performance, recvd_mcast_packets_delta);
  evel_nic_performance_rx_octets_acc_set(nic_performance, recvd_octets_acc);
  evel_nic_performance_rx_octets_delta_set(nic_performance, recvd_octets_delta);
  evel_nic_performance_rx_total_pkt_acc_set(nic_performance, recvd_total_packets_acc);
  evel_nic_performance_rx_total_pkt_delta_set(nic_performance, recvd_total_packets_delta);
  evel_nic_performance_rx_ucast_pkt_acc_set(nic_performance, recvd_ucast_packets_acc);
  evel_nic_performance_rx_ucast_pkt_delta_set(nic_performance, recvd_ucast_packets_delta);
  evel_nic_performance_tx_bcast_pkt_acc_set(nic_performance, tx_bcast_packets_acc);
  evel_nic_performance_tx_bcast_pkt_delta_set(nic_performance, tx_bcast_packets_delta);
  evel_nic_performance_tx_discarded_pkt_acc_set(nic_performance, tx_discarded_packets_acc);
  evel_nic_performance_tx_discarded_pkt_delta_set(nic_performance, tx_discarded_packets_delta);
  evel_nic_performance_tx_error_pkt_acc_set(nic_performance, tx_error_packets_acc);
  evel_nic_performance_tx_error_pkt_delta_set(nic_performance, tx_error_packets_delta);
  evel_nic_performance_tx_mcast_pkt_acc_set(nic_performance, tx_mcast_packets_acc);
  evel_nic_performance_tx_mcast_pkt_delta_set(nic_performance, tx_mcast_packets_delta);
  evel_nic_performance_tx_octets_acc_set(nic_performance, tx_octets_acc);
  evel_nic_performance_tx_octets_delta_set(nic_performance, tx_octets_delta);
  evel_nic_performance_tx_total_pkt_acc_set(nic_performance, tx_total_packets_acc);
  evel_nic_performance_tx_total_pkt_delta_set(nic_performance, tx_total_packets_delta);
  evel_nic_performance_tx_ucast_pkt_acc_set(nic_performance, tx_ucast_packets_acc);
  evel_nic_performance_tx_ucast_pkt_delta_set(nic_performance, tx_ucast_packets_delta);
  evel_meas_nic_performance_add(measurement, nic_performance);
}

MEASUREMENT_IPMI * evel_measurement_new_ipmi_add(
                                  EVENT_MEASUREMENT * measurement)
{
  MEASUREMENT_IPMI *ipmi = NULL;
  EVEL_ENTER();

  /***************************************************************************/
  /* Check assumptions.                                                      */
  /***************************************************************************/
  assert(measurement != NULL);
  assert(measurement->header.event_domain == EVEL_DOMAIN_MEASUREMENT);

  /***************************************************************************/
  /* Allocate a container for the value and push onto the list.              */
  /***************************************************************************/
  ipmi = malloc(sizeof(MEASUREMENT_IPMI));
  assert(ipmi != NULL);
  memset(ipmi, 0, sizeof(MEASUREMENT_IPMI));

  evel_init_option_double(&ipmi->exitAirTemperature);
  evel_init_option_double(&ipmi->frontPanelTemperature);
  evel_init_option_double(&ipmi->ioModuleTemperature);
  evel_init_option_double(&ipmi->systemAirflow);

  dlist_initialize(&ipmi->ipmi_base_board_temparature);
  dlist_initialize(&ipmi->ipmi_base_board_voltage);
  dlist_initialize(&ipmi->ipmi_battery);
  dlist_initialize(&ipmi->ipmi_fan);
  dlist_initialize(&ipmi->ipmi_hsbp);
  dlist_initialize(&ipmi->ipmi_global_agg_temp_margin);
  dlist_initialize(&ipmi->ipmi_nic);
  dlist_initialize(&ipmi->ipmi_power);
  dlist_initialize(&ipmi->ipmi_processor);

  dlist_push_last(&measurement->ipmis, ipmi);

  EVEL_EXIT();
  return ipmi;
}

/**************************************************************************//**
 * Set the System fan exit air flow temperature in Celsius of IPMI
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param ipmi      Pointer to the IPMI Use.
 * @param double
 *****************************************************************************/
void evel_measurement_ipmi_exitAirTemperature_set(MEASUREMENT_IPMI *ipmi,
                                              const double val)
{
  EVEL_ENTER();
  assert(ipmi != NULL);
  evel_set_option_double(&ipmi->exitAirTemperature, val, "exitAirTemperature");
  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the Front panel temp in Celsius of IPMI
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param ipmi      Pointer to the IPMI Use.
 * @param double
 *****************************************************************************/
void evel_measurement_ipmi_frontPanelTemperature_set(MEASUREMENT_IPMI *ipmi,
                                              const double val)
{
  EVEL_ENTER();
  assert(ipmi != NULL);
  evel_set_option_double(&ipmi->frontPanelTemperature, val, "frontPanelTemperature");
  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the Io module temp in Celsius of IPMI
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param ipmi      Pointer to the IPMI Use.
 * @param double
 *****************************************************************************/
void evel_measurement_ipmi_ioModuleTemperature_set(MEASUREMENT_IPMI *ipmi,
                                              const double val)
{
  EVEL_ENTER();
  assert(ipmi != NULL);
  evel_set_option_double(&ipmi->ioModuleTemperature, val, "ioModuleTemperature");
  EVEL_EXIT();
}

/**************************************************************************//**
 * Set the Airflow in cubic feet per minute (cfm) of IPMI
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param ipmi      Pointer to the IPMI Use.
 * @param double
 *****************************************************************************/
void evel_measurement_ipmi_systemAirflow_set(MEASUREMENT_IPMI *ipmi,
                                              const double val)
{
  EVEL_ENTER();
  assert(ipmi != NULL);
  evel_set_option_double(&ipmi->systemAirflow, val, "systemAirflow");
  EVEL_EXIT();
}

/**************************************************************************//**
 * Add a new Baseboard Temperature Array element to IPMI
 *
 * @note  The property is treated as immutable: it is only valid to call
 *        the setter once.  However, we don't assert if the caller tries to
 *        overwrite, just ignoring the update instead.
 *
 * @param ipmi      Pointer to the IPMI Use.
 * @param id        Indentifier
 *****************************************************************************/
MEASUREMENT_IPMI_BB_TEMPERATURE *evel_measurement_new_base_board_temp_add(
                                 MEASUREMENT_IPMI * ipmi,
                                 char * id)
{
  MEASUREMENT_IPMI_BB_TEMPERATURE * bb_temp = NULL;
  EVEL_ENTER();

  /***************************************************************************/
  /* Check assumptions.                                                      */
  /***************************************************************************/
  assert(ipmi != NULL);
  assert(id != NULL);

  /***************************************************************************/
  /* Allocate a container for the value and push onto the list.              */
  /***************************************************************************/
  EVEL_DEBUG("Adding id=%s", id);
  bb_temp = malloc(sizeof(MEASUREMENT_IPMI_BB_TEMPERATURE));
  assert(bb_temp != NULL);
  memset(bb_temp, 0, sizeof(MEASUREMENT_IPMI_BB_TEMPERATURE));
  bb_temp->BBTemperatureID = strdup(id);
  evel_init_option_double(&bb_temp->BBTemperature);

  dlist_push_last(&ipmi->ipmi_base_board_temparature, bb_temp);

  EVEL_EXIT();
  return bb_temp;
}


void evel_measurement_ipmi_bb_temp_set(MEASUREMENT_IPMI *ipmi,
                                    MEASUREMENT_IPMI_BB_TEMPERATURE * bb_temp,
                                    const double val)
{
  EVEL_ENTER();
  assert(ipmi != NULL);
  assert(bb_temp != NULL);
  evel_set_option_double(&bb_temp->BBTemperature, val, "Base Board Temperature");
  EVEL_EXIT();
}


MEASUREMENT_IPMI_BB_VOLTAGE *evel_measurement_new_base_board_volt_add(
                                 MEASUREMENT_IPMI * ipmi,
                                 const char const * id)
{
  MEASUREMENT_IPMI_BB_VOLTAGE * bb_volt = NULL;
  EVEL_ENTER();

  /***************************************************************************/
  /* Check assumptions.                                                      */
  /***************************************************************************/
  assert(ipmi != NULL);

  /***************************************************************************/
  /* Allocate a container for the value and push onto the list.              */
  /***************************************************************************/
  bb_volt = malloc(sizeof(MEASUREMENT_IPMI_BB_VOLTAGE));
  assert(bb_volt != NULL);
  assert(id != NULL);
  memset(bb_volt, 0, sizeof(MEASUREMENT_IPMI_BB_VOLTAGE));

  bb_volt->BBVoltageRegID = strdup(id);
  evel_init_option_double(&bb_volt->voltageRegTemperature);

  dlist_push_last(&ipmi->ipmi_base_board_voltage, bb_volt);

  EVEL_EXIT();
  return bb_volt;
}


void evel_measurement_ipmi_bb_volt_set(MEASUREMENT_IPMI *ipmi,
                                    MEASUREMENT_IPMI_BB_VOLTAGE * bb_volt,
                                    const double val)
{
  EVEL_ENTER();
  assert(ipmi != NULL);
  assert(bb_volt != NULL);
  evel_set_option_double(&bb_volt->voltageRegTemperature, val, "Voltage Regulator Temperature");
  EVEL_EXIT();
}



MEASUREMENT_IPMI_BATTERY *evel_measurement_new_ipmi_battery_add(
                                 MEASUREMENT_IPMI * ipmi,
                                 char * id)
{
  MEASUREMENT_IPMI_BATTERY * ipmi_battery = NULL;
  EVEL_ENTER();

  /***************************************************************************/
  /* Check assumptions.                                                      */
  /***************************************************************************/
  assert(ipmi != NULL);
  assert(id != NULL);

  /***************************************************************************/
  /* Allocate a container for the value and push onto the list.              */
  /***************************************************************************/
  EVEL_DEBUG("Adding id=%s", id);
  ipmi_battery = malloc(sizeof(MEASUREMENT_IPMI_BATTERY));
  assert(ipmi_battery != NULL);
  memset(ipmi_battery, 0, sizeof(MEASUREMENT_IPMI_BATTERY));
  ipmi_battery->batteryIdentifier = strdup(id);
  evel_init_option_string(&ipmi_battery->batteryType);
  evel_init_option_double(&ipmi_battery->batteryVoltageLevel);

  dlist_push_last(&ipmi->ipmi_battery, ipmi_battery);

  EVEL_EXIT();
  return ipmi_battery;
}


void evel_measurement_ipmi_battery_type_set(MEASUREMENT_IPMI *ipmi,
                                    MEASUREMENT_IPMI_BATTERY * ipmiBattery,
                                    const char * const batteryType)
{

  EVEL_ENTER();
  assert(ipmi != NULL);
  assert(ipmiBattery != NULL);
  assert(batteryType != NULL);
  evel_set_option_string(&ipmiBattery->batteryType, batteryType, "Battery type");
  EVEL_EXIT();
}



void evel_measurement_ipmi_battery_voltage_set(MEASUREMENT_IPMI *ipmi,
                                    MEASUREMENT_IPMI_BATTERY * ipmiBattery,
                                    const double val)
{
  EVEL_ENTER();
  assert(ipmi != NULL);
  assert(ipmiBattery != NULL);
  evel_set_option_double(&ipmiBattery->batteryVoltageLevel, val, "Battery Voltage Level");
  EVEL_EXIT();
}



MEASUREMENT_IPMI_FAN *evel_measurement_new_ipmi_fan_add(
                                 MEASUREMENT_IPMI * ipmi,
                                 char * id)
{
  MEASUREMENT_IPMI_FAN * ipmi_fan = NULL;

  EVEL_ENTER();

  /***************************************************************************/
  /* Check assumptions.                                                      */
  /***************************************************************************/
  assert(ipmi != NULL);
  assert(id != NULL);

  /***************************************************************************/
  /* Allocate a container for the value and push onto the list.              */
  /***************************************************************************/
  EVEL_DEBUG("Adding id=%s", id);
  ipmi_fan = malloc(sizeof(MEASUREMENT_IPMI_FAN));
  assert(ipmi_fan != NULL);
  memset(ipmi_fan, 0, sizeof(MEASUREMENT_IPMI_FAN));
  ipmi_fan->fanIdentifier = strdup(id);
  evel_init_option_double(&ipmi_fan->fanSpeed);

  dlist_push_last(&ipmi->ipmi_fan, ipmi_fan);

  EVEL_EXIT();
  return ipmi_fan;
}


void evel_measurement_ipmi_fan_speed_set(MEASUREMENT_IPMI *ipmi,
                                    MEASUREMENT_IPMI_FAN * ipmiFan,
                                    const double val)
{
  EVEL_ENTER();
  assert(ipmi != NULL);
  assert(ipmiFan != NULL);
  evel_set_option_double(&ipmiFan->fanSpeed, val, "Fan Speed");
  EVEL_EXIT();
}



MEASUREMENT_IPMI_HSBP *evel_measurement_new_ipmi_hsbp_add(
                                 MEASUREMENT_IPMI * ipmi,
                                 char * id)
{
  MEASUREMENT_IPMI_HSBP * ipmi_hsbp = NULL;
  EVEL_ENTER();

  /***************************************************************************/
  /* Check assumptions.                                                      */
  /***************************************************************************/
  assert(ipmi != NULL);
  assert(id != NULL);

  /***************************************************************************/
  /* Allocate a container for the value and push onto the list.              */
  /***************************************************************************/
  EVEL_DEBUG("Adding id=%s", id);
  ipmi_hsbp = malloc(sizeof(MEASUREMENT_IPMI_HSBP));
  assert(ipmi_hsbp != NULL);
  memset(ipmi_hsbp, 0, sizeof(MEASUREMENT_IPMI_HSBP));
  ipmi_hsbp->hsbpIdentifier = strdup(id);
  evel_init_option_double(&ipmi_hsbp->hsbpTemperature);

  dlist_push_last(&ipmi->ipmi_hsbp, ipmi_hsbp);

  EVEL_EXIT();
  return ipmi_hsbp;
}


void evel_measurement_ipmi_hsbp_temp_set(MEASUREMENT_IPMI *ipmi,
                                    MEASUREMENT_IPMI_HSBP * ipmiHsbp,
                                    const double val)
{
  EVEL_ENTER();
  assert(ipmi != NULL);
  assert(ipmiHsbp != NULL);
  evel_set_option_double(&ipmiHsbp->hsbpTemperature, val, "HSBP Temperature");
  EVEL_EXIT();
}


MEASUREMENT_IPMI_GLOBAL_AGG_TEMP_MARGIN *evel_measurement_new_ipmi_global_temp_add(
                                 MEASUREMENT_IPMI * ipmi,
                                 const char * const id)
{
  MEASUREMENT_IPMI_GLOBAL_AGG_TEMP_MARGIN * global_temp = NULL;
  EVEL_ENTER();

  /***************************************************************************/
  /* Check assumptions.                                                      */
  /***************************************************************************/
  assert(ipmi != NULL);
  assert(id != NULL);

  /***************************************************************************/
  /* Allocate a container for the value and push onto the list.              */
  /***************************************************************************/
  EVEL_DEBUG("Adding id=%s", id);
  global_temp = malloc(sizeof(MEASUREMENT_IPMI_GLOBAL_AGG_TEMP_MARGIN));
  assert(global_temp != NULL);
  memset(global_temp, 0, sizeof(MEASUREMENT_IPMI_GLOBAL_AGG_TEMP_MARGIN));
  global_temp->globalAggTempID = strdup(id);
  evel_init_option_double(&global_temp->globalAggTempMargin);

  dlist_push_last(&ipmi->ipmi_global_agg_temp_margin, global_temp);

  EVEL_EXIT();
  return global_temp;
}

void evel_measurement_ipmi_global_temp_margin_set(MEASUREMENT_IPMI *ipmi,
                      MEASUREMENT_IPMI_GLOBAL_AGG_TEMP_MARGIN * ipmig_temp,
                      const double val)
{
  EVEL_ENTER();
  assert(ipmi != NULL);
  assert(ipmig_temp != NULL);
  evel_set_option_double(&ipmig_temp->globalAggTempMargin, val, "Global Aggregate Temperature Margin");
  EVEL_EXIT();
}


MEASUREMENT_IPMI_NIC *evel_measurement_new_ipmi_nic_add(
                                 MEASUREMENT_IPMI * ipmi,
                                 char * id)
{
  MEASUREMENT_IPMI_NIC * ipmi_nic = NULL;
  EVEL_ENTER();

  /***************************************************************************/
  /* Check assumptions.                                                      */
  /***************************************************************************/
  assert(ipmi != NULL);
  assert(id != NULL);

  /***************************************************************************/
  /* Allocate a container for the value and push onto the list.              */
  /***************************************************************************/
  EVEL_DEBUG("Adding id=%s", id);
  ipmi_nic = malloc(sizeof(MEASUREMENT_IPMI_NIC));
  assert(ipmi_nic != NULL);
  memset(ipmi_nic, 0, sizeof(MEASUREMENT_IPMI_NIC));
  ipmi_nic->nicIdentifier = strdup(id);
  evel_init_option_double(&ipmi_nic->nicTemperature);

  dlist_push_last(&ipmi->ipmi_nic, ipmi_nic);

  EVEL_EXIT();
  return ipmi_nic;
}


void evel_measurement_ipmi_nic_temp_set(MEASUREMENT_IPMI *ipmi,
                                    MEASUREMENT_IPMI_NIC * ipminic,
                                    const double val)
{
  EVEL_ENTER();
  assert(ipmi != NULL);
  assert(ipminic != NULL);
  evel_set_option_double(&ipminic->nicTemperature, val, "NIC Temperature");
  EVEL_EXIT();
}


MEASUREMENT_IPMI_POWER_SUPPLY *evel_measurement_new_ipmi_power_add(
                                 MEASUREMENT_IPMI * ipmi,
                                 char * id)
{
  MEASUREMENT_IPMI_POWER_SUPPLY * ipmi_power = NULL;
  EVEL_ENTER();

  /***************************************************************************/
  /* Check assumptions.                                                      */
  /***************************************************************************/
  assert(ipmi != NULL);
  assert(id != NULL);

  /***************************************************************************/
  /* Allocate a container for the value and push onto the list.              */
  /***************************************************************************/
  EVEL_DEBUG("Adding id=%s", id);
  ipmi_power = malloc(sizeof(MEASUREMENT_IPMI_POWER_SUPPLY));
  assert(ipmi_power != NULL);
  memset(ipmi_power, 0, sizeof(MEASUREMENT_IPMI_POWER_SUPPLY));
  ipmi_power->powerSupplyIdentifier = strdup(id);
  evel_init_option_double(&ipmi_power->powerSupplyInputPower);
  evel_init_option_double(&ipmi_power->powerSupplyCurrentOutput);
  evel_init_option_double(&ipmi_power->powerSupplyTemperature);

  dlist_push_last(&ipmi->ipmi_power, ipmi_power);

  EVEL_EXIT();
  return ipmi_power;
}


void evel_measurement_ipmi_power_inputpwr_set(MEASUREMENT_IPMI *ipmi,
                                    MEASUREMENT_IPMI_POWER_SUPPLY * ipmipwr,
                                    const double val)
{
  EVEL_ENTER();
  assert(ipmi != NULL);
  assert(ipmipwr != NULL);
  evel_set_option_double(&ipmipwr->powerSupplyInputPower, val, "Power Supply Input Power");
  EVEL_EXIT();
}


void evel_measurement_ipmi_power_current_op_set(MEASUREMENT_IPMI *ipmi,
                                    MEASUREMENT_IPMI_POWER_SUPPLY * ipmipwr,
                                    const double val)
{
  EVEL_ENTER();
  assert(ipmi != NULL);
  assert(ipmipwr != NULL);
  evel_set_option_double(&ipmipwr->powerSupplyCurrentOutput, val, "Power Supply Current Output");
  EVEL_EXIT();
}


void evel_measurement_ipmi_power_temp_set(MEASUREMENT_IPMI *ipmi,
                                    MEASUREMENT_IPMI_POWER_SUPPLY * ipmipwr,
                                    const double val)
{
  EVEL_ENTER();
  assert(ipmi != NULL);
  assert(ipmipwr != NULL);
  evel_set_option_double(&ipmipwr->powerSupplyTemperature, val, "Power Supply Temperature");
  EVEL_EXIT();
}


MEASUREMENT_IPMI_PROCESSOR *evel_measurement_new_ipmi_processor_add(
                                 MEASUREMENT_IPMI * ipmi,
                                 char * id)
{
  MEASUREMENT_IPMI_PROCESSOR * ipmi_processor = NULL;
  EVEL_ENTER();

  /***************************************************************************/
  /* Check assumptions.                                                      */
  /***************************************************************************/
  assert(ipmi != NULL);
  assert(id != NULL);

  /***************************************************************************/
  /* Allocate a container for the value and push onto the list.              */
  /***************************************************************************/
  EVEL_DEBUG("Adding id=%s", id);
  ipmi_processor = malloc(sizeof(MEASUREMENT_IPMI_PROCESSOR));
  assert(ipmi_processor != NULL);
  memset(ipmi_processor, 0, sizeof(MEASUREMENT_IPMI_PROCESSOR));
  ipmi_processor->processorIdentifier = strdup(id);
  evel_init_option_double(&ipmi_processor->pprocessorThermalControl);
  evel_init_option_double(&ipmi_processor->processorDtsThermalMargin);

  dlist_initialize(&ipmi_processor->processorDimmAggregateThermalMargin);

  dlist_push_last(&ipmi->ipmi_processor, ipmi_processor);

  EVEL_EXIT();
  return ipmi_processor;
}


void evel_measurement_ipmi_processor_theralCtrl_set(MEASUREMENT_IPMI *ipmi,
                                    MEASUREMENT_IPMI_PROCESSOR * ipmi_processor,
                                    const double val)
{
  EVEL_ENTER();
  assert(ipmi != NULL);
  assert(ipmi_processor != NULL);
  evel_set_option_double(&ipmi_processor->pprocessorThermalControl, val, "IO Module Temperature");
  EVEL_EXIT();
}


void evel_measurement_ipmi_processor_theralMargin_set(MEASUREMENT_IPMI *ipmi,
                                    MEASUREMENT_IPMI_PROCESSOR * ipmi_processor,
                                    const double val)
{
  EVEL_ENTER();
  assert(ipmi != NULL);
  assert(ipmi_processor != NULL);
  evel_set_option_double(&ipmi_processor->processorDtsThermalMargin, val, "Front Panel Temperature");
  EVEL_EXIT();
}

MEASUREMENT_IPMI_PROCESSOR_DIMMAGG_THERM * evel_measurement_ipmi_processor_new_dimmAggThermalMargin_add(
                                  MEASUREMENT_IPMI * ipmi,
                                  MEASUREMENT_IPMI_PROCESSOR *ipmi_processor,
                                  const char * const id, double therm_margin)
{
  MEASUREMENT_IPMI_PROCESSOR_DIMMAGG_THERM * thermal_margin = NULL;
  EVEL_ENTER();

  /***************************************************************************/
  /* Check assumptions.                                                      */
  /***************************************************************************/
  assert(ipmi != NULL);
  assert(ipmi_processor != NULL);
  assert(id != NULL);

  /***************************************************************************/
  /* Allocate a container for the value and push onto the list.              */
  /***************************************************************************/
  EVEL_DEBUG("Adding id=%s, thermal_margin=%lf", id, thermal_margin);
  thermal_margin = malloc(sizeof(MEASUREMENT_IPMI_PROCESSOR_DIMMAGG_THERM));
  assert(thermal_margin != NULL);
  memset(thermal_margin, 0, sizeof(MEASUREMENT_IPMI_PROCESSOR_DIMMAGG_THERM));
  thermal_margin->MarginIdentifier = strdup(id);
  thermal_margin->thermalMargin = therm_margin;

  dlist_push_last(&ipmi_processor->processorDimmAggregateThermalMargin, thermal_margin);

  EVEL_EXIT();
  return thermal_margin;
}


MEASUREMENT_LOAD * evel_measurement_new_loads_add(
                                  EVENT_MEASUREMENT * measurement)
{
  MEASUREMENT_LOAD *load = NULL;
  EVEL_ENTER();

  /***************************************************************************/
  /* Check assumptions.                                                      */
  /***************************************************************************/
  assert(measurement != NULL);
  assert(measurement->header.event_domain == EVEL_DOMAIN_MEASUREMENT);

  /***************************************************************************/
  /* Allocate a container for the value and push onto the list.              */
  /***************************************************************************/
  load = malloc(sizeof(MEASUREMENT_LOAD));
  assert(load != NULL);
  memset(load, 0, sizeof(MEASUREMENT_LOAD));

  evel_init_option_double(&load->shortTerm);
  evel_init_option_double(&load->midTerm);
  evel_init_option_double(&load->longTerm);

  dlist_push_last(&measurement->loads, load);


  EVEL_EXIT();
  return load;
}


void evel_measurement_load_shortTerm_set(MEASUREMENT_LOAD *load,
                                const double val)
{
  EVEL_ENTER();
  assert(load != NULL);
  evel_set_option_double(&load->shortTerm, val, "shortTerm");
  EVEL_EXIT();
}

void evel_measurement_load_midTerm_set(MEASUREMENT_LOAD *load,
                                const double val)
{
  EVEL_ENTER();
  assert(load != NULL);
  evel_set_option_double(&load->midTerm, val, "midTerm");
  EVEL_EXIT();
}

void evel_measurement_load_longTerm_set(MEASUREMENT_LOAD *load,
                                const double val)
{
  EVEL_ENTER();
  assert(load != NULL);
  evel_set_option_double(&load->longTerm, val, "longTerm");
  EVEL_EXIT();
}

MEASUREMENT_PROCESS_STATS * evel_measurement_new_process_stats_add(
                                  EVENT_MEASUREMENT * measurement, 
                                  const char * const processIdentifier )
{
  MEASUREMENT_PROCESS_STATS *process_stat = NULL;
  EVEL_ENTER();

  /***************************************************************************/
  /* Check assumptions.                                                      */
  /***************************************************************************/
  assert(measurement != NULL);
  assert(measurement->header.event_domain == EVEL_DOMAIN_MEASUREMENT);

  /***************************************************************************/
  /* Allocate a container for the value and push onto the list.              */
  /***************************************************************************/
  EVEL_DEBUG("Adding id=%s Process State", processIdentifier);
  process_stat = malloc(sizeof(MEASUREMENT_PROCESS_STATS));
  assert(process_stat != NULL);
  memset(process_stat, 0, sizeof(MEASUREMENT_PROCESS_STATS));
  process_stat->processIdentifier = strdup(processIdentifier);
  assert(process_stat->processIdentifier != NULL);
  dlist_push_last(&measurement->process_stats, process_stat);

  evel_init_option_double(&process_stat->forkRate);
  evel_init_option_double(&process_stat->psStateBlocked);
  evel_init_option_double(&process_stat->psStatePaging);
  evel_init_option_double(&process_stat->psStateRunning);
  evel_init_option_double(&process_stat->psStateSleeping);
  evel_init_option_double(&process_stat->psStateStopped);
  evel_init_option_double(&process_stat->psStateZombie);

  EVEL_EXIT();
  return process_stat;
}

void evel_measurement_process_stat_forkRate_set(MEASUREMENT_PROCESS_STATS *process_stat,
                                              const double val)
{
  EVEL_ENTER();
  assert(process_stat != NULL);
  evel_set_option_double(&process_stat->forkRate, val, "forkRate");
  EVEL_EXIT();
}



void evel_measurement_process_stat_psStateBlocked_set(MEASUREMENT_PROCESS_STATS *process_stat,
                                              const double val)
{
  EVEL_ENTER();
  assert(process_stat != NULL);
  evel_set_option_double(&process_stat->psStateBlocked, val, "psStateBlocked");
  EVEL_EXIT();
}

void evel_measurement_process_stat_psStatePaging_set(MEASUREMENT_PROCESS_STATS *process_stat,
                                              const double val)
{
  EVEL_ENTER();
  assert(process_stat != NULL);
  evel_set_option_double(&process_stat->psStatePaging, val, "psStatePaging");
  EVEL_EXIT();
}


void evel_measurement_process_stat_psStateRunning_set(MEASUREMENT_PROCESS_STATS *process_stat,
                                              const double val)
{
  EVEL_ENTER();
  assert(process_stat != NULL);
  evel_set_option_double(&process_stat->psStateRunning, val, "psStateRunning");
  EVEL_EXIT();
}

void evel_measurement_process_stat_psStateSleeping_set(MEASUREMENT_PROCESS_STATS *process_stat,
                                              const double val)
{
  EVEL_ENTER();
  assert(process_stat != NULL);
  evel_set_option_double(&process_stat->psStateSleeping, val, "psStateSleeping");
  EVEL_EXIT();
}


void evel_measurement_process_stat_psStateStopped_set(MEASUREMENT_PROCESS_STATS *process_stat,
                                              const double val)
{
  EVEL_ENTER();
  assert(process_stat != NULL);
  evel_set_option_double(&process_stat->psStateStopped, val, "psStateStopped");
  EVEL_EXIT();
}

void evel_measurement_process_stat_psStateZombie_set(MEASUREMENT_PROCESS_STATS *process_stat,
                                              const double val)
{
  EVEL_ENTER();
  assert(process_stat != NULL);
  evel_set_option_double(&process_stat->psStateZombie, val, "psStateZombie");
  EVEL_EXIT();
}

MACHINE_CHECK_EXCEPTION * evel_measurement_new_machine_check_exception_add(
                                  EVENT_MEASUREMENT * measurement, 
                                  const char * const process_id )
{
  MACHINE_CHECK_EXCEPTION *machine_check = NULL;
  EVEL_ENTER();

  /***************************************************************************/
  /* Check assumptions.                                                      */
  /***************************************************************************/
  assert(measurement != NULL);
  assert(measurement->header.event_domain == EVEL_DOMAIN_MEASUREMENT);
  assert(process_id != NULL);

  /***************************************************************************/
  /* Allocate a container for the value and push onto the list.              */
  /***************************************************************************/
  EVEL_DEBUG("Adding id=%s - machine check exception", process_id);
  machine_check = malloc(sizeof(MACHINE_CHECK_EXCEPTION));
  assert(machine_check != NULL);
  memset(machine_check, 0, sizeof(MACHINE_CHECK_EXCEPTION));
  machine_check->process_id = strdup(process_id);
  assert(machine_check->process_id != NULL);

  evel_init_option_double(&machine_check->corrected_memory_errors);
  evel_init_option_double(&machine_check->corrected_memory_errors_in_1Hr);
  evel_init_option_double(&machine_check->uncorrected_memory_errors);
  evel_init_option_double(&machine_check->uncorrected_memory_errors_in_1Hr);

  dlist_push_last(&measurement->machine_check_exception, machine_check);

  EVEL_EXIT();
  return machine_check;
}

void evel_measurement_machine_check_cor_mem_err_set(MACHINE_CHECK_EXCEPTION *machine_check,
                                              const double val)
{
  EVEL_ENTER();
  assert(machine_check != NULL);
  evel_set_option_double(&machine_check->corrected_memory_errors, val, "corrected_memory_errors");
  EVEL_EXIT();
}


void evel_measurement_machine_check_cor_mem_err_1hr_set(MACHINE_CHECK_EXCEPTION *machine_check,
                                              const double val)
{
  EVEL_ENTER();
  assert(machine_check != NULL);
  evel_set_option_double(&machine_check->corrected_memory_errors_in_1Hr, val, "corrected_memory_errors_in_1Hr");
  EVEL_EXIT();
}

void evel_measurement_machine_check_uncor_mem_err_set(MACHINE_CHECK_EXCEPTION *machine_check,
                                              const double val)
{
  EVEL_ENTER();
  assert(machine_check != NULL);
  evel_set_option_double(&machine_check->uncorrected_memory_errors, val, "uncorrected_memory_errors");
  EVEL_EXIT();
}

void evel_measurement_machine_check_uncor_mem_err_1hr_set(MACHINE_CHECK_EXCEPTION *machine_check,
                                              const double val)
{
  EVEL_ENTER();
  assert(machine_check != NULL);
  evel_set_option_double(&machine_check->uncorrected_memory_errors_in_1Hr, val, "uncorrected_memory_errors_in_1Hr");
  EVEL_EXIT();
}

MEASUREMENT_HUGE_PAGE * evel_measurement_new_huge_page_add(
                                  EVENT_MEASUREMENT * measurement, 
                                  const char * const hugePagesIdentifier )
{
  MEASUREMENT_HUGE_PAGE *huge_page = NULL;
  EVEL_ENTER();

  /***************************************************************************/
  /* Check assumptions.                                                      */
  /***************************************************************************/
  assert(measurement != NULL);
  assert(measurement->header.event_domain == EVEL_DOMAIN_MEASUREMENT);
  assert(hugePagesIdentifier != NULL);

  /***************************************************************************/
  /* Allocate a container for the value and push onto the list.              */
  /***************************************************************************/
  EVEL_DEBUG("Adding id=%s Huge Page", hugePagesIdentifier);
  huge_page = malloc(sizeof(MEASUREMENT_HUGE_PAGE));
  assert(huge_page != NULL);
  memset(huge_page, 0, sizeof(MEASUREMENT_HUGE_PAGE));
  huge_page->hugePagesIdentifier = strdup(hugePagesIdentifier);
  assert(huge_page->hugePagesIdentifier != NULL);

  evel_init_option_double(&huge_page->bytesUsed);
  evel_init_option_double(&huge_page->bytesFree);
  evel_init_option_double(&huge_page->vmPageNumberUsed);
  evel_init_option_double(&huge_page->vmPageNumberFree);
  evel_init_option_double(&huge_page->percentUsed);
  evel_init_option_double(&huge_page->percentFree);

  dlist_push_last(&measurement->huge_pages, huge_page);

  EVEL_EXIT();
  return huge_page;
}

void evel_measurement_huge_page_bytesUsed_set(MEASUREMENT_HUGE_PAGE *huge_page,
                                              const double val)
{
  EVEL_ENTER();
  assert(huge_page != NULL);
  evel_set_option_double(&huge_page->bytesUsed, val, "bytesUsed");
  EVEL_EXIT();
}

void evel_measurement_huge_page_bytesFree_set(MEASUREMENT_HUGE_PAGE *huge_page,
                                              const double val)
{
  EVEL_ENTER();
  assert(huge_page != NULL);
  evel_set_option_double(&huge_page->bytesFree, val, "bytesFree");
  EVEL_EXIT();
}


void evel_measurement_huge_page_vmPageNumberUsed_set(MEASUREMENT_HUGE_PAGE *huge_page,
                                              const double val)
{
  EVEL_ENTER();
  assert(huge_page != NULL);
  evel_set_option_double(&huge_page->vmPageNumberUsed, val, "vmPageNumberUsed");
  EVEL_EXIT();
}


void evel_measurement_huge_page_vmPageNumberFree_set(MEASUREMENT_HUGE_PAGE *huge_page,
                                              const double val)
{
  EVEL_ENTER();
  assert(huge_page != NULL);
  evel_set_option_double(&huge_page->vmPageNumberFree, val, "vmPageNumberFree");
  EVEL_EXIT();
}


void evel_measurement_huge_page_percentUsed_set(MEASUREMENT_HUGE_PAGE *huge_page,
                                              const double val)
{
  EVEL_ENTER();
  assert(huge_page != NULL);
  evel_set_option_double(&huge_page->percentUsed, val, "percentUsed");
  EVEL_EXIT();
}


void evel_measurement_huge_page_percentFree_set(MEASUREMENT_HUGE_PAGE *huge_page,
                                              const double val)
{
  EVEL_ENTER();
  assert(huge_page != NULL);
  evel_set_option_double(&huge_page->percentFree, val, "percentFree");
  EVEL_EXIT();
}

void evel_json_encode_ipmi(EVEL_JSON_BUFFER * jbuf, MEASUREMENT_IPMI * ipmi_entry)
{

  DLIST_ITEM * item = NULL;
  MEASUREMENT_IPMI_BB_TEMPERATURE * bb_temp = NULL;
  MEASUREMENT_IPMI_BB_VOLTAGE * bb_volt = NULL;
  MEASUREMENT_IPMI_BATTERY * ipmi_batt = NULL;
  MEASUREMENT_IPMI_FAN * ipmi_fan = NULL;
  MEASUREMENT_IPMI_HSBP * ipmi_hsbp = NULL;
  MEASUREMENT_IPMI_NIC * ipmi_nic = NULL;
  MEASUREMENT_IPMI_POWER_SUPPLY * ipmi_pwr = NULL;
  MEASUREMENT_IPMI_PROCESSOR * ipmi_proc = NULL;
  MEASUREMENT_IPMI_PROCESSOR_DIMMAGG_THERM * dimm_therm = NULL;
  MEASUREMENT_IPMI_GLOBAL_AGG_TEMP_MARGIN * agg_temp = NULL;
  DLIST_ITEM * item1 = NULL;

  EVEL_ENTER();
  assert(ipmi_entry != NULL);

  evel_enc_kv_opt_double(jbuf, "exitAirTemperature", &ipmi_entry->exitAirTemperature);
  evel_enc_kv_opt_double(jbuf, "frontPanelTemperature", &ipmi_entry->frontPanelTemperature);
  evel_enc_kv_opt_double(jbuf, "ioModuleTemperature", &ipmi_entry->ioModuleTemperature);
  evel_enc_kv_opt_double(jbuf, "systemAirflow", &ipmi_entry->systemAirflow);

  /***************************************************************************/
  /* Baseboard Temperature                                                   */
  /***************************************************************************/
  evel_json_checkpoint(jbuf);
  if (evel_json_open_opt_named_list(jbuf, "ipmiBaseboardTemperatureArray"))
  {
    bool item_added = false;

    item = dlist_get_first(&ipmi_entry->ipmi_base_board_temparature);
    while (item != NULL)
    {
      bb_temp = (MEASUREMENT_IPMI_BB_TEMPERATURE *) item->item;
      assert(bb_temp != NULL);

      if (!evel_throttle_suppress_nv_pair(jbuf->throttle_spec,
                                          "ipmiBaseboardTemperatureArray",
                                          bb_temp->BBTemperatureID))
      {
        evel_json_open_object(jbuf);

        evel_enc_kv_string(jbuf, "baseboardTemperatureIdentifier", bb_temp->BBTemperatureID);
        evel_enc_kv_opt_double(jbuf, "baseboardTemperature", &bb_temp->BBTemperature);

        evel_json_close_object(jbuf);
        item_added = true;
      }
      item = dlist_get_next(item);
    }
    evel_json_close_list(jbuf);

    /*************************************************************************/
    /* If we've not written anything, rewind to before we opened the list.   */
    /*************************************************************************/
    if (!item_added)
    {
      evel_json_rewind(jbuf);
    }
  }

  /***************************************************************************/
  /* Baseboard Voltage                                                       */
  /***************************************************************************/
  evel_json_checkpoint(jbuf);
  if (evel_json_open_opt_named_list(jbuf, "ipmiBaseboardVoltageRegulatorArray"))
  {
    bool item_added = false;

    item = dlist_get_first(&ipmi_entry->ipmi_base_board_voltage);
    while (item != NULL)
    {
      bb_volt = (MEASUREMENT_IPMI_BB_VOLTAGE *) item->item;
      assert(bb_volt != NULL);

      if (!evel_throttle_suppress_nv_pair(jbuf->throttle_spec,
                                          "ipmiBaseboardVoltageRegulatorArray",
                                          bb_volt->BBVoltageRegID))
      {
        evel_json_open_object(jbuf);

        evel_enc_kv_string(jbuf, "baseboardVoltageRegulatorIdentifier", bb_volt->BBVoltageRegID);
        evel_enc_kv_opt_double(jbuf, "voltageRegulatorTemperature", &bb_volt->voltageRegTemperature);

        evel_json_close_object(jbuf);
        item_added = true;
      }
      item = dlist_get_next(item);
    }
    evel_json_close_list(jbuf);

    /*************************************************************************/
    /* If we've not written anything, rewind to before we opened the list.   */
    /*************************************************************************/
    if (!item_added)
    {
      evel_json_rewind(jbuf);
    }
  }

  /***************************************************************************/
  /* IPMI Battery                                                            */
  /***************************************************************************/
  evel_json_checkpoint(jbuf);
  if (evel_json_open_opt_named_list(jbuf, "ipmiBatteryArray"))
  {
    bool item_added = false;

    item = dlist_get_first(&ipmi_entry->ipmi_battery);
    while (item != NULL)
    {
      ipmi_batt = (MEASUREMENT_IPMI_BATTERY *) item->item;
      assert(ipmi_batt != NULL);

      if (!evel_throttle_suppress_nv_pair(jbuf->throttle_spec,
                                          "ipmiBatteryArray",
                                          ipmi_batt->batteryIdentifier))
      {
        evel_json_open_object(jbuf);

        evel_enc_kv_string(jbuf, "batteryIdentifier", ipmi_batt->batteryIdentifier);
        evel_enc_kv_opt_double(jbuf, "batteryVoltageLevel", &ipmi_batt->batteryVoltageLevel);
        evel_enc_kv_opt_string(jbuf, "batteryType", &ipmi_batt->batteryType);

        evel_json_close_object(jbuf);
        item_added = true;
      }
      item = dlist_get_next(item);
    }
    evel_json_close_list(jbuf);

    /*************************************************************************/
    /* If we've not written anything, rewind to before we opened the list.   */
    /*************************************************************************/
    if (!item_added)
    {
      evel_json_rewind(jbuf);
    }
  }


  /***************************************************************************/
  /* IPMI Fan                                                                */
  /***************************************************************************/
  evel_json_checkpoint(jbuf);
  if (evel_json_open_opt_named_list(jbuf, "ipmiFanArray"))
  {
    bool item_added = false;

    item = dlist_get_first(&ipmi_entry->ipmi_fan);
    while (item != NULL)
    {
      ipmi_fan = (MEASUREMENT_IPMI_FAN *) item->item;
      assert(ipmi_fan != NULL);

      if (!evel_throttle_suppress_nv_pair(jbuf->throttle_spec,
                                          "ipmiFanArray",
                                          ipmi_fan->fanIdentifier))
      {
        evel_json_open_object(jbuf);

        evel_enc_kv_string(jbuf, "fanIdentifier", ipmi_fan->fanIdentifier);
        evel_enc_kv_opt_double(jbuf, "fanSpeed", &ipmi_fan->fanSpeed);

        evel_json_close_object(jbuf);
        item_added = true;
      }
      item = dlist_get_next(item);
    }
    evel_json_close_list(jbuf);

    /*************************************************************************/
    /* If we've not written anything, rewind to before we opened the list.   */
    /*************************************************************************/
    if (!item_added)
    {
      evel_json_rewind(jbuf);
    }
  }

  /***************************************************************************/
  /* IPMI HSBP                                                               */
  /***************************************************************************/
  evel_json_checkpoint(jbuf);
  if (evel_json_open_opt_named_list(jbuf, "ipmiHsbpArray"))
  {
    bool item_added = false;

    item = dlist_get_first(&ipmi_entry->ipmi_hsbp);
    while (item != NULL)
    {
      ipmi_hsbp = (MEASUREMENT_IPMI_HSBP *) item->item;
      assert(ipmi_hsbp != NULL);

      if (!evel_throttle_suppress_nv_pair(jbuf->throttle_spec,
                                          "ipmiHsbpArray",
                                          ipmi_hsbp->hsbpIdentifier))
      {
        evel_json_open_object(jbuf);

        evel_enc_kv_string(jbuf, "hsbpIdentifier", ipmi_hsbp->hsbpIdentifier);
        evel_enc_kv_opt_double(jbuf, "hsbpTemperature", &ipmi_hsbp->hsbpTemperature);

        evel_json_close_object(jbuf);
        item_added = true;
      }
      item = dlist_get_next(item);
    }
    evel_json_close_list(jbuf);

    /*************************************************************************/
    /* If we've not written anything, rewind to before we opened the list.   */
    /*************************************************************************/
    if (!item_added)
    {
      evel_json_rewind(jbuf);
    }
  }

  /***************************************************************************/
  /* IPMI Global Aggregate Temperature margin                                */
  /***************************************************************************/
  evel_json_checkpoint(jbuf);
  if (evel_json_open_opt_named_list(jbuf, "ipmiGlobalAggregateTemperatureMarginArray"))
  {
    bool item_added = false;

    item = dlist_get_first(&ipmi_entry->ipmi_global_agg_temp_margin);
    while (item != NULL)
    {
      agg_temp = (MEASUREMENT_IPMI_GLOBAL_AGG_TEMP_MARGIN *) item->item;
      assert(agg_temp != NULL);

      if (!evel_throttle_suppress_nv_pair(jbuf->throttle_spec,
                                   "ipmiGlobalAggregateTemperatureMarginArray",
                                    agg_temp->globalAggTempID))
      {
        evel_json_open_object(jbuf);

        evel_enc_kv_string(jbuf, "globalAggregateTemperatureMarginIdentifier", agg_temp->globalAggTempID);
        evel_enc_kv_opt_double(jbuf, "globalAggregateTemperatureMargin", &agg_temp->globalAggTempMargin);

        evel_json_close_object(jbuf);
        item_added = true;
      }
      item = dlist_get_next(item);
    }
    evel_json_close_list(jbuf);

    /*************************************************************************/
    /* If we've not written anything, rewind to before we opened the list.   */
    /*************************************************************************/
    if (!item_added)
    {
      evel_json_rewind(jbuf);
    }
  }

  /***************************************************************************/
  /* IPMI NIC                                                                */
  /***************************************************************************/
  evel_json_checkpoint(jbuf);
  if (evel_json_open_opt_named_list(jbuf, "ipmiNicArray"))
  {
    bool item_added = false;

    item = dlist_get_first(&ipmi_entry->ipmi_nic);
    while (item != NULL)
    {
      ipmi_nic = (MEASUREMENT_IPMI_NIC *) item->item;
      assert(ipmi_nic != NULL);

      if (!evel_throttle_suppress_nv_pair(jbuf->throttle_spec,
                                          "ipmiNicArray",
                                          ipmi_nic->nicIdentifier))
      {
        evel_json_open_object(jbuf);

        evel_enc_kv_string(jbuf, "nicIdentifier", ipmi_nic->nicIdentifier);
        evel_enc_kv_opt_double(jbuf, "nicTemperature", &ipmi_nic->nicTemperature);

        evel_json_close_object(jbuf);
        item_added = true;
      }
      item = dlist_get_next(item);
    }
    evel_json_close_list(jbuf);

    /*************************************************************************/
    /* If we've not written anything, rewind to before we opened the list.   */
    /*************************************************************************/
    if (!item_added)
    {
      evel_json_rewind(jbuf);
    }
  }

  /***************************************************************************/
  /* IPMI Power                                                              */
  /***************************************************************************/
  evel_json_checkpoint(jbuf);
  if (evel_json_open_opt_named_list(jbuf, "ipmiPowerSupplyArray"))
  {
    bool item_added = false;

    item = dlist_get_first(&ipmi_entry->ipmi_power);
    while (item != NULL)
    {
      ipmi_pwr = (MEASUREMENT_IPMI_POWER_SUPPLY *) item->item;
      assert(ipmi_pwr != NULL);

      if (!evel_throttle_suppress_nv_pair(jbuf->throttle_spec,
                                          "ipmiPowerSupplyArray",
                                          ipmi_pwr->powerSupplyIdentifier))
      {
        evel_json_open_object(jbuf);

        evel_enc_kv_string(jbuf, "powerSupplyIdentifier", ipmi_pwr->powerSupplyIdentifier);
        evel_enc_kv_opt_double(jbuf, "powerSupplyCurrentOutputPercent", &ipmi_pwr->powerSupplyCurrentOutput);
        evel_enc_kv_opt_double(jbuf, "powerSupplyInputPower", &ipmi_pwr->powerSupplyInputPower);
        evel_enc_kv_opt_double(jbuf, "powerSupplyTemperature", &ipmi_pwr->powerSupplyTemperature);

        evel_json_close_object(jbuf);
        item_added = true;
      }
      item = dlist_get_next(item);
    }
    evel_json_close_list(jbuf);

    /*************************************************************************/
    /* If we've not written anything, rewind to before we opened the list.   */
    /*************************************************************************/
    if (!item_added)
    {
      evel_json_rewind(jbuf);
    }
  }

  /***************************************************************************/
  /* IPMI Processor                                                          */
  /***************************************************************************/
  evel_json_checkpoint(jbuf);
  if (evel_json_open_opt_named_list(jbuf, "ipmiProcessorArray"))
  {
    bool item_added = false;

    item = dlist_get_first(&ipmi_entry->ipmi_processor);
    while (item != NULL)
    {
      ipmi_proc = (MEASUREMENT_IPMI_PROCESSOR *) item->item;
      assert(ipmi_proc != NULL);

      if (!evel_throttle_suppress_nv_pair(jbuf->throttle_spec,
                                          "ipmiProcessorArray",
                                          ipmi_proc->processorIdentifier))
      {
        evel_json_open_object(jbuf);

        evel_enc_kv_string(jbuf, "processorIdentifier", ipmi_proc->processorIdentifier);
        evel_enc_kv_opt_double(jbuf, "processorDtsThermalMargin", &ipmi_proc->processorDtsThermalMargin);
        evel_enc_kv_opt_double(jbuf, "processorThermalControlPercent", &ipmi_proc->pprocessorThermalControl);
        evel_json_checkpoint(jbuf);
        if (evel_json_open_opt_named_list(jbuf, "processorDimmAggregateThermalMarginArray"))
        {
          bool item1_added = false;

          item1 = dlist_get_first(&ipmi_proc->processorDimmAggregateThermalMargin);
          while (item1 != NULL)
          {
            dimm_therm = (MEASUREMENT_IPMI_PROCESSOR_DIMMAGG_THERM *) item1->item;
            assert(dimm_therm != NULL);

            if (!evel_throttle_suppress_nv_pair(jbuf->throttle_spec,
                                          "processorDimmAggregateThermalMarginArray",
                                          dimm_therm->MarginIdentifier))
            {
              evel_json_open_object(jbuf);
              evel_enc_kv_string(jbuf, "processorDimmAggregateThermalMarginIdentifier", dimm_therm->MarginIdentifier);
              evel_enc_kv_double(jbuf, "thermalMargin", dimm_therm->thermalMargin);

              evel_json_close_object(jbuf);
              item1_added = true;
            }
            item1 = dlist_get_next(item1);
          }
          evel_json_close_list(jbuf);

          if (!item1_added)
          {
            evel_json_rewind(jbuf);
          }
        }

        evel_json_close_object(jbuf);
        item_added = true;
      }
      item = dlist_get_next(item);
    }
    evel_json_close_list(jbuf);

    /*************************************************************************/
    /* If we've not written anything, rewind to before we opened the list.   */
    /*************************************************************************/
    if (!item_added)
    {
      evel_json_rewind(jbuf);
    }
  }
  EVEL_EXIT();
}

/**************************************************************************//**
 * Encode the measurement as a JSON measurement.
 *
 * @param jbuf          Pointer to the ::EVEL_JSON_BUFFER to encode into.
 * @param event         Pointer to the ::EVENT_HEADER to encode.
 *****************************************************************************/
void evel_json_encode_measurement(EVEL_JSON_BUFFER * jbuf,
                                  EVENT_MEASUREMENT * event)
{
  MEASUREMENT_HUGE_PAGE * huge_page = NULL;
  MEASUREMENT_CPU_USE * cpu_use = NULL;
  MEASUREMENT_MEM_USE * mem_use = NULL;
  MEASUREMENT_DISK_USE * disk_use = NULL;
  MEASUREMENT_FSYS_USE * fsys_use = NULL;
  MEASUREMENT_LATENCY_BUCKET * bucket = NULL;
  MEASUREMENT_NIC_PERFORMANCE * nic_performance = NULL;
  MEASUREMENT_CODEC_USE * codec_use = NULL;
  MEASUREMENT_PROCESS_STATS * proc_stat = NULL;
  MEASUREMENT_LOAD * load = NULL;
  MACHINE_CHECK_EXCEPTION * machine_check = NULL;
  MEASUREMENT_IPMI * ipmi_entry = NULL;
  DLIST_ITEM * item = NULL;
  DLIST_ITEM * other_field_item = NULL;
  EVEL_JSON_OBJECT_INSTANCE * jsonobjinst = NULL;
  EVEL_JSON_OBJECT * jsonobjp = NULL;
  DLIST_ITEM * jsobj_field_item = NULL;
  EVEL_INTERNAL_KEY * keyinst = NULL;
  DLIST_ITEM * keyinst_field_item = NULL;
  DLIST_ITEM * dlist_item = NULL;
  HASHTABLE_T * ht;
  ENTRY_T *entry;
  char * state = NULL;

  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.                                                    */
  /***************************************************************************/
  assert(event != NULL);
  assert(event->header.event_domain == EVEL_DOMAIN_MEASUREMENT);

  evel_json_encode_header(jbuf, &event->header);
  evel_json_open_named_object(jbuf, "measurementFields");

  /***************************************************************************/
  /* Mandatory fields.                                                       */
  /***************************************************************************/
  evel_enc_kv_int(jbuf, "measurementInterval", event->measurement_interval);

  /***************************************************************************/
  /* Optional fields.                                                        */
  /***************************************************************************/

  /***************************************************************************/
  /* IPMI                                                                    */
  /***************************************************************************/
  evel_json_checkpoint(jbuf);
  if (evel_json_open_opt_named_object(jbuf, "ipmi"))
  {
    bool item_added = false;

    item = dlist_get_first(&event->ipmis);
    while (item != NULL)
    {
      ipmi_entry = (MEASUREMENT_IPMI *) item->item;
      assert(ipmi_entry != NULL);

      if (!evel_throttle_suppress_field(jbuf->throttle_spec,
                                          "ipmi"))
      {
       // evel_json_open_object(jbuf);
        evel_json_encode_ipmi(jbuf, ipmi_entry);
       // evel_json_close_object(jbuf);
        item_added = true;
      }
      item = dlist_get_next(item);
    }
    evel_json_close_object(jbuf);

    /*************************************************************************/
    /* If we've not written anything, rewind to before we opened the list.   */
    /*************************************************************************/
    if (!item_added)
    {
      evel_json_rewind(jbuf);
    }
  }

  /***************************************************************************/
  /* Huge Page                                                               */
  /***************************************************************************/
  evel_json_checkpoint(jbuf);
  if (evel_json_open_opt_named_list(jbuf, "hugePagesArray"))
  {
    bool item_added = false;

    item = dlist_get_first(&event->huge_pages);
    while (item != NULL)
    {
      huge_page = (MEASUREMENT_HUGE_PAGE *) item->item;
      assert(huge_page != NULL);

      if (!evel_throttle_suppress_nv_pair(jbuf->throttle_spec,
                                          "hugePagesArray",
                                          huge_page->hugePagesIdentifier))
      {
        evel_json_open_object(jbuf);
        evel_enc_kv_string(jbuf, "hugePagesIdentifier", huge_page->hugePagesIdentifier);
        evel_enc_kv_opt_double(jbuf, "bytesUsed", &huge_page->bytesUsed);
        evel_enc_kv_opt_double(jbuf, "bytesFree", &huge_page->bytesFree);
        evel_enc_kv_opt_double(jbuf, "vmPageNumberUsed", &huge_page->vmPageNumberUsed);
        evel_enc_kv_opt_double(jbuf, "vmPageNumberFree", &huge_page->vmPageNumberFree);
        evel_enc_kv_opt_double(jbuf, "percentUsed", &huge_page->bytesUsed);
        evel_enc_kv_opt_double(jbuf, "percentFree", &huge_page->bytesUsed);
        evel_json_close_object(jbuf);
        item_added = true;
      }
      item = dlist_get_next(item);
    }
    evel_json_close_list(jbuf);

    /*************************************************************************/
    /* If we've not written anything, rewind to before we opened the list.   */
    /*************************************************************************/
    if (!item_added)
    {
      evel_json_rewind(jbuf);
    }
  }

  /***************************************************************************/
  /* Machine check exception                                                 */
  /***************************************************************************/
  evel_json_checkpoint(jbuf);
  if (evel_json_open_opt_named_list(jbuf, "machineCheckExceptionArray"))
  {
    bool item_added = false;

    item = dlist_get_first(&event->machine_check_exception);
    while (item != NULL)
    {
      machine_check = (MACHINE_CHECK_EXCEPTION *) item->item;
      assert(machine_check != NULL);

      if (!evel_throttle_suppress_nv_pair(jbuf->throttle_spec,
                                          "machineCheckExceptionArray",
                                          machine_check->process_id))
      {
        evel_json_open_object(jbuf);
        evel_enc_kv_string(jbuf, "vmIdentifier", machine_check->process_id);
        evel_enc_kv_opt_double(jbuf, "correctedMemoryErrors", &machine_check->corrected_memory_errors);
        evel_enc_kv_opt_double(jbuf, "correctedMemoryErrorsIn1Hr", &machine_check->corrected_memory_errors_in_1Hr);
        evel_enc_kv_opt_double(jbuf, "uncorrectedMemoryErrors", &machine_check->uncorrected_memory_errors);
        evel_enc_kv_opt_double(jbuf, "uncorrectedMemoryErrorsIn1Hr", &machine_check->uncorrected_memory_errors_in_1Hr);
        evel_json_close_object(jbuf);
        item_added = true;
      }
      item = dlist_get_next(item);
    }
    evel_json_close_list(jbuf);

    /*************************************************************************/
    /* If we've not written anything, rewind to before we opened the list.   */
    /*************************************************************************/
    if (!item_added)
    {
      evel_json_rewind(jbuf);
    }
  }

  /***************************************************************************/
  /* Loads                                                                   */
  /***************************************************************************/
  evel_json_checkpoint(jbuf);
  if (evel_json_open_opt_named_list(jbuf, "loadArray"))
  {
    bool item_added = false;

    item = dlist_get_first(&event->loads);
    while (item != NULL)
    {
      load = (MEASUREMENT_LOAD *) item->item;
      assert(load != NULL);

      if (!evel_throttle_suppress_field(jbuf->throttle_spec,
                                          "loadArray"))
      {
        evel_json_open_object(jbuf);
        evel_enc_kv_opt_double(jbuf, "shortTerm", &load->shortTerm);
        evel_enc_kv_opt_double(jbuf, "midTerm", &load->midTerm);
        evel_enc_kv_opt_double(jbuf, "longTerm", &load->longTerm);
        evel_json_close_object(jbuf);
        item_added = true;
      }
      item = dlist_get_next(item);
    }
    evel_json_close_list(jbuf);

    /*************************************************************************/
    /* If we've not written anything, rewind to before we opened the list.   */
    /*************************************************************************/
    if (!item_added)
    {
      evel_json_rewind(jbuf);
    }
  }

  /***************************************************************************/
  /*  Process stats                                                          */
  /***************************************************************************/
  evel_json_checkpoint(jbuf);
  if (evel_json_open_opt_named_list(jbuf, "processStatsArray"))
  {
    bool item_added = false;

    item = dlist_get_first(&event->process_stats);
    while (item != NULL)
    {
      proc_stat = (MEASUREMENT_PROCESS_STATS *) item->item;
      assert(proc_stat != NULL);

      if (!evel_throttle_suppress_nv_pair(jbuf->throttle_spec,
                                          "processStatsArray",
                                          proc_stat->processIdentifier))
      {
        evel_json_open_object(jbuf);
        evel_enc_kv_string(jbuf, "processIdentifier", proc_stat->processIdentifier);
        evel_enc_kv_opt_double(jbuf, "forkRate", &proc_stat->forkRate);
        evel_enc_kv_opt_double(jbuf, "psStateBlocked", &proc_stat->psStateBlocked);
        evel_enc_kv_opt_double(jbuf, "psStatePaging", &proc_stat->psStatePaging);
        evel_enc_kv_opt_double(jbuf, "psStateRunning", &proc_stat->psStateRunning);
        evel_enc_kv_opt_double(jbuf, "psStateSleeping", &proc_stat->psStateSleeping);
        evel_enc_kv_opt_double(jbuf, "psStateStopped", &proc_stat->psStateStopped);
        evel_enc_kv_opt_double(jbuf, "psStateZombie", &proc_stat->psStateZombie);
        evel_json_close_object(jbuf);
        item_added = true;
      }
      item = dlist_get_next(item);
    }
    evel_json_close_list(jbuf);

    /*************************************************************************/
    /* If we've not written anything, rewind to before we opened the list.   */
    /*************************************************************************/
    if (!item_added)
    {
      evel_json_rewind(jbuf);
    }
  }

  // additional fields
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
            EVEL_DEBUG("Encoding additionalFields %s %s",(char *) (entry->key), entry->value);
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

  evel_json_checkpoint(jbuf);
  if(evel_json_open_opt_named_list(jbuf, "additionalObjects"))
  {
  bool item_added = false;
  other_field_item = dlist_get_first(&event->additional_objects);
  while (other_field_item != NULL)
  {
    jsonobjp = (EVEL_JSON_OBJECT *) other_field_item->item;
    if(jsonobjp != NULL)
    {
     evel_json_open_object(jbuf);

       if( evel_json_open_opt_named_list(jbuf, "objectInstances"))
       {
        bool item_added2 = false;
        jsobj_field_item = dlist_get_first(&jsonobjp->jsonobjectinstances);
        while (jsobj_field_item != NULL)
        {
           jsonobjinst = (EVEL_JSON_OBJECT_INSTANCE *) jsobj_field_item->item;
           if( jsonobjinst != NULL )
           {
              evel_json_open_object(jbuf);
              evel_enc_kv_object(jbuf, "objectInstance", jsonobjinst->jsonstring);
              evel_enc_kv_opt_ull(jbuf, "objectInstanceEpochMicrosec", &jsonobjinst->objinst_epoch_microsec);
  //evel_json_checkpoint(jbuf);
  if (evel_json_open_opt_named_list(jbuf, "objectKeys"))
  {
//   bool item_added3 = false;

    keyinst_field_item = dlist_get_first(&jsonobjinst->object_keys);
    while (keyinst_field_item != NULL)
    {
      keyinst = (EVEL_INTERNAL_KEY *)keyinst_field_item->item;
      if(keyinst != NULL)
      {
        evel_json_open_object(jbuf);
        evel_enc_kv_string(jbuf, "keyName", keyinst->keyname);
        evel_enc_kv_opt_int(jbuf, "keyOrder", &keyinst->keyorder);
        evel_enc_kv_opt_string(jbuf, "keyValue", &keyinst->keyvalue);
        evel_json_close_object(jbuf);
//      item_added3 = true;
      }
      keyinst_field_item = dlist_get_next(keyinst_field_item);
    }
    evel_json_close_list(jbuf);

    /*************************************************************************/
    /* If we've not written anything, rewind to before we opened the list.   */
    /*************************************************************************/
    //if (!item_added3)
    //{
    //  evel_json_rewind(jbuf);
    //}
  }
               evel_json_close_object(jbuf);
            }
            item_added2 = true;
            jsobj_field_item = dlist_get_next(jsobj_field_item);
        }
        evel_json_close_list(jbuf);
        if( !item_added2 )
        {
          evel_json_rewind(jbuf);
        }
       }

    evel_enc_kv_string(jbuf, "objectName", jsonobjp->object_name);
    evel_enc_kv_opt_string(jbuf, "objectSchema", &jsonobjp->objectschema);
    evel_enc_kv_opt_string(jbuf, "objectSchemaUrl", &jsonobjp->objectschemaurl);
    evel_enc_kv_opt_string(jbuf, "nfSubscribedObjectName", &jsonobjp->nfsubscribedobjname);
    evel_enc_kv_opt_string(jbuf, "nfSubscriptionId", &jsonobjp->nfsubscriptionid);
    evel_json_close_object(jbuf);
    item_added = true;
  }
  other_field_item = dlist_get_next(other_field_item);
  }
  evel_json_close_list(jbuf);

  if (!item_added)
  {
     evel_json_rewind(jbuf);
  }
  }


  // additional json objects
  evel_enc_kv_opt_int(jbuf, "concurrentSessions", &event->concurrent_sessions);
  evel_enc_kv_opt_int(jbuf, "configuredEntities", &event->configured_entities);

  /***************************************************************************/
  /* CPU Use list.                                                           */
  /***************************************************************************/
  evel_json_checkpoint(jbuf);
  if (evel_json_open_opt_named_list(jbuf, "cpuUsageArray"))
  {
    bool item_added = false;

    item = dlist_get_first(&event->cpu_usage);
    while (item != NULL)
    {
      cpu_use = (MEASUREMENT_CPU_USE*) item->item;
      assert(cpu_use != NULL);

      if (!evel_throttle_suppress_nv_pair(jbuf->throttle_spec,
                                          "cpuUsageArray",
                                          cpu_use->id))
      {
        evel_json_open_object(jbuf);
        evel_enc_kv_string(jbuf, "cpuIdentifier", cpu_use->id);
        evel_enc_kv_opt_double(jbuf, "cpuIdle", &cpu_use->idle);
        evel_enc_kv_opt_double(jbuf, "cpuUsageInterrupt", &cpu_use->intrpt);
        evel_enc_kv_opt_double(jbuf, "cpuUsageNice", &cpu_use->nice);
        evel_enc_kv_opt_double(jbuf, "cpuUsageSoftIrq", &cpu_use->softirq);
        evel_enc_kv_opt_double(jbuf, "cpuUsageSteal", &cpu_use->steal);
        evel_enc_kv_opt_double(jbuf, "cpuUsageSystem", &cpu_use->sys);
        evel_enc_kv_opt_double(jbuf, "cpuUsageUser", &cpu_use->user);
        evel_enc_kv_opt_double(jbuf, "cpuWait", &cpu_use->wait);
        evel_enc_kv_double(jbuf, "percentUsage",cpu_use->usage);
        evel_enc_kv_opt_double(jbuf, "cpuCapacityContention", &cpu_use->cpuCapacityContention);
        evel_enc_kv_opt_double(jbuf, "cpuDemandAvg", &cpu_use->cpuDemandAvg);
        evel_enc_kv_opt_double(jbuf, "cpuDemandMhz", &cpu_use->cpuDemandMhz);
        evel_enc_kv_opt_double(jbuf, "cpuDemandPct", &cpu_use->cpuDemandPct);
        evel_enc_kv_opt_double(jbuf, "cpuLatencyAvg", &cpu_use->cpuLatencyAvg);
        evel_enc_kv_opt_double(jbuf, "cpuOverheadAvg", &cpu_use->cpuOverheadAvg);
        evel_enc_kv_opt_double(jbuf, "cpuSwapWaitTime", &cpu_use->cpuSwapWaitTime);
        evel_json_close_object(jbuf);
        item_added = true;
      }
      item = dlist_get_next(item);
    }
    evel_json_close_list(jbuf);

    /*************************************************************************/
    /* If we've not written anything, rewind to before we opened the list.   */
    /*************************************************************************/
    if (!item_added)
    {
      evel_json_rewind(jbuf);
    }
  }


  /***************************************************************************/
  /* Disk Use list.                                                           */
  /***************************************************************************/
  evel_json_checkpoint(jbuf);
  if (evel_json_open_opt_named_list(jbuf, "diskUsageArray"))
  {
    bool item_added = false;

    item = dlist_get_first(&event->disk_usage);
    while (item != NULL)
    {
      disk_use = (MEASUREMENT_DISK_USE*) item->item;
      assert(disk_use != NULL);

      if (!evel_throttle_suppress_nv_pair(jbuf->throttle_spec,
                                          "diskUsageArray",
                                          disk_use->id))
      {
        evel_json_open_object(jbuf);
        evel_enc_kv_string(jbuf, "diskIdentifier", disk_use->id);
        evel_enc_kv_opt_double(jbuf, "diskIoTimeAvg", &disk_use->iotimeavg);
        evel_enc_kv_opt_double(jbuf, "diskIoTimeLast", &disk_use->iotimelast);
        evel_enc_kv_opt_double(jbuf, "diskIoTimeMax", &disk_use->iotimemax);
        evel_enc_kv_opt_double(jbuf, "diskIoTimeMin", &disk_use->iotimemin);
        evel_enc_kv_opt_double(jbuf, "diskMergedReadAvg", &disk_use->mergereadavg);
        evel_enc_kv_opt_double(jbuf, "diskMergedReadLast", &disk_use->mergereadlast);
        evel_enc_kv_opt_double(jbuf, "diskMergedReadMax", &disk_use->mergereadmax);
        evel_enc_kv_opt_double(jbuf, "diskMergedReadMin", &disk_use->mergereadmin);
        evel_enc_kv_opt_double(jbuf, "diskMergedWriteAvg", &disk_use->mergewriteavg);
        evel_enc_kv_opt_double(jbuf, "diskMergedWriteLast", &disk_use->mergewritelast);
        evel_enc_kv_opt_double(jbuf, "diskMergedWriteMax", &disk_use->mergewritemax);
        evel_enc_kv_opt_double(jbuf, "diskMergedWriteMin", &disk_use->mergewritemin);
        evel_enc_kv_opt_double(jbuf, "diskOctetsReadAvg", &disk_use->octetsreadavg);
        evel_enc_kv_opt_double(jbuf, "diskOctetsReadLast", &disk_use->octetsreadlast);
        evel_enc_kv_opt_double(jbuf, "diskOctetsReadMax", &disk_use->octetsreadmax);
        evel_enc_kv_opt_double(jbuf, "diskOctetsReadMin", &disk_use->octetsreadmin);
        evel_enc_kv_opt_double(jbuf, "diskOctetsWriteAvg", &disk_use->octetswriteavg);
        evel_enc_kv_opt_double(jbuf, "diskOctetsWriteLast", &disk_use->octetswritelast);
        evel_enc_kv_opt_double(jbuf, "diskOctetsWriteMax", &disk_use->octetswritemax);
        evel_enc_kv_opt_double(jbuf, "diskOctetsWriteMin", &disk_use->octetswritemin);
        evel_enc_kv_opt_double(jbuf, "diskOpsReadAvg", &disk_use->opsreadavg);
        evel_enc_kv_opt_double(jbuf, "diskOpsReadLast", &disk_use->opsreadlast);
        evel_enc_kv_opt_double(jbuf, "diskOpsReadMax", &disk_use->opsreadmax);
        evel_enc_kv_opt_double(jbuf, "diskOpsReadMin", &disk_use->opsreadmin);
        evel_enc_kv_opt_double(jbuf, "diskOpsWriteAvg", &disk_use->opswriteavg);
        evel_enc_kv_opt_double(jbuf, "diskOpsWriteLast", &disk_use->opswritelast);
        evel_enc_kv_opt_double(jbuf, "diskOpsWriteMax", &disk_use->opswritemax);
        evel_enc_kv_opt_double(jbuf, "diskOpsWriteMin", &disk_use->opswritemin);
        evel_enc_kv_opt_double(jbuf, "diskPendingOperationsAvg", &disk_use->pendingopsavg);
        evel_enc_kv_opt_double(jbuf, "diskPendingOperationsLast", &disk_use->pendingopslast);
        evel_enc_kv_opt_double(jbuf, "diskPendingOperationsMax", &disk_use->pendingopsmax);
        evel_enc_kv_opt_double(jbuf, "diskPendingOperationsMin", &disk_use->pendingopsmin);
        evel_enc_kv_opt_double(jbuf, "diskTimeReadAvg", &disk_use->timereadavg);
        evel_enc_kv_opt_double(jbuf, "diskTimeReadLast", &disk_use->timereadlast);
        evel_enc_kv_opt_double(jbuf, "diskTimeReadMax", &disk_use->timereadmax);
        evel_enc_kv_opt_double(jbuf, "diskTimeReadMin", &disk_use->timereadmin);
        evel_enc_kv_opt_double(jbuf, "diskTimeWriteAvg", &disk_use->timewriteavg);
        evel_enc_kv_opt_double(jbuf, "diskTimeWriteLast", &disk_use->timewritelast);
        evel_enc_kv_opt_double(jbuf, "diskTimeWriteMax", &disk_use->timewritemax);
        evel_enc_kv_opt_double(jbuf, "diskTimeWriteMin", &disk_use->timewritemin);
        evel_enc_kv_opt_double(jbuf, "diskBusResets", &disk_use->diskBusResets);
        evel_enc_kv_opt_double(jbuf, "diskCommandsAborted", &disk_use->diskCommandsAborted);
        evel_enc_kv_opt_double(jbuf, "diskTime", &disk_use->diskTime);
        evel_enc_kv_opt_double(jbuf, "diskFlushRequests", &disk_use->diskFlushRequests);
        evel_enc_kv_opt_double(jbuf, "diskFlushTime", &disk_use->diskFlushTime);
        evel_enc_kv_opt_double(jbuf, "diskCommandsAvg", &disk_use->diskCommandsAvg);
        evel_enc_kv_opt_double(jbuf, "diskReadCommandsAvg", &disk_use->diskReadCommandsAvg);
        evel_enc_kv_opt_double(jbuf, "diskWriteCommandsAvg", &disk_use->diskWriteCommandsAvg);
        evel_enc_kv_opt_double(jbuf, "diskTotalReadLatencyAvg", &disk_use->diskTotalReadLatencyAvg);
        evel_enc_kv_opt_double(jbuf, "diskTotalWriteLatencyAvg", &disk_use->diskTotalWriteLatencyAvg);
        evel_enc_kv_opt_double(jbuf, "diskWeightedIoTimeAvg", &disk_use->diskWeightedIoTimeAvg);
        evel_enc_kv_opt_double(jbuf, "diskWeightedIoTimeLast", &disk_use->diskWeightedIoTimeLast);
        evel_enc_kv_opt_double(jbuf, "diskWeightedIoTimeMax", &disk_use->diskWeightedIoTimeMax);
        evel_enc_kv_opt_double(jbuf, "diskWeightedIoTimeMin", &disk_use->diskWeightedIoTimeMin);
        evel_json_close_object(jbuf);
        item_added = true;
      }
      item = dlist_get_next(item);
    }
    evel_json_close_list(jbuf);

    /*************************************************************************/
    /* If we've not written anything, rewind to before we opened the list.   */
    /*************************************************************************/
    if (!item_added)
    {
      evel_json_rewind(jbuf);
    }
  }

  /***************************************************************************/
  /* Filesystem Usage list.                                                  */
  /***************************************************************************/
  evel_json_checkpoint(jbuf);
  if (evel_json_open_opt_named_list(jbuf, "filesystemUsageArray"))
  {
    bool item_added = false;

    item = dlist_get_first(&event->filesystem_usage);
    while (item != NULL)
    {
      fsys_use = (MEASUREMENT_FSYS_USE *) item->item;
      assert(fsys_use != NULL);

      if (!evel_throttle_suppress_nv_pair(jbuf->throttle_spec,
                                          "filesystemUsageArray",
                                          fsys_use->filesystem_name))
      {
        evel_json_open_object(jbuf);
        evel_enc_kv_string(jbuf, "filesystemName", fsys_use->filesystem_name);
        evel_enc_kv_double(
          jbuf, "blockConfigured", fsys_use->block_configured);
        evel_enc_kv_double(jbuf, "blockIops", fsys_use->block_iops);
        evel_enc_kv_double(jbuf, "blockUsed", fsys_use->block_used);
        evel_enc_kv_double(
          jbuf, "ephemeralConfigured", fsys_use->ephemeral_configured);
        evel_enc_kv_double(jbuf, "ephemeralIops", fsys_use->ephemeral_iops);
        evel_enc_kv_double(jbuf, "ephemeralUsed", fsys_use->ephemeral_used);
        evel_json_close_object(jbuf);
        item_added = true;
      }
      item = dlist_get_next(item);
    }
    evel_json_close_list(jbuf);

    /*************************************************************************/
    /* If we've not written anything, rewind to before we opened the list.   */
    /*************************************************************************/
    if (!item_added)
    {
      evel_json_rewind(jbuf);
    }
  }

  /***************************************************************************/
  /* Latency distribution.                                                   */
  /***************************************************************************/
  item = dlist_get_first(&event->latency_distribution);
  if ((item != NULL) &&
      evel_json_open_opt_named_list(jbuf, "latencyDistribution"))
  {
    while (item != NULL)
    {
      bucket = (MEASUREMENT_LATENCY_BUCKET*) item->item;
      assert(bucket != NULL);

      evel_json_open_object(jbuf);
      evel_enc_kv_opt_double(
        jbuf, "lowEndOfLatencyBucket", &bucket->low_end);
      evel_enc_kv_opt_double(
        jbuf, "highEndOfLatencyBucket", &bucket->high_end);
      evel_enc_kv_int(jbuf, "countsInTheBucket", bucket->count);
      evel_json_close_object(jbuf);
      item = dlist_get_next(item);
    }
    evel_json_close_list(jbuf);
  }

  evel_enc_kv_opt_double(
    jbuf, "meanRequestLatency", &event->mean_request_latency);
  evel_enc_kv_opt_double(jbuf, "requestRate", &event->request_rate);

  /***************************************************************************/
  /* NIC Usage TBD Performance array                          */
  /***************************************************************************/
  evel_json_checkpoint(jbuf);
  if (evel_json_open_opt_named_list(jbuf, "nicPerformanceArray"))
  {
    bool item_added = false;

    item = dlist_get_first(&event->nic_performance);
    while (item != NULL)
    {
      nic_performance = (MEASUREMENT_NIC_PERFORMANCE *) item->item;
      assert(nic_performance != NULL);

      if (!evel_throttle_suppress_nv_pair(jbuf->throttle_spec,
                                          "nicPerformanceArray",
                                          nic_performance->nic_id))
      {
        evel_json_open_object(jbuf);

        /*********************************************************************/
        /* Optional fields.                                                  */
        /*********************************************************************/
        state = evel_entity_opt_op_state(&nic_performance->administrativeState);
        if (state != NULL)
        {
          evel_enc_kv_string(jbuf, "administrativeState", state);
        }
        state = evel_entity_opt_op_state(&nic_performance->operationalState);
        if (state != NULL)
        {
          evel_enc_kv_string(jbuf, "operationalState", state);
        }

        evel_enc_kv_opt_double( jbuf,
		 "receivedPercentDiscard", &nic_performance->receivedPercentDiscard);

        evel_enc_kv_opt_double( jbuf,
		 "receivedPercentError", &nic_performance->receivedPercentError);

        evel_enc_kv_opt_double( jbuf,
		 "receivedUtilization", &nic_performance->receivedUtilization);

        evel_enc_kv_opt_double( jbuf,
		 "speed", &nic_performance->speed);

        evel_enc_kv_opt_double( jbuf,
		 "transmittedPercentDiscard", &nic_performance->transmittedPercentDiscard);

        evel_enc_kv_opt_double( jbuf,
		 "transmittedPercentError", &nic_performance->transmittedPercentError);

        evel_enc_kv_opt_double( jbuf,
		 "transmittedUtilization", &nic_performance->transmittedUtilization);

        evel_enc_kv_opt_double( jbuf,
		 "receivedBroadcastPacketsAccumulated", &nic_performance->recvd_bcast_packets_acc);
        evel_enc_kv_opt_double( jbuf,
		 "receivedBroadcastPacketsDelta", &nic_performance->recvd_bcast_packets_delta);
        evel_enc_kv_opt_double( jbuf,
		 "receivedDiscardedPacketsAccumulated", &nic_performance->recvd_discarded_packets_acc);
        evel_enc_kv_opt_double( jbuf,
		 "receivedDiscardedPacketsDelta", &nic_performance->recvd_discarded_packets_delta);
        evel_enc_kv_opt_double( jbuf,
		 "receivedErrorPacketsAccumulated", &nic_performance->recvd_error_packets_acc);
        evel_enc_kv_opt_double( jbuf,
		 "receivedErrorPacketsDelta", &nic_performance->recvd_error_packets_delta);
        evel_enc_kv_opt_double( jbuf,
		 "receivedMulticastPacketsAccumulated", &nic_performance->recvd_mcast_packets_acc);
        evel_enc_kv_opt_double( jbuf,
		 "receivedMulticastPacketsDelta", &nic_performance->recvd_mcast_packets_delta);
        evel_enc_kv_opt_double( jbuf,
		 "receivedOctetsAccumulated", &nic_performance->recvd_octets_acc);
        evel_enc_kv_opt_double( jbuf,
		 "receivedOctetsDelta", &nic_performance->recvd_octets_delta);
        evel_enc_kv_opt_double( jbuf,
		 "receivedTotalPacketsAccumulated", &nic_performance->recvd_total_packets_acc);
        evel_enc_kv_opt_double( jbuf,
		 "receivedTotalPacketsDelta", &nic_performance->recvd_total_packets_delta);
        evel_enc_kv_opt_double( jbuf,
		 "receivedUnicastPacketsAccumulated", &nic_performance->recvd_ucast_packets_acc);
        evel_enc_kv_opt_double( jbuf,
		 "receivedUnicastPacketsDelta", &nic_performance->recvd_ucast_packets_delta);
        evel_enc_kv_opt_double( jbuf,
		 "transmittedBroadcastPacketsAccumulated", &nic_performance->tx_bcast_packets_acc);
        evel_enc_kv_opt_double( jbuf,
		 "transmittedBroadcastPacketsDelta", &nic_performance->tx_bcast_packets_delta);
        evel_enc_kv_opt_double( jbuf,
		 "transmittedDiscardedPacketsAccumulated", &nic_performance->tx_discarded_packets_acc);
        evel_enc_kv_opt_double( jbuf,
		 "transmittedDiscardedPacketsDelta", &nic_performance->tx_discarded_packets_delta);
        evel_enc_kv_opt_double( jbuf,
		 "transmittedErrorPacketsAccumulated", &nic_performance->tx_error_packets_acc);
        evel_enc_kv_opt_double( jbuf,
		 "transmittedErrorPacketsDelta", &nic_performance->tx_error_packets_delta);
        evel_enc_kv_opt_double( jbuf,
		 "transmittedMulticastPacketsAccumulated", &nic_performance->tx_mcast_packets_acc);
        evel_enc_kv_opt_double( jbuf,
		 "transmittedMulticastPacketsDelta", &nic_performance->tx_mcast_packets_delta);
        evel_enc_kv_opt_double( jbuf,
		 "transmittedOctetsAccumulated", &nic_performance->tx_octets_acc);
        evel_enc_kv_opt_double( jbuf,
		 "transmittedOctetsDelta", &nic_performance->tx_octets_delta);
        evel_enc_kv_opt_double( jbuf,
		 "transmittedTotalPacketsAccumulated", &nic_performance->tx_total_packets_acc);
        evel_enc_kv_opt_double( jbuf,
		 "transmittedTotalPacketsDelta", &nic_performance->tx_total_packets_delta);
        evel_enc_kv_opt_double( jbuf,
		 "transmittedUnicastPacketsAccumulated", &nic_performance->tx_ucast_packets_acc);
        evel_enc_kv_opt_double( jbuf,
		 "transmittedUnicastPacketsDelta", &nic_performance->tx_ucast_packets_delta);

        /*********************************************************************/
        /* Mandatory fields.                                                 */
        /*********************************************************************/
        evel_enc_kv_string(jbuf, "valuesAreSuspect", nic_performance->valuesaresuspect);
        evel_enc_kv_string(jbuf, "nicIdentifier", nic_performance->nic_id);

        evel_json_close_object(jbuf);
        item_added = true;
      }
      item = dlist_get_next(item);
    }

    evel_json_close_list(jbuf);

    /*************************************************************************/
    /* If we've not written anything, rewind to before we opened the list.   */
    /*************************************************************************/
    if (!item_added)
    {
      evel_json_rewind(jbuf);
    }
  }


  /***************************************************************************/
  /* Memory Use list.                                                        */
  /***************************************************************************/
  evel_json_checkpoint(jbuf);
  if (evel_json_open_opt_named_list(jbuf, "memoryUsageArray"))
  {
    bool item_added = false;

    item = dlist_get_first(&event->mem_usage);
    while (item != NULL)
    {
      mem_use = (MEASUREMENT_MEM_USE*) item->item;
      assert(mem_use != NULL);

      if (!evel_throttle_suppress_nv_pair(jbuf->throttle_spec,
                                          "memoryUsageArray",
                                          mem_use->vmid))
      {
        evel_json_open_object(jbuf);
        evel_enc_kv_opt_double(jbuf, "memoryBuffered", &mem_use->membuffsz);
        evel_enc_kv_opt_double(jbuf, "memoryCached", &mem_use->memcache);
        evel_enc_kv_opt_double(jbuf, "memoryConfigured", &mem_use->memconfig);
        evel_enc_kv_double(jbuf, "memoryFree", mem_use->memfree);
        evel_enc_kv_opt_double(jbuf, "memorySlabRecl", &mem_use->slabrecl);
        evel_enc_kv_opt_double(jbuf, "memorySlabUnrecl", &mem_use->slabunrecl);
        evel_enc_kv_double(jbuf, "memoryUsed", mem_use->memused);
        evel_enc_kv_string(jbuf, "vmIdentifier", mem_use->vmid);
        evel_enc_kv_opt_double(jbuf, "memoryDemand", &mem_use->memoryDemand);
        evel_enc_kv_opt_double(jbuf, "memoryLatencyAvg", &mem_use->memoryLatencyAvg);
        evel_enc_kv_opt_double(jbuf, "memorySharedAvg", &mem_use->memorySharedAvg);
        evel_enc_kv_opt_double(jbuf, "memorySwapInAvg", &mem_use->memorySwapInAvg);
        evel_enc_kv_opt_double(jbuf, "memorySwapInRateAvg", &mem_use->memorySwapInRateAvg);
        evel_enc_kv_opt_double(jbuf, "memorySwapOutAvg", &mem_use->memorySwapOutAvg);
        evel_enc_kv_opt_double(jbuf, "memorySwapOutRateAvg", &mem_use->memorySwapOutRateAvg);
        evel_enc_kv_opt_double(jbuf, "memorySwapUsedAvg", &mem_use->memorySwapUsedAvg);
        evel_enc_kv_opt_double(jbuf, "percentMemoryUsage", &mem_use->percentMemoryUsage);

        evel_json_close_object(jbuf);
        item_added = true;
      }
      item = dlist_get_next(item);
    }
    evel_json_close_list(jbuf);

    /*************************************************************************/
    /* If we've not written anything, rewind to before we opened the list.   */
    /*************************************************************************/
    if (!item_added)
    {
      evel_json_rewind(jbuf);
    }
  }


  evel_enc_kv_opt_int(
    jbuf, "numberOfMediaPortsInUse", &event->media_ports_in_use);
  evel_enc_kv_opt_int(
    jbuf, "nfcScalingMetric", &event->vnfc_scaling_metric);

  /***************************************************************************/
  /* Feature Utilization list.                                               */
  /***************************************************************************/
  evel_json_checkpoint(jbuf);
  ht = event->feature_usage;
  if( ht != NULL )
  {
    bool added = false;
    if( ht->size > 0)
    {
      evel_json_checkpoint(jbuf);
      if (evel_json_open_opt_named_object(jbuf, "featureUsageArray"))
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
            EVEL_DEBUG("Encoding feature usage %s %s",(char *) (entry->key), entry->value);
            if (!evel_throttle_suppress_nv_pair(jbuf->throttle_spec,
                                              "featureUsageArray",
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

  /***************************************************************************/
  /* Codec Utilization list.                                                 */
  /***************************************************************************/
  evel_json_checkpoint(jbuf);
  if (evel_json_open_opt_named_list(jbuf, "codecUsageArray"))
  {
    bool item_added = false;

    item = dlist_get_first(&event->codec_usage);
    while (item != NULL)
    {
      codec_use = (MEASUREMENT_CODEC_USE*) item->item;
      assert(codec_use != NULL);

      if (!evel_throttle_suppress_nv_pair(jbuf->throttle_spec,
                                          "codecUsageArray",
                                          codec_use->codec_id))
      {
        evel_json_open_object(jbuf);
        evel_enc_kv_string(jbuf, "codecIdentifier", codec_use->codec_id);
        evel_enc_kv_int(jbuf, "numberInUse", codec_use->number_in_use);
        evel_json_close_object(jbuf);
        item_added = true;
      }
      item = dlist_get_next(item);
    }
    evel_json_close_list(jbuf);

    /*************************************************************************/
    /* If we've not written anything, rewind to before we opened the list.   */
    /*************************************************************************/
    if (!item_added)
    {
      evel_json_rewind(jbuf);
    }
  }

  /***************************************************************************/
  /* Additional Measurement Groups list.                                     */
  /***************************************************************************/
  /***************************************************************************/
  /* Checkpoint, so that we can wind back if all fields are suppressed.      */
  /***************************************************************************/
  evel_json_checkpoint(jbuf);
  if (evel_json_open_opt_named_list(jbuf, "additionalMeasurements"))
  {
    bool added_array = false;

    dlist_item = dlist_get_first(&event->additional_measurements);
    while (dlist_item != NULL)
    {
      bool added = false;
      ht = (HASHTABLE_T *) dlist_item->item;
      assert(ht != NULL);

      if((ht->size > 0) && (ht-> n > 0))
      {
        evel_json_checkpoint(jbuf);
        evel_json_open_object(jbuf);
        evel_enc_kv_string(jbuf, "name", ht->hmName);

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
              EVEL_DEBUG("Encoding additional measurements %s %s",(char *) (entry->key), entry->value);
              if (!evel_throttle_suppress_nv_pair(jbuf->throttle_spec,
                                                ht->hmName,
                                                entry->key))
              {

                //evel_json_open_object(jbuf);
                evel_enc_kv_string(jbuf, entry->key, entry->value);
                //evel_json_close_object(jbuf);
                added = true;
                added_array = true;
              }
              entry = entry->next;
            }
          }
          evel_json_close_object(jbuf);
          if (!added)
          {
            evel_json_rewind(jbuf);
          }
        }
        evel_json_close_object(jbuf);
      }
      dlist_item = dlist_get_next(dlist_item);
    }
    evel_json_close_list(jbuf);

    if (!added_array)
    {
      evel_json_rewind(jbuf);
    }
  }

  /***************************************************************************/
  /* Although optional, we always generate the version.  Note that this      */
  /* closes the object, too.                                                 */
  /***************************************************************************/
  evel_enc_version(jbuf,
                   "measurementFieldsVersion",
                   event->major_version,
                   event->minor_version);
  evel_json_close_object(jbuf);

  EVEL_EXIT();
}
void evel_measurement_free_ipmi_processor(MEASUREMENT_IPMI_PROCESSOR * ipmi_processor)
{

  MEASUREMENT_IPMI_PROCESSOR_DIMMAGG_THERM * proc_dimm_therm = NULL;

  EVEL_ENTER();

  free(ipmi_processor->processorIdentifier);

  proc_dimm_therm = dlist_pop_last(&ipmi_processor->processorDimmAggregateThermalMargin);
  while (proc_dimm_therm != NULL)
  {
    EVEL_DEBUG("Freeing IPMI proc dimm therm Info (%s)", proc_dimm_therm->MarginIdentifier);
    free(proc_dimm_therm->MarginIdentifier);
    free(proc_dimm_therm);
    proc_dimm_therm = dlist_pop_last(&ipmi_processor->processorDimmAggregateThermalMargin);
  }

  EVEL_EXIT();
}

void  evel_measurement_free_ipmi(MEASUREMENT_IPMI * ipmi)
{
  MEASUREMENT_IPMI_BB_TEMPERATURE * bb_temp = NULL;
  MEASUREMENT_IPMI_BB_VOLTAGE * bb_volt = NULL;
  MEASUREMENT_IPMI_BATTERY * ipmi_battery = NULL;
  MEASUREMENT_IPMI_FAN * ipmi_fan = NULL;
  MEASUREMENT_IPMI_HSBP * ipmi_hsbp = NULL;
  MEASUREMENT_IPMI_GLOBAL_AGG_TEMP_MARGIN * ipmi_tempMargin = NULL;
  MEASUREMENT_IPMI_NIC * ipmi_nic = NULL;
  MEASUREMENT_IPMI_POWER_SUPPLY * ipmi_power = NULL;
  MEASUREMENT_IPMI_PROCESSOR * ipmi_processor = NULL;

  EVEL_ENTER();

  bb_temp = dlist_pop_last(&ipmi->ipmi_base_board_temparature);
  while (bb_temp != NULL)
  {
    EVEL_DEBUG("Freeing base board temp Info (%s)", bb_temp->BBTemperatureID);
    free(bb_temp->BBTemperatureID);
    free(bb_temp);
    bb_temp = dlist_pop_last(&ipmi->ipmi_base_board_temparature);
  }

  bb_volt = dlist_pop_last(&ipmi->ipmi_base_board_voltage);
  while (bb_volt != NULL)
  {
    EVEL_DEBUG("Freeing IPMI FAN Info (%s)", bb_volt->BBVoltageRegID);
    free(bb_volt->BBVoltageRegID);
    free(bb_volt);
    bb_volt = dlist_pop_last(&ipmi->ipmi_base_board_voltage);
  }

  ipmi_battery = dlist_pop_last(&ipmi->ipmi_battery);
  while (ipmi_battery != NULL)
  {
    EVEL_DEBUG("Freeing IPMI Battery Info (%s)", ipmi_battery->batteryIdentifier);
    free(ipmi_battery->batteryIdentifier);
    free(ipmi_battery);
    ipmi_battery = dlist_pop_last(&ipmi->ipmi_battery);
  }

  ipmi_fan = dlist_pop_last(&ipmi->ipmi_fan);
  while (ipmi_fan != NULL)
  {
    EVEL_DEBUG("Freeing IPMI FAN Info (%s)", ipmi_fan->fanIdentifier);
    free(ipmi_fan->fanIdentifier);
    free(ipmi_fan);
    ipmi_fan = dlist_pop_last(&ipmi->ipmi_fan);
  }

  ipmi_hsbp = dlist_pop_last(&ipmi->ipmi_hsbp);
  while (ipmi_hsbp != NULL)
  {
    EVEL_DEBUG("Freeing IPMI HSBP Info (%s)", ipmi_hsbp->hsbpIdentifier);
    free(ipmi_hsbp->hsbpIdentifier);
    free(ipmi_hsbp);
    ipmi_hsbp = dlist_pop_last(&ipmi->ipmi_hsbp);
  }

  ipmi_tempMargin = dlist_pop_last(&ipmi->ipmi_global_agg_temp_margin);
  while (ipmi_tempMargin != NULL)
  {
    EVEL_DEBUG("Freeing IPMI Global AGG Temp margin info (%s)", ipmi_tempMargin->globalAggTempID);
    free(ipmi_tempMargin->globalAggTempID);
    free(ipmi_tempMargin);
    ipmi_tempMargin = dlist_pop_last(&ipmi->ipmi_global_agg_temp_margin);
  }

  ipmi_nic = dlist_pop_last(&ipmi->ipmi_nic);
  while (ipmi_nic != NULL)
  {
    EVEL_DEBUG("Freeing IPMI NIC Info (%s)", ipmi_nic->nicIdentifier);
    free(ipmi_nic->nicIdentifier);
    free(ipmi_nic);
    ipmi_nic = dlist_pop_last(&ipmi->ipmi_nic);
  }

  ipmi_power = dlist_pop_last(&ipmi->ipmi_power);
  while (ipmi_power != NULL)
  {
    EVEL_DEBUG("Freeing IPMI Power Info (%s)", ipmi_power->powerSupplyIdentifier);
    free(ipmi_power->powerSupplyIdentifier);
    free(ipmi_power);
    ipmi_power = dlist_pop_last(&ipmi->ipmi_power);
  }

  ipmi_processor = dlist_pop_last(&ipmi->ipmi_processor);
  while (ipmi_processor != NULL)
  {
    EVEL_DEBUG("Freeing IPMI Processor Info (%s)", ipmi_processor->processorIdentifier);
    evel_measurement_free_ipmi_processor(ipmi_processor);
    free(ipmi_processor);
    ipmi_processor = dlist_pop_last(&ipmi->ipmi_processor);
  }

  EVEL_EXIT();
}

/**************************************************************************//**
 * Free a Measurement.
 *
 * Free off the Measurement supplied.  Will free all the contained allocated
 * memory.
 *
 * @note It does not free the Measurement itself, since that may be part of a
 * larger structure.
 *****************************************************************************/
void evel_free_measurement(EVENT_MEASUREMENT * event)
{
  MEASUREMENT_HUGE_PAGE * huge_page = NULL;
  MEASUREMENT_CPU_USE * cpu_use = NULL;
  MEASUREMENT_DISK_USE * disk_use = NULL;
  MEASUREMENT_FSYS_USE * fsys_use = NULL;
  MEASUREMENT_LATENCY_BUCKET * bucket = NULL;
  MEASUREMENT_MEM_USE * mem_use = NULL;
  MEASUREMENT_NIC_PERFORMANCE * nic_performance = NULL;
  MEASUREMENT_CODEC_USE * codec_use = NULL;
  MEASUREMENT_LOAD * load = NULL;
  MEASUREMENT_PROCESS_STATS * proc_stat = NULL;
  MEASUREMENT_IPMI * ipmi = NULL;
  MACHINE_CHECK_EXCEPTION * machine_check = NULL;
  EVEL_JSON_OBJECT * jsonobjp = NULL;
  HASHTABLE_T *ht;

  EVEL_ENTER();

  /***************************************************************************/
  /* Check preconditions.  As an internal API we don't allow freeing NULL    */
  /* events as we do on the public API.                                      */
  /***************************************************************************/
  assert(event != NULL);
  assert(event->header.event_domain == EVEL_DOMAIN_MEASUREMENT);

  /***************************************************************************/
  /* Free all internal strings then the header itself.                       */
  /***************************************************************************/
  ht = event->additional_info;
  if( ht != NULL )
  {
     ht_destroy(ht);
  }

  jsonobjp = dlist_pop_last(&event->additional_objects);
  while (jsonobjp != NULL)
  {
    EVEL_DEBUG("Freeing jsonObject %p",jsonobjp);
    evel_free_jsonobject( jsonobjp );
    jsonobjp = dlist_pop_last(&event->additional_objects);
  }

  cpu_use = dlist_pop_last(&event->cpu_usage);
  while (cpu_use != NULL)
  {
    EVEL_DEBUG("Freeing CPU use Info (%s)", cpu_use->id);
    free(cpu_use->id);
    free(cpu_use);
    cpu_use = dlist_pop_last(&event->cpu_usage);
  }

  disk_use = dlist_pop_last(&event->disk_usage);
  while (disk_use != NULL)
  {
    EVEL_DEBUG("Freeing Disk use Info (%s)", disk_use->id);
    free(disk_use->id);
    free(disk_use);
    disk_use = dlist_pop_last(&event->disk_usage);
  }

  mem_use = dlist_pop_last(&event->mem_usage);
  while (mem_use != NULL)
  {
    EVEL_DEBUG("Freeing Memory use Info - (%s)", mem_use->vmid);
    free(mem_use->vmid);
    free(mem_use);
    mem_use = dlist_pop_last(&event->mem_usage);
  }

  fsys_use = dlist_pop_last(&event->filesystem_usage);
  while (fsys_use != NULL)
  {
    EVEL_DEBUG("Freeing Filesystem Use info (%s)", fsys_use->filesystem_name);
    free(fsys_use->filesystem_name);
    free(fsys_use);
    fsys_use = dlist_pop_last(&event->filesystem_usage);
  }

  bucket = dlist_pop_last(&event->latency_distribution);
  while (bucket != NULL)
  {
    EVEL_DEBUG("Freeing Latency Bucket");
    free(bucket);
    bucket = dlist_pop_last(&event->latency_distribution);
  }

  nic_performance = dlist_pop_last(&event->nic_performance);
  while (nic_performance != NULL)
  {
    EVEL_DEBUG("Freeing NIC performance Info (%s)", nic_performance->nic_id);
    evel_measurement_free_nic_performance(nic_performance);
    free(nic_performance);
    nic_performance = dlist_pop_last(&event->nic_performance);
  }

  ipmi = dlist_pop_last(&event->ipmis);
  while (ipmi != NULL)
  {
    EVEL_DEBUG("Freeing IPMI");
    evel_measurement_free_ipmi(ipmi);
    free(ipmi);
    ipmi = dlist_pop_last(&event->ipmis);
  }

  codec_use = dlist_pop_last(&event->codec_usage);
  while (codec_use != NULL)
  {
    EVEL_DEBUG("Freeing Codec use Info (%s)", codec_use->codec_id);
    free(codec_use->codec_id);
    free(codec_use);
    codec_use = dlist_pop_last(&event->codec_usage);
  }

  proc_stat = dlist_pop_last(&event->process_stats);
  while (proc_stat != NULL)
  {
    EVEL_DEBUG("Freeing Process Stats Info (%s)", proc_stat->processIdentifier);
    free(proc_stat->processIdentifier);
    free(proc_stat);
    proc_stat = dlist_pop_last(&event->process_stats);
  }

  load = dlist_pop_last(&event->loads);
  while (load != NULL)
  {
    EVEL_DEBUG("Freeing load Info");
    free(load);
    load = dlist_pop_last(&event->loads);
  }

  ht = event->feature_usage;
  if( ht != NULL )
  {
     ht_destroy(ht);
  }

  huge_page = dlist_pop_last(&event->huge_pages);
  while (huge_page != NULL)
  {
    EVEL_DEBUG("Freeing huge page id (%s)", huge_page->hugePagesIdentifier);
    free(huge_page->hugePagesIdentifier);
    free(huge_page);
    huge_page = dlist_pop_last(&event->huge_pages);
  }

  machine_check = dlist_pop_last(&event->machine_check_exception);
  while (machine_check != NULL)
  {
    EVEL_DEBUG("Freeing machine check exception id (%s)", machine_check->process_id);

    free(machine_check->process_id);
    free(machine_check);
    machine_check = dlist_pop_last(&event->machine_check_exception);
  }

  ht = dlist_pop_last(&event->additional_measurements);
  while (ht != NULL)
  {
    EVEL_DEBUG("Freeing measurement additional_measurements %s", ht->hmName);
    ht_destroy(ht);
    ht = dlist_pop_last(&event->additional_measurements);
  }

  evel_free_header(&event->header);

  EVEL_EXIT();
}

