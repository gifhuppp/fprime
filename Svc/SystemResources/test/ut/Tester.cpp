// ======================================================================
// \title  SystemResources.hpp
// \author mstarch
// \brief  cpp file for SystemResources test harness implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#include "Tester.hpp"
#include "version.hpp"
#define INSTANCE 0
#define MAX_HISTORY_SIZE 100

namespace Svc {

// ----------------------------------------------------------------------
// Construction and destruction
// ----------------------------------------------------------------------

Tester ::Tester(void) : SystemResourcesGTestBase("Tester", MAX_HISTORY_SIZE), component("SystemResources") {
    this->initComponents();
    this->connectPorts();
}

Tester ::~Tester(void) {}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void Tester ::test_tlm(bool enabled) {
    U32 count = 0;
    if (Os::SystemResources::getCpuCount(count) == Os::SystemResources::SYSTEM_RESOURCES_OK) {
        this->invoke_to_run(0, 0);
        // All cascades expected
        switch (count) {
            case 16:
                ASSERT_TLM_CPU_15_SIZE((enabled) ? 1 : 0);
            // Cascade expected 
            case 15:
                ASSERT_TLM_CPU_14_SIZE((enabled) ? 1 : 0);
            // Cascade expected 
            case 14:
                ASSERT_TLM_CPU_13_SIZE((enabled) ? 1 : 0);
            // Cascade expected 
            case 13:
                ASSERT_TLM_CPU_12_SIZE((enabled) ? 1 : 0);
            // Cascade expected 
            case 12:
                ASSERT_TLM_CPU_11_SIZE((enabled) ? 1 : 0);
            // Cascade expected 
            case 11:
                ASSERT_TLM_CPU_10_SIZE((enabled) ? 1 : 0);
            // Cascade expected 
            case 10:
                ASSERT_TLM_CPU_09_SIZE((enabled) ? 1 : 0);
            // Cascade expected 
            case 9:
                ASSERT_TLM_CPU_08_SIZE((enabled) ? 1 : 0);
            // Cascade expected 
            case 8:
                ASSERT_TLM_CPU_07_SIZE((enabled) ? 1 : 0);
            // Cascade expected 
            case 7:
                ASSERT_TLM_CPU_06_SIZE((enabled) ? 1 : 0);
            // Cascade expected 
            case 6:
                ASSERT_TLM_CPU_05_SIZE((enabled) ? 1 : 0);
            // Cascade expected 
            case 5:
                ASSERT_TLM_CPU_04_SIZE((enabled) ? 1 : 0);
            // Cascade expected 
            case 4:
                ASSERT_TLM_CPU_03_SIZE((enabled) ? 1 : 0);
            // Cascade expected 
            case 3:
                ASSERT_TLM_CPU_02_SIZE((enabled) ? 1 : 0);
            // Cascade expected 
            case 2:
                ASSERT_TLM_CPU_01_SIZE((enabled) ? 1 : 0);
            // Cascade expected 
            case 1:
                ASSERT_TLM_CPU_00_SIZE((enabled) ? 1 : 0);
            // Cascade expected 
            default:
                ASSERT_TLM_CPU_SIZE((enabled) ? 1 : 0);

                ASSERT_TLM_MEMORY_USED_SIZE((enabled) ? 1 : 0);
                ASSERT_TLM_MEMORY_TOTAL_SIZE((enabled) ? 1 : 0);
                ASSERT_TLM_NON_VOLATILE_FREE_SIZE((enabled) ? 1 : 0);
                ASSERT_TLM_NON_VOLATILE_TOTAL_SIZE((enabled) ? 1 : 0);
                ASSERT_TLM_VERSION_SIZE((enabled) ? 1 : 0);
                if (enabled) {
                    ASSERT_TLM_VERSION(0, VERSION);
                }
                ASSERT_TLM_SIZE((enabled) ? (count + 6) : 0); // CPU count channels + avg + 2 mem + 2 non-volatile + ver
                break;
        }
    }
}

void Tester ::test_disable_enable() {
    this->sendCmd_ENABLE(0, 0, SystemResourcesComponentBase::SystemResourceEnabled::SYS_RES_DISABLED);
    this->test_tlm(false);
    this->sendCmd_ENABLE(0, 0, SystemResourcesComponentBase::SystemResourceEnabled::SYS_RES_ENABLED);
    this->test_tlm(true);
}

void Tester ::test_version_evr() {
    this->sendCmd_VERSION(0, 0);
    ASSERT_EVENTS_VERSION_SIZE(1);
    ASSERT_EVENTS_VERSION(0, VERSION);
}

// ----------------------------------------------------------------------
// Helper methods
// ----------------------------------------------------------------------

void Tester ::connectPorts(void) {
    // run
    this->connect_to_run(0, this->component.get_run_InputPort(0));

    // CmdDisp
    this->connect_to_CmdDisp(0, this->component.get_CmdDisp_InputPort(0));

    // CmdStatus
    this->component.set_CmdStatus_OutputPort(0, this->get_from_CmdStatus(0));

    // CmdReg
    this->component.set_CmdReg_OutputPort(0, this->get_from_CmdReg(0));

    // Tlm
    this->component.set_Tlm_OutputPort(0, this->get_from_Tlm(0));

    // Time
    this->component.set_Time_OutputPort(0, this->get_from_Time(0));

    // Log
    this->component.set_Log_OutputPort(0, this->get_from_Log(0));

    // LogText
    this->component.set_LogText_OutputPort(0, this->get_from_LogText(0));
}

void Tester ::initComponents(void) {
    this->init();
    this->component.init(INSTANCE);
}

}  // end namespace Svc
