// ======================================================================
// \title  GpsManagerTester.cpp
// \author starchmd
// \brief  cpp file for GpsManager component test harness implementation class
// ======================================================================

#include "GpsManagerTester.hpp"

namespace NmeaGps {

// ----------------------------------------------------------------------
// Construction and destruction
// ----------------------------------------------------------------------

GpsManagerTester ::GpsManagerTester()
    : GpsManagerGTestBase("GpsManagerTester", GpsManagerTester::MAX_HISTORY_SIZE), component("GpsManager") {
    this->initComponents();
    this->connectPorts();
}

GpsManagerTester ::~GpsManagerTester() {}

}  // namespace NmeaGps
