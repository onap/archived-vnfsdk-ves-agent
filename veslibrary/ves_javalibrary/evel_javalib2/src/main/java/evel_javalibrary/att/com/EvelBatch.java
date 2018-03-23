package evel_javalibrary.att.com;

/**************************************************************************//**
 * @file
 * Evel Batch container class
 *
 * This file implements the Evel Mobile Flow Event class which is intended to provide a
 * simple wrapper around the complexity of AT&T's Vendor Event Listener API so
 * that VNFs can use it to send Mobile flow events.
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


import java.util.ArrayList;

import javax.json.Json;
import javax.json.JsonArrayBuilder;
import javax.json.JsonObject;
import javax.json.JsonObjectBuilder;

import org.apache.log4j.Logger;


public class EvelBatch {
	
	ArrayList<EvelHeader> batch_events;
	
    private static final Logger LOGGER = Logger.getLogger( EvelScalingMeasurement.class.getName() );

	
	public EvelBatch(){
		batch_events = new ArrayList<EvelHeader>();
		LOGGER.trace("Allocated new batch");
	}
	
	public boolean addEvent(EvelHeader element){
		boolean ret = false;
		ret = batch_events.add(element);
		if( ret == false){
			LOGGER.error("Unable to add batch event");
		}
		return ret;
		
	}
	
	/**************************************************************************//**
	* Encode the event as a JSON event object according to AT&T's schema.
	* retval : String of JSON event header only message
	*****************************************************************************/
	  JsonObject evel_json_encode_event()
	  {
		  JsonObjectBuilder batchobj = Json.createObjectBuilder();
		  
		  if( batch_events != null && batch_events.size() > 0 )
		  {			
		    JsonArrayBuilder builder = Json.createArrayBuilder();
		    for(int i=0;i<batch_events.size();i++) {
			  EvelHeader el = batch_events.get(i);
			  //add Json objects
			  builder.add(el.evel_json_encode_event());
		    }
		    
			batchobj.add("eventList", builder);
		  }
	    
	      return batchobj.build();

	  }

}
