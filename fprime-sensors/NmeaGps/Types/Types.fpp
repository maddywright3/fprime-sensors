module NmeaGps {

    #####
    # A note on the use of F64 (double):
    #
    # A meter is approximately ~0.00001 degrees and the maximum degree value is 180. Thus in order to give meter
    # precision there must be at least log2(180 00001) or ~24 bits of precision. F32 only has 23 bits of precision and
    # thus would be limited to a precision of > 1 meter.
    ####

    @ Struct representing GPS data
    struct GpsData {
        @ Latitude in degrees
        latitude: F64,
        @ Longitude in degrees
        longitude: F64,
        @ Altitude in meters
        altitude: F64,
    }
}