// ======================================================================
// \title  AccumulatorAdapterTester.cpp
// \author starchmd
// \brief  cpp file for AccumulatorAdapter component test harness implementation class
// ======================================================================

#include "AccumulatorAdapterTester.hpp"

namespace FprimeSensors {

// ----------------------------------------------------------------------
// Construction and destruction
// ----------------------------------------------------------------------

AccumulatorAdapterTester ::AccumulatorAdapterTester()
    : AccumulatorAdapterGTestBase("AccumulatorAdapterTester", AccumulatorAdapterTester::MAX_HISTORY_SIZE),
      component("AccumulatorAdapter") {
    this->initComponents();
    this->connectPorts();
}

AccumulatorAdapterTester ::~AccumulatorAdapterTester() {}

}  // namespace FprimeSensors
