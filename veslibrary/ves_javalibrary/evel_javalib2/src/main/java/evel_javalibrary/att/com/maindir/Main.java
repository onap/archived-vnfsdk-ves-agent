
package evel_javalibrary.att.com.maindir;

/**************************************************************************//**
 * @file
 * Sample Test Agent for EVEL library
 *
 * This file implements the Sample Agent which is intended to provide a
 * simple wrapper around the complexity of AT&T's Vendor Event Listener API so
 * that VNFs can use it without worrying about details of the API transport.
 * It also shows how events can be formatted with data for POST
 *
 * License
 * -------
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
 *****************************************************************************/



import evel_javalibrary.att.com.*;
import evel_javalibrary.att.com.EvelFault.EVEL_SEVERITIES;
import evel_javalibrary.att.com.EvelFault.EVEL_SOURCE_TYPES;
import evel_javalibrary.att.com.EvelFault.EVEL_VF_STATUSES;
import evel_javalibrary.att.com.EvelMobileFlow.MOBILE_GTP_PER_FLOW_METRICS;
import evel_javalibrary.att.com.EvelScalingMeasurement.MACHINE_CHECK_EXCEPTION;
import evel_javalibrary.att.com.EvelScalingMeasurement.MEASUREMENT_CODEC_USE;
import evel_javalibrary.att.com.EvelScalingMeasurement.MEASUREMENT_CPU_USE;
import evel_javalibrary.att.com.EvelScalingMeasurement.MEASUREMENT_DISK_USE;
import evel_javalibrary.att.com.EvelScalingMeasurement.MEASUREMENT_FEATURE_USE;
import evel_javalibrary.att.com.EvelScalingMeasurement.MEASUREMENT_FSYS_USE;
import evel_javalibrary.att.com.EvelScalingMeasurement.MEASUREMENT_HUGE_PAGE;
import evel_javalibrary.att.com.EvelScalingMeasurement.MEASUREMENT_IPMI;
import evel_javalibrary.att.com.EvelScalingMeasurement.MEASUREMENT_LATENCY_BUCKET;
import evel_javalibrary.att.com.EvelScalingMeasurement.MEASUREMENT_LOAD;
import evel_javalibrary.att.com.EvelScalingMeasurement.MEASUREMENT_MEM_USE;
import evel_javalibrary.att.com.EvelScalingMeasurement.MEASUREMENT_NIC_PERFORMANCE;
import evel_javalibrary.att.com.EvelScalingMeasurement.MEASUREMENT_PROCESS_STATS;
import evel_javalibrary.att.com.EvelScalingMeasurement.MEASUREMENT_IPMI.MEASUREMENT_IPMI_PROCESSOR;
import evel_javalibrary.att.com.EvelSyslog.EVEL_SYSLOG_FACILITIES;

import org.apache.log4j.Level;

import java.io.*;
import java.text.SimpleDateFormat;
import java.util.Date;

public class Main
{

