// ======================================================================
// \title  ImuManager.hpp
// \author mstarch
// \brief  hpp file for ImuManager component implementation class
// ======================================================================

#ifndef MpuImu_ImuManager_HPP
#define MpuImu_ImuManager_HPP

#include "fprime-sensors/MpuImu/Components/ImuManager/ImuManagerComponentAc.hpp"

namespace MpuImu {

class ImuManager final : public ImuManagerComponentBase {
  public:
    static constexpr U8 DATA_LENGTH = (6 + 1) * sizeof(U16);  // 6 DoF + temperature
    static constexpr U8 DATA_BASE_REGISTER = 0x3B;
    static constexpr U8 DEVICE_ADDRESS = 0x68;
    static constexpr U8 POWER_MGMT_REGISTER = 0x6B;
    static constexpr U8 RESET_VALUE = 0x80;
    static constexpr U8 POWER_ON_VALUE = 0x00;
    static constexpr U8 GYRO_CONFIG_REGISTER = 0x1B;
    static constexpr U8 ACCEL_CONFIG_REGISTER = 0x1C;

    // Configuration values for the accelerometer and gyroscope
    static constexpr U8 ACCEL_CONFIG_2G = 0x00;
    static constexpr U8 ACCEL_CONFIG_4G = 0x08;
    static constexpr U8 ACCEL_CONFIG_8G = 0x10;
    static constexpr U8 ACCEL_CONFIG_16G = 0x18;
    static constexpr U8 GYRO_CONFIG_250DEG = 0x00;
    static constexpr U8 GYRO_CONFIG_500DEG = 0x08;
    static constexpr U8 GYRO_CONFIG_1000DEG = 0x10;
    static constexpr U8 GYRO_CONFIG_2000DEG = 0x18;
    static constexpr F32 TEMPERATURE_SCALAR = 340.0f;
    static constexpr F32 TEMPERATURE_OFFSET = 36.53f;

    struct RawImuData {
        U16 acceleration[3];
        U16 temperature;
        U16 gyroscope[3];
    };

    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct ImuManager object
    ImuManager(const char* const compName  //!< The component name
    );

    //! Destroy ImuManager object
    ~ImuManager();

    //! Converts raw IMU data to the telemetry structure
    static ImuData convert_raw_data(const RawImuData& raw,
                                    const AccelerationRange& accelerationRange,
                                    const GyroscopeRange& gyroscopeRange);

    //! Acceleration range to register value
    static U8 accelerometer_range_to_register(AccelerationRange range);

    //! Gyroscope range to register value
    static U8 gyroscope_range_to_register(GyroscopeRange range);

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for typed input ports
    // ----------------------------------------------------------------------

    //! Emit parameter updated EVR
    //!
    void parameterUpdated(FwPrmIdType id  //!< The parameter ID
                          ) override;

    //! Handler implementation for run
    //!
    //! Scheduling port for reading from IMU and writing to telemetry
    void run_handler(FwIndexType portNum,  //!< The port number
                     U32 context           //!< The call order
                     ) override;

    // ----------------------------------------------------------------------
    // Helper functions
    // ----------------------------------------------------------------------

    //! Resets the IMU
    bool reset();

    //! Power on the IMU
    bool power_on();

    //! Read the reset register value
    bool read_reset(U8& value);

    //! Configure the IMU's accelerometer and gyroscope
    bool configure_device();

    //! Write to the I2C bus and handle errors
    bool bus_write(Fw::Buffer& writeBuffer, Fw::Buffer& readBuffer);

    //! Deserializes raw data from the bus
    RawImuData deserialize_raw_data(Fw::Buffer& buffer);

    //! State of the IMU component
    enum ImuState { RESET, POWER_ON, CONFIGURE, RUNNING };

    //! Tracks the state of the IMU
    ImuState m_state;
};

}  // namespace MpuImu

#endif
