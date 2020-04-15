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

import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.apache.log4j.Level;
import org.apache.log4j.Logger;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

import evel_javalibrary.att.com.AgentMain;
import evel_javalibrary.att.com.EvelScalingMeasurement;

public class MeasureData  extends Thread{
	
	
	static HashMap<String, String> measConfig = new HashMap<>();
	static String[] resDevice =null;
	static String[] tempInitres;
	static String[] tempcommandres;
	static String[] tempcommandres1;	
	static HashMap<String, String> vNicPerformanceCommand1 = new HashMap<>();
	static HashMap<String, String> vNicPerformanceArray = new HashMap<>();
	static HashMap<String, String> initTempCommand = new HashMap<>();
	static float bytesInLo;
	static float bytesOutLo;
	static float packetsInLo;
	static float packetsOutLo;
	
	static float bytesInEnps03;
	static float bytesOutEnps03;
	static float packetsInEnps03;
	static float packetsOutEnps03;
	
	static float bytesInDocker0;
	static float bytesOutDocker0;
	static float packetsInDocker0;
	static float packetsOutDocker0;
	
	
	static int  gmEventId = 1;
	static String eventId1 = "mvfs";
	static String eventId = "00000000";
	static String eventId2=null;
	
	static int requestRate = 0;
	static String linkStart = "";
	static int linkCount; 
	
	private static final Logger logger = Logger.getLogger(AgentMain.class);
	Long startEpochMicrosec = 0L;
	Long lastEpochMicrosec = 0L;
	
