// ======================================================================
// \title  AccumulatorAdapterTester.hpp
// \author starchmd
// \brief  hpp file for AccumulatorAdapter component test harness implementation class
// ======================================================================

#ifndef FprimeSensors_AccumulatorAdapterTester_HPP
#define FprimeSensors_AccumulatorAdapterTester_HPP

#include "fprime-sensors/Helpers/Components/AccumulatorAdapter/AccumulatorAdapter.hpp"
#include "fprime-sensors/Helpers/Components/AccumulatorAdapter/AccumulatorAdapterGTestBase.hpp"

namespace FprimeSensors {

class AccumulatorAdapterTester : public AccumulatorAdapterGTestBase, public ::testing::Test {
  public:
    // ----------------------------------------------------------------------
    // Constants
    // ----------------------------------------------------------------------

    // Maximum size of histories storing events, telemetry, and port outputs
    static const FwSizeType MAX_HISTORY_SIZE = 10;

    // Instance ID supplied to the component instance under test
    static const FwEnumStoreType TEST_INSTANCE_ID = 0;

  public:
    // ----------------------------------------------------------------------
    // Construction and destruction
    // ----------------------------------------------------------------------

    //! Construct object AccumulatorAdapterTester
    AccumulatorAdapterTester();

    //! Destroy object AccumulatorAdapterTester
    ~AccumulatorAdapterTester();

  private:
    // ----------------------------------------------------------------------
    // Helper functions
    // ----------------------------------------------------------------------

    //! Connect ports
    void connectPorts();

    //! Initialize components
    void initComponents();

  private:
    // ----------------------------------------------------------------------
    // Member variables
    // ----------------------------------------------------------------------

    //! The component under test
    AccumulatorAdapter component;
};

}  // namespace FprimeSensors

#endif
