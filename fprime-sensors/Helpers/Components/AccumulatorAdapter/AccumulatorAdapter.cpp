// ======================================================================
// \title  AccumulatorAdapter.cpp
// \author starchmd
// \brief  cpp file for AccumulatorAdapter component implementation class
// ======================================================================

#include "fprime-sensors/Helpers/Components/AccumulatorAdapter/AccumulatorAdapter.hpp"

namespace FprimeSensors {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

AccumulatorAdapter ::AccumulatorAdapter(const char* const compName) : AccumulatorAdapterComponentBase(compName) {}

AccumulatorAdapter ::~AccumulatorAdapter() {}

// ----------------------------------------------------------------------
// Handler implementations for typed input ports
// ----------------------------------------------------------------------

void AccumulatorAdapter ::bufferLikeIn_handler(FwIndexType portNum,
                                               Fw::Buffer& data) {
    this->commLikeOut_out(portNum, data, ComCfg::FrameContext());
}

void AccumulatorAdapter ::commLikeIn_handler(FwIndexType portNum,
                                             Fw::Buffer& data,
                                             const ComCfg::FrameContext& _) {
    this->bufferLikeOut_out(portNum, data);
}

void AccumulatorAdapter ::byteStreamLikeIn_handler(FwIndexType portNum,
                                                   Fw::Buffer& buffer,
                                                   const Drv::ByteStreamStatus& status) {
    if (status == Drv::ByteStreamStatus::OP_OK) {
        this->bufferLikeIn_handler(portNum, buffer);
    } else {
        this->bufferLikeOut_out(portNum, buffer);
    }
}

}  // namespace FprimeSensors
