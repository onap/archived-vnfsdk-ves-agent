#include "XEventSamples.h"

shared_ptr<XSerialable> buildFault()
{
    auto header = XCommonEventHeader::create(
        "EventName",
        "EventId",
        "SourceName",
        "ReportName",
        XEnumCommonEventHeaderPriorityNormal,
        111
        );

    auto fault = XFaultFields::create(header,
        "condition",
        "specProblem",
        XEnumFaultFieldsEventSourceTypeVirtualMachine,
        XEnumFaultFieldsEventSeverityNORMAL,
        XEnumFaultFieldsVfStatusActive);

    auto header2 = fault->getCommonHeader();
    header2->setSourceId("XXSourceID");

    fault->setAlarmInterfaceA("Interface");
    fault->setEventSeverity(XEnumFaultFieldsEventSeverityMAJOR);
    fault->setAlarmCondition("XXCondition");
    fault->setVfStatus(XEnumFaultFieldsVfStatusRequestingTermination);
    fault->setEventCategory("Category");
    fault->setEventSourceType(XEnumFaultFieldsEventSourceTypeVirtualMachine);
    fault->setSpecificProblem("XXProblem");
    XHashMap hm{ { "xxx","123" },{ "yyy","456" } };
    fault->setAlarmAdditionalInformation(hm);

    return fault;
}

shared_ptr<XSerialable> buildHeartbeat()
{
    auto header = XCommonEventHeader::create(
        "EventName",
        "EventId",
        "SourceName",
        "ReportName",
        XEnumCommonEventHeaderPriorityNormal,
        111
        );

    header->toString();
    header->setEventId("event id");
    header->setStartEpochMicrosec(0);
    header->setLastEpochMicrosec(0);
    header->setReportingEntityName("report name");
    header->setReportingEntityId("report id");
    header->setEventType("event type");
    header->setSequence(0);
    header->setInternalHeaderFields("{}");
    header->setPriority(XEnumCommonEventHeaderPriorityHigh);
    header->setSourceName("source name");
    header->setEventName("event name");
    header->setNfNamingCode("nf");
    header->setNfcNamingCode("nfc");
    header->setTimeZoneOffset("zone");
    header->setNfVendorName("vendor");

    auto event = XHeartbeatFields::create(header, 100);
    event->setHeartbeatInterval(11);
    XHashMap hm{ { "xxx","123" },{ "yyy","456" } };
    event->setAdditionalFields(hm);
    event->getCommonHeader();

    return event;
}

