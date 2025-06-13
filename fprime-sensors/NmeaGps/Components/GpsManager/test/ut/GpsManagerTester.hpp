// ======================================================================
// \title  GpsManagerTester.hpp
// \author starchmd
// \brief  hpp file for GpsManager component test harness implementation class
// ======================================================================

#ifndef NmeaGps_GpsManagerTester_HPP
#define NmeaGps_GpsManagerTester_HPP

#include "fprime-sensors/NmeaGps/Components/GpsManager/GpsManager.hpp"
#include "fprime-sensors/NmeaGps/Components/GpsManager/GpsManagerGTestBase.hpp"

namespace NmeaGps {

class GpsManagerTester : public GpsManagerGTestBase, public ::testing::Test {
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

    //! Construct object GpsManagerTester
    GpsManagerTester();

    //! Destroy object GpsManagerTester
    ~GpsManagerTester();

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
    GpsManager component;
};

}  // namespace NmeaGps

#endif
