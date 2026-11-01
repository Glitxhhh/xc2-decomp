#pragma once
#include <stddef.h>

#include "dr/dr_calc_clip_work_plane.h"
#include "grlib/cglib_depth_target.h"
#include "mm_math/mm_mat44.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {

class DrPixlShadowCacheObj : public grlib::CGLibDepthTarget {
public:
  void createShadow(int size, u32 resArea);
  void release();
  void begin();
  bool clipTest(const mm::Vec3 &position, f32 radius);
  void end();
  void setClear();
  void setNewGrid();
  void setBigMode(bool isBig);
  void setID(int id);
  void depthClear();

  u8 _800[0x808 - 0x800];
  u32 unknown808;       // Inferred role: flags; original member name unknown.
  s32 unknown80c;       // Inferred role: shadow size; original member name unknown.
  mm::Mat44 unknown810; // Inferred role: shadow matrix; original member name unknown.
  mm::Mat44 unknown850; // Inferred role: shadow view projection matrix; original member name unknown.
  u8 _890[0x8e8 - 0x890];
  u64 unknown8e8; // Inferred role: id mask; original member name unknown.
  u16 unknown8f0; // Inferred role: id; original member name unknown.
  u16 unknown8f2; // Inferred role: id; original member name unknown.
  u8 _8f4[0x900 - 0x8f4];
  DrCalcClipWorkPlane unknown900; // Inferred role: clip work; original member name unknown.
};

static_assert(offsetof(DrPixlShadowCacheObj, unknown808) == 0x808, "");
static_assert(offsetof(DrPixlShadowCacheObj, unknown80c) == 0x80c, "");
static_assert(offsetof(DrPixlShadowCacheObj, unknown810) == 0x810, "");
static_assert(offsetof(DrPixlShadowCacheObj, unknown850) == 0x850, "");
static_assert(offsetof(DrPixlShadowCacheObj, unknown8e8) == 0x8e8, "");
static_assert(offsetof(DrPixlShadowCacheObj, unknown8f2) == 0x8f2, "");
static_assert(offsetof(DrPixlShadowCacheObj, unknown900) == 0x900, "");

} // namespace ml
