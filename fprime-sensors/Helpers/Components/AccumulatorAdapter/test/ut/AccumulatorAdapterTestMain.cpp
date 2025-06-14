// ======================================================================
// \title  AccumulatorAdapterTestMain.cpp
// \author starchmd
// \brief  cpp file for AccumulatorAdapter component test main function
// ======================================================================

#include "AccumulatorAdapterTester.hpp"

namespace FprimeSensors {

TEST_F(AccumulatorAdapterTester, ContextSend) {
    U8 dataBuffer[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    Fw::Buffer data(dataBuffer, sizeof(dataBuffer));
    this->invoke_to_commLikeIn(0, data, ComCfg::FrameContext());
    
    ASSERT_from_bufferLikeOut_SIZE(1);
    ASSERT_from_commLikeOut_SIZE(0);
    ASSERT_EQ(this->fromPortHistory_bufferLikeOut->at(0).fwBuffer.getData(), data.getData());
}

TEST_F(AccumulatorAdapterTester, BufferSend) {
    U8 dataBuffer[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    Fw::Buffer data(dataBuffer, sizeof(dataBuffer));
    this->invoke_to_bufferLikeIn(0, data);
    
    ASSERT_from_bufferLikeOut_SIZE(0);
    ASSERT_from_commLikeOut_SIZE(1);
    ASSERT_EQ(this->fromPortHistory_commLikeOut->at(0).data.getData(), data.getData());
}

TEST_F(AccumulatorAdapterTester, ByteStreamSendGood) {
    U8 dataBuffer[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    Fw::Buffer data(dataBuffer, sizeof(dataBuffer));
    this->invoke_to_byteStreamLikeIn(0, data, Drv::ByteStreamStatus::OP_OK);
    
    ASSERT_from_bufferLikeOut_SIZE(0);
    ASSERT_from_commLikeOut_SIZE(1);
    ASSERT_EQ(this->fromPortHistory_commLikeOut->at(0).data.getData(), data.getData());
}

TEST_F(AccumulatorAdapterTester, ByteStreamSendBad) {
    U8 dataBuffer[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    Fw::Buffer data(dataBuffer, sizeof(dataBuffer));
    this->invoke_to_byteStreamLikeIn(0, data, Drv::ByteStreamStatus::OTHER_ERROR);
    
    ASSERT_from_bufferLikeOut_SIZE(1);
    ASSERT_from_commLikeOut_SIZE(0);
    ASSERT_EQ(this->fromPortHistory_bufferLikeOut->at(0).fwBuffer.getData(), data.getData());
}


} // namespace FprimeSensors

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
