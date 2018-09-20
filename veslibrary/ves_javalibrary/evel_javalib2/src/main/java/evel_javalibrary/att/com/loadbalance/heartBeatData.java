package evel_javalibrary.att.com.loadbalance;
/**************************************************************************//**
 * @file
 * Heartbeat field class
 *
 * This file implements the Heartbeat Event class which is intended to provide a
 * simple wrapper around the complexity of AT&T's Vendor Event Listener API so
 * that VNFs can use it to send Agent status.
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

import javax.json.Json;
import javax.json.JsonArray;
import javax.json.JsonArrayBuilder;
import javax.json.JsonObject;
import javax.json.JsonObjectBuilder;

import evel_javalibrary.att.com.AgentMain;
import evel_javalibrary.att.com.EvelBatch;
import evel_javalibrary.att.com.EvelHeartbeatField;

public class heartBeatData extends Thread{
	
	static HashMap<String, String> hm = new HashMap<>();
	static HashMap<String, String> hb_config = new HashMap<>();
	static int  gm_event_id = 1;
	static String event_id1 = "mvfs";
	static String event_id2=null;
	
	
	public void run() {
		
		Long start_epoch_microsec = 0L;
		Long last_epoch_microsec = 0L;
		
		MeasureData mdataThread = new MeasureData();
		hm = mdataThread.read_common_config_file();
		read_hb_config_file();
		
		while(true) {
		event_id2 = event_id1+ (gm_event_id++);
		
		
		EvelHeartbeatField evelHb = new EvelHeartbeatField(Integer.parseInt(hb_config.get("heartbeatInterval")) ,
				hb_config.get("eventName"),
                event_id2);
		
		if( hm.get("eventType")!=null) {
			
			start_epoch_microsec = last_epoch_microsec;
    	    last_epoch_microsec = System.nanoTime()/1000;
    		
    	    evelHb.evel_last_epoch_set(start_epoch_microsec);
    	    evelHb.evel_start_epoch_set(last_epoch_microsec);
		
		evelHb.evel_header_type_set(hm.get("eventType").toString());
		evelHb.evel_nfcnamingcode_set(hm.get("nfcNamingCode").toString());
		evelHb.evel_nfnamingcode_set(hm.get("nfNamingCode").toString());
		evelHb.evel_reporting_entity_name_set(hm.get("reportingEntityName").toString());
		evelHb.evel_reporting_entity_id_set(hm.get("reportingEntityId").toString());
		evelHb.evel_nfVendorName_set(hm.get("nfVendorName").toString());
		evelHb.evel_header_set_sourceid(true,hm.get("sourceId").toString());
		evelHb.evel_header_set_source_name(hm.get("sourceName").toString());
		
		evelHb.evel_timeZoneOffset_set(hm.get("timeZoneOffset").toString());
		
		
		JsonObject obj = Json.createObjectBuilder()    	     	    	        
		    	         .add( "heartbeatFields",evelHeartbeatFieldObject()
		    	         ).build();

		EvelBatch ebt = new EvelBatch();
		//ebt.addEvent(evelHb);
		
		
		System.out.println(" Event sent..."+ obj.asJsonObject());
		System.out.println("Event sent...###########");		
		AgentMain.evel_post_event(evelHb);
		System.out.println(" Event sent...");
		}
		
		try {
			Thread.sleep(1000);
			}catch(Exception e) {
				
			}
		}
	}
	
	
	JsonObjectBuilder evelHeartbeatFieldObject()
	 {  
		String version = "3.0";
		JsonObjectBuilder evelHeatbeat = Json.createObjectBuilder()
	   	         .add("heartbeatInterval", hb_config.get("heartbeatInterval"));	  
	  evelHeatbeat.add( "heartbeatFieldsVersion", version);
		return evelHeatbeat;
	 }
	
	
	public static HashMap<String, String> read_hb_config_file() {

		List<String> list = new ArrayList<String>();

		hb_config.put("eventName", "");
		hb_config.put("heartbeatInterval", "");

		
		System.out.println("KEYS: " + hb_config.keySet().size());
		System.out.println("VALUES: " + hb_config.values());

		try {
			//File file = new File("/home/ves/users/admin/temp/fw_hb_config.txt");
			File file = new File("./src/main/java/evel_javalibrary/att/com/loadbalance/fw_hb_config.txt");
			list = Files.readAllLines(file.toPath(), Charset.defaultCharset());
			for (String lineSplit : list) {
				String[] res = lineSplit.split(" ");
				hb_config.put(res[0], res[1]);
//				System.out.println("File reading after split ---" + res[0]);
//				System.out.println("File reading after split second---" + res[1]);
			}
		} catch (Exception ex) {
			ex.printStackTrace();
		}
		System.out.println("KEYS:hb_config " + hb_config.keySet().size());
		System.out.println("VALUES:hb_config " + hb_config.values());
		return hb_config;
	}

	


}
