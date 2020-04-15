package evel_javalibrary.att.com;
/**************************************************************************//**
 * @file
 * Evel Scaling Measurement class
 *
  * This file implements the Evel Scaling Measurement Event class which is intended to provide a
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
import org.slf4j.helpers.MessageFormatter;

import evel_javalibrary.att.com.EvelScalingMeasurement.MEASUREMENT_IPMI.IPMIHSBP;
import evel_javalibrary.att.com.EvelScalingMeasurement.MEASUREMENT_IPMI.IPMINIC;
import evel_javalibrary.att.com.EvelScalingMeasurement.MEASUREMENT_IPMI.IPMIbaseboardTemperature;
import evel_javalibrary.att.com.EvelScalingMeasurement.MEASUREMENT_IPMI.IPMIbaseboardvoltageResulator;
import evel_javalibrary.att.com.EvelScalingMeasurement.MEASUREMENT_IPMI.IPMIbattery;
import evel_javalibrary.att.com.EvelScalingMeasurement.MEASUREMENT_IPMI.IPMIfan;
import evel_javalibrary.att.com.EvelScalingMeasurement.MEASUREMENT_IPMI.IPMIglobalAggregateTemperatureMargin;
import evel_javalibrary.att.com.EvelScalingMeasurement.MEASUREMENT_IPMI.IPMIpowerSupply;
import evel_javalibrary.att.com.EvelScalingMeasurement.MEASUREMENT_IPMI.MEASUREMENT_IPMI_PROCESSOR;
import evel_javalibrary.att.com.EvelScalingMeasurement.MEASUREMENT_IPMI.MEASUREMENT_IPMI_PROCESSOR.Processor_DIMMaggregate_Thermal_Margin;


public class EvelScalingMeasurement extends EvelHeader {
	
	int major_version = 4;
	int minor_version = 0;
	
	/*
	 * VES6.0 Added Fields 14/07/2018
	 */
	
	
	
	/*****************************************************************************
	* MachineCheck Exception
	* JSON equivalent field: machineCheckException
	******************************************************************************/
	public class MACHINE_CHECK_EXCEPTION{
		
		/**
		 * 
		 */
	//	private static final long serialVersionUID = 1L;
		String processIdentifier;
		EvelOptionDouble correctedMemoryErrors;
		EvelOptionDouble correctedMemoryErrors_In1Hr;
		EvelOptionDouble uncorrectedMemoryErrors;
		EvelOptionDouble uncorrectedMemoryErrors_In1Hr;
		
		
	}
	 
	/**************************************************************************//**
	 * Huge Pages.
	 * JSON equivalent field: hugePages
	 *****************************************************************************/
	public class MEASUREMENT_HUGE_PAGE {
	  String hugePagesIdentifier;
	  double bytesUsed;
	  private  EvelOptionDouble bytesFree;
	  private EvelOptionDouble vmPageNumberUsed;
	  private EvelOptionDouble vmPageNumberFree;
	  private EvelOptionDouble percentUsed;
	  private EvelOptionDouble percentFree;
	  
	}
	
	/**************************************************************************//**
	 * Process Stats.
	 * JSON equivalent field: processStats
	 *****************************************************************************/
	public class MEASUREMENT_PROCESS_STATS {
	  String processIdentifier;
	  private EvelOptionDouble forkRate;
	  private EvelOptionDouble psStateBlocked;
	  private EvelOptionDouble psStatePaging;
	  private EvelOptionDouble psStateRunning;
	  private EvelOptionDouble psStateSleeping;
	  private EvelOptionDouble psStateStopped;
	  private EvelOptionDouble psStateZombie;
	  
	}
	
	/**************************************************************************//**
	 * Load.
	 * JSON equivalent field: load
	 *****************************************************************************/
	public class MEASUREMENT_LOAD {
//	  String loadIdentifier;
		private EvelOptionDouble shortTerm;
		private EvelOptionDouble midTerm;
		private EvelOptionDouble longTerm;
	  
	}
	
	/**************************************************************************//**
	 * CPU Usage.
	 * JSON equivalent field: cpuUsage
	 *****************************************************************************/
	public class MEASUREMENT_CPU_USE {
	  String id;
	  double usage;
	  private EvelOptionDouble idle;
	  private EvelOptionDouble intrpt;
	  private EvelOptionDouble nice;
	  private EvelOptionDouble softirq;
	  private EvelOptionDouble steal;
	  private EvelOptionDouble sys;
	  private EvelOptionDouble user;
	  private EvelOptionDouble wait;
	  /*
	   * Ves6.0 added fields 14/07/2018
	   */
	  private EvelOptionDouble cpuCapacityContention;
	  private EvelOptionDouble cpuDemandAvg;
	  private EvelOptionDouble cpuDemandMhz;
	  private EvelOptionDouble cpuDemandPct;
	  private EvelOptionDouble cpuLatencyAvg;
	  private EvelOptionDouble cpuOverheadAvg;
	  private EvelOptionDouble cpuSwapWaitTime;
	}


	/**************************************************************************//**
	 * Disk Usage.
	 * JSON equivalent field: diskUsage
	 *****************************************************************************/
	public class MEASUREMENT_DISK_USE {
	  String id;
	  private EvelOptionDouble iotimeavg;
	  private EvelOptionDouble iotimelast;
	  private EvelOptionDouble iotimemax;
	  private EvelOptionDouble iotimemin;
	  private EvelOptionDouble mergereadavg;
	  private EvelOptionDouble mergereadlast;
	  private EvelOptionDouble mergereadmax;
	  private EvelOptionDouble mergereadmin;
	  private EvelOptionDouble mergewriteavg;
	  private EvelOptionDouble mergewritelast;
	  private EvelOptionDouble mergewritemax;
	  private EvelOptionDouble mergewritemin;
	  private EvelOptionDouble octetsreadavg;
	  private EvelOptionDouble octetsreadlast;
	  private EvelOptionDouble octetsreadmax;
	  private EvelOptionDouble octetsreadmin;
	  private EvelOptionDouble octetswriteavg;
	  private EvelOptionDouble octetswritelast;
	  private EvelOptionDouble octetswritemax;
	  private EvelOptionDouble octetswritemin;
	  private EvelOptionDouble opsreadavg;
	  private EvelOptionDouble opsreadlast;
	  private EvelOptionDouble opsreadmax;
	  private EvelOptionDouble opsreadmin;
	  private EvelOptionDouble opswriteavg;
	  private EvelOptionDouble opswritelast;
	  private EvelOptionDouble opswritemax;
	  private EvelOptionDouble opswritemin;
	  private EvelOptionDouble pendingopsavg;
	  private EvelOptionDouble pendingopslast;
	  private EvelOptionDouble pendingopsmax;
	  private EvelOptionDouble pendingopsmin;
	  private EvelOptionDouble timereadavg;
	  private EvelOptionDouble timereadlast;
	  private EvelOptionDouble timereadmax;
	  private EvelOptionDouble timereadmin;
	  private EvelOptionDouble timewriteavg;
	  private EvelOptionDouble timewritelast;
	  private EvelOptionDouble timewritemax;
	  private EvelOptionDouble timewritemin;
	  /*
	   * VES6.0 Added fields 14/07/2018
	   */
	  private EvelOptionDouble diskBusResets;
	  private EvelOptionDouble diskCommandsAborted;
	  private EvelOptionDouble diskTime;
	  private EvelOptionDouble diskFlushRequests;
	  private EvelOptionDouble diskFlushTime;
	  private EvelOptionDouble diskCommandsAvg;
	  private EvelOptionDouble diskReadCommandsAvg;
	  private EvelOptionDouble diskWriteCommandsAvg;
	  private EvelOptionDouble diskTotalReadLatencyAvg;
	  private EvelOptionDouble diskTotalWriteLatencyAvg;
	  
	  private EvelOptionDouble diskWeightedIoTimeAvg;
	  private EvelOptionDouble diskWeightedIoTimeLast;
	  private EvelOptionDouble diskWeightedIoTimeMax;
	  private EvelOptionDouble diskWeightedIoTimeMin;
	  
	  
	}

	/**************************************************************************//**
	 * Filesystem Usage.
	 * JSON equivalent field: filesystemUsage
	 *****************************************************************************/
	public class MEASUREMENT_FSYS_USE {
	  String filesystem_name;
	  double block_configured;
	  double block_iops;
	  double block_used;
	  double ephemeral_configured;
	  double ephemeral_iops;
	  double ephemeral_used;
	}

	/**************************************************************************//**
	 * Memory Usage.
	 * JSON equivalent field: memoryUsage
	 *****************************************************************************/
	public class MEASUREMENT_MEM_USE {
	  String id;
	  String vmid;
	  double membuffsz;
	  private EvelOptionDouble memcache;
	  private EvelOptionDouble memconfig;
	  private EvelOptionDouble memfree;
	  private EvelOptionDouble slabrecl;
	  private EvelOptionDouble slabunrecl;
	  private EvelOptionDouble memused;
	  
	  
	  /*
	   * VES6.0 Added fields 14/07/2018
	   */
	  private EvelOptionDouble memoryDemand;
	  private EvelOptionDouble memoryLatencyAvg;
	  private EvelOptionDouble memorySwapUsedAvg;
	  private EvelOptionDouble memorySwapOutAvg;
	  private EvelOptionDouble memorySwapInAvg;
	  private EvelOptionDouble memorySwapInRateAvg;
	  private EvelOptionDouble memorySwapOutRateAvg;
	  private EvelOptionDouble memorySharedAvg;
	  
	  
	  
	  
	}

	/**************************************************************************//**
	 * myerrors.
	 * JSON equivalent field: myerrors
	 *****************************************************************************/