shared_ptr<XSerialable> buildMeasurement()
{
    auto header = XCommonEventHeader::create(
        "EventName",
        "EventId",
        "SourceName",
        "ReportName",
        XEnumCommonEventHeaderPriorityNormal,
        111
        );

    auto event = XMeasurementFields::create(header, 100.0);
    event->setMeasurementInterval(1);
    event->getCommonHeader();

    XHashMap hm{ { "xxx","123" },{ "yyy","456" } };

    {
        XCodecsInUse cd("xx",11);
        cd.setCodecIdentifier("zzz");
        cd.setNumberInUse(300);
        XArrayOfXCodecsInUse arr{ cd };
        event->setCodecUsageArray(arr);
    }

    event->setFeatureUsageArray(hm);
    event->setConfiguredEntities(100);

    {
        XArrayOfNamedHashMap arr{ { "name1", hm },{ "name2", hm } };
        event->setAdditionalMeasurements(arr);
    }

    {
        XArrayOfXCpuUsage arr;

        XCpuUsage u1("cpu1", 100);
        u1.setCpuUsageSystem(90);
        u1.setCpuCapacityContention(1);
        u1.setCpuDemandAvg(1);
        u1.setCpuDemandMhz(1);
        u1.setCpuDemandPct(1);
        u1.setCpuIdentifier("id");
        u1.setCpuIdle(1);
        u1.setCpuLatencyAvg(1);
        u1.setCpuOverheadAvg(1);
        u1.setCpuSwapWaitTime(1);
        u1.setCpuUsageInterrupt(1);
        u1.setCpuUsageNice(1);
        u1.setCpuUsageSoftIrq(1);
        u1.setCpuUsageSteal(1);
        u1.setCpuUsageUser(1);
        u1.setCpuWait(1);
        u1.setPercentUsage(1);

        XCpuUsage u2("cpu2", 10);
        u2.setCpuUsageSystem(99);

        arr.push_back(u1);
        arr.push_back(u2);
        event->setCpuUsageArray(arr);
    }

    event->setRequestRate(99);

    {
        XArrayOfXFilesystemUsage arr{ { "/root", 1, 2, 3, 4, 5, 6 },{ "/tmp", 1, 2, 3, 4, 5, 6 } };
        arr[0].setBlockConfigured(1);
        arr[0].setBlockUsed(1);
        arr[0].setEphemeralConfigured(1);
        arr[0].setEphemeralIops(1);
        arr[0].setBlockIops(1);
        arr[0].setEphemeralUsed(1);
        arr[0].setFilesystemName("/var");

        event->setFilesystemUsageArray(arr);
    }

    {
        XArrayOfXLoad arr;

        XLoad l1;
        l1.setLongTerm(100);
        l1.setMidTerm(50);

        XLoad l2;
        l2.setLongTerm(100);
        l2.setShortTerm(10);

        arr.push_back(l1);
        arr.push_back(l2);
        event->setLoadArray(arr);
    }

    {
        XArrayOfXMachineCheckException arr{ { "Machine1" } };

        XMachineCheckException m("Machine2");
        m.setCorrectedMemoryErrors(1);
        m.setUncorrectedMemoryErrors(1);
        m.setUncorrectedMemoryErrorsIn1Hr(1);
        m.setCorrectedMemoryErrorsIn1Hr(1);
        m.setVmIdentifier("xx");
        arr.push_back(m);

        event->setMachineCheckExceptionArray(arr);
    }

    event->setMeanRequestLatency(2000);
    event->setConcurrentSessions(300);
    event->setAdditionalFields(hm);
    {
        XArrayOfXProcessStats arr{ { "process1" } };

        XProcessStats p2("p2");
        p2.setForkRate(1);
        p2.setPsStateStopped(1);
        p2.setPsStatePaging(1);
        p2.setPsStateSleeping(1);
        p2.setProcessIdentifier("xx");
        p2.setPsStateBlocked(1);
        p2.setPsStateZombie(1);
        p2.setPsStateRunning(1);

        arr.push_back(p2);

        event->setProcessStatsArray(arr);
    }

    {
        XNicPerformance nic("Nic1", XEnumNicPerformanceValuesAreSuspectTrue );
        nic.setTransmittedErrorPacketsDelta(1);
        nic.setReceivedErrorPacketsAccumulated(1);
        nic.setTransmittedDiscardedPacketsDelta(1);
        nic.setReceivedOctetsDelta(1);
        nic.setReceivedMulticastPacketsDelta(1);
        nic.setTransmittedDiscardedPacketsAccumulated(1);
        nic.setTransmittedMulticastPacketsAccumulated(1);
        nic.setReceivedDiscardedPacketsDelta(1);
        nic.setReceivedOctetsAccumulated(1);
        nic.setTransmittedTotalPacketsAccumulated(1);
        nic.setTransmittedOctetsAccumulated(1);
        nic.setSpeed(1);
        nic.setReceivedDiscardedPacketsAccumulated(1);
        nic.setReceivedBroadcastPacketsDelta(1);
        nic.setReceivedPercentDiscard(1);
        nic.setTransmittedPercentDiscard(1);
        nic.setTransmittedErrorPacketsAccumulated(1);
        nic.setTransmittedBroadcastPacketsAccumulated(1);
        nic.setReceivedTotalPacketsAccumulated(1);
        nic.setReceivedUnicastPacketsAccumulated(1);
        nic.setTransmittedBroadcastPacketsDelta(1);
        nic.setTransmittedMulticastPacketsDelta(1);
        nic.setReceivedMulticastPacketsAccumulated(1);
        nic.setReceivedTotalPacketsDelta(1);
        nic.setReceivedPercentError(1);
        nic.setReceivedErrorPacketsDelta(1);
        nic.setTransmittedOctetsDelta(1);
        nic.setNicIdentifier("xx");
        nic.setTransmittedUnicastPacketsAccumulated(1);
        nic.setReceivedUnicastPacketsDelta(1);
        nic.setTransmittedUtilization(1);
        nic.setReceivedBroadcastPacketsAccumulated(1);
        nic.setTransmittedUnicastPacketsDelta(1);
        nic.setReceivedUtilization(1);
        nic.setTransmittedPercentError(1);
        nic.setTransmittedTotalPacketsDelta(1);
        nic.setValuesAreSuspect(XEnumNicPerformanceValuesAreSuspectFalse);
        nic.setOperationalState(XEnumNicPerformanceOperationalStateInService);
        nic.setAdministrativeState(XEnumNicPerformanceAdministrativeStateInService);

        XArrayOfXNicPerformance arr{ nic };

        event->setNicPerformanceArray(arr);
    }

    {
        XArrayOfXDiskUsage arr{ { "d1" } };

        XDiskUsage d2("d2");

        d2.setDiskOctetsWriteLast(1);
        d2.setDiskIoTimeAvg(1);
        d2.setDiskMergedReadMin(1);
        d2.setDiskTotalReadLatencyAvg(1);
        d2.setDiskOpsReadMax(1);
        d2.setDiskOpsReadMin(1);
        d2.setDiskBusResets(1);
        d2.setDiskMergedReadLast(1);
        d2.setDiskTimeReadAvg(1);
        d2.setDiskMergedWriteMax(1);
        d2.setDiskTime(1);
        d2.setDiskOpsWriteLast(1);
        d2.setDiskOpsReadAvg(1);
        d2.setDiskFlushRequests(1);
        d2.setDiskFlushTime(1);
        d2.setDiskOpsReadLast(1);
        d2.setDiskMergedReadAvg(1);
        d2.setDiskWriteCommandsAvg(1);
        d2.setDiskTimeReadMin(1);
        d2.setDiskOpsWriteAvg(1);
        d2.setDiskWeightedIoTimeMin(1);
        d2.setDiskIoTimeLast(1);
        d2.setDiskMergedReadMax(1);
        d2.setDiskOctetsReadMin(1);
        d2.setDiskWeightedIoTimeAvg(1);
        d2.setDiskTimeWriteMin(1);
        d2.setDiskCommandsAvg(1);
        d2.setDiskTimeWriteMax(1);
        d2.setDiskPendingOperationsMin(1);
        d2.setDiskTimeReadMax(1);
        d2.setDiskOctetsReadMax(1);
        d2.setDiskOpsWriteMin(1);
        d2.setDiskReadCommandsAvg(1);
        d2.setDiskMergedWriteMin(1);
        d2.setDiskOctetsWriteMax(1);
        d2.setDiskTimeWriteLast(1);
        d2.setDiskPendingOperationsLast(1);
        d2.setDiskWeightedIoTimeLast(1);
        d2.setDiskIdentifier("id");
        d2.setDiskOctetsWriteMin(1);
        d2.setDiskTimeWriteAvg(1);
        d2.setDiskOctetsWriteAvg(1);
        d2.setDiskOctetsReadLast(1);
        d2.setDiskWeightedIoTimeMax(1);
        d2.setDiskCommandsAborted(1);
        d2.setDiskOpsWriteMax(1);
        d2.setDiskTimeReadLast(1);
        d2.setDiskMergedWriteAvg(1);
        d2.setDiskOctetsReadAvg(1);
        d2.setDiskTotalWriteLatencyAvg(1);
        d2.setDiskIoTimeMax(1);
        d2.setDiskIoTimeMin(1);
        d2.setDiskPendingOperationsAvg(1);
        d2.setDiskMergedWriteLast(1);
        d2.setDiskPendingOperationsMax(1);
    
        arr.push_back(d2);
        event->setDiskUsageArray(arr);
    }

    {
        XIpmi ipmi;

        XIpmiBattery battery("id");
        battery.setBatteryIdentifier("id");
        battery.setBatteryType("xx");
        battery.setBatteryVoltageLevel(1);
        XArrayOfXIpmiBattery batteries{ battery };
        ipmi.setIpmiBatteryArray(batteries);

        XIpmiHsbp hsbp("id");
        hsbp.setHsbpIdentifier("xx");
        hsbp.setHsbpTemperature(1);
        ipmi.setIpmiHsbpArray({hsbp});

        ipmi.setSystemAirflow(100);

        XArrayOfXIpmiFan fans{ { "fan1" } };
        XIpmiFan fan("fan2");
        fan.setFanSpeed(100);
        fan.setFanIdentifier("xx");
        fans.push_back(fan);
        ipmi.setIpmiFanArray(fans);

        XArrayOfXIpmiProcessor processors{ { "processor1" } };
        XIpmiProcessor processor2("processor2");
        processor2.setProcessorThermalControlPercent(90);
        processor2.setProcessorDtsThermalMargin(80);
        processor2.setProcessorIdentifier("xx");

        XArrayOfXProcessorDimmAggregateThermalMargin margins{ { "m1",1 },{ "m2",2 } };
        margins[0].setThermalMargin(1);
        margins[0].setProcessorDimmAggregateThermalMarginIdentifier("xx");

        processor2.setProcessorDimmAggregateThermalMarginArray(margins);
        processors.push_back(processor2);
        ipmi.setIpmiProcessorArray(processors);

        ipmi.setExitAirTemperature(36.5);


        XArrayOfXIpmiBaseboardVoltageRegulator vols{ { "vol1" } };
        XIpmiBaseboardVoltageRegulator vol2("vol2");
        vol2.setVoltageRegulatorTemperature(70);
        vol2.setBaseboardVoltageRegulatorIdentifier("xx");
        vols.push_back(vol2);
        ipmi.setIpmiBaseboardVoltageRegulatorArray(vols);

        XArrayOfXIpmiGlobalAggregateTemperatureMargin ts{ { "t1",11 },{ "t2", 22 } };
        ts[0].setGlobalAggregateTemperatureMargin(1);
        ts[0].setIpmiGlobalAggregateTemperatureMarginIdentifier("xx");

        ipmi.setIpmiGlobalAggregateTemperatureMarginArray(ts);

        XArrayOfXIpmiNic nics{ { "nic1" } };
        XIpmiNic nic2{ "nic2" };
        nic2.setNicTemperature(333);
        nic2.setNicIdentifier("xx");
        nics.push_back(nic2);
        ipmi.setIpmiNicArray(nics);

        XArrayOfXIpmiBaseboardTemperature bts{ { "t1" } };
        XIpmiBaseboardTemperature bt2("b2");
        bt2.setBaseboardTemperature(55);
        bt2.setBaseboardTemperatureIdentifier("xx");

        bts.push_back(bt2);
        ipmi.setIpmiBaseboardTemperatureArray(bts);

        XArrayOfXIpmiPowerSupply pss{ { "p1" } };
        XIpmiPowerSupply ps2("p2");
        ps2.setPowerSupplyCurrentOutputPercent(1);
        ps2.setPowerSupplyInputPower(2);
        ps2.setPowerSupplyTemperature(3);
        ps2.setPowerSupplyIdentifier("xx");
        pss.push_back(ps2);
        ipmi.setIpmiPowerSupplyArray(pss);

        ipmi.setIoModuleTemperature(66);
        ipmi.setFrontPanelTemperature(1);

        event->setIpmi(ipmi);
    }

    {
        XArrayOfXLatencyBucketMeasure arr{ 1 };
        XLatencyBucketMeasure lat2(2);
        lat2.setCountsInTheBucket(100);
        lat2.setHighEndOfLatencyBucket(1000);
        lat2.setLowEndOfLatencyBucket(1);
        arr.push_back(lat2);

        event->setLatencyDistribution(arr);
    }

    {
        XArrayOfXHugePages arr{ { "h1" } };
        XHugePages h2("h2");
        h2.setBytesUsed(100);
        h2.setVmPageNumberFree(1);
        h2.setBytesFree(1);
        h2.setPercentFree(1);
        h2.setPercentUsed(1);
        h2.setVmPageNumberUsed(1);
        h2.setHugePagesIdentifier("h2");

        arr.push_back(h2);
        event->setHugePagesArray(arr);
    }

    event->setNumberOfMediaPortsInUse(111);
    event->setNfcScalingMetric(222);

    {
        XArrayOfXMemoryUsage arr{ { "mem1", 100, 200 } };
        XMemoryUsage mem2("mem2", 2, 3);
        mem2.setMemorySwapInAvg(1);
        mem2.setMemorySwapUsedAvg(1);
        mem2.setMemorySlabRecl(1);
        mem2.setMemorySwapInRateAvg(1);
        mem2.setMemoryDemand(1);
        mem2.setMemoryConfigured(1);
        mem2.setMemorySharedAvg(1);
        mem2.setVmIdentifier("xx");
        mem2.setMemoryLatencyAvg(1);
        mem2.setMemorySwapOutAvg(1);
        mem2.setMemorySwapOutRateAvg(1);
        mem2.setMemoryFree(1);
        mem2.setMemorySlabUnrecl(1);
        mem2.setMemoryCached(1);
        mem2.setMemoryUsed(1);
        mem2.setMemoryBuffered(1);
        mem2.setPercentMemoryUsage(1);

        arr.push_back(mem2);
        event->setMemoryUsageArray(arr);
    }

    {
        XArrayOfJsonObject objs;

        XArrayOfXJsonObjectInstance ins;
        XArrayOfXJsonObjectInstance ins2;

        XJsonObject obj2("obj2", ins2);
        obj2.setObjectSchema("xx");
        obj2.setObjectName("xx");
        obj2.setNfSubscribedObjectName("xx");
        obj2.setNfSubscriptionId("xx");
        obj2.setObjectSchemaUrl("xx");
        obj2.setObjectInstances(ins2);

        XJsonObjectInstance ins1;
        ins1.setJsonObject(obj2);
        ins1.setObjectInstance(R"({"aa":"bb"})");
        ins1.setObjectInstanceEpochMicrosec(111);
        XArrayOfXKey keys{ { "k1" } };
        XKey k2("k2");
        k2.setKeyName("keyname");
        k2.setKeyOrder(11);
        k2.setKeyValue("value");
        keys.push_back(k2);
        ins1.setObjectKeys(keys);

        ins.push_back(ins1);

        XJsonObject obj("obj1", ins);
        objs.push_back(obj);

        event->setAdditionalObjects(objs);
    }

    return event;
}

shared_ptr<XSerialable> buildNotification()
{
    auto header = XCommonEventHeader::create(
        "EventName",
        "EventId",
        "SourceName",
        "ReportName",
        XEnumCommonEventHeaderPriorityNormal,
        111
        );

    auto event = XNotificationFields::create(header, "notif", "removed");
    event->getCommonHeader();
    event->setNewState("xx");
    event->setChangeType("xx");
    event->setChangeContact("xx");
    event->setChangeIdentifier("xx");
    event->setAdditionalFields({ { "xxx","123" },{ "yyy","456" } });
    event->setOldState("xx");
    event->setStateInterface("xx");
    XNamedHashMap nhm("xx", { { "xxx","123" },{ "yyy","456" } });
    nhm.setName("xx");
    nhm.setHashMap({ { "xxx","123" },{ "yyy","456" } });
    event->setArrayOfNamedHashMap({nhm});

    return event;
}

shared_ptr<XSerialable> buildOther()
{
    auto header = XCommonEventHeader::create(
        "EventName",
        "EventId",
        "SourceName",
        "ReportName",
        XEnumCommonEventHeaderPriorityNormal,
        111
        );

    auto event = XOtherFields::create(header);
    XHashMap hm{ { "xxx","123" },{ "yyy","456" } };
    XArrayOfNamedHashMap arr{ { "name1", hm },{ "name2", hm } };

    event->setHashMap(hm);
    event->setArrayOfNamedHashMap(arr);

    {
        XArrayOfJsonObject objs;

        XArrayOfXJsonObjectInstance ins;
        XArrayOfXJsonObjectInstance ins2;

        XJsonObject obj2("obj2", ins2);

        XJsonObjectInstance ins1;
        ins1.setJsonObject(obj2);
        ins1.setObjectInstance(R"({"aa":"bb"})");
        ins1.setObjectInstanceEpochMicrosec(111);
        XArrayOfXKey keys{ { "k1" } };
        XKey k2("k2");
        k2.setKeyName("keyname");
        k2.setKeyOrder(11);
        k2.setKeyValue("value");
        keys.push_back(k2);
        ins1.setObjectKeys(keys);

        ins.push_back(ins1);

        XJsonObject obj("obj1", ins);
        objs.push_back(obj);

        event->setJsonObjects(objs);
    }
    event->getCommonHeader();
    return event;
}

