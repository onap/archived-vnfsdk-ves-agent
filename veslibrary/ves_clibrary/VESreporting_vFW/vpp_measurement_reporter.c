/*************************************************************************//**
 *
 * Copyright © 2017 AT&T Intellectual Property. All rights reserved.
 *
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
 *
 ****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>
#include <sys/stat.h>

#include "evel.h"

#define BUFSIZE 128
#define MAX_INTERFACES 40


void *MeasureThread(void *interfaceId);
void *FaultThread(void *interfaceId);
void *HeartbeatThread(void *threadarg);
void read_common_config_file();

typedef struct dummy_vpp_metrics_struct {
  int curr_bytes_in;
  int curr_bytes_out;
  int curr_packets_in;
  int curr_packets_out;
  int last_bytes_in;
  int last_bytes_out;
  int last_packets_in;
  int last_packets_out;
} vpp_metrics_struct;

typedef struct linkstat {

  char linkname[32];
  char linkdescr[64];
  char linkmode[64];
  int  speedmbps;
  int  fault_raised;
  unsigned long long last_epoch;

}LINKSTAT;

vpp_metrics_struct meas_intfstat[MAX_INTERFACES];
LINKSTAT meas_linkstat[MAX_INTERFACES];
int gm_linkcount = 0;

vpp_metrics_struct fault_intfstat[MAX_INTERFACES];
LINKSTAT fault_linkstat[MAX_INTERFACES];
int gf_faultCheckInterval = 0;
int gf_lowWaterMark = 0;
int gf_linkcount = 0;

void read_vpp_metrics(vpp_metrics_struct *, LINKSTAT *, int);

unsigned long long epoch_start = 0;
time_t common_filetime = 0;
time_t hb_filetime = 0;
time_t meas_filetime = 0;
time_t fault_filetime = 0;
time_t intf_ffiletime = 0;
time_t intf_mfiletime = 0;

int gh_eventId = 1;
int gm_eventId = 1;
char gh_event_name[BUFSIZE];
char gm_event_name[BUFSIZE];
char gf_event_name[BUFSIZE];
char g_event_type[BUFSIZE];
char g_nfc_nam_code[BUFSIZE];
char g_nf_nam_code[BUFSIZE];
char g_nf_vendor_name[BUFSIZE];
char g_report_entity_id[BUFSIZE];
char g_report_entity_name[BUFSIZE];
char g_source_id[BUFSIZE];
char g_timezone[BUFSIZE];
int gm_interval = 0;
int gh_interval = 0;
char g_source_name[BUFSIZE];

int request_rate=0;

int measure_traffic() 
{

  FILE *fp;
  int status;
  char count[10];
  time_t rawtime;
  struct tm * timeinfo;
  char period [21];
  char cmd [100];
  char secs [3];
  int sec;

  printf("Checking app traffic\n");
  time (&rawtime);
  timeinfo = localtime (&rawtime);
  strftime(period,21,"%d/%b/%Y:%H:%M:",timeinfo);
  strftime(secs,3,"%S",timeinfo);
  sec = atoi(secs);
  if (sec == 0) sec = 59;
  sprintf(secs, "%02d", sec);
  strncat(period, secs, 21);
  // ....x....1....x....2.
  // 15/Oct/2016:17:51:19
  strcpy(cmd, "sudo docker logs vHello | grep -c ");
  strncat(cmd, period, 100);

  fp = popen(cmd, "r");
  if (fp == NULL) {
    EVEL_ERROR("popen failed to execute command");
  }

  if (fgets(count, 10, fp) != NULL) {
    request_rate = atoi(count);
    printf("Reporting request rate for second: %s as %d\n", period, request_rate);

    }
    else {
      EVEL_ERROR("New Measurement failed");
    }
    printf("Processed measurement\n");
  
  status = pclose(fp);
  if (status == -1) {
    EVEL_ERROR("pclose returned an error");
  }
  return request_rate;
}

/**************************************************************************//**
 * tap live cpu stats
 *****************************************************************************/
void evel_get_cpu_stats(EVENT_MEASUREMENT * measurement)
{
  FILE *fp;
  char path[1024];
  double usage=0.0;
  double idle;
  double intrpt;
  double nice;
  double softirq;
  double steal;
  double sys;
  double user;
  double wait;
  MEASUREMENT_CPU_USE *cpu_use = NULL;

  /* Open the command for reading. */
  //fp = popen("/bin/ls /etc/", "r");
  fp = popen("/usr/bin/top -bn 2 -d 0.01 | grep '^%Cpu' | tail -n 1 ", "r");
  if (fp == NULL) {
    printf("Failed to run command\n" );
    exit(1);
  }

  /* Read the output a line at a time - output it. */
  while (fgets(path, sizeof(path)-1, fp) != NULL) {
    printf("%s", path+10);
    sscanf(path+10," %lf us, %lf sy,  %lf ni,  %lf id,  %lf wa,  %lf hi,  %lf si,  %lf st",
    &user,&sys,&nice,&idle,&wait,&intrpt,&softirq,&steal);
  }

  /* close */
  pclose(fp);

  cpu_use = evel_measurement_new_cpu_use_add(measurement, "cpu1", usage);
  if( cpu_use != NULL ){

  evel_measurement_cpu_use_idle_set(cpu_use,idle);
  //evel_measurement_cpu_use_interrupt_set(cpu_use,intrpt);
  //evel_measurement_cpu_use_nice_set(cpu_use,nice);
  //evel_measurement_cpu_use_softirq_set(cpu_use,softirq);
  //evel_measurement_cpu_use_steal_set(cpu_use,steal);
  evel_measurement_cpu_use_system_set(cpu_use,sys);
  evel_measurement_cpu_use_usageuser_set(cpu_use,user);
  //evel_measurement_cpu_use_wait_set(cpu_use,wait);
  //evel_measurement_cpu_use_add(measurement, "cpu2", usage,idle,intrpt,nice,softirq,steal,sys,user,wait);
  }
}

