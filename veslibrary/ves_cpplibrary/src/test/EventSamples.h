#pragma once

#include "XFaultFields.h"
#include "XHeartbeatFields.h"
#include "XMeasurementFields.h"
#include "XNotificationFields.h"
#include "XOtherFields.h"
#include "XPnfRegistrationFields.h"
#include "XStateChangeFields.h"
#include "XSyslogFields.h"
#include "XThresholdCrossingAlertFields.h"
#include "XVoiceQualityFields.h"
#include "XBatch.h"
#include "XMobileFlowFields.h"
#include "XSipSignalingFields.h"

using namespace std;
using namespace vagt;
using namespace vagt::encode;

shared_ptr<XSerialable> buildFault();
shared_ptr<XSerialable> buildHeartbeat();
shared_ptr<XSerialable> buildMeasurement();
shared_ptr<XSerialable> buildNotification();
shared_ptr<XSerialable> buildOther();
shared_ptr<XSerialable> buildPnfRegistration();
shared_ptr<XSerialable> buildStateChange();
shared_ptr<XSerialable> buildSyslog();
shared_ptr<XSerialable> buildThresholdCrossingAlert();
shared_ptr<XSerialable> buildXVoiceQuality();
shared_ptr<XSerialable> buildBatch();
shared_ptr<XSerialable> buildMobileFlow();
shared_ptr<XSerialable> buildSipSignaling();