shared_ptr<XSerialable> buildPnfRegistration()
{
    auto header = XCommonEventHeader::create(
        "EventName",
        "EventId",
        "SourceName",
        "ReportName",
        XEnumCommonEventHeaderPriorityNormal,
        111
        );

    auto event = XPnfRegistrationFields::create(header);
    event->setMacAddress("xx");
    event->setUnitFamily("xx");
    event->setSerialNumber("xx");
    event->setUnitType("xx");
    event->setManufactureDate("xx");
    event->setSoftwareVersion("xx");
    event->setModelNumber("xx");
    event->setLastServiceDate("xx");
    event->setOamV6IpAddress("xx");
    event->setAdditionalFields({ { "xxx","123" },{ "yyy","456" } });
    event->setVendorName("xx");
    event->setOamV4IpAddress("xx");

    event->getCommonHeader();
    return event;
}

shared_ptr<XSerialable> buildStateChange()
{
    auto header = XCommonEventHeader::create(
        "EventName",
        "EventId",
        "SourceName",
        "ReportName",
        XEnumCommonEventHeaderPriorityNormal,
        111
        );

    auto event = XStateChangeFields::create(header,
        XEnumStateChangeFieldsStateInService,
        XEnumStateChangeFieldsStateOutOfService,
        "interface"
        );
    XHashMap hm{ { "xxx","123" },{ "yyy","456" } };
    event->setAdditionalFields(hm);
    event->setNewState(XEnumStateChangeFieldsStateMaintenance);
    event->setOldState(XEnumStateChangeFieldsStateMaintenance);
    event->setStateInterface("xx");
    event->getCommonHeader();
    return event;
}

