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

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;


import org.apache.log4j.Level;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

import evel_javalibrary.att.com.AgentMain;
import evel_javalibrary.att.com.EvelBatch;
import evel_javalibrary.att.com.EvelFault;
import evel_javalibrary.att.com.EvelFault.EVEL_SEVERITIES;
import evel_javalibrary.att.com.EvelFault.EVEL_SOURCE_TYPES;
import evel_javalibrary.att.com.EvelFault.EVEL_VF_STATUSES;
import evel_javalibrary.att.com.EvelHeader;



public class FaultData{
	
	
	static HashMap<String, String> fault_config = new HashMap<>();
	static HashMap<String, String> interface_config = new HashMap<>();
	
	static HashMap<String, String> faultConfig = new HashMap<>();
	
	static HashMap<String, String> faultInstanceres01 = new HashMap<>();
	static HashMap<String, String> faultInstanceres02 = new HashMap<>();
	static HashMap<String, String> tempAlaramClearParameter = new HashMap<>();
	
	
	static HashMap<String, String> Instanceres02ClearParameter = new HashMap<>();
	
	
	static String[] resDevice =null;
	static String[] tempInitres;
	static String[] tempcommandres;
	static String[] tempcommand02res;
	static HashMap<String, String> faultConfigTempInit = new HashMap<>();
	static HashMap<String, String> faultConfigCommand = new HashMap<>();
	static String alarmCondition ="";
	static String specificProblem = "";
	static String eventSeverity="";
	static String alarmInterfaceA ="";
	
	static String alarmConditionClear ="";
	static String specificProblemClear = "";
	static String eventSeverityClear="";
	
	static String Instance02alarmInterfaceA;  
	static String Instance02eventCategory;  
	static String Instance02eventSourceType;    
	static String Instance02eventName;  
	
	static String  ins02alarmConditionClear;
	static String  ins02specificProblemClear;
	static String  ins02eventSeverityClear; 

	static String  setAlarmCondition;
	static String  setSpecificProblem;
	static String  setEventSeverity;
	
	static String eventCategory ="";
	static String eventSourceType ="";
	static HashMap<String, String> hm = new HashMap<>();
	
	static String linkStart = "";
	static int linkCount; 
	static String event_id1 = "fault";
	static String event_id = "00000000";
	static float bytes_in;
	static float bytes_out;
	static float packets_in;
	static float packets_out;
	
	static float ins02Cmd;
	
	
	static int falut_raised =0;

	
	public final Runnable faultInstance01;
	public final Runnable faultInstance02;
	