int file_is_modified(const char *path, time_t *oldMTime) {
    struct stat file_stat;
    int err = stat(path, &file_stat);
    if (err != 0) {
        perror(" [file_is_modified] stat");
        exit(1);
    }
    if( file_stat.st_mtime > *oldMTime)
    {
      *oldMTime = file_stat.st_mtime;
      return 1;
    }
    else
      return 0;
}

void read_fault_config_file()
{
  char const* const fault_fileName = "fw_flt_config.txt";
  char const* const intf_fileName = "fw_interface_config.txt";
  char *pos;
  char line[BUFSIZE];
  char param[BUFSIZE];
  char value[BUFSIZE];
    
  read_common_config_file();

  FILE* file = fopen(fault_fileName, "r"); /* should check the result */
  if( file == NULL ){
    EVEL_ERROR("Error: file open error or config file is not there\n");
    exit(-1);
  }
  if(file_is_modified(fault_fileName, &fault_filetime))
  {
    printf("Fault config file changed \n");
    
    memset(gf_event_name, 0, BUFSIZE);
    gf_faultCheckInterval = 0;
    gf_lowWaterMark = 0;

    while ( file != NULL && fgets(line, sizeof(line), file)) {
        /* note that fgets don't strip the terminating \n, checking its
           presence would allow to handle lines longer that sizeof(line) */
        memset(param, 0, BUFSIZE);
        memset(value, 0, BUFSIZE);

        if ((pos=strchr(line, '\n')) != NULL)
           *pos = '\0';
        sscanf(line,"%s %s",param,value);
        //remove_spaces(line);
        if (strcmp (param, "eventName") ==0)
        {
           if (strlen(value) != 0)
           {
              strcpy(gf_event_name, value);
           }
           else
           {
              printf("\nError: eventName is a mandatory parameter, update the config file\n");
              exit(-1);
           }
        }
        else if (strcmp (param, "faultCheckInterval") ==0)
        {
           if (strlen(value) != 0)
           {
              gf_faultCheckInterval = atoi(value);
           }
           else
           {
              printf("\nError: eventName is a mandatory parameter, update the config file\n");
              exit(-1);
           }
        }
        else if (strcmp (param, "lowWaterMark") ==0)
        {
           if (strlen(value) != 0)
           {
             gf_lowWaterMark = atoi(value);
           }
           else
           {
              printf("Error: lowWaterMark is a mandatory parameter, update the config file\n");
              exit(-1);
           }
        }
        else
        {
           printf ("Invalid parameter -%s %s\n", param, value);
        }
    }
  }

  /* Now read the interface file */
  file = fopen(intf_fileName, "r"); /* should check the result */
  if( file == NULL ){
    EVEL_ERROR("Error: file open error or config file is not there\n");
    exit(-1);
  }
  if(file_is_modified(intf_fileName, &intf_ffiletime))
  {
    printf("Fault config file changed \n");
    
    gf_linkcount = 0;

    while ( file != NULL && fgets(line, sizeof(line), file)) {
        /* note that fgets don't strip the terminating \n, checking its
           presence would allow to handle lines longer that sizeof(line) */
        memset(param, 0, BUFSIZE);
        memset(value, 0, BUFSIZE);

        if ((pos=strchr(line, '\n')) != NULL)
           *pos = '\0';
        sscanf(line,"%s %s",param,value);
        if (strlen(param) != 0)
        {
          strcpy(fault_linkstat[gf_linkcount].linkname, param);
          strcpy(fault_linkstat[gf_linkcount].linkdescr, value);
          gf_linkcount++;
        }
    }
  }
}

void read_hb_config_file()
{
  char const* const fileName = "fw_hb_config.txt";
  char *pos;
  char line[BUFSIZE];
  char param[BUFSIZE];
  char value[BUFSIZE];
    
  read_common_config_file();

  FILE* file = fopen(fileName, "r"); /* should check the result */
  if( file == NULL ){
    EVEL_ERROR("Error: file open error or config file is not there\n");
    exit(-1);
  }
  if(file_is_modified(fileName, &hb_filetime))
  {
    printf("HB config file changed \n");
    
    memset(gh_event_name, 0, BUFSIZE);
    gh_interval = 0;

    while ( file != NULL && fgets(line, sizeof(line), file)) {
        /* note that fgets don't strip the terminating \n, checking its
           presence would allow to handle lines longer that sizeof(line) */
        memset(param, 0, BUFSIZE);
        memset(value, 0, BUFSIZE);

        if ((pos=strchr(line, '\n')) != NULL)
           *pos = '\0';
        sscanf(line,"%s %s",param,value);
        //remove_spaces(line);
        if (strcmp (param, "eventName") ==0)
        {
           if (strlen(value) != 0)
           {
              strcpy(gh_event_name, value);
           }
           else
           {
              printf("\nError: eventName is a mandatory parameter, update the config file\n");
              exit(-1);
           }
        }
        else if (strcmp (param, "heartbeatInterval") ==0)
        {
           if (strlen(value) != 0)
           {
             gh_interval = atoi(value);
           }
           else
           {
              printf("Error: heartbeatInterval is a mandatory parameter, update the config file\n");
              exit(-1);
           }
        }
        else
        {
           printf ("Invalid parameter -%s %s\n", param, value);
        }
    }
  }
}

void read_meas_config_file()
{
  char const* const fileName = "fw_meas_config.txt";
  char const* const intf_fileName = "fw_interface_config.txt";
  char *pos;
  char line[BUFSIZE];
  char param[BUFSIZE];
  char value[BUFSIZE];
    
  read_common_config_file();

  FILE* file = fopen(fileName, "r"); /* should check the result */
  if( file == NULL ){
    EVEL_ERROR("Error: file open error or config file is not there\n");
    exit(-1);
  }
  if(file_is_modified(fileName, &meas_filetime))
  {
    printf("Measurement Config file changed \n");
    
    memset(gm_event_name, 0, BUFSIZE);
    gm_interval = 0;

    while ( file != NULL && fgets(line, sizeof(line), file)) {
        /* note that fgets don't strip the terminating \n, checking its
           presence would allow to handle lines longer that sizeof(line) */
        memset(param, 0, BUFSIZE);
        memset(value, 0, BUFSIZE);

        if ((pos=strchr(line, '\n')) != NULL)
           *pos = '\0';
        sscanf(line,"%s %s",param,value);
        printf("\n param and value are %s, %s\n", param,value);
        //remove_spaces(line);
        if (strcmp (param, "eventName") ==0)
        {
           if (strlen(value) != 0)
           {
              strcpy(gm_event_name, value);
           }
           else
           {
              printf("\nError: eventName is a mandatory parameter, update the config file\n");
              exit(-1);
           }
        }
        else if (strcmp (param, "measurementInterval") ==0)
        {
           if (strlen(value) != 0)
           {
             gm_interval = atoi(value);
           }
           else
           {
              printf("Error: measurementInterval is a mandatory parameter, update the config file\n");
              exit(-1);
           }
        }
        else
        {
           printf ("Invalid parameter -%s %s\n", param, value);
        }
    }
  }

  /* Now read the interface file */
  file = fopen(intf_fileName, "r"); /* should check the result */
  if( file == NULL ){
    EVEL_ERROR("Error: file open error or config file is not there\n");
    exit(-1);
  }

  if(file_is_modified(intf_fileName, &intf_mfiletime))
  {
    printf("Interface config file changed \n");
    
    gf_linkcount = 0;


    while ( file != NULL && fgets(line, sizeof(line), file)) {
        /* note that fgets don't strip the terminating \n, checking its
           presence would allow to handle lines longer that sizeof(line) */
        memset(param, 0, BUFSIZE);
        memset(value, 0, BUFSIZE);

        if ((pos=strchr(line, '\n')) != NULL)
           *pos = '\0';
        sscanf(line,"%s %s",param,value);
        if (strlen(param) != 0)
        {
          strcpy(meas_linkstat[gm_linkcount].linkname, param);
          strcpy(meas_linkstat[gm_linkcount].linkdescr, value);
          gm_linkcount++;
        }
    }
  }
}