shared_ptr<XSerialable> buildSyslog()
{
    auto header = XCommonEventHeader::create(
        "EventName",
        "EventId",
        "SourceName",
        "ReportName",
        XEnumCommonEventHeaderPriorityNormal,
        111
        );

    auto event = XSyslogFields::create(header,
        XEnumSyslogFieldsEventSourceTypePort,
        "tag",
        "message"
        );
    event->setSyslogSev(XEnumSyslogFieldsSyslogSevInfo);
    event->setSyslogProcId(1);
    event->setSyslogFacility(1);
    event->setSyslogPri(1);
    event->setSyslogMsgHost("xx");
    event->setSyslogSData("xx");
    event->setSyslogMsg("xx");
    event->setSyslogProc("xx");
    event->setEventSourceHost("xx");
    event->setSyslogTs("xx");
    event->setSyslogTag("xx");
    event->setSyslogVer(1);
    event->setAdditionalFields({ { "xxx","123" },{ "yyy","456" } });
    event->setSyslogSdId("xx");
    event->setEventSourceType(XEnumSyslogFieldsEventSourceTypeCard);

    event->getCommonHeader();
    return event;
}

shared_ptr<XSerialable> buildThresholdCrossingAlert()
{
    auto header = XCommonEventHeader::create(
        "EventName",
        "EventId",
        "SourceName",
        "ReportName",
        XEnumCommonEventHeaderPriorityNormal,
        111
        );

    XHashMap hm{ { "xxx","123" },{ "yyy","456" } };
    XArrayOfXCounter counters{ { XEnumCounterCriticalityMAJ, hm, "thres1" } };
    counters[0].setCriticality(XEnumCounterCriticalityCRIT);
    counters[0].setThresholdCrossed("xx");
    counters[0].setHashMap(hm);
    
    auto event = XThresholdCrossingAlertFields::create(header,
        XEnumThresholdCrossingAlertFieldsAlertActionSET,
        XEnumThresholdCrossingAlertFieldsAlertTypeINTERFACE_ANOMALY,
        XEnumThresholdCrossingAlertFieldsEventSeverityMINOR,
        "description",
        "collect time",
        "start time",
        counters
        );

    event->getCommonHeader();
    event->setAlertDescription("xx");
    event->setInterfaceName("xx");
    event->setCollectionTimestamp("xx");
    event->setPossibleRootCause("xx");
    event->setAlertValue("xx");
    event->setDataCollector("xx");
    event->setNetworkService("xx");
    event->setElementType("xx");
    event->setAdditionalFields({ { "xxx","123" },{ "yyy","456" } });
    event->setEventStartTimestamp("xx");
    event->setAlertType(XEnumThresholdCrossingAlertFieldsAlertTypeCARD_ANOMALY);
    event->setEventSeverity(XEnumThresholdCrossingAlertFieldsEventSeverityCRITICAL);
    event->setAssociatedAlertIdList({"xx","yy"});

    XCounter x(XEnumCounterCriticalityCRIT, {{"xx","123"}}, "xx");
    event->setAdditionalParameters({x});
    event->setAlertAction(XEnumThresholdCrossingAlertFieldsAlertActionCONT);

    return event;
}

