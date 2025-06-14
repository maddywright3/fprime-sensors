module NmeaGps {
    @ Manager overseeing the GPS system
    instance gpsManager: NmeaGps.GpsManager base id NmeaGps.SubtoplogyConfig.BASE_ID + 0x00001000

    @ Adapter for GPS to received data from the FrameAccumulator
    instance gpsAdapter: FprimeSensors.AccumulatorAdapter base id NmeaGps.SubtoplogyConfig.BASE_ID + 0x00002000

    @ FrameAccumulator collecting NMEA messages
    instance frameAccumulator: Svc.FrameAccumulator base id NmeaGps.SubtoplogyConfig.BASE_ID + 0x00003000

    @ Adapter from driver to FrameAccumulator
    instance driverInterface: FprimeSensors.AccumulatorAdapter base id NmeaGps.SubtoplogyConfig.BASE_ID + 0x00004000


    topology Subtopology {
        instance gpsManager
        instance gpsAdapter
        instance frameAccumulator
        instance driverInterface

        connections NmeaGps {
            gpsAdapter.bufferLikeOut -> gpsManager.dataIn
            gpsManager.dataReturnOut -> gpsAdapter.bufferLikeIn

            frameAccumulator.dataOut -> gpsAdapter.commLikeIn
            gpsAdapter.commLikeOut -> frameAccumulator.dataReturnIn



            driverInterface.commLikeOut -> frameAccumulator.dataIn
            frameAccumulator.dataReturnOut -> driverInterface.commLikeIn
        }

    }
}