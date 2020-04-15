package evel_javalibrary.att.com;
/**************************************************************************//**
 * @file
 * Evel Syslog class
 *
  * This file implements the Evel Syslog Event class which is intended to provide a
 * simple wrapper around the complexity of AT&T's Vendor Event Listener API so
 * that VNFs can use it to send Syslog events.
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
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Map.Entry;

import javax.json.Json;
import javax.json.JsonArrayBuilder;
import javax.json.JsonObject;
import javax.json.JsonObjectBuilder;

import org.apache.log4j.Logger;



public class EvelSyslog extends EvelHeader {
	
	int major_version = 3;
	int minor_version = 0;
	
	
	/**************************************************************************//**
	 * Alert types.
	 * JSON equivalent fields: newState, oldState
	 *****************************************************************************/
	/**************************************************************************//**
	 * Syslog facilities.
	 * JSON equivalent field: syslogFacility
	 *****************************************************************************/
	public enum EVEL_SYSLOG_FACILITIES{
	  EVEL_SYSLOG_FACILITY_KERNEL,
	  EVEL_SYSLOG_FACILITY_USER,
	  EVEL_SYSLOG_FACILITY_MAIL,
	  EVEL_SYSLOG_FACILITY_SYSTEM_DAEMON,
	  EVEL_SYSLOG_FACILITY_SECURITY_AUTH,
	  EVEL_SYSLOG_FACILITY_INTERNAL,
	  EVEL_SYSLOG_FACILITY_LINE_PRINTER,
	  EVEL_SYSLOG_FACILITY_NETWORK_NEWS,
	  EVEL_SYSLOG_FACILITY_UUCP,
	  EVEL_SYSLOG_FACILITY_CLOCK_DAEMON,
	  EVEL_SYSLOG_FACILITY_SECURITY_AUTH2,
	  EVEL_SYSLOG_FACILITY_FTP_DAEMON,
	  EVEL_SYSLOG_FACILITY_NTP,
	  EVEL_SYSLOG_FACILITY_LOG_AUDIT,
	  EVEL_SYSLOG_FACILITY_LOG_ALERT,
	  EVEL_SYSLOG_FACILITY_CLOCK_DAEMON2,
	  EVEL_SYSLOG_FACILITY_LOCAL0,
	  EVEL_SYSLOG_FACILITY_LOCAL1,
	  EVEL_SYSLOG_FACILITY_LOCAL2,
	  EVEL_SYSLOG_FACILITY_LOCAL3,
	  EVEL_SYSLOG_FACILITY_LOCAL4,
	  EVEL_SYSLOG_FACILITY_LOCAL5,
	  EVEL_SYSLOG_FACILITY_LOCAL6,
	  EVEL_SYSLOG_FACILITY_LOCAL7,
	  EVEL_MAX_SYSLOG_FACILITIES
	}


	
	/***************************************************************************/
	/* Mandatory fields                                                        */
	/***************************************************************************/
	  EvelFault.EVEL_SOURCE_TYPES event_source_type;
	  String syslog_msg;
	  String syslog_tag;

	/***************************************************************************/
	/* Optional fields                                                         */
	/***************************************************************************/
	  EvelOptionString additional_filters;
	  EvelOptionString event_source_host;
	  EvelOptionInt syslog_facility;
	  EvelOptionInt syslog_priority;
	  EvelOptionString syslog_proc;
	  EvelOptionInt syslog_proc_id;
	  EvelOptionString syslog_s_data;
	  EvelOptionString syslog_sdid;
	  EvelOptionString syslog_severity;
	  double syslog_fver;
	  EvelOptionInt syslog_ver;
	  EvelOptionString syslogmsg_host;
	  
	  EvelOptionString syslogTs;
	  
	  HashMap<String, String > additional_inf;

	
	  private static final Logger LOGGER = Logger.getLogger( EvelSyslog.class.getName() );

	  /**************************************************************************//**
	   * Create a new Syslog event.
	   *
	   *
	   * @param syslg_msg     The Syslog message string.
	   * @param syslg_tag     The Syslog tag string.
	   * @param interface     The card or port name of the reporting entity.
	   *
	   *****************************************************************************/
	public EvelSyslog(String evname, String evid,
			EvelFault.EVEL_SOURCE_TYPES evt_source_type,
                      String syslg_msg,
                      String syslg_tag)
	{
		super(evname,evid);
		event_domain = EvelHeader.DOMAINS.EVEL_DOMAIN_SYSLOG;
	    assert(EvelFault.EVEL_SOURCE_TYPES.EVEL_MAX_SOURCE_TYPES.compareTo(evt_source_type) >= 0);
	    assert(syslg_msg != null);
	    assert(syslg_tag != null);

	    event_source_type = evt_source_type;
	    syslog_msg = syslg_msg;
	    syslog_tag = syslg_tag;
	    syslog_facility = new EvelOptionInt();
	    syslog_priority = new EvelOptionInt();
	    syslog_proc_id = new EvelOptionInt();
	    syslog_ver = new EvelOptionInt();
	    additional_filters = new EvelOptionString();
	    event_source_host = new EvelOptionString();
	    syslog_proc = new EvelOptionString();
	    syslog_s_data = new EvelOptionString();
	    syslog_sdid = new EvelOptionString();
	    syslog_severity = new EvelOptionString();	
	    
	    syslogmsg_host = new EvelOptionString();	
	    
	    syslogTs = new EvelOptionString();	
	    
	    
	    additional_inf =null;
	}	  
	  
	  /**************************************************************************//**
	   * Set the Event Type property of the Syslog.
	   *
	   * @param type        The Event Type to be set. ASCIIZ string. The caller
	   *                    does not need to preserve the value once the function
	   *                    returns.
	   *****************************************************************************/
	  public void evel_syslog_type_set(String typ)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions and call evel_header_type_set.                      */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_SYSLOG);
	    evel_header_type_set(typ);

	    EVEL_EXIT();
	  }
	  
	  //VES 7.O added 4Sept2018
	  /**************************************************************************//**
	   * Add an additional value name/value pair to the Syslog.
	   *
	   * The name and value are null delimited ASCII strings.  The library takes
	   * a copy so the caller does not have to preserve values after the function
	   * returns.
	   *
	   * 
	   * @param name      ASCIIZ string with the attribute's name.  The caller
	   *                  does not need to preserve the value once the function
	   *                  returns.
	   * @param value     ASCIIZ string with the attribute's value.  The caller
	   *                  does not need to preserve the value once the function
	   *                  returns.
	   *****************************************************************************/
	  public void evel__syslog_addl_info_add(String name, String value)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_SYSLOG);
	    assert(name != null);
		assert(value != null);

		if( additional_inf == null )
		  {
			  additional_inf = new HashMap<>();
		  }
		
		LOGGER.debug(MessageFormat.format("Adding name={0} value={1}", name, value));
		additional_inf.put(name,  value);
		
	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Add an additional value name/value pair to the Syslog.
	   *
	   * The name and value are null delimited ASCII strings.  The library takes
	   * a copy so the caller does not have to preserve values after the function
	   * returns.
	   *
	   * 
	   * @param name      ASCIIZ string with the attribute's name.  The caller
	   *                  does not need to preserve the value once the function
	   *                  returns.
	   * @param value     ASCIIZ string with the attribute's value.  The caller
	   *                  does not need to preserve the value once the function
	   *                  returns.
	   *****************************************************************************/
	  public void evel_syslog_addl_filter_set(String filter) 
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_SYSLOG);
	    assert(filter != null);

	    additional_filters.SetValuePr(
	                           filter,
	                           "Syslog filter string");

	    EVEL_EXIT();
	  }
	  
	  
	  
	  /**************************************************************************//**
	   * Set the Event Source Host property of the Syslog.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * 
	   * @param host       The Event Source Host to be set. ASCIIZ string. The caller
	   *                   does not need to preserve the value once the function
	   *                   returns.
	   *****************************************************************************/
	  public void evel_syslog_priority_set(int priority)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_SYSLOG);
	    assert(priority > 0);

	    syslog_priority.SetValuePr(
	    		priority,
	                        "Priority");
	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the Event Source Host property of the Syslog.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * 
	   * @param host       The Event Source Host to be set. ASCIIZ string. The caller
	   *                   does not need to preserve the value once the function
	   *                   returns.
	   *****************************************************************************/
	  public void evel_syslog_event_source_host_set(String host)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_SYSLOG);
	    assert(host != null);

	    event_source_host.SetValuePr(
	                           host,
	                           "Event Source Host");
	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the Facility property of the Syslog.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param syslog      Pointer to the Syslog.
	   * @param facility    The Syslog Facility to be set.  ASCIIZ string. The caller
	   *                    does not need to preserve the value once the function
	   *                    returns.
	   *****************************************************************************/
	  public void evel_syslog_facility_set(
	                                EVEL_SYSLOG_FACILITIES facility)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_SYSLOG);
	    assert(facility.compareTo(EVEL_SYSLOG_FACILITIES.EVEL_MAX_SYSLOG_FACILITIES) < 0);
	    int num = facility.compareTo(EVEL_SYSLOG_FACILITIES.EVEL_SYSLOG_FACILITY_KERNEL);

	    syslog_facility.SetValuePr(
	                        num,
	                        "Facility");
	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the Process property of the Syslog.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * 
	   * @param proc       The Process to be set. ASCIIZ string. The caller does not
	   *                   need to preserve the value once the function returns.
	   *****************************************************************************/
	  public void evel_syslog_proc_set(String proc)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_SYSLOG);
	    assert(proc != null);

	    syslog_proc.SetValuePr(proc, "Process");
	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the Process ID property of the Syslog.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * 
	   * @param proc_id    The Process ID to be set. ASCIIZ string. The caller does
	   *                   not need to preserve the value once the function returns.
	   *****************************************************************************/
	  public void evel_syslog_proc_id_set(int proc_id)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_SYSLOG);
	    assert(proc_id > 0);

	    syslog_proc_id.SetValuePr(
	                        proc_id,
	                        "Process ID");
	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the Version property of the Syslog.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * 
	   * @param version    The Version to be set. ASCIIZ string. The caller does not
	   *                   need to preserve the value once the function returns.
	   *****************************************************************************/
	  public void evel_syslog_version_set(int version)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_SYSLOG);
	    assert(version >= 0);

	    syslog_ver.SetValuePr(
	                        version,
	                        "Version");
	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the Structured Data property of the Syslog.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * 
	   * @param s_data     The Structured Data to be set. ASCIIZ string. The caller
	   *                   does not need to preserve the value once the function
	   *                   returns.
	   *****************************************************************************/
	  public void evel_syslog_s_data_set(String s_data)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_SYSLOG);
	    assert(s_data != null);

	    syslog_s_data.SetValuePr(
	                           s_data,
	                           "Structured Data");
	    EVEL_EXIT();
	  }
	  
	  
	  /**************************************************************************//**
	   * Set the Structured SDID property of the Syslog.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * 
	   * @param sdid     The Structured Data to be set. ASCIIZ string. name@number
	   *                 Caller does not need to preserve the value once the function
	   *                   returns.
	   *****************************************************************************/
	  public void evel_syslog_msghost_set(String msghost)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_SYSLOG);
	    assert(msghost != null);

	    syslogmsg_host.SetValuePr(
	    		msghost,
	                           "SysLog msg log");
	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the Structured SDID property of the SyslogTs.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * 
	   * @param sdid     The Structured Data to be set. ASCIIZ string. name@number
	   *                 Caller does not need to preserve the value once the function
	   *                   returns.
	   *****************************************************************************/
	  public void evel_syslogTs_set(String syslogT)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_SYSLOG);
	    assert(syslogT != null);

	    syslogTs.SetValuePr(syslogT, "SyslogTs");
	    EVEL_EXIT();
	  }
	  
	  /**************************************************************************//**
	   * Set the Structured SDID property of the Syslog.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * 
	   * @param sdid     The Structured Data to be set. ASCIIZ string. name@number
	   *                 Caller does not need to preserve the value once the function
	   *                   returns.
	   *****************************************************************************/
	  public void evel_syslog_sdid_set(String sdid)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_SYSLOG);
	    assert(sdid != null);

	    syslog_sdid.SetValuePr(
	                           sdid,
	                           "SdId set");
	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the Structured Severity property of the Syslog.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * 
	   * @param sdid     The Structured Data to be set. ASCIIZ string. 
	   *                 Caller does not need to preserve the value once the function
	   *                   returns.
	   *****************************************************************************/
	  public void evel_syslog_severity_set(String severty)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_SYSLOG);
	    assert(severty != null);

	    if( severty.equals("Alert") || severty.equals("Critical") || severty.equals("Debug") ||
	    		severty.equals("Emergency") || severty.equals("Error") || severty.equals("Info") ||
	    		severty.equals("Notice") || severty.equals("Warning") )
	    {
	       syslog_severity.SetValuePr(
	                           severty,
	                           "Severity set");
	    }
	    EVEL_EXIT();
	  }
	  
	  

	
	  
		/**************************************************************************//**
		 * Encode the Syslog in JSON according to AT&T's schema.
		 *
		 *****************************************************************************/
		 JsonObjectBuilder evelSyslogObject()
		 {
		  String evt_source_type;
		//  double version = major_version+(double)minor_version/10;
          String version = "4.0";
		  EVEL_ENTER();
		  
		  assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_SYSLOG);
		  
		  /***************************************************************************/
		  /* Mandatory fields                                                        */
		  /***************************************************************************/
		  JsonObjectBuilder obj = Json.createObjectBuilder()
		   	         .add("eventSourceType", EvelFault.evel_source_type(event_source_type))
		   	         .add("syslogMsg", syslog_msg)
		   	         .add("syslogTag", syslog_tag)
		   	         .add("syslogFieldsVersion",version);

		  /***************************************************************************/
		  /* Optional fields                                                         */
		  /***************************************************************************/
		  event_source_host.encJsonValue(obj, "eventSourceHost");
		  syslog_facility.encJsonValue(obj,"syslogFacility");
		  syslog_priority.encJsonValue(obj,"syslogPri");
		  syslog_proc.encJsonValue(obj, "syslogProc");
		  syslog_proc_id.encJsonValue(obj, "syslogProcId");
		  syslog_s_data.encJsonValue(obj, "syslogSData");
		  syslog_sdid.encJsonValue(obj, "syslogSdId");
		  syslog_severity.encJsonValue(obj, "syslogSev");
		  syslog_ver.encJsonValue(obj, "syslogVer");
		  syslogmsg_host.encJsonValue(obj, "syslogMsgHost");
		  
		  syslogTs.encJsonValue(obj, "syslogTs");
		  
		  
		  if(additional_inf != null) {
			  //JsonArrayBuilder builder = Json.createArrayBuilder();
			  JsonObjectBuilder builder = Json.createObjectBuilder();
			  Iterator<Entry<String, String>> it = additional_inf.entrySet().iterator();
			  while(it.hasNext()) {
				  Map.Entry<String, String> add_inf = (Map.Entry<String, String>)it.next();
				  String addl_info_key = add_inf.getKey();
				  String addl_info_value = add_inf.getValue();
//				  JsonObject obj1 = Json.createObjectBuilder()
//				    	     .add("name", addl_info_key)
//				    	     .add("value", addl_info_value).build();
				  builder.add(addl_info_key, addl_info_value);
			  }
			  obj.add("additionalFields", builder);
		  }
		  

		  EVEL_EXIT();
		  
		  return obj;
		}	
	
	/**************************************************************************//**
     * Encode the event as a JSON event object according to AT&T's schema.
     * retval : String of JSON syslog event message
     *****************************************************************************/
      public JsonObject evel_json_encode_event()
	  {
		EVEL_ENTER();
		
		assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_SYSLOG);
	        
	    JsonObject obj = Json.createObjectBuilder()
	    	     .add("event", Json.createObjectBuilder()
		    	         .add( "commonEventHeader",eventHeaderObject() )
		    	         .add( "syslogFields",evelSyslogObject() )
		    	         ).build();

	    EVEL_EXIT();
	    
	    return obj;

	  }
      
      public JsonObject evel_json_encode_event_batch()
	  {
		EVEL_ENTER();
		
		assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_SYSLOG);
	        
	    JsonObject obj = Json.createObjectBuilder()
	    	    // .add("event", Json.createObjectBuilder()
		    	         .add( "commonEventHeader",eventHeaderObject() )
		    	         .add( "syslogFields",evelSyslogObject() )
		    	         .build();

	    EVEL_EXIT();
	    
	    return obj;

	  }
	  
	  
	

}
