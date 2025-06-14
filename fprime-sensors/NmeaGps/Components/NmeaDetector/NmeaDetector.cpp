// ======================================================================
// \title  NmeaDetector.cpp
// \brief  Frame detector for NMEA messages
// ======================================================================

#include "fprime-sensors/NmeaGps/Components/NmeaDetector/NmeaDetector.hpp"
#include "Fw/Types/Assert.hpp"

namespace NmeaGps {

Svc::FrameDetector::Status NmeaDetector::detect(const Types::CircularBuffer& data, FwSizeType& size_out) const {
    U8 start = 0;
    // Minimum length check
    if (data.get_allocated_size() < NMEA_MINIMUM_MESSAGE_LENGTH) {
        // Not enough data for a valid NMEA message
        size_out = NMEA_MINIMUM_MESSAGE_LENGTH;
        return Status::MORE_DATA_NEEDED;
    }
    // Check if the first character is the start character '$'
    if (data.peek(start) != Fw::FW_SERIALIZE_OK || static_cast<char>(start) != NMEA_START_CHAR) {
        size_out = NMEA_MINIMUM_MESSAGE_LENGTH;
        return Status::NO_FRAME_DETECTED;
    }
    FwSizeType end_index = 0;
    char checksum = 0;
    bool found_asterisk = false;
    // Loop through message characters looking for an end character
    for (end_index = 1; end_index < data.get_allocated_size(); end_index++) {
        U8 current_char = 0;
        // Must need more data if the peak fails
        if (data.peek(current_char, end_index) != Fw::FW_SERIALIZE_OK) {
            size_out = end_index + 1;
            return Status::MORE_DATA_NEEDED;
        }
        // Check if the current character is the end character
        if (static_cast<char>(current_char) == NMEA_END_CHAR) {
            break;
        }
        // Check if the current character indicates checksum
        else if (static_cast<char>(current_char) == '*') {
            found_asterisk = true;
        } else if (not found_asterisk) {
            checksum ^= static_cast<char>(current_char);
        }
    }
    // When the end character was not found, more data is needed
    if (end_index >= data.get_allocated_size()) {
        size_out = end_index + 1;
        return Status::MORE_DATA_NEEDED;
    }
    // If checksum was found, check against the recalculated checksum
    if (found_asterisk) {
        U8 checksum_digit_1 = 0;
        U8 checksum_digit_2 = 0;
        // Grab the checksum digits
        if ((data.peek(checksum_digit_1, end_index - 3) != Fw::FW_SERIALIZE_OK) ||
            (data.peek(checksum_digit_2, end_index - 2) != Fw::FW_SERIALIZE_OK)) {
            FW_ASSERT(0); // Should never fail
        }
        U8 read_checksum = ((checksum_digit_1 >= 'A') ? (checksum_digit_1 - 'A' + 10) : (checksum_digit_1 - '0')) << 4 |
                           ((checksum_digit_2 >= 'A') ? (checksum_digit_2 - 'A' + 10) : (checksum_digit_2 - '0'));
        // Bad checksum, no frame detected
        if (read_checksum != checksum) {
            size_out = NMEA_MINIMUM_MESSAGE_LENGTH;
            return Status::NO_FRAME_DETECTED;
        }
    }
    size_out = end_index + 1; // Include the end character in the size
    return Status::FRAME_DETECTED;
}
} // namespace NmeaGps