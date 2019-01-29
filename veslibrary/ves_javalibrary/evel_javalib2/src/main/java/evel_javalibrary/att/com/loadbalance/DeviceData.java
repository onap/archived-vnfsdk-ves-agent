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

import java.io.Serializable;

public class DeviceData implements Serializable{
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private String t0bytesIn;
	private String t0bytesOut;
	private String t0packetIn;
	private String t0packetOut;
	
	private String t1Bytesin;
	private String t1Bytesout;
	private String t1Packetsin;
	private String t1Packetsout;
	
	private String Instanceres02Command;

	public String getT0bytesIn() {
		return t0bytesIn;
	}

	public void setT0bytesIn(String t0bytesIn) {
		this.t0bytesIn = t0bytesIn;
	}

	public String getT0bytesOut() {
		return t0bytesOut;
	}

	public void setT0bytesOut(String t0bytesOut) {
		this.t0bytesOut = t0bytesOut;
	}

	public String getT0packetIn() {
		return t0packetIn;
	}

	public void setT0packetIn(String t0packetIn) {
		this.t0packetIn = t0packetIn;
	}

	public String getT0packetOut() {
		return t0packetOut;
	}

	public void setT0packetOut(String t0packetOut) {
		this.t0packetOut = t0packetOut;
	}

	public String getT1Bytesin() {
		return t1Bytesin;
	}

	public void setT1Bytesin(String t1Bytesin) {
		this.t1Bytesin = t1Bytesin;
	}

	public String getT1Bytesout() {
		return t1Bytesout;
	}

	public void setT1Bytesout(String t1Bytesout) {
		this.t1Bytesout = t1Bytesout;
	}

	public String getT1Packetsin() {
		return t1Packetsin;
	}

	public void setT1Packetsin(String t1Packetsin) {
		this.t1Packetsin = t1Packetsin;
	}

	public String getT1Packetsout() {
		return t1Packetsout;
	}

	public void setT1Packetsout(String t1Packetsout) {
		this.t1Packetsout = t1Packetsout;
	}

	public String getInstanceres02Command() {
		return Instanceres02Command;
	}

	public void setInstanceres02Command(String instanceres02Command) {
		Instanceres02Command = instanceres02Command;
	}
	

}