//	public class MEASUREMENT_ERRORS {
//	  int receive_discards;
//	  int receive_myerrors;
//	  int transmit_discards;
//	  int transmit_myerrors;
//	}
	
	/**************************************************************************//**
	 * Latency Bucket.
	 * JSON equivalent field: latencyBucketMeasure
	 *****************************************************************************/
	public class MEASUREMENT_LATENCY_BUCKET {
	  int count;

	  /***************************************************************************/
	  /* Optional fields                                                         */
	  /***************************************************************************/
	  private EvelOptionDouble high_end;
	  private EvelOptionDouble low_end;

	}

	/**************************************************************************//**
	 * Virtual NIC usage.
	 * JSON equivalent field: vNicUsage
	 *****************************************************************************/
	public class MEASUREMENT_NIC_PERFORMANCE {
       String vnic_id;
       String valuesaresuspect;
	  /***************************************************************************/
	  /* Optional fields                                                         */
	  /***************************************************************************/
	  /*Cumulative count of broadcast packets received as read at the end of
	   the measurement interval*/
       private EvelOptionDouble recvd_bcast_packets_acc;
	  /*Count of broadcast packets received within the measurement interval*/
       private EvelOptionDouble recvd_bcast_packets_delta;
	  /*Cumulative count of discarded packets received as read at the end of
	   the measurement interval*/
       private EvelOptionDouble recvd_discarded_packets_acc;
	  /*Count of discarded packets received within the measurement interval*/
       private EvelOptionDouble recvd_discarded_packets_delta;
	  /*Cumulative count of error packets received as read at the end of
	   the measurement interval*/
       private EvelOptionDouble recvd_error_packets_acc;
	  /*Count of error packets received within the measurement interval*/
       private EvelOptionDouble recvd_error_packets_delta;
	  /*Cumulative count of multicast packets received as read at the end of
	   the measurement interval*/
       private EvelOptionDouble recvd_mcast_packets_acc;
	  /*Count of mcast packets received within the measurement interval*/
       private EvelOptionDouble recvd_mcast_packets_delta;
	  /*Cumulative count of octets received as read at the end of
	   the measurement interval*/
       private EvelOptionDouble recvd_octets_acc;
	  /*Count of octets received within the measurement interval*/
       private EvelOptionDouble recvd_octets_delta;
	  /*Cumulative count of all packets received as read at the end of
	   the measurement interval*/
       private EvelOptionDouble recvd_total_packets_acc;
	  /*Count of all packets received within the measurement interval*/
       private EvelOptionDouble recvd_total_packets_delta;
	  /*Cumulative count of unicast packets received as read at the end of
	   the measurement interval*/
	  private EvelOptionDouble recvd_ucast_packets_acc;
	  /*Count of unicast packets received within the measurement interval*/
	  private EvelOptionDouble recvd_ucast_packets_delta;
	  /*Cumulative count of transmitted broadcast packets at the end of
	   the measurement interval*/
	  private EvelOptionDouble tx_bcast_packets_acc;
	  /*Count of transmitted broadcast packets within the measurement interval*/
	  private EvelOptionDouble tx_bcast_packets_delta;
	  /*Cumulative count of transmit discarded packets at the end of
	   the measurement interval*/
	  private EvelOptionDouble tx_discarded_packets_acc;
	  /*Count of transmit discarded packets within the measurement interval*/
	  private EvelOptionDouble tx_discarded_packets_delta;
	  /*Cumulative count of transmit error packets at the end of
	   the measurement interval*/
	  private EvelOptionDouble tx_error_packets_acc;
	  /*Count of transmit error packets within the measurement interval*/
	  private EvelOptionDouble tx_error_packets_delta;
	  /*Cumulative count of transmit multicast packets at the end of
	   the measurement interval*/
	  private EvelOptionDouble tx_mcast_packets_acc;
	  /*Count of transmit multicast packets within the measurement interval*/
	  private EvelOptionDouble tx_mcast_packets_delta;
	  /*Cumulative count of transmit octets at the end of
	   the measurement interval*/
	  private EvelOptionDouble tx_octets_acc;
	  /*Count of transmit octets received within the measurement interval*/
	  private EvelOptionDouble tx_octets_delta;
	  /*Cumulative count of all transmit packets at the end of
	   the measurement interval*/
	  private EvelOptionDouble tx_total_packets_acc;
	  /*Count of transmit packets within the measurement interval*/
	  private EvelOptionDouble tx_total_packets_delta;
	  /*Cumulative count of all transmit unicast packets at the end of
	   the measurement interval*/
	  private EvelOptionDouble tx_ucast_packets_acc;
	  /*Count of transmit unicast packets within the measurement interval*/
	  private EvelOptionDouble tx_ucast_packets_delta;
	  
	  /*VES6.0 added field 14July*/
	  String nicIdentifier;
	  
	  /*
	   * VES6.0 added field 19July 
	   */
	  private EvelOptionString administrativeState;
	  private EvelOptionString operationalState;
	  private EvelOptionDouble receivedPercentDiscard;
	  private EvelOptionDouble receivedPercentError;
	  private EvelOptionDouble receivedUtilization;
	  private EvelOptionDouble speed;
	  private EvelOptionDouble transmittedPercentDiscard;
	  private EvelOptionDouble transmittedPercentError;
	  private EvelOptionDouble transmittedUtilization;
	  
	}

	/**************************************************************************//**
	 * Codec Usage.
	 * JSON equivalent field: codecsInUse
	 *****************************************************************************/
	public class MEASUREMENT_CODEC_USE {
	  String codec_id;
	  int number_in_use;
	}

	/**************************************************************************//**
	 * Feature Usage.
	 * JSON equivalent field: featuresInUse
	 *****************************************************************************/
	public class MEASUREMENT_FEATURE_USE {
	  String feature_id;
	  int feature_utilization;
	}


	/**************************************************************************//**
	 * Custom Defined Measurement.
	 * JSON equivalent field: measurements
	 *****************************************************************************/
	public class CUSTOM_MEASUREMENT {
	  String name;
	  String value;
	}

	/**************************************************************************//**
	 * Measurement Group.
	 * JSON equivalent field: additionalMeasurements
	 *****************************************************************************/
	public class MEASUREMENT_GROUP {
	  String name;
	  ArrayList<CUSTOM_MEASUREMENT> measurements;
	}
	
	
	
	
	
	
	
	/*
	 * VES6.0 added fields 14July
	*/
	
	/**************************************************************************//**
	 * IPMI.
	 * JSON equivalent field: Ipmi
	 *****************************************************************************/
	public class MEASUREMENT_IPMI {
		
		
		
		/***************************************************************************/
		  /* Optional fields                                                         */
		  /***************************************************************************/
		private EvelOptionDouble exitAirTemperature;
		private EvelOptionDouble ioModuleTemperature;
		private EvelOptionDouble frontPanelTemperature;
		private EvelOptionDouble systemAirflow;
		
		

		
		  
		
		
		public void evel_measurement_ipmi_exitAirTemperature_set(MEASUREMENT_IPMI ipmi,
	             double val)
		  {
			  EVEL_ENTER();
			  ipmi.exitAirTemperature.SetValuePr(val,"exitAir Temperature");
			  EVEL_EXIT();
		  }
		
		

		
		
		
		  ArrayList<MEASUREMENT_IPMI_PROCESSOR> ipmiprocessor;
		  
		  public class MEASUREMENT_IPMI_PROCESSOR {
			  private String processorIdentifier;
			  private EvelOptionDouble processorThermalControlPercent;
			  private EvelOptionDouble processorDtsThermalMargin;
		  
			  ArrayList<Processor_DIMMaggregate_Thermal_Margin> processorDIMMaggregateThermalMargin;
			  
			  public class Processor_DIMMaggregate_Thermal_Margin {
				  private String processorDIMMaggregateThermalMarginIdentifier;
				  private double thermalMargin;
				 
				  
				}
			  
			  public ArrayList<Processor_DIMMaggregate_Thermal_Margin> getProcessorDIMMaggregateThermalMargin(
	                      String thermalMarginIdentifier,
	                      double thermalMargin)
				  {
					  Processor_DIMMaggregate_Thermal_Margin pp = null;
					  EVEL_ENTER();

					  /***************************************************************************/
					  /* Check assumptions.                                                      */
					  /***************************************************************************/
						assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_MEASUREMENT);
						assert(thermalMarginIdentifier != null);
						assert(thermalMargin > 0.0);
						
						/***************************************************************************/
						/* Allocate a container for the value and push onto the list.              */
						/***************************************************************************/
						LOGGER.debug(MessageFormatter.format("Adding ThermalMarginIdentifier={0} Use={1}", thermalMarginIdentifier, thermalMargin));
						pp = new Processor_DIMMaggregate_Thermal_Margin();
						assert(pp != null);
						pp.processorDIMMaggregateThermalMarginIdentifier = thermalMarginIdentifier;
						assert(pp.thermalMargin >= 0.0);
						pp.thermalMargin = thermalMargin;
						
						if( processorDIMMaggregateThermalMargin == null ){
							processorDIMMaggregateThermalMargin = new ArrayList<Processor_DIMMaggregate_Thermal_Margin>();
						LOGGER.debug("Allocate new ProcessorDIMMaggregateThermalMargin");
						}

						processorDIMMaggregateThermalMargin.add(pp);
					

						EVEL_EXIT();
						return processorDIMMaggregateThermalMargin;
				  }
				  
		  
		  
		  
		  
		  }	  	
		  
		  
		  
		  ArrayList<Processor_DIMMaggregate_Thermal_Margin> processorDIMMaggregateThermalMargin;
		  public void evelMeasurementIpmiProcessorAdd(String processorIdentifier,double val, double processDTSthermalMargin,String thermalMarginIdentifier, double thermalMargin) {
			  MEASUREMENT_IPMI_PROCESSOR mIP = null;
			  EVEL_ENTER();
              
			  /***************************************************************************/
			  /* Check assumptions.                                                      */
			  /***************************************************************************/
				assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_MEASUREMENT);
				assert(processorIdentifier != null);
				
				
				/***************************************************************************/
				/* Allocate a container for the value and push onto the list.              */
				/***************************************************************************/
				LOGGER.debug(MessageFormatter.format("Adding Identifier={0}", processorIdentifier));
				mIP = new MEASUREMENT_IPMI_PROCESSOR();
				assert(mIP != null);
				mIP.processorIdentifier = processorIdentifier;
				mIP.processorThermalControlPercent = new EvelOptionDouble();
				mIP.processorThermalControlPercent.SetValuePr(val,"Processor Thermal Control Percent");
				mIP.processorDtsThermalMargin = new EvelOptionDouble();
				mIP.processorDtsThermalMargin.SetValuePr(processDTSthermalMargin,"processor DTSthermal Margin");
				
				
				
				if( ipmiprocessor == null ){
					ipmiprocessor = new ArrayList<MEASUREMENT_IPMI_PROCESSOR>();
				LOGGER.debug("Allocate new IPMI_PROCESSOR");
				}
				
				
					mIP.processorDIMMaggregateThermalMargin = new MEASUREMENT_IPMI_PROCESSOR().getProcessorDIMMaggregateThermalMargin(thermalMarginIdentifier,thermalMargin);//processorDIMMaggregateThermalMargin;
					
					
					ipmiprocessor.add(mIP);
				

				EVEL_EXIT();

		  }

		  
		  public MEASUREMENT_IPMI_PROCESSOR evel_measurement_IPMI_MEASUREMENT_IPMI_PROCESSOR_add(
                  String processorIdentifier,double val
                  )
		  {
			  MEASUREMENT_IPMI_PROCESSOR mIP = null;
			  EVEL_ENTER();

			  /***************************************************************************/
			  /* Check assumptions.                                                      */
			  /***************************************************************************/
				assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_MEASUREMENT);
				assert(processorIdentifier != null);
				
				
				/***************************************************************************/
				/* Allocate a container for the value and push onto the list.              */
				/***************************************************************************/
				LOGGER.debug(MessageFormatter.format("Adding Identifier={0}", processorIdentifier));
				mIP = new MEASUREMENT_IPMI_PROCESSOR();
				assert(mIP != null);
				mIP.processorIdentifier = processorIdentifier;
				mIP.processorThermalControlPercent = new EvelOptionDouble();
				mIP.processorThermalControlPercent.SetValuePr(val,"Processor Thermal Control Percent");
				mIP.processorDtsThermalMargin = new EvelOptionDouble(); 
				
				
				
				if( ipmiprocessor == null ){
					ipmiprocessor = new ArrayList<MEASUREMENT_IPMI_PROCESSOR>();
				LOGGER.debug("Allocate new IPMI_PROCESSOR");
				}

				ipmiprocessor.add(mIP);
                
				EVEL_EXIT();
				return mIP;
		  }
		  

			  ArrayList<IPMIglobalAggregateTemperatureMargin> ipmiglobalAggregateTemperatureMarginArray;
			  
			  public class IPMIglobalAggregateTemperatureMargin {
				  private String globalAggregateTemperatureMarginIdentifier;
				  private EvelOptionDouble globalAggregateTemeratureMargin;			  
				}
			  
			  public void evel_measurement_IPMI_MEASUREMENT_IPMIglobalAggregateTemperatureMargin_add(
	                  String globalAggregateTemperatureMarginIdentifier,double val
	                  )
			  {
				  IPMIglobalAggregateTemperatureMargin ipmiGlobalAgg = null;
				  EVEL_ENTER();

				  /***************************************************************************/
				  /* Check assumptions.                                                      */
				  /***************************************************************************/
					assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_MEASUREMENT);
					assert(globalAggregateTemperatureMarginIdentifier != null);
					
					
					/***************************************************************************/
					/* Allocate a container for the value and push onto the list.              */
					/***************************************************************************/
					LOGGER.debug(MessageFormatter.format("Adding Identifier={0}", globalAggregateTemperatureMarginIdentifier));
					ipmiGlobalAgg = new IPMIglobalAggregateTemperatureMargin();
					assert(ipmiGlobalAgg != null);
					ipmiGlobalAgg.globalAggregateTemperatureMarginIdentifier = globalAggregateTemperatureMarginIdentifier;
					ipmiGlobalAgg.globalAggregateTemeratureMargin = new EvelOptionDouble();
					ipmiGlobalAgg.globalAggregateTemeratureMargin.SetValuePr(val,"Processor Thermal Control Percent");
					
					if( ipmiglobalAggregateTemperatureMarginArray == null ){
						ipmiglobalAggregateTemperatureMarginArray = new ArrayList<IPMIglobalAggregateTemperatureMargin>();
					LOGGER.debug("Allocate new IPMIglobalAggregateTemperatureMargin");
					}

					ipmiglobalAggregateTemperatureMarginArray.add(ipmiGlobalAgg);

					EVEL_EXIT();
			  }
			  
			  
			  
			  
			  
			  ArrayList<IPMIpowerSupply> ipmipowerSupply;
			  
			  public class IPMIpowerSupply {
				  private String powerSupplyIdentifier;
				  private EvelOptionDouble powerSupplyInputPower;
				  private EvelOptionDouble powerSupplycurrentOutputPercent;
				  private EvelOptionDouble powerSupplyTemperature;
				}
			  
			  public void evel_measurement_IPMI_MEASUREMENT_IPMIpowerSupply_add(
	                  String powerSupplyIdentifier,double powerSupplyInputPower,double powerSupplycurrentOutputPercent,double powerSupplyTemperature
	                  )
			  {
				  IPMIpowerSupply ipmipower = null;
				  EVEL_ENTER();

				  /***************************************************************************/
				  /* Check assumptions.                                                      */
				  /***************************************************************************/
					assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_MEASUREMENT);
					//assert(ipmipower != null);
					
					
					/***************************************************************************/
					/* Allocate a container for the value and push onto the list.              */
					/***************************************************************************/
					LOGGER.debug(MessageFormatter.format("Adding Identifier={0}", powerSupplyIdentifier));
					ipmipower = new IPMIpowerSupply();
					assert(ipmipower != null);
					ipmipower.powerSupplyIdentifier = powerSupplyIdentifier;
					ipmipower.powerSupplycurrentOutputPercent = new EvelOptionDouble();
					ipmipower.powerSupplycurrentOutputPercent.SetValuePr(powerSupplyInputPower,"Power Supply Input Power");
					ipmipower.powerSupplyInputPower = new EvelOptionDouble();
					ipmipower.powerSupplyInputPower.SetValuePr(powerSupplycurrentOutputPercent,"power Supply currentOutput Percent");
					ipmipower.powerSupplyTemperature = new EvelOptionDouble();
					ipmipower.powerSupplyTemperature.SetValuePr(powerSupplyTemperature,"power Supply Temperature");
					
					
					if( ipmipowerSupply == null ){
						ipmipowerSupply = new ArrayList<IPMIpowerSupply>();
					LOGGER.debug("Allocate new IPMIpowerSupply");
					}

					ipmipowerSupply.add(ipmipower);

					EVEL_EXIT();
			  }
			  
			  
			  
			  
			  
			  ArrayList<IPMIbattery> ipmibattery;
			  
			  public class IPMIbattery {
				  private String batteryIdentifier;
				  private EvelOptionString batteryType;
				  private EvelOptionDouble batteryVoltageLevel;
				  
				}
			  
			  public void evel_measurement_IPMI_MEASUREMENT_IPMIbattery_add(
	                  String batteryIdentifier,String batteryType,double batteryVoltageLevel
	                  )
			  {
				  IPMIbattery imibatt = null;
				  EVEL_ENTER();

				  /***************************************************************************/
				  /* Check assumptions.                                                      */
				  /***************************************************************************/
					assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_MEASUREMENT);
					//assert(imibatt != null);
					
					
					/***************************************************************************/
					/* Allocate a container for the value and push onto the list.              */
					/***************************************************************************/
					LOGGER.debug(MessageFormatter.format("Adding Identifier={0}", batteryIdentifier));
					imibatt = new IPMIbattery();
					assert(imibatt != null);
					imibatt.batteryIdentifier = batteryIdentifier;
					imibatt.batteryType = new EvelOptionString();
					imibatt.batteryType.SetValue("BatteryType");
					imibatt.batteryVoltageLevel = new EvelOptionDouble();
					imibatt.batteryVoltageLevel.SetValuePr(batteryVoltageLevel,"Battery Voltage Level");
					
					if( ipmibattery == null ){
						ipmibattery = new ArrayList<IPMIbattery>();
					LOGGER.debug("Allocate new IPMIbattery");
					}

					ipmibattery.add(imibatt);

					EVEL_EXIT();
			  }
			  
			  
			  
              ArrayList<IPMINIC> ipmiNIC;
			  
			  public class IPMINIC {
				  private String nicIdentifier;
				  private EvelOptionDouble nicTemperature;
				  
				  
				}
			  
			  public void evel_measurement_IPMINIC_add(
	                  String nicIdentifier,double nicTemperature
	                  )
			  {
				  IPMINIC ipmiNic = null;
				  EVEL_ENTER();

				  /***************************************************************************/
				  /* Check assumptions.                                                      */
				  /***************************************************************************/
					assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_MEASUREMENT);
					//assert(ipmiNic != null);
					
					
					/***************************************************************************/
					/* Allocate a container for the value and push onto the list.              */
					/***************************************************************************/
					
					ipmiNic = new IPMINIC();
					assert(ipmiNic != null);
					ipmiNic.nicIdentifier = nicIdentifier;
					ipmiNic.nicTemperature = new EvelOptionDouble();
					ipmiNic.nicTemperature.SetValuePr(nicTemperature, "nic Temperature");
					
					
					
					
					if( ipmiNIC == null ){
						ipmiNIC = new ArrayList<IPMINIC>();
					LOGGER.debug("Allocate new IPMINIC");
					}

					ipmiNIC.add(ipmiNic);

					EVEL_EXIT();
			  }
			  
			  
			  
             ArrayList<IPMIHSBP> ipmiHSBP;
			  
			  public class IPMIHSBP {
				  private String hsbpIdentifier;
				  private EvelOptionDouble hsbpTemperature;
				  
				  
				}
			  
			  
			  public void evel_measurement_IPMIHSBP_add(
	                  String hsbpIdentifier,double hsbpTemperature
	                  )
			  {
				  IPMIHSBP ipmiHsbp = null;
				  EVEL_ENTER();

				  /***************************************************************************/
				  /* Check assumptions.                                                      */
				  /***************************************************************************/
					assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_MEASUREMENT);
					//assert(ipmiHsbp != null);
					
					
					/***************************************************************************/
					/* Allocate a container for the value and push onto the list.              */
					/***************************************************************************/
					LOGGER.debug(MessageFormatter.format("Adding Identifier={0}", hsbpIdentifier));
					ipmiHsbp = new IPMIHSBP();
					assert(ipmiHsbp != null);
					ipmiHsbp.hsbpIdentifier = hsbpIdentifier;
					ipmiHsbp.hsbpTemperature = new EvelOptionDouble();
					ipmiHsbp.hsbpTemperature.SetValuePr(hsbpTemperature,"Hsbp Temperature");
					
					if( ipmiHSBP == null ){
						ipmiHSBP = new ArrayList<IPMIHSBP>();
					LOGGER.debug("Allocate new IPMIHSBP");
					}

					ipmiHSBP.add(ipmiHsbp);

					EVEL_EXIT();
			  }
			  
			  
			  
			  
            ArrayList<IPMIbaseboardTemperature> ipmibaseboardTemperature;
			  
			  public class IPMIbaseboardTemperature {
				  private String baseboardTemperatureIdentifier;
				  private EvelOptionDouble baseboardTemperature;
				  
				  
				}
			  
			  
			  
			  public void evel_measurement_IPMIbaseboardTemperature_add(
	                  String baseboardTemperatureIdentifier,double baseboardTemperature
	                  )
			  {
				  IPMIbaseboardTemperature ipmibaseboardTemp = null;
				  EVEL_ENTER();

				  /***************************************************************************/
				  /* Check assumptions.                                                      */
				  /***************************************************************************/
					assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_MEASUREMENT);
					//assert(ipmibaseboardTemperature != null);
					
					
					/***************************************************************************/
					/* Allocate a container for the value and push onto the list.              */
					/***************************************************************************/
					LOGGER.debug(MessageFormatter.format("Adding Identifier={0}", baseboardTemperatureIdentifier));
					ipmibaseboardTemp = new IPMIbaseboardTemperature();
					assert(ipmibaseboardTemp != null);
					ipmibaseboardTemp.baseboardTemperatureIdentifier = baseboardTemperatureIdentifier;
					ipmibaseboardTemp.baseboardTemperature = new EvelOptionDouble();
					ipmibaseboardTemp.baseboardTemperature.SetValuePr(baseboardTemperature,"Baseboard Temperature");
					
					if( ipmibaseboardTemperature == null ){
						ipmibaseboardTemperature = new ArrayList<IPMIbaseboardTemperature>();
					LOGGER.debug("Allocate new IPMIbaseboardTemperature");
					}

					ipmibaseboardTemperature.add(ipmibaseboardTemp);

					EVEL_EXIT();
			  }
			  
			  
			  
			  
               ArrayList<IPMIbaseboardvoltageResulator> ipmiBaseboardvoltageResulator;
			  
			  public class IPMIbaseboardvoltageResulator {
				  private String baseboardVoltageRegulatorIdentifier;
				  private EvelOptionDouble voltageRegulatorTemperature;
				  
				  
				}
			  
			  
			  public void evel_measurement_IPMIbaseboardvoltageResulator_add(
	                  String baseboardVoltageRegulatorIdentifier,double voltageRegulatorTemperature
	                  )
			  {
				  IPMIbaseboardvoltageResulator ipmiBaseboardvoltageRes = null;
				  EVEL_ENTER();

				  /***************************************************************************/
				  /* Check assumptions.                                                      */
				  /***************************************************************************/
					assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_MEASUREMENT);
					//assert(ipmiBaseboardvoltageRes != null);
					
					
					/***************************************************************************/
					/* Allocate a container for the value and push onto the list.              */
					/***************************************************************************/
					LOGGER.debug(MessageFormatter.format("Adding Identifier={0}", baseboardVoltageRegulatorIdentifier));
					ipmiBaseboardvoltageRes = new IPMIbaseboardvoltageResulator();
					assert(ipmiBaseboardvoltageRes != null);
					ipmiBaseboardvoltageRes.baseboardVoltageRegulatorIdentifier = baseboardVoltageRegulatorIdentifier;
					ipmiBaseboardvoltageRes.voltageRegulatorTemperature = new EvelOptionDouble();
					ipmiBaseboardvoltageRes.voltageRegulatorTemperature.SetValuePr(voltageRegulatorTemperature,"Voltage Regulator Temperature");
					
					if( ipmiBaseboardvoltageResulator == null ){
						ipmiBaseboardvoltageResulator = new ArrayList<IPMIbaseboardvoltageResulator>();
					LOGGER.debug("Allocate new IPMIbaseboardvoltageResulator");
					}

					ipmiBaseboardvoltageResulator.add(ipmiBaseboardvoltageRes);

					EVEL_EXIT();
			  }
			  
			  
			  
			  
            ArrayList<IPMIfan> ipmiFan;
			  
			  public class IPMIfan {
				  private String fanIdentifier;
				  private EvelOptionDouble fanSpeed;
				  
				  
				}
			  
			  public void evel_measurement_IPMIfan_add(
	                  String fanIdentifier,double fanSpeed
	                  )
			  {
				  IPMIfan ipmiF = null;
				  EVEL_ENTER();

				  /***************************************************************************/
				  /* Check assumptions.                                                      */
				  /***************************************************************************/
					assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_MEASUREMENT);
					//assert(ipmiF != null);
					
					
					/***************************************************************************/
					/* Allocate a container for the value and push onto the list.              */
					/***************************************************************************/
					LOGGER.debug(MessageFormatter.format("Adding Identifier={0}", fanIdentifier));
					ipmiF = new IPMIfan();
					assert(ipmiF != null);
					ipmiF.fanIdentifier = fanIdentifier;
					ipmiF.fanSpeed = new EvelOptionDouble();
					ipmiF.fanSpeed.SetValuePr(fanSpeed,"Fan Speed");
					
					if( ipmiFan == null ){
						ipmiFan = new ArrayList<IPMIfan>();
					LOGGER.debug("Allocate new IPMIfan");
					}

					ipmiFan.add(ipmiF);

					EVEL_EXIT();
			  }
			  
			  
			  
			  
			  
			  
				public void evel_meas_ipmi_add(MEASUREMENT_IPMI ipmi,double exitAirTemperature,double frontPanelTemperature,double ioModuleTemperature,double systemAirflow)
				{
					EVEL_ENTER();
					
					/***************************************************************************/
					/* Check preconditions.                                                    */
					/***************************************************************************/
					// MEASUREMENT_IPMI ipmi = new MEASUREMENT_IPMI();
					assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_MEASUREMENT);
					assert(ipmi != null);
					
					
					
					    assert(ipmi != null);
					    //cpu_use.id    = id;
					    //cpu_use.usage = usage;
					    ipmi.exitAirTemperature = new EvelOptionDouble();
					  ipmi.exitAirTemperature.SetValuePr(exitAirTemperature, "Exit Air Temperature");
					    ipmi.frontPanelTemperature = new EvelOptionDouble();
					    ipmi.frontPanelTemperature.SetValuePr(frontPanelTemperature, "front Panel Temperature");
					    ipmi.ioModuleTemperature = new EvelOptionDouble();
					    ipmi.ioModuleTemperature.SetValuePr(ioModuleTemperature, "IOModule Temperature");
					    ipmi.systemAirflow = new EvelOptionDouble();
					    ipmi.systemAirflow.SetValuePr(systemAirflow, "System Airflow");
					    ipmi.ipmibaseboardTemperature = null;
					    ipmi.ipmiBaseboardvoltageResulator = null;
					    ipmi.ipmibattery = null;
					    ipmi.ipmiFan = null;
					    ipmi.ipmiglobalAggregateTemperatureMarginArray = null;
					    ipmi.ipmiHSBP = null;
					    ipmi.ipmiNIC = null;
					    ipmi.ipmipowerSupply = null;
					    ipmi.ipmiprocessor = null;
					
				    
					if( ipmis == null ){
					ipmis = new ArrayList<MEASUREMENT_IPMI>();
					LOGGER.debug("Allocate new file system usage");
					}
					
					
					ipmis.add(ipmi);
					
					EVEL_EXIT();
					
					//return ipmi;
				}
				


				 public void evel_measurement_ipmi_frontPanelTemperature_set(MEASUREMENT_IPMI ipmi,
			             double val)
				  {
					  EVEL_ENTER();
					  ipmi.frontPanelTemperature.SetValuePr(val,"Front panel temp in Celsius");
					  EVEL_EXIT();
				  }
				 public void evel_measurement_ipmi_ioModuleTemperature_set(MEASUREMENT_IPMI ipmi,
			             double val)
				  {
					  EVEL_ENTER();
					  ipmi.ioModuleTemperature.SetValuePr(val,"Io module temp in Celsius ");
					  EVEL_EXIT();
				  }
				 public void evel_measurement_ipmi_systemAirflow_set(MEASUREMENT_IPMI ipmi,
			             double val)
				  {
					  EVEL_ENTER();
					  ipmi.systemAirflow.SetValuePr(val,"Airflow in cubic feet per minute (cfm)");
					  EVEL_EXIT();
				  }
				

			  

			  
			  
			  
			  
			  
			  
			  
			  

}
	
	


	
	
	
	

	
	/***************************************************************************/
	  /* Mandatory fields                                                        */
	  /***************************************************************************/
	  double measurement_interval;

	  /***************************************************************************/
	  /* Optional fields                                                         */
	  /***************************************************************************/
	//  ArrayList<String[]> additional_info;
	  
	  HashMap<String, String > additional_inf;
	  
	  ArrayList<MEASUREMENT_GROUP> additional_measurements;
	  ArrayList<javax.json.JsonObject> additional_objects;
	  ArrayList<MEASUREMENT_CODEC_USE> codec_usage;
	  EvelOptionInt concurrent_sessions;
	  EvelOptionInt configured_entities;
	  ArrayList<MEASUREMENT_CPU_USE> cpu_usage;
	  //VES6.0 Added field 14/07/2018
	  ArrayList<MEASUREMENT_HUGE_PAGE> huge_pages;
	  ArrayList<MEASUREMENT_LOAD> loads;
	  ArrayList<MEASUREMENT_PROCESS_STATS> process_stats;
	  ArrayList<MEASUREMENT_IPMI> ipmis;
	  ArrayList<MACHINE_CHECK_EXCEPTION> machineCheckException;
	  
	  
	  
	  
	  ArrayList<MEASUREMENT_DISK_USE> disk_usage;
	  boolean errstat;
	//  MEASUREMENT_ERRORS myerrors;
	  ArrayList<MEASUREMENT_FEATURE_USE> feature_usage;
	  ArrayList<MEASUREMENT_FSYS_USE> filesystem_usage;
	  ArrayList<MEASUREMENT_LATENCY_BUCKET> latency_distribution;
	  EvelOptionDouble mean_request_latency;
	  ArrayList<MEASUREMENT_MEM_USE> mem_usage;
	  EvelOptionInt media_ports_in_use;
	  EvelOptionInt request_rate;
	  EvelOptionInt vnfc_scaling_metric;
	  ArrayList<MEASUREMENT_NIC_PERFORMANCE> vnic_usage;


	/***************************************************************************/
	/* Optional fields                                                         */
	/***************************************************************************/

	  private static final Logger LOGGER = Logger.getLogger( EvelScalingMeasurement.class.getName() );


	  /**************************************************************************//**
	   * Constructs a new Measurement event.
	   *
	   * @note    The mandatory fields on the Measurement must be supplied to this
	   *          factory function and are immutable once set.  Optional fields have
	   *          explicit setter functions, but again values may only be set once so
	   *          that the Measurement has immutable properties.
	   *
	   * @param   measurement_interval
	   *
	   *****************************************************************************/
	  public EvelScalingMeasurement(double meas_interval,String evname,String evid)
	  { //Init header
        super(evname,evid);

	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(meas_interval >= 0.0);

	    LOGGER.debug("New measurement is at "+meas_interval);

	    /***************************************************************************/
	    /* Initialize the header & the measurement fields.                         */
	    /***************************************************************************/
	    event_domain = EvelHeader.DOMAINS.EVEL_DOMAIN_MEASUREMENT;
        //initialize optional fields
	    measurement_interval = meas_interval;
	    additional_inf = null;
	    additional_measurements = null;
	    additional_objects = null;
	    cpu_usage = null;
	    disk_usage = null;
	    mem_usage = null;
	    filesystem_usage = null;
	    latency_distribution = null;
	    vnic_usage = null;
	    codec_usage = null;
	    feature_usage = null;
	    errstat = false;
	    
	    
	    huge_pages=null;
	    loads = null;
	    process_stats=null;
	    ipmis=null;
	    machineCheckException = null;
	    
	    
	    mean_request_latency = new EvelOptionDouble(false, 0.0);
	    vnfc_scaling_metric = new EvelOptionInt(false, 0);
	    concurrent_sessions = new EvelOptionInt(false, 0);
	    configured_entities = new EvelOptionInt(false, 0);
	    media_ports_in_use = new EvelOptionInt(false, 0);
	    request_rate = new EvelOptionInt(false, 0);
	    errstat = false;

	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the Event Type property of the Measurement.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   
	   * @param type        The Event Type to be set. ASCIIZ string. The caller
	   *                    does not need to preserve the value once the function
	   *                    returns.
	   *****************************************************************************/
	  public void evel_measurement_type_set(String typ)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions and call evel_header_type_set.                      */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_MEASUREMENT);
	    evel_header_type_set(typ);

	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Add an additional value name/value pair to the Measurement.
	   *
	   * The name and value are null delimited ASCII strings.  The library takes
	   * a copy so the caller does not have to preserve values after the function
	   * returns.
	   *
	   * @param name      ASCIIZ string with the attribute's name.  The caller
	   *                  does not need to preserve the value once the function
	   *                  returns.
	   * @param value     ASCIIZ string with the attribute's value.  The caller
	   *                  does not need to preserve the value once the function
	   *                  returns.
	   *****************************************************************************/
	  public void evel_measurement_addl_info_add(String name, String value)
		{
		//  String[] addl_info = null;
		  EVEL_ENTER();

		  /***************************************************************************/
		  /* Check preconditions.                                                    */
		  /***************************************************************************/
		  assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_MEASUREMENT);
		  assert(name != null);
		  assert(value != null);
		  
		  if( additional_inf == null )
		  {
			  additional_inf = new HashMap<String, String >();
		  }

		  LOGGER.debug(MessageFormat.format("Adding name={0} value={1}", name, value));
		  additional_inf.put(name,  value);
		  EVEL_EXIT();
		}

	  /**************************************************************************/
	  /* IPMI.																	*/
	  /* JSON equivalent field: Ipmi 											*/
	  /*****************************************************************************/
	  
	  public MEASUREMENT_IPMI evel_measurement_new_ipmis_add()
	  {
			EVEL_ENTER();
			
			/***************************************************************************/
			/* Check preconditions.                                                    */
			/***************************************************************************/
			 MEASUREMENT_IPMI ipmi = new MEASUREMENT_IPMI();
			assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_MEASUREMENT);
			assert(ipmi != null);
			
			
			
			    assert(ipmi != null);
			    //cpu_use.id    = id;
			    //cpu_use.usage = usage;
			    ipmi.exitAirTemperature = new EvelOptionDouble();
			 //   ipmi.exitAirTemperature.SetValuePr(exitAirTemperature, "Exit Air Temperature");
			    ipmi.frontPanelTemperature = new EvelOptionDouble();
			 //   ipmi.frontPanelTemperature.SetValuePr(frontPanelTemperature, "front Panel Temperature");
			    ipmi.ioModuleTemperature = new EvelOptionDouble();
			//    ipmi.ioModuleTemperature.SetValuePr(ioModuleTemperature, "IOModule Temperature");
			    ipmi.systemAirflow = new EvelOptionDouble();
			//    ipmi.systemAirflow.SetValuePr(systemAirflow, "System Airflow");
			    ipmi.ipmibaseboardTemperature = null;
			    ipmi.ipmiBaseboardvoltageResulator = null;
			    ipmi.ipmibattery = null;
			    ipmi.ipmiFan = null;
			    ipmi.ipmiglobalAggregateTemperatureMarginArray = null;
			    ipmi.ipmiHSBP = null;
			    ipmi.ipmiNIC = null;
			    ipmi.ipmipowerSupply = null;
			    ipmi.ipmiprocessor = null;
			
		    
			if( ipmis == null ){
			ipmis = new ArrayList<MEASUREMENT_IPMI>();
			LOGGER.debug("Allocate new file IPMI");
			}
			
			
			ipmis.add(ipmi);
			
			EVEL_EXIT();
			
	    return ipmi;
	  }
	  

	  
	  
	  
	  
	  
	  
	  
