// ======================================================================
// \title  SubtopologyTopologyDefs.hpp
// \brief subtopology definitions header
//
// ======================================================================
#ifndef MpuImu_SubtopologyTopologyDefs_hpp
#define MpuImu_SubtopologyTopologyDefs_hpp

#include <Fw/Logger/Logger.hpp>
#include "MpuImuConfig/MpuImuSubtopologyConfig.hpp"

namespace MpuImu {
    struct SubtopologyState {
        ImuDevice device;
    };

    struct TopologyState {
        SubtopologyState mpu;
    };
}
#endif // MpuImu_SubtopologyTopologyDefs_hpp
