package evel_javalibrary.att.com;

import java.text.MessageFormat;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Map.Entry;

import javax.json.Json;
import javax.json.JsonArrayBuilder;
import javax.json.JsonObject;
import javax.json.JsonObjectBuilder;

import org.apache.log4j.Logger;

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

public class EvelPnfRegistration extends EvelHeader{
	
	int major_version = 1;
	int minor_version = 0;

	/***************************************************************************/
	  /* Mandatory fields                                                        */
	  /***************************************************************************/
	EvelOptionString pnfRegistrationFieldsVersion;
	  
	  
	/***************************************************************************/
	/* Optional fields                                                         */
	/***************************************************************************/
	
	EvelOptionString lastServiceDate;
	EvelOptionString macAddress;
	EvelOptionString manufactureDate;
	EvelOptionString modelNumber;	
	EvelOptionString oamV4IpAddress;
	EvelOptionString oamV6IpAddress;
//	EvelOptionDouble pnfRegistrationFieldsVersion;
	EvelOptionString serialNumber;
	EvelOptionString softwareVersion;
	EvelOptionString unitFamily;
	EvelOptionString unitType;
	EvelOptionString vendorName;
	
	//ArrayList<String[]> additional_info;
	HashMap<String, String > additional_inf;
	
	private static final Logger LOGGER = Logger.getLogger( EvelNotification.class.getName() );

	public EvelPnfRegistration(String eventname, String ev_id) {
		super(eventname, ev_id);
		// TODO Auto-generated constructor stub
	
		event_domain = EvelHeader.DOMAINS.EVEL_DOMAIN_PNFREGISTRATION;
		lastServiceDate = new EvelOptionString();
		macAddress = new EvelOptionString();
		manufactureDate = new EvelOptionString();
		modelNumber = new EvelOptionString();
		oamV4IpAddress = new EvelOptionString();
		oamV6IpAddress =new EvelOptionString();
		pnfRegistrationFieldsVersion = new EvelOptionString();
		
		serialNumber = new EvelOptionString();
		softwareVersion = new EvelOptionString();
		unitFamily = new EvelOptionString();
		unitType =new EvelOptionString();
		vendorName =new EvelOptionString();
		
		
		additional_inf=null;

	
	}
	
	public void evel_pnrregistration_addl_info_add(String name, String value)
	{
	 // String[] addl_info = null;
      
	  EVEL_ENTER();

	  /***************************************************************************/
	  /* Check preconditions.                                                    */
	  /***************************************************************************/
	  assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_PNFREGISTRATION);
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
	
	public void evel_pnrregistration_add_lastServiceDate_set(String lastSerDate) {
		EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_PNFREGISTRATION);
	    assert(lastSerDate != null);

	    lastServiceDate.SetValuePr(
	    		lastSerDate,
	                           "pnr registration last service date String");

