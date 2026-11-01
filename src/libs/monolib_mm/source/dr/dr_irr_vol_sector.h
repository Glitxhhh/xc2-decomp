#pragma once
#include <stddef.h>

#include "mm_math/mm_aabb.h"
#include "types.h"

namespace ml {
namespace irrvol {

struct SLightProbe {
  u8 _00[0x50];
};

static_assert(sizeof(SLightProbe) == 0x50, "");

struct SSectorInfo {
  mm::Aabb unknown00; // Inferred role: bounds, drawn by DrIrrVolResMan::drawDebugInfo; original member name unknown.
  u8 _20[0x40 - 0x20];
  const SLightProbe *unknown40; // Inferred role: probes; original member name unknown.
};

static_assert(offsetof(SSectorInfo, unknown40) == 0x40, "");

// One 0x30 byte entry of SGlobalInfo::unknown28: the DrIrrVolCascade constructor keeps a pointer to the entry of its cascade.
struct SCascadeInfo {
  f32 unknown00; // Inferred role: min x; original member name unknown.
  u8 _04[0x08 - 0x04];
  f32 unknown08; // Inferred role: min z; original member name unknown.
  u8 _0c[0x10 - 0x0c];
  f32 unknown10; // Inferred role: max x; original member name unknown.
  u8 _14[0x18 - 0x14];
  f32 unknown18; // Inferred role: max z; original member name unknown.
  u8 _1c[0x20 - 0x1c];
  f32 unknown20; // Inferred role: sector parameter, a float step that DrIrrVolMan::updateIrrVol adds to its update position; original member name unknown.
  f32 unknown24; // Inferred role: sector size; original member name unknown.
  u8 _28[0x30 - 0x28];
};

static_assert(offsetof(SCascadeInfo, unknown08) == 0x08, "");
static_assert(offsetof(SCascadeInfo, unknown18) == 0x18, "");
static_assert(offsetof(SCascadeInfo, unknown20) == 0x20, "");
static_assert(offsetof(SCascadeInfo, unknown24) == 0x24, "");
static_assert(sizeof(SCascadeInfo) == 0x30, "");

struct SGlobalInfo {
  u8 _00[0x20 - 0x00];
  u32 unknown20; // Inferred role: cascade max; original member name unknown.
  u8 _24[0x28 - 0x24];
  SCascadeInfo *unknown28; // Inferred role: cascades; original member name unknown.
};

static_assert(offsetof(SGlobalInfo, unknown20) == 0x20, "");
static_assert(offsetof(SGlobalInfo, unknown28) == 0x28, "");

class DrIrrVolSector {
public:
  DrIrrVolSector(const SSectorInfo *sectorInfo, const SCascadeInfo *cascadeInfo);
  ~DrIrrVolSector();
  const SLightProbe *getProbe(int index) const;

  const SSectorInfo *unknown00; // Inferred role: sector info; original member name unknown.
  f32 unknown08;                // Inferred role: sector parameter; original member name unknown.
};

static_assert(offsetof(DrIrrVolSector, unknown08) == 0x08, "");

} // namespace irrvol
} // namespace ml