void read_common_config_file()
{
  char const* const fileName = "fw_common_config.txt";
  char *pos;
  char line[BUFSIZE];
  char param[BUFSIZE];
  char value[BUFSIZE];
    
  FILE* file = fopen(fileName, "r"); /* should check the result */
  if( file == NULL ){
    EVEL_ERROR("Error: file open error or config file is not there\n");
    exit(-1);
  }
  if(file_is_modified(fileName, &common_filetime))
  {
    printf("Common Config file changed \n");
    
    memset(g_event_type, 0, BUFSIZE);
    memset(g_nfc_nam_code, 0, BUFSIZE);
    memset(g_nf_nam_code, 0, BUFSIZE);
    memset(g_nf_vendor_name, 0, BUFSIZE);
    memset(g_report_entity_id, 0, BUFSIZE);
    memset(g_report_entity_name, 0, BUFSIZE);
    memset(g_source_id, 0, BUFSIZE);
    memset(g_timezone, 0, BUFSIZE);

    while ( file != NULL && fgets(line, sizeof(line), file)) {
        /* note that fgets don't strip the terminating \n, checking its
           presence would allow to handle lines longer that sizeof(line) */
        memset(param, 0, BUFSIZE);
        memset(value, 0, BUFSIZE);

        if ((pos=strchr(line, '\n')) != NULL)
           *pos = '\0';
        sscanf(line,"%s %s",param,value);
        //remove_spaces(line);

        if (strcmp (param, "eventType") ==0)
        {
           if (strlen(value) != 0)
           {
             strcpy(g_event_type, value);
           }
        }
        else if (strcmp (param, "nfcNamingCode") ==0)
        {
           if (strlen(value) != 0)
           {
             strcpy(g_nfc_nam_code, value); 
           }
        }
        else if (strcmp (param, "nfNamingCode") ==0)
        {
           if (strlen(value) != 0)
           {
             strcpy(g_nf_nam_code, value); 
           }
        }
        else if (strcmp (param, "nfVendorName") ==0)
        {
           if (strlen(value) != 0)
           {
             strcpy(g_nf_vendor_name, value); 
           }
        }
        else if (strcmp (param, "reportingEntityId") ==0)
        {
           if (strlen(value) != 0)
           {
             strcpy(g_report_entity_id, value); 
           }
        }
        else if (strcmp (param, "reportingEntityName") ==0)
        {
           if (strlen(value) != 0)
           {
             strcpy(g_report_entity_name, value); 
           }
           else
           {
              printf("Error: reportingEntityName is a mandatory parameter, update the config file\n");
              exit(-1);
           }
        }
        else if (strcmp (param, "sourceId") ==0)
        {
           if (strlen(value) != 0)
           {
             strcpy(g_source_id, value); 
           }
        }
        else if (strcmp (param, "sourceName") ==0)
        {
           if (strlen(value) != 0)
           {
             strcpy(g_source_name, value); 
           }
           else
           {
              printf("Error: sourceName is a mandatory parameter, update the config file\n");
              exit(-1);
           }
        }
        else if (strcmp (param, "timeZoneOffset") ==0)
        {
           if (strlen(value) != 0)
           {
             strcpy(g_timezone, value); 
           }
        }
        else
        {
           printf ("Invalid parameter -%s %s\n", param, value);
        }
    }
  }
}

int main(int argc, char** argv)
{
  char* fqdn = argv[1];
  int port = atoi(argv[2]);
  char* fqdn2 = NULL;
  int port2 = 0;
  int i=0;
  int rc;
  pthread_attr_t attr;
  pthread_t hb_thread;
  pthread_t meas_thread;
  pthread_t flt_thread;
  
  if(argc == 5)
  {
     fqdn2 = argv[3];
     port2 = atoi(argv[4]);
  }

  if (!((argc == 3) || (argc == 5)))
  {
    fprintf(stderr, "Usage: %s <FQDN>|<IP address> <port> <FQDN>|<IP address> <port>  \n", argv[0]);
    fprintf(stderr, "OR\n");
    fprintf(stderr, "Usage: %s <FQDN>|<IP address> <port> \n", argv[0]);
    exit(-1);
  }

  /**************************************************************************/
  /* Initialize                                                             */
  /**************************************************************************/
  if(evel_initialize(fqdn,                         /* FQDN                  */
                     port, 	                   /* Port                  */
                     fqdn2, 	                   /* Backup FQDN           */
                     port2, 	                   /* Backup port           */
                     NULL,                         /* optional path         */
                     NULL,                         /* optional topic        */
                     100,                          /* Ring Buffer size      */
                     0,                            /* HTTPS?                */
                     NULL,                         /* cert file             */
                     NULL,                         /* key  file             */
                     NULL,                         /* ca   info             */
                     NULL,                         /* ca   file             */
                     0,                            /* verify peer           */
                     0,                            /* verify host           */
                     "sample1",                    /* Username              */
                     "sample1",                    /* Password              */
                     "sample1",                    /* Username2             */
                     "sample1",                    /* Password2             */
                     NULL,                         /* Source ip             */
                     NULL,                         /* Source ip2            */
                     EVEL_SOURCE_VIRTUAL_MACHINE,  /* Source type           */
                     "vFirewall",      	           /* Role                  */
                     1))                           /* Verbosity             */
  {
    fprintf(stderr, "\nFailed to initialize the EVEL library!!!\n");
    exit(-1);
  }
  else
  {
    printf("\nInitialization completed\n");
  }

  read_common_config_file();

  /* Initialize and set thread detached attribute */
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

  printf("Main:Creating thread \n");
  rc = pthread_create(&hb_thread, NULL, HeartbeatThread, &i);
  if (rc)
  {
    printf("ERROR; return code from pthread_create() is %d\n", rc);
    exit(-1);
  }
  printf("Main:Created HB thread \n");

  rc = pthread_create(&meas_thread, NULL, MeasureThread, &i);
  if (rc)
  {
    printf("ERROR; return code from pthread_create() is %d\n", rc);
    exit(-1);
  }
  printf("Main:Created Measurement thread \n");


  rc = pthread_create(&flt_thread, NULL, FaultThread, &i);
  if (rc)
  {
    printf("ERROR; return code from pthread_create() is %d\n", rc);
    exit(-1);
  }
  printf("Main:Created Fault thread \n");

  pthread_join(hb_thread, NULL);
  pthread_join(meas_thread, NULL);
  pthread_join(flt_thread, NULL);

  evel_terminate();
  printf("Terminated\n");
  return 0;
}

