// ======================================================================
// \title  GpsManager.hpp
// \author starchmd
// \brief  hpp file for GpsManager component implementation class
// ======================================================================

#ifndef NmeaGps_GpsManager_HPP
#define NmeaGps_GpsManager_HPP

#include "fprime-sensors/NmeaGps/Components/GpsManager/GpsManagerComponentAc.hpp"

namespace NmeaGps {

class GpsManager final : public GpsManagerComponentBase {
  public:
    struct GgaMessage {
        double time;       //!< Time in HHMMSS.SS format
        double latitude;   //!< Latitude in DDmm.mmmm format
        char latitudeDirection;    //!< Latitude direction (N or S)
        double longitude;  //!< Longitude in DDmm.mmmm format
        char longitudeDirection;   //!< Latitude direction (N or S)
        uint8_t fixType;   //!< Fix type (0 = no fix, 1 = GPS fix, etc.)
        uint8_t numSatellites;     //!< Number of satellites
        double horizontalDilution; //!< Horizontal dilution of precision
        double altitude;   //!< Altitude in meters
        char altitudeUnits;        //!< Altitude unit (M for meters)
        double undulation; //!< Undulation in meters
        char undulationUnits;      //!< Undulation unit (M for meters)
        uint8_t age;       //!< Age of differential GPS data in seconds
        char stationId[4 + 1];     //!< Station ID for differential GPS
    };

    //! NMEA header format
    const char* HEADER_FORMAT = "$%5s";

    //! Message without the header nor checksum
    const char* GGA_FORMAT = "%lf,%lf,%c,%lf,%c,%" SCNu8 ",%" SCNu8 ",%lf,%lf,%c,%lf,%c,%" SCNu8 ",%4s";

    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct GpsManager object
    GpsManager(const char* const compName  //!< The component name
    );

    //! Destroy GpsManager object
    ~GpsManager();

  private:

    //! Parse GGA message from the given data buffer
    //! \param data: buffer message without header
    //! \param messageHeader: header to be used for logging
    void parse_gga_message(const char* data, Fw::StringBase& messageHeader);

    //! Convert DDmm.mmmm to degrees
    //! \param ddmmmmmm: the DDmm.mmmm value
    //! \param direction: the direction character (N, S, E, W)
    //!
    //! \return the converted value in degrees
    double ddmmmmmm_to_degrees(F64 ddmmmmmm, char direction);

    // ----------------------------------------------------------------------
    // Handler implementations for typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for dataIn
    //!
    //! Port to receive framed data, with optional context
    void dataIn_handler(FwIndexType portNum,  //!< The port number
                        Fw::Buffer& data     //!< Full message data
    ) override;
};

}  // namespace NmeaGps

#endif