shared_ptr<XSerialable> buildXVoiceQuality()
{
    auto header = XCommonEventHeader::create(
        "EventName",
        "EventId",
        "SourceName",
        "ReportName",
        XEnumCommonEventHeaderPriorityNormal,
        111
        );

    XVendorNfNameFields vendor("testVendor");

    auto event = XVoiceQualityFields::create(header,
        "calleeSideCodec",
        "callerSideCodec",
        "correlator",
        "midCallRtcp",
        vendor
        );
    
    XEndOfCallVqmSummaries summaries("summeries", XEnumEndOfCallVqmSummariesEndpointDescriptionCallee);
    summaries.setLocalRtpPacketsDiscarded(1);
    summaries.setLocalMaxJitter(1);
    summaries.setRoundTripDelay(1);
    summaries.setLocalRtpOctetsSent(1);
    summaries.setLocalAverageJitterBufferDelay(1);
    summaries.setLocalRtpPacketsLost(1);
    summaries.setEndpointRtpOctetsReceived(1);
    summaries.setRFactor(1);
    summaries.setLocalRtpPacketsReceived(1);
    summaries.setEndpointRtpPacketsLost(1);
    summaries.setLocalAverageJitter(1);
    summaries.setMosCqe(1);
    summaries.setOneWayDelay(1);
    summaries.setEndpointRtpOctetsLost(1);
    summaries.setPacketLossPercent(1);
    summaries.setEndpointRtpOctetsDiscarded(1);
    summaries.setLocalRtpPacketsSent(1);
    summaries.setEndpointAverageJitter(1);
    summaries.setEndpointRtpOctetsSent(1);
    summaries.setEndpointMaxJitter(1);
    summaries.setEndpointRtpPacketsReceived(1);
    summaries.setEndpointRtpPacketsSent(1);
    summaries.setLocalMaxJitterBufferDelay(1);
    summaries.setLocalRtpOctetsLost(1);
    summaries.setLocalRtpOctetsReceived(1);
    summaries.setEndpointRtpPacketsDiscarded(1);
    summaries.setLocalRtpOctetsDiscarded(1);
    summaries.setAdjacencyName("xxxx");
    summaries.setEndpointDescription(XEnumEndOfCallVqmSummariesEndpointDescriptionCallee);

    event->setEndOfCallVqmSummaries(summaries);
    event->setMidCallRtcp("xx");
    event->setAdditionalInformation({ { "xxx","123" },{ "yyy","456" } });
    event->setCalleeSideCodec("xx");
    event->setPhoneNumber("xx");
    event->setCallerSideCodec("xx");
    event->setCorrelator("xx");
    event->setVendorNfNameFields(vendor);
    event->getCommonHeader();

    return event;
}