void *HeartbeatThread(void *threadarg)
{
 sleep(1);
 printf("Running HB thread \n");
 fflush(stdout);

 while(1)
 {
   EVENT_HEARTBEAT_FIELD * event = NULL;
   EVENT_HEADER* hb_header = NULL;
   EVEL_ERR_CODES evel_rc = EVEL_SUCCESS;

   /***************************************************************************/
   /* Heartbeat                                                               */
   /***************************************************************************/
   read_hb_config_file();
   char event_id1[10] = "heartbeat";
   char event_id2[15] = {0};
   char event_id[BUFSIZE] = {0};

   memset(event_id, 0, BUFSIZE);
   sprintf(event_id2, "%09d", gh_eventId++);
   strcat(event_id, event_id1);
   strcat(event_id, event_id2);

   event = evel_new_heartbeat_field(gh_interval, gh_event_name, event_id);

   if (event != NULL)
   {
     hb_header = (EVENT_HEADER *)event;

     if (g_event_type != NULL)
        evel_header_type_set(&event->header, g_event_type);

      struct timeval tv_now;
      gettimeofday(&tv_now, NULL);
      unsigned long long epoch_now = tv_now.tv_usec + 1000000 * tv_now.tv_sec;

      evel_start_epoch_set(&event->header, epoch_start);
      evel_last_epoch_set(&event->header, epoch_now);
      epoch_start = epoch_now;

      if(g_nfc_nam_code != NULL)
        evel_nfcnamingcode_set(&event->header, g_nfc_nam_code);
      if(g_nf_nam_code != NULL)
        evel_nfnamingcode_set(&event->header, g_nf_nam_code);
      evel_reporting_entity_name_set(&event->header, g_report_entity_name);
      if(g_report_entity_id != NULL)
        evel_reporting_entity_id_set(&event->header, g_report_entity_id);
      if(g_timezone != NULL)
        evel_time_zone_offset_set(&event->header, g_timezone);
      if(g_nf_vendor_name != NULL)
        evel_nf_vendor_name_set(&event->header, g_nf_vendor_name);
      if(g_source_id != NULL )
        evel_source_id_set(&event->header, g_source_id);
      if(g_source_name!= NULL )
        evel_source_name_set(&event->header, g_source_name);

      evel_rc = evel_post_event(hb_header);
      if (evel_rc != EVEL_SUCCESS)
      {
        EVEL_ERROR("Post failed %d (%s)", evel_rc, evel_error_string());
      }
   }
   else
   {
     EVEL_ERROR("New Heartbeat failed");
   }
   printf("   Processed Heartbeat\n");

   sleep(gh_interval);
 }
}

