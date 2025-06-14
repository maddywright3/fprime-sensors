// ======================================================================
// \title  NmeaDetector.hpp
// \brief  Frame detector for NMEA messages
// ======================================================================

#include "Svc/FrameAccumulator/FrameDetector.hpp"

namespace NmeaGps {

constexpr char NMEA_START_CHAR = '$'; //!< Start character for NMEA messages
constexpr char NMEA_END_CHAR = '\n';   //!< End character for NMEA messages
constexpr FwSizeType NMEA_MINIMUM_MESSAGE_LENGTH = 6 + 2 + 2; //!< Minimum size of a valid NMEA message: $?????*?\r\n

class NmeaDetector final : public Svc::FrameDetector {
  public:

    //! \brief detect if there is a NMEA message available within the circular buffer
    Svc::FrameDetector::Status detect(const Types::CircularBuffer& data, FwSizeType& size_out) const;
};

} // namespace NmeaGps