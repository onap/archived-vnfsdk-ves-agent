package evel_javalibrary.att.com;

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



import java.text.MessageFormat;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;

import javax.json.Json;
import javax.json.JsonArrayBuilder;
import javax.json.JsonObject;
import javax.json.JsonObjectBuilder;

import org.apache.log4j.Logger;

public class EvelNotification extends EvelHeader {
	int major_version = 1;
	int minor_version = 0;
	
	
	/***************************************************************************/
	/* Mandatory fields                                                        */
	/***************************************************************************/
	String changeType = null;
	String changeIdentifier;
	//ArrayList<String[]> additional_info;
	HashMap<String, String > additional_inf;
	
	
	/***************************************************************************/
	/* Optional fields                                                         */
	/***************************************************************************/
	
	EvelOptionString newState;
	EvelOptionString oldState;
	EvelOptionString changeContact;
	EvelOptionString stateInterface;
	
	
	ArrayList<javax.json.JsonObject> additional_objects;
	Map<String,Map<String,String>> evelmap;
	
	private static final Logger LOGGER = Logger.getLogger( EvelNotification.class.getName() );
	
	public EvelNotification(String eventname, String ev_id, String change_identifier, String change_type) {
		super(eventname, ev_id);
		// TODO Auto-generated constructor stub
		event_domain = EvelHeader.DOMAINS.EVEL_DOMAIN_NOTIFICATION;
		changeType = change_type;
		newState = new EvelOptionString();
		oldState = new EvelOptionString();
		changeContact = new EvelOptionString();
		stateInterface = new EvelOptionString();
		changeIdentifier = change_identifier;
		
		
		//additional_info=null;
		additional_inf =null;
		
		additional_objects = null;
		evelmap = null;
	}
	
	/**************************************************************************//**
	   * Set the Event Type property of the Notification.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   
	   * @param type        The Event Type to be set. ASCIIZ string. The caller
	   *                    does not need to preserve the value once the function
	   *                    returns.
	   *****************************************************************************/
	public void evel_notification_type_set(String typ)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions and call evel_header_type_set.                      */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_NOTIFICATION);
	    evel_header_type_set(typ);

	    EVEL_EXIT();
	  }
	
	
	
	  /**************************************************************************//**
	   * Adds name value pair under hash key
	   *
	   *
	   * @param hashname String         Hash name.
	   * @param name String             Name.
	   * @param value String            Value.
	   *****************************************************************************/
	  public void evel_notification_add_namedarray(String hashname,String name, String value)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_NOTIFICATION);
	    assert(hashname != null);
	    assert(name != null);
	    assert(value != null);
	    
	    Map<String,String> mymap = null;
	    
      try{

          if( evelmap == null)
                  evelmap = new HashMap<String,Map<String,String>>();

          if( evelmap.containsKey(hashname) )
          {
                  mymap = evelmap.get(hashname);
          }
          else
          {
                  mymap = new HashMap<String,String>();
                  evelmap.put(hashname, mymap);
                  LOGGER.debug("Inserted map hash : "+hashname+" name="+name);
          }

          if( mymap.containsKey(name) )
          {
                  String val = mymap.get(name);
                  LOGGER.error("Error already contains key " + name + "val "+val );
          }
          else
          {
                  mymap.put(name, value);
                  LOGGER.debug("Adding hash : "+hashname+" name="+name+"value= "+value);
          }

      } catch( Exception e)
      {
          
      }

	    EVEL_EXIT();
	  }

	
	
	  /**************************************************************************//**
	   * Add a json object to optional jsonObject list.
	   *
	   * @param jsonobj   Pointer to json object
	   *****************************************************************************/
	  public void evel_other_field_add_jsonobj(javax.json.JsonObject  jsonobj)
	  {

	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_OTHER);
	    assert(jsonobj != null);

	    LOGGER.debug("Adding jsonObject");
	    
	    if( additional_objects == null )
	    	additional_objects = new ArrayList<javax.json.JsonObject>();
	    
	    additional_objects.add(jsonobj);

	    EVEL_EXIT();
	  }

	
	
	
	
	public void evel_notification_addl_info_add(String name, String value)
	{
	  //String[] addl_info = null;
	  EVEL_ENTER();

	  /***************************************************************************/
	  /* Check preconditions.                                                    */
	  /***************************************************************************/
	  assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_NOTIFICATION);
	  assert(name != null);
	  assert(value != null);
	  
	  if( additional_inf == null )
	  {
		 // additional_info = new ArrayList<String[]>();
		  additional_inf = new HashMap<>();
	  }

	  LOGGER.debug(MessageFormat.format("Adding name={0} value={1}", name, value));
	  //addl_info = new String[2];
	  //assert(addl_inf != null);
	  //addl_info[0] = name;
	  //addl_info[1] = value;
	  additional_inf.put(name,  value);

	 // additional_info.add(addl_info);

	  EVEL_EXIT();
	}
	
	
	
//	public void evel_notification_add_changeType_set(String changeTyp) {
//		EVEL_ENTER();
//
//	    /***************************************************************************/
//	    /* Check preconditions.                                                    */
//	    /***************************************************************************/
//	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_NOTIFICATION);
//	    assert(changeTyp != null);
//
//	    changeType.SetValuePr(
//	                           changeTyp,
//	                           "notification ChangeType String");
//
//	    EVEL_EXIT();
//	}
	public void evel_notification_add_newState_set(String newStat ){
		EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_NOTIFICATION);
	    assert(newStat != null);

	    newState.SetValuePr(
	                           newStat,
	                           "notification newState String");

	    EVEL_EXIT();
	}
	public void evel_notification_add_oldState_set(String oldStat) {
		EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_NOTIFICATION);
	    assert(oldStat != null);

	    oldState.SetValuePr(
	                           oldStat,
	                           "notification OldState String");

	    EVEL_EXIT();
	}
	public void evel_notification_add_changeContact_set(String changeCont) {
		EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_NOTIFICATION);
	    assert(changeCont != null);

	    changeContact.SetValuePr(
	                           changeCont,
	                           "notification ChangeContact String");

	    EVEL_EXIT();
	}
	public void evel_notification_add_stateInterface_set(String statInter) {
		EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_NOTIFICATION);
	    assert(statInter != null);

	    stateInterface.SetValuePr(
	                           statInter,
	                           "notification StateInterface String");

	    EVEL_EXIT();
	}
//	public void evel_notification_add_changeIdentifier_set(double changeId) {
//		EVEL_ENTER();
//
//	    /***************************************************************************/
//	    /* Check preconditions.                                                    */
//	    /***************************************************************************/
//	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_NOTIFICATION);
//	    assert(changeId > 0.0);
//
//	    changeIdentifier.SetValuePr(
//	                           changeId,
//	                           "notification ChangeIdentifier Integer");
//
//	    EVEL_EXIT();
//	}
//	public void evel_notification_add_notificationsFieldVersion_set(int stateChangeFieldsVer) {
//		EVEL_ENTER();
//
//	    /***************************************************************************/
//	    /* Check preconditions.                                                    */
//	    /***************************************************************************/
//	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_NOTIFICATION);
//	    assert(stateChangeFieldsVer > 0);
//
//	    notificationsFieldVersion.SetValuePr(
//	    		stateChangeFieldsVer,
//	                           "notification notificationsFieldVersion Int");
//
//	    EVEL_EXIT();
//	}
//	
	/**************************************************************************//**
	 * Encode the Syslog in JSON according to AT&T's schema.
	 *
	 *****************************************************************************/
	 JsonObjectBuilder evelNotificationObject()
	 {
	  //String evt_source_type;
	  //double version = major_version+(double)minor_version/10;
        String version = "2.0";       
	  EVEL_ENTER();
	  
	  assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_NOTIFICATION);
	  
	  /***************************************************************************/
	  /* Mandatory fields                                                        */
	  /***************************************************************************/
	  JsonObjectBuilder obj = Json.createObjectBuilder()
			  	 .add("changeIdentifier", changeIdentifier)
	   	         .add("changeType", changeType)
	   	         .add("notificationFieldsVersion",version);
	  
	  

	  /***************************************************************************/
	  /* Optional fields                                                         */
	  /***************************************************************************/
	  newState.encJsonValue(obj, "newState");
	  oldState.encJsonValue(obj,"oldState");
	  changeContact.encJsonValue(obj,"changeContact");
	  stateInterface.encJsonValue(obj, "stateInterface");
	// additional fields
