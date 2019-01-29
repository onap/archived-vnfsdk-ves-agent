# EVEL Library Overview {#mainpage}

# Introduction

The ECOMP Vendor Event Listener ("EVEL") library encapsulates the use of
AT&T's JSON API to the collector function within the ECOMP infrastructure.

As such, it provides a reference implementation of the EVEL JSON API which
can either be directly as part of a project or can be used to inform the
independent implementation of an equivalent binding to the API in another
development environment.

This section provides an overview of the library and how it is integrated
into the target application.  If all you want is a set of instructions to
get you started, the @ref quickstart "Quick Start" section is for you.  If
you want a more in-depth understanding of the _EVEL Library_ then this section
provides an overview and then you can read the detailed API documentation for 
each function. The documentation for evel.h is a good starting point, since 
that defines the public API of the _EVEL Library_.

# Library Structure 

The API is designed to be used on multi-process platforms where each process
may be multi-threaded.  Each process using this library will create an
independent HTTP client (using libcURL).  Each process will have a single
thread running the HTTP client but that thread receives work on a
ring-buffer from however may threads are required to implement the function.

**Note**: libcurl imposes a constraint that it is initialized before
the process starts multi-threaded operation.

# Typical Usage

The library is designed to be very straightforward to use and lightweight to
integrate into projects. The only serious external dependency is on libcURL.

The supplied Makefile produces a single library **libevel.so** or
**libevel.a** which your application needs to be linked against.

Each process within the application which wants to generate events needs to
call ::evel_initialize at the start of day (observing the above warning
about not being MT safe at this stage.)   The initialization specifies the
details of where the API is located.  Management of configuration is the
responsibility of the client.

Once initialized, and now MT-safe, there are factory functions to produce
new events:
- Faults  - ::evel_new_fault
- Measurements - ::evel_new_measurement
- State Change - ::evel_new_state_change
- Syslog - ::evel_new_syslog
- Other - ::evel_new_other
- Mobile Flow - ::evel_new_mobile_flow
- Notification - ::evel_new_notification
- PNF Registration - ::evel_new_pnf_registration
- SIP Signaling - ::evel_new_signaling
- Threshold Crossing Alert - ::evel_new_threshold_cross
- Voice Quality - ::evel_new_voice_quality

There is also a factory function ::evel_new_mobile_gtp_flow_metrics to create
the parameter gtp_per_flow_metrics, which is then configured and passed to the
::evel_new_mobile_flow factory function.

The event structures are initialized with mandatory fields at the point of
creation and optional fields may be added thereafter.  Once set, values in
the structures are immutable.

Once the event is prepared, it may be posted, using ::evel_post_event,  at
which point the calling thread relinquishes all responsibility for the
event.  It will be freed once successfully or unsuccessfully posted to the
API.  If, for any reason, you change your mind and don't want to post a
created event, it must be destroyed with ::evel_free_event.

Finally, at the end of day, the library can be terminated cleanly by calling
::evel_terminate.

## Example Code

The following fragment illustrates the above usage:

```C

  if(evel_initialize(fqdn,                         /* FQDN                  */
                     port,                         /* Port                  */
                     fqdn2,                        /* Backup FQDN           */
                     port2,                        /* Backup port           */
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
                     "",                           /* Username              */
                     "",                           /* Password              */
                     "",                           /* Username2             */
                     "",                           /* Password2             */
                     NULL,                         /* Source ip             */
                     NULL,                         /* Source ip2            */
                     EVEL_SOURCE_VIRTUAL_MACHINE,  /* Source type           */
                     "EVEL demo client",           /* Role                  */
                     verbose_mode))                /* Verbosity             */
  {
    fprintf(stderr, "Failed to initialize the EVEL library!!!");
    exit(-1);
  }

  ...

 fault = evel_new_fault("fault_eNodeB_alarm",
                         "fault000000001",
                         "My alarm condition",
                         "It broke very badly",
                         EVEL_PRIORITY_NORMAL,
                         EVEL_SEVERITY_MAJOR,
                         EVEL_SOURCE_HOST,
                         EVEL_VF_STATUS_READY_TERMINATE);
  if (fault != NULL)
  {
    evel_fault_type_set(fault, "Bad things happen...");
    evel_fault_interface_set(fault, "My Interface Card");
    evel_fault_addl_info_add(fault, "name1", "value1");
    evel_fault_addl_info_add(fault, "name2", "value2");
    evel_rc = evel_post_event((EVENT_HEADER *)fault);
    if (evel_rc != EVEL_SUCCESS)
    {
      EVEL_ERROR("Post failed %d (%s)", evel_rc, evel_error_string());
    }
  }

```

The public API to the library is defined in evel.h.  The internal APIs
within library are defined in separate headers (<em>e.g.</em>
evel_internal.h), but these should not need to be included by the code
using the library.

# Restrictions and Limitations

## Constraint Validation

The _EVEL Library_ has been designed to be production-safe code with the
emphasis at this stage being in correctness of operation rather than
raw performance.

The API tries to check as much information as possible to avoid misuse and
will **assert()** if constraints are not satisfied.  This is likely to lead
to the rapid discovery of coding errors by programmers, but does mean that
the application can fail abruptly if the library is misused in any way.

## Performance

The default Makefile avoids aggressive optimizations so that any core-files
are easy to interpret.  Production code should use greater optimization
levels.

As described above, the HTTP client is single threaded and will run all
transactions synchronously.  As transactions are serialized, a client that
generates a lot of events will be paced by the round-trip time.

It would be a straightforward enhancement to use the multi-thread API into
libcurl and use a pool of client threads to run transactions in parallel if
this ever became a bottleneck.

## Logging

The initialization of the library includes the log verbosity.  The verbose
operation makes the library very chatty so syslog may get rather clogged
with detailed diagnostics.  It is possible to configure syslog to put these
events into a separate file.  A trivial syslog.conf file would be:

```

# Log all user messages so debug information is captured.

user.*      /var/log/debug
```

If verbose logging is enabled, the cURL library will generate information 
about the HTTP operations on **stdout**. 