//	  public MEASUREMENT_IPMI evel_measurement_new_ipmis_add(double exitAirTemperature,double frontPanelTemperature,double ioModuleTemperature,double systemAirflow)
//	  {
//	    EVEL_ENTER();
//
//	    /***************************************************************************/
//	    /* Check assumptions.                                                      */
//	    /***************************************************************************/
//	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_MEASUREMENT);
//
//	    /***************************************************************************/
//	    /* Allocate a container for the value and push onto the list.              */
//	    /***************************************************************************/
//	    //LOGGER.debug(MessageFormatter.format("Adding id={0} usage={1}", id, usage));
//	    MEASUREMENT_IPMI ipmi = new MEASUREMENT_IPMI();
//	    assert(ipmi != null);
//	    //cpu_use.id    = id;
//	    //cpu_use.usage = usage;
//	    ipmi.exitAirTemperature = new EvelOptionDouble();
//	    ipmi.exitAirTemperature.SetValuePr(exitAirTemperature, "Exit Air Temperature");
//	    ipmi.frontPanelTemperature = new EvelOptionDouble();
//	    ipmi.frontPanelTemperature.SetValuePr(frontPanelTemperature, "front Panel Temperature");
//	    ipmi.ioModuleTemperature = new EvelOptionDouble();
//	    ipmi.ioModuleTemperature.SetValuePr(ioModuleTemperature, "IOModule Temperature");
//	    ipmi.systemAirflow = new EvelOptionDouble();
//	    ipmi.systemAirflow.SetValuePr(systemAirflow, "System Airflow");
//	    
//	   
//	    	    if( ipmis == null ){
//	    	    	ipmis= new ArrayList<MEASUREMENT_IPMI>();
//	    	LOGGER.debug("Allocate new ipmis");
//	    }
//
//	    ipmis.add(ipmi);
//
//	    EVEL_EXIT();
//	    return ipmi;
//	  }
	  
	  
	  
	  /*
	   * 
	   */
	  
	  
	  
	  
	  
	  
	  
	  
	  
	  
	  /**************************************************************************//**
	   * Set the Concurrent Sessions property of the Measurement.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   
	   * @param concurrent_sessions The Concurrent Sessions to be set.
	   *****************************************************************************/
	  public void evel_measurement_concurrent_sessions_set(int conc_sessions)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_MEASUREMENT);
	    assert(conc_sessions >= 0);

		concurrent_sessions.SetValuePr(conc_sessions,"Concurrent Sessions");
		  
	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the Configured Entities property of the Measurement.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   
	   * @param configured_entities The Configured Entities to be set.
	   *****************************************************************************/
	  public void evel_measurement_config_entities_set(int config_entities)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_MEASUREMENT);
	    assert(config_entities >= 0);

	    configured_entities.SetValuePr(config_entities,"Configured Entities");
		
	    EVEL_EXIT();
	  }


	  /**************************************************************************//**
	   * Set the Mean Request Latency property of the Measurement.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   
	   * @param mean_request_latency The Mean Request Latency to be set.
	   *****************************************************************************/
	  public void evel_measurement_mean_req_lat_set(
	                                         double mean_req_latency)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_MEASUREMENT);
	    assert(mean_req_latency >= 0.0);

	    mean_request_latency.SetValuePr(mean_req_latency,"Mean Request Latency");
	    
	    EVEL_EXIT();
	  }


	  /**************************************************************************//**
	   * Set the Request Rate property of the Measurement.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   
	   * @param request_rate The Request Rate to be set.
	   *****************************************************************************/
	  public void evel_measurement_request_rate_set(int req_rate)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_MEASUREMENT);
	    assert(req_rate >= 0);

	    request_rate.SetValuePr(req_rate,"Request Rate");
	    
	    EVEL_EXIT();
	  }
	  
	  
	  
	  /*
	   * VES6.0 Added fields 14July2018
      */ 
	  
	  /**************************************************************************//**
	   load average figures giving the number of jobs in the run queue (state R) or waiting for disk I/O (state D) averaged over 1 Minute
      measured CPU and IO utilization for 1 min using /proc/loadavg
	   * The name and value are null delimited ASCII strings.  The library takes
	   * a copy so the caller does not have to preserve values after the function
	   * returns.
	   *
	   * 
	   * @param id            ASCIIZ string with the CPU's identifier.
	   * @param usage         CPU utilization.
	   *****************************************************************************/
	  public MEASUREMENT_PROCESS_STATS evel_measurement_new_process_stats_add(String id, double usage)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check assumptions.                                                      */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_MEASUREMENT);
	    assert(id != null);
	    assert(usage >= 0.0);

	    /***************************************************************************/
	    /* Allocate a container for the value and push onto the list.              */
	    /***************************************************************************/
	    LOGGER.debug(MessageFormatter.format("Adding id={0} usage={1}", id, usage));
	    MEASUREMENT_PROCESS_STATS process_stat = new MEASUREMENT_PROCESS_STATS();
	    assert(process_stat != null);
	    process_stat.processIdentifier    = id;
	    process_stat.forkRate = new EvelOptionDouble();
	    process_stat.psStateBlocked = new EvelOptionDouble();
	    process_stat.psStatePaging = new EvelOptionDouble();	
	    process_stat.psStateRunning = new EvelOptionDouble();	
	    process_stat.psStateSleeping = new EvelOptionDouble();	
	    process_stat.psStateStopped = new EvelOptionDouble();	
	    process_stat.psStateZombie = new EvelOptionDouble();	
	    
	   
	    if( process_stats == null ){
	    	process_stats = new ArrayList<MEASUREMENT_PROCESS_STATS>();
	    	LOGGER.debug("Allocate Process_Stats");
	    }

	    process_stats.add(process_stat);

	    EVEL_EXIT();
	    return process_stat;
	  }
	  
	  
	  
	  
	  
	  
	  /**************************************************************************//**
	   * the number of threads created since the last reboo
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param cpu_use      Pointer to the CPU Use.
	   * @param val          double
	   *****************************************************************************/
	  
	  
	  public void evel_measurement_process_stats_forkRate_set(MEASUREMENT_PROCESS_STATS process_stat,
              double val)
	  {
		  EVEL_ENTER();
		  process_stat.forkRate.SetValuePr(val,"the number of threads created since the last reboot");
		  EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * the number of processes in a blocked state
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param cpu_use      Pointer to the CPU Use.
	   * @param val          double
	   *****************************************************************************/
	  
	  
	  public void evel_measurement_process_stats_psStateBlocked_set(MEASUREMENT_PROCESS_STATS process_stat,
              double val)
	  {
		  EVEL_ENTER();
		  process_stat.psStateBlocked.SetValuePr(val,"the number of processes in a blocked state");
		  EVEL_EXIT();
	  }
	  
	  
	  /**************************************************************************//**
	   * the number of processes in a paging state
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param cpu_use      Pointer to the CPU Use.
	   * @param val          double
	   *****************************************************************************/
	  
	  
	  public void evel_measurement_process_stats_psStatePaging_set(MEASUREMENT_PROCESS_STATS process_stat,
              double val)
	  {
		  EVEL_ENTER();
		  process_stat.psStatePaging.SetValuePr(val,"the number of processes in a paging state");
		  EVEL_EXIT();
	  }
	  
	  
	  
	  /**************************************************************************//**
	   * the number of processes in a running state
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param cpu_use      Pointer to the CPU Use.
	   * @param val          double
	   *****************************************************************************/
	  
	  
	  public void evel_measurement_process_stats_psStateRunning_set(MEASUREMENT_PROCESS_STATS process_stat,
              double val)
	  {
		  EVEL_ENTER();
		  process_stat.psStateRunning.SetValuePr(val,"the number of processes in a running state");
		  EVEL_EXIT();
	  }
	  
	  /**************************************************************************//**
	   * the number of processes in a sleeping state
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param cpu_use      Pointer to the CPU Use.
	   * @param val          double
	   *****************************************************************************/
	  
	  
	  public void evel_measurement_process_stats_psStateSleeping_set(MEASUREMENT_PROCESS_STATS process_stat,
              double val)
	  {
		  EVEL_ENTER();
		  process_stat.psStateSleeping.SetValuePr(val,"the number of processes in a sleeping state");
		  EVEL_EXIT();
	  }
	  
	  
	  /**************************************************************************//**
	   * the number of processes in a stopped state
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param cpu_use      Pointer to the CPU Use.
	   * @param val          double
	   *****************************************************************************/
	  
	  
	  public void evel_measurement_process_stats_psStateStopped_set(MEASUREMENT_PROCESS_STATS process_stat,
              double val)
	  {
		  EVEL_ENTER();
		  process_stat.psStateStopped.SetValuePr(val,"the number of processes in a stopped state");
		  EVEL_EXIT();
	  }
	  
	  /**************************************************************************//**
	   * the number of processes in a Zombie state
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param cpu_use      Pointer to the CPU Use.
	   * @param val          double
	   *****************************************************************************/
	  
	  
	  public void evel_measurement_process_stats_psStateZombie_set(MEASUREMENT_PROCESS_STATS process_stat,
              double val)
	  {
		  EVEL_ENTER();
		  process_stat.psStateZombie.SetValuePr(val,"the number of processes in a Zombie state");
		  EVEL_EXIT();
	  }
	  
	  /*
	   * VES6.0 Added fields 14July2018
      */ 
	  
	  /**************************************************************************//**
	   load average figures giving the number of jobs in the run queue (state R) or waiting for disk I/O (state D) averaged over 1 Minute
      measured CPU and IO utilization for 1 min using /proc/loadavg
	   * The name and value are null delimited ASCII strings.  The library takes
	   * a copy so the caller does not have to preserve values after the function
	   * returns.
	   *
	   * 
	   * @param usage         CPU utilization.
	   *****************************************************************************/
	  public MEASUREMENT_LOAD evel_measurement_new_load_add(double usage)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check assumptions.                                                      */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_MEASUREMENT);
//	    assert(id != null);
	    assert(usage >= 0.0);

	    /***************************************************************************/
	    /* Allocate a container for the value and push onto the list.              */
	    /***************************************************************************/
//	    LOGGER.debug(MessageFormatter.format("Adding id={0} usage={1}", id, usage));
	    MEASUREMENT_LOAD load = new MEASUREMENT_LOAD();
	    assert(load != null);
