package evel_javalibrary.att.com.loadbalance;

import java.io.BufferedReader;
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
import org.apache.log4j.Level;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;
import evel_javalibrary.att.com.AgentMain;
import evel_javalibrary.att.com.EvelFault;
import evel_javalibrary.att.com.EvelSyslog;
import evel_javalibrary.att.com.EvelSyslog.EVEL_SYSLOG_FACILITIES;

/**************************************************************************//**
 * @file
 * Syslog class
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

public class syslogData extends Thread{
	
	
	static HashMap<String, String> syslogConfig = new HashMap<>();
	static String[] interfaceDevice =null;
	
	static String syslogInterval="";
	static String syslogFile ="";
	static String tempCommand = "";	
	static int  gmEventId = 1;
	static String eventId1 = "syslog";
	static String eventId = "00000000";
	static String eventId2=null;
	
	private static int linesReadFromFile =0;
	
	public void run() {
		try {
			readSyslogConfig();
			
		} catch (IOException | ParseException e) {}
		
		while(true) {
			String tagToCompare = syslogConfig.get("syslogTag").toString();
			
			syslogFileRead(tagToCompare );
		
			try { Thread.sleep(500);}catch(Exception e) {}

		}
	}
	

	public void sendSysLogEvent(String sysTag,String syslogMsg) {
		Long start_epoch_microsec = 0L;
		Long last_epoch_microsec = 0L;
		String hostName = hostName();
		
		eventId2 = eventId1+ eventId+(gmEventId++);
		EvelSyslog eveSyslog  = new EvelSyslog(syslogConfig.get("eventName"), 
				eventId2, EvelFault.EVEL_SOURCE_TYPES.EVEL_SOURCE_VIRTUAL_MACHINE, 
				syslogMsg, sysTag);
					
		if( syslogConfig.get("eventType")!=null) {			
			start_epoch_microsec = last_epoch_microsec;
    	    last_epoch_microsec = System.nanoTime()/1000;
    		
    	    eveSyslog.evel_last_epoch_set(start_epoch_microsec);
    	    eveSyslog.evel_start_epoch_set(last_epoch_microsec);
		
    	    eveSyslog.evel_header_type_set(syslogConfig.get("eventType").toString());
    	    eveSyslog.evel_nfcnamingcode_set(syslogConfig.get("nfcNamingCode").toString());
    	    eveSyslog.evel_nfnamingcode_set(syslogConfig.get("nfNamingCode").toString());
		if(syslogConfig.get("reportingEntityName") == null) {
			eveSyslog.evel_reporting_entity_name_set(hostName);
		}else {
			eveSyslog.evel_reporting_entity_name_set(syslogConfig.get("reportingEntityName").toString());
		}
		eveSyslog.evel_reporting_entity_id_set(syslogConfig.get("reportingEntityId").toString());
//		eveSyslog.evel_nfVendorName_set(syslogConfig.get("nfVendorName").toString());
		eveSyslog.evel_header_set_sourceid(true,syslogConfig.get("sourceId").toString());
		if(syslogConfig.get("sourceName") == null) {
			eveSyslog.evel_header_set_source_name(hostName);
		}else {
			eveSyslog.evel_header_set_source_name(syslogConfig.get("sourceName").toString());
		}				
//		eveSyslog.evel_timeZoneOffset_set(syslogConfig.get("timeZoneOffset").toString());
		}
		
		eveSyslog.evel_syslog_facility_set(EVEL_SYSLOG_FACILITIES.EVEL_SYSLOG_FACILITY_LOCAL0);
		eveSyslog.evel_syslog_proc_set(syslogConfig.get("syslogProc").toString());			

		
		
		AgentMain.evel_post_event(eveSyslog);

	}
	
	public  String syslogFileRead(String tagToCompare){		
		String syslines ="";
		int currentIndex = 0;
		boolean compare = false;
		
	        try {
	        	
	        	BufferedReader reader = new BufferedReader(new FileReader("/var/log/syslog"));
				String line = reader.readLine();
				while (line != null) {
					if( currentIndex == linesReadFromFile ) {
						compare=true;
					}
					if( compare ) {
						if( line.contains(tagToCompare) )
							sendSysLogEvent( tagToCompare, line);
					}
					currentIndex ++;					
					
					line = reader.readLine();
				}
				
				if( compare )
				linesReadFromFile=currentIndex;
	        	
	        	
	        } catch (Exception ex) {
	           ex.printStackTrace();
	        } 
	        
	  return null;
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
			e.printStackTrace();
		}

		return hostname;
	}

	
	public static HashMap<String, String> readSyslogConfig() throws IOException, ParseException {

		JSONParser jsonParser = new JSONParser();
		try {
			
			FileReader reader = new FileReader("./src/main/java/evel_javalibrary/att/com/loadbalance/syslog_config.json");
			JSONObject obj = (JSONObject) jsonParser.parse(reader);
			Map.Entry directPair = null;
			String directObject ="";
			String[] directres;
			Map directParameters = ((Map)obj.get("tmp_directParameters"));
			Iterator<Map.Entry> itr1 = directParameters.entrySet().iterator(); 
	        while (itr1.hasNext()) { 
	        	directPair = itr1.next(); 
	        	directObject=String.valueOf(directPair);  
	        	directres = directObject.split("=");
	        	syslogConfig.put(directres[0], directres[1]);	        

	        } 		
	        //tmp_indirectParameters
	        Map.Entry indirectPair = null;
	        String indirectObject ="";
	        String[] indirectres;
			Map indirectParameters = ((Map)obj.get("tmp_indirectParameters"));
			Iterator<Map.Entry> itr2 = indirectParameters.entrySet().iterator(); 
	        while (itr2.hasNext()) { 
	        	indirectPair = itr2.next(); 
	        	indirectObject=String.valueOf(indirectPair);  
	        	indirectres = indirectObject.split("=");
	        	syslogConfig.put(indirectres[0], indirectres[1]);	        
	        } 	
	        syslogFile =      syslogConfig.get("tmp_syslogFile").toString();
			} catch (ClassCastException ex) {
			ex.printStackTrace();
		}
		return syslogConfig;
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
			 e.printStackTrace();
			 return;
		 }
		syslogData syslogDataThread = new syslogData();		
		syslogDataThread.start();
	}




}