	public FaultData(){
		
		faultInstance01 = new Runnable() {
			
			@Override
			public void run() {
				 int  gm_event_id = 1;
				  String event_id2=null;
				
				Long start_epoch_microsec = 0L;
				Long last_epoch_microsec = 0L;
				String hostName = hostName();
				try {
					readFalutConfig();		
					readVppMetrics(resDevice);						
				} catch (IOException | ParseException e1) {

				}		
				
				
				String[] intFaceMapFault = resDevice;		
				int numOfInterfacesFalut = 0;
				if( intFaceMapFault != null)
					numOfInterfacesFalut = intFaceMapFault.length;		
				if( numOfInterfacesFalut <= 0) {
					
					return;
				}				
				
				HashMap<String, DeviceData> falut_last_metrics = readVppMetrics(resDevice);		
				
				while(true) {
					try {				
					EvelBatch ebt = new EvelBatch();
				
					for( String falut : intFaceMapFault ) {				
					    
						HashMap<String, DeviceData> falut_current_metrics = readVppMetrics(resDevice);

						
						for( String tmp_device :falut_current_metrics.keySet() ) {
						
						
							
							int receivedOctetsDelta = Integer.parseInt((falut_current_metrics.get(tmp_device).getT1Bytesin()) )
									- Integer.parseInt((falut_last_metrics.get(tmp_device).getT0bytesIn()));
							
							int receivedTotalPacketsDelta = Integer.parseInt((falut_current_metrics.get(tmp_device).getT1Packetsin()) )
									- Integer.parseInt((falut_last_metrics.get(tmp_device).getT0packetIn()));
							
							int transmittedOctetsDelta = Integer.parseInt((falut_current_metrics.get(tmp_device).getT1Bytesout()) )
							- Integer.parseInt((falut_last_metrics.get(tmp_device).getT0bytesOut()));
							
							
							
							int transmittedTotalPacketsDelta = Integer.parseInt((falut_current_metrics.get(tmp_device).getT1Packetsout()) )
							- Integer.parseInt((falut_last_metrics.get(tmp_device).getT0packetOut()));
							
						
						String alarmInterface = tmp_device; //resDevice[0];
						if((receivedOctetsDelta < Integer.parseInt((String)faultInstanceres01.get("tmp_lowWaterMark")) || transmittedOctetsDelta < Integer.parseInt((String)faultInstanceres01.get("tmp_lowWaterMark")) || 
								receivedTotalPacketsDelta < Integer.parseInt((String)faultInstanceres01.get("tmp_lowWaterMark")) || transmittedTotalPacketsDelta < Integer.parseInt((String)faultInstanceres01.get("tmp_lowWaterMark"))) && falut_raised == 0){
							event_id2 = event_id1+ event_id+(gm_event_id++);
							EvelFault eveFalt  = new EvelFault(faultInstanceres01.get("eventName"),event_id2, alarmCondition, specificProblem,
				                    EvelHeader.PRIORITIES.EVEL_PRIORITY_LOW,
				                    EVEL_SEVERITIES.EVEL_SEVERITY_MAJOR,
				                    EVEL_SOURCE_TYPES.EVEL_SOURCE_ROUTER,
				                    EVEL_VF_STATUSES.EVEL_VF_STATUS_IDLE);
		                    if(eveFalt != null) {
		                    	
		                    	falut_raised =1;
		                    	
		                    	if( faultConfig.get("eventType")!=null) {
		                    		eveFalt.evel_fault_type_set(faultConfig.get("eventType"));
		                    		
		                    		start_epoch_microsec = last_epoch_microsec;
		                    	    last_epoch_microsec = System.nanoTime()/1000;
		                    		
		                    		eveFalt.evel_last_epoch_set(start_epoch_microsec);
		                    		eveFalt.evel_start_epoch_set(last_epoch_microsec);
		                    		
		                    		eveFalt.evel_fault_category_set(eventCategory);
		                    		eveFalt.evel_fault_interface_set(alarmInterface.replaceAll("^[\"']+|[\"']+$", ""));
		                    		eveFalt.evel_nfcnamingcode_set(faultConfig.get("nfcNamingCode").toString());
		                    		eveFalt.evel_nfnamingcode_set(faultConfig.get("nfNamingCode").toString());
		                    		if(faultConfig.get("reportingEntityName") == null) {
		                    			eveFalt.evel_reporting_entity_name_set(hostName);
		                    			}else {
		                    			eveFalt.evel_reporting_entity_name_set(faultConfig.get("reportingEntityName").toString());
		                    			}		                   		
		        					eveFalt.evel_reporting_entity_id_set(faultConfig.get("reportingEntityId").toString());
		        					eveFalt.evel_nfVendorName_set(faultConfig.get("nfVendorName").toString());
		        					eveFalt.evel_header_set_sourceid(true,faultConfig.get("sourceId").toString()); 
		        					
		        		     		if(faultConfig.get("sourceName") == null) {
		        		     			eveFalt.evel_header_set_source_name(hostName);
		                    			}else {
		                    				eveFalt.evel_header_set_source_name(faultConfig.get("sourceName").toString());
		                    			}			        					
		        							
		        					eveFalt.evel_timeZoneOffset_set(faultConfig.get("timeZoneOffset").toString());
		        					AgentMain.evel_post_event(eveFalt);		
		                    	}
		                    	
		                    }
						
						}else if((receivedOctetsDelta > Integer.parseInt((String)faultInstanceres01.get("tmp_lowWaterMark")) && transmittedOctetsDelta > Integer.parseInt((String)faultInstanceres01.get("tmp_lowWaterMark")) && 
								receivedTotalPacketsDelta > Integer.parseInt((String)faultInstanceres01.get("tmp_lowWaterMark")) && transmittedTotalPacketsDelta > Integer.parseInt((String)faultInstanceres01.get("tmp_lowWaterMark"))) && falut_raised == 1) {							
							
							event_id2 = event_id1+event_id+ (gm_event_id++);
							EvelFault eveFalt  = new EvelFault(faultInstanceres01.get("eventName"),event_id2, alarmConditionClear, specificProblemClear,
				                    EvelHeader.PRIORITIES.EVEL_PRIORITY_LOW,
				                    EVEL_SEVERITIES.EVEL_SEVERITY_NORMAL,
				                    EVEL_SOURCE_TYPES.EVEL_SOURCE_ROUTER,
				                    EVEL_VF_STATUSES.EVEL_VF_STATUS_IDLE);

							
							
		                    if(eveFalt != null) {
		                    	falut_raised =1;
		                    	
		                    	if( faultConfig.get("eventType")!=null) {
		                    		eveFalt.evel_fault_type_set(faultConfig.get("eventType"));                    		
		                    		eveFalt.evel_fault_category_set(eventCategory);
		                    		eveFalt.evel_fault_interface_set(alarmInterface.replaceAll("^[\"']+|[\"']+$", ""));
		                    		                    		
		                    		eveFalt.evel_nfcnamingcode_set(faultConfig.get("nfcNamingCode").toString());
		                    		eveFalt.evel_nfnamingcode_set(faultConfig.get("nfNamingCode").toString());
		                    		
		                    		if(faultConfig.get("reportingEntityName") == null) {
		                    			eveFalt.evel_reporting_entity_name_set(hostName);
		                    			}else {
		                    			eveFalt.evel_reporting_entity_name_set(faultConfig.get("reportingEntityName").toString());
		                    			}	
		                    		
		                    		
		        					eveFalt.evel_reporting_entity_id_set(faultConfig.get("reportingEntityId").toString());
		        					eveFalt.evel_nfVendorName_set(faultConfig.get("nfVendorName").toString());
		        					eveFalt.evel_header_set_sourceid(true,faultConfig.get("sourceId").toString());
		        					
		        		     		if(faultConfig.get("sourceName") == null) {
		        		     			eveFalt.evel_header_set_source_name(hostName);
		                    			}else {
		                    				eveFalt.evel_header_set_source_name(faultConfig.get("sourceName").toString());
		                    			}		
		        					
		        							
		        					eveFalt.evel_timeZoneOffset_set(faultConfig.get("timeZoneOffset").toString());
		        					AgentMain.evel_post_event(eveFalt);		
		                    		
		                    	}
		                    	
		                    }

							
							
						}
						
						
					try {
						String Ins01Interval="";
						long milliseconds = 60000;
						if(faultInstanceres01.get("tmp_faultCheckInterval") == null) {
							Ins01Interval = Long.toString(milliseconds);
						}else {
							Ins01Interval = faultInstanceres01.get("tmp_faultCheckInterval");
						}
					Thread.sleep(Integer.parseInt(Ins01Interval));
					}catch(Exception e) {}
					
					} //for map keyset
					
					} //for intFaceMapFault 
					
					
					}catch (Exception e) {
						
					}
					
					
				}
			}
		};
		
		faultInstance02 = new Runnable() {
			
			@Override
			public void run() {
				 int  gm_event_id = 1;
				  String event_id2=null;
				Long start_epoch_microsec = 0L;
				Long last_epoch_microsec = 0L;
				String hostName = hostName();
				try {
					readFalutConfig();		
					readVppMetrics(resDevice);						
				} catch (IOException | ParseException e1) {

				}		
				
				
				String[] intFaceMapFault = resDevice;		
				int numOfInterfacesFalut = 0;
				if( intFaceMapFault != null)
					numOfInterfacesFalut = intFaceMapFault.length;		
				if( numOfInterfacesFalut <= 0) {
					
					return;
				}				
				
				HashMap<String, DeviceData> falut_last_metrics = readVppMetrics(resDevice);		
				
				while(true) {
					try {				
					EvelBatch ebt = new EvelBatch();
					
					HashMap<String, DeviceData> falutMetric = readVppMetrics(resDevice);
					DeviceData mdGetdata = new DeviceData();
					String ins02cmd = mdGetdata.getInstanceres02Command();
					
					
						if(ins02Cmd < Integer.parseInt((String)falutMetric.get("Instanceres02Cmd").getInstanceres02Command())){					
							
							event_id2 = event_id1+ event_id+(gm_event_id++);
							EvelFault eveFalt  = new EvelFault(Instance02eventName,event_id2, setAlarmCondition, setSpecificProblem,
				                    EvelHeader.PRIORITIES.EVEL_PRIORITY_LOW,
				                    EVEL_SEVERITIES.EVEL_SEVERITY_MAJOR,
				                    EVEL_SOURCE_TYPES.EVEL_SOURCE_VIRTUAL_MACHINE,
				                    EVEL_VF_STATUSES.EVEL_VF_STATUS_IDLE);

			
		                    if(eveFalt != null) {
		                    	
		                    	falut_raised =1;
		                    	
		                    	
		                    	
		                    	if( faultConfig.get("eventType")!=null) {
		                    		eveFalt.evel_fault_type_set(faultConfig.get("eventType"));
		                    		
		                    		start_epoch_microsec = last_epoch_microsec;
		                    	    last_epoch_microsec = System.nanoTime()/1000;
		                    		
		                    		eveFalt.evel_last_epoch_set(start_epoch_microsec);
		                    		eveFalt.evel_start_epoch_set(last_epoch_microsec);
		                    		
		                    		eveFalt.evel_fault_category_set(Instance02eventCategory);
		                    		eveFalt.evel_fault_interface_set(Instance02alarmInterfaceA.replaceAll("^[\"']+|[\"']+$", ""));
		                    		
		                    		eveFalt.evel_nfcnamingcode_set(faultConfig.get("nfcNamingCode").toString());
		                    		eveFalt.evel_nfnamingcode_set(faultConfig.get("nfNamingCode").toString());
		                    		
		                    		if(faultConfig.get("reportingEntityName") == null) {
		                    			eveFalt.evel_reporting_entity_name_set(hostName);
		                    			}else {
		                    			eveFalt.evel_reporting_entity_name_set(faultConfig.get("reportingEntityName").toString());
		                    			}	
		                    		
		                    		
		        					eveFalt.evel_reporting_entity_id_set(faultConfig.get("reportingEntityId").toString());
		        					eveFalt.evel_nfVendorName_set(faultConfig.get("nfVendorName").toString());
		        					eveFalt.evel_header_set_sourceid(true,faultConfig.get("sourceId").toString()); 
		        					
		        		     		if(faultConfig.get("sourceName") == null) {
		        		     			eveFalt.evel_header_set_source_name(hostName);
		                    			}else {
		                    				eveFalt.evel_header_set_source_name(faultConfig.get("sourceName").toString());
		                    			}		
		        							
		        					eveFalt.evel_timeZoneOffset_set(faultConfig.get("timeZoneOffset").toString());
		        					AgentMain.evel_post_event(eveFalt);		
		                    	}
		                    	
		                    }
						
						}else if(ins02Cmd > Integer.parseInt((String)falutMetric.get("Instanceres02Cmd").getInstanceres02Command())) {
							
							
							event_id2 = event_id1+ event_id+(gm_event_id++);
							EvelFault eveFalt  = new EvelFault(Instance02eventName,event_id2, ins02alarmConditionClear, ins02specificProblemClear,
				                    EvelHeader.PRIORITIES.EVEL_PRIORITY_LOW,
				                    EVEL_SEVERITIES.EVEL_SEVERITY_NORMAL,
				                    EVEL_SOURCE_TYPES.EVEL_SOURCE_VIRTUAL_MACHINE,
				                    EVEL_VF_STATUSES.EVEL_VF_STATUS_IDLE);

							
							
		                    if(eveFalt != null) {
		                    	falut_raised =1;
		   
		                    	if( faultConfig.get("eventType")!=null) {
		                    		eveFalt.evel_fault_type_set(faultConfig.get("eventType"));                    		
		                    		eveFalt.evel_fault_category_set(Instance02eventCategory);
		                    		eveFalt.evel_fault_interface_set(Instance02alarmInterfaceA.replaceAll("^[\"']+|[\"']+$", ""));
		                    		                    		
		                    		eveFalt.evel_nfcnamingcode_set(faultConfig.get("nfcNamingCode").toString());
		                    		eveFalt.evel_nfnamingcode_set(faultConfig.get("nfNamingCode").toString());
		                    		
		                    		if(faultConfig.get("reportingEntityName") == null) {
		                    			eveFalt.evel_reporting_entity_name_set(hostName);
		                    			}else {
		                    			eveFalt.evel_reporting_entity_name_set(faultConfig.get("reportingEntityName").toString());
		                    			}	
		                    		
		                    		
		        					eveFalt.evel_reporting_entity_id_set(faultConfig.get("reportingEntityId").toString());
		        					eveFalt.evel_nfVendorName_set(faultConfig.get("nfVendorName").toString());
		        					eveFalt.evel_header_set_sourceid(true,faultConfig.get("sourceId").toString());
		        					
		        		     		if(faultConfig.get("sourceName") == null) {
		        		     			eveFalt.evel_header_set_source_name(hostName);
		                    			}else {
		                    				eveFalt.evel_header_set_source_name(faultConfig.get("sourceName").toString());
		                    			}		
		        					
		        							
		        					eveFalt.evel_timeZoneOffset_set(faultConfig.get("timeZoneOffset").toString());
		        					AgentMain.evel_post_event(eveFalt);		
		                    		
		                    	}
		                    	
		                    }

							
							
						}
						
						
					try {
						String Ins02Interval="";
						long milliseconds = 60000;
						if(faultInstanceres02.get("tmp_faultCheckInterval") == null) {
							Ins02Interval = Long.toString(milliseconds);
						}else {
							Ins02Interval = faultInstanceres02.get("tmp_faultCheckInterval");
						}
					Thread.sleep(Integer.parseInt(Ins02Interval));					
					}catch(Exception e) {
						
					}
					
					}catch (Exception e) {
						
					}
					
					
				}
			}
		};
		
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
	
	
	
	public static HashMap<String, String> readFalutConfig() throws IOException, ParseException {
		
		System.out.println("readFalutConfig calling out lo:");
		
		List<String> list = new ArrayList<String>();
		JSONParser jsonParser = new JSONParser();
		try {
			
			FileReader reader = new FileReader("./src/main/java/evel_javalibrary/att/com/loadbalance/flt_config.json");
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
	            faultConfig.put(directres[0], directres[1]);	        
	        } 		
	        JSONArray arrJson = (JSONArray) directParameters.get("tmp_device");
	        resDevice = new String[arrJson.size()];
	        for(int i = 0; i < arrJson.size(); i++)
	        	resDevice[i] = (String) arrJson.get(i);
	        
	        
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
	            faultConfig.put(indirectres[0], indirectres[1]);	        
	        } 	
	        
	        
	        //tmp_faultInstance01
	        Map.Entry faultInstancePair = null;
	        String faultInstanceObject ="";
	        String[] faultInstanceres;
			Map faultInstanceParameters = ((Map)indirectParameters.get("tmp_faultInstance01"));
			Iterator<Map.Entry> itr3 = faultInstanceParameters.entrySet().iterator(); 
	        while (itr3.hasNext()) { 
	        	faultInstancePair = itr3.next(); 
	        	faultInstanceObject=String.valueOf(faultInstancePair);  
	        	faultInstanceres = faultInstanceObject.split("=");
	        	faultInstanceres01.put(faultInstanceres[0], faultInstanceres[1]);	        
	        } 
	        
	         
	        eventCategory = faultInstanceres01.get("eventCategory").toString();
	        eventSourceType = faultInstanceres01.get("eventSourceType").toString();
	        //tmp_init
	        Map.Entry tempInitPair = null;
	        String tempInitObject ="";
			Map tempInitParameters = ((Map)faultInstanceParameters.get("tmp_init"));
			Iterator<Map.Entry> itr4 = tempInitParameters.entrySet().iterator(); 
	        while (itr4.hasNext()) { 
	        	tempInitPair = itr4.next(); 
	        	tempInitObject=String.valueOf(tempInitPair);  
	        	tempInitres = tempInitObject.split("=");
	        	faultConfigTempInit.put(tempInitres[0], tempInitres[1]);	        
	        } 	
	        
	        String tmp_t0BytesOut = faultConfigTempInit.get("tmp_init");
	        
	        
	        
	        //tmp_command
	        Map.Entry tempcommandPair = null;
	        String tempcommandObject ="";	        
			Map tempcommandParameters = ((Map)faultInstanceParameters.get("tmp_command"));
			Iterator<Map.Entry> itr5 = tempcommandParameters.entrySet().iterator(); 
	        while (itr5.hasNext()) { 
	        	tempcommandPair = itr5.next(); 
	        	tempcommandObject=String.valueOf(tempcommandPair);  
	        	tempcommandres = tempcommandObject.split("=");
	            faultConfigCommand.put(tempcommandres[0], tempcommandres[1]);	        
	        } 	
	        
	        //tmp_alarmSetParameters
	        Map.Entry alarmSetPair = null;
	        String alarmSetObject ="";
	        String[] alarmSetres;
			Map alarmSetParameters = ((Map)faultInstanceParameters.get("tmp_alarmSetParameters"));
			Iterator<Map.Entry> itr6 = alarmSetParameters.entrySet().iterator(); 
	        while (itr6.hasNext()) { 
	        	alarmSetPair = itr6.next(); 
	        	alarmSetObject=String.valueOf(alarmSetPair);  
	        	alarmSetres = alarmSetObject.split("=");
	            faultConfig.put(alarmSetres[0], alarmSetres[1]);	        
	        } 	
	        
	        
	        alarmCondition = faultConfig.get("alarmCondition").toString();
	        specificProblem = faultConfig.get("specificProblem").toString();
	        eventSeverity =   faultConfig.get("eventSeverity").toString();
	        
	        //tmp_alarmClearParameters
	        Map.Entry alarmClearPair = null;
	        String alarmClearObject ="";
	        String[] alarmClearres;
			Map alarmClearParameters = ((Map)faultInstanceParameters.get("tmp_alarmClearParameters"));
			Iterator<Map.Entry> itr7 = alarmClearParameters.entrySet().iterator(); 
	        while (itr7.hasNext()) { 
	        	alarmClearPair = itr7.next(); 
	        	alarmClearObject=String.valueOf(alarmClearPair);  
	        	alarmClearres = alarmClearObject.split("=");
	            tempAlaramClearParameter.put(alarmClearres[0], alarmClearres[1]);	        
	        } 	
	        
	        alarmConditionClear = tempAlaramClearParameter.get("alarmCondition").toString();
	        specificProblemClear = tempAlaramClearParameter.get("specificProblem").toString();
	        eventSeverityClear =   tempAlaramClearParameter.get("eventSeverity").toString();
	        System.out.println("specificProblemClear data:"+ specificProblemClear);
	        
	        //tmp_faultInstance02
	        Map.Entry faultInstance02Pair = null;
	        String faultInstance02Object ="";
	        String[] faultInstance02res;
			Map faultInstance02Parameters = ((Map)indirectParameters.get("tmp_faultInstance02"));
			Iterator<Map.Entry> itr8 = faultInstance02Parameters.entrySet().iterator(); 
	        while (itr8.hasNext()) { 
	        	faultInstance02Pair = itr8.next(); 
	        	faultInstance02Object=String.valueOf(faultInstance02Pair);  
	        	faultInstance02res = faultInstance02Object.split("=");
	        	faultInstanceres02.put(faultInstance02res[0], faultInstance02res[1]);	        
	        } 	
	        Instance02alarmInterfaceA  = faultInstanceres02.get("alarmInterfaceA");
	        Instance02eventCategory  = faultInstanceres02.get("eventCategory");
	        Instance02eventSourceType  = faultInstanceres02.get("eventSourceType");
	        Instance02eventName  = faultInstanceres02.get("eventName");
	        
	        //tmp_command
	        Map.Entry tempcommand02Pair = null;
	        String tempcommand02Object ="";	        
			Map tempcommand02Parameters = ((Map)faultInstance02Parameters.get("tmp_command"));
			Iterator<Map.Entry> itr9 = tempcommand02Parameters.entrySet().iterator(); 
	        while (itr9.hasNext()) { 
	        	tempcommand02Pair = itr9.next(); 
	        	tempcommand02Object=String.valueOf(tempcommand02Pair);  
	        	tempcommand02res = tempcommand02Object.split("=");
	        	faultInstanceres02.put(tempcommand02res[0], tempcommand02res[1]);	        
	        } 	
	        
	        
	        
	        //tmp_alarmSetParameters
	        Map.Entry Instance02alarmSetPair = null;
	        String Instance02alarmSetObject ="";
	        String[] Instance02alarmSetres;
			Map Instance02alarmSetParameters = ((Map)faultInstance02Parameters.get("tmp_alarmSetParameters"));
			Iterator<Map.Entry> itr10 = Instance02alarmSetParameters.entrySet().iterator(); 
	        while (itr10.hasNext()) { 
	        	Instance02alarmSetPair = itr10.next(); 
	        	Instance02alarmSetObject=String.valueOf(Instance02alarmSetPair);  
	        	Instance02alarmSetres = Instance02alarmSetObject.split("=");
	        	faultInstanceres02.put(Instance02alarmSetres[0], Instance02alarmSetres[1]);	        
	        } 	
	        
	        
	        setAlarmCondition = faultInstanceres02.get("alarmCondition").toString();
	        setSpecificProblem = faultInstanceres02.get("specificProblem").toString();
	        setEventSeverity =   faultInstanceres02.get("eventSeverity").toString();
	        
	        //tmp_alarmClearParameters
	        Map.Entry Instanceres02alarmClearPair = null;
	        String Instanceres02alarmClearObject ="";
	        String[] Instanceres02alarmClearres;
			Map Instanceres02alarmClearParameters = ((Map)faultInstance02Parameters.get("tmp_alarmClearParameters"));
			Iterator<Map.Entry> itr11 = Instanceres02alarmClearParameters.entrySet().iterator(); 
	        while (itr11.hasNext()) { 
	        	Instanceres02alarmClearPair = itr11.next(); 
	        	Instanceres02alarmClearObject=String.valueOf(Instanceres02alarmClearPair);  
	        	Instanceres02alarmClearres = Instanceres02alarmClearObject.split("=");
	        	Instanceres02ClearParameter.put(Instanceres02alarmClearres[0], Instanceres02alarmClearres[1]);	        
	        } 	
	        
	        ins02alarmConditionClear = Instanceres02ClearParameter.get("alarmCondition").toString();
	        ins02specificProblemClear = Instanceres02ClearParameter.get("specificProblem").toString();
	        ins02eventSeverityClear =   Instanceres02ClearParameter.get("eventSeverity").toString();
	        

	        	        
	        
			} catch (ClassCastException ex) {
			ex.printStackTrace();
		}
		return faultConfig;
	}



	
	public static HashMap<String, String> readFalutConfig1() throws IOException, ParseException {
		List<String> list = new ArrayList<String>();
		JSONParser jsonParser = new JSONParser();
		try {
			
			FileReader reader = new FileReader("./src/main/java/evel_javalibrary/att/com/loadbalance/flt_config.json");
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
	            faultConfig.put(directres[0], directres[1]);	        
	        } 		
	        JSONArray arrJson = (JSONArray) directParameters.get("tmp_device");
	        resDevice = new String[arrJson.size()];
	        for(int i = 0; i < arrJson.size(); i++)
	        	resDevice[i] = (String) arrJson.get(i);
	        
	        
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
	            faultConfig.put(indirectres[0], indirectres[1]);	        
	        } 	
	        
	        
	        //tmp_faultInstance01
	        Map.Entry faultInstancePair = null;
	        String faultInstanceObject ="";
	        String[] faultInstanceres;
			Map faultInstanceParameters = ((Map)indirectParameters.get("tmp_faultInstance01"));
			Iterator<Map.Entry> itr3 = faultInstanceParameters.entrySet().iterator(); 
	        while (itr3.hasNext()) { 
	        	faultInstancePair = itr3.next(); 
	        	faultInstanceObject=String.valueOf(faultInstancePair);  
	        	faultInstanceres = faultInstanceObject.split("=");
	        	faultInstanceres01.put(faultInstanceres[0], faultInstanceres[1]);	        
	        } 
	        
	         
	        eventCategory = faultInstanceres01.get("eventCategory").toString();
	        eventSourceType = faultInstanceres01.get("eventSourceType").toString();
	        //tmp_init
	        Map.Entry tempInitPair = null;
	        String tempInitObject ="";
			Map tempInitParameters = ((Map)faultInstanceParameters.get("tmp_init"));
			Iterator<Map.Entry> itr4 = tempInitParameters.entrySet().iterator(); 
	        while (itr4.hasNext()) { 
	        	tempInitPair = itr4.next(); 
	        	tempInitObject=String.valueOf(tempInitPair);  
	        	tempInitres = tempInitObject.split("=");
	        	faultConfigTempInit.put(tempInitres[0], tempInitres[1]);	        
	        } 	
	        
	        String tmp_t0BytesOut = faultConfigTempInit.get("tmp_init");
	        
	        
	        
	        //tmp_command
	        Map.Entry tempcommandPair = null;
	        String tempcommandObject ="";	        
			Map tempcommandParameters = ((Map)faultInstanceParameters.get("tmp_command"));
			Iterator<Map.Entry> itr5 = tempcommandParameters.entrySet().iterator(); 
	        while (itr5.hasNext()) { 
	        	tempcommandPair = itr5.next(); 
	        	tempcommandObject=String.valueOf(tempcommandPair);  
	        	tempcommandres = tempcommandObject.split("=");
	            faultConfig.put(tempcommandres[0], tempcommandres[1]);	        
	        } 	
	        
	        //tmp_alarmSetParameters
	        Map.Entry alarmSetPair = null;
	        String alarmSetObject ="";
	        String[] alarmSetres;
			Map alarmSetParameters = ((Map)faultInstanceParameters.get("tmp_alarmSetParameters"));
			Iterator<Map.Entry> itr6 = alarmSetParameters.entrySet().iterator(); 
	        while (itr6.hasNext()) { 
	        	alarmSetPair = itr6.next(); 
	        	alarmSetObject=String.valueOf(alarmSetPair);  
	        	alarmSetres = alarmSetObject.split("=");
	            faultConfig.put(alarmSetres[0], alarmSetres[1]);	        
	        } 	
	        
	        
	        alarmCondition = faultConfig.get("alarmCondition").toString();
	        specificProblem = faultConfig.get("specificProblem").toString();
	        eventSeverity =   faultConfig.get("eventSeverity").toString();
	        
	        //tmp_alarmClearParameters
	        Map.Entry alarmClearPair = null;
	        String alarmClearObject ="";
	        String[] alarmClearres;
			Map alarmClearParameters = ((Map)faultInstanceParameters.get("tmp_alarmClearParameters"));
			Iterator<Map.Entry> itr7 = alarmClearParameters.entrySet().iterator(); 
	        while (itr7.hasNext()) { 
	        	alarmClearPair = itr7.next(); 
	        	alarmClearObject=String.valueOf(alarmClearPair);  
	        	alarmClearres = alarmClearObject.split("=");
	            tempAlaramClearParameter.put(alarmClearres[0], alarmClearres[1]);	        
	        } 	
	        
	        alarmConditionClear = tempAlaramClearParameter.get("alarmCondition").toString();
	        specificProblemClear = tempAlaramClearParameter.get("specificProblem").toString();
	        eventSeverityClear =   tempAlaramClearParameter.get("eventSeverity").toString();
	        
	        
	        //tmp_faultInstance02
	        Map.Entry faultInstance02Pair = null;
	        String faultInstance02Object ="";
	        String[] faultInstance02res;
			Map faultInstance02Parameters = ((Map)indirectParameters.get("tmp_faultInstance02"));
			Iterator<Map.Entry> itr8 = faultInstance02Parameters.entrySet().iterator(); 
	        while (itr8.hasNext()) { 
	        	faultInstance02Pair = itr8.next(); 
	        	faultInstance02Object=String.valueOf(faultInstance02Pair);  
	        	faultInstance02res = faultInstance02Object.split("=");
	        	faultInstanceres02.put(faultInstance02res[0], faultInstance02res[1]);	        
	        } 	
	        Instance02alarmInterfaceA  = faultInstanceres02.get("alarmInterfaceA");
	        Instance02eventCategory  = faultInstanceres02.get("eventCategory");
	        Instance02eventSourceType  = faultInstanceres02.get("eventSourceType");
	        Instance02eventName  = faultInstanceres02.get("eventName");
	        
	        //tmp_command
	        Map.Entry tempcommand02Pair = null;
	        String tempcommand02Object ="";	        
			Map tempcommand02Parameters = ((Map)faultInstance02Parameters.get("tmp_command"));
			Iterator<Map.Entry> itr9 = tempcommand02Parameters.entrySet().iterator(); 
	        while (itr9.hasNext()) { 
	        	tempcommand02Pair = itr9.next(); 
	        	tempcommand02Object=String.valueOf(tempcommand02Pair);  
	        	tempcommand02res = tempcommand02Object.split("=");
	        	faultInstanceres02.put(tempcommand02res[0], tempcommand02res[1]);	        
	        } 	
	        
	        
	        
	        //tmp_alarmSetParameters
	        Map.Entry Instance02alarmSetPair = null;
	        String Instance02alarmSetObject ="";
	        String[] Instance02alarmSetres;
			Map Instance02alarmSetParameters = ((Map)faultInstance02Parameters.get("tmp_alarmSetParameters"));
			Iterator<Map.Entry> itr10 = Instance02alarmSetParameters.entrySet().iterator(); 
	        while (itr10.hasNext()) { 
	        	Instance02alarmSetPair = itr10.next(); 
	        	Instance02alarmSetObject=String.valueOf(Instance02alarmSetPair);  
	        	Instance02alarmSetres = Instance02alarmSetObject.split("=");
	        	faultInstanceres02.put(Instance02alarmSetres[0], Instance02alarmSetres[1]);	        
	        } 	
	        
	        
	        setAlarmCondition = faultInstanceres02.get("alarmCondition").toString();
	        setSpecificProblem = faultInstanceres02.get("specificProblem").toString();
	        setEventSeverity =   faultInstanceres02.get("eventSeverity").toString();
	        
	        //tmp_alarmClearParameters
	        Map.Entry Instanceres02alarmClearPair = null;
	        String Instanceres02alarmClearObject ="";
	        String[] Instanceres02alarmClearres;
			Map Instanceres02alarmClearParameters = ((Map)faultInstance02Parameters.get("tmp_alarmClearParameters"));
			Iterator<Map.Entry> itr11 = Instanceres02alarmClearParameters.entrySet().iterator(); 
	        while (itr11.hasNext()) { 
	        	Instanceres02alarmClearPair = itr11.next(); 
	        	Instanceres02alarmClearObject=String.valueOf(Instanceres02alarmClearPair);  
	        	Instanceres02alarmClearres = Instanceres02alarmClearObject.split("=");
	        	Instanceres02ClearParameter.put(Instanceres02alarmClearres[0], Instanceres02alarmClearres[1]);	        
	        } 	
	        
	        ins02alarmConditionClear = Instanceres02ClearParameter.get("alarmCondition").toString();
	        ins02specificProblemClear = Instanceres02ClearParameter.get("specificProblem").toString();
	        ins02eventSeverityClear =   Instanceres02ClearParameter.get("eventSeverity").toString();
	        

	        	        
	        
			} catch (ClassCastException ex) {
			ex.printStackTrace();
		}
		return faultConfig;
	}
	
	
	public static HashMap<String, DeviceData> readVppMetrics(String[] linkStart) {
		
		//t0
		String Bytesin = faultConfigTempInit.get("tmp_t0BytesIn");
		String BytesOut = faultConfigTempInit.get("tmp_t0BytesOut").toString();
		String PacketsIn = faultConfigTempInit.get("tmp_t0PacketsIn");
		String PacketsOut = faultConfigTempInit.get("tmp_t0PacketsOut");
		
		
		//t1
		String t1BytesIn = faultConfigCommand.get("tmp_t1BytesIn");
		String t1BytesOut = faultConfigCommand.get("tmp_t1BytesOut").toString();
		String t1PacketsIn = faultConfigCommand.get("tmp_t1PacketsIn");
		String t1PacketsOut = faultConfigCommand.get("tmp_t1PacketsOut");
		
		
		
		
		String echoFalut = faultInstanceres02.get("tmp_cmd1");
		HashMap<String, DeviceData> vppMetrics =  new HashMap<>();
		
		for(int i=0;i<linkStart.length;i++) {
		String device = linkStart[i];
		
		
		//t0
		String replaceBytesin ="";
		if(Bytesin.contains("$tmp_device")) {
		 String repString = Bytesin.replace("$tmp_device", device.trim());
		 replaceBytesin = repString.replace("sudo", "/bin/sh,-c,");
		}			
		String[] bytesinArray= replaceBytesin.split(",");
		
		
		String replaceBytesOut ="";
		if(BytesOut.contains("$tmp_device")) {
		 String  repString = BytesOut.replace("$tmp_device", device.trim());
		 replaceBytesOut = repString.replace("sudo", "/bin/sh,-c,");
		}		
		String[] bytesoutArray = replaceBytesOut.split(",");
		
		
		String replacePacketsIn ="";
		if(PacketsIn.contains("$tmp_device")) {
		 String repString = PacketsIn.replace("$tmp_device", device.trim());
		 replacePacketsIn = repString.replace("sudo", "/bin/sh,-c,");
		}		
		String[] packetsInArray= replacePacketsIn.split(",");
				
		String replacePacketsOut ="";
		if(PacketsOut.contains("$tmp_device")) {
		 String repString = PacketsOut.replace("$tmp_device", device.trim());
		 replacePacketsOut = repString.replace("sudo", "/bin/sh,-c,");
		}		
		String[] packetsOutArray= replacePacketsOut.split(",");
		
		
		
		//t1
		String replacet1Bytesin ="";
		if(t1BytesIn.contains("$tmp_device")) {
		 String repString = t1BytesIn.replace("$tmp_device", device.trim());
		 replacet1Bytesin = repString.replace("sudo", "/bin/sh,-c,");
		}			
		String[] t1BytesinArray= replacet1Bytesin.split(",");
				
		String replacet1BytesOut ="";
		if(t1BytesOut.contains("$tmp_device")) {
		 String  repString = t1BytesOut.replace("$tmp_device", device.trim());
		 replacet1BytesOut = repString.replace("sudo", "/bin/sh,-c,");
		}		
		String[] t1BytesoutArray = replacet1BytesOut.split(",");
								
		String replacet1PacketsIn ="";
		if(t1PacketsIn.contains("$tmp_device")) {
		 String repString = t1PacketsIn.replace("$tmp_device", device.trim());
		 replacet1PacketsIn = repString.replace("sudo", "/bin/sh,-c,");
		}		
		String[] t1PacketsInArray= replacet1PacketsIn.split(",");
				
		String replacet1PacketsOut ="";
		if(t1PacketsOut.contains("$tmp_device")) {
		 String repString = t1PacketsOut.replace("$tmp_device", device.trim());
		 replacet1PacketsOut = repString.replace("sudo", "/bin/sh,-c,");

		}		
		String[] t1PacketsOutArray= replacet1PacketsOut.split(",");

		try {
			//t0
			Runtime rt1 = Runtime.getRuntime();
		    Process bytesinchild = rt1.exec(bytesinArray);
		    BufferedReader readerBytesin = new BufferedReader(new InputStreamReader(        
		    		bytesinchild.getInputStream())); 
		    String readMetrics= readerBytesin.readLine();
		    
		    
		    Runtime rt2 = Runtime.getRuntime();
     	    Process bytesoutchild = rt2.exec(bytesoutArray);
		    BufferedReader readerBytesout = new BufferedReader(new InputStreamReader(        
		    		bytesoutchild.getInputStream())); 
		    String readMetrics1= readerBytesout.readLine();
		    
		    Runtime rt3 = Runtime.getRuntime();
     	    Process packetsInchild = rt3.exec(packetsInArray);
		    BufferedReader readerPacketsIn = new BufferedReader(new InputStreamReader(        
		    		packetsInchild.getInputStream())); 
		    String readMetrics2= readerPacketsIn.readLine();
		    
		    Runtime rt4 = Runtime.getRuntime();
     	    Process packetsOutchild = rt4.exec(packetsOutArray);
		    BufferedReader readerpacketsOut = new BufferedReader(new InputStreamReader(        
		    		packetsOutchild.getInputStream())); 
		    String readMetrics3= readerpacketsOut.readLine();
		    
		    Runtime rt5 = Runtime.getRuntime();
     	    Process echoFaultchild = rt5.exec(echoFalut);
		    BufferedReader readerechoFault = new BufferedReader(new InputStreamReader(        
		    		echoFaultchild.getInputStream())); 
		    String echoFaultMetric= readerechoFault.readLine();
		    DeviceData mddata = new DeviceData();
		    
		    
			//t1_Commands run
		    
			Runtime rt6 = Runtime.getRuntime();
		    Process t1bytesinchild = rt6.exec(t1BytesinArray);
		    BufferedReader readert1Bytesin = new BufferedReader(new InputStreamReader(        
		    		t1bytesinchild.getInputStream())); 
		    String readMetrics5= readert1Bytesin.readLine();
		    
		    

		    Runtime rt7 = Runtime.getRuntime();
     	    Process t1bytesoutchild = rt7.exec(t1BytesoutArray);
		    BufferedReader readert1Bytesout = new BufferedReader(new InputStreamReader(        
		    		t1bytesoutchild.getInputStream())); 
		    String readMetrics6= readert1Bytesout.readLine();

		    Runtime rt8 = Runtime.getRuntime();
     	    Process t1packetsInchild = rt8.exec(t1PacketsInArray);
		    BufferedReader readert1PacketsIn = new BufferedReader(new InputStreamReader(        
		    		t1packetsInchild.getInputStream())); 
		    String readMetrics7= readert1PacketsIn.readLine();


		    Runtime rt9 = Runtime.getRuntime();
     	    Process t1packetsOutchild = rt9.exec(t1PacketsOutArray);
		    BufferedReader readert1packetsOut = new BufferedReader(new InputStreamReader(        
		    		t1packetsOutchild.getInputStream())); 
		    String readMetrics8= readert1packetsOut.readLine();

		    
		    mddata.setT0bytesIn(readMetrics);
		    mddata.setT0bytesOut(readMetrics1);
		    mddata.setT0packetIn(readMetrics2);
		    mddata.setT0packetOut(readMetrics3);
		    
		    mddata.setT1Bytesin(readMetrics5);
		    mddata.setT1Bytesout(readMetrics6);
		    mddata.setT1Packetsin(readMetrics7);
		    mddata.setT1Packetsout(readMetrics8);
		    
		    
		    mddata.setInstanceres02Command(echoFaultMetric);
		    
		    vppMetrics.put("Instanceres02Cmd", mddata);
		    
		    if(device.equals("enp0s3")) {
		    	vppMetrics.put("enp0s3", mddata);
		    }else if(device.equals("lo")) {
		    	vppMetrics.put("lo", mddata);
			}else if(device.equals("docker0")) {
				vppMetrics.put("docker0", mddata);
			}
		    
		        }catch (Exception e) {
					
				}   						
		}		
		return vppMetrics;
	}	



	public static HashMap<String, DeviceData> readVppMetrics1(String[] linkStart) {
		String Bytesin = faultConfigTempInit.get("tmp_t0BytesIn");
		String BytesOut = faultConfigTempInit.get("tmp_t0BytesOut").toString();
		String PacketsIn = faultConfigTempInit.get("tmp_t0PacketsIn");
		String PacketsOut = faultConfigTempInit.get("tmp_t0PacketsOut");
		
		String echoFalut = faultInstanceres02.get("tmp_cmd1");
		HashMap<String, DeviceData> vppMetrics =  new HashMap<>();
		
		for(int i=0;i<linkStart.length;i++) {
		String device = linkStart[i];
		String replaceBytesin ="";
		if(Bytesin.contains("$tmp_device")) {
		 String repString = Bytesin.replace("$tmp_device", device.trim());
		 replaceBytesin = repString.replace("sudo", "/bin/sh,-c,");

		}	
		
		String[] bytesinArray= replaceBytesin.split(",");
		
		
		String replaceBytesOut ="";
		if(BytesOut.contains("$tmp_device")) {
		 String  repString = BytesOut.replace("$tmp_device", device.trim());
		 replaceBytesOut = repString.replace("sudo", "/bin/sh,-c,");
		}
		
		String[] bytesoutArray = replaceBytesOut.split(",");
		
		
		
		
		String replacePacketsIn ="";
		if(PacketsIn.contains("$tmp_device")) {
		 String repString = PacketsIn.replace("$tmp_device", device.trim());
		 replacePacketsIn = repString.replace("sudo", "/bin/sh,-c,");

		}		
		String[] packetsInArray= replacePacketsIn.split(",");
		
		
		String replacePacketsOut ="";
		if(PacketsOut.contains("$tmp_device")) {
		 String repString = PacketsOut.replace("$tmp_device", device.trim());
		 replacePacketsOut = repString.replace("sudo", "/bin/sh,-c,");

		}		
		String[] packetsOutArray= replacePacketsOut.split(",");
		try {
			
			Runtime rt1 = Runtime.getRuntime();
		    Process bytesinchild = rt1.exec(bytesinArray);
		    BufferedReader readerBytesin = new BufferedReader(new InputStreamReader(        
		    		bytesinchild.getInputStream())); 
		    String readMetrics= readerBytesin.readLine();
		    Runtime rt2 = Runtime.getRuntime();
     	    Process bytesoutchild = rt2.exec(bytesoutArray);
		    BufferedReader readerBytesout = new BufferedReader(new InputStreamReader(        
		    		bytesoutchild.getInputStream())); 
		    String readMetrics1= readerBytesout.readLine();
		    Runtime rt3 = Runtime.getRuntime();
     	    Process packetsInchild = rt3.exec(packetsInArray);
		    BufferedReader readerPacketsIn = new BufferedReader(new InputStreamReader(        
		    		packetsInchild.getInputStream())); 
		    String readMetrics2= readerPacketsIn.readLine();
		    Runtime rt4 = Runtime.getRuntime();
     	    Process packetsOutchild = rt4.exec(packetsOutArray);
		    BufferedReader readerpacketsOut = new BufferedReader(new InputStreamReader(        
		    		packetsOutchild.getInputStream())); 
		    String readMetrics3= readerpacketsOut.readLine();
		    Runtime rt5 = Runtime.getRuntime();
     	    Process echoFaultchild = rt5.exec(echoFalut);
		    BufferedReader readerechoFault = new BufferedReader(new InputStreamReader(        
		    		echoFaultchild.getInputStream())); 
		    String echoFaultMetric= readerechoFault.readLine();
		    DeviceData mddata = new DeviceData();
		    
//		    mddata.setBytesIn(readMetrics);
//		    mddata.setBytesOut(readMetrics1);
//		    mddata.setPacketIn(readMetrics2);
//		    mddata.setPacketOut(readMetrics3);
		    
		    mddata.setInstanceres02Command(echoFaultMetric);
		    
		    vppMetrics.put("Instanceres02Cmd", mddata);
		    
		    if(device.equals("enp0s3")) {
		    	vppMetrics.put("enp0s3", mddata);
		    }else if(device.equals("lo")) {
		    	vppMetrics.put("lo", mddata);
			}else if(device.equals("docker0")) {
				vppMetrics.put("docker0", mddata);
			}
		        }catch (Exception e) {
					
				}   						
		}		
		return vppMetrics;
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
		FaultData flDataThread = new FaultData();	
         new Thread(flDataThread.faultInstance01).start();	
         new Thread(flDataThread.faultInstance02).start();
	}

}
