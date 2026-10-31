#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibSampler;
} // namespace grlib

namespace ml {
struct MdsMpfMatInfoHeader;

// Layout evidence: the constructor 0x7100868f7c clears 0x08 to 0x20, and setupSampler 0x7100868f88 stores the
// samplers it creates at this + 0x08 + index * 8 for three indices.
struct DrResMpfSampler {
  DrResMpfSampler(const MdsMpfMatInfoHeader *header);
  ~DrResMpfSampler();
  void setupSampler(const MdsMpfMatInfoHeader *header);
  void samplerRelease();

  u8 _00[0x08];
  grlib::CGLibSampler *unknown08[3]; // Inferred role: samplers of the three textures; original member name unknown.
};

static_assert(offsetof(DrResMpfSampler, unknown08) == 0x08, "");

} // namespace ml
