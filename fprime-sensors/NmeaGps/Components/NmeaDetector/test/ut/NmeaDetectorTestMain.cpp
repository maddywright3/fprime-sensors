// ======================================================================
// \title  NmeaDetectorTestMain.cpp
// \author starchmd
// \brief  cpp file for NmeaDetector test main function
// ======================================================================
#include "gtest/gtest.h"
#include "fprime-sensors/NmeaGps/Components/NmeaDetector/NmeaDetector.hpp"

namespace NmeaGps {
    // From https://en.wikipedia.org/wiki/NMEA_0183
    char GOOD_MESSAGE[] = "$GPGGA,092750.000,5321.6802,N,00630.3372,W,1,8,1.03,61.7,M,55.2,M,,*76\r\n";

    // Modified from aboce
    char NO_CHECKSUM[] = "$GPGGA,092750.000,5321.6802,N,00630.3372,W,1,8,1.03,61.7,M,55.2,M,12,AAAA\r\n";
    char BAD_CHECKSUM[] = "$GPGGA,092750.000,5321.6802,N,00630.3372,W,1,8,1.03,61.7,M,55.2,M,12,AAAA*76\r\n";
    
    U8 BUFFER[1024];

    TEST(NemaFrameDetector, WellFormedMessage) {
        Types::CircularBuffer data(BUFFER, sizeof(BUFFER));
        data.serialize(reinterpret_cast<const U8*>(GOOD_MESSAGE), sizeof(GOOD_MESSAGE));

        FwSizeType size_out = 0;
        NmeaGps::NmeaDetector detector;
        ASSERT_EQ(detector.detect(data, size_out), Svc::FrameDetector::Status::FRAME_DETECTED);
        ASSERT_EQ(size_out, sizeof(GOOD_MESSAGE) - 1); // Exclude the null terminator
    }

    TEST(NemaFrameDetector, NoChecksum) {
        Types::CircularBuffer data(BUFFER, sizeof(BUFFER));
        data.serialize(reinterpret_cast<const U8*>(NO_CHECKSUM), sizeof(NO_CHECKSUM));

        FwSizeType size_out = 0;
        NmeaGps::NmeaDetector detector;
        ASSERT_EQ(detector.detect(data, size_out), Svc::FrameDetector::Status::FRAME_DETECTED);
        ASSERT_EQ(size_out, sizeof(NO_CHECKSUM) - 1); // Exclude the null terminator
    }

    TEST(NemaFrameDetector, BadChecksum) {
        Types::CircularBuffer data(BUFFER, sizeof(BUFFER));
        data.serialize(reinterpret_cast<const U8*>(BAD_CHECKSUM), sizeof(BAD_CHECKSUM));

        FwSizeType size_out = 0;
        NmeaGps::NmeaDetector detector;
        ASSERT_EQ(detector.detect(data, size_out), Svc::FrameDetector::Status::NO_FRAME_DETECTED);
        ASSERT_EQ(size_out, NmeaGps::NMEA_MINIMUM_MESSAGE_LENGTH);
    }


    TEST(NemaFrameDetector, BadStartCharacter) {
        Types::CircularBuffer data(BUFFER + 1, sizeof(BUFFER) - 1);
        data.serialize(reinterpret_cast<const U8*>(BAD_CHECKSUM), sizeof(BAD_CHECKSUM));

        FwSizeType size_out = 0;
        NmeaGps::NmeaDetector detector;
        ASSERT_EQ(detector.detect(data, size_out), Svc::FrameDetector::Status::NO_FRAME_DETECTED);
        ASSERT_EQ(size_out, NmeaGps::NMEA_MINIMUM_MESSAGE_LENGTH);
    }

    TEST(NemaFrameDetector, ShortMessages) {
        Types::CircularBuffer data(BUFFER + 1, sizeof(BUFFER) - 1);
        NmeaGps::NmeaDetector detector;

        for (FwSizeType i = 0; i < sizeof(GOOD_MESSAGE) - 1; i++) {
            data.serialize(reinterpret_cast<const U8*>(GOOD_MESSAGE + i), 1);
            FwSizeType size_out = 0;
            // Lest than last iteration should ask for more data
            if (i < sizeof(GOOD_MESSAGE) - 2) {
                ASSERT_EQ(detector.detect(data, size_out), Svc::FrameDetector::Status::MORE_DATA_NEEDED);
                ASSERT_GT(size_out, i);
            }
            // Last iteration should detect the full message
            else {
                ASSERT_EQ(detector.detect(data, size_out), Svc::FrameDetector::Status::FRAME_DETECTED);
                ASSERT_EQ(size_out, sizeof(GOOD_MESSAGE) - 1); // Exclude null terminator (only in test)
            }
        }
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
