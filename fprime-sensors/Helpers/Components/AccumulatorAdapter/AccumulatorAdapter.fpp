module FprimeSensors {
    @ Adapter for FrameAccumulator for use outside of communications
    passive component AccumulatorAdapter {

        @ Port to receive buffer like data
        sync input port bufferLikeIn: Fw.BufferSend

        @ Port for sending buffer like data
        output port bufferLikeOut: Fw.BufferSend

        @ Port to receive comm like data
        sync input port commLikeIn: Svc.ComDataWithContext

        @ Port to receive byte stream like data
        sync input port byteStreamLikeIn: Drv.ByteStreamData

        @ Port for sending comm like data
        output port commLikeOut: Svc.ComDataWithContext
    }
}