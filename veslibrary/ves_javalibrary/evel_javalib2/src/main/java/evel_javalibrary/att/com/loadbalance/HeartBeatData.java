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

import java.io.FileReader;
import java.io.IOException;
import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;


import evel_javalibrary.att.com.AgentMain;
import evel_javalibrary.att.com.EvelHeartbeatField;

import org.apache.log4j.Level;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;


public class HeartBeatData extends Thread{
	static HashMap<String, String> hbConfig = new HashMap();	
	static int  gm_event_id = 1;
	static String event_id1 = "heartbeatvfs";
	static String event_id = "00000000";
	static String event_id2=null;
	
	
	public void run() {
		
		Long start_epoch_microsec = 0L;
		Long last_epoch_microsec = 0L;
        String hostName = hostName();
		try {
		readHeartbeatConfig();
		}catch(Exception e) {			
		}
		while(true) {
		String heatBeatInterval="";
		long milliseconds = 60000;
		
		event_id2 = event_id1+ event_id+(gm_event_id++);	
		if(hbConfig.get("heartbeatInterval") == null) {
			heatBeatInterval = Long.toString(milliseconds);
		}else {
			heatBeatInterval = hbConfig.get("heartbeatInterval");
		}
		EvelHeartbeatField evelHb = new EvelHeartbeatField(Integer.parseInt(heatBeatInterval) ,
				hbConfig.get("eventName"),
                event_id2);
		
		if( hbConfig.get("eventType")!=null) {			
			start_epoch_microsec = last_epoch_microsec;
    	    last_epoch_microsec = System.nanoTime()/1000;
    		
    	    evelHb.evel_last_epoch_set(start_epoch_microsec);
    	    evelHb.evel_start_epoch_set(last_epoch_microsec);
		
		evelHb.evel_header_type_set(hbConfig.get("eventType").toString());
		evelHb.evel_nfcnamingcode_set(hbConfig.get("nfcNamingCode").toString());
		evelHb.evel_nfnamingcode_set(hbConfig.get("nfNamingCode").toString());
		if(hbConfig.get("reportingEntityName") == null) {
		evelHb.evel_reporting_entity_name_set(hostName);
		}else {
		evelHb.evel_reporting_entity_name_set(hbConfig.get("reportingEntityName").toString());
		}
		evelHb.evel_reporting_entity_id_set(hbConfig.get("reportingEntityId").toString());
		evelHb.evel_nfVendorName_set(hbConfig.get("nfVendorName").toString());
		evelHb.evel_header_set_sourceid(true,hbConfig.get("sourceId").toString());
		if(hbConfig.get("sourceName") == null) {
			evelHb.evel_header_set_source_name(hostName);
		}else {
			evelHb.evel_header_set_source_name(hbConfig.get("sourceName").toString());
		}				
		evelHb.evel_timeZoneOffset_set(hbConfig.get("timeZoneOffset").toString());
		
		}
		
		try {
			Thread.sleep(Integer.parseInt(heatBeatInterval));
			}catch(Exception e) {
				
			}
		AgentMain.evel_post_event(evelHb);
		}
	}
	
	
	public static HashMap<String, String> readHeartbeatConfig() throws IOException, ParseException {
		JSONParser jsonParser = new JSONParser();
		try {
			
			FileReader reader = new FileReader("./src/main/java/evel_javalibrary/att/com/loadbalance/hb_config.json");
			JSONObject obj = (JSONObject) jsonParser.parse(reader);
			Map.Entry pair = null;
			String convertObject ="";
			String[] res;
			Map directParameters = ((Map)obj.get("tmp_directParameters"));
			Iterator<Map.Entry> itr1 = directParameters.entrySet().iterator(); 
	        while (itr1.hasNext()) { 
	        	pair = itr1.next(); 
	            convertObject=String.valueOf(pair);  
	            res = convertObject.split("=");
				hbConfig.put(res[0], res[1]);	        
	        } 			
	        
			} catch (ClassCastException ex) {
			ex.printStackTrace();
		}
		return hbConfig;
	}

private final static char[] hexArray = "0123456789ABCDEF".toCharArray();	
private static String bytesToHex(byte[] bytes) {
	      char[] hexChars = new char[bytes.length * 2];
	      for ( int j = 0; j < bytes.length; j++ ) {
	          int v = bytes[j] & 0xFF;
	          hexChars[j * 2] = hexArray[v >>> 4];
	          hexChars[j * 2 + 1] = hexArray[v & 0x0F];
	      }
	      return new String(hexChars);
}

public static String hostName() {
    String hostname = "Unknown";
    String uuid = "Unknown";
    try
    {
        InetAddress addr;
        addr = InetAddress.getLocalHost();
        hostname = addr.getHostName();
    }
    catch (UnknownHostException ex)
    {
    }	    
    try{	    	
      Enumeration<NetworkInterface> networks =
            NetworkInterface.getNetworkInterfaces();
      while(networks.hasMoreElements()) {
        NetworkInterface network = networks.nextElement();
        byte[] mac = network.getHardwareAddress();
        
        if(hostname.equalsIgnoreCase("unknown"))
        {
            Enumeration inetAddrs = network.getInetAddresses();
            while(inetAddrs.hasMoreElements()){
            InetAddress inetAddr = (InetAddress) inetAddrs.nextElement();
            if (!inetAddr.isLoopbackAddress()) {
            	hostname = inetAddr.getHostAddress();
            	break;
            }
         }
        }
        if (mac != null) {
            uuid = bytesToHex(mac);
        }
      }
    } catch (SocketException e) {
		// TODO Auto-generated catch block
		
	}

	return hostname;
}
	
public static void main(String[] args) {
		// TODO Auto-generated method stub
        
		try {
            AgentMain.evel_initialize("http://127.0.0.1",30000,
                    null,null,
                    "will",
                    "pill",
                    null, null, null,
                    "http://127.0.0.1",30001, "will",
                    "pill",
                    Level.TRACE); 
		 }catch(Exception e) {
			 
			 return;
		 }
		HeartBeatData hbDataThread = new HeartBeatData();		
		hbDataThread.start();
	}

	

}