	@Override
	public void run() {
        
		try {
			
			readMeasurementConfig();
			readVppMetrics(resDevice);
		} catch (IOException | ParseException e1) {
			logger.error(e1);
		}
	
		String[] intFaceMap = resDevice;
		
		int numOfInterfaces = 0;
		if( intFaceMap != null)
			numOfInterfaces = intFaceMap.length;		
		if( numOfInterfaces <= 0) {
			
			return;
		}	
		
		


		try {
		Thread.sleep(1000);  
		}catch(Exception e) {
			logger.error(e);
		}

		
		while(true) {
			HashMap<String, DeviceData> lastMetrics = readVppMetrics(resDevice);
			HashMap<String, DeviceData> currentMetrics = lastMetrics;
			requestRate =2;
			eventId2 = eventId1+ eventId+(gmEventId++);
			String measurmentInterval="";
			long milliseconds = 60000;
			if(measConfig.get("measurementInterval") == null) {
				measurmentInterval = Long.toString(milliseconds);
			}else {
				measurmentInterval = measConfig.get("measurementInterval");
			}			
			EvelScalingMeasurement eveMeas = new EvelScalingMeasurement(Integer.parseInt(measurmentInterval) ,
					measConfig.get("eventName"),
                    eventId2);	
			
			for( String vNic : intFaceMap) {
                
				int receivedOctetsDeltaLo = 0;
				int receivedTotalPacketsDeltaLo = 0;
				int transmittedOctetsDeltaLo = 0;
				int transmittedTotalPacketsDeltaLo = 0;
								
				
				    if (Integer.parseInt((currentMetrics.get(vNic).getT1Bytesin()))
							- Integer.parseInt((lastMetrics.get(vNic).getT0bytesIn()) ) > 0) {
						receivedOctetsDeltaLo = (Integer.parseInt((currentMetrics.get(vNic).getT1Bytesin()) )
								- Integer.parseInt((lastMetrics.get(vNic).getT0bytesIn()) ));
					} else {
						receivedOctetsDeltaLo = 0;
					}
										
					
					if (Integer.parseInt((currentMetrics.get(vNic).getT1Packetsin()))
							- Integer.parseInt((lastMetrics.get(vNic).getT0packetIn()) ) > 0) {
						receivedTotalPacketsDeltaLo =(Integer.parseInt((currentMetrics.get(vNic).getT1Packetsin()) )
								- Integer.parseInt((lastMetrics.get(vNic).getT0packetIn())  ));
					} else {
						receivedTotalPacketsDeltaLo = 0;
					}
					
					
					if (Integer.parseInt((currentMetrics.get(vNic).getT1Bytesout()))
							- Integer.parseInt((lastMetrics.get(vNic).getT0bytesOut()) ) > 0) {
						transmittedOctetsDeltaLo = (Integer.parseInt((currentMetrics.get(vNic).getT1Bytesout()) )
								- Integer.parseInt((lastMetrics.get(vNic).getT0bytesOut())));
					} else {
						transmittedOctetsDeltaLo = 0;
					}
							
					
					if (Integer.parseInt((currentMetrics.get(vNic).getT1Packetsout()))
							- Integer.parseInt((lastMetrics.get(vNic).getT0packetOut()) ) > 0) {
						transmittedTotalPacketsDeltaLo = (Integer.parseInt((currentMetrics.get(vNic).getT1Packetsout()) )
								- Integer.parseInt((lastMetrics.get(vNic).getT0packetOut())));
					} else {
						transmittedTotalPacketsDeltaLo = 0;
					}

				EvelScalingMeasurement.MEASUREMENT_NIC_PERFORMANCE vNicPerf = eveMeas.evel_measurement_new_vnic_performance(vNic.replaceAll("^[\"']+|[\"']+$", ""), "true");
				if( measConfig.get("eventType")!=null) {
					String hostName = hostName();
					startEpochMicrosec = lastEpochMicrosec;
					lastEpochMicrosec = System.nanoTime()/1000;            		
            	    eveMeas.evel_last_epoch_set(startEpochMicrosec);
            	    eveMeas.evel_start_epoch_set(lastEpochMicrosec);										
					eveMeas.evel_measurement_type_set( measConfig.get("eventType"));
					
					
					eveMeas.evel_vnic_performance_rx_octets_delta_set( vNicPerf, receivedOctetsDeltaLo);
					eveMeas.evel_vnic_performance_rx_total_pkt_delta_set(vNicPerf, receivedTotalPacketsDeltaLo);
					eveMeas.evel_vnic_performance_tx_octets_delta_set( vNicPerf, transmittedOctetsDeltaLo);
					eveMeas.evel_vnic_performance_tx_total_pkt_delta_set(vNicPerf, transmittedTotalPacketsDeltaLo);
			
					eveMeas.evel_nfcnamingcode_set(measConfig.get("nfcNamingCode"));
					eveMeas.evel_nfnamingcode_set(measConfig.get("nfNamingCode"));					
            		if(measConfig.get("reportingEntityName") == null) {
            			eveMeas.evel_reporting_entity_name_set(hostName);
            			}else {
            				eveMeas.evel_reporting_entity_name_set(measConfig.get("reportingEntityName"));
            			}											
					eveMeas.evel_reporting_entity_id_set(measConfig.get("reportingEntityId"));
					eveMeas.evel_nfVendorName_set(measConfig.get("nfVendorName"));
					eveMeas.evel_header_set_sourceid(true,measConfig.get("sourceId"));					
		     		if(measConfig.get("sourceName") == null) {
		     			eveMeas.evel_header_set_source_name(hostName);
            			}else {
            				eveMeas.evel_header_set_source_name(measConfig.get("sourceName"));	
            			}												
					eveMeas.evel_timeZoneOffset_set(measConfig.get("timeZoneOffset"));
					
				}
				
			}
			AgentMain.evel_post_event(eveMeas);
			boolean continues = true;
			long curr  = System.currentTimeMillis();
			while(continues) {
				try {
					Thread.sleep(100);
					}catch (Exception e) {
                     logger.error(e);
					}
				if(System.currentTimeMillis() >= (curr+Integer.parseInt(measurmentInterval))) {
					continues = false;				
				}
				
				
			}
		}
			
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
	    try
	    {
	        InetAddress addr;
	        addr = InetAddress.getLocalHost();
	        hostname = addr.getHostName();
	    }
	    catch (UnknownHostException ex)
	    {
	    	logger.error(ex);
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
	            bytesToHex(mac);
	        }
	      }
	    } catch (SocketException e) {
		   logger.error(e);			
		}

		return hostname;
	}

	
	
	private static HashMap<String, String> readMeasurementConfig() throws IOException, ParseException {
		JSONParser jsonParser = new JSONParser();
		
		try {
			
			FileReader reader = new FileReader("./src/main/java/evel_javalibrary/att/com/loadbalance/meas_config.json");			
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
	        	measConfig.put(directres[0], directres[1]);	        
	        } 		
	        
	        String eventName  = measConfig.get("eventName");   
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
	        	measConfig.put(indirectres[0], indirectres[1]);	        
	        } 	
	        
	        //tmp_init
	        Map.Entry tempcommandPair = null;
	        String tempcommandObject ="";	        
			Map tempcommandParameters = ((Map)indirectParameters.get("tmp_init"));
			Iterator<Map.Entry> itr3 = tempcommandParameters.entrySet().iterator(); 
	        while (itr3.hasNext()) { 
	        	tempcommandPair = itr3.next(); 
	        	tempcommandObject=String.valueOf(tempcommandPair);  
	        	tempcommandres = tempcommandObject.split("=");
	        	initTempCommand.put(tempcommandres[0], tempcommandres[1]);	        
	        } 	
	        
	        //tmp_command1
	        Map.Entry tempcommand1Pair = null;
	        String tempcommand1Object ="";	        
	        JSONArray nicPerfomenceArray = (JSONArray) indirectParameters.get("vNicPerformance"); 
	        Map vNic = (Map)nicPerfomenceArray.get(0);
	        Map perf = ((Map)vNic.get("tmp_vnic_command"));
	        Iterator<Map.Entry> itr5 = perf.entrySet().iterator(); 
	        while (itr5.hasNext()) { 
	        	tempcommand1Pair = itr5.next(); 
	        	tempcommand1Object=String.valueOf(tempcommand1Pair);  
	        	tempcommandres1 = tempcommand1Object.split("=");
	        	vNicPerformanceCommand1.put(tempcommandres1[0], tempcommandres1[1]);	        
	        } 	
	        Map.Entry vnicPair = null;
	        String vnicObject ="";	
	        String[] nicPerfomenceArrayRes;
	        vNic = (Map)nicPerfomenceArray.get(0);
	        Iterator<Map.Entry> itr6 = vNic.entrySet().iterator(); 
	        while (itr6.hasNext()) { 
	        	vnicPair = itr6.next(); 
	        	vnicObject=String.valueOf(vnicPair);  
	        	nicPerfomenceArrayRes = vnicObject.split("=");
	        	vNicPerformanceArray.put(nicPerfomenceArrayRes[0], nicPerfomenceArrayRes[1]);	        
	        } 	
	       
	        String receivedOctetsDelta = vNicPerformanceArray.get("receivedOctetsDelta");
	        
			} catch (ClassCastException ex) {
			logger.error(ex);
		}
		return measConfig;
	}
	

	
	private static HashMap<String, DeviceData> readVppMetrics(String[] linkStart) {
		DeviceData mddata = null;
		new DeviceData();
	
		
		//tmp_t0
		String t0BytesIn = initTempCommand.get("tmp_t0BytesIn");
		String t0BytesOut = initTempCommand.get("tmp_t0BytesOut");
		String t0PacketsIn = initTempCommand.get("tmp_t0PacketsIn");
		String t0PacketsOut = initTempCommand.get("tmp_t0PacketsOut");
		
		//tmp_t1
		String t1BytesIn = vNicPerformanceCommand1.get("tmp_t1BytesIn");
		String t1BytesOut = vNicPerformanceCommand1.get("tmp_t1BytesOut").toString();
		String t1PacketsIn = vNicPerformanceCommand1.get("tmp_t1PacketsIn");
		String t1PacketsOut = vNicPerformanceCommand1.get("tmp_t1PacketsOut");
		
		
		HashMap<String, DeviceData> vppMetrics =  new HashMap<>();
		for(int i = 0; i < linkStart.length; i++) {
			 mddata =new DeviceData();
			String device = linkStart[i];
			
			//t0_
			String replaceInitBytesint0 ="";
			if(t0BytesIn.contains("$tmp_device")) {
			 String repString = t0BytesIn.replace("$tmp_device", device.trim());
			 replaceInitBytesint0 = repString.replace("sudo", "/bin/sh,-c,");

			}		
			String[] t0BytesinArray= replaceInitBytesint0.split(",");
			
			
			String replaceInitBytesout="";
			if(t0BytesOut.contains("$tmp_device")) {
			 String repString = t0BytesOut.replace("$tmp_device", device.trim());
			 replaceInitBytesout = repString.replace("sudo", "/bin/sh,-c,");

			}		
			String[] t0BytesoutArray= replaceInitBytesout.split(",");
			
			String replaceInitPacketsin ="";
			if(t0PacketsIn.contains("$tmp_device")) {
			 String repString = t0PacketsIn.replace("$tmp_device", device.trim());
			 replaceInitPacketsin = repString.replace("sudo", "/bin/sh,-c,");

			}		
			String[] t0PacketsinArray= replaceInitPacketsin.split(",");
			
			
			String replaceInitPacketsout ="";
			if(t0PacketsOut.contains("$tmp_device")) {
			 String repString = t0PacketsOut.replace("$tmp_device", device.trim());
			 replaceInitPacketsout = repString.replace("sudo", "/bin/sh,-c,");

			}		
			String[] t0PacketsoutArray= replaceInitPacketsout.split(",");
												
		//t1
		String replaceBytesin ="";
		if(t1BytesIn.contains("$tmp_device")) {
		 String repString = t1BytesIn.replace("$tmp_device", device.trim());
		 replaceBytesin = repString.replace("sudo", "/bin/sh,-c,");

		}			
		String[] t1BytesinArray= replaceBytesin.split(",");
				
		String replaceBytesOut ="";
		if(t1BytesOut.contains("$tmp_device")) {
		 String  repString = t1BytesOut.replace("$tmp_device", device.trim());
		 replaceBytesOut = repString.replace("sudo", "/bin/sh,-c,");
		}		
		String[] t1BytesoutArray = replaceBytesOut.split(",");
								
		String replacePacketsIn ="";
		if(t1PacketsIn.contains("$tmp_device")) {
		 String repString = t1PacketsIn.replace("$tmp_device", device.trim());
		 replacePacketsIn = repString.replace("sudo", "/bin/sh,-c,");
		}		
		String[] t1PacketsInArray= replacePacketsIn.split(",");
				
		String replacePacketsOut ="";
		if(t1PacketsOut.contains("$tmp_device")) {
		 String repString = t1PacketsOut.replace("$tmp_device", device.trim());
		 replacePacketsOut = repString.replace("sudo", "/bin/sh,-c,");

		}		
		String[] t1PacketsOutArray= replacePacketsOut.split(",");
		
		try {			
            //t0_Commands run		    
		    Runtime rt5 = Runtime.getRuntime();  
     	    Process initBytesint0child = rt5.exec(t0BytesinArray);
		    BufferedReader readerinitBytesint0 = new BufferedReader(new InputStreamReader(        
		    		initBytesint0child.getInputStream())); 
		    String readinitMetrics= readerinitBytesint0.readLine();
		    
		    Runtime rt6 = Runtime.getRuntime();  
     	    Process initBytesoutchild = rt6.exec(t0BytesoutArray);
		    BufferedReader readerinitBytesout = new BufferedReader(new InputStreamReader(        
		    		initBytesoutchild.getInputStream())); 
		    String readinitMetrics2= readerinitBytesout.readLine();
		   
		    
		    Runtime rt7 = Runtime.getRuntime();  
     	    Process initPacketsinchild = rt7.exec(t0PacketsinArray);
		    BufferedReader readerinitPacketsin = new BufferedReader(new InputStreamReader(        
		    		initPacketsinchild.getInputStream())); 
		    String readinitMetrics3= readerinitPacketsin.readLine();
		  
		    
		    
		    Runtime rt8 = Runtime.getRuntime();  
     	    Process initPacketsoutchild = rt8.exec(t0PacketsoutArray);
		    BufferedReader readerinitPacketsout = new BufferedReader(new InputStreamReader(        
		    		initPacketsoutchild.getInputStream())); 
		    String readinitMetrics4= readerinitPacketsout.readLine();
		    		    
		  

			//t1_Commands run
		    Thread.sleep(Integer.parseInt(measConfig.get("measurementInterval"))); 		    
			Runtime rt1 = Runtime.getRuntime();
		    Process bytesinchild = rt1.exec(t1BytesinArray);
		    BufferedReader readerBytesin = new BufferedReader(new InputStreamReader(        
		    		bytesinchild.getInputStream())); 
		    String readMetrics= readerBytesin.readLine();
		    
		  
		     
		    Runtime rt2 = Runtime.getRuntime();
     	    Process bytesoutchild = rt2.exec(t1BytesoutArray);
		    BufferedReader readerBytesout = new BufferedReader(new InputStreamReader(        
		    		bytesoutchild.getInputStream())); 
		    String readMetrics1= readerBytesout.readLine();
		     
		    Runtime rt3 = Runtime.getRuntime();
     	    Process packetsInchild = rt3.exec(t1PacketsInArray);
		    BufferedReader readerPacketsIn = new BufferedReader(new InputStreamReader(        
		    		packetsInchild.getInputStream())); 
		    String readMetrics2= readerPacketsIn.readLine();

		    
		    Runtime rt4 = Runtime.getRuntime();
     	    Process packetsOutchild = rt4.exec(t1PacketsOutArray);
		    BufferedReader readerpacketsOut = new BufferedReader(new InputStreamReader(        
		    		packetsOutchild.getInputStream())); 
		    String readMetrics3= readerpacketsOut.readLine();
		    
		    
		    //t1
		    mddata.setT1Bytesin(readMetrics);
		    mddata.setT1Bytesout(readMetrics1);
		    mddata.setT1Packetsin(readMetrics2);
		    mddata.setT1Packetsout(readMetrics3);
		    
		    //t0
		    mddata.setT0bytesIn(readinitMetrics);
		    mddata.setT0bytesOut(readinitMetrics2);
		    mddata.setT0packetIn(readinitMetrics3);
		    mddata.setT0packetOut(readinitMetrics4);
		    
		    if(device.equals("enp0s3")) {
		    	vppMetrics.put("enp0s3", mddata);
		    	
		    }else if(device.equals("lo")) {
		    	vppMetrics.put("lo", mddata);
			}else if(device.equals("docker0")) {
				vppMetrics.put("docker0", mddata);
			}
		    
		        }catch (Exception e) {
					logger.error(e);
				}   						
		}		
		return vppMetrics;
	}	


	
	
	
	public static void main(String[] args) {

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
		MeasureData mdataThread = new MeasureData();
		mdataThread.start();
		
	}
	


}