void *FaultThread(void *interfaceId)
{
  EVEL_ERR_CODES evel_rc = EVEL_SUCCESS;
  EVENT_FAULT * fault = NULL;
  EVENT_HEADER* fault_header = NULL;
  int bytes_in;
  int bytes_out;
  int packets_in;
  int packets_out;
  unsigned long long epoch_now;

  struct timeval time_val;
  char event_id1[10] = "fault";
  char event_id2[15] = {0};
  char event_id[BUFSIZE] = {0};

  sleep(1);
  printf("Running Measurement thread \n");
  fflush(stdout);

  memset(&fault_intfstat[0],0,(sizeof(vpp_metrics_struct)* MAX_INTERFACES));
  memset(&fault_linkstat[0],0,(sizeof(LINKSTAT) * MAX_INTERFACES));

  read_fault_config_file();
  read_vpp_metrics(fault_intfstat, fault_linkstat, gf_linkcount);

  gettimeofday(&time_val, NULL);

  sleep(gf_faultCheckInterval);

  /***************************************************************************/
  /* Collect metrics from the VNIC                                           */
  /***************************************************************************/
  while(1) {
    read_fault_config_file();
    read_vpp_metrics(fault_intfstat, fault_linkstat, gf_linkcount);

    for (int i = 0; i < gm_linkcount; i++)
    {
      if(fault_intfstat[i].curr_bytes_in - fault_intfstat[i].last_bytes_in > 0) {
        bytes_in = fault_intfstat[i].curr_bytes_in - fault_intfstat[i].last_bytes_in;
      }
      else {
        bytes_in = 0;
      }
      if(fault_intfstat[i].curr_bytes_out - fault_intfstat[i].last_bytes_out > 0) {
        bytes_out = fault_intfstat[i].curr_bytes_out - fault_intfstat[i].last_bytes_out;
      }
      else {
        bytes_out = 0;
      }
      if(fault_intfstat[i].curr_packets_in - fault_intfstat[i].last_packets_in > 0) {
        packets_in = fault_intfstat[i].curr_packets_in - fault_intfstat[i].last_packets_in;
      }
      else {
        packets_in = 0;
      }
      if(fault_intfstat[i].curr_packets_out - fault_intfstat[i].last_packets_out > 0) {
        packets_out = fault_intfstat[i].curr_packets_out - fault_intfstat[i].last_packets_out;
      }
      else {
        packets_out = 0;
      }
      if (((bytes_in < gf_lowWaterMark) || (bytes_out < gf_lowWaterMark) || 
          (packets_in < gf_lowWaterMark) || (packets_out < gf_lowWaterMark)) &&
          (fault_linkstat[i].fault_raised == 0)) 
      {
        memset(event_id, 0, BUFSIZE);
        sprintf(event_id2, "%09d", (i+1));
        strcat(event_id, event_id1);
        strcat(event_id, event_id2);

        fault = evel_new_fault(gf_event_name, event_id, "linkDown", 
                               "Transmit-Receive issue", 
                               EVEL_PRIORITY_MEDIUM, EVEL_SEVERITY_MAJOR, 
                               EVEL_SOURCE_HOST,EVEL_VF_STATUS_IDLE);
        if (fault != NULL)
        {
          fault_linkstat[i].fault_raised = 1;

          struct timeval tv_now;
          gettimeofday(&tv_now, NULL);
          epoch_now = tv_now.tv_usec + 1000000 * tv_now.tv_sec;
          fault_linkstat[i].last_epoch = epoch_now;

          fault_header = (EVENT_HEADER *)fault;
          evel_fault_category_set(fault, "link");
          evel_fault_interface_set(fault, fault_linkstat[i].linkname);
  
          if (g_event_type != NULL)
            evel_fault_type_set(fault, g_event_type); 
    
          evel_start_epoch_set(&fault->header, epoch_now);
          evel_last_epoch_set(&fault->header, epoch_now);
          if(g_nfc_nam_code != NULL)
            evel_nfcnamingcode_set(&fault->header, g_nfc_nam_code);
          if(g_nf_nam_code != NULL)
            evel_nfnamingcode_set(&fault->header, g_nf_nam_code);
          evel_reporting_entity_name_set(&fault->header, g_report_entity_name);
          if(g_report_entity_id != NULL)
            evel_reporting_entity_id_set(&fault->header, g_report_entity_id);
          if(g_timezone != NULL)
            evel_time_zone_offset_set(&fault->header, g_timezone);
          if(g_nf_vendor_name != NULL)
            evel_nf_vendor_name_set(&fault->header, g_nf_vendor_name);
          if(g_source_id != NULL )
          evel_source_id_set(&fault->header, g_source_id);
          if(g_source_name!= NULL )
            evel_source_name_set(&fault->header, g_source_name);
    
          evel_rc = evel_post_event(fault_header);

          if(evel_rc == EVEL_SUCCESS) {
            printf("Fault event is correctly sent to the collector!\n");
          }
          else {
            printf("Post failed %d (%s)\n", evel_rc, evel_error_string());
        }
      }
      else {
        printf("New new fault failed (%s)\n", evel_error_string());
      }
    }
    else if (((bytes_in > gf_lowWaterMark) && (bytes_out > gf_lowWaterMark) && 
          (packets_in > gf_lowWaterMark) && (packets_out > gf_lowWaterMark)) &&
          (fault_linkstat[i].fault_raised == 1)) 
    {
        memset(event_id, 0, BUFSIZE);
        sprintf(event_id2, "%09d", (i+1));
        strcat(event_id, event_id1);
        strcat(event_id, event_id2);

        fault = evel_new_fault(gf_event_name, event_id, "linkDown", 
                               "Transmit-Receive issue", 
                               EVEL_PRIORITY_MEDIUM, EVEL_SEVERITY_NORMAL, 
                               EVEL_SOURCE_HOST, EVEL_VF_STATUS_ACTIVE);
        if (fault != NULL)
        {
          fault_linkstat[i].fault_raised = 0;

          struct timeval tv_now;
          gettimeofday(&tv_now, NULL);
          epoch_now = tv_now.tv_usec + 1000000 * tv_now.tv_sec;

          fault_header = (EVENT_HEADER *)fault;
          evel_fault_category_set(fault, "link");
          evel_fault_interface_set(fault, fault_linkstat[i].linkname);
  
          if (g_event_type != NULL)
            evel_fault_type_set(fault, g_event_type); 
    
          evel_start_epoch_set(&fault->header, fault_linkstat[i].last_epoch);
          evel_last_epoch_set(&fault->header, epoch_now);
          fault_linkstat[i].last_epoch = 0;

          if(g_nfc_nam_code != NULL)
            evel_nfcnamingcode_set(&fault->header, g_nfc_nam_code);
          if(g_nf_nam_code != NULL)
            evel_nfnamingcode_set(&fault->header, g_nf_nam_code);
          evel_reporting_entity_name_set(&fault->header, g_report_entity_name);
          if(g_report_entity_id != NULL)
            evel_reporting_entity_id_set(&fault->header, g_report_entity_id);
          if(g_timezone != NULL)
            evel_time_zone_offset_set(&fault->header, g_timezone);
          if(g_nf_vendor_name != NULL)
            evel_nf_vendor_name_set(&fault->header, g_nf_vendor_name);
          if(g_source_id != NULL )
          evel_source_id_set(&fault->header, g_source_id);
          if(g_source_name!= NULL )
            evel_source_name_set(&fault->header, g_source_name);
    
          evel_rc = evel_post_event(fault_header);

          if(evel_rc == EVEL_SUCCESS) {
            printf("Fault event is correctly sent to the collector!\n");
          }
          else {
            printf("Post failed %d (%s)\n", evel_rc, evel_error_string());
        }
      }
      else {
        printf("New fault failed (%s)\n", evel_error_string());
      }

    }
    }

    sleep(gf_faultCheckInterval);
  }

  /***************************************************************************/
  /* Terminate                                                               */
  /***************************************************************************/
  sleep(1);
}

