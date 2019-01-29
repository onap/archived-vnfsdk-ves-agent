
PROJECT DESCRIPTION

---
This project contains the source code and scripts for the periodic generation of network measurement reports and heartbeat events. It also generates fault event if the packets/bytes transferred are below the low water mark for the network interface. 


 - syslogData.java file: source code that uses the ECOMP Vendor Event Listener Library (VES) to read syslog message from /var/log/syslog and send syslog events to the VES collector in DCAE. It reads syslog_config.json file for parameter values and populate the syslog event. If eventName parameter value is not given, the application terminates. If reportingEntityName and sourceName parameter values are not given.


 - - syslogData.java: It reads input parameters like DCAE IP address and port from configuration files contained in /opt/config. Based on the collector configuration, use MeasureData.java for single and 2 collectors configuration.


USAGE
-----

Update the configuration files with proper parameters values so that events generated would contain those values

To run the MeasureData.java, please execute the following steps:

  -Compile Load Balance VES agent
   javac -cp <.:dependent jars> ./evel_javalibrary/att/com/loadbalance
   In Eclipse right click on veslibrary/ves_javalibrary/evel_javalib2 application-> click Run As ->and select -> mvn build option then
   ->select the configuration mvn clean install.

  -Run Load Balance VES agent
   java -cp <.:dependent jars> evel_javalibrary.att.com.loadbalance.syslogData.java
   In Eclipse right click on evel_javalibrary.att.com.loadbalance.syslogData.java class right click -> click Run As -> click Java application.