//	  if( additional_info != null )
//	  {
//	    JsonArrayBuilder builder = Json.createArrayBuilder();
//	    for(int i=0;i<additional_info.size();i++) {
//		  String[] addl_info = additional_info.get(i);
//		  JsonObject obj1 = Json.createObjectBuilder()
//		    	     .add("name", addl_info[0])
//		    	     .add("value", addl_info[1]).build();
//		  builder.add(obj1);
//	    }
//		obj.add("additionalFields", builder);
//	  }
	  
	  
	  if(additional_inf != null) {
		  JsonObjectBuilder builder = Json.createObjectBuilder();
		 // JsonArrayBuilder builder = Json.createArrayBuilder();
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
	  
      if( additional_objects != null && additional_objects.size() > 0 )
	    {
		    JsonArrayBuilder builder = Json.createArrayBuilder();
		    for(int i=0;i<additional_objects.size();i++) {
			  JsonObject jobj = additional_objects.get(i);
			  builder.add(jobj);
		    }
			obj.add("jsonObjects",builder);
	    } 
	  
      
      
	   if( evelmap != null && evelmap.size() > 0)
	   {
		    JsonArrayBuilder builder = Json.createArrayBuilder();
	        for(Map.Entry<String, Map<String,String>> entry : evelmap.entrySet()){
	              LOGGER.debug(MessageFormat.format("Key : {0} and Value: {1}", entry.getKey(), entry.getValue()));
	              Map<String,String> item = entry.getValue(); 
	              
				  JsonObjectBuilder obj1 = Json.createObjectBuilder()
	                      .add( "name", entry.getKey());
	             // JsonArrayBuilder builder2 = Json.createArrayBuilder();   
				  JsonObjectBuilder builder2 = Json.createObjectBuilder();
	              for(Map.Entry<String, String> entry2 : item.entrySet()){
	                  LOGGER.debug(MessageFormat.format("Key : {0} and Value: {1}", entry2.getKey(), entry2.getValue()));
//	    			  JsonObjectBuilder obj2 = Json.createObjectBuilder()
//	    			    	     .add("name", entry2.getKey())
//	    			    	     .add("value",entry2.getValue());
	    			  builder2.add(entry2.getKey(), entry2.getValue());
	    		   }
	              
				  obj1.add("hashMap", builder2);
				  builder.add(obj1.build());
			}
			obj.add("arrayOfNamedHashMap", builder);
	   }


	   
	   
	  
	  
	  

	  EVEL_EXIT();
	  
	  return obj;
	}
	 
	 
	 public JsonObject evel_json_encode_event()
	  {
		EVEL_ENTER();
		
		assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_NOTIFICATION);
	        
	    JsonObject obj = Json.createObjectBuilder()
	    	     .add("event", Json.createObjectBuilder()
		    	         .add( "commonEventHeader",eventHeaderObject() )
		    	         .add( "notificationFields", evelNotificationObject() )
		    	         ).build();

	    EVEL_EXIT();
	    
	    return obj;

	  }
	 
	 public JsonObject evel_json_encode_event_batch()
	  {
		EVEL_ENTER();
		
		assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_NOTIFICATION);
	        
	    JsonObject obj = Json.createObjectBuilder()
	    	    // .add("event", Json.createObjectBuilder()
		    	         .add( "commonEventHeader",eventHeaderObject() )
		    	         .add( "notificationFields", evelNotificationObject() )
		    	         .build();

	    EVEL_EXIT();
	    
	    return obj;

	  }

}