shared_ptr<XSerialable> buildBatch()
{
    auto batch = XBatch::create();
    batch->addEvent(buildFault());
    batch->addEvent(buildSyslog());
    return batch;
}

shared_ptr<XSerialable> buildMobileFlow()
{
    auto header = XCommonEventHeader::create(
        "EventName",
        "EventId",
        "SourceName",
        "ReportName",
        XEnumCommonEventHeaderPriorityNormal,
        111
        );

    XHashMap hm{ { "xxx","123" },{ "yyy","456" } };

    XGtpPerFlowMetrics m(1, 1, 1, 1, 1, 1, 1, 1, 1, "xx", "yy", 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);

    m.setNumLostPackets(1);
    m.setNumPacketsReceivedExclRetrans(1);
    m.setFlowDeactivationMicrosec(1);
    m.setAvgTransmitThroughput(1);
    m.setLargePacketRtt(1);
    m.setNumHttpErrors(1);
    m.setNumTimeouts(1);
    m.setFlowActivationEpoch(1);
    m.setNumPacketErrors(1);
    m.setAvgPacketDelayVariation(1);
    m.setAvgBitErrorRate(1);
    m.setFlowActivationMicrosec(1);
    m.setAvgPacketLatency(1);
    m.setNumBytesTransmitted(1);
    m.setNumBitErrors(1);
    m.setMaxReceiveBitRate(1);
    m.setMaxTransmitBitRate(1);
    m.setAvgReceiveThroughput(1);
    m.setNumRetries(1);
    m.setDurConnectionFailedStatus(1);
    m.setNumL7BytesTransmitted(1);
    m.setTimeToFirstByte(1);
    m.setNumBytesReceived(1);
    m.setFlowDeactivationEpoch(1);
    m.setNumGtpEchoFailures(1);
    m.setNumPacketsReceivedInclRetrans(1);
    m.setNumGtpTunnelErrors(1);
    m.setRoundTripTime(1);
    m.setNumActivationFailures(1);
    m.setMaxPacketDelayVariation(1);
    m.setNumTunneledL7BytesReceived(1);
    m.setNumL7BytesReceived(1);
    m.setNumDroppedPackets(1);
    m.setNumPacketsTransmittedInclRetrans(1);
    m.setNumOutOfOrderPackets(1);
    m.setLargePacketThreshold(1);
    m.setDurTunnelFailedStatus(1);
    m.setFlowActivationTime("xx");
    m.setFlowDeactivationTime("xx");
    m.setFlowActivatedBy("xx");
    m.setIpTosCountList(hm);
    m.setMobileQciCosCountList(hm);
    m.setIpTosList({"xxx","yyy"});
    m.setMobileQciCosList({"xxx","yyy"});
    m.setGtpConnectionStatus("xx");
    m.setTcpFlagList({"xxx","yyy"});
    m.setFlowStatus("xx");
    m.setGtpTunnelStatus("xx");
    m.setTcpFlagCountList(hm);
    m.setFlowDeactivatedBy("xx");

    auto event = XMobileFlowFields::create(header,"xx", m, "xx", "xx", "xx",1,"xx",1);
    event->setRac("xx");
    event->setSac("xx");
    event->setSamplingAlgorithm(1);
    event->setIpVersion("xx");
    event->setTac("xx");
    event->setMnc("xx");
    event->setTunnelId("xx");
    event->setAppProtocolVersion("xx");
    event->setGtpVersion("xx");
    event->setConnectionType("xx");
    event->setHttpHeader("xx");
    event->setImsi("xx");
    event->setApplicationType("xx");
    event->setMsisdn("xx");
    event->setMcc("xx");
    event->setFlowDirection("xx");
    event->setLac("xx");
    event->setOtherEndpointPort(1);
    event->setVlanId("xx");
    event->setImei("xx");
    event->setGtpProtocolType("xx");
    event->setEcgi("xx");
    event->setCid("xx");
    event->setReportingEndpointPort(1);
    event->setRadioAccessTechnology("xx");
    event->setAppProtocolType("xx");
    event->setOtherEndpointIpAddress("xx");
    event->setIpProtocolType("xx");
    event->setOtherFunctionalRole("xx");
    event->setReportingEndpointIpAddr("xx");

    event->setGtpPerFlowMetrics(m);
    event->setAdditionalFields({ { "xxx","123" },{ "yyy","456" } });
    event->getCommonHeader();

    return event;
}

shared_ptr<XSerialable> buildSipSignaling()
{
    auto header = XCommonEventHeader::create(
        "EventName",
        "EventId",
        "SourceName",
        "ReportName",
        XEnumCommonEventHeaderPriorityNormal,
        111
        );

    XVendorNfNameFields vendor("xx");
    vendor.setVendorName("xx");
    vendor.setNfName("xx");
    vendor.setNfModuleName("xx");
    auto event = XSipSignalingFields::create(header,"x","x","x","x","x", vendor);
    event->getCommonHeader();

    event->setRemotePort("xx");
    event->setSummarySip("xx");
    event->setLocalPort("xx");
    event->setAdditionalInformation({ { "xxx","123" },{ "yyy","456" } });
    event->setLocalIpAddress("xx");
    event->setCompressedSip("xx");
    event->setCorrelator("xx");
    event->setRemoteIpAddress("xx");
    event->setVendorNfNameFields(vendor);

    return event;
}
