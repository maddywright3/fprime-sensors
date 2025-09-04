module MpuImu {

    constant BASE_ID = 0xE0000000

    module QueueSizes {
        constant imuManager  = 10
    }

    instance imuDriver: Drv.LinuxI2cDriver base id MpuImu.BASE_ID + 0x00002000 {
        phase Fpp.ToCpp.Phases.configComponents """
        if (not MpuImu::imuDriver.open(state.mpu.device)) {
            Fw::Logger::log("[ERROR] MPU IMU open failed\\n");
        }
        else {
            Fw::Logger::log("[INFO] MPU IMU open successful\\n");
        }
        """
    }
}
