// ======================================================================
// \title  ImuManagerTestMain.cpp
// \author mstarch
// \brief  cpp file for ImuManager component test main function
// ======================================================================

#include "ImuManagerTester.hpp"
#include "STest/Pick/Pick.hpp"
#include "STest/Random/Random.hpp"

namespace MpuImu {

TEST_F(ImuManagerTester, NominalBootSequence) {
    this->nominal_boot_sequence();
    this->reconfigure_sequence();
    this->nominal_run_sequence();
}

TEST_F(ImuManagerTester, NominalParameterChange) {
    this->nominal_boot_sequence();
    this->reconfigure_sequence();
    this->nominal_run_sequence();
    this->pick_acceleration_range();
    this->pick_gyroscope_range();
    ASSERT_EVENTS_AccelerometerRangeUpdated_SIZE(1);
    ASSERT_EVENTS_AccelerometerRangeUpdated(0, this->accelerationRange);
    ASSERT_EVENTS_GyroscopeRangeUpdated_SIZE(1);
    ASSERT_EVENTS_GyroscopeRangeUpdated(0, this->gyroscopeRange);
    this->state = ImuManagerTester::State::CONFIGURE_ACCELEROMETER;
    this->reconfigure_sequence();
    this->nominal_run_sequence();
}

TEST_F(ImuManagerTester, FailureRate) {
    // Choose a failure rate up to about 10% of the time
    this->failureRate = STest::Pick::lowerUpper(10, 10);
    for (U32 i = 0; i < STest::Pick::lowerUpper(10000, 1000000); i++) {
        this->tick();
        ASSERT_EVENTS_I2cError_SIZE(this->i2cFailure);
        this->clearFromPortHistory();
        this->clearTlm();
    }
}

}  // namespace MpuImu
int main(int argc, char** argv) {
    STest::Random::seed();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
