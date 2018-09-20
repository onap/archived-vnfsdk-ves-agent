package evel_javalibrary.att.com.loadbalance;
/**************************************************************************//**
 * @file
 * Sample Test Agent for EVEL library
 *
 * This file implements the Sample Agent which is intended to provide a
 * simple wrapper around the complexity of AT&T's Vendor Event Listener API so
 * that VNFs can use it without worrying about details of the API transport.
 * It also shows how events can be formatted with data for POST
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

import org.apache.log4j.Level;

import evel_javalibrary.att.com.AgentMain;
//import evel_javalibrary.att.com.MeasureData;
//import evel_javalibrary.att.com.heartBeatData;





public class Main {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
        
		try {
			AgentMain.evel_initialize("http://127.0.0.1", 30000,
	                  null,null,
	                 "will",
	                 "pill",
	                 null, null, null,
	                 Level.TRACE);
		 }catch(Exception e) {
			 e.printStackTrace();
			 return;
		 }
		MeasureData mdataThread = new MeasureData();
		mdataThread.start();
	
		heartBeatData hbDataThread = new heartBeatData();		
		hbDataThread.start();
		
		faultData flDataThread = new faultData();		
		flDataThread.start();
		
	}

}

