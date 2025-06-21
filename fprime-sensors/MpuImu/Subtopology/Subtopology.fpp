module MpuImu {
    @ Manager overseeing the IMU
    instance imuManager: MpuImu.ImuManager base id MpuImu.SubtoplogyConfig.BASE_ID + 0x00001000

    topology Subtopology {
        instance imuManager
        instance imuDriver

        connections MpuImu {
            imuManager.busWriteRead -> imuDriver.writeRead
            imuManager.busWrite -> imuDriver.write
        }
    }
}
