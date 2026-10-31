#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;

class GfFobjGottenEffectManager {
public:
  // Layout evidence: createEffect (0x71002f60dc) fills the four curve points, the effect handle and the target
  // before Vector<EffectInfo>::push_back (0x71002f6424), whose copy moves the Vec3 members one by one and the bytes
  // from 0x40 to 0x54 raw; update (0x71002f6558) advances the time at 0x50 and moves the effect along the curve.
  struct EffectInfo {
    mm::Vec3 unknown00;       // Inferred role: start position; original member name unknown.
    mm::Vec3 unknown10;       // Inferred role: first control point; original member name unknown.
    mm::Vec3 unknown20;       // Inferred role: second control point; original member name unknown.
    mm::Vec3 unknown30;       // Inferred role: target position; original member name unknown.
    u32 unknown40;            // Inferred role: effect handle; original member name unknown.
    GF_OBJ_HANDLE *unknown48; // Inferred role: target object; original member name unknown.
    f32 unknown50;            // Inferred role: elapsed time; original member name unknown.
  };
};

static_assert(offsetof(GfFobjGottenEffectManager::EffectInfo, unknown10) == 0x10, "");
static_assert(offsetof(GfFobjGottenEffectManager::EffectInfo, unknown20) == 0x20, "");
static_assert(offsetof(GfFobjGottenEffectManager::EffectInfo, unknown30) == 0x30, "");
static_assert(offsetof(GfFobjGottenEffectManager::EffectInfo, unknown40) == 0x40, "");
static_assert(offsetof(GfFobjGottenEffectManager::EffectInfo, unknown48) == 0x48, "");
static_assert(offsetof(GfFobjGottenEffectManager::EffectInfo, unknown50) == 0x50, "");
static_assert(sizeof(GfFobjGottenEffectManager::EffectInfo) == 0x60, "");

} // namespace gf
