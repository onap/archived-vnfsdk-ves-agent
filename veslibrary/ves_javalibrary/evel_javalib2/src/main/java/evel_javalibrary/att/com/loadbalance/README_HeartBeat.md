
PROJECT DESCRIPTION

---
This project contains the source code and scripts for the periodic generation of heartbeat events. 

 - README.md: this file.


 - HeartBeatData.java file: source code that uses the ECOMP Vendor Event Listener Library (VES) to generate the periodic heartbeat events. It reads hb_config.json file for parameter values and populate the heartbeat event. If eventName parameter value is not given, the application terminates. If reportingEntityName and sourceName parameter values are not given, then it gets the hostname and populates it. If heartbeatInterval is not given, it defaults to 60 seconds. 



 - HeartBeatData.java file: It reads input parameters like DCAE IP address and port from configuration files contained in /opt/config. Based on the collector configuration, use HeartBeatData.java file for single and 2 collectors configuration.


USAGE
-----

Update the configuration files with proper parameters values so that events generated would contain those values

To run the HeartBeatData.java in single collector configuration, please execute the following steps:

  -Compile Load Balance VES agent
   javac -cp <.:dependent jars> ./evel_javalibrary/att/com/loadbalance
   In Eclipse right click on veslibrary/ves_javalibrary/evel_javalib2 application-> click Run As ->and select -> mvn build option then
   ->select the configuration mvn clean install.

  -Run Load Balance VES agent
   java -cp <.:dependent jars> evel_javalibrary.att.com.loadbalance.HeartBeatData.java
   In Eclipse right click on evel_javalibrary.att.com.loadbalance.HeartBeatData.java class right click -> click Run As -> click Java application.


