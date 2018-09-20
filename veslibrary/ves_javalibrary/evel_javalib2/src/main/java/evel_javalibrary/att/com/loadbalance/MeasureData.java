package evel_javalibrary.att.com.loadbalance;
/**************************************************************************//**
 * @file
 * Measurement class
 *
  * This file implements the Measurement Event class which is intended to provide a
 * simple wrapper around the complexity of AT&T's Vendor Event Listener API so
 * that VNFs can use it to send CPU, Memory, Disk Measurements to Collector.
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


import java.io.BufferedReader;
import java.io.File;
import java.io.InputStreamReader;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import org.apache.log4j.Level;

import evel_javalibrary.att.com.AgentMain;
import evel_javalibrary.att.com.EvelBatch;
import evel_javalibrary.att.com.EvelScalingMeasurement;

public class MeasureData  extends Thread{
	static HashMap<String, String> hm = new HashMap<>();
	static HashMap<String, String> vpp_metrics = new HashMap<>();
	
	static HashMap<String, String> common_meas = new HashMap<>();

	
	static int bytes_in_this_round;
	static int bytes_out_this_round;
	static int packets_in_this_round;
	static int packets_out_this_round;
	
	static int  gm_event_id = 1;
	static String event_id1 = "mvfs";
	static String event_id = "00000000";
	static String event_id2=null;
	
	static int request_rate = 0;
	
	static long epoch_start = 0;
	
	static String linkStart = "";
	static int linkCount; 
	
	
	Long start_epoch_microsec = 0L;
	Long last_epoch_microsec = 0L;
	 
	//public static void main(String[] args) {
	public void run() {
		// TODO Auto-generated method stub
		//read_config_file();
		read_meas_traffic();		
		read_common_config_file();
		read_meas_config_file();
		
		HashMap<String, String> intFaceMap = read_interface_config_file();
		int numOfInterfaces = 0;
		if( !intFaceMap.isEmpty() )
			numOfInterfaces = intFaceMap.size();
		if( numOfInterfaces <= 0) {
			System.out.println("ERROR : Didn't find interfacess in config file, exiting thread");
			return;
		}
		
		System.out.println("MAP values: " + hm.values());
		
		HashMap last_metrics = read_vpp_metrics(linkStart);
		try {
		Thread.sleep(Integer.parseInt(common_meas.get("measurementInterval")));
		}catch(Exception e) {}

		
		while(true) {
			//request_rate = rand()%10000;
			request_rate =2;
			EvelBatch ebt = new EvelBatch();
			event_id2 = event_id1+ event_id+(gm_event_id++);
			EvelScalingMeasurement eveMeas = new EvelScalingMeasurement( Double.parseDouble(common_meas.get("measurementInterval")) ,
					common_meas.get("eventName"),
                    event_id2);
			
			for( String vNic : intFaceMap.keySet() ) {
				//System.out.println("INFO:: getting vpp metrics for vNic "+vNic);
			
				HashMap current_metrics = read_vpp_metrics(vNic);
				if( current_metrics.size() !=4 ) {
					System.out.println("ERROR:: Did't get vpp metrics for vNic "+vNic);
					continue;
				}
				
				if (Integer.parseInt((String) current_metrics.get("bytes_in"))
						- Integer.parseInt((String) last_metrics.get("bytes_in")) > 0) {
					bytes_in_this_round = Integer.parseInt((String) current_metrics.get("bytes_in"))
							- Integer.parseInt((String) last_metrics.get("bytes_in"));
				} else {
					bytes_in_this_round = 0;
				}
				
				if (Integer.parseInt((String) current_metrics.get("bytes_out"))
						- Integer.parseInt((String) last_metrics.get("bytes_out")) > 0) {
					bytes_out_this_round = Integer.parseInt((String) current_metrics.get("bytes_out"))
							- Integer.parseInt((String) last_metrics.get("bytes_out"));
				} else {
					bytes_out_this_round = 0;
				}
				
				if (Integer.parseInt((String) current_metrics.get("packets_in"))
						- Integer.parseInt((String) last_metrics.get("packets_in")) > 0) {
					packets_in_this_round = Integer.parseInt((String) current_metrics.get("packets_in"))
							- Integer.parseInt((String) last_metrics.get("packets_in"));
				} else {
					packets_in_this_round = 0;
				}
				
				if (Integer.parseInt((String) current_metrics.get("packets_out"))
						- Integer.parseInt((String) last_metrics.get("packets_out")) > 0) {
					packets_out_this_round = Integer.parseInt((String) current_metrics.get("packets_out"))
							- Integer.parseInt((String) last_metrics.get("packets_out"));
				} else {
					packets_out_this_round = 0;
				}
				
				event_id2 = event_id1+ (gm_event_id++);
			/*	EvelScalingMeasurement eveMeas = new EvelScalingMeasurement( Double.parseDouble(hm.get("measurementInterval")) ,
																			                    hm.get("eventName"),
																			                    event_id2); */
			
				
				EvelScalingMeasurement.MEASUREMENT_NIC_PERFORMANCE vNicPerf = eveMeas.evel_measurement_new_vnic_performance(vNic, "true");
				eveMeas.evel_meas_vnic_performance_add(vNicPerf );
				
				if( hm.get("eventType")!=null) {
					
					start_epoch_microsec = last_epoch_microsec;
            	    last_epoch_microsec = System.nanoTime()/1000;
            		
            	    eveMeas.evel_last_epoch_set(start_epoch_microsec);
            	    eveMeas.evel_start_epoch_set(last_epoch_microsec);
					
					
					eveMeas.evel_measurement_type_set( hm.get("eventType").toString());
					eveMeas.evel_measurement_request_rate_set(request_rate );
					eveMeas.evel_vnic_performance_rx_total_pkt_delta_set(vNicPerf, packets_in_this_round);
					eveMeas.evel_vnic_performance_tx_total_pkt_delta_set(vNicPerf, packets_out_this_round);
					eveMeas.evel_vnic_performance_rx_octets_delta_set( vNicPerf, bytes_in_this_round);
					eveMeas.evel_vnic_performance_tx_octets_delta_set( vNicPerf, bytes_out_this_round);
					
					eveMeas.evel_nfcnamingcode_set(hm.get("nfcNamingCode").toString());
					eveMeas.evel_nfnamingcode_set(hm.get("nfNamingCode").toString());
					eveMeas.evel_reporting_entity_name_set(hm.get("reportingEntityName").toString());
					eveMeas.evel_reporting_entity_id_set(hm.get("reportingEntityId").toString());
					eveMeas.evel_nfVendorName_set(hm.get("nfVendorName").toString());
					eveMeas.evel_header_set_sourceid(true,hm.get("sourceId").toString());
					
					eveMeas.evel_header_set_source_name(hm.get("sourceName").toString());		
					eveMeas.evel_timeZoneOffset_set(hm.get("timeZoneOffset").toString());
					
					
				
					
				}

			
			try {
			Thread.sleep(Integer.parseInt(common_meas.get("measurementInterval")));
			}catch(Exception e) {}
			last_metrics = current_metrics;
			}
				
			//ebt.addEvent(eveMeas);
			AgentMain.evel_post_event(eveMeas);
			System.out.println(" Event sent");
			
		}
			
	}
	
	
	
	
	public static HashMap<String, String> read_vpp_metrics(String linkStart) {
		Process p;
		
		String s=""; 
		HashMap<String, String> vpp_metrics_map =  new HashMap<>();
		String params[] = {"-f3", "-f11", "-f4", "-f12"};
		try {
			Runtime rt = Runtime.getRuntime();
			for(int i=0;i<4;i++) {
			String[] command = {"/bin/sh", "-c", "cat /proc/net/dev | grep \""+linkStart+"\" | tr -s \' \' | cut -d\' \' "+params[i]+""}; 
     	    Process child = rt.exec(command);

		    BufferedReader reader = new BufferedReader(new InputStreamReader(        
		    		child.getInputStream()));                                          
		                                                                       
		        while ((s= reader.readLine()) != null) {                                
		        		String[] res = s.split(" ");
		        		if( i==0)
		        			vpp_metrics_map.put("bytes_in", res[0]);
		        		if( i==1)
		        			vpp_metrics_map.put("packets_in", res[0]);
		        		if( i==2)
		        			vpp_metrics_map.put("bytes_out", res[0]);
		        		if( i==3)
		        			vpp_metrics_map.put("packets_out", res[0]);
						
					}
		        }   
						
		} catch (Exception e) {
			e.printStackTrace();
		}
		return vpp_metrics_map;
	}

	
	
	public static HashMap<String, String> read_common_config_file() {

		List<String> list = new ArrayList<String>();

		
		hm.put("eventType", "");
		hm.put("nfcNamingCode", "");
		hm.put("nfNamingCode", "");
		hm.put("nfVendorName", "");
		hm.put("reportingEntityId", "");
		hm.put("reportingEntityName", "");
		hm.put("sourceId", "");
	    hm.put("sourceName", "");
		hm.put("timeZoneOffset", "");
		


		System.out.println("KEYS: " + hm.keySet().size());
		System.out.println("VALUES: " + hm.values());

		try {
		//	File file = new File("/home/ves/users/admin/temp/fw_common_config.txt");
			File file = new File("./src/main/java/evel_javalibrary/att/com/loadbalance/fw_common_config.txt");
			list = Files.readAllLines(file.toPath(), Charset.defaultCharset());
			for (String lineSplit : list) {
				String[] res = lineSplit.split(" ");
				hm.put(res[0], res[1]);
				System.out.println("File reading after split ---" + res[0]);
				System.out.println("File reading after split second---" + res[1]);
			}
		} catch (Exception ex) {
			ex.printStackTrace();
		}
		System.out.println("KEYS: " + hm.keySet().size());
		System.out.println("VALUES: " + hm.values());
		return hm;
	}
	
	
	
	public static HashMap<String, String> read_interface_config_file() {

		List<String> list = new ArrayList<String>();
		HashMap<String, String> interface_config = new HashMap<>();
		//interface_config.put("lo", "");
		
		
		System.out.println("KEYS: " + interface_config.keySet().size());
		System.out.println("VALUES: " + interface_config.values());

		try {
			//File file = new File("/home/ves/users/admin/temp/fw_interface_config.txt");
			File file = new File("./src/main/java/evel_javalibrary/att/com/loadbalance/fw_interface_config.txt");
			list = Files.readAllLines(file.toPath(), Charset.defaultCharset());
			for (String lineSplit : list) {
				String[] res = lineSplit.split(" ");
				interface_config.put(res[0], res[1]);
			}
			
			linkStart = (String)interface_config.keySet().toArray()[1];
			linkCount = interface_config.keySet().size();

			
			
		} catch (Exception ex) {
			ex.printStackTrace();
		}
		
		return interface_config;
	}


	
	
	

	
	public static HashMap<String, String> read_meas_config_file() {

		List<String> list = new ArrayList<String>();

		common_meas.put("eventName", "Measurement_vFirewall-AT&T_nicPerformance");
		common_meas.put("measurementInterval", "");
		
		System.out.println("KEYS: " + common_meas.keySet().size());
		System.out.println("VALUES: " + common_meas.values());

		try {
			//File file = new File("/home/ves/users/admin/temp/fw_meas_config.txt");
			File file = new File("./src/main/java/evel_javalibrary/att/com/loadbalance/fw_meas_config.txt");
			list = Files.readAllLines(file.toPath(), Charset.defaultCharset());
			for (String lineSplit : list) {
				String[] res = lineSplit.split(" ");
				common_meas.put(res[0], res[1]);
			}
		} catch (Exception ex) {
			ex.printStackTrace();
		}
		System.out.println("KEYS: " + common_meas.keySet().size());
		System.out.println("VALUES: " + common_meas.values());
		return common_meas;
	}



	
	
	public static HashMap<String, String> read_meas_traffic() {
		Process p;
		List<String> vpp_params = new ArrayList();
		String s=""; 
	//	HashMap<String, String> vpp_metrics_map =  new HashMap<>();
		String params[] = {"-f3", "-f11", "-f4", "-f12"};
		try {
//			System.out.println("***********inside read_vpp_metrics");
//			String command = "cat /proc/net/dev | grep \"Receive\" | tr -s \' \' | cut -d\' \' -f3";
			//{"-f3", "-f11", "-f4", "-f12"};
//			String command = "cat /proc/net/dev | grep \""+vnic+"\" ";
			for(int i=0;i<4;i++) {
			String[] command = {"/bin/sh", "-c", "docker logs vHello | grep -c"}; 
//			System.out.println("**COMMAND***: "+command);
		    Process child = Runtime.getRuntime().exec(command);

		    BufferedReader reader = new BufferedReader(new InputStreamReader(        
		    		child.getInputStream()));                                          
		                                                                       
		        while ((s= reader.readLine()) != null) {                                
		        	vpp_params.add(s);
		        	System.out.println("VPP meas_traffic:----" + s);   		        	
		        }   
			}			
		} catch (Exception e) {
			e.printStackTrace();
		}
		return vpp_metrics;
	}
}
