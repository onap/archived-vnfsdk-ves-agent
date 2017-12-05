package evel_javalibrary.att.com;
/**************************************************************************//**
 * @file
 * Evel Object class
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


public class EvelObject {
	
	public Object datastr; // data string
	public boolean type; //regular or batch type
	
	public EvelObject(){
		datastr = null;
		type = false;
	}
	
	public EvelObject(String data, boolean batchtype){
		datastr = data;
		type = batchtype;
	}

}