    public static void main(String[] args)
    {

        try{
            AgentMain.evel_initialize("http://127.0.0.1",30000,
                    //  "http://1.2.3.4", 8080,
                    //"/vendor_event_listener","/example_vnf",
                    null,null,
                    "will",
                    "pill",
                    null, null, null,
                    "http://127.0.0.1",30001, "will",
                    "pill",
                    //"/home/gokul/newwk/demo/vnfs/VES5.0/evel/sslcerts2/my-keystore.jks", "changeit", "changeit",
                    Level.TRACE); 
        } catch( Exception e )
        {            
        }
        for(int i= 0; i < 30; i++) //srikanth no need for forloop , send only once.
        {
        	
            EvelHeader header  = EvelHeader.evel_new_heartbeat("Hearbeat_vAFX","vmname_ip");
            header.evel_nfnamingcode_set("vVNF");
            header.evel_nfcnamingcode_set("vVNF");
            header.evel_timeZoneOffset_set("UTC+5:30");
            
            
            
            
      //      AgentMain.evel_post_event(header);
            try {
                Thread.sleep(1000);
            } catch( Exception e )
            {
                
            }
            
            
            
            EvelBatch be = new EvelBatch(); 
            
            
            EvelFault flt  = new EvelFault("Fault_vVNF", "vmname_ip",
                    "My alaram condition", "It broke very badly",
                    EvelHeader.PRIORITIES.EVEL_PRIORITY_HIGH,
                    EVEL_SEVERITIES.EVEL_SEVERITY_MAJOR,
                    EVEL_SOURCE_TYPES.EVEL_SOURCE_CARD,
                    EVEL_VF_STATUSES.EVEL_VF_STATUS_ACTIVE);
            flt.evel_fault_addl_info_add("name1", "value1");
            flt.evel_fault_addl_info_add("name2", "value2");
            flt.evel_fault_interface_set("My Interface Card");
            flt.evel_fault_category_set("link");
            
            
          //  be.addEvent(flt);
           AgentMain.evel_post_event(flt);

            

            
 /*
  * Fault is End
  * */           
            
            EvelStateChange stc  = new EvelStateChange("StateChange_vVNF", "vmname_ip",
                    EvelStateChange.EVEL_ENTITY_STATE.EVEL_ENTITY_STATE_IN_SERVICE,
                    EvelStateChange.EVEL_ENTITY_STATE.EVEL_ENTITY_STATE_OUT_OF_SERVICE,"bgp");
            stc.evel_statechange_addl_info_add("bgpa", "fail");
            stc.evel_statechange_addl_info_add("bgpb", "fail");
         
            
            

          //  be.addEvent(stc);
          AgentMain.evel_post_event(stc);
 
 /*  
  * State Change End
  * */           
            
            
          EvelNotification notification = new EvelNotification("Notification_vVNF", "vmname_ip","change_identifier", "configuration changed");
          notification.evel_notification_add_newState_set("maintainance");
          notification.evel_notification_add_oldState_set("out of Service");
          notification.evel_notification_add_changeContact_set("ChangeContact");
          notification.evel_notification_addl_info_add("name1", "value1");
          notification.evel_notification_addl_info_add("name4", "value5");
          
          notification.evel_notification_add_namedarray("hmNam1", "hmName1", "hmNmae2");
          
          notification.evel_notification_add_stateInterface_set("StateChange");
          
        //  be.addEvent(notification);
      
           AgentMain.evel_post_event(notification);  
          
          
/*  
* notification Change End
* */             
            

            EvelScalingMeasurement sm  = new EvelScalingMeasurement(10.0,"Measurements_vVNF", "vmname_ip");
       //     sm.evel_measurement_myerrors_set(10,20,30,40);
            
            sm.evel_measurement_concurrent_sessions_set(5);
            sm.evel_measurement_config_entities_set(9);
            sm.evel_measurement_mean_req_lat_set(13.6);
            sm.evel_measurement_request_rate_set(1234);
            sm.evel_measurement_vnfc_scaling_metric_set(35);
            sm.evel_measurement_media_port_use_set(20);
            
            MEASUREMENT_CPU_USE cpuuse = sm.evel_measurement_new_cpu_use_add("cpu2", 10.0);
            sm.evel_measurement_cpu_use_cpuCapacityContention_set(cpuuse, 11.3);
            sm.evel_measurement_cpu_use_cpuDeamandAvg_set(cpuuse, 11.4);
            sm.evel_measurement_cpu_use_cpuDeamandPct_set(cpuuse, 11.6);
            sm.evel_measurement_cpu_use_cpuDeamandMhz_set(cpuuse, 11.8);
            sm.evel_measurement_cpu_use_cpuLatencyAvg_set(cpuuse, 11.9);
            sm.evel_measurement_cpu_use_cpuOverheadAvg_set(cpuuse, 12.2);
            sm.evel_measurement_cpu_use_cpuSwapWaitTime_set(cpuuse, 13.2);
            sm.evel_measurement_cpu_use_idle_set(cpuuse, 14.2);
            sm.evel_measurement_cpu_use_interrupt_set(cpuuse, 15.2);
            sm.evel_measurement_cpu_use_nice_set(cpuuse, 16.2);
            sm.evel_measurement_cpu_use_softirq_set(cpuuse, 17.2);
            sm.evel_measurement_cpu_use_steal_set(cpuuse, 18.2);
            sm.evel_measurement_cpu_use_system_set(cpuuse, 19.2);
            sm.evel_measurement_cpu_use_usageuser_set(cpuuse, 18.9);
            sm.evel_measurement_cpu_use_wait_set(cpuuse, 19.9);
            
            
            MEASUREMENT_DISK_USE diskuse = sm.evel_measurement_new_disk_use_add("100");
            sm.evel_measurement_disk_use_diskWeightedIoTimeAvg_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_diskWeightedIoTimeLast_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_diskWeightedIoTimeMax_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_diskWeightedIoTimeMin_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_diskBusResets_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_diskCommandsAborted_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_diskCommandsAvg_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_diskFlushRequests_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_diskReadCommandsAvg_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_diskFlushTime_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_diskTime_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_diskTotalReadLatencyAvg_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_diskTotalWriteLatencyAvg_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_diskWriteCommandsAvg_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_iotimeavg_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_iotimelast_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_iotimemax_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_iotimemin_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_mergereadavg_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_mergereadlast_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_mergereadmax_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_mergereadmin_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_mergewritelast_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_mergewritemax_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_mergewritemin_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_mergewriteavg_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_octetsreadavg_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_octetsreadlast_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_octetsreadmax_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_octetsreadmin_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_octetswriteavg_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_octetswritelast_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_octetswritemax_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_octetswritemin_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_opsreadavg_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_opsreadlast_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_opsreadmax_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_opsreadmin_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_opswriteavg_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_opswritelast_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_opswritemax_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_opswritemin_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_pendingopsavg_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_pendingopslast_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_pendingopsmax_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_pendingopsmin_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_timereadavg_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_timereadlast_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_timereadmax_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_timereadmin_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_timewriteavg_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_timewritelast_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_timewritemax_set(diskuse, 10.1);
            sm.evel_measurement_disk_use_timewritemin_set(diskuse, 10.1);
       
            MEASUREMENT_FEATURE_USE featureuse = sm.evel_measurement_feature_use_add("features", 100);
            
            MEASUREMENT_HUGE_PAGE husePage= sm.evel_measurement_new_huge_page_add("HUGEPage1", 100000);
            sm.evel_measurement_huge_page_bytesFree_set(husePage, 1100000);
            sm.evel_measurement_huge_page_percentFree_set(husePage, 1000);
            sm.evel_measurement_huge_page_percentUsed_set(husePage, 2000);
            sm.evel_measurement_huge_page_vmPageNumberFree_set(husePage, 3000);
            sm.evel_measurement_huge_page_vmPageNumberUsed_set(husePage, 4000);
            
       
            MEASUREMENT_MEM_USE memuse = sm.evel_measurement_new_mem_use_add("memuse", 100.0);
            sm.evel_measurement_mem_use_memcache_set(memuse, 51.1);
            sm.evel_measurement_mem_use_memconfig_set(memuse, 51.1);
            sm.evel_measurement_mem_use_memfree_set(memuse, 51.1);
            sm.evel_measurement_mem_use_slab_reclaimed_set(memuse, 51.1);
            sm.evel_measurement_mem_use_slab_unreclaimable_set(memuse, 51.1);
            sm.evel_measurement_mem_use_usedup_set(memuse, 51.1);
            
            sm.evel_measurement_mem_use_memoryDemand_set(memuse, 51.1);
            sm.evel_measurement_mem_use_memoryLatencyAvg_set(memuse, 51.1);
            sm.evel_measurement_mem_use_memorySharedAvg_set(memuse, 51.1);
            sm.evel_measurement_mem_use_memorySwapInAvg_set(memuse, 51.1);
            sm.evel_measurement_mem_use_memorySwapInRateAvg_set(memuse, 51.1);
            sm.evel_measurement_mem_use_memorySwapOutAvg_set(memuse, 51.1);
            sm.evel_measurement_mem_use_memorySwapOutRateAvg_set(memuse, 51.1);
            sm.evel_measurement_mem_use_memorySwapUsedAvg_set(memuse, 51.1);
            
            
            
            
            MEASUREMENT_LATENCY_BUCKET latecy = sm.evel_measurement_latency_add(10000, 2000, 3000);
            sm.evel_meas_latency_bucket_low_end_set(latecy, 10);
            sm.evel_meas_latency_bucket_high_end_set(latecy, 20);
            
            MEASUREMENT_FSYS_USE fileuse = sm.evel_measurement_fsys_use_add("FileSystem", 10.0, 2.8, 2.4, 3.3, 5.5, 9.0);
           
            
          MEASUREMENT_NIC_PERFORMANCE vnic = sm.evel_measurement_new_vnic_performance("VNicIdentifiew", "false");
          
          sm.evel_vnic_performance_rx_bcast_pkt_acc_set(vnic, 1000.0);
          sm.evel_vnic_performance_rx_bcast_pkt_delta_set(vnic, 200.0);
          sm.evel_vnic_performance_rx_discard_pkt_acc_set(vnic, 300.0);
          sm.evel_vnic_performance_rx_discard_pkt_delta_set(vnic, 400.0);
          sm.evel_vnic_performance_rx_error_pkt_acc_set(vnic, 500.0);
          sm.evel_vnic_performance_rx_error_pkt_delta_set(vnic, 600.0);
          sm.evel_vnic_performance_rx_mcast_pkt_acc_set(vnic, 700.0);
          sm.evel_vnic_performance_rx_mcast_pkt_delta_set(vnic, 800.0);
          sm.evel_vnic_performance_rx_octets_acc_set(vnic, 900.0);
          sm.evel_vnic_performance_rx_octets_delta_set(vnic, 3400.0);
          
          sm.evel_vnic_performance_rx_total_pkt_acc_set(vnic, 67.9);
          sm.evel_vnic_performance_rx_total_pkt_delta_set(vnic, 37.8);
          sm.evel_vnic_performance_rx_ucast_pkt_acc_set(vnic, 234.7);
          sm.evel_vnic_performance_rx_ucast_pkt_delta_set(vnic, 457.9);
          sm.evel_vnic_performance_tx_bcast_pkt_acc_set(vnic, 76.4);
          sm.evel_vnic_performance_tx_bcast_pkt_delta_set(vnic, 65.9);
          sm.evel_vnic_performance_tx_discarded_pkt_acc_set(vnic, 76.87);
          sm.evel_vnic_performance_tx_discarded_pkt_delta_set(vnic, 45.98);
          sm.evel_vnic_performance_tx_error_pkt_acc_set(vnic, 54.98);
          sm.evel_vnic_performance_tx_error_pkt_delta_set(vnic, 22.90);
          sm.evel_vnic_performance_tx_mcast_pkt_acc_set(vnic, 22.8);
          sm.evel_vnic_performance_tx_mcast_pkt_delta_set(vnic, 22.8);
          sm.evel_vnic_performance_tx_octets_acc_set(vnic, 33.3);
          sm.evel_vnic_performance_tx_octets_delta_set(vnic, 33.9);
          sm.evel_vnic_performance_tx_total_pkt_acc_set(vnic, 23.9);
          sm.evel_vnic_performance_tx_total_pkt_delta_set(vnic, 65.9);
          sm.evel_vnic_performance_tx_ucast_pkt_acc_set(vnic, 23.9);
          sm.evel_vnic_performance_tx_ucast_pkt_delta_set(vnic, 44.9);
          sm.evel_vnic_performance_administrativeState_set(vnic, "inService");
          sm.evel_vnic_performance_operationalState_set(vnic, "inService");
          sm.evel_vnic_performance_receivedPercentDiscard_set(vnic, 12.0);
          sm.evel_vnic_performance_receivedPercentError_set(vnic, 13.0);
          sm.evel_vnic_performance_receivedUtilization_set(vnic, 14.01);
          sm.evel_vnic_performance_speed_set(vnic, 12.99);
          sm.evel_vnic_performance_transmittedPercentDiscard_set(vnic, 98.9);
          sm.evel_vnic_performance_transmittedPercentError_set(vnic, 23.9);
          sm.evel_vnic_performance_transmittedUtilization_set(vnic, 23.9);
          
          
          
          MEASUREMENT_CODEC_USE codecuse = sm.evel_measurement_codec_use_add("codecuse", 100);
         
          
          MEASUREMENT_LOAD load = sm.evel_measurement_new_load_add(19);
          sm.evel_measurement_load_shortTerm_set(load, 55.5);
          sm.evel_measurement_load_midTerm_set(load, 66.3);
          sm.evel_measurement_load_longTerm_set(load, 77.3);
          
          MEASUREMENT_PROCESS_STATS processtate = sm.evel_measurement_new_process_stats_add("ProcessState", 19);
          sm.evel_measurement_process_stats_forkRate_set(processtate, 20.3);
          sm.evel_measurement_process_stats_psStateBlocked_set(processtate, 22.1);
          sm.evel_measurement_process_stats_psStatePaging_set(processtate, 23.3);
          sm.evel_measurement_process_stats_psStateRunning_set(processtate, 24.2);
          sm.evel_measurement_process_stats_psStateSleeping_set(processtate, 25.5);
          sm.evel_measurement_process_stats_psStateStopped_set(processtate, 26.6);
          sm.evel_measurement_process_stats_psStateZombie_set(processtate, 26.6);
          
          MACHINE_CHECK_EXCEPTION except = sm.evel_measurement_new_machine_check_exception_add("Exception");
          sm.evel_measurement_Exception_correctedMemoryErrors_set(except, 10.0);
          sm.evel_measurement_Exception_correctedMemoryErrors_In1Hr_set(except, 12.5);
          sm.evel_measurement_Exception_uncorrectedMemoryErrors_set(except, 15.2);
          sm.evel_measurement_Exception_uncorrectedMemoryErrors_In1Hr_set(except, 15.3);
         
          
          sm.evel_measurement_addl_info_add("name", "value");
          

          MEASUREMENT_IPMI ipmi = sm.evel_measurement_new_ipmis_add();
          
          ipmi.evel_meas_ipmi_add(ipmi,10.2, 10.2, 10.2, 10.2);
          
 //         ipmi.evel_measurement_ipmi_exitAirTemperature_set(ipmi, 10.0);
//          ipmi.evel_measurement_ipmi_frontPanelTemperature_set(ipmi, 11.0);
//          ipmi.evel_measurement_ipmi_ioModuleTemperature_set(ipmi, 12.2);
//          ipmi.evel_measurement_ipmi_systemAirflow_set(ipmi, 13.4);
          
          
          MEASUREMENT_IPMI_PROCESSOR proc = ipmi.evel_measurement_IPMI_MEASUREMENT_IPMI_PROCESSOR_add("Proc1", 11.008);
          
          
          
          proc.getProcessorDIMMaggregateThermalMargin("ThermID1", 23.45);
          proc.getProcessorDIMMaggregateThermalMargin("ThermID2", 65.45);
          ipmi.evelMeasurementIpmiProcessorAdd("IPMIPro",10.000,12.000,"DIMM1",90.000);
          ipmi.evelMeasurementIpmiProcessorAdd("IPMIPro",10.000,12.000,"DIMM1",90.000);
         
          
          ipmi.evel_measurement_IPMIbaseboardTemperature_add("IPMIbaseboardTemperature", 10.001);
          ipmi.evel_measurement_IPMIbaseboardTemperature_add("IPMIbaseboardTemperature2", 3445.0033);
         
          
          ipmi.evel_measurement_IPMIbaseboardvoltageResulator_add("IPMIbaseboardvoltageRegulator", 12.000);
          ipmi.evel_measurement_IPMIbaseboardvoltageResulator_add("IPMIbaseboardvoltageRegulator2", 99.000089);
          
          
          ipmi.evel_measurement_IPMI_MEASUREMENT_IPMIbattery_add("IPMIbattery", "BatteryType", 123.00);
          ipmi.evel_measurement_IPMI_MEASUREMENT_IPMIbattery_add("IPMIbattery2", "BatteryType2", 123.11);
          
          ipmi.evel_measurement_IPMI_MEASUREMENT_IPMIpowerSupply_add("PowerSupply", 19.000, 23.000, 34.000);
          ipmi.evel_measurement_IPMI_MEASUREMENT_IPMIpowerSupply_add("PowerSupply2", 11.002, 33.44, 90.0001);
         
          
          ipmi.evel_measurement_IPMI_MEASUREMENT_IPMIglobalAggregateTemperatureMargin_add("AggregateTemperatureMargin",14.00000);
          ipmi.evel_measurement_IPMI_MEASUREMENT_IPMIglobalAggregateTemperatureMargin_add("AggregateTemperatureMargin2",14.1111);
         
          ipmi.evel_measurement_IPMINIC_add("nic_Identifier", 10.000);
          ipmi.evel_measurement_IPMINIC_add("nic_Identifier2", 1111.011);
          ipmi.evel_measurement_IPMIHSBP_add("hsbpIdentifier", 10.990);
          ipmi.evel_measurement_IPMIHSBP_add("hsbpIdentifier2", 12.990);
          ipmi.evel_measurement_IPMIfan_add("fanIdentfier", 10.000);
          ipmi.evel_measurement_IPMIfan_add("fanIdentfier2", 21.077);
         
          sm.evel_measurement_custom_measurement_add("Measurement", "name", "value");
          

            sm.evel_measurement_custom_measurement_add("group1","name1","val1");
            sm.evel_measurement_custom_measurement_add("group1","name2","val2");
            sm.evel_measurement_custom_measurement_add("group2","name1","val1");
            sm.evel_measurement_custom_measurement_add("group2","name2","val2");
            
            sm.evel_measurement_addl_info_add("name", "value");
            sm.evel_measurement_addl_info_add("name", "value");
         //   be.addEvent(sm);
            AgentMain.evel_post_event(sm);
            
            
            
            
/*  
  * EvelScalingMeasurement Change End
  * */              
            
            
            


            
            
            

            
            
            
            
            EvelSyslog sysl = new EvelSyslog("Syslog_vVNF", "vmname_ip",
            		EvelFault.EVEL_SOURCE_TYPES.EVEL_SOURCE_ROUTER,
                    "Router failed","JUNIPER");
            
            sysl.evel_syslog_event_source_host_set("SL Host");
            sysl.evel_syslog_priority_set(21);
            sysl.evel_syslog_proc_id_set(456);
            sysl.evel_syslog_proc_set("routed");
            
            sysl.evel_syslog_s_data_set("sys data");
            sysl.evel_syslog_sdid_set("200");
            sysl.evel_syslog_severity_set("Alert");
            
            sysl.evel_syslog_facility_set(EVEL_SYSLOG_FACILITIES.EVEL_SYSLOG_FACILITY_INTERNAL);
            sysl.evel_syslog_severity_set("Data");
            sysl.evel_syslog_version_set(20);
            sysl.evel_syslog_msghost_set("Host@msg");
            sysl.evel_syslogTs_set("SyslogTs");
            
            
            sysl.evel__syslog_addl_info_add("name1", "value1");
            sysl.evel__syslog_addl_info_add("name2", "value2");
            
         //   be.addEvent(sysl);
            AgentMain.evel_post_event(sysl);
            /*
             * Ves6.0 Updated 15/07/2018
             */
 
            
            
            
/*  
 * EvelSyslog Change End
 * */             
           
            
      
            
            
            
            EvelPnfRegistration pnfRegistration = new EvelPnfRegistration("PnfRegistration_vVNF", "vmname_ip");
            pnfRegistration.evel_pnrregistration_add_lastServiceDate_set("10FEB2019");
            pnfRegistration.evel_pnrregistration_add_modelNumber_set("123456789");
            pnfRegistration.evel_pnfRegistration_serialNumber_set("6061ZW3");
            pnfRegistration.evel_pnrregistration_add_macaddress_set("localhost");
            pnfRegistration.evel_pnrregistration_add_manufactureDate_set("FEB2011");
          //  pnfRegistration.evel_pnrregistration_add_modelNumber_set("FE934567");
            pnfRegistration.evel_pnrregistration_add_oamV4IpAddress_set("localhost");
            
            pnfRegistration.evel_pnfRegistration_softwareVersion_set("SW1234");
            
            
            pnfRegistration.evel_pnfRegistration_unitFamily_set("unitFamily222");
            pnfRegistration.evel_pnfRegistration_unitType_set("unitType1");
            
            pnfRegistration.evel_pnrregistration_add_oamV4IpAddress_set("localhost");
            pnfRegistration.evel_pnrregistration_add_oamV6IpAddress_set("localhost");
            
            
            pnfRegistration.evel_pnfRegistration_vendorName_set("Vend_nam_123");
            pnfRegistration.evel_pnrregistration_addl_info_add("Name1", "value1");
            pnfRegistration.evel_pnrregistration_addl_info_add("Name2", "value2");
            
            
         
                      
        //    be.addEvent(pnfRegistration);
          AgentMain.evel_post_event(pnfRegistration);
            
/*  
 * EvelPnfRegistration Change End
 * */            

            EvelHeartbeatField hfld = new EvelHeartbeatField(123,"HeartbeatField_vVNF", "1");
            hfld.evel_hrtbt_interval_set(100);
            hfld.evel_timeZoneOffset_set("UTC+5:30");
            hfld.evel_hrtbt_field_addl_info_add("Name", "Value");
        //    be.addEvent(hfld);
            AgentMain.evel_post_event(hfld);
            
            
/*  
 * EvelHeartbeatField Change End
 * */            
           
            EvelSipSignaling sip = new EvelSipSignaling("SipSignaling_vVNF", "vmname_ip","aricent","corlator","localhost","5647","localhost","5678");
            sip.evel_signaling_vnfmodule_name_set("nfName");
            sip.evel_signaling_vnfname_set("nf_name");
            sip.evel_signaling_addl_info_add("name1", "value1");
            sip.evel_signaling_addl_info_add("name2", "value2");
           sip.evel_signaling_compressed_sip_set("CompressedIP");    
           sip.evel_signaling_summary_sip_set("SummarySip");
           
            
         //   be.addEvent(sip);
            AgentMain.evel_post_event(sip);
/*  
 * EvelSipSignaling Change End
 * */             
            
            

            EvelVoiceQuality vq = new EvelVoiceQuality("VoiceQuality_vVNF", "vmname_ip",
                    "calleeSideCodc",
                    "callerSideCodc", "corlator",
                    "midCllRtcp", "juniper");
            vq.evel_voice_quality_end_metrics_set("adjname", "Caller", 20, 30, 40, 50, 60, 70, 80, 100, 110, 120, 130, 140, 1.1, 160.12, 17, 190, 200,210,220,230,240,250,260,270,280,290,300);
            
            
            vq.evel_voice_quality_phone_number_set("PhoneNumber");
            vq.evel_voice_quality_vnfmodule_name_set("vnfNaming");
            vq.evel_voice_quality_vnfname_set("vnfName");
            vq.evel_voice_quality_addl_info_add("Name1", "value1");
            vq.evel_voice_quality_addl_info_add("Name2", "value2");
            
            
            
         //   be.addEvent(vq);
           AgentMain.evel_post_event(vq);
            
/*  
 * EvelVoiceQuality Change End
 * */           
            

            EvelOther ev = new EvelOther("MyCustomEvent_vVNF", "vmname_ip");
            ev.evel_other_field_add("name1", "value1");
            ev.evel_other_field_add("name2", "value2");
            ev.evel_other_field_add("name3", "value3");
            ev.evel_other_field_add("name4", "value4");
            
            ev.evel_other_field_add_namedarray("value3", "name3", "value6");
            ev.evel_other_field_add_namedarray("value1", "name4", "value7");
            ev.evel_other_field_add_namedarray("value1", "name4", "value7");
            ev.evel_other_field_add_namedarray("value4", "name5", "value8");
           
            
            
          //  be.addEvent(ev);
            AgentMain.evel_post_event(ev);
/*  
 * EvelOther Change End
 * */            
            
            String dateStart = "01/14/2012 09:29:58";
            String dateStop = "01/15/2012 10:31:48";

            //HH converts hour in 24 hours format (0-23), day calculation
            SimpleDateFormat format = new SimpleDateFormat("MM/dd/yyyy HH:mm:ss");

            Date d1 = null;
            Date d2 = null;

            try {
                d1 = format.parse(dateStart);
                d2 = format.parse(dateStop);
            }catch (Exception e) {
                
            }
            EvelThresholdCross tca = new EvelThresholdCross("ThresholdCross_vVNF", "vmname_ip", "CRIT", 
            		"mcastRxPackets", EvelThresholdCross.EVEL_EVENT_ACTION.EVEL_EVENT_ACTION_CLEAR, 
            		"Mcast Rx breached", 
            		EvelThresholdCross.EVEL_ALERT_TYPE.EVEL_CARD_ANOMALY, 
            		
            		d1, EvelThresholdCross.EVEL_SEVERITIES.EVEL_SEVERITY_CRITICAL, 
            		d2);
            
            tca.evel_threshold_cross_alertvalue_set("alertvalue");
            tca.evel_threshold_cross_data_collector_set("data_collector");
            tca.evel_threshold_cross_data_elementtype_set("data_elementtype");
            tca.evel_threshold_cross_interfacename_set("interfacename");
            tca.evel_threshold_cross_networkservice_set("networkservice");
            tca.evel_threshold_cross_possible_rootcause_set("possible_rootcause");
            
            
            
            
            tca.evel_thresholdcross_addl_info_add("addname1", "addvalue1");
            tca.evel_thresholdcross_addl_info_add("addname2", "addvalue2");
            tca.evel_thresholdcross_alertid_add("alert1");
            tca.evel_thresholdcross_alertid_add("alert2");
            tca.evel_thresholdcross_alertid_add("alert3");
            tca.evel_thresholdcross_hashMap_add("hashName", "hashValue");

            
            
         //   be.addEvent(tca);
            AgentMain.evel_post_event(tca);
            
            
            
/*  
 * EvelThresholdCross Change End
 * */            
            


            EvelMobileFlow mf = new EvelMobileFlow("MobileFlow_vVNF", "vmname_ip",
                    "In",
                    null,
                    "GTP",
                    "v2.3",
                    "localhost",
                    345556,
                    "localhost",
                    334344);
			MOBILE_GTP_PER_FLOW_METRICS mygtp = mf.new MOBILE_GTP_PER_FLOW_METRICS(
                    1.01,
                    2.02,
                    3,
                    4,
                    5,
                    6,
                    7,
                    8,
                    9,
                    d1,
                    "ACTIVE",
                    10,
                    11,
                    12,
                    13,
                    14,
                    15,
                    16,
                    17,
                    18,
                    19,
                    20,
                    21,
                    22,
                    23,
                    24,
                    25,
                    26,
                    27,
                    28);
            mf.gtp_per_flow_metrics = mygtp;
            
            
            mf.evel_mobile_gtp_metrics_dur_con_fail_set(mygtp, 1);
            mf.evel_mobile_gtp_metrics_dur_tun_fail_set(mygtp, 1);
            mf.evel_mobile_gtp_metrics_act_by_set(mygtp, "Active");
            mf.evel_mobile_gtp_metrics_act_time_set(mygtp, "Time");
            mf.evel_mobile_gtp_metrics_deact_by_set(mygtp, "FlowDeactivation");
            mf.evel_mobile_gtp_metrics_con_status_set(mygtp, "Status");
            mf.evel_mobile_gtp_metrics_tun_status_set(mygtp, "Tunnel Status");
            mf.evel_mobile_gtp_metrics_large_pkt_rtt_set(mygtp, 12);
            mf.evel_mobile_gtp_metrics_large_pkt_thresh_set(mygtp, 123);
            mf.evel_mobile_gtp_metrics_max_rcv_bit_rate_set(mygtp, 12);
            mf.evel_mobile_gtp_metrics_max_trx_bit_rate_set(mygtp, 12);
            mf.evel_mobile_gtp_metrics_num_echo_fail_set(mygtp, 1);
            mf.evel_mobile_gtp_metrics_num_tun_fail_set(mygtp, 2);
            mf.evel_mobile_gtp_metrics_num_http_errors_set(mygtp, 2);
            
            mf.evel_mobile_gtp_metrics_iptos_set(mygtp,2, 3);            
            mf.evel_mobile_gtp_metrics_iptos_set(mygtp,5, 6);
            
            mf.evel_mobile_gtp_metrics_tcp_flag_count_add(mygtp, 3, 4);
            mf.evel_mobile_gtp_metrics_tcp_flag_count_add(mygtp, 5, 8);
            
            mf.evel_mobile_gtp_metrics_qci_cos_count_add(mygtp, 2, 3);
            mf.evel_mobile_gtp_metrics_qci_cos_count_add(mygtp, 5, 6);
            mf.evel_mobile_flow_addl_field_add("mobileFlowName1", "mobileValue1");          
            mf.evel_mobile_flow_app_type_set("application type");
            mf.evel_mobile_flow_app_prot_type_set("appProtocolType");
            mf.evel_mobile_flow_app_prot_ver_set("appProtocolVersion");
            mf.evel_mobile_flow_cid_set("CID");
            mf.evel_mobile_flow_con_type_set("ConnectionType");
            mf.evel_mobile_flow_ecgi_set("ECGI");
            mf.evel_mobile_flow_gtp_prot_type_set("gtpProtocalType");
            mf.evel_mobile_flow_gtp_prot_ver_set("GtpVersion");
            mf.evel_mobile_flow_http_header_set("HttpHeader");
            mf.evel_mobile_flow_imei_set("IMEI");
            mf.evel_mobile_flow_imsi_set("IMSI");
            mf.evel_mobile_flow_lac_set("LAC");
            mf.evel_mobile_flow_mcc_set("MCC");
            mf.evel_mobile_flow_mnc_set("MNC");
            mf.evel_mobile_flow_msisdn_set("Msisdn");
            mf.evel_mobile_flow_other_func_role_set("OtherFunctionRole");
            
            mf.evel_mobile_flow_rac_set("RAC");
            mf.evel_mobile_flow_radio_acc_tech_set("RadoiAcessTech");
            mf.evel_mobile_flow_sac_set("SAC");
            
            mf.evel_mobile_flow_samp_alg_set(123);
            mf.evel_mobile_flow_tac_set("TAC");
            mf.evel_mobile_flow_tunnel_id_set("Tunnel");
            mf.evel_mobile_flow_vlan_id_set("Vlan");
            
            
            
         //    be.addEvent(mf);
            AgentMain.evel_post_event(mf);
            

            
/*  
 * EvelMobileFlow Change End
 * */           
            
            
        }  //srikanth no need for forloop , send only once.
        

            AgentMain.evel_shutdown();

    }
}

