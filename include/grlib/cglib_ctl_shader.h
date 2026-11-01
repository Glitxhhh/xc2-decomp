#pragma once
#include "types.h"

namespace grlib {
class CGLibDecShader;
class CGLibDecShdExtTbl;
class CGLibDblUniformBlock;
class CGLibEtcUniformBlock;
class CGLibOneUniformBlock;
class CGLibSampler;
class CGLibTriUniformBlock;
class CGLibVtxFetch;

enum GrlUtilVertFetch {
  GRL_UTIL_VERT_FETCH_UNKNOWN_0 = 0,
  GRL_UTIL_VERT_FETCH_UNKNOWN_1 = 1,
};

enum GrlUtilSampler {
  GRL_UTIL_SAMPLER_UNKNOWN_1 = 1,
};

class CGLibCtlShader {
public:
  static void setShader(CGLibDecShader &shader, CGLibVtxFetch &fetch);
  static void setShader(CGLibDecShdExtTbl &shader, CGLibVtxFetch &fetch);
  static void setComputeShader(CGLibDecShader &shader);
  static void setComputeShader(CGLibDecShdExtTbl &shader);
  static void setDispatchCompute(u32 groupsX, u32 groupsY, u32 groupsZ);
  static void setDispatchComputeIndirect(const CGLibEtcUniformBlock &block, u32 offset);
  static void setDispatchComputeIndirect(const CGLibOneUniformBlock &block, u32 offset);
  static void setDispatchComputeIndirect(const CGLibDblUniformBlock &block, u32 offset);
  static void setDispatchComputeIndirect(const CGLibTriUniformBlock &block, u32 offset);
  static void setMemoryBarrier();
  static void setMemoryBarrierBit(u32 bits);
  static CGLibDecShader *getDecShader();
  static CGLibVtxFetch *getVtxFetch(GrlUtilVertFetch type);
  static CGLibSampler *getSampler(GrlUtilSampler type);
};

} // namespace grlib
