
PROJECT DESCRIPTION

---
This project contains the source code and scripts for the generation of fault events.

 - README.md: this file.


 - FaultData.java and DeviceData.java files: source code that uses the ECOMP Vendor Event Listener Library (VES) to generate the fault events. Fault is generated based on the link status. If number of bytes transmitted/received is less than the low water mark, the fault is generated. The application reads flt_config.json file for parameter values and populate the fault event. If eventName, eventSourceType, vfStatus, specificProblem or alarmCondition parameter value is not given, the application terminates. If reportingEntityName and sourceName parameter values are not given, then it gets the hostname and populates it. If tmp_faultCheckInterval is not given, it defaults to 60 seconds. 

 

 - FaultData.java: It reads input parameters like DCAE IP address and port from configuration files contained in /opt/config. Based on the collector configuration, use FaultData.java for use single and 2 collectors configuration.


USAGE
-----

Update the configuration files with proper parameters values so that events generated would contain those values

To run the FaultData.java in single collector configuration, please execute the following steps:

  -Compile Load Balance VES agent
   javac -cp <.:dependent jars> ./evel_javalibrary/att/com/loadbalance
   In Eclipse right click on veslibrary/ves_javalibrary/evel_javalib2 application-> click Run As ->and select -> mvn build option then
   ->select the configuration mvn clean install.


  -Run Load Balance VES agent
   java -cp <.:dependent jars> evel_javalibrary.att.com.loadbalance.FaultData.java
   In Eclipse right click on evel_javalibrary.att.com.loadbalance.FaultData.java class right click -> click Run As -> click Java application.