	    EVEL_EXIT();
	}
	
	public void evel_pnrregistration_add_macaddress_set(String macAdddr) {
		EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_PNFREGISTRATION);
	    assert(macAdddr != null);

	    macAddress.SetValuePr(
	    		macAdddr,
	                           "MAC address of OAM interface of the unit");

	    EVEL_EXIT();
	}
	
	public void evel_pnrregistration_add_manufactureDate_set(String manufacDate) {
		EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_PNFREGISTRATION);
	    assert(manufacDate != null);

	    manufactureDate.SetValuePr(
	    		manufacDate,
	                           "pnr registration manufacture date String");

	    EVEL_EXIT();
	}
	
	public void evel_pnrregistration_add_modelNumber_set(String modelNum) {
		EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_PNFREGISTRATION);
	    assert(modelNum != null);

	    modelNumber.SetValuePr(
	    		modelNum,
	                           "pnr registration model number String");

	    EVEL_EXIT();
	}
	
	public void evel_pnrregistration_add_oamV4IpAddress_set(String oamv4ipAddr) {
		EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_PNFREGISTRATION);
	    assert(oamv4ipAddr != null);

	    oamV4IpAddress.SetValuePr(
	    		oamv4ipAddr,
	                           "pnr registration oamv4ipaddress String");

	    EVEL_EXIT();
	}
	
	public void evel_pnrregistration_add_oamV6IpAddress_set(String oamv6ipAddr) {
		EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_PNFREGISTRATION);
	    assert(oamv6ipAddr != null);

	    oamV6IpAddress.SetValuePr(
	    		oamv6ipAddr,
	                           "pnr registration oamv6ipaddress String");

	    EVEL_EXIT();
	}

	public void evel_pnfRegistrationFieldsVersion_set(String feildVersion) {
		EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_PNFREGISTRATION);
	    assert(feildVersion != null);

	    pnfRegistrationFieldsVersion.SetValuePr(
	    		feildVersion,
	                           "Version of the registrationFields block");

	    EVEL_EXIT();
	}
	
	
	public void evel_pnfRegistration_serialNumber_set(String srNo) {
		EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_PNFREGISTRATION);
	    assert(srNo != null);

	    serialNumber.SetValuePr(
	                           srNo,
	                           "serial number of the unit");

	    EVEL_EXIT();
	}
	public void evel_pnfRegistration_softwareVersion_set(String softwareVers) {
		EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_PNFREGISTRATION);
	    assert(softwareVers != null);

	    softwareVersion.SetValuePr(
	    						softwareVers,
	                           "active SW running on the unit");

	    EVEL_EXIT();
	}	
	public void evel_pnfRegistration_unitFamily_set(String unitFamily) {
		EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_PNFREGISTRATION);
	    assert(unitFamily != null);

	    this.unitFamily.SetValuePr(
	    						unitFamily,
	                           "vendor Unit Family Type ");

	    EVEL_EXIT();
	}	
	public void evel_pnfRegistration_unitType_set(String unitType) {
		EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_PNFREGISTRATION);
	    assert(unitType != null);

	    this.unitType.SetValuePr(
	    						unitType,
	                           "vendor Unit Family Type ");

	    EVEL_EXIT();
	}
	public void evel_pnfRegistration_vendorName_set(String vendorName) {
		EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_PNFREGISTRATION);
	    assert(vendorName != null);

	    this.vendorName.SetValuePr(
	    						vendorName,
	                           "name of manufacturer");

	    EVEL_EXIT();
	}
	
	JsonObjectBuilder evelPnfRegistrationObject()
	 {
	  //String evt_source_type;
	  //double version = major_version+(double)minor_version/10;
        String version = "2.0";
	  EVEL_ENTER();
	  
	  assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_PNFREGISTRATION);
	  
	  /***************************************************************************/
	  /* Mandatory fields                                                        */
	  /***************************************************************************/
	  JsonObjectBuilder obj = Json.createObjectBuilder();
			    	      //   .add("pnfRegistrationFieldsVersion", version); 
	  //pnfRegistrationFieldsVersion.encJsonValue(obj, version);
	  /***************************************************************************/
	  /* Optional fields                                                         */
	  /***************************************************************************/
	  serialNumber.encJsonValue(obj, "serialNumber");
	  modelNumber.encJsonValue(obj, "modelNumber");
	  lastServiceDate.encJsonValue(obj,"lastServiceDate");
	  macAddress.encJsonValue(obj,"macAddress");
	  manufactureDate.encJsonValue(obj, "manufactureDate");
	  oamV4IpAddress.encJsonValue(obj, "oamV4IpAddress");
	  oamV6IpAddress.encJsonValue(obj, "oamV6IpAddress");
	 // pnfRegistrationFieldsVersion.encJsonValue(obj, "pnfRegistrationFieldsVersion");
	 //  serialNumber.encJsonValue(obj, "serialNumber");
	  softwareVersion.encJsonValue(obj, "softwareVersion");
	  unitFamily.encJsonValue(obj, "unitFamily");
	  unitType.encJsonValue(obj, "unitType");
	  vendorName.encJsonValue(obj, "vendorName");
	  obj.add("pnfRegistrationFieldsVersion", version); 
	  
	  
	  if(additional_inf != null) {
		//  JsonArrayBuilder builder = Json.createArrayBuilder();
		  JsonObjectBuilder builder = Json.createObjectBuilder();
		  Iterator<Entry<String, String>> it = additional_inf.entrySet().iterator();
		  while(it.hasNext()) {
			  Map.Entry<String, String> add_inf = (Map.Entry<String, String>)it.next();
			  String addl_info_key = add_inf.getKey();
			  String addl_info_value = add_inf.getValue();
//			  JsonObject obj1 = Json.createObjectBuilder()
//			    	     .add("name", addl_info_key)
//			    	     .add("value", addl_info_value).build();
			  builder.add(addl_info_key, addl_info_value);
		  }
		  obj.add("additionalFields", builder);
	  }
	  
	  

	  EVEL_EXIT();
	  
	  return obj;
	}
  
	  /**************************************************************************//**
	   * Encode the event as a JSON event object according to AT&T's schema.
	   * retval : String of JSON event message
	   *****************************************************************************/
	  JsonObject evel_json_encode_event()
	  {
		assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_PNFREGISTRATION);
		//encode common event header and body     
	    JsonObject obj = Json.createObjectBuilder()
	    	     .add("event", Json.createObjectBuilder()
		    	         .add( "commonEventHeader",eventHeaderObject() )
		    	         .add( "pnfRegistrationFields",evelPnfRegistrationObject() )
		    	         ).build();

	    EVEL_EXIT();
	    
	    return obj;

	  }	
	


}