//	    load.loadIdentifier    = id;
	    load.shortTerm = new EvelOptionDouble();
	    load.midTerm = new EvelOptionDouble();
	    load.longTerm = new EvelOptionDouble();	    	   
	   
	    if( loads == null ){
	    	loads = new ArrayList<MEASUREMENT_LOAD>();
	    	LOGGER.debug("Allocate Load");
	    }

	    loads.add(load);

	    EVEL_EXIT();
	    return load;
	  }
	  
	  /**************************************************************************//**
	   * load average figures giving the number of jobs in the run queue (state R) or waiting for disk I/O (state D) averaged over 1 Minute
          measured CPU and IO utilization for 1 min using /proc/loadavg"
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param cpu_use      Pointer to the CPU Use.
	   * @param val          double
	   *****************************************************************************/
	  
	  
	  public void evel_measurement_load_shortTerm_set(MEASUREMENT_LOAD load,
              double val)
	  {
		  EVEL_ENTER();
		  load.shortTerm.SetValuePr(val,"load short term");
		  EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * "load average figures giving the number of jobs in the run queue (state R) or waiting for disk I/O (state D) averaged over 5 Minutes
          measured CPU and IO utilization for 5 mins using /proc/loadavg"
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param cpu_use      Pointer to the CPU Use.
	   * @param val          double
	   *****************************************************************************/
	  
	  
	  public void evel_measurement_load_midTerm_set(MEASUREMENT_LOAD load,
              double val)
	  {
		  EVEL_ENTER();
		  load.midTerm.SetValuePr(val,"load midterm");
		  EVEL_EXIT();
	  }
      
	  /**************************************************************************//**
	   * load average figures giving the number of jobs in the run queue (state R) or waiting for disk I/O (state D) averaged over 15 Minutes
          measured CPU and IO utilization for 15 mins using /proc/loadavg
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param cpu_use      Pointer to the CPU Use.
	   * @param val          double
	   *****************************************************************************/
	  
	  
	  public void evel_measurement_load_longTerm_set(MEASUREMENT_LOAD load,
              double val)
	  {
		  EVEL_ENTER();
		  load.longTerm.SetValuePr(val,"load longterm");
		  EVEL_EXIT();
	  }
	  
	  /******************************************************************************
	   * 
	   *****************************************************************************/
	  
	  public MACHINE_CHECK_EXCEPTION evel_measurement_new_machine_check_exception_add(String id)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check assumptions.                                                      */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_MEASUREMENT);
	    assert(id != null);

	    /***************************************************************************/
	    /* Allocate a container for the value and push onto the list.              */
	    /***************************************************************************/
	    LOGGER.debug(MessageFormatter.format("Adding id={0}", id));
	    MACHINE_CHECK_EXCEPTION machine_check_exception = new MACHINE_CHECK_EXCEPTION();
	    assert(machine_check_exception != null);
	    machine_check_exception.processIdentifier = id;
	    machine_check_exception.correctedMemoryErrors = new EvelOptionDouble();
	    machine_check_exception.correctedMemoryErrors_In1Hr = new EvelOptionDouble();
	    machine_check_exception.uncorrectedMemoryErrors = new EvelOptionDouble();
	    machine_check_exception.uncorrectedMemoryErrors_In1Hr = new EvelOptionDouble();
	   
	   
	    if( machineCheckException == null ){
	    	machineCheckException = new ArrayList<MACHINE_CHECK_EXCEPTION>();
	    	LOGGER.debug("Allocate new machineCheckException");
	    }

	    machineCheckException.add(machine_check_exception);

	    EVEL_EXIT();
	    return machine_check_exception;
	  }
	  
	  
	  public MACHINE_CHECK_EXCEPTION evel_measurement_Exception_correctedMemoryErrors_set(MACHINE_CHECK_EXCEPTION exception,
              double val)
	  {
		  EVEL_ENTER();
		  exception.correctedMemoryErrors.SetValuePr(val, "Exception_correctedMemoryErrors");
		  EVEL_EXIT();
		  
		  return exception;
	  }
      
	  public MACHINE_CHECK_EXCEPTION evel_measurement_Exception_correctedMemoryErrors_In1Hr_set(MACHINE_CHECK_EXCEPTION exception,
              double val)
	  {
		  EVEL_ENTER();
		  exception.correctedMemoryErrors_In1Hr.SetValuePr(val, "Exception_correctedMemoryErrors_In1Hr");
		  EVEL_EXIT();
		  return exception;
		  
	  }
	 
	  public MACHINE_CHECK_EXCEPTION evel_measurement_Exception_uncorrectedMemoryErrors_set(MACHINE_CHECK_EXCEPTION exception,
              double val)
	  {
		  EVEL_ENTER();
		  exception.uncorrectedMemoryErrors.SetValuePr(val, "Exception_uncorrectedMemoryErrors");
		  EVEL_EXIT();
		  return exception;
	  }
	  
	  public MACHINE_CHECK_EXCEPTION evel_measurement_Exception_uncorrectedMemoryErrors_In1Hr_set(MACHINE_CHECK_EXCEPTION exception,
              double val)
	  {
		  EVEL_ENTER();
		  exception.uncorrectedMemoryErrors_In1Hr.SetValuePr(val, "Exception_uncorrectedMemoryErrors_In1Hr");
		  EVEL_EXIT();
		  return exception;
	  }
	  
	  
	  /*
	   * VES6.0 Added fields 14July2018
      */
	  /**************************************************************************//**
	   * Add an additional HUGE PAGE value name/value pair to the Measurement.
	   *
	   * The name and value are null delimited ASCII strings.  The library takes
	   * a copy so the caller does not have to preserve values after the function
	   * returns.
	   *
	   * 
	   * @param id            ASCIIZ string with the CPU's identifier.
	   * @param usage         CPU utilization.
	   *****************************************************************************/
	  public MEASUREMENT_HUGE_PAGE evel_measurement_new_huge_page_add(String id, double usage)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check assumptions.                                                      */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_MEASUREMENT);
	    assert(id != null);
	    assert(usage >= 0.0);

	    /***************************************************************************/
	    /* Allocate a container for the value and push onto the list.              */
	    /***************************************************************************/
	    LOGGER.debug(MessageFormatter.format("Adding id={0} usage={1}", id, usage));
	    MEASUREMENT_HUGE_PAGE huge_page = new MEASUREMENT_HUGE_PAGE();
	    assert(huge_page != null);
	    huge_page.hugePagesIdentifier    = id;
	    huge_page.bytesUsed = usage;
	    huge_page.bytesFree = new EvelOptionDouble();
	    huge_page.percentFree = new EvelOptionDouble();
	    huge_page.percentUsed = new EvelOptionDouble();
	    huge_page.vmPageNumberFree = new EvelOptionDouble();
	    huge_page.vmPageNumberUsed = new EvelOptionDouble();
	   
	   
	    if( huge_pages == null ){
	    	huge_pages = new ArrayList<MEASUREMENT_HUGE_PAGE>();
	    	LOGGER.debug("Allocate new cpu usage");
	    }

	    huge_pages.add(huge_page);

	    EVEL_EXIT();
	    return huge_page;
	  }

	  /**************************************************************************//**
	   * Set Number of free hugepages in percent
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param cpu_use      Pointer to the CPU Use.
	   * @param val          double
	   *****************************************************************************/
	  
	  
	  public void evel_measurement_huge_page_percentFree_set(MEASUREMENT_HUGE_PAGE huge_page,
              double val)
	  {
		  EVEL_ENTER();
		  huge_page.percentFree.SetValuePr(val,"Number of free hugepages in percent");
		  EVEL_EXIT();
		  
		  
	  }
	  
	  /**************************************************************************//**
	   * Set Number of used hugepages in percent
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param cpu_use      Pointer to the CPU Use.
	   * @param val          double
	   *****************************************************************************/
	  
	  
	  public void evel_measurement_huge_page_percentUsed_set(MEASUREMENT_HUGE_PAGE huge_page,
              double val)
	  {
		  EVEL_ENTER();
		  huge_page.percentUsed.SetValuePr(val,"Number of used hugepages in percent");
		  EVEL_EXIT();
	  }
	  /**************************************************************************//**
	   * Set Number of used hugepages in numbers
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param cpu_use      Pointer to the CPU Use.
	   * @param val          double
	   *****************************************************************************/
	  
	  
	  public void evel_measurement_huge_page_vmPageNumberFree_set(MEASUREMENT_HUGE_PAGE huge_page,
              double val)
	  {
		  EVEL_ENTER();
		  huge_page.vmPageNumberFree.SetValuePr(val,"Number of used hugepages in numbers");
		  EVEL_EXIT();
	  }
	  /**************************************************************************//**
	   * Set Number of used hugepages in numbers
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param cpu_use      Pointer to the CPU Use.
	   * @param val          double
	   *****************************************************************************/
	  
	  
	  public void evel_measurement_huge_page_vmPageNumberUsed_set(MEASUREMENT_HUGE_PAGE huge_page,
              double val)
	  {
		  EVEL_ENTER();
		  huge_page.vmPageNumberUsed.SetValuePr(val,"Number of used hugepages in numbers");
		  EVEL_EXIT();
	  }
	  
	  /**************************************************************************//**
	   * Set Number of used hugepages in numbers
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param cpu_use      Pointer to the CPU Use.
	   * @param val          double
	   *****************************************************************************/
	  
	  
	  public void evel_measurement_huge_page_bytesFree_set(MEASUREMENT_HUGE_PAGE huge_page,
              double val)
	  {
		  EVEL_ENTER();
		  huge_page.bytesFree.SetValuePr(val,"Number of used hugepages in numbers");
		  EVEL_EXIT();
	  }
	  /**************************************************************************//**
	   * Add an additional CPU usage value name/value pair to the Measurement.
	   *
	   * The name and value are null delimited ASCII strings.  The library takes
	   * a copy so the caller does not have to preserve values after the function
	   * returns.
	   *
	   * 
	   * @param id            ASCIIZ string with the CPU's identifier.
	   * @param usage         CPU utilization.
	   *****************************************************************************/
	  public MEASUREMENT_CPU_USE evel_measurement_new_cpu_use_add(String id, double usage)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check assumptions.                                                      */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_MEASUREMENT);
	    assert(id != null);
	    assert(usage >= 0.0);

	    /***************************************************************************/
	    /* Allocate a container for the value and push onto the list.              */
	    /***************************************************************************/
	    LOGGER.debug(MessageFormatter.format("Adding id={0} usage={1}", id, usage));
	    MEASUREMENT_CPU_USE cpu_use = new MEASUREMENT_CPU_USE();
	    assert(cpu_use != null);
	    cpu_use.id    = id;
	    cpu_use.usage = usage;
	    cpu_use.idle = new EvelOptionDouble();
	    cpu_use.intrpt = new EvelOptionDouble();
	    cpu_use.nice = new EvelOptionDouble();
	    cpu_use.softirq = new EvelOptionDouble();
	    cpu_use.steal = new EvelOptionDouble();
	    cpu_use.sys = new EvelOptionDouble();
	    cpu_use.user = new EvelOptionDouble();
	    cpu_use.wait = new EvelOptionDouble();
	    /*
	     * Ves6.0 Added Fields 14/07/2018
	     */
	    cpu_use.cpuCapacityContention= new EvelOptionDouble();
	    cpu_use.cpuDemandAvg= new EvelOptionDouble();
	    cpu_use.cpuDemandMhz= new EvelOptionDouble();
	    cpu_use.cpuDemandPct= new EvelOptionDouble();
	    cpu_use.cpuLatencyAvg= new EvelOptionDouble();
	    cpu_use.cpuOverheadAvg= new EvelOptionDouble();
	    cpu_use.cpuSwapWaitTime= new EvelOptionDouble();
	    if( cpu_usage == null ){
	    	cpu_usage = new ArrayList<MEASUREMENT_CPU_USE>();
	    	LOGGER.debug("Allocate new cpu usage");
	    }

	    cpu_usage.add(cpu_use);

	    EVEL_EXIT();
	    return cpu_use;
	  }
	  /**************************************************************************//**
	   * Set the amount of time the CPU cannot run due to centention, in milliseconds.
	   *   
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param cpu_use      Pointer to the CPU Use.
	   * @param val          double
	   *****************************************************************************/
	  
	  
	  public void evel_measurement_cpu_use_cpuCapacityContention_set(MEASUREMENT_CPU_USE cpu_use,
              double val)
	  {
		  EVEL_ENTER();
		  cpu_use.cpuCapacityContention.SetValuePr(val,"CPU cpuCapacityContention");
		  EVEL_EXIT();
	  }
	  /**************************************************************************//**
	   * Set the total CPU time that the VNF/VNFC/VM could use if there is no contention, in milliseconds.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param cpu_use      Pointer to the CPU Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_cpu_use_cpuDeamandAvg_set(MEASUREMENT_CPU_USE cpu_use,
              double val)
	  {
		  EVEL_ENTER();
		  cpu_use.cpuDemandAvg.SetValuePr(val,"Total CPU Time");
		  EVEL_EXIT();
	  }
	  
	  /**************************************************************************//**
	   * Set CPU demand as a percentage of the provisioned capacity.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param cpu_use      Pointer to the CPU Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_cpu_use_cpuDeamandPct_set(MEASUREMENT_CPU_USE cpu_use,
              double val)
	  {
		  EVEL_ENTER();
		  cpu_use.cpuDemandPct.SetValuePr(val,"CPU Demand as a percentage");
		  EVEL_EXIT();
	  }
	  /**************************************************************************//**
	   * Set CPU demand in megahertz.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param cpu_use      Pointer to the CPU Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_cpu_use_cpuDeamandMhz_set(MEASUREMENT_CPU_USE cpu_use,
              double val)
	  {
		  EVEL_ENTER();
		  cpu_use.cpuDemandMhz.SetValuePr(val,"CPU demand in megahertz");
		  EVEL_EXIT();
	  }
	  /**************************************************************************//**
	   * Set Percentage of time the VM is unable to run because it is contending for access to the physical CPUs.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param cpu_use      Pointer to the CPU Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_cpu_use_cpuLatencyAvg_set(MEASUREMENT_CPU_USE cpu_use,
              double val)
	  {
		  EVEL_ENTER();
		  cpu_use.cpuLatencyAvg.SetValuePr(val,"CPU Percentage of time");
		  EVEL_EXIT();
	  }
	  /**************************************************************************//**
	   * Set The overhead demand above available allocations and reservations.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param cpu_use      Pointer to the CPU Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_cpu_use_cpuOverheadAvg_set(MEASUREMENT_CPU_USE cpu_use,
              double val)
	  {
		  EVEL_ENTER();
		  cpu_use.cpuOverheadAvg.SetValuePr(val,"CPU overhead demand");
		  EVEL_EXIT();
	  }
	  /**************************************************************************//**
	   * Set CPU Swap wait time in milliseconds.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param cpu_use      Pointer to the CPU Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_cpu_use_cpuSwapWaitTime_set(MEASUREMENT_CPU_USE cpu_use,
              double val)
	  {
		  EVEL_ENTER();
		  cpu_use.cpuSwapWaitTime.SetValuePr(val,"CPU Swap wait time");
		  EVEL_EXIT();
	  }
	  

	 

	  /**************************************************************************//**
	   * Set the CPU Idle value in measurement interval
	   *   percentage of CPU time spent in the idle task
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param cpu_use      Pointer to the CPU Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_cpu_use_idle_set(MEASUREMENT_CPU_USE cpu_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    cpu_use.idle.SetValuePr(val,"CPU idle time");
	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the percentage of time spent servicing interrupts
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param cpu_use      Pointer to the CPU Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_cpu_use_interrupt_set(MEASUREMENT_CPU_USE cpu_use,
	                                              double val)
	  {
	    EVEL_ENTER();
	    cpu_use.intrpt.SetValuePr(val,"CPU interrupt value");

	    EVEL_EXIT();
	  }


	  /**************************************************************************//**
	   * Set the percentage of time spent running user space processes that have been niced
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param cpu_use      Pointer to the CPU Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_cpu_use_nice_set(MEASUREMENT_CPU_USE cpu_use,
	                                         double val)
	  {
	    EVEL_ENTER();
	    cpu_use.nice.SetValuePr(val, "CPU nice value");

	    EVEL_EXIT();
	  }


	  /**************************************************************************//**
	   * Set the percentage of time spent handling soft irq interrupts
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param cpu_use      Pointer to the CPU Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_cpu_use_softirq_set(MEASUREMENT_CPU_USE cpu_use,
	                                            double val)
	  {
	    EVEL_ENTER();
	    cpu_use.softirq.SetValuePr(val, "CPU Soft IRQ value");

	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the percentage of time spent in involuntary wait
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param cpu_use      Pointer to the CPU Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_cpu_use_steal_set(MEASUREMENT_CPU_USE cpu_use,
	                                          double val)
	  {
	    EVEL_ENTER();
	    cpu_use.steal.SetValuePr(val,"CPU involuntary wait");

	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the percentage of time spent on system tasks running the kernel
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param cpu_use      Pointer to the CPU Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_cpu_use_system_set(MEASUREMENT_CPU_USE cpu_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    cpu_use.sys.SetValuePr(val,"CPU System load");
	    EVEL_EXIT();
	  }


	  /**************************************************************************//**
	   * Set the percentage of time spent running un-niced user space processes
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param cpu_use      Pointer to the CPU Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_cpu_use_usageuser_set(MEASUREMENT_CPU_USE cpu_use,
	                                              double val)
	  {
	    EVEL_ENTER();
	    cpu_use.user.SetValuePr(val,"CPU User load value");

	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the percentage of CPU time spent waiting for I/O operations to complete
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param cpu_use      Pointer to the CPU Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_cpu_use_wait_set(MEASUREMENT_CPU_USE cpu_use,
	                                         double val)
	  {
	    EVEL_ENTER();
	    cpu_use.wait.SetValuePr(val, "CPU Wait IO value");

	    EVEL_EXIT();
	  }

      
	  /**************************************************************************//**
	   * Add an additional Memory usage value name/value pair to the Measurement.
	   *
	   * The name and value are null delimited ASCII strings.  The library takes
	   * a copy so the caller does not have to preserve values after the function
	   * returns.
	   *
	   * 
	   * @param id            ASCIIZ string with the Memory identifier.
	   * @param vmidentifier  ASCIIZ string with the VM's identifier.
	   * @param membuffsz     Memory Size.
	   *
	   * @return  Returns pointer to memory use structure in measurements
	   *****************************************************************************/
	  public MEASUREMENT_MEM_USE evel_measurement_new_mem_use_add(
	                                   String vmidentifier,  double membuffsz)
	  {
	    MEASUREMENT_MEM_USE mem_use = null;
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check assumptions.                                                      */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_MEASUREMENT);
	//    assert(id != null);
	    assert(membuffsz >= 0.0);

	    /***************************************************************************/
	    /* Allocate a container for the value and push onto the list.              */
	    /***************************************************************************/
	    LOGGER.debug(MessageFormatter.format("Adding buffer size={1}", membuffsz));
	    mem_use = new MEASUREMENT_MEM_USE();
	    assert(mem_use != null);
	//    mem_use.id    = id;
	    mem_use.vmid  = vmidentifier;
	    mem_use.membuffsz = membuffsz;
	    mem_use.memcache = new EvelOptionDouble();
	    mem_use.memconfig= new EvelOptionDouble();
	    mem_use.memfree= new EvelOptionDouble();
	    mem_use.slabrecl= new EvelOptionDouble();
	    mem_use.slabunrecl= new EvelOptionDouble();
	    mem_use.memused= new EvelOptionDouble();
	    
	    
	    
	    mem_use.memoryDemand= new EvelOptionDouble();
	    mem_use.memoryLatencyAvg= new EvelOptionDouble();
	    mem_use.memorySharedAvg= new EvelOptionDouble();
	    mem_use.memorySwapInAvg= new EvelOptionDouble();
	    mem_use.memorySwapInRateAvg= new EvelOptionDouble();
	    mem_use.memorySwapOutAvg= new EvelOptionDouble();
	    mem_use.memorySwapOutRateAvg= new EvelOptionDouble();
	    mem_use.memorySwapUsedAvg= new EvelOptionDouble();

	//    assert(mem_use.id != null);
	    
	    if( mem_usage == null ){
	    	mem_usage = new ArrayList<MEASUREMENT_MEM_USE>();
	    	LOGGER.debug("Allocated new memory usage");
	    }

	    mem_usage.add(mem_use);

	    EVEL_EXIT();
	    return mem_use;
	  }

	  /**************************************************************************//**
	   * Set kilobytes of memory used for cache
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param mem_use      Pointer to the Memory Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_mem_use_memcache_set(MEASUREMENT_MEM_USE mem_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    mem_use.memcache.SetValuePr(val,"Memory cache value");

	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set kilobytes of memory configured in the virtual machine on which the VNFC reporting
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param mem_use      Pointer to the Memory Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_mem_use_memconfig_set(MEASUREMENT_MEM_USE mem_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    mem_use.memconfig.SetValuePr(val, "Memory configured value");
	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set kilobytes of physical RAM left unused by the system
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param mem_use      Pointer to the Memory Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_mem_use_memfree_set(MEASUREMENT_MEM_USE mem_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    mem_use.memfree.SetValuePr(val, "Memory freely available value");
	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the part of the slab that can be reclaimed such as caches measured in kilobytes
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param mem_use      Pointer to the Memory Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_mem_use_slab_reclaimed_set(MEASUREMENT_MEM_USE mem_use,
	                                       double val)
	  {
	    EVEL_ENTER();
	    mem_use.slabrecl.SetValuePr(val, "Memory reclaimable slab set");
	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the part of the slab that cannot be reclaimed such as caches measured in kilobytes
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param mem_use      Pointer to the Memory Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_mem_use_slab_unreclaimable_set(MEASUREMENT_MEM_USE  mem_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    mem_use.slabunrecl.SetValuePr(val, "Memory unreclaimable slab set");
	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the total memory minus the sum of free, buffered, cached and slab memory in kilobytes
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param mem_use      Pointer to the Memory Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_mem_use_usedup_set(MEASUREMENT_MEM_USE mem_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    mem_use.memused.SetValuePr(val, "Memory usedup total set");
	    EVEL_EXIT();
	  }
	  
	  
	  /*
	   * VES6.0 Added Fields 14July
	  */
	  /**************************************************************************//**
	   * Set the Host demand in kibibytes.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param mem_use      Pointer to the Memory Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_mem_use_memoryDemand_set(MEASUREMENT_MEM_USE mem_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    mem_use.memoryDemand.SetValuePr(val, "Host demand in kibibytes");
	    EVEL_EXIT();
	  }
	  
	  
	  /**************************************************************************//**
	   * Set Percentage of time the VM is waiting to access swapped or compressed memory.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param mem_use      Pointer to the Memory Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_mem_use_memoryLatencyAvg_set(MEASUREMENT_MEM_USE mem_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    mem_use.memoryLatencyAvg.SetValuePr(val, "Percentage of time the VM is waiting to access swapped or compressed memory");
	    EVEL_EXIT();
	  }
	  
	  /**************************************************************************//**
	   * Set Space used for caching swapped pages in the host cache in kibibytes.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param mem_use      Pointer to the Memory Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_mem_use_memorySharedAvg_set(MEASUREMENT_MEM_USE mem_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    mem_use.memorySharedAvg.SetValuePr(val, "Space used for caching swapped pages in the host cache in kibibytes");
	    EVEL_EXIT();
	  }

	  
	  /**************************************************************************//**
	   * Set Amount of memory swapped-in from host cache in kibibytes.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param mem_use      Pointer to the Memory Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_mem_use_memorySwapInAvg_set(MEASUREMENT_MEM_USE mem_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    mem_use.memorySwapInAvg.SetValuePr(val, "Amount of memory swapped-in from host cache in kibibytes.");
	    EVEL_EXIT();
	  }
	  
	  /**************************************************************************//**
	   * Set Rate at which memory is swapped from disk into active memory during the interval in kilobyte per second.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param mem_use      Pointer to the Memory Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_mem_use_memorySwapInRateAvg_set(MEASUREMENT_MEM_USE mem_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    mem_use.memorySwapInRateAvg.SetValuePr(val, "Rate at which memory is swapped from disk into active memory during the interval in kilobyte per second.");
	    EVEL_EXIT();
	  }
	  
	  
	  /**************************************************************************//**
	   * Set Amount of memory swapped-out to host cache in kibibytes
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param mem_use      Pointer to the Memory Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_mem_use_memorySwapOutAvg_set(MEASUREMENT_MEM_USE mem_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    mem_use.memorySwapOutAvg.SetValuePr(val, "Amount of memory swapped-out to host cache in kibibytes.");
	    EVEL_EXIT();
	  }
	  
	  /**************************************************************************//**
	   * Set Rate at which memory is being swapped from active memory to disk during the current interval in kilobytes per second.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param mem_use      Pointer to the Memory Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_mem_use_memorySwapOutRateAvg_set(MEASUREMENT_MEM_USE mem_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    mem_use.memorySwapOutRateAvg.SetValuePr(val, "Rate at which memory is being swapped from active memory to disk during the current interval in kilobytes per second");
	    EVEL_EXIT();
	  }
	  
	  /**************************************************************************//**
	   * Set Space used for caching swapped pages in the host cache in kibibytes.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param mem_use      Pointer to the Memory Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_mem_use_memorySwapUsedAvg_set(MEASUREMENT_MEM_USE mem_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    mem_use.memorySwapUsedAvg.SetValuePr(val, "Space used for caching swapped pages in the host cache in kibibytes.");
	    EVEL_EXIT();
	  }
	  
	  
	  /**************************************************************************//**
	   * Add an additional Disk usage value name/value pair to the Measurement.
	   *
	   * The name and value are null delimited ASCII strings.  The library takes
	   * a copy so the caller does not have to preserve values after the function
	   * returns.
	   *
	   * 
	   * @param id            ASCIIZ string with the CPU's identifier.
	   * @param usage         Disk utilization.
	   *****************************************************************************/
	  public MEASUREMENT_DISK_USE evel_measurement_new_disk_use_add(String id)
	  {
	    MEASUREMENT_DISK_USE disk_use = null;
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check assumptions.                                                      */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_MEASUREMENT);
	    assert(id != null);

	    /***************************************************************************/
	    /* Allocate a container for the value and push onto the list.              */
	    /***************************************************************************/
	    LOGGER.debug(MessageFormatter.format("Adding id={0} disk usage", id));
	    disk_use = new MEASUREMENT_DISK_USE();
	    assert(disk_use != null);
	    disk_use.id    = id;
	    assert(disk_use.id != null);

	    disk_use.iotimeavg= new EvelOptionDouble();
	    disk_use.iotimelast= new EvelOptionDouble();
	    disk_use.iotimemax= new EvelOptionDouble();
	    disk_use.iotimemin= new EvelOptionDouble();
	    disk_use.mergereadavg= new EvelOptionDouble();
	    disk_use.mergereadlast= new EvelOptionDouble();
	    disk_use.mergereadmax= new EvelOptionDouble();
	    disk_use.mergereadmin= new EvelOptionDouble();
	    disk_use.mergewriteavg= new EvelOptionDouble();
	    disk_use.mergewritelast= new EvelOptionDouble();
	    disk_use.mergewritemax= new EvelOptionDouble();
	    disk_use.mergewritemin= new EvelOptionDouble();
	    disk_use.octetsreadavg= new EvelOptionDouble();
	    disk_use.octetsreadlast= new EvelOptionDouble();
	    disk_use.octetsreadmax= new EvelOptionDouble();
	    disk_use.octetsreadmin= new EvelOptionDouble();
	    disk_use.octetswriteavg= new EvelOptionDouble();
	    disk_use.octetswritelast= new EvelOptionDouble();
	    disk_use.octetswritemax= new EvelOptionDouble();
	    disk_use.octetswritemin= new EvelOptionDouble();
	    disk_use.opsreadavg= new EvelOptionDouble();
	    disk_use.opsreadlast= new EvelOptionDouble();
	    disk_use.opsreadmax= new EvelOptionDouble();
	    disk_use.opsreadmin= new EvelOptionDouble();
	    disk_use.opswriteavg= new EvelOptionDouble();
	    disk_use.opswritelast= new EvelOptionDouble();
	    disk_use.opswritemax= new EvelOptionDouble();
	    disk_use.opswritemin= new EvelOptionDouble();
	    disk_use.pendingopsavg= new EvelOptionDouble();
	    disk_use.pendingopslast= new EvelOptionDouble();
	    disk_use.pendingopsmax= new EvelOptionDouble();
	    disk_use.pendingopsmin= new EvelOptionDouble();
	    disk_use.timereadavg= new EvelOptionDouble();
	    disk_use.timereadlast= new EvelOptionDouble();
	    disk_use.timereadmax= new EvelOptionDouble();
	    disk_use.timereadmin= new EvelOptionDouble();
	    disk_use.timewriteavg= new EvelOptionDouble();
	    disk_use.timewritelast= new EvelOptionDouble();
	    disk_use.timewritemax= new EvelOptionDouble();
	    disk_use.timewritemin= new EvelOptionDouble();
	    /*
	     * 
	     */
	    disk_use.diskBusResets=new EvelOptionDouble();
	    disk_use.diskCommandsAborted=new EvelOptionDouble();
	    disk_use.diskCommandsAvg=new EvelOptionDouble();
	    disk_use.diskFlushRequests=new EvelOptionDouble();
	    disk_use.diskFlushTime=new EvelOptionDouble();
	    disk_use.diskReadCommandsAvg=new EvelOptionDouble();
	    disk_use.diskTime=new EvelOptionDouble();
	    disk_use.diskTotalReadLatencyAvg=new EvelOptionDouble();
	    disk_use.diskWriteCommandsAvg=new EvelOptionDouble();
	    disk_use.diskTotalWriteLatencyAvg=new EvelOptionDouble();
	    
	    
	    disk_use.diskWeightedIoTimeAvg=new EvelOptionDouble();
	    disk_use.diskWeightedIoTimeLast=new EvelOptionDouble();
	    disk_use.diskWeightedIoTimeMax=new EvelOptionDouble();
	    disk_use.diskWeightedIoTimeMin=new EvelOptionDouble();
	    
	    
	    
	    if( disk_usage == null ){
	    	disk_usage = new ArrayList<MEASUREMENT_DISK_USE>();
	    	LOGGER.debug("Unable to allocate new disk usage");
	    }

	    
	    disk_usage.add(disk_use);


	    EVEL_EXIT();
	    return disk_use;
	  }
	  
	  /*
	   * Ves 6.0 19/07/2018
	   */
	  
	  /**************************************************************************//**
	   * Set milliseconds spent doing input/output operations over 1 sec; treat
	   * this metric as a device load percentage where 1000ms  matches 100% load;
	   * provide the average over the measurement interval
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/

	  
	  public void evel_measurement_disk_use_diskWeightedIoTimeAvg_set(MEASUREMENT_DISK_USE  disk_use,
              double val) 
	  {
		  	EVEL_ENTER();
		  	disk_use.diskWeightedIoTimeAvg.SetValuePr(val,"average within the collection interval");
		  	EVEL_EXIT();
	  }
	  
	  
	  public void evel_measurement_disk_use_diskWeightedIoTimeLast_set(MEASUREMENT_DISK_USE  disk_use,
              double val) 
	  {
		  	EVEL_ENTER();
		  	disk_use.diskWeightedIoTimeLast.SetValuePr(val,"last within the collection interval.");
		  	EVEL_EXIT();
	  }
	  
	  public void evel_measurement_disk_use_diskWeightedIoTimeMax_set(MEASUREMENT_DISK_USE  disk_use,
              double val) 
	  {
		  	EVEL_ENTER();
		  	disk_use.diskWeightedIoTimeMax.SetValuePr(val,"maximum within the collection interval.");
		  	EVEL_EXIT();
	  }
	  
	  public void evel_measurement_disk_use_diskWeightedIoTimeMin_set(MEASUREMENT_DISK_USE  disk_use,
              double val) 
	  {
		  	EVEL_ENTER();
		  	disk_use.diskWeightedIoTimeMin.SetValuePr(val,"minimum within the collection interval.");
		  	EVEL_EXIT();
	  }
	  
	  
	  
	  
	  /*
	   * *************************************
	   */
	  
	  /**************************************************************************//**
	   * Set milliseconds spent doing input/output operations over 1 sec; treat
	   * this metric as a device load percentage where 1000ms  matches 100% load;
	   * provide the average over the measurement interval
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_diskBusResets_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val) 
	  {
	    EVEL_ENTER();
	    disk_use.diskBusResets.SetValuePr(val,"Disk Bus Resets");
	    EVEL_EXIT();
	  }
	  /**************************************************************************//**
	   * Set milliseconds spent doing input/output operations over 1 sec; treat
	   * this metric as a device load percentage where 1000ms  matches 100% load;
	   * provide the average over the measurement interval
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_diskCommandsAborted_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val) 
	  {
	    EVEL_ENTER();
	    disk_use.diskCommandsAborted.SetValuePr(val,"Disk ioload set");
	    EVEL_EXIT();
	  }
	  /**************************************************************************//**
	   * Set Average number of commands per second.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_diskCommandsAvg_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val) 
	  {
	    EVEL_ENTER();
	    disk_use.diskCommandsAvg.SetValuePr(val,"Average number of commands per second");
	    EVEL_EXIT();
	  }
	  /**************************************************************************//**
	   * Set Total flush requests of the disk cache.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_diskFlushRequests_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val) 
	  {
	    EVEL_ENTER();
	    disk_use.diskFlushRequests.SetValuePr(val,"Total flush requests");
	    EVEL_EXIT();
	  }
	  /**************************************************************************//**
	   * Set Average number of read commands issued per second to the disk during the collection interval.
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_diskReadCommandsAvg_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val) 
	  {
	    EVEL_ENTER();
	    disk_use.diskReadCommandsAvg.SetValuePr(val,"Average number of read commands issued per second to the disk during the collection interval.");
	    EVEL_EXIT();
	  }
	  /**************************************************************************//**
	   * Set Total time spent on disk cache flushing in milliseconds.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_diskFlushTime_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val) 
	  {
	    EVEL_ENTER();
	    disk_use.diskFlushTime.SetValuePr(val,"Total time spent on disk cache flushing in milliseconds.");
	    EVEL_EXIT();
	  }
	  /**************************************************************************//**
	   * Set Total time spent on disk cache reads/writes in nanoseconds
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_diskTime_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val) 
	  {
	    EVEL_ENTER();
	    disk_use.diskTime.SetValuePr(val,"Total time spent on disk cache reads/writes in nanoseconds");
	    EVEL_EXIT();
	  }
	  /**************************************************************************//**
	   * Set The average amount of time taken for a read from the perspective of a Guest OS. This is the sum of Kernel Read Latency and Physical Device Read Latency.
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_diskTotalReadLatencyAvg_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val) 
	  {
	    EVEL_ENTER();
	    disk_use.diskTotalReadLatencyAvg.SetValuePr(val,"The average amount of time taken for a read from the perspective of a Guest OS. This is the sum of Kernel Read Latency and Physical Device Read Latency.");
	    EVEL_EXIT();
	  }
	  /**************************************************************************//**
	   * Set The average amount of time taken for a write from the perspective of a Guest OS. This is the sum of Kernel Write Latency and Physical Device Write Latency.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_diskTotalWriteLatencyAvg_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val) 
	  {
	    EVEL_ENTER();
	    disk_use.diskTotalWriteLatencyAvg.SetValuePr(val,"The average amount of time taken for a write from the perspective of a Guest OS. This is the sum of Kernel Write Latency and Physical Device Write Latency.");
	    EVEL_EXIT();
	  }
	  /**************************************************************************//**
	   * Set Average number of write commands issued per second to the disk during the collection interval.
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_diskWriteCommandsAvg_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val) 
	  {
	    EVEL_ENTER();
	    disk_use.diskWriteCommandsAvg.SetValuePr(val,"Average number of write commands issued per second to the disk during the collection interval.");
	    EVEL_EXIT();
	  }
	  /**************************************************************************//**
	   * Set milliseconds spent doing input/output operations over 1 sec; treat
	   * this metric as a device load percentage where 1000ms  matches 100% load;
	   * provide the average over the measurement interval
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_iotimeavg_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val) 
	  {
	    EVEL_ENTER();
	    disk_use.iotimeavg.SetValuePr(val,"Disk ioload set");
	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set milliseconds spent doing input/output operations over 1 sec; treat
	   * this metric as a device load percentage where 1000ms  matches 100% load;
	   * provide the last value within the measurement interval
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_iotimelast_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    disk_use.iotimelast.SetValuePr(val, "Disk ioloadlast set");
	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set milliseconds spent doing input/output operations over 1 sec; treat
	   * this metric as a device load percentage where 1000ms  matches 100% load;
	   * provide the maximum value within the measurement interval
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_iotimemax_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    disk_use.iotimemax.SetValuePr(val, "Disk ioloadmax set");
	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set milliseconds spent doing input/output operations over 1 sec; treat
	   * this metric as a device load percentage where 1000ms  matches 100% load;
	   * provide the minimum value within the measurement interval
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_iotimemin_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    disk_use.iotimemin.SetValuePr(val, "Disk ioloadmin set");
	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set number of logical read operations that were merged into physical read
	   * operations, e.g., two logical reads were served by one physical disk access;
	   * provide the average measurement within the measurement interval
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_mergereadavg_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    disk_use.mergereadavg.SetValuePr(val, "Disk Merged read average set");
	    EVEL_EXIT();
	  }
	  /**************************************************************************//**
	   * Set number of logical read operations that were merged into physical read
	   * operations, e.g., two logical reads were served by one physical disk access;
	   * provide the last measurement within the measurement interval
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_mergereadlast_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    disk_use.mergereadlast.SetValuePr(val, "Disk mergedload last set");
	    EVEL_EXIT();
	  }
	  /**************************************************************************//**
	   * Set number of logical read operations that were merged into physical read
	   * operations, e.g., two logical reads were served by one physical disk access;
	   * provide the maximum measurement within the measurement interval
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_mergereadmax_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    disk_use.mergereadmax.SetValuePr(val, "Disk merged loadmax set");
	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set number of logical read operations that were merged into physical read
	   * operations, e.g., two logical reads were served by one physical disk access;
	   * provide the minimum measurement within the measurement interval
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_mergereadmin_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    disk_use.mergereadmin.SetValuePr(val, "Disk merged loadmin set");
	    EVEL_EXIT();
	  }
	  /**************************************************************************//**
	   * Set number of logical write operations that were merged into physical read
	   * operations, e.g., two logical writes were served by one physical disk access;
	   * provide the last measurement within the measurement interval
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_mergewritelast_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    disk_use.mergewritelast.SetValuePr(val, "Disk merged writelast set");
	    EVEL_EXIT();
	  }
	  /**************************************************************************//**
	   * Set number of logical write operations that were merged into physical read
	   * operations, e.g., two logical writes were served by one physical disk access;
	   * provide the maximum measurement within the measurement interval
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_mergewritemax_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    disk_use.mergewritemax.SetValuePr(val, "Disk writemax set");
	    EVEL_EXIT();
	  }
	  /**************************************************************************//**
	   * Set number of logical write operations that were merged into physical read
	   * operations, e.g., two logical writes were served by one physical disk access;
	   * provide the maximum measurement within the measurement interval
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_mergewritemin_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    disk_use.mergewritemin.SetValuePr(val, "Disk writemin set");
	    EVEL_EXIT();
	  }
          /**************************************************************************//**
           * Set number of logical write operations that were merged into physical read
           * operations, e.g., two logical writes were served by one physical disk access;
           * provide the maximum measurement within the measurement interval
           *
           * @note  The property is treated as immutable: it is only valid to call
           *        the setter once.  However, we don't assert if the caller tries to
           *        overwrite, just ignoring the update instead.
           *
           * @param disk_use     Pointer to the Disk Use.
           * @param val          double
           *****************************************************************************/
          public void evel_measurement_disk_use_mergewriteavg_set(MEASUREMENT_DISK_USE  disk_use,
                                              double val)
          {
            EVEL_ENTER();
            disk_use.mergewriteavg.SetValuePr(val, "Disk writeavg set");
            EVEL_EXIT();
          }


	  /**************************************************************************//**
	   * Set number of octets per second read from a disk or partition;
	   * provide the average measurement within the measurement interval
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_octetsreadavg_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    disk_use.octetsreadavg.SetValuePr(val, "Octets readavg set");
	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set number of octets per second read from a disk or partition;
	   * provide the last measurement within the measurement interval
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_octetsreadlast_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    disk_use.octetsreadlast.SetValuePr(val, "Octets readlast set");
	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set number of octets per second read from a disk or partition;
	   * provide the maximum measurement within the measurement interval
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_octetsreadmax_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    disk_use.octetsreadmax.SetValuePr(val, "Octets readmax set");
	    EVEL_EXIT();
	  }
	  /**************************************************************************//**
	   * Set number of octets per second read from a disk or partition;
	   * provide the minimum measurement within the measurement interval
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_octetsreadmin_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    disk_use.octetsreadmin.SetValuePr(val, "Octets readmin set");
	    EVEL_EXIT();
	  }
	  /**************************************************************************//**
	   * Set number of octets per second written to a disk or partition;
	   * provide the average measurement within the measurement interval
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_octetswriteavg_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    disk_use.octetswriteavg.SetValuePr(val, "Octets writeavg set");
	    EVEL_EXIT();
	  }
	  /**************************************************************************//**
	   * Set number of octets per second written to a disk or partition;
	   * provide the last measurement within the measurement interval
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_octetswritelast_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    disk_use.octetswritelast.SetValuePr(val, "Octets writelast set");
	    EVEL_EXIT();
	  }
	  /**************************************************************************//**
	   * Set number of octets per second written to a disk or partition;
	   * provide the maximum measurement within the measurement interval
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_octetswritemax_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    disk_use.octetswritemax.SetValuePr(val, "Octets writemax set");
	    EVEL_EXIT();
	  }
	  /**************************************************************************//**
	   * Set number of octets per second written to a disk or partition;
	   * provide the minimum measurement within the measurement interval
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_octetswritemin_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    disk_use.octetswritemin.SetValuePr(val, "Octets writemin set");
	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set number of read operations per second issued to the disk;
	   * provide the average measurement within the measurement interval
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_opsreadavg_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    disk_use.opsreadavg.SetValuePr(val, "Disk read operation average set");
	    EVEL_EXIT();
	  }
	  /**************************************************************************//**
	   * Set number of read operations per second issued to the disk;
	   * provide the last measurement within the measurement interval
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_opsreadlast_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    disk_use.opsreadlast.SetValuePr(val, "Disk read operation last set");
	    EVEL_EXIT();
	  }
	  /**************************************************************************//**
	   * Set number of read operations per second issued to the disk;
	   * provide the maximum measurement within the measurement interval
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_opsreadmax_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    disk_use.opsreadmax.SetValuePr(val, "Disk read operation maximum set");
	    EVEL_EXIT();
	  }
	  /**************************************************************************//**
	   * Set number of read operations per second issued to the disk;
	   * provide the minimum measurement within the measurement interval
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_opsreadmin_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    disk_use.opsreadmin.SetValuePr(val, "Disk read operation minimum set");
	    EVEL_EXIT();
	  }
	  /**************************************************************************//**
	   * Set number of write operations per second issued to the disk;
	   * provide the average measurement within the measurement interval
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_opswriteavg_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    disk_use.opswriteavg.SetValuePr(val, "Disk write operation average set");
	    EVEL_EXIT();
	  }
	  /**************************************************************************//**
	   * Set number of write operations per second issued to the disk;
	   * provide the last measurement within the measurement interval
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_opswritelast_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    disk_use.opswritelast.SetValuePr(val, "Disk write operation last set");
	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set number of write operations per second issued to the disk;
	   * provide the maximum measurement within the measurement interval
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_opswritemax_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    disk_use.opswritemax.SetValuePr(val, "Disk write operation maximum set");
	    EVEL_EXIT();
	  }
	  /**************************************************************************//**
	   * Set number of write operations per second issued to the disk;
	   * provide the average measurement within the measurement interval
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_opswritemin_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    disk_use.opswritemin.SetValuePr(val, "Disk write operation minimum set");
	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set queue size of pending I/O operations per second;
	   * provide the average measurement within the measurement interval
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_pendingopsavg_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    disk_use.pendingopsavg.SetValuePr(val, "Disk pending operation average set");
	    EVEL_EXIT();
	  }
	  /**************************************************************************//**
	   * Set queue size of pending I/O operations per second;
	   * provide the last measurement within the measurement interval
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_pendingopslast_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    disk_use.pendingopslast.SetValuePr(val, "Disk pending operation last set");
	    EVEL_EXIT();
	  }
	  /**************************************************************************//**
	   * Set queue size of pending I/O operations per second;
	   * provide the maximum measurement within the measurement interval
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_pendingopsmax_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    disk_use.pendingopsmax.SetValuePr(val, "Disk pending operation maximum set");
	    EVEL_EXIT();
	  }
	  /**************************************************************************//**
	   * Set queue size of pending I/O operations per second;
	   * provide the minimum measurement within the measurement interval
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_pendingopsmin_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    disk_use.pendingopsmin.SetValuePr(val, "Disk pending operation min set");
	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set milliseconds a read operation took to complete;
	   * provide the average measurement within the measurement interval
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_timereadavg_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    disk_use.timereadavg.SetValuePr(val, "Disk read time average set");
	    EVEL_EXIT();
	  }
	  /**************************************************************************//**
	   * Set milliseconds a read operation took to complete;
	   * provide the last measurement within the measurement interval
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_timereadlast_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    disk_use.timereadlast.SetValuePr(val, "Disk read time last set");
	    EVEL_EXIT();
	  }
	  /**************************************************************************//**
	   * Set milliseconds a read operation took to complete;
	   * provide the maximum measurement within the measurement interval
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_timereadmax_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    disk_use.timereadmax.SetValuePr(val, "Disk read time maximum set");
	    EVEL_EXIT();
	  }
	  /**************************************************************************//**
	   * Set milliseconds a read operation took to complete;
	   * provide the minimum measurement within the measurement interval
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_timereadmin_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    disk_use.timereadmin.SetValuePr(val, "Disk read time minimum set");
	    EVEL_EXIT();
	  }
	  /**************************************************************************//**
	   * Set milliseconds a write operation took to complete;
	   * provide the average measurement within the measurement interval
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_timewriteavg_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    disk_use.timewriteavg.SetValuePr(val, "Disk write time average set");
	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set milliseconds a write operation took to complete;
	   * provide the last measurement within the measurement interval
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_timewritelast_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    disk_use.timewritelast.SetValuePr(val, "Disk write time last set");
	    EVEL_EXIT();
	  }
	  /**************************************************************************//**
	   * Set milliseconds a write operation took to complete;
	   * provide the maximum measurement within the measurement interval
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_timewritemax_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    disk_use.timewritemax.SetValuePr(val, "Disk write time max set");
	    EVEL_EXIT();
	  }
	  /**************************************************************************//**
	   * Set milliseconds a write operation took to complete;
	   * provide the average measurement within the measurement interval
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param disk_use     Pointer to the Disk Use.
	   * @param val          double
	   *****************************************************************************/
	  public void evel_measurement_disk_use_timewritemin_set(MEASUREMENT_DISK_USE  disk_use,
	                                      double val)
	  {
	    EVEL_ENTER();
	    disk_use.timewritemin.SetValuePr(val, "Disk write time min set");
	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Add an additional File System usage value name/value pair to the
	   * Measurement.
	   *
	   * The filesystem_name is null delimited ASCII string.  The library takes a
	   * copy so the caller does not have to preserve values after the function
	   * returns.
	   *
	   * 
	   * @param filesystem_name   ASCIIZ string with the file-system's UUID.
	   * @param block_configured  Block storage configured.
	   * @param block_used        Block storage in use.
	   * @param block_iops        Block storage IOPS.
	   * @param ephemeral_configured  Ephemeral storage configured.
	   * @param ephemeral_used        Ephemeral storage in use.
	   * @param ephemeral_iops        Ephemeral storage IOPS.
	   *****************************************************************************/
	  public MEASUREMENT_FSYS_USE evel_measurement_fsys_use_add(
	                                     String filesystem_name,
	                                     double block_configured,
	                                     double block_used,
	                                     double block_iops,
	                                     double ephemeral_configured,
	                                     double ephemeral_used,
	                                     double ephemeral_iops)
	  {
	    MEASUREMENT_FSYS_USE fsys_use = null;
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check assumptions.                                                      */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_MEASUREMENT);
	    assert(filesystem_name != null);
	    assert(block_configured >= 0.0);
	    assert(block_used >= 0.0);
	    assert(block_iops >= 0.0);
	    assert(ephemeral_configured >= 0.0);
	    assert(ephemeral_used >= 0.0);
	    assert(ephemeral_iops >= 0.0);

	    /***************************************************************************/
	    /* Allocate a container for the value and push onto the list.              */
	    /***************************************************************************/
	    LOGGER.debug("Adding filesystem_name="+filesystem_name);
	    fsys_use = new MEASUREMENT_FSYS_USE();
	    assert(fsys_use != null);
	    fsys_use.filesystem_name = filesystem_name;
	    fsys_use.block_configured = block_configured;
	    fsys_use.block_used = block_used;
	    fsys_use.block_iops = block_iops;
	    fsys_use.ephemeral_configured = ephemeral_configured;
	    fsys_use.ephemeral_used = ephemeral_used;
	    fsys_use.ephemeral_iops = ephemeral_iops;
	    
	    if( filesystem_usage == null ){
	    	filesystem_usage = new ArrayList<MEASUREMENT_FSYS_USE>();
	    	LOGGER.debug("Allocated new file system usage");
	    }

	    filesystem_usage.add(fsys_use);

	    EVEL_EXIT();
	    
	    return fsys_use;
	  }

	  /**************************************************************************//**
	   * Add a Feature usage value name/value pair to the Measurement.
	   *
	   * The name is null delimited ASCII string.  The library takes
	   * a copy so the caller does not have to preserve values after the function
	   * returns.
	   *
	   * 
	   * @param feature         ASCIIZ string with the feature's name.
	   * @param utilization     Utilization of the feature.
	   *****************************************************************************/
	  public MEASUREMENT_FEATURE_USE evel_measurement_feature_use_add(
	                                        String feature,
	                                        int utilization)
	  {
	    MEASUREMENT_FEATURE_USE feature_use = null;
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check assumptions.                                                      */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_MEASUREMENT);
	    assert(feature != null);
	    assert(utilization >= 0);

	    /***************************************************************************/
	    /* Allocate a container for the value and push onto the list.              */
	    /***************************************************************************/
	    LOGGER.debug(MessageFormatter.format("Adding Feature={0} Use={1}", feature, utilization));
	    feature_use = new MEASUREMENT_FEATURE_USE();
	    assert(feature_use != null);
	    feature_use.feature_id = feature;
	    assert(feature_use.feature_id != null);
	    feature_use.feature_utilization = utilization;
	    
	    if( feature_usage == null ){
	    	feature_usage = new ArrayList<MEASUREMENT_FEATURE_USE>();
	    	LOGGER.debug("Allocate new feature usage");
	    }

	    feature_usage.add(feature_use);

	    EVEL_EXIT();
	    return feature_use;
	  }

	  /**************************************************************************//**
	   * Add a Additional Measurement value name/value pair to the Report.
	   *
	   * The name is null delimited ASCII string.  The library takes
	   * a copy so the caller does not have to preserve values after the function
	   * returns.
	   *
	   * @param measurement   Pointer to the Measaurement.
	   * @param group    ASCIIZ string with the measurement group's name.
	   * @param name     ASCIIZ string containing the measurement's name.
	   * @param value    ASCIIZ string containing the measurement's value.
	   *****************************************************************************/
	  public void evel_measurement_custom_measurement_add(
	                                               String  group,
	                                               String  name,
	                                               String  value)
	  {
	    MEASUREMENT_GROUP measurement_group = null;
	    CUSTOM_MEASUREMENT custom_measurement = null;
	    MEASUREMENT_GROUP item = null;
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check assumptions.                                                      */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_MEASUREMENT);
	    assert(group != null);
	    assert(name != null);
	    assert(value != null);

	    /***************************************************************************/
	    /* Allocate a container for the name/value pair.                           */
	    /***************************************************************************/
	    LOGGER.debug(MessageFormat.format("Adding Measurement Group={0} Name={1} Value={2}",
	                group, name, value));
	    custom_measurement = new CUSTOM_MEASUREMENT();
	    assert(custom_measurement != null);
	    custom_measurement.name = name;
	    assert(custom_measurement.name != null);
	    custom_measurement.value = value;
	    assert(custom_measurement.value != null);

	    /***************************************************************************/
	    /* See if we have that group already.                                      */
	    /***************************************************************************/
	    if (additional_measurements != null && additional_measurements.size()>0)
	    {
	      for(int i=0;i<additional_measurements.size();i++)
	      {
	    	  item = additional_measurements.get(i);
	    	  if( item.name.equals(group))
	    	  {
	    		  LOGGER.debug("Found existing Measurement Group");
	    		  measurement_group = item;
	    		  break;
	    	  }
	     }
	    }

	    /***************************************************************************/
	    /* If we didn't have the group already, create it.                         */
	    /***************************************************************************/
	    if (measurement_group == null)
	    {
	      LOGGER.debug("Creating new Measurement Group");
	      measurement_group = new MEASUREMENT_GROUP();
	      assert(measurement_group != null);
	      measurement_group.name = group;
	      assert(measurement_group.name != null);
	      measurement_group.measurements = new ArrayList<CUSTOM_MEASUREMENT>();
	      if( additional_measurements == null){
	    	  LOGGER.debug("Creating new Measurement Group list"+group);
	    	  additional_measurements = new ArrayList<MEASUREMENT_GROUP>();
	    	  LOGGER.debug("Allocate additional measurements ");
	      }
	      additional_measurements.add(measurement_group);
	    }

	    /***************************************************************************/
	    /* If we didn't have the group already, create it.                         */
	    /***************************************************************************/
	    LOGGER.debug("Adding custom measurement");
	    measurement_group.measurements.add(custom_measurement);

	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Add a Codec usage value name/value pair to the Measurement.
	   *
	   * The name is null delimited ASCII string.  The library takes
	   * a copy so the caller does not have to preserve values after the function
	   * returns.
	   *
	   * 
	   * @param codec           ASCIIZ string with the codec's name.
	   * @param utilization     Number of codecs in use.
	   *****************************************************************************/
	  public MEASUREMENT_CODEC_USE evel_measurement_codec_use_add( String codec,
	                                       int utilization )
	  {
	    MEASUREMENT_CODEC_USE codec_use = null;
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check assumptions.                                                      */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_MEASUREMENT);
	    assert(codec != null);
	    assert(utilization >= 0.0);

	    /***************************************************************************/
	    /* Allocate a container for the value and push onto the list.              */
	    /***************************************************************************/
	    LOGGER.debug(MessageFormatter.format("Adding Codec={0} Use={1}", codec, utilization));
	    codec_use = new MEASUREMENT_CODEC_USE();
	    assert(codec_use != null);
	    codec_use.codec_id = codec;
	    codec_use.number_in_use = utilization;
	    
	    if( codec_usage == null ){
	    	codec_usage = new ArrayList<MEASUREMENT_CODEC_USE>();
	    	LOGGER.debug("Allocated new codec usage");
	    }

	    codec_usage.add(codec_use);

	    EVEL_EXIT();
	    
	    return codec_use;
	  }


	  /**************************************************************************//**
	   * Set the Media Ports in Use property of the Measurement.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   
	   * @param media_ports_in_use  The media port usage to set.
	   *****************************************************************************/
	  public void evel_measurement_media_port_use_set(
	                                           int media_portsuse)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_MEASUREMENT);
	    assert(media_portsuse >= 0);

	    media_ports_in_use.SetValuePr(
	                        media_portsuse,
	                        "Media Ports In Use");
	    EVEL_EXIT();
	  }

	  public void evel_measurement_vnfc_scaling_metric_set(int scaling_metric)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_MEASUREMENT);
	    assert(scaling_metric >= 0.0);

	    vnfc_scaling_metric.SetValuePr(
	                           scaling_metric,
	                           "VNFC Scaling Metric");
	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Create a new Latency Bucket to be added to a Measurement event.
	   *
	   * @note    The mandatory fields on the ::MEASUREMENT_LATENCY_BUCKET must be
	   *          supplied to this factory function and are immutable once set.
	   *          Optional fields have explicit setter functions, but again values
	   *          may only be set once so that the ::MEASUREMENT_LATENCY_BUCKET has
	   *          immutable properties.
	   *
	   * @param count         Count of events in this bucket.
	   *
	   * @returns pointer to the newly manufactured ::MEASUREMENT_LATENCY_BUCKET.
	   *          If the structure is not used it must be released using free.
	   * @retval  null  Failed to create the Latency Bucket.
	   *****************************************************************************/
	  public MEASUREMENT_LATENCY_BUCKET evel_new_meas_latency_bucket(int count)
	  {
	    MEASUREMENT_LATENCY_BUCKET bucket=null;

	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(count >= 0);

	    /***************************************************************************/
	    /* Allocate, then set Mandatory Parameters.                                */
	    /***************************************************************************/
	    LOGGER.debug("Creating bucket, count = "+count);
	    bucket = new MEASUREMENT_LATENCY_BUCKET();
	    assert(bucket != null);

	    /***************************************************************************/
	    /* Set Mandatory Parameters.                                               */
	    /***************************************************************************/
	    bucket.count = count;
	    
	    /***************************************************************************/
	    /* Initialize Optional Parameters.                                         */
	    /***************************************************************************/
        bucket.low_end = new EvelOptionDouble();
        bucket.high_end = new EvelOptionDouble();
        
	    EVEL_EXIT();

	    return bucket;
	  }

	  /**************************************************************************//**
	   * Set the High End property of the Measurement Latency Bucket.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param bucket        Pointer to the Measurement Latency Bucket.
	   * @param high_end      High end of the bucket's range.
	   *****************************************************************************/
	  public void evel_meas_latency_bucket_high_end_set(
	                                       MEASUREMENT_LATENCY_BUCKET  bucket,
	                                       double high_end)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(high_end >= 0.0);
	    bucket.high_end.SetValuePr(high_end, "High End");

	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the Low End property of the Measurement Latency Bucket.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param bucket        Pointer to the Measurement Latency Bucket.
	   * @param low_end       Low end of the bucket's range.
	   *****************************************************************************/
	  public void evel_meas_latency_bucket_low_end_set(
	                                       MEASUREMENT_LATENCY_BUCKET  bucket,
	                                       double low_end)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(low_end >= 0.0);
	    bucket.low_end.SetValuePr(low_end, "Low End");
	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Add an additional Measurement Latency Bucket to the specified event.
	   *
	   * @param measurement   Pointer to the Measurement event.
	   * @param bucket        Pointer to the Measurement Latency Bucket to add.
	   *****************************************************************************/
	  public void evel_meas_latency_bucket_add(MEASUREMENT_LATENCY_BUCKET  bucket)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_MEASUREMENT);
	    assert(bucket != null);
	    
	    if( latency_distribution == null ){
	    	latency_distribution = new ArrayList<MEASUREMENT_LATENCY_BUCKET>();
	    	LOGGER.debug("Allocate new file system usage");
	    }
	    latency_distribution.add(bucket);

	    EVEL_EXIT();
	    
	    
	  }

	  /**************************************************************************//**
	   * Add an additional Latency Distribution bucket to the Measurement.
	   *
	   * This function implements the previous API, purely for convenience.
	   *
	   * 
	   * @param low_end       Low end of the bucket's range.
	   * @param high_end      High end of the bucket's range.
	   * @param count         Count of events in this bucket.
	   *****************************************************************************/
	  public MEASUREMENT_LATENCY_BUCKET evel_measurement_latency_add(
	                                    double low_end,
	                                    double high_end,
	                                    int count)
	  {
	    MEASUREMENT_LATENCY_BUCKET bucket = null;

	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Trust the assertions in the underlying methods.                         */
	    /***************************************************************************/
	    bucket = evel_new_meas_latency_bucket(count);
	    bucket.low_end.SetValue(low_end);
	    bucket.high_end.SetValue(high_end);
	    evel_meas_latency_bucket_add(bucket);

	    EVEL_EXIT();
	    
	    return bucket;
	  }

	  /**************************************************************************//**
	   * Create a new vNIC Use to be added to a Measurement event.
	   *
	   * @note    The mandatory fields on the ::MEASUREMENT_NIC_PERFORMANCE must be supplied
	   *          to this factory function and are immutable once set. Optional
	   *          fields have explicit setter functions, but again values may only be
	   *          set once so that the ::MEASUREMENT_NIC_PERFORMANCE has immutable
	   *          properties.
	   *
	   * @param vnic_id               ASCIIZ string with the vNIC's ID.
	   * @param val_suspect           True or false confidence in data.
	   *
	   * @returns pointer to the newly manufactured ::MEASUREMENT_NIC_PERFORMANCE.
	   *          If the structure is not used it must be released using
	   *          ::evel_measurement_free_vnic_performance.
	   * @retval  null  Failed to create the vNIC Use.
	   *****************************************************************************/
	  public MEASUREMENT_NIC_PERFORMANCE evel_measurement_new_vnic_performance(String vnic_id,
	                                                        String  val_suspect)
	  {
	    MEASUREMENT_NIC_PERFORMANCE vnic_perf=null;

	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(vnic_id != null);
	   // assert(val_suspect.equals("true") || val_suspect.equals("false"));
	    

	    /***************************************************************************/
	    /* Allocate, then set Mandatory Parameters.                                */
	    /***************************************************************************/
    
	    vnic_perf = new MEASUREMENT_NIC_PERFORMANCE();
	    assert(vnic_perf != null);
	    vnic_perf.vnic_id = vnic_id;
	    vnic_perf.valuesaresuspect = val_suspect;
	    
	    //VES6.0 added field 14July
	    //vnic_perf.nicIdentifier = vnic_id;
	    
	    vnic_perf.recvd_bcast_packets_acc= new EvelOptionDouble();
	    vnic_perf.recvd_bcast_packets_delta= new EvelOptionDouble();

	    vnic_perf.recvd_discarded_packets_acc= new EvelOptionDouble();
	    vnic_perf.recvd_discarded_packets_delta= new EvelOptionDouble();
	    vnic_perf.recvd_error_packets_acc= new EvelOptionDouble();
	    vnic_perf.recvd_error_packets_delta= new EvelOptionDouble();
	    vnic_perf.recvd_mcast_packets_acc= new EvelOptionDouble();
	    vnic_perf.recvd_mcast_packets_delta= new EvelOptionDouble();
	    vnic_perf.recvd_octets_acc= new EvelOptionDouble();
	    vnic_perf.recvd_octets_delta= new EvelOptionDouble();
	    vnic_perf.recvd_total_packets_acc= new EvelOptionDouble();
	    vnic_perf.recvd_total_packets_delta= new EvelOptionDouble();
	    vnic_perf.recvd_ucast_packets_acc= new EvelOptionDouble();
	    vnic_perf.recvd_ucast_packets_delta= new EvelOptionDouble();
	    vnic_perf.tx_bcast_packets_acc= new EvelOptionDouble();
	    vnic_perf.tx_bcast_packets_delta= new EvelOptionDouble();
	    vnic_perf.tx_discarded_packets_acc= new EvelOptionDouble();
	    vnic_perf.tx_discarded_packets_delta= new EvelOptionDouble();
	    vnic_perf.tx_error_packets_acc= new EvelOptionDouble();
	    vnic_perf.tx_error_packets_delta= new EvelOptionDouble();
	    vnic_perf.tx_mcast_packets_acc= new EvelOptionDouble();
	    vnic_perf.tx_mcast_packets_delta= new EvelOptionDouble();
	    vnic_perf.tx_octets_acc= new EvelOptionDouble();
	    vnic_perf.tx_octets_delta= new EvelOptionDouble();
	    vnic_perf.tx_total_packets_acc= new EvelOptionDouble();
	    vnic_perf.tx_total_packets_delta= new EvelOptionDouble();
	    vnic_perf.tx_ucast_packets_acc= new EvelOptionDouble();
	    vnic_perf.tx_ucast_packets_delta= new EvelOptionDouble();
	    
	    
	    vnic_perf.administrativeState= new EvelOptionString();
	    vnic_perf.operationalState= new EvelOptionString();
	    vnic_perf.receivedPercentDiscard= new EvelOptionDouble();
	    vnic_perf.receivedPercentError= new EvelOptionDouble();
	    vnic_perf.receivedUtilization= new EvelOptionDouble();
	    vnic_perf.speed= new EvelOptionDouble();
	    vnic_perf.transmittedPercentDiscard= new EvelOptionDouble();
	    vnic_perf.transmittedPercentError= new EvelOptionDouble();
	    vnic_perf.transmittedUtilization= new EvelOptionDouble();
	    
        
        //assert(vnic_perf.vnic_id != null);
	    
	    if( vnic_usage == null ){
	    	vnic_usage = new ArrayList<MEASUREMENT_NIC_PERFORMANCE>();
	    	LOGGER.debug("Allocated new Vnic Perfomence");
	    }


	    vnic_usage.add(vnic_perf);
	    

	    EVEL_EXIT();

	    return vnic_perf;
	  }



	  /**************************************************************************//**
	   * Set the Accumulated Broadcast Packets Received in measurement interval
	   * property of the vNIC performance.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param vnic_performance      Pointer to the vNIC Use.
	   * @param recvd_bcast_packets_acc
	   *****************************************************************************/
	  public void evel_vnic_performance_rx_bcast_pkt_acc_set(MEASUREMENT_NIC_PERFORMANCE  vnic_performance,
	                                      double recvd_bcast_packets_acc)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(recvd_bcast_packets_acc >= 0.0);

	    vnic_performance.recvd_bcast_packets_acc.SetValuePr(
	                        recvd_bcast_packets_acc,
	                        "Broadcast Packets accumulated");

	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the Delta Broadcast Packets Received in measurement interval
	   * property of the vNIC performance.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param vnic_performance      Pointer to the vNIC Use.
	   * @param recvd_bcast_packets_delta
	   *****************************************************************************/
	  public void evel_vnic_performance_rx_bcast_pkt_delta_set(MEASUREMENT_NIC_PERFORMANCE  vnic_performance,
	                                      double recvd_bcast_packets_delta)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(recvd_bcast_packets_delta >= 0.0);

	    vnic_performance.recvd_bcast_packets_delta.SetValuePr(
	                        recvd_bcast_packets_delta,
	                        "Delta Broadcast Packets recieved");

	    EVEL_EXIT();
	  }


	  /**************************************************************************//**
	   * Set the Discarded Packets Received in measurement interval
	   * property of the vNIC performance.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param vnic_performance      Pointer to the vNIC Use.
	   * @param recvd_discard_packets_acc
	   *****************************************************************************/
	  public void evel_vnic_performance_rx_discard_pkt_acc_set(MEASUREMENT_NIC_PERFORMANCE  vnic_performance,
	                                      double recvd_discard_packets_acc)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(recvd_discard_packets_acc >= 0.0);

	    vnic_performance.recvd_discarded_packets_acc.SetValuePr(
	                        recvd_discard_packets_acc,
	                        "Discarded Packets accumulated");

	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the Delta Discarded Packets Received in measurement interval
	   * property of the vNIC performance.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param vnic_performance      Pointer to the vNIC Use.
	   * @param recvd_discard_packets_delta
	   *****************************************************************************/
	  public void evel_vnic_performance_rx_discard_pkt_delta_set(MEASUREMENT_NIC_PERFORMANCE  vnic_performance,
	                                      double recvd_discard_packets_delta)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(recvd_discard_packets_delta >= 0.0);

	    vnic_performance.recvd_discarded_packets_delta.SetValuePr(
	                        recvd_discard_packets_delta,
	                        "Delta Discarded Packets recieved");

	    EVEL_EXIT();
	  }


	  /**************************************************************************//**
	   * Set the Error Packets Received in measurement interval
	   * property of the vNIC performance.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param vnic_performance      Pointer to the vNIC Use.
	   * @param recvd_error_packets_acc
	   *****************************************************************************/
	  public void evel_vnic_performance_rx_error_pkt_acc_set(MEASUREMENT_NIC_PERFORMANCE  vnic_performance,
	                                      double recvd_error_packets_acc)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(recvd_error_packets_acc >= 0.0);

	    vnic_performance.recvd_error_packets_acc.SetValuePr(
	                        recvd_error_packets_acc,
	                        "Error Packets received accumulated");

	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the Delta Error Packets Received in measurement interval
	   * property of the vNIC performance.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param vnic_performance      Pointer to the vNIC Use.
	   * @param recvd_error_packets_delta
	   *****************************************************************************/
	  public void evel_vnic_performance_rx_error_pkt_delta_set(MEASUREMENT_NIC_PERFORMANCE  vnic_performance,
	                                      double recvd_error_packets_delta)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(recvd_error_packets_delta >= 0.0);

	    vnic_performance.recvd_error_packets_delta.SetValuePr(
	                        recvd_error_packets_delta,
	                        "Delta Error Packets recieved");

	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the Accumulated Multicast Packets Received in measurement interval
	   * property of the vNIC performance.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param vnic_performance      Pointer to the vNIC Use.
	   * @param recvd_mcast_packets_acc
	   *****************************************************************************/
	  public void evel_vnic_performance_rx_mcast_pkt_acc_set(MEASUREMENT_NIC_PERFORMANCE  vnic_performance,
	                                      double recvd_mcast_packets_acc)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(recvd_mcast_packets_acc >= 0.0);

	    vnic_performance.recvd_mcast_packets_acc.SetValuePr(
	                        recvd_mcast_packets_acc,
	                        "Multicast Packets accumulated");

	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the Delta Multicast Packets Received in measurement interval
	   * property of the vNIC performance.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param vnic_performance      Pointer to the vNIC Use.
	   * @param recvd_mcast_packets_delta
	   *****************************************************************************/
	  public void evel_vnic_performance_rx_mcast_pkt_delta_set(MEASUREMENT_NIC_PERFORMANCE  vnic_performance,
	                                      double recvd_mcast_packets_delta)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(recvd_mcast_packets_delta >= 0.0);

	    vnic_performance.recvd_mcast_packets_delta.SetValuePr(
	                        recvd_mcast_packets_delta,
	                        "Delta Multicast Packets recieved");

	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the Accumulated Octets Received in measurement interval
	   * property of the vNIC performance.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param vnic_performance      Pointer to the vNIC Use.
	   * @param recvd_octets_acc
	   *****************************************************************************/
	  public void evel_vnic_performance_rx_octets_acc_set(MEASUREMENT_NIC_PERFORMANCE  vnic_performance,
	                                      double recvd_octets_acc)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(recvd_octets_acc >= 0.0);

	    vnic_performance.recvd_octets_acc.SetValuePr(
	                        recvd_octets_acc,
	                        "Octets received accumulated");

	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the Delta Octets Received in measurement interval
	   * property of the vNIC performance.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param vnic_performance      Pointer to the vNIC Use.
	   * @param recvd_octets_delta
	   *****************************************************************************/
	  public void evel_vnic_performance_rx_octets_delta_set(MEASUREMENT_NIC_PERFORMANCE  vnic_performance,
	                                      double recvd_octets_delta)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(recvd_octets_delta >= 0.0);

	    vnic_performance.recvd_octets_delta.SetValuePr(
	                        recvd_octets_delta,
	                        "Delta Octets recieved");

	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the Accumulated Total Packets Received in measurement interval
	   * property of the vNIC performance.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param vnic_performance      Pointer to the vNIC Use.
	   * @param recvd_total_packets_acc
	   *****************************************************************************/
	  public void evel_vnic_performance_rx_total_pkt_acc_set(MEASUREMENT_NIC_PERFORMANCE  vnic_performance,
	                                      double recvd_total_packets_acc)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(recvd_total_packets_acc >= 0.0);

	    vnic_performance.recvd_total_packets_acc.SetValuePr(
	                        recvd_total_packets_acc,
	                        "Total Packets accumulated");

	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the Delta Total Packets Received in measurement interval
	   * property of the vNIC performance.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param vnic_performance      Pointer to the vNIC Use.
	   * @param recvd_total_packets_delta
	   *****************************************************************************/
	  public void evel_vnic_performance_rx_total_pkt_delta_set(MEASUREMENT_NIC_PERFORMANCE  vnic_performance,
	                                      double recvd_total_packets_delta)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(recvd_total_packets_delta >= 0.0);

	    vnic_performance.recvd_total_packets_delta.SetValuePr(
	                        recvd_total_packets_delta,
	                        "Delta Total Packets recieved");

	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the Accumulated Unicast Packets Received in measurement interval
	   * property of the vNIC performance.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param vnic_performance      Pointer to the vNIC Use.
	   * @param recvd_ucast_packets_acc
	   *****************************************************************************/
	  public void evel_vnic_performance_rx_ucast_pkt_acc_set(MEASUREMENT_NIC_PERFORMANCE  vnic_performance,
	                                      double recvd_ucast_packets_acc)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(recvd_ucast_packets_acc >= 0.0);

	    vnic_performance.recvd_ucast_packets_acc.SetValuePr(
	                        recvd_ucast_packets_acc,
	                        "Unicast Packets received accumulated");

	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the Delta Unicast packets Received in measurement interval
	   * property of the vNIC performance.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param vnic_performance      Pointer to the vNIC Use.
	   * @param recvd_ucast_packets_delta
	   *****************************************************************************/
	  public void evel_vnic_performance_rx_ucast_pkt_delta_set(MEASUREMENT_NIC_PERFORMANCE  vnic_performance,
	                                      double recvd_ucast_packets_delta)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(recvd_ucast_packets_delta >= 0.0);

	    vnic_performance.recvd_ucast_packets_delta.SetValuePr(
	                        recvd_ucast_packets_delta,
	                        "Delta Unicast packets recieved");

	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the Transmitted Broadcast Packets in measurement interval
	   * property of the vNIC performance.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param vnic_performance      Pointer to the vNIC Use.
	   * @param tx_bcast_packets_acc
	   *****************************************************************************/
	  public void evel_vnic_performance_tx_bcast_pkt_acc_set(MEASUREMENT_NIC_PERFORMANCE  vnic_performance,
	                                      double tx_bcast_packets_acc)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(tx_bcast_packets_acc >= 0.0);

	    vnic_performance.tx_bcast_packets_acc.SetValuePr(
	                        tx_bcast_packets_acc,
	                        "Transmitted Broadcast Packets accumulated");

	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the Delta Broadcast packets Transmitted in measurement interval
	   * property of the vNIC performance.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param vnic_performance      Pointer to the vNIC Use.
	   * @param tx_bcast_packets_delta
	   *****************************************************************************/
	  public void evel_vnic_performance_tx_bcast_pkt_delta_set(MEASUREMENT_NIC_PERFORMANCE  vnic_performance,
	                                      double tx_bcast_packets_delta)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(tx_bcast_packets_delta >= 0.0);

	    vnic_performance.tx_bcast_packets_delta.SetValuePr(
	                        tx_bcast_packets_delta,
	                        "Delta Transmitted Broadcast packets ");

	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the Transmitted Discarded Packets in measurement interval
	   * property of the vNIC performance.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param vnic_performance      Pointer to the vNIC Use.
	   * @param tx_discarded_packets_acc
	   *****************************************************************************/
	  public void evel_vnic_performance_tx_discarded_pkt_acc_set(MEASUREMENT_NIC_PERFORMANCE  vnic_performance,
	                                      double tx_discarded_packets_acc)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(tx_discarded_packets_acc >= 0.0);

	    vnic_performance.tx_discarded_packets_acc.SetValuePr(
	                        tx_discarded_packets_acc,
	                        "Transmitted Discarded Packets accumulated");

	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the Delta Discarded packets Transmitted in measurement interval
	   * property of the vNIC performance.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param vnic_performance      Pointer to the vNIC Use.
	   * @param tx_discarded_packets_delta
	   *****************************************************************************/
	  public void evel_vnic_performance_tx_discarded_pkt_delta_set(MEASUREMENT_NIC_PERFORMANCE  vnic_performance,
	                                      double tx_discarded_packets_delta)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(tx_discarded_packets_delta >= 0.0);

	    vnic_performance.tx_discarded_packets_delta.SetValuePr(
	                        tx_discarded_packets_delta,
	                        "Delta Transmitted Discarded packets ");

	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the Transmitted Errored Packets in measurement interval
	   * property of the vNIC performance.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param vnic_performance      Pointer to the vNIC Use.
	   * @param tx_error_packets_acc
	   *****************************************************************************/
	  public void evel_vnic_performance_tx_error_pkt_acc_set(MEASUREMENT_NIC_PERFORMANCE  vnic_performance,
	                                      double tx_error_packets_acc)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(tx_error_packets_acc >= 0.0);

	    vnic_performance.tx_error_packets_acc.SetValuePr(
	                        tx_error_packets_acc,
	                        "Transmitted Error Packets accumulated");

	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the Delta Errored packets Transmitted in measurement interval
	   * property of the vNIC performance.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param vnic_performance      Pointer to the vNIC Use.
	   * @param tx_error_packets_delta
	   *****************************************************************************/
	  public void evel_vnic_performance_tx_error_pkt_delta_set(MEASUREMENT_NIC_PERFORMANCE  vnic_performance,
	                                      double tx_error_packets_delta)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(tx_error_packets_delta >= 0.0);

	    vnic_performance.tx_error_packets_delta.SetValuePr(
	                        tx_error_packets_delta,
	                        "Delta Transmitted Error packets ");

	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the Transmitted Multicast Packets in measurement interval
	   * property of the vNIC performance.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param vnic_performance      Pointer to the vNIC Use.
	   * @param tx_mcast_packets_acc
	   *****************************************************************************/
	  public void evel_vnic_performance_tx_mcast_pkt_acc_set(MEASUREMENT_NIC_PERFORMANCE  vnic_performance,
	                                      double tx_mcast_packets_acc)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(tx_mcast_packets_acc >= 0.0);

	    vnic_performance.tx_mcast_packets_acc.SetValuePr(
	                        tx_mcast_packets_acc,
	                        "Transmitted Multicast Packets accumulated");

	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the Delta Multicast packets Transmitted in measurement interval
	   * property of the vNIC performance.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param vnic_performance      Pointer to the vNIC Use.
	   * @param tx_mcast_packets_delta
	   *****************************************************************************/
	  public void evel_vnic_performance_tx_mcast_pkt_delta_set(MEASUREMENT_NIC_PERFORMANCE  vnic_performance,
	                                      double tx_mcast_packets_delta)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(tx_mcast_packets_delta >= 0.0);

	    vnic_performance.tx_mcast_packets_delta.SetValuePr(
	                        tx_mcast_packets_delta,
	                        "Delta Transmitted Multicast packets ");

	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the Transmitted Octets in measurement interval
	   * property of the vNIC performance.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param vnic_performance      Pointer to the vNIC Use.
	   * @param tx_octets_acc
	   *****************************************************************************/
	  public void evel_vnic_performance_tx_octets_acc_set(MEASUREMENT_NIC_PERFORMANCE  vnic_performance,
	                                      double tx_octets_acc)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(tx_octets_acc >= 0.0);

	    vnic_performance.tx_octets_acc.SetValuePr(
	                        tx_octets_acc,
	                        "Transmitted Octets accumulated");

	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the Delta Octets Transmitted in measurement interval
	   * property of the vNIC performance.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param vnic_performance      Pointer to the vNIC Use.
	   * @param tx_octets_delta
	   *****************************************************************************/
	  public void evel_vnic_performance_tx_octets_delta_set(MEASUREMENT_NIC_PERFORMANCE  vnic_performance,
	                                      double tx_octets_delta)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(tx_octets_delta >= 0.0);

	    vnic_performance.tx_octets_delta.SetValuePr(
	                        tx_octets_delta,
	                        "Delta Transmitted Octets ");

	    EVEL_EXIT();
	  }


	  /**************************************************************************//**
	   * Set the Transmitted Total Packets in measurement interval
	   * property of the vNIC performance.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param vnic_performance      Pointer to the vNIC Use.
	   * @param tx_total_packets_acc
	   *****************************************************************************/
	  public void evel_vnic_performance_tx_total_pkt_acc_set(MEASUREMENT_NIC_PERFORMANCE  vnic_performance,
	                                      double tx_total_packets_acc)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(tx_total_packets_acc >= 0.0);

	    vnic_performance.tx_total_packets_acc.SetValuePr(
	                        tx_total_packets_acc,
	                        "Transmitted Total Packets accumulated");

	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the Delta Total Packets Transmitted in measurement interval
	   * property of the vNIC performance.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param vnic_performance      Pointer to the vNIC Use.
	   * @param tx_total_packets_delta
	   *****************************************************************************/
	  public void evel_vnic_performance_tx_total_pkt_delta_set(MEASUREMENT_NIC_PERFORMANCE  vnic_performance,
	                                      double tx_total_packets_delta)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(tx_total_packets_delta >= 0.0);

	    vnic_performance.tx_total_packets_delta.SetValuePr(
	                        tx_total_packets_delta,
	                        "Delta Transmitted Total Packets ");

	    EVEL_EXIT();
	  }


	  /**************************************************************************//**
	   * Set the Transmitted Unicast Packets in measurement interval
	   * property of the vNIC performance.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param vnic_performance      Pointer to the vNIC Use.
	   * @param tx_ucast_packets_acc
	   *****************************************************************************/
	  public void evel_vnic_performance_tx_ucast_pkt_acc_set(MEASUREMENT_NIC_PERFORMANCE  vnic_performance,
	                                      double tx_ucast_packets_acc)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(tx_ucast_packets_acc >= 0.0);

	    vnic_performance.tx_ucast_packets_acc.SetValuePr(
	                        tx_ucast_packets_acc,
	                        "Transmitted Unicast Packets accumulated");

	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Set the Delta Octets Transmitted in measurement interval
	   * property of the vNIC performance.
	   *
	   * @note  The property is treated as immutable: it is only valid to call
	   *        the setter once.  However, we don't assert if the caller tries to
	   *        overwrite, just ignoring the update instead.
	   *
	   * @param vnic_performance      Pointer to the vNIC Use.
	   * @param tx_ucast_packets_delta
	   *****************************************************************************/
	  public void evel_vnic_performance_tx_ucast_pkt_delta_set(MEASUREMENT_NIC_PERFORMANCE  vnic_performance,
	                                      double tx_ucast_packets_delta)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(tx_ucast_packets_delta >= 0.0);

	    vnic_performance.tx_ucast_packets_delta.SetValuePr(
	                        tx_ucast_packets_delta,
	                        "Delta Transmitted Unicast Packets ");

	    EVEL_EXIT();
	  }
	  
	  /*
	   * VES6.0 UPDATE 19JULY
	   */
	  
	  public void evel_vnic_performance_administrativeState_set(MEASUREMENT_NIC_PERFORMANCE  vnic_performance,
              String administrativeState)
	  {
		  EVEL_ENTER();

		/***************************************************************************/
		/* Check preconditions.                                                    */
		/***************************************************************************/
		assert(administrativeState != null);
		
		vnic_performance.administrativeState.SetValuePr(
				administrativeState,"Administrative State");

		EVEL_EXIT();
	  }
	  
	  
	  
	  public void evel_vnic_performance_operationalState_set(MEASUREMENT_NIC_PERFORMANCE  vnic_performance,
              String operationalState)
	  {
		  EVEL_ENTER();

		/***************************************************************************/
		/* Check preconditions.                                                    */
		/***************************************************************************/
		assert(operationalState != null);
		
		vnic_performance.operationalState.SetValuePr(
				operationalState,"operational State");

		EVEL_EXIT();
	  }
	  
	  public void evel_vnic_performance_receivedPercentDiscard_set(MEASUREMENT_NIC_PERFORMANCE  vnic_performance,
              double receivedPercentDiscard)
	  {
		  EVEL_ENTER();

		/***************************************************************************/
		/* Check preconditions.                                                    */
		/***************************************************************************/
		assert(receivedPercentDiscard >= 0.0);
		
		vnic_performance.receivedPercentDiscard.SetValuePr(
				receivedPercentDiscard,"Received Percent Discard");

		EVEL_EXIT();
	  }
	  
	  public void evel_vnic_performance_receivedPercentError_set(MEASUREMENT_NIC_PERFORMANCE  vnic_performance,
              double receivedPercentError)
	  {
		  EVEL_ENTER();

		/***************************************************************************/
		/* Check preconditions.                                                    */
		/***************************************************************************/
		assert(receivedPercentError >= 0.0);
		
		vnic_performance.receivedPercentError.SetValuePr(
				receivedPercentError,"Received Percent Error");

		EVEL_EXIT();
	  }
	  
	  public void evel_vnic_performance_receivedUtilization_set(MEASUREMENT_NIC_PERFORMANCE  vnic_performance,
              double receivedUtilization)
	  {
		  EVEL_ENTER();

		/***************************************************************************/
		/* Check preconditions.                                                    */
		/***************************************************************************/
		assert(receivedUtilization >= 0.0);
		
		vnic_performance.receivedUtilization.SetValuePr(
				receivedUtilization,"Received Utilization");

		EVEL_EXIT();
	  }
	  
	  public void evel_vnic_performance_speed_set(MEASUREMENT_NIC_PERFORMANCE  vnic_performance,
              double speed)
	  {
		  EVEL_ENTER();

		/***************************************************************************/
		/* Check preconditions.                                                    */
		/***************************************************************************/
		assert(speed >= 0.0);
		
		vnic_performance.speed.SetValuePr(speed, "Speed");
				

		EVEL_EXIT();
	  }
	  
	  public void evel_vnic_performance_transmittedPercentDiscard_set(MEASUREMENT_NIC_PERFORMANCE  vnic_performance,
              double transmittedPercentDiscard)
	  {
		  EVEL_ENTER();

		/***************************************************************************/
		/* Check preconditions.                                                    */
		/***************************************************************************/
		assert(transmittedPercentDiscard >= 0.0);
		
		vnic_performance.transmittedPercentDiscard.SetValuePr(
				transmittedPercentDiscard,"Transmitted Percent Discard");

		EVEL_EXIT();
	  }
	  
	  public void evel_vnic_performance_transmittedPercentError_set(MEASUREMENT_NIC_PERFORMANCE  vnic_performance,
              double transmittedPercentError)
	  {
		  EVEL_ENTER();

		/***************************************************************************/
		/* Check preconditions.                                                    */
		/***************************************************************************/
		  assert(transmittedPercentError >= 0.0);
		
		vnic_performance.transmittedPercentError.SetValuePr(
				transmittedPercentError,"Transmitted Percent Error");

		EVEL_EXIT();
	  }
	  
	  public void evel_vnic_performance_transmittedUtilization_set(MEASUREMENT_NIC_PERFORMANCE  vnic_performance,
              double transmittedUtilization)
	  {
		  EVEL_ENTER();

		/***************************************************************************/
		/* Check preconditions.                                                    */
		/***************************************************************************/
		  assert(transmittedUtilization >= 0.0);
		
		vnic_performance.transmittedUtilization.SetValuePr(
				transmittedUtilization,"transmittedUtilization");

		EVEL_EXIT();
	  }
	  
	  
	  


	  /**************************************************************************//**
	   * Add an additional vNIC Use to the specified Measurement event.
	   *
	   * 
	   * @param vnic_performance      Pointer to the vNIC Use to add.
	   *****************************************************************************/
	  public void evel_meas_vnic_performance_add(
	                              MEASUREMENT_NIC_PERFORMANCE  vnic_performance)
	  {
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/

	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_MEASUREMENT);
	    assert(vnic_performance != null);
	    
	    if( vnic_usage == null ){
	    	vnic_usage = new ArrayList<MEASUREMENT_NIC_PERFORMANCE>();
	    	LOGGER.debug("Allocate new file system usage");
	    }

	    vnic_usage.add(vnic_performance);
	   

	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Add an additional vNIC usage record Measurement.
	   *
	   * This function implements the previous API, purely for convenience.
	   *
	   * The ID is null delimited ASCII string.  The library takes a copy so the
	   * caller does not have to preserve values after the function returns.
	   *
	   * @param measurement           Pointer to the measurement.
	   * @param vnic_id               ASCIIZ string with the vNIC's ID.
	   * @param valset                true or false confidence level
	   * @param recvd_bcast_packets_acc         Recieved broadcast packets
	   * @param recvd_bcast_packets_delta       Received delta broadcast packets
	   * @param recvd_discarded_packets_acc     Recieved discarded packets
	   * @param recvd_discarded_packets_delta   Received discarded delta packets
	   * @param recvd_error_packets_acc         Received error packets
	   * @param recvd_error_packets_delta,      Received delta error packets
	   * @param recvd_mcast_packets_acc         Received multicast packets
	   * @param recvd_mcast_packets_delta       Received delta multicast packets
	   * @param recvd_octets_acc                Received octets
	   * @param recvd_octets_delta              Received delta octets
	   * @param recvd_total_packets_acc         Received total packets
	   * @param recvd_total_packets_delta       Received delta total packets
	   * @param recvd_ucast_packets_acc         Received Unicast packets
	   * @param recvd_ucast_packets_delta       Received delta unicast packets
	   * @param tx_bcast_packets_acc            Transmitted broadcast packets
	   * @param tx_bcast_packets_delta          Transmitted delta broadcast packets
	   * @param tx_discarded_packets_acc        Transmitted packets discarded
	   * @param tx_discarded_packets_delta      Transmitted delta discarded packets
	   * @param tx_error_packets_acc            Transmitted error packets
	   * @param tx_error_packets_delta          Transmitted delta error packets
	   * @param tx_mcast_packets_acc            Transmitted multicast packets accumulated
	   * @param tx_mcast_packets_delta          Transmitted delta multicast packets
	   * @param tx_octets_acc                   Transmitted octets
	   * @param tx_octets_delta                 Transmitted delta octets
	   * @param tx_total_packets_acc            Transmitted total packets
	   * @param tx_total_packets_delta          Transmitted delta total packets
	   * @param tx_ucast_packets_acc            Transmitted Unicast packets
	   * @param tx_ucast_packets_delta          Transmitted delta Unicast packets
	   *****************************************************************************/
	  public void evel_measurement_vnic_performance_add(
	                                 String  vnic_id,
	                                 String valset,
	                                 //VES6.0 added field 14July
	                                 //String nicIdentifier,
	                                 double speed,
	                                 double recvd_bcast_packets_acc,
	                                 double recvd_bcast_packets_delta,
	                                 double recvd_discarded_packets_acc,
	                                 double recvd_discarded_packets_delta,
	                                 double recvd_error_packets_acc,
	                                 double recvd_error_packets_delta,
	                                 double recvd_mcast_packets_acc,
	                                 double recvd_mcast_packets_delta,
	                                 double recvd_octets_acc,
	                                 double recvd_octets_delta,
	                                 double recvd_total_packets_acc,
	                                 double recvd_total_packets_delta,
	                                 double recvd_ucast_packets_acc,
	                                 double recvd_ucast_packets_delta,
	                                 double tx_bcast_packets_acc,
	                                 double tx_bcast_packets_delta,
	                                 double tx_discarded_packets_acc,
	                                 double tx_discarded_packets_delta,
	                                 double tx_error_packets_acc,
	                                 double tx_error_packets_delta,
	                                 double tx_mcast_packets_acc,
	                                 double tx_mcast_packets_delta,
	                                 double tx_octets_acc,
	                                 double tx_octets_delta,
	                                 double tx_total_packets_acc,
	                                 double tx_total_packets_delta,
	                                 double tx_ucast_packets_acc,
	                                 double tx_ucast_packets_delta,
	                                 //VES6.0 addded fileds 19July
	                                 String administrativeState,
	                                 String operationalState, 
	                                 double receivedPercentDiscard,
	                                 double receivedPercentError,
	                                 double receivedUtilization,
	                                 
	                                 double transmittedPercentDiscard,
	                                 double transmittedPercentError,
	                                 double transmittedUtilization
			  )
	  {
	    MEASUREMENT_NIC_PERFORMANCE vnic_performance = null;
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Trust the assertions in the underlying methods.                         */
	    /***************************************************************************/
	    //VES6.0 added field 14July
	    vnic_performance = evel_measurement_new_vnic_performance(vnic_id, valset);
	                                             
	    evel_vnic_performance_rx_bcast_pkt_acc_set(vnic_performance, recvd_bcast_packets_acc);
	    evel_vnic_performance_rx_bcast_pkt_delta_set(vnic_performance, recvd_bcast_packets_delta);
	    evel_vnic_performance_rx_discard_pkt_acc_set(vnic_performance, recvd_discarded_packets_acc);
	    evel_vnic_performance_rx_discard_pkt_delta_set(vnic_performance, recvd_discarded_packets_delta);
	    evel_vnic_performance_rx_error_pkt_acc_set(vnic_performance, recvd_error_packets_acc);
	    evel_vnic_performance_rx_error_pkt_delta_set(vnic_performance, recvd_error_packets_delta);
	    evel_vnic_performance_rx_mcast_pkt_acc_set(vnic_performance, recvd_mcast_packets_acc);
	    evel_vnic_performance_rx_mcast_pkt_delta_set(vnic_performance, recvd_mcast_packets_delta);
	    evel_vnic_performance_rx_octets_acc_set(vnic_performance, recvd_octets_acc);
	    evel_vnic_performance_rx_octets_delta_set(vnic_performance, recvd_octets_delta);
	    evel_vnic_performance_rx_total_pkt_acc_set(vnic_performance, recvd_total_packets_acc);
	    evel_vnic_performance_rx_total_pkt_delta_set(vnic_performance, recvd_total_packets_delta);
	    evel_vnic_performance_rx_ucast_pkt_acc_set(vnic_performance, recvd_ucast_packets_acc);
	    evel_vnic_performance_rx_ucast_pkt_delta_set(vnic_performance, recvd_ucast_packets_delta);
	    evel_vnic_performance_tx_bcast_pkt_acc_set(vnic_performance, tx_bcast_packets_acc);
	    evel_vnic_performance_tx_bcast_pkt_delta_set(vnic_performance, tx_bcast_packets_delta);
	    evel_vnic_performance_tx_discarded_pkt_acc_set(vnic_performance, tx_discarded_packets_acc);
	    evel_vnic_performance_tx_discarded_pkt_delta_set(vnic_performance, tx_discarded_packets_delta);
	    evel_vnic_performance_tx_error_pkt_acc_set(vnic_performance, tx_error_packets_acc);
	    evel_vnic_performance_tx_error_pkt_delta_set(vnic_performance, tx_error_packets_delta);
	    evel_vnic_performance_tx_mcast_pkt_acc_set(vnic_performance, tx_mcast_packets_acc);
	    evel_vnic_performance_tx_mcast_pkt_delta_set(vnic_performance, tx_mcast_packets_delta);
	    evel_vnic_performance_tx_octets_acc_set(vnic_performance, tx_octets_acc);
	    evel_vnic_performance_tx_octets_delta_set(vnic_performance, tx_octets_delta);
	    evel_vnic_performance_tx_total_pkt_acc_set(vnic_performance, tx_total_packets_acc);
	    evel_vnic_performance_tx_total_pkt_delta_set(vnic_performance, tx_total_packets_delta);
	    evel_vnic_performance_tx_ucast_pkt_acc_set(vnic_performance, tx_ucast_packets_acc);
	    evel_vnic_performance_tx_ucast_pkt_delta_set(vnic_performance, tx_ucast_packets_delta);
	    
	    //VES6.0 added fields 19July
	    
	    evel_vnic_performance_administrativeState_set(vnic_performance, administrativeState);
	    evel_vnic_performance_operationalState_set(vnic_performance, operationalState);
	    evel_vnic_performance_receivedPercentDiscard_set(vnic_performance, receivedPercentDiscard);
	    evel_vnic_performance_receivedPercentError_set(vnic_performance, receivedPercentError);
	    evel_vnic_performance_receivedUtilization_set(vnic_performance, receivedUtilization);
	    evel_vnic_performance_speed_set(vnic_performance, speed);
	    evel_vnic_performance_transmittedPercentDiscard_set(vnic_performance, transmittedPercentDiscard);
	    evel_vnic_performance_transmittedPercentError_set(vnic_performance, transmittedPercentError);
	    evel_vnic_performance_transmittedUtilization_set(vnic_performance, transmittedUtilization);
	    
	    
	    
	    
	    if( vnic_usage == null ){
	    	vnic_usage = new ArrayList<MEASUREMENT_NIC_PERFORMANCE>();
	    	LOGGER.debug("Allocate new file system usage");
	    }
	    
	    vnic_usage.add(vnic_performance);
	  }
	  
	  /**************************************************************************//**
	   * Add a json object to jsonObject list.
	   *
	   * The name and value are null delimited ASCII strings.  The library takes
	   * a copy so the caller does not have to preserve values after the function
	   * returns.
	   *
	   * @param jsonobj   Pointer to json object
	   *****************************************************************************/
	  public  void evel_measurement_add_jsonobj(javax.json.JsonObject  jsonobj)
	  {

	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_MEASUREMENT);
	    assert(jsonobj != null);

	    LOGGER.debug("Adding jsonObject");
	    
	    if( additional_objects == null )
	    	additional_objects = new ArrayList<javax.json.JsonObject>();
	    
	    additional_objects.add(jsonobj);

	    EVEL_EXIT();
	  }

	  /**************************************************************************//**
	   * Encode Scaling Measurement Object according to VES schema
	   *
	   * @retval JSON Object of Scaling Measurement event
	   *****************************************************************************/
	@SuppressWarnings("null")
	JsonObjectBuilder evelScalingMeasurementObject()
	  {
	    MEASUREMENT_CPU_USE cpu_use = null;
	    MEASUREMENT_MEM_USE mem_use = null;
	    MEASUREMENT_DISK_USE disk_use = null;
	    MEASUREMENT_FSYS_USE fsys_use = null;
	    MEASUREMENT_LATENCY_BUCKET bucket = null;
	    MEASUREMENT_NIC_PERFORMANCE nic_use = null;
	    MEASUREMENT_FEATURE_USE feature_use = null;
	    MEASUREMENT_CODEC_USE codec_use = null;
	    MEASUREMENT_GROUP meas_group = null;
	    CUSTOM_MEASUREMENT custom_meas = null;
	    
	    MEASUREMENT_IPMI ipmij = null;
	    MEASUREMENT_LOAD load = null;
	    MEASUREMENT_PROCESS_STATS process_stats = null;
	    MACHINE_CHECK_EXCEPTION check_exception = null;
	    
	    MEASUREMENT_HUGE_PAGE hugePage = null;
	    
	    
	    MEASUREMENT_IPMI_PROCESSOR ipmiProcessorJson = null;
	    IPMIglobalAggregateTemperatureMargin ipmiGlobalAggTempMarginJson;
	    Processor_DIMMaggregate_Thermal_Margin ipmiProcessorDIMMagregatejson = null;
	    IPMIpowerSupply ipmiPowerSupplyJson;
	    IPMIbattery ipmiBatteryJson;
	    IPMINIC ipmiNicJson;
	    IPMIHSBP ipmiHsbpJson;
	    IPMIbaseboardTemperature ipmiBaseBoardTempJson;
	    IPMIbaseboardvoltageResulator ipmiBaseboardVoltageResultatorJson;
	    IPMIfan ipmifanjson;
//	    double version = major_version+(double)minor_version/10;
        String version = "4.0";
	    EVEL_ENTER();

	    /***************************************************************************/
	    /* Check preconditions.                                                    */
	    /***************************************************************************/
	    assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_MEASUREMENT);

	    /***************************************************************************/
	    /* Mandatory fields.                                                       */
	    /***************************************************************************/
	    JsonObjectBuilder evelmeasmt = Json.createObjectBuilder()
	   	                          .add("measurementInterval", measurement_interval);

	    /***************************************************************************/
	    /* Optional fields.                                                        */
	    /***************************************************************************/
	    
		  if(additional_inf != null) {
			  JsonObjectBuilder builder = Json.createObjectBuilder();
			  //JsonArrayBuilder builder = Json.createArrayBuilder();
			  Iterator<Entry<String, String>> it = additional_inf.entrySet().iterator();
			  while(it.hasNext()) {
				  Map.Entry<String, String> add_inf = (Map.Entry<String, String>)it.next();
				  String addl_info_key = add_inf.getKey();
				  String addl_info_value = add_inf.getValue();
				  builder.add(addl_info_key, addl_info_value);
			  }
			  evelmeasmt.add("additionalFields", builder);
		  }

	    // TBD additional json objects
		if( concurrent_sessions.is_set )
			evelmeasmt.add("concurrentSessions", concurrent_sessions.GetValue());
		if( configured_entities.is_set )
			evelmeasmt.add("configuredEntities", configured_entities.GetValue());
		/*******************************************************************************
		 * MEASUREMENT Load
		 *******************************************************************************/
		 if(loads != null && loads.size() >0) {
			 JsonArrayBuilder builder = Json.createArrayBuilder();
			 for(int i=0;i<loads.size();i++) {
				 load = loads.get(i);
				 JsonObjectBuilder obj = Json.createObjectBuilder();
		//				 .add("loadIdentifier", load.loadIdentifier);
				 load.longTerm.encJsonValue(obj,"longTerm");
				 load.midTerm.encJsonValue(obj,"midTerm");
				 load.shortTerm.encJsonValue(obj,"shortTerm");
				 builder.add(obj.build());
				 
			 }
			 evelmeasmt.add("loadArray", builder);
		 }
		 
		 /***************************************************************************/
		 /* process_stats       */
		 /***************************************************************************/
		 if(this.process_stats!=null && this.process_stats.size()>0) {
			 
			 JsonArrayBuilder builder = Json.createArrayBuilder();
			 for(int i=0;i<this.process_stats.size();i++) {
				 process_stats = this.process_stats.get(i);
				 JsonObjectBuilder obj = Json.createObjectBuilder()
						 				.add("processIdentifier", process_stats.processIdentifier);
				 process_stats.forkRate.encJsonValue(obj, "forkRate");
				 process_stats.psStateBlocked.encJsonValue(obj, "psStateBlocked");
				 process_stats.psStatePaging.encJsonValue(obj, "psStatePaging");
				 process_stats.psStateRunning.encJsonValue(obj, "psStateRunning");
				 process_stats.psStateSleeping.encJsonValue(obj, "psStateSleeping");
				 process_stats.psStateStopped.encJsonValue(obj, "psStateStopped");
				 process_stats.psStateZombie.encJsonValue(obj, "psStateZombie");
				 
				 builder.add(obj.build());
				 
				 
				 
			 }
			 evelmeasmt.add("processStatsArray", builder); 
		 }
		 
		 /***************************************************************************/
		 /* MACHINE_Check_Exception       */
		 /***************************************************************************/
		 if( machineCheckException != null && machineCheckException.size()>0) {
			 JsonArrayBuilder builder = Json.createArrayBuilder();
			 for(int i=0;i<machineCheckException.size();i++) {
				 check_exception = machineCheckException.get(i);
				 JsonObjectBuilder obj = Json.createObjectBuilder()
	                      .add( "vmIdentifier", check_exception.processIdentifier);
				 check_exception.correctedMemoryErrors.encJsonValue(obj, "correctedMemoryErrors");
				 check_exception.correctedMemoryErrors_In1Hr.encJsonValue(obj, "correctedMemoryErrorsIn1Hr");
				 check_exception.uncorrectedMemoryErrors.encJsonValue(obj, "uncorrectedMemoryErrors");
				 check_exception.uncorrectedMemoryErrors_In1Hr.encJsonValue(obj, "uncorrectedMemoryErrorsIn1Hr");
				 
				 builder.add(obj.build());
				 
			 }
			 evelmeasmt.add("machineCheckExceptionArray", builder);
		 }
		 
		 
		 /***************************************************************************/
		 /* MACHINE_Check_Exception       */
		 /***************************************************************************/
		 if( huge_pages != null && huge_pages.size()>0) { 
			 JsonArrayBuilder builder = Json.createArrayBuilder();
			 for(int i=0;i<huge_pages.size();i++) {
				 hugePage = huge_pages.get(i);
				 JsonObjectBuilder obj = Json.createObjectBuilder();
				 obj.add( "hugePagesIdentifier", hugePage.hugePagesIdentifier);
				 obj.add( "bytesUsed", hugePage.bytesUsed);			
				 
				
				 
				 obj.add("bytesFree", hugePage.bytesFree.value);
				 obj.add("vmPageNumberUsed", hugePage.vmPageNumberUsed.value);
				 obj.add( "vmPageNumberFree", hugePage.vmPageNumberFree.value);
				 obj.add( "percentUsed", hugePage.percentUsed.value);
				 obj.add( "percentFree", hugePage.percentFree.value);
				 
				 
				 builder.add(obj.build());
				 
			 }
			 evelmeasmt.add("hugePagesArray", builder);
		 }
		 
	    /***************************************************************************/
	    /* CPU Use list.                                                           */
	    /***************************************************************************/
		  if( cpu_usage != null && cpu_usage.size() > 0 )
		  {
		    JsonArrayBuilder builder = Json.createArrayBuilder();
		    for(int i=0;i<cpu_usage.size();i++) {
			  cpu_use = cpu_usage.get(i);
			  JsonObjectBuilder obj = Json.createObjectBuilder()
			                      .add( "cpuIdentifier", cpu_use.id)
			                      .add( "percentUsage",cpu_use.usage);
			  
			  cpu_use.idle.encJsonValue(obj,"cpuIdle");
			  cpu_use.intrpt.encJsonValue(obj,"cpuUsageInterrupt");
			  cpu_use.nice.encJsonValue(obj,"cpuUsageNice");
			  cpu_use.softirq.encJsonValue(obj,"cpuUsageSoftIrq");
			  cpu_use.steal.encJsonValue(obj,"cpuUsageSteal");
			  cpu_use.sys.encJsonValue(obj,"cpuUsageSystem");
			  cpu_use.user.encJsonValue(obj,"cpuUsageUser");
			  cpu_use.wait.encJsonValue(obj,"cpuWait");	
			  /*********************
			   * VES6.0 added fields 14/07/2018
			   */
			  cpu_use.cpuCapacityContention.encJsonValue(obj,"cpuCapacityContention");
			  cpu_use.cpuDemandAvg.encJsonValue(obj,"cpuDemandAvg");
			  cpu_use.cpuDemandMhz.encJsonValue(obj,"cpuDemandMhz");
			  cpu_use.cpuDemandPct.encJsonValue(obj,"cpuDemandPct");
			  cpu_use.cpuLatencyAvg.encJsonValue(obj,"cpuLatencyAvg");
			  cpu_use.cpuOverheadAvg.encJsonValue(obj,"cpuOverheadAvg");
			  cpu_use.cpuSwapWaitTime.encJsonValue(obj,"cpuSwapWaitTime");
			  builder.add(obj.build());
		    }
			evelmeasmt.add("cpuUsageArray", builder);
		  }
		
		  if(ipmis != null && ipmis.size() > 0) {
			  JsonObjectBuilder builder1 = Json.createObjectBuilder();
			 JsonArrayBuilder builder = Json.createArrayBuilder();
			  
			  for(int i=0;i<ipmis.size();i++) {
				  ipmij = ipmis.get(i);
				//  JsonObjectBuilder obj= null;
				  
				  builder1.add("exitAirTemperature", ipmij.exitAirTemperature.GetValue().doubleValue());
				  builder1.add("frontPanelTemperature", ipmij.frontPanelTemperature.GetValue().doubleValue());
				  builder1.add("ioModuleTemperature", ipmij.ioModuleTemperature.GetValue().doubleValue());
				  builder1.add("systemAirflow", ipmij.systemAirflow.GetValue().doubleValue());
				  
				  
				  
				  /*JsonObjectBuilder obj = Json.createObjectBuilder();
				  ipmij.exitAirTemperature.encJsonValue(obj, "exitAirTemperature");
				  ipmij.frontPanelTemperature.encJsonValue(obj, "frontPanelTemperature");
				  ipmij.ioModuleTemperature.encJsonValue(obj, "ioModuleTemperature");
				  ipmij.systemAirflow.encJsonValue(obj, "systemAirflow"); */
				  
				  
				  
				  


				  
				  if(ipmij.ipmiprocessor != null && ipmij.ipmiprocessor.size() > 0 ) {
					  JsonArrayBuilder ipmi_processor_builder = Json.createArrayBuilder();
					  for(int j=0; j<ipmij.ipmiprocessor.size();j++) {
						  ipmiProcessorJson = ipmij.ipmiprocessor.get(j);
						  JsonObjectBuilder obj1 = Json.createObjectBuilder().add("processorIdentifier", ipmiProcessorJson.processorIdentifier);
						  ipmiProcessorJson.processorDtsThermalMargin.encJsonValue(obj1 , "processorDtsThermalMargin");
						  ipmiProcessorJson.processorThermalControlPercent.encJsonValue(obj1, "processorThermalControlPercent");
						  if(ipmiProcessorJson.processorDIMMaggregateThermalMargin != null && 
								  ipmiProcessorJson.processorDIMMaggregateThermalMargin.size() > 0) {
							  JsonArrayBuilder ipmi_procesor_DTS_thermal_margin = Json.createArrayBuilder();
							  for( int k=0 ;k<ipmiProcessorJson.processorDIMMaggregateThermalMargin.size();k++) {
								  
								  ipmiProcessorDIMMagregatejson = ipmiProcessorJson.processorDIMMaggregateThermalMargin.get(k);
								  JsonObjectBuilder obj2 = Json.createObjectBuilder().add("processorDimmAggregateThermalMarginIdentifier", ipmiProcessorDIMMagregatejson.processorDIMMaggregateThermalMarginIdentifier)
										  .add("thermalMargin", ipmiProcessorDIMMagregatejson.thermalMargin);
								
								  ipmi_procesor_DTS_thermal_margin.add(obj2.build()); 
							  }
							  obj1.add("processorDimmAggregateThermalMarginArray", ipmi_procesor_DTS_thermal_margin );
						  
						  }
						  
						  ipmi_processor_builder.add(obj1.build());
						  					  
					  }
					//  obj.add("ipmiProcessorArray", ipmi_processor_builder);
					  builder1.add("ipmiProcessorArray", ipmi_processor_builder);
				  }
				  
				  
				  if(ipmij.ipmiglobalAggregateTemperatureMarginArray != null &&
						  ipmij.ipmiglobalAggregateTemperatureMarginArray.size()>0) {
					  
					  JsonArrayBuilder ipmi_global_aggregate_tepmerature_margin_array = Json.createArrayBuilder();
					  for(int j=0; j<ipmij.ipmiglobalAggregateTemperatureMarginArray.size();j++) {
						  ipmiGlobalAggTempMarginJson = ipmij.ipmiglobalAggregateTemperatureMarginArray.get(j);
						  JsonObjectBuilder obj1 = Json.createObjectBuilder().add("globalAggregateTemperatureMarginIdentifier", ipmiGlobalAggTempMarginJson.globalAggregateTemperatureMarginIdentifier);
						  ipmiGlobalAggTempMarginJson.globalAggregateTemeratureMargin.encJsonValue(obj1, "globalAggregateTemperatureMargin");
						  
						  ipmi_global_aggregate_tepmerature_margin_array.add(obj1.build());
					  }
					  
					//  obj.add("globalAggregateTemperatureMarginArray", ipmi_global_aggregate_tepmerature_margin_array );
					  builder1.add("ipmiGlobalAggregateTemperatureMarginArray", ipmi_global_aggregate_tepmerature_margin_array);
				  }
				  
				  
				  
				  if(ipmij.ipmipowerSupply != null &&
						  ipmij.ipmipowerSupply.size()>0) {
					  
					  JsonArrayBuilder ipmi_power_supply_array = Json.createArrayBuilder();
					  for(int j=0; j<ipmij.ipmipowerSupply.size();j++) {
						  ipmiPowerSupplyJson = ipmij.ipmipowerSupply.get(j);
						  JsonObjectBuilder obj1 = Json.createObjectBuilder().add("powerSupplyIdentifier", ipmiPowerSupplyJson.powerSupplyIdentifier);
						  ipmiPowerSupplyJson.powerSupplycurrentOutputPercent.encJsonValue(obj1, "powerSupplyCurrentOutputPercent");
						  ipmiPowerSupplyJson.powerSupplyInputPower.encJsonValue(obj1, "powerSupplyInputPower");
						  ipmiPowerSupplyJson.powerSupplyTemperature.encJsonValue(obj1, "powerSupplyTemperature");
						  
						  ipmi_power_supply_array.add(obj1.build());
					  }
					  
					 // obj.add("ipmiPowerSupplyArray", ipmi_power_supply_array );
					  builder1.add("ipmiPowerSupplyArray", ipmi_power_supply_array);
				  }
				  
				  if(ipmij.ipmibattery != null && ipmij.ipmibattery.size()>0) {
					  
					  JsonArrayBuilder ipmi_battery_array = Json.createArrayBuilder();
					  for(int j=0; j<ipmij.ipmibattery.size();j++) {
						  ipmiBatteryJson = ipmij.ipmibattery.get(j);
						  JsonObjectBuilder obj1 = Json.createObjectBuilder().add("batteryIdentifier", ipmiBatteryJson.batteryIdentifier);
						  ipmiBatteryJson.batteryType.encJsonValue(obj1, "batteryType");
						  ipmiBatteryJson.batteryVoltageLevel.encJsonValue(obj1, "batteryVoltageLevel");
						  
						  
						  ipmi_battery_array.add(obj1.build());
					  }
					  
					//  obj.add("ipmiBatteryArray", ipmi_battery_array );
					  builder1.add("ipmiBatteryArray", ipmi_battery_array);
					   
					  
				  }
				  
				  
				  if(ipmij.ipmiNIC != null && ipmij.ipmiNIC.size()>0) {
					  
					  JsonArrayBuilder ipmi_Nic_array = Json.createArrayBuilder();
					  for(int j=0; j<ipmij.ipmiNIC.size();j++) {
						  ipmiNicJson = ipmij.ipmiNIC.get(j);
						  JsonObjectBuilder obj1 = Json.createObjectBuilder().add("nicIdentifier", ipmiNicJson.nicIdentifier);
						  ipmiNicJson.nicTemperature.encJsonValue(obj1, "nicTemperature");
						  
						  
						  
						  
						  ipmi_Nic_array.add(obj1.build());
					  }
					  
				//  obj.add("ipmiNicArray", ipmi_Nic_array );
					  builder1.add("ipmiNicArray", ipmi_Nic_array);
					  
				  }
				  if(ipmij.ipmiHSBP != null && ipmij.ipmiHSBP.size()>0) {
					  
					  JsonArrayBuilder ipmi_HSBP_array = Json.createArrayBuilder();
					  for(int j=0; j<ipmij.ipmiHSBP.size();j++) {
						  ipmiHsbpJson = ipmij.ipmiHSBP.get(j);
						  JsonObjectBuilder obj1 = Json.createObjectBuilder().add("hsbpIdentifier", ipmiHsbpJson.hsbpIdentifier);
						  ipmiHsbpJson.hsbpTemperature.encJsonValue(obj1, "hsbpTemperature");
						  
						  
						  
						  ipmi_HSBP_array.add(obj1.build());
					  }
					  
				//	  obj.add("ipmiHsbpArray", ipmi_HSBP_array );
					  builder1.add("ipmiHsbpArray", ipmi_HSBP_array);
					  
				  }
				  
				  
				  if(ipmij.ipmibaseboardTemperature!= null && ipmij.ipmibaseboardTemperature.size()>0) {
					  
					  JsonArrayBuilder ipmi_baseboard_Temperature_array = Json.createArrayBuilder();
					  for(int j=0; j<ipmij.ipmibaseboardTemperature.size();j++) {
						  ipmiBaseBoardTempJson = ipmij.ipmibaseboardTemperature.get(j);
						  JsonObjectBuilder obj1 = Json.createObjectBuilder().add("baseboardTemperatureIdentifier", ipmiBaseBoardTempJson.baseboardTemperatureIdentifier);
						  ipmiBaseBoardTempJson.baseboardTemperature.encJsonValue(obj1, "baseboardTemperature");
						  
						  
						  
						  ipmi_baseboard_Temperature_array.add(obj1.build());
					  }
					  
					//  obj.add("ipmiBaseboardTemperatureArray", ipmi_baseboard_Temperature_array );
					  builder1.add("ipmiBaseboardTemperatureArray", ipmi_baseboard_Temperature_array);
					  
				  }
				  
				  if(ipmij.ipmiBaseboardvoltageResulator!= null && ipmij.ipmiBaseboardvoltageResulator.size()>0) {
					  
					  JsonArrayBuilder ipmi_Baseboardvoltage_Resulator = Json.createArrayBuilder();
					  for(int j=0; j<ipmij.ipmiBaseboardvoltageResulator.size();j++) {
						  ipmiBaseboardVoltageResultatorJson = ipmij.ipmiBaseboardvoltageResulator.get(j);
						  JsonObjectBuilder obj1 = Json.createObjectBuilder().add("baseboardVoltageRegulatorIdentifier",
								  ipmiBaseboardVoltageResultatorJson.baseboardVoltageRegulatorIdentifier);
						  ipmiBaseboardVoltageResultatorJson.voltageRegulatorTemperature.encJsonValue(obj1, "voltageRegulatorTemperature");
						  
						  
						  
						  ipmi_Baseboardvoltage_Resulator.add(obj1.build());
					  }
					  
					//  obj.add("ipmiBaseboardVoltageRegulatorArray", ipmi_Baseboardvoltage_Resulator );
					  builder1.add("ipmiBaseboardVoltageRegulatorArray", ipmi_Baseboardvoltage_Resulator);
					  
				  }
				  
				  if(ipmij.ipmiFan!= null && ipmij.ipmiFan.size()>0) {
					  
					  JsonArrayBuilder ipmi_Fan = Json.createArrayBuilder();
					  for(int j=0; j<ipmij.ipmiFan.size();j++) {
						  ipmifanjson = ipmij.ipmiFan.get(j);
						  JsonObjectBuilder obj1 = Json.createObjectBuilder().add("fanIdentifier",
								  ipmifanjson.fanIdentifier);
						  ipmifanjson.fanSpeed.encJsonValue(obj1, "fanSpeed");
						  
						  
						  
						  ipmi_Fan.add(obj1.build());
					  }
					  
					//  obj.add("ipmiFanArray", ipmi_Fan );
					  builder1.add("ipmiFanArray", ipmi_Fan);
					  
				  }
				  
				  
				  
				  
				  
				  
				  //builder.add(obj.build());
			  }
			//evelmeasmt.add("ipmi", builder) ;
			  
			evelmeasmt.add("ipmi", builder1) ;
		  }

	    /***************************************************************************/
	    /* Disk Use list.                                                           */
	    /***************************************************************************/
		  if( disk_usage != null && disk_usage.size() > 0 )
		  {
		    JsonArrayBuilder builder = Json.createArrayBuilder();
		    for(int i=0;i<disk_usage.size();i++) {
			  disk_use = disk_usage.get(i);
			  JsonObjectBuilder obj = Json.createObjectBuilder()
			                      .add( "diskIdentifier", disk_use.id);
			  
			   disk_use.iotimeavg.encJsonValue(obj,"diskIoTimeAvg");
			   disk_use.iotimelast.encJsonValue(obj,"diskIoTimeLast");
			   disk_use.iotimemax.encJsonValue(obj,"diskIoTimeMax");
			   disk_use.iotimemin.encJsonValue(obj,"diskIoTimeMin");
			   disk_use.mergereadavg.encJsonValue(obj,"diskMergedReadAvg");
			   disk_use.mergereadlast.encJsonValue(obj,"diskMergedReadLast");
			   disk_use.mergereadmax.encJsonValue(obj,"diskMergedReadMax");
			   disk_use.mergereadmin.encJsonValue(obj,"diskMergedReadMin");
			   disk_use.mergewriteavg.encJsonValue(obj,"diskMergedWriteAvg");
			   disk_use.mergewritelast.encJsonValue(obj,"diskMergedWriteLast");
			   disk_use.mergewritemax.encJsonValue(obj,"diskMergedWriteMax");
			   disk_use.mergewritemin.encJsonValue(obj,"diskMergedWriteMin");
			   disk_use.octetsreadavg.encJsonValue(obj,"diskOctetsReadAvg");
			   disk_use.octetsreadlast.encJsonValue(obj,"diskOctetsReadLast");
			   disk_use.octetsreadmax.encJsonValue(obj,"diskOctetsReadMax");
			   disk_use.octetsreadmin.encJsonValue(obj,"diskOctetsReadMin");
			   disk_use.octetswriteavg.encJsonValue(obj,"diskOctetsWriteAvg");
			   disk_use.octetswritelast.encJsonValue(obj,"diskOctetsWriteLast");
			   disk_use.octetswritemax.encJsonValue(obj,"diskOctetsWriteMax");
			   disk_use.octetswritemin.encJsonValue(obj,"diskOctetsWriteMin");
			   disk_use.opsreadavg.encJsonValue(obj,"diskOpsReadAvg");
			   disk_use.opsreadlast.encJsonValue(obj,"diskOpsReadLast");
			   disk_use.opsreadmax.encJsonValue(obj,"diskOpsReadMax");
			   disk_use.opsreadmin.encJsonValue(obj,"diskOpsReadMin");
			   disk_use.opswriteavg.encJsonValue(obj,"diskOpsWriteAvg");
			   disk_use.opswritelast.encJsonValue(obj,"diskOpsWriteLast");
			   disk_use.opswritemax.encJsonValue(obj,"diskOpsWriteMax");
			   disk_use.opswritemin.encJsonValue(obj,"diskOpsWriteMin");
			   disk_use.pendingopsavg.encJsonValue(obj,"diskPendingOperationsAvg");
			   disk_use.pendingopslast.encJsonValue(obj,"diskPendingOperationsLast");
			   disk_use.pendingopsmax.encJsonValue(obj,"diskPendingOperationsMax");
			   disk_use.pendingopsmin.encJsonValue(obj,"diskPendingOperationsMin");
			   disk_use.timereadavg.encJsonValue(obj,"diskTimeReadAvg");
			   disk_use.timereadlast.encJsonValue(obj,"diskTimeReadLast");
			   disk_use.timereadmax.encJsonValue(obj,"diskTimeReadMax");
			   disk_use.timereadmin.encJsonValue(obj,"diskTimeReadMin");
			   disk_use.timewriteavg.encJsonValue(obj,"diskTimeWriteAvg");
			   disk_use.timewritelast.encJsonValue(obj,"diskTimeWriteLast");
			   disk_use.timewritemax.encJsonValue(obj,"diskTimeWriteMax");
			   disk_use.timewritemin.encJsonValue(obj,"diskTimeWriteMin");
			   
			   disk_use.diskTime.encJsonValue(obj, "diskTime");
			   disk_use.diskFlushRequests.encJsonValue(obj, "diskFlushRequests");
			   disk_use.diskFlushTime.encJsonValue(obj, "diskFlushTime");
			   disk_use.diskCommandsAvg.encJsonValue(obj, "diskCommandsAvg");
			   disk_use.diskReadCommandsAvg.encJsonValue(obj, "diskReadCommandsAvg");
			   disk_use.diskWriteCommandsAvg.encJsonValue(obj, "diskWriteCommandsAvg");
			   disk_use.diskCommandsAborted.encJsonValue(obj, "diskCommandsAborted");
			   disk_use.diskBusResets.encJsonValue(obj, "diskBusResets");
			   disk_use.diskTotalReadLatencyAvg.encJsonValue(obj, "diskTotalReadLatencyAvg");
			   disk_use.diskTotalWriteLatencyAvg.encJsonValue(obj, "diskTotalWriteLatencyAvg");
			   
			   disk_use.diskWeightedIoTimeAvg.encJsonValue(obj, "diskWeightedIoTimeAvg");
			   disk_use.diskWeightedIoTimeLast.encJsonValue(obj, "diskWeightedIoTimeLast");
			   disk_use.diskWeightedIoTimeMax.encJsonValue(obj, "diskWeightedIoTimeMax");
			   disk_use.diskWeightedIoTimeMin.encJsonValue(obj, "diskWeightedIoTimeMin");
			   
			   
			 
			  builder.add(obj.build());
		    }
			evelmeasmt.add("diskUsageArray", builder);
		  }


	    /***************************************************************************/
	    /* Filesystem Usage list.                                                  */
	    /***************************************************************************/
		  if( filesystem_usage != null &&  filesystem_usage.size() > 0 )
		  {
		    JsonArrayBuilder builder = Json.createArrayBuilder();
		    for(int i=0;i<filesystem_usage.size();i++) {
			  fsys_use = filesystem_usage.get(i);
			  JsonObject obj = Json.createObjectBuilder()
			    	     .add("blockConfigured", fsys_use.block_configured)
			    	     .add("blockIops", fsys_use.block_iops)
				         .add("blockUsed", fsys_use.block_used)
				         .add("ephemeralConfigured", fsys_use.ephemeral_configured)
				         .add("ephemeralIops", fsys_use.ephemeral_iops)
				         .add("ephemeralUsed", fsys_use.ephemeral_used)
				         .add("filesystemName", fsys_use.filesystem_name)			    	     
			    	     .build();
			  builder.add(obj);
		    }
			evelmeasmt.add("filesystemUsageArray", builder);
		  }

	    /***************************************************************************/
	    /* Latency distribution.                                                   */
	    /***************************************************************************/ 
		  if( latency_distribution != null && latency_distribution.size() > 0 )
		  {
		    JsonArrayBuilder builder = Json.createArrayBuilder();
		    for(int i=0;i<latency_distribution.size();i++) {
			  bucket = latency_distribution.get(i);
			  JsonObjectBuilder obj = Json.createObjectBuilder()
			                      .add( "countsInTheBucket", bucket.count);
			  
			  bucket.low_end.encJsonValue(obj,"lowEndOfLatencyBucket");
			  bucket.high_end.encJsonValue(obj,"highEndOfLatencyBucket");				  
					  
			  builder.add(obj.build());
		    }
			evelmeasmt.add("latencyDistribution", builder);
		  }
		  
		  mean_request_latency.encJsonValue(evelmeasmt, "meanRequestLatency");
		  request_rate.encJsonValue(evelmeasmt, "requestRate");

	    /***************************************************************************/
	    /* vNIC Usage TBD Performance array                          */
	    /***************************************************************************/
		  if( vnic_usage!= null && vnic_usage.size() > 0 )
		  {
		    JsonArrayBuilder builder = Json.createArrayBuilder();
		    for(int i=0;i<vnic_usage.size();i++) {
			  nic_use = vnic_usage.get(i);
			  JsonObjectBuilder obj = Json.createObjectBuilder()
			                      .add( "nicIdentifier", nic_use.vnic_id)
			                      .add( "valuesAreSuspect",nic_use.valuesaresuspect);
			  
			  
	          /*********************************************************************/
	          /* Optional fields.                                                  */
	          /*********************************************************************/			  
			  nic_use.recvd_bcast_packets_acc.encJsonValue(obj,"receivedBroadcastPacketsAccumulated");
			  nic_use.recvd_bcast_packets_delta.encJsonValue(obj,"receivedBroadcastPacketsDelta");
			  nic_use.recvd_discarded_packets_acc.encJsonValue(obj,"receivedDiscardedPacketsAccumulated");
			  nic_use.recvd_discarded_packets_delta.encJsonValue(obj,"receivedDiscardedPacketsDelta");
			  nic_use.recvd_error_packets_acc.encJsonValue(obj,"receivedErrorPacketsAccumulated");
			  nic_use.recvd_error_packets_delta.encJsonValue(obj,"receivedErrorPacketsDelta");
			  
			  nic_use.recvd_mcast_packets_acc.encJsonValue(obj,"receivedMulticastPacketsAccumulated");
			  nic_use.recvd_mcast_packets_delta.encJsonValue(obj,"receivedMulticastPacketsDelta");
			  nic_use.recvd_octets_acc.encJsonValue(obj,"receivedOctetsAccumulated");
			  nic_use.recvd_octets_delta.encJsonValue(obj,"receivedOctetsDelta");
			  
			  nic_use.recvd_total_packets_acc.encJsonValue(obj,"receivedTotalPacketsAccumulated");
			  nic_use.recvd_total_packets_delta.encJsonValue(obj,"receivedTotalPacketsDelta");
			  nic_use.recvd_ucast_packets_acc.encJsonValue(obj,"receivedUnicastPacketsAccumulated");
			  nic_use.recvd_ucast_packets_delta.encJsonValue(obj,"receivedUnicastPacketsDelta");
			  
			  nic_use.tx_bcast_packets_acc.encJsonValue(obj,"transmittedBroadcastPacketsAccumulated");
			  nic_use.tx_bcast_packets_delta.encJsonValue(obj,"transmittedBroadcastPacketsDelta");
			  nic_use.tx_discarded_packets_acc.encJsonValue(obj,"transmittedDiscardedPacketsAccumulated");
			  nic_use.tx_discarded_packets_delta.encJsonValue(obj,"transmittedDiscardedPacketsDelta");			  

			  nic_use.tx_error_packets_acc.encJsonValue(obj,"transmittedErrorPacketsAccumulated");
			  nic_use.tx_error_packets_delta.encJsonValue(obj,"transmittedErrorPacketsDelta");
			  nic_use.tx_mcast_packets_acc.encJsonValue(obj,"transmittedMulticastPacketsAccumulated");
			  nic_use.tx_mcast_packets_delta.encJsonValue(obj,"transmittedMulticastPacketsDelta");
			  
			  nic_use.tx_octets_acc.encJsonValue(obj,"transmittedOctetsAccumulated");
			  nic_use.tx_octets_delta.encJsonValue(obj,"transmittedOctetsDelta");
			  nic_use.tx_total_packets_acc.encJsonValue(obj,"transmittedTotalPacketsAccumulated");
			  nic_use.tx_total_packets_delta.encJsonValue(obj,"transmittedTotalPacketsDelta");
			  nic_use.tx_ucast_packets_acc.encJsonValue(obj,"transmittedUnicastPacketsAccumulated");
			  nic_use.tx_ucast_packets_delta.encJsonValue(obj,"transmittedUnicastPacketsDelta");
			  
			  //VES6.0 added fields 19July
			//  nic_use.administrativeState.encJsonValue(obj, "administrativeState");
			  nic_use.administrativeState.encJsonValue(obj, "administrativeState");
			  nic_use.operationalState.encJsonValue(obj, "operationalState");
			  nic_use.receivedPercentDiscard.encJsonValue(obj, "receivedPercentDiscard");
			  nic_use.receivedPercentError.encJsonValue(obj, "receivedPercentError");
			  nic_use.receivedUtilization.encJsonValue(obj, "receivedUtilization");
			  nic_use.speed.encJsonValue(obj, "speed");
			  nic_use.transmittedPercentDiscard.encJsonValue(obj, "transmittedPercentDiscard");
			  nic_use.transmittedPercentError.encJsonValue(obj, "transmittedPercentError");
			  nic_use.transmittedUtilization.encJsonValue(obj, "transmittedUtilization");
			  
			  
			  
					  
			  builder.add(obj.build());
		    }
			evelmeasmt.add("nicPerformanceArray", builder);
		  }  
		  


	    /***************************************************************************/
	    /* Memory Use list.                                                           */
	    /***************************************************************************/ 
		  if( mem_usage != null && mem_usage.size() > 0 )
		  {
		    JsonArrayBuilder builder = Json.createArrayBuilder();
		    for(int i=0;i<mem_usage.size();i++) {
			  mem_use = mem_usage.get(i);
			  JsonObjectBuilder obj = Json.createObjectBuilder()
		    //                  .add( "memIdentifier", mem_use.id)
			                      .add( "vmIdentifier", mem_use.vmid)
			                      .add( "memoryBuffered",mem_use.membuffsz);
			  
			  mem_use.memcache.encJsonValue(obj,"memoryCached");
			  mem_use.memconfig.encJsonValue(obj,"memoryConfigured");
			  mem_use.memfree.encJsonValue(obj,"memoryFree");
			  mem_use.slabrecl.encJsonValue(obj,"memorySlabRecl");
			  mem_use.slabunrecl.encJsonValue(obj,"memorySlabUnrecl");
			  mem_use.memused.encJsonValue(obj,"memoryUsed");
			  
			  mem_use.memoryDemand.encJsonValue(obj,"memoryDemand");
			  mem_use.memoryLatencyAvg.encJsonValue(obj,"memoryLatencyAvg");
			  
			  mem_use.memoryLatencyAvg.encJsonValue(obj,"memoryLatencyAvg");
			  mem_use.memorySharedAvg.encJsonValue(obj,"memorySharedAvg");
			  mem_use.memorySwapInAvg.encJsonValue(obj,"memorySwapInAvg");
			  mem_use.memorySwapInRateAvg.encJsonValue(obj,"memorySwapInRateAvg");
			  
			  mem_use.memorySwapOutAvg.encJsonValue(obj,"memorySwapOutAvg");
			  mem_use.memorySwapOutRateAvg.encJsonValue(obj,"memorySwapOutRateAvg");
			  mem_use.memorySwapUsedAvg.encJsonValue(obj,"memorySwapUsedAvg");
			  
					  
			  builder.add(obj.build());
		    }
			evelmeasmt.add("memoryUsageArray", builder);
		  }
		  
		  media_ports_in_use.encJsonValue(evelmeasmt, "numberOfMediaPortsInUse");
		  vnfc_scaling_metric.encJsonValue(evelmeasmt, "nfcScalingMetric");
		  

	    /***************************************************************************/
	    /* Feature Utilization list.                                               */
	    /***************************************************************************/
		  if( feature_usage != null && feature_usage.size() > 0 )
		  {
			  JsonObjectBuilder builder = Json.createObjectBuilder();  
		   // JsonArrayBuilder builder = Json.createArrayBuilder();
		    for(int i=0;i<feature_usage.size();i++) {
			  feature_use = feature_usage.get(i);
			  builder.add(feature_use.feature_id, feature_use.feature_utilization+"");
		    }
			evelmeasmt.add("featureUsageArray", builder);
		  }


	    /***************************************************************************/
	    /* Codec Utilization list.                                                 */
	    /***************************************************************************/
		  if( codec_usage != null && codec_usage.size() > 0 )
		  {
			  //JsonObjectBuilder builder = Json.createObjectBuilder(); 
		   JsonArrayBuilder builder = Json.createArrayBuilder();
		    for(int i=0;i<codec_usage.size();i++) {
			  codec_use = codec_usage.get(i);
			  JsonObjectBuilder obj = Json.createObjectBuilder()
			                      .add( "codecIdentifier", codec_use.codec_id)
			                      .add( "numberInUse", codec_use.number_in_use);			  
					  
			  builder.add(obj);
		    }
			evelmeasmt.add("codecUsageArray", builder);
		  }
		  

	    /***************************************************************************/
	    /* Additional Measurement Groups list.                                     */
	    /***************************************************************************/
		  if( additional_measurements != null && additional_measurements.size() > 0 )
		  {
		    JsonArrayBuilder builder = Json.createArrayBuilder();
		    for(int i=0;i<additional_measurements.size();i++) {
			  meas_group = additional_measurements.get(i);
			  JsonObjectBuilder obj = Json.createObjectBuilder()
			                      .add( "name", meas_group.name);
			  JsonObjectBuilder builder2 = Json.createObjectBuilder();
			 
			  for(int j=0;j<meas_group.measurements.size();j++) {
				  custom_meas = meas_group.measurements.get(j);
				  builder2.add(custom_meas.name, custom_meas.value);	  
			  }
			  obj.add("hashMap", builder2);			  
			  builder.add(obj.build());
			  
			  
		    }
			evelmeasmt.add("additionalMeasurements", builder);
		  }
		  
		    /***************************************************************************/
		    /* Additional Objects.                                                 */
		    /***************************************************************************/
	      if( additional_objects != null && additional_objects.size() > 0 )
		  {
			    JsonArrayBuilder builder = Json.createArrayBuilder();
			    for(int i=0;i<additional_objects.size();i++) {
				  JsonObject jobj = additional_objects.get(i);
				  builder.add(jobj);
			    }
				evelmeasmt.add("additionalObjects",builder);
		  }

	    /***************************************************************************/
	    /* Although optional, we always generate the version.  Note that this      */
	    /* closes the object, too.                                                 */
	    /***************************************************************************/
	    evelmeasmt.add("measurementFieldsVersion", version);

	    EVEL_EXIT();
	    
	    return evelmeasmt;
	  }
	  
	  /**************************************************************************//**
	   * Encode the event as a JSON event object according to AT&T's schema.
	   *
	   * retval : String of JSON event message
	   *****************************************************************************/
	  public JsonObject evel_json_encode_event()
	  {
		EVEL_ENTER();
		
		assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_MEASUREMENT);
		//encode common event header and measurement body    
	    JsonObject obj = Json.createObjectBuilder()
	    	     .add("event", Json.createObjectBuilder()
		    	         .add( "commonEventHeader",eventHeaderObject() )
		    	         .add( "measurementFields",evelScalingMeasurementObject() )
		    	         ).build();

	    EVEL_EXIT();
	    
	    return obj;

	  }
	  
	  
	  public JsonObject evel_json_encode_event_batch()
	  {
		EVEL_ENTER();
		
		assert(event_domain == EvelHeader.DOMAINS.EVEL_DOMAIN_MEASUREMENT);
		//encode common event header and measurement body    
	    JsonObject obj = Json.createObjectBuilder()
	    	    // .add("event", Json.createObjectBuilder()
		    	         .add( "commonEventHeader",eventHeaderObject() )
		    	         .add( "measurementFields",evelScalingMeasurementObject() )
		    	         .build();

	    EVEL_EXIT();
	    
	    return obj;

	  }


}