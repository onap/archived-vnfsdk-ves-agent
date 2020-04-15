package evel_javalibrary.att.com;

/**************************************************************************//**
 * @file
 * Header for EVEL Header library
 *
 * This file implements the EVEL library which is intended to provide a
 * simple wrapper around the complexity of AT&T's Vendor Event Listener API so
 * that VNFs can use it without worrying about details of the API transport.
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


import java.text.MessageFormat;
import java.util.Enumeration;
import java.util.logging.Logger;
import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.net.UnknownHostException;

import javax.json.Json;
import javax.json.JsonObject;
import javax.json.JsonObjectBuilder;


public class EvelHeader {
	
	
	/**************************************************************************//**
	 * Event domains for the various events we support.
	 * JSON equivalent field: domain
	 *****************************************************************************/
	public enum DOMAINS {
	  EVEL_DOMAIN_INTERNAL,       /** Internal event, not for external routing.  */
	  EVEL_DOMAIN_FAULT,          /** A Fault event.                             */
	  EVEL_DOMAIN_HEARTBEAT,      /** A Heartbeat event (event header only).     */
	  EVEL_DOMAIN_MEASUREMENT,    /** A Measurement for VF Scaling event.        */
	  EVEL_DOMAIN_MOBILE_FLOW,    /** A Mobile Flow event.                       */
	  EVEL_DOMAIN_OTHER,          /** Another event.                             */
	  EVEL_DOMAIN_REPORT,         /** A Measurement for VF Reporting event.      */
	  EVEL_DOMAIN_SIPSIGNALING,   /** A Signaling event.                         */
	  EVEL_DOMAIN_STATE_CHANGE,   /** A State Change event.                      */
	  EVEL_DOMAIN_SYSLOG,         /** A Syslog event.                            */
	  EVEL_DOMAIN_THRESHOLD_CROSSING,  /** A Threshold crossing alert Event     */
	  EVEL_DOMAIN_VOICE_QUALITY,  /** A Voice Quality Event		 	     */
	  EVEL_DOMAIN_HEARTBEAT_FIELD,/** A Heartbeat field event.                   */
	  EVEL_DOMAIN_NOTIFICATION,
	  EVEL_DOMAIN_PNFREGISTRATION,
	  EVEL_MAX_DOMAINS          /** Maximum number of recognized Event types.  */
	  
	}
	
	/**************************************************************************//**
	 * Event priorities.
	 * JSON equivalent field: priority
	 *****************************************************************************/
	public enum PRIORITIES {
	  EVEL_PRIORITY_HIGH,
	  EVEL_PRIORITY_MEDIUM,
	  EVEL_PRIORITY_NORMAL,
	  EVEL_PRIORITY_LOW,
	  EVEL_MAX_PRIORITIES
	}
	
	final int EVEL_HEADER_MAJOR_VERSION = 4;
	final int EVEL_HEADER_MINOR_VERSION = 0;
	  /***************************************************************************/
	  /* Version                                                                 */
	  /***************************************************************************/
	  int major_version;
	  int minor_version;

	  /***************************************************************************/
	  /* Mandatory fields                                                        */
	  /***************************************************************************/
	  DOMAINS event_domain;
	  String event_id=null;
	  String event_name=null;
	  String source_name=null;
	  String reporting_entity_name=null;
	  PRIORITIES priority;
	  Long start_epoch_microsec = 0L;
	  Long last_epoch_microsec = 0L;
	  int sequence = 0;
	  
	  //VES 7.0 added 4Sept2108
	  String ves_eventListener_version =null;

	  /***************************************************************************/
	  /* Optional fields                                                         */
	  /***************************************************************************/
	  EvelOptionString event_type;
	  EvelOptionString source_id;
	  EvelOptionString reporting_entity_id;
	  EvelOptionIntHeader internal_field;
	  EvelOptionString nfcnaming_code;
	  EvelOptionString nfnaming_code;
	  
	  
	//VES 7.0 added 4Sept2108
	  EvelOptionString nfVendor_name;
	  EvelOptionString timeZoneOffset;
	  
	  
	  /**************************************************************************//**
	   * Unique sequence number for events from this VNF.
	   *****************************************************************************/
	  int event_sequence = 1;
	  private static final Logger LOGGER = Logger.getLogger( EvelHeader.class.getName() );

		protected static void EVEL_EXIT() {
			// TODO Auto-generated method stub
			
		}

		protected static void EVEL_ENTER() {
			// TODO Auto-generated method stub
		}

	  /**************************************************************************//**
	   * Set the next event_sequence to use.
	   *
	   * @param sequence      The next sequence number to use.
	   *****************************************************************************/
	  void evel_set_next_event_sequence( int seqnce)
	  {
	    EVEL_ENTER();

	    LOGGER.info(MessageFormat.format("Setting event sequence to {0}, was {1} ", sequence, event_sequence));
	    sequence = seqnce;

	    EVEL_EXIT();
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

	  /**************************************************************************//**
	   * Initialize a newly created event header.
	   *
	   * @param header  Pointer to the header being initialized.
	   *****************************************************************************/
	  public EvelHeader(String eventname,String ev_id)
	  {
	    EVEL_ENTER();

	    assert(eventname != null);

	    /***************************************************************************/
	    /* Initialize the header.  Get a new event sequence number.  Note that if  */
	    /* any memory allocation fails in here we will fail gracefully because     */
	    /* everything downstream can cope with nulls.                              */
	    /***************************************************************************/
	    this.event_domain = DOMAINS.EVEL_DOMAIN_HEARTBEAT;
	    if(ev_id == null){
                event_sequence ++;
                sequence = event_sequence;
	    	event_id = MessageFormat.format("{0}", event_sequence);
	    	LOGGER.warning("WARNING:not confirming to Common Event Format 28.3 standard");
	    } else {
	    	event_id = ev_id;
	        sequence = 1000;
	    }
	    event_name = eventname;
	    start_epoch_microsec = last_epoch_microsec;
	    last_epoch_microsec = System.nanoTime()/1000;
	    priority = PRIORITIES.EVEL_PRIORITY_NORMAL;
	    
	    
	    
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
                /* 

                StringBuilder sb = new StringBuilder();
                for (int i = 0; i < mac.length; i++) {
                    sb.append(String.format("%02X%s", mac[i],
                                 (i < mac.length - 1) ? "-" : ""));
                } */
                
                uuid = bytesToHex(mac);
            }
          }
        
	    } catch (SocketException e) {
			// TODO Auto-generated catch block
	   
		}
	    
	    
	    reporting_entity_name = hostname;
	    source_name = hostname;

	    major_version = EVEL_HEADER_MAJOR_VERSION;
	    minor_version = EVEL_HEADER_MINOR_VERSION;
	    
	    //VES 7.0 added 4Sept 2018
	    ves_eventListener_version = "7.1";

	    /***************************************************************************/
	    /* Optional parameters.                                                    */
	    /***************************************************************************/
	    event_type = new EvelOptionString(true, "Perf management");
	    nfcnaming_code = new EvelOptionString(true, "NfcNamingCode");
	    nfnaming_code = new EvelOptionString(true, "NfNamingCode");
	    reporting_entity_id = new EvelOptionString(true, uuid);
	    source_id = new EvelOptionString(true, uuid);
	    internal_field = new EvelOptionIntHeader(false, "InternalFeild");
	    
	    //VES 7.0 added 4Sept2018
	    nfVendor_name = new EvelOptionString(true, "nfVendorName");
        timeZoneOffset = new EvelOptionString(true, "UTC-5:30");
	    EVEL_EXIT();
	  }

	  
	  /**************************************************************************//**
	   * Create a new heartbeat event.
	   *
	   * @note that the heartbeat is just a "naked" commonEventHeader!
	   *
	   * @returns pointer to the newly manufactured ::EVENT_HEADER.  
	   * @retval  null  Failed to create the event.
	   ****************************************************************************/


	  public static EvelHeader evel_new_heartbeat()
	  {
		EvelHeader header = null;
	    EVEL_ENTER();
	    /***************************************************************************/
	    /* Initialize the header.  Get a new event sequence number.  Note that if  */
	    /* any memory allocation fails in here we will fail gracefully because     */
	    /* everything downstream can cope with nulls.                              */
	    /***************************************************************************/
	    header = new EvelHeader("Heartbeat",null);
	    header.event_type.set_option(true);
	    header.event_type.SetValue("HEARTBEAT");
	    LOGGER.info(header.event_type.value);

	    EVEL_EXIT();
	    return header;
	  }
	  
	  /**************************************************************************//**
	   * Create a new heartbeat event.
	   *
	   * @note that the heartbeat is just a "naked" commonEventHeader!
	   *
	   * @returns pointer to the newly manufactured ::EVENT_HEADER.  
	   * @retval  null  Failed to create the event.
	   ****************************************************************************/


	  public static EvelHeader evel_new_heartbeat(String evname,String evid)
	  {
		EvelHeader header = null;
	    EVEL_ENTER();
	    /***************************************************************************/
	    /* Initialize the header.  Get a new event sequence number.  Note that if  */
	    /* any memory allocation fails in here we will fail gracefully because     */
	    /* everything downstream can cope with nulls.                              */
	    /***************************************************************************/
	    header = new EvelHeader(evname,evid);
	    header.event_type.set_option(true);
	    header.event_type.SetValue("HEARTBEAT");;
	    LOGGER.info(header.event_type.value);

	    EVEL_EXIT();
	    return header;
	  }


	/**************************************************************************//**
	   * Set the Event Type property of the event header.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param header        Pointer to the ::EVENT_HEADER.
	   * @param type          The Event Type to be set. ASCIIZ string. The caller
	   *                      does not need to preserve the value once the function
	   *                      returns.
	   *****************************************************************************/
	  public void evel_header_type_set(String type)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(type != null);

	    event_type.set_option(true);
	    event_type.SetValue(type);

	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the Start Epoch property of the event header.
	   *
	   * @note The Start Epoch defaults to the time of event creation.
	   *
	   * @param header        Pointer to the ::EVENT_HEADER.
	   * @param start_epoch_microsec
	   *                      The start epoch to set, in microseconds.
	   *****************************************************************************/
	  public void evel_start_epoch_set(Long epoch_microsec)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions and assign the new value.                           */
	    /***************************************************************************/
	    start_epoch_microsec = epoch_microsec;

	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the Last Epoch property of the event header.
	   *
	   * @note The Last Epoch defaults to the time of event creation.
	   *
	   * @param header        Pointer to the ::EVENT_HEADER.
	   * @param last_epoch_microsec
	   *                      The last epoch to set, in microseconds.
	   *****************************************************************************/
	  public void evel_last_epoch_set(Long epoch_microsec)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions and assign the new value.                           */
	    /***************************************************************************/
	    last_epoch_microsec = epoch_microsec;

	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the NFC Naming code property of the event header.
	   *
	   * @param header        Pointer to the ::EVENT_HEADER.
	   * @param nfcnamingcode String
	   *****************************************************************************/
	  public void evel_nfcnamingcode_set(String nfcnam)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions and assign the new value.                           */
	    /***************************************************************************/
	    assert(nfcnam != null);
	    nfcnaming_code.set_option(true);
	    nfcnaming_code.SetValue(nfcnam);
	
	    EVEL_EXIT();
	  }	  
	
	  /**************************************************************************//**
	   * Set the NF Naming code property of the event header.
	   *
	   * @param header        Pointer to the ::EVENT_HEADER.
	   * @param nfnamingcode String
	   *****************************************************************************/
	  public void evel_nfnamingcode_set(String nfnam)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions and assign the new value.                           */
	    /***************************************************************************/
	    assert(nfnam != null);
	    nfnaming_code.set_option(true);
	    nfnaming_code.SetValue(nfnam);

	    EVEL_EXIT();
	  }
	  
	//VES 7.0 added 4Sept2018
	  /**************************************************************************//**
	   * Set the NF Vendor name property of the event header.
	   *
	   * @param header        Pointer to the ::EVENT_HEADER.
	   * @param nfVendorName String
	   *****************************************************************************/
	  public void evel_nfVendorName_set(String nfvendor)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions and assign the new value.                           */
	    /***************************************************************************/
	    assert(nfvendor != null);
	    nfVendor_name.set_option(true);
	    nfVendor_name.SetValue(nfvendor);

	    EVEL_EXIT();
	  }

	  
	  /**************************************************************************//**
	   * Set the NF Vendor name property of the event header.
	   *
	   * @param header        Pointer to the ::EVENT_HEADER.
	   * @param nfVendorName String
	   *****************************************************************************/
	  public void evel_timeZoneOffset_set(String timezoneset)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions and assign the new value.                           */
	    /***************************************************************************/
	    assert(timezoneset != null);
	    timeZoneOffset.set_option(true);
	    timeZoneOffset.SetValue(timezoneset);

	    EVEL_EXIT();
	  }
	  
	  
	  
	  /**************************************************************************//**
	   * Set the Ves Event Listener Version property of the event header.
	   *
	   * @note The Ves Event Listener Version defaults to the OpenStack VM Name.
	   *
	   * @param header        Pointer to the ::EVENT_HEADER.
	   * @param vesEventListenerVersion   The vesEventListenerVersion to set.
	   *****************************************************************************/
	  public void evel_vesEventListenerVersion_set(String vesEventListVersion)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions and assign the new value.                           */
	    /***************************************************************************/
	    assert(vesEventListVersion != null);

	    /***************************************************************************/
	    /* Free the previously allocated memory and replace it with a copy of the  */
	    /* provided one.                                                           */
	    /***************************************************************************/
	    ves_eventListener_version = vesEventListVersion;

	    EVEL_EXIT();
	  }
	  
	  
	 
	  /**************************************************************************//**
	   * Set the Reporting Entity Name property of the event header.
	   *
	   * @note The Reporting Entity Name defaults to the OpenStack VM Name.
	   *
	   * @param header        Pointer to the ::EVENT_HEADER.
	   * @param entity_name   The entity name to set.
	   *****************************************************************************/
	  public void evel_reporting_entity_name_set(String entity_name)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions and assign the new value.                           */
	    /***************************************************************************/
	    assert(entity_name != null);

	    /***************************************************************************/
	    /* Free the previously allocated memory and replace it with a copy of the  */
	    /* provided one.                                                           */
	    /***************************************************************************/
	    reporting_entity_name = entity_name;

	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the Reporting Entity Id property of the event header.
	   *
	   * @note The Reporting Entity Id defaults to the OpenStack VM UUID.
	   *
	   * @param header        Pointer to the ::EVENT_HEADER.
	   * @param entity_id     The entity id to set.
	   *****************************************************************************/
	  public void evel_reporting_entity_id_set(String entity_id)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions and assign the new value.                           */
	    /***************************************************************************/
	    assert(entity_id != null);

	    /***************************************************************************/
	    /* Free the previously allocated memory and replace it with a copy of the  */
	    /* provided one.  Note that evel_force_option_string strdups entity_id.    */
	    /***************************************************************************/
	    reporting_entity_id.set_option(true);
	    reporting_entity_id.SetValue(entity_id);

	    EVEL_EXIT();
	  }
	  
	  /**************************************************************************//**
	   * Set the Priority property of the event header.
	   *
	   * @note The Priority of event being reported.
	   *
	   * @param priorityval    Value of priority.
	   * 
	   *****************************************************************************/
	  public void evel_header_set_priority(PRIORITIES priority_val)
	  {
	    EVEL_ENTER();
	    
	    assert(EvelHeader.PRIORITIES.EVEL_MAX_PRIORITIES.compareTo(priority_val) >= 0 );
	    
	    priority = priority_val;

	    EVEL_EXIT();
	  }
	  
	  /**************************************************************************//**
	   * Set the Priority property of the event header.
	   *
	   * @note The Reporting Entity Id defaults to the OpenStack VM UUID.
	   *
	   * @param val       Optional true or false.
	   * @param srcid     The source id to set.
	   *****************************************************************************/
	  public void evel_header_set_sourceid(boolean val, String srcid)
	  {
	    EVEL_ENTER();
	    
	    assert(srcid != null);
	    
	    source_id.set_option(val);
	    
	    source_id.SetValue(srcid);

	    EVEL_EXIT();
	  }
	  
	  /**************************************************************************//**
	   * Set the Event Type property of the event header.
	   *
	   * @note The Reporting Entity Id defaults to the OpenStack VM UUID.
	   *
	   * @param val       Optional true or false
	   *****************************************************************************/
	  public void evel_header_set_eventType(String eventtype)
	  {
	    EVEL_ENTER();
	    
	    assert(event_type != null);
	    
	    event_type.set_option(true);
	    event_type.SetValue(eventtype);

	    EVEL_EXIT();
	  }
	  
	  
	  /**************************************************************************//**
	   * Set the Source name property of the event header.
	   *
	   * @note Source name should identify the IP address or Source Event originator
	   *       for inventory
	   *
	   * @param srcname  String for sourcename.
	   *****************************************************************************/
	  public void evel_header_set_source_name(String srcname)
	  {
	    EVEL_ENTER();
	    
	    assert(srcname != null);
	    
	    source_name = srcname;

	    EVEL_EXIT();
	  }
	  
	  /**************************************************************************//**
	   * Map an ::EVEL_EVENT_DOMAINS enum value to the equivalent string.
	   *
	   * @param domain        The domain to convert.
	   * @returns The equivalent string.
	   *****************************************************************************/
	  String evel_event_domain(DOMAINS domain)
	  {
	    String result;

	    EVEL_ENTER();

	    switch (domain)
	    {
	      case EVEL_DOMAIN_HEARTBEAT:
	        result = "heartbeat";
	        break;

	      case EVEL_DOMAIN_FAULT:
	        result = "fault";
	        break;

	      case EVEL_DOMAIN_MEASUREMENT:
	        result = "measurement";
	        break;

	      case EVEL_DOMAIN_REPORT:
	        result = "measurementsForVfReporting";
	        break;

	      case EVEL_DOMAIN_MOBILE_FLOW:
	        result = "mobileFlow";
	        break;

	      case EVEL_DOMAIN_HEARTBEAT_FIELD:
	        result = "heartbeat";
	        break;

	      case EVEL_DOMAIN_SIPSIGNALING:
	        result = "sipSignaling";
	        break;

	      case EVEL_DOMAIN_STATE_CHANGE:
	        result = "stateChange";
	        break;

	      case EVEL_DOMAIN_SYSLOG:
	        result = "syslog";
	        break;

	      case EVEL_DOMAIN_OTHER:
	        result = "other";
	        break;

	      case EVEL_DOMAIN_VOICE_QUALITY:
	        result = "voiceQuality";
	        break;

	      case EVEL_DOMAIN_THRESHOLD_CROSSING:
		        result = "thresholdCrossingAlert";
		        break;
	      case EVEL_DOMAIN_NOTIFICATION:
	    	  result="notification";
	    	  break;
	      
	      case EVEL_DOMAIN_PNFREGISTRATION:
	    	  result="pnfRegistration";
	    	  break;
	    	  
	      default:
	        result = null;
	        LOGGER.severe(MessageFormat.format("Unexpected domain {0}", domain));
	    }

	    EVEL_EXIT();

	    return result;
	  }

	  /**************************************************************************//**
	   * Map an ::EVEL_EVENT_PRIORITIES enum value to the equivalent string.
	   *
	   * @param priority      The priority to convert.
	   * @returns The equivalent string.
	   *****************************************************************************/
	  String evel_event_priority(PRIORITIES priority)
	  {
	    String result;

	    EVEL_ENTER();

	    switch (priority)
	    {
	      case EVEL_PRIORITY_HIGH:
	        result = "High";
	        break;

	      case EVEL_PRIORITY_MEDIUM:
	        result = "Medium";
	        break;

	      case EVEL_PRIORITY_NORMAL:
	        result = "Normal";
	        break;

	      case EVEL_PRIORITY_LOW:
	        result = "Low";
	        break;

	      default:
	        result = null;
	        LOGGER.severe(MessageFormat.format("Unexpected priority {0}", priority));
	    }

	    EVEL_EXIT();

	    return result;
	  }
	  
	  /**************************************************************************//**
	   * Encode the CommonEventHeaeder as a JSON event object builder
	   * according to AT&T's schema.
	   *
	   * @retval JsonObjectBuilder of fault body portion of message   
	   *****************************************************************************/
	  JsonObjectBuilder eventHeaderObject()
	  {
	    String domain = evel_event_domain(event_domain);
	    String prity = evel_event_priority(priority);
	  //  double version = major_version+(double)minor_version/10;
	    String version = "4.1";
	    EVEL_ENTER();
	    
	    /***************************************************************************/
	    /* Required fields.                                                        */
	    /***************************************************************************/
	    
	    JsonObjectBuilder commheader = Json.createObjectBuilder()
	         	 .add("vesEventListenerVersion", ves_eventListener_version)
	   	         .add("domain", domain)
	   	         .add("eventId", event_id)
	   	         .add("eventName", event_name)
	   	         .add("lastEpochMicrosec", last_epoch_microsec)
	   	         .add("priority", prity)
	   	         .add("reportingEntityName", reporting_entity_name)
	   	         .add("sequence", sequence)
	   	         .add("sourceName", source_name)
	   	         .add("startEpochMicrosec", start_epoch_microsec)
	   	         .add("version", version)
	   	         .add("reportingEntityId", reporting_entity_id.GetValue())
	   	         .add("sourceId", source_id.GetValue());
	             
	    /***************************************************************************/
	    /* Optional fields.                                                        */
	    /***************************************************************************/
	    
	    commheader.add("eventType", event_type.GetValue());
	    if( event_type.is_set )
//	    	commheader.add("eventType", event_type.GetValue());
//	    if( source_id.is_set )
//	    	commheader.add("sourceId", source_id.GetValue());
//	    if( reporting_entity_id.is_set )
//	    	commheader.add("reportingEntityId", reporting_entity_id.GetValue());
//	    
	    if( internal_field.is_set )
	    	commheader.add("internalField",internal_field.toString());	    
	    
	    if( nfcnaming_code.is_set )
	    	commheader.add("nfcNamingCode", nfcnaming_code.GetValue());
	    if( nfnaming_code.is_set )
	    	commheader.add("nfNamingCode", nfnaming_code.GetValue());
	    
	    //VES 7.0 added 4Sept2018
	    if( nfVendor_name.is_set )
	    	commheader.add("nfVendorName", nfVendor_name.GetValue());
	    if( timeZoneOffset.is_set )
	    	commheader.add("timeZoneOffset", timeZoneOffset.GetValue());
	    
	    
	    EVEL_EXIT();
	    
	    return commheader;

	  }


	  /**************************************************************************//**
	   * Encode the event as a JSON event object according to AT&T's schema.
	   * retval : String of JSON event header only message
	   *****************************************************************************/
  	  JsonObject evel_json_encode_event()
	  {	        
	    JsonObject obj = Json.createObjectBuilder()   		
	    		.add("event", Json.createObjectBuilder()	
		        .add("commonEventHeader",eventHeaderObject())
		       ).build();

	    EVEL_EXIT();
	    
	    return obj;

	  }   
	  
	  JsonObject evel_json_encode_event_batch()
	  {
	        
	    JsonObject obj = Json.createObjectBuilder()
	    	        //   .add("event", Json.createObjectBuilder())
		    	         .add("commonEventHeader",eventHeaderObject()).build();

	    EVEL_EXIT();
	    
	    return obj;

	  }
	  
	  

}
