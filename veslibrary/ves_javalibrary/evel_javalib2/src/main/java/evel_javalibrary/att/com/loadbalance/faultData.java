package evel_javalibrary.att.com.loadbalance;
/**************************************************************************//**
 * @file
 * Evel Fault Event class extends EvelHeader class
 *
 * This file implements the Evel Fault Event class which is intended to provide a
 * simple wrapper around the complexity of AT&T's Vendor Event Listener API so
 * that VNFs can use it to send Fault events.
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

import java.io.File;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import evel_javalibrary.att.com.AgentMain;
import evel_javalibrary.att.com.EvelBatch;
import evel_javalibrary.att.com.EvelFault;
import evel_javalibrary.att.com.EvelFault.EVEL_SEVERITIES;
import evel_javalibrary.att.com.EvelFault.EVEL_SOURCE_TYPES;
import evel_javalibrary.att.com.EvelFault.EVEL_VF_STATUSES;
import evel_javalibrary.att.com.EvelHeader;
import evel_javalibrary.att.com.EvelHeader.PRIORITIES;



public class faultData extends Thread{
	
	static HashMap<String, String> fault_config = new HashMap<>();
	static HashMap<String, String> interface_config = new HashMap<>();
	
	static HashMap<String, String> hm = new HashMap<>();
	
	static String linkStart = "";
	static int linkCount; 
	
	
	static int  gm_event_id = 1;
	static String event_id1 = "fault";
	static String event_id = "00000000";
	static String event_id2=null;
	
	
	static int bytes_in;
	static int bytes_out;
	static int packets_in;
	static int packets_out;
	
	
	static int falut_raised =0;
	
	
	public void run() {
		
		String alarmCondition = "linkDown";
		String specificProblem = "Transmit-Receive issue";
		
		Long start_epoch_microsec = 0L;
		Long last_epoch_microsec = 0L;
		
		
		MeasureData mdataThread = new MeasureData();
		hm = mdataThread.read_common_config_file();
		
		read_fault_config_file();
		HashMap<String, String> intFaceMapFault = mdataThread.read_interface_config_file();
		int numOfInterfacesFalut = 0;
		if( !intFaceMapFault.isEmpty() )
			numOfInterfacesFalut = intFaceMapFault.size();
		if( numOfInterfacesFalut <= 0) {
			System.out.println("ERROR : Didn't find interfacess in config file, exiting thread");
			return;
		}
		
		
		HashMap falut_last_metrics = mdataThread.read_vpp_metrics(linkStart);
		
		while(true) {
			//request_rate = rand()%10000;
			//request_rate =2;
			EvelBatch ebt = new EvelBatch();
			event_id2 = event_id1+ event_id+(gm_event_id++);
//			EvelScalingMeasurement eveMeas = new EvelScalingMeasurement( Double.parseDouble(common_meas.get("measurementInterval")) ,
//					common_meas.get("eventName"),
//                    event_id2);
			
			EvelHeader header = new EvelHeader("", "");	
			
			
			//EvelFault eveFalt = new EvelFault(fault_config.get("eventName"), event_id2, alarmCondition, specificProblem,EVEL_PRIORITY_MEDIUM, EVEL_SEVERITY_MAJOR,EVEL_SOURCE_HOST,EVEL_VF_STATUS_IDLE);
			
			EvelFault eveFalt  = new EvelFault(fault_config.get("eventName"),event_id2, alarmCondition, specificProblem,
                    EvelHeader.PRIORITIES.EVEL_PRIORITY_HIGH,
                    EVEL_SEVERITIES.EVEL_SEVERITY_MAJOR,
                    EVEL_SOURCE_TYPES.EVEL_SOURCE_CARD,
                    EVEL_VF_STATUSES.EVEL_VF_STATUS_ACTIVE);
			
			
			
			//EvelFault eveFalt = new EvelFault(fault_config.get("eventName"), event_id2, alarmCondition,specificProblem,1,1,3,1);			
	//		EvelFault eveFalt = new EvelFault("eventName", "event_id2", "alarmCondition","specificProblem",1,1,3,1);
	//		EvelFault eveFalt = new EvelFault(fault_config.get("eventName"), event_id2, alarmCondition,specificProblem,1,1,3,1);
			
			for( String falut : intFaceMapFault.keySet() ) {				
			    
				HashMap falut_current_metrics = mdataThread.read_vpp_metrics(falut);
				if( falut_current_metrics.size() !=4 ) {
					System.out.println("ERROR:: Did't get vpp metrics for vNic "+falut);
					continue;
				}
				
				if (Integer.parseInt((String) falut_current_metrics.get("bytes_in"))
						- Integer.parseInt((String) falut_last_metrics.get("bytes_in")) > 0) {
					bytes_in = Integer.parseInt((String) falut_current_metrics.get("bytes_in"))
							- Integer.parseInt((String) falut_last_metrics.get("bytes_in"));
				} else {
					bytes_in = 0;
				}
				
				if (Integer.parseInt((String) falut_current_metrics.get("bytes_out"))
						- Integer.parseInt((String) falut_last_metrics.get("bytes_out")) > 0) {
					bytes_out = Integer.parseInt((String) falut_current_metrics.get("bytes_out"))
							- Integer.parseInt((String) falut_last_metrics.get("bytes_out"));
				} else {
					bytes_out = 0;
				}
				
				if (Integer.parseInt((String) falut_current_metrics.get("packets_in"))
						- Integer.parseInt((String) falut_last_metrics.get("packets_in")) > 0) {
					packets_in = Integer.parseInt((String) falut_current_metrics.get("packets_in"))
							- Integer.parseInt((String) falut_last_metrics.get("packets_in"));
				} else {
					packets_in = 0;
				}
				
				if (Integer.parseInt((String) falut_current_metrics.get("packets_out"))
						- Integer.parseInt((String) falut_last_metrics.get("packets_out")) > 0) {
					packets_out = Integer.parseInt((String) falut_current_metrics.get("packets_out"))
							- Integer.parseInt((String) falut_last_metrics.get("packets_out"));
				} else {
					packets_out = 0;
				}
				
				
                
				if((bytes_in < Integer.parseInt((String)fault_config.get("lowWaterMark")) || bytes_out < Integer.parseInt((String)fault_config.get("lowWaterMark")) || 
						packets_in < Integer.parseInt((String)fault_config.get("lowWaterMark")) || packets_out < Integer.parseInt((String)fault_config.get("lowWaterMark"))) && falut_raised == 0){
					
					event_id2 = event_id1+ (gm_event_id++);
					
                    if(eveFalt != null) {
                    	
                    	falut_raised =1;
                    	eveFalt.evel_fault_interface_set(linkStart);
                    	
                    	if( hm.get("eventType")!=null) {
                    		eveFalt.evel_fault_type_set(hm.get("eventType"));
                    		
                    		start_epoch_microsec = last_epoch_microsec;
                    	    last_epoch_microsec = System.nanoTime()/1000;
                    		
                    		eveFalt.evel_last_epoch_set(start_epoch_microsec);
                    		eveFalt.evel_start_epoch_set(last_epoch_microsec);
                    		
                    		eveFalt.evel_fault_category_set("link");
                    		eveFalt.evel_fault_interface_set("My Interface");
                    		eveFalt.evel_nfcnamingcode_set(hm.get("nfcNamingCode").toString());
                    		eveFalt.evel_nfnamingcode_set(hm.get("nfNamingCode").toString());
                    		eveFalt.evel_reporting_entity_name_set(hm.get("reportingEntityName").toString());
        					eveFalt.evel_reporting_entity_id_set(hm.get("reportingEntityId").toString());
        					eveFalt.evel_nfVendorName_set(hm.get("nfVendorName").toString());
        					eveFalt.evel_header_set_sourceid(true,hm.get("sourceId").toString());
        					
        					eveFalt.evel_header_set_source_name(hm.get("sourceName").toString());		
        					eveFalt.evel_timeZoneOffset_set(hm.get("timeZoneOffset").toString());
                    		
                    	}
                    	
                    }
					
				}else if((bytes_in > Integer.parseInt((String)fault_config.get("lowWaterMark")) && bytes_out > Integer.parseInt((String)fault_config.get("lowWaterMark")) && 
						packets_in > Integer.parseInt((String)fault_config.get("lowWaterMark")) && packets_out > Integer.parseInt((String)fault_config.get("lowWaterMark"))) && falut_raised == 1) {
					
					
					
					event_id2 = event_id1+ (gm_event_id++);
//					EvelHeader header = new EvelHeader("", "");			
//					EvelFault eveFalt = new EvelFault(fault_config.get("eventName"), event_id2, "linkDown", "Transmit-Receive issue", header.priority, eveFalt.event_severity,eveFalt.event_source_type,eveFalt.vf_status);
					
                    if(eveFalt != null) {
                    	falut_raised =1;
                    	
                    	eveFalt.evel_fault_interface_set(linkStart);
                    	System.out.println("Event type is "+hm.get("eventType")  );
                    	if( hm.get("eventType")!=null) {
                    		eveFalt.evel_fault_type_set(hm.get("eventType"));
                    		
                    		eveFalt.evel_fault_category_set("link");
                    		eveFalt.evel_nfcnamingcode_set(hm.get("nfcNamingCode").toString());
                    		eveFalt.evel_nfnamingcode_set(hm.get("nfNamingCode").toString());
                    		eveFalt.evel_reporting_entity_name_set(hm.get("reportingEntityName").toString());
        					eveFalt.evel_reporting_entity_id_set(hm.get("reportingEntityId").toString());
        					eveFalt.evel_nfVendorName_set(hm.get("nfVendorName").toString());
        					eveFalt.evel_header_set_sourceid(true,hm.get("sourceId").toString());
        					
        					eveFalt.evel_header_set_source_name(hm.get("sourceName").toString());		
        					eveFalt.evel_timeZoneOffset_set(hm.get("timeZoneOffset").toString());
                    		
                    	}
                    	
                    }

					
					
				}
				
			
			try {
			Thread.sleep(1000);
			}catch(Exception e) {}
			}
		//	ebt.addEvent(eveFalt);
			AgentMain.evel_post_event(eveFalt);
			System.out.println(" Event sent");
			
		}
		
		
	}
	
	
	
	
	
	
	public static HashMap<String, String> read_fault_config_file() {

		List<String> list = new ArrayList<String>();
		
		List<String> list_interface = new ArrayList<String>();

		fault_config.put("eventName", "");
		fault_config.put("faultCheckInterval", "");
		fault_config.put("lowWaterMark", "");
		
		//interface_config.put("lo", "");

		try {
		//	File file = new File("/home/ves/users/admin/temp/fw_flt_config.txt");
			File file = new File("./src/main/java/evel_javalibrary/att/com/loadbalance/fw_flt_config.txt");
			System.out.println("File path is..."+ file);
			list = Files.readAllLines(file.toPath(), Charset.defaultCharset());
			for (String lineSplit : list) {
				String[] res = lineSplit.split(" ");
				fault_config.put(res[0], res[1]);
			}
			
			
		} catch (Exception ex) {
			ex.printStackTrace();
		}
		System.out.println("KEYS:fault_config " + fault_config.keySet().size());
		System.out.println("VALUES:fault_config " + fault_config.values());
		return fault_config;
	}



}
