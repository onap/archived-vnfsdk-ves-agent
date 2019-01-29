# ECOMP Vendor Event Listener Library

“The content of this directory is currently under development and, at this stage, is not intended for demonstration and/or testing.”

This project contains a C library that supports interfacing to AT&T's ECOMP
Vendor Event Listener. For an overview of ECOMP, see the 
[ECOMP White Paper](http://att.com/ECOMP).

Developed in 2016 for AT&T by:
 * Alok Gupta (https://github.com/ag1367)
 * Paul Potochniak (https://github.com/pp8491)
 * Gayathri Patrachari(https://github.com/gp2421)

Current Maintainers: 
 * Alok Gupta (https://github.com/ag1367)
 * Paul Potochniak (https://github.com/pp8491)
 * Gayathri Patrachari(https://github.com/gp2421)

# Installation

For installation instructions, clone this repo and load the 
[installation guide](./docs/source/evel/html/quickstart.html) in your web browser.

Full source-code documentation is included with the code and can be built from 
the included Makefile. See the [readme file](./code/evel_library/readme.md).

# Use

Clone this repo and load the [user guide](./docs/source/evel/html/index.html)
in your web browser.

# Package installation
Following packages are to be installed using apt-get as below
sudo apt-get install gcc
sudo apt-get install libcurl3-dev

# Compiling the VES Library code
Go to /vnfsdk/ves-agent/veslibrary/ves_clibrary/evel/evel-library/bldjobs directory and run the below commands

make all - to create the VES library
make package - to create the VES package if needed

make install- can also be given to make a package and install the package in another machine - see Makefile for more details 

# Loading the VES library(evel)
Go to vnfsdk/ves-agent/veslibrary/ves_clibrary/evel/evel-library/libs/x86_64 directory and run below commands

sudo cp libevel.so /usr/lib
sudo ldconfig

# Sample Agent application information

There are 4 sample agent codes reside in below directories. These events are driven by the JSON configure which are getting populated while generating the events. Each directory has readme.md file that explains how to configure JSON config file and procedure to run. You can compile the code using 'make all'. 

- /vnfsdk/ves-agent/veslibrary/ves_clibrary/evel/evel-library/code/VESreporting_HB - Sample heartbeat event generated periodically

- /vnfsdk/ves-agent/veslibrary/ves_clibrary/evel/evel-library/code/VESreporting_fault - Sample fault event based on low byte/packet count on interface.

- /vnfsdk/ves-agent/veslibrary/ves_clibrary/evel/evel-library/code/VESreporting_syslog - Sample syslog event based on pattern being logged into any file

- /vnfsdk/ves-agent/veslibrary/ves_clibrary/evel/evel-library/code/VESreporting_vFW - Sample Firewall application that generates measurement event periodically. 

Apart from the above there is a virtual Firewall application at the below location.

- /vnfsdk/ves-agent/veslibrary/ves_clibrary/VESreporting_vFW - This generates the periodic heartbeat and measurement events. It also gives fault event.

Care to be taken to compile the virtual Firewall agent

- Copy the contents of the directory into ~/vnfsdk/ves-agent/veslibrary/ves_clibrary/evel/evel-library/code/VESreporting directory

- run 'make all' to create an executable (alternatively, this agent gets compiled during compilation of evel library when VESreporting directory has all relevant files specific to that event

- run the application using go-client.sh command (see readme.md for details)