void *MeasureThread(void *interfaceId)
{
  EVEL_ERR_CODES evel_rc = EVEL_SUCCESS;
  EVENT_MEASUREMENT* vpp_m = NULL;
  EVENT_HEADER* vpp_m_header = NULL;
  int bytes_in;
  int bytes_out;
  int packets_in;
  int packets_out;

  struct timeval time_val;
  MEASUREMENT_NIC_PERFORMANCE * vnic_performance = NULL;
  //struct timeval tv_start;
  char event_id1[10] = "mvfs";
  char event_id2[15] = {0};
  char event_id[BUFSIZE] = {0};

  printf("\nVector Packet Processing (VPP) measurement collection\n");
  fflush(stdout);

  memset(&meas_intfstat[0],0,(sizeof(vpp_metrics_struct) * MAX_INTERFACES));
  memset(&meas_linkstat[0],0,(sizeof(LINKSTAT) * MAX_INTERFACES));

  read_meas_config_file();

  read_vpp_metrics(meas_intfstat, meas_linkstat, gm_linkcount);

  gettimeofday(&time_val, NULL);
  epoch_start = time_val.tv_sec * 1000000 + time_val.tv_usec;

  sleep(gm_interval);

  /***************************************************************************/
  /* Collect metrics from the VNIC                                           */
  /***************************************************************************/
  while(1) {
    request_rate = rand()%10000;
    read_meas_config_file();
    read_vpp_metrics(meas_intfstat, meas_linkstat, gm_linkcount);

    memset(event_id, 0, BUFSIZE);
    sprintf(event_id2, "%09d", gm_eventId++);
    strcat(event_id, event_id1);
    strcat(event_id, event_id2);

    vpp_m = evel_new_measurement(gm_interval, gm_event_name, event_id);

    if(vpp_m != NULL) {
      printf("New measurement report created...\n");
      if (g_event_type != NULL)
        evel_measurement_type_set(vpp_m, g_event_type);

      for (int i = 0; i < gm_linkcount; i++)
      {
        if(meas_intfstat[i].curr_bytes_in - meas_intfstat[i].last_bytes_in > 0) {
          bytes_in = meas_intfstat[i].curr_bytes_in - meas_intfstat[i].last_bytes_in;
        }
        else {
          bytes_in = 0;
        }
        if(meas_intfstat[i].curr_bytes_out - meas_intfstat[i].last_bytes_out > 0) {
          bytes_out = meas_intfstat[i].curr_bytes_out - meas_intfstat[i].last_bytes_out;
        }
        else {
          bytes_out = 0;
        }
        if(meas_intfstat[i].curr_packets_in - meas_intfstat[i].last_packets_in > 0) {
          packets_in = meas_intfstat[i].curr_packets_in - meas_intfstat[i].last_packets_in;
        }
        else {
          packets_in = 0;
        }
        if(meas_intfstat[i].curr_packets_out - meas_intfstat[i].last_packets_out > 0) {
          packets_out = meas_intfstat[i].curr_packets_out - meas_intfstat[i].last_packets_out;
        }
        else {
          packets_out = 0;
        }
        vnic_performance = (MEASUREMENT_NIC_PERFORMANCE *)evel_measurement_new_nic_performance(meas_linkstat[i].linkname, "true");
        evel_meas_nic_performance_add(vpp_m, vnic_performance);
        evel_nic_performance_rx_total_pkt_delta_set(vnic_performance, packets_in);
        evel_nic_performance_tx_total_pkt_delta_set(vnic_performance, packets_out);

        evel_nic_performance_rx_octets_delta_set(vnic_performance, bytes_in);
        evel_nic_performance_tx_octets_delta_set(vnic_performance, bytes_out);

        if (strcmp(meas_linkstat[i].linkname, "docker") == 0)
        {
          request_rate = measure_traffic();
        }
      }
      evel_measurement_request_rate_set(vpp_m, request_rate);

      evel_get_cpu_stats(vpp_m);

      /***************************************************************************/
      /* Set parameters in the MEASUREMENT header packet                         */
      /***************************************************************************/
      struct timeval tv_now;
      gettimeofday(&tv_now, NULL);
      unsigned long long epoch_now = tv_now.tv_usec + 1000000 * tv_now.tv_sec;

      //last_epoch = start_epoch + READ_INTERVAL * 1000000;
      vpp_m_header = (EVENT_HEADER *)vpp_m;
      //vpp_m_header->start_epoch_microsec = start_epoch;
      //vpp_m_header->last_epoch_microsec = last_epoch;
      evel_start_epoch_set(&vpp_m->header, epoch_start);
      evel_last_epoch_set(&vpp_m->header, epoch_now);
      epoch_start = epoch_now;
      if(g_nfc_nam_code != NULL)
        evel_nfcnamingcode_set(&vpp_m->header, g_nfc_nam_code);
      if(g_nf_nam_code != NULL)
        evel_nfnamingcode_set(&vpp_m->header, g_nf_nam_code);
      //strcpy(vpp_m_header->reporting_entity_id.value, "No UUID available");
      //strcpy(vpp_m_header->reporting_entity_name, hostname);
      evel_reporting_entity_name_set(&vpp_m->header, g_report_entity_name);
      if(g_report_entity_id != NULL)
        evel_reporting_entity_id_set(&vpp_m->header, g_report_entity_id);
      if(g_timezone != NULL)
        evel_time_zone_offset_set(&vpp_m->header, g_timezone);
      if(g_nf_vendor_name != NULL)
        evel_nf_vendor_name_set(&vpp_m->header, g_nf_vendor_name);
      if(g_source_id != NULL )
        evel_source_id_set(&vpp_m->header, g_source_id);
      if(g_source_name!= NULL )
        evel_source_name_set(&vpp_m->header, g_source_name);

      evel_rc = evel_post_event(vpp_m_header);

      if(evel_rc == EVEL_SUCCESS) {
        printf("Measurement report correctly sent to the collector!\n");
      }
      else {
        printf("Post failed %d (%s)\n", evel_rc, evel_error_string());
      }
    }
    else {
      printf("New measurement report failed (%s)\n", evel_error_string());
    }

    sleep(gm_interval);
  }

  /***************************************************************************/
  /* Terminate                                                               */
  /***************************************************************************/
  sleep(1);
}

void read_vpp_metrics(vpp_metrics_struct *intfstats, LINKSTAT *linkstat, int linkcount) 
{
  // Define an array of char that contains the parameters of the unix 'cut' command
  char* params[] = {"-f3", "-f11", "-f4", "-f12"};
  // Define the unix command to execute in order to read metrics from the vNIC
  char* cmd_prefix = "sudo cat /proc/net/dev | grep \"";
  char* cmd_mid = "\" | tr -s \' \' | cut -d\' \' ";
  char cmd[BUFSIZE];
  // Define other variables
  char buf[BUFSIZE];		/* buffer used to store VPP metrics 	*/
  int temp[] = {0, 0, 0, 0};	/* temp array that contains VPP values 	*/
  FILE *fp;			/* file descriptor to pipe cmd to shell */
  int i, j;

  for(i = 0; i < linkcount; i++)
  {
    for(j = 0; j < 4; j++) {
      // Clear buffers
      memset(buf, 0, BUFSIZE);
      memset(cmd, 0, BUFSIZE);
      // Build shell command to read metrics from the vNIC
      strcat(cmd, cmd_prefix);
      strcat(cmd, linkstat[i].linkname);
      strcat(cmd, cmd_mid);
      strcat(cmd, params[j]);
    
      // Open a pipe and read VPP values
      if ((fp = popen(cmd, "r")) == NULL) {
          printf("Error opening pipe!\n");
          return;
      }

      while (fgets(buf, BUFSIZE, fp) != NULL);
      temp[j] = atoi(buf);

      if(pclose(fp))  {
          printf("Command not found or exited with error status\n");
          return;
      }
    }
    // Store the current metric in the last metric
    intfstats[i].last_bytes_in = intfstats[i].curr_bytes_in;
    intfstats[i].last_bytes_out = intfstats[i].curr_bytes_out;
    intfstats[i].last_packets_in = intfstats[i].curr_packets_in;
    intfstats[i].last_packets_out = intfstats[i].curr_packets_out;

    // Store metrics read from the vNIC in the current 
    intfstats[i].curr_bytes_in = temp[0];
    intfstats[i].curr_bytes_out = temp[1];
    intfstats[i].curr_packets_in = temp[2];
    intfstats[i].curr_packets_out = temp[3];
  }
}
