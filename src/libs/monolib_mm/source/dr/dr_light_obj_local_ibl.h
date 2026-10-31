#pragma once
#include <stddef.h>

#include "dr/dr_light_obj.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mm_math/mm_vec4.h"
#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
}

namespace ml {

// Layout from the constructor (1.0.0: 0x71008b7f8c) and setup (0x71008b7ff4).
class DrLightObjLocalIBL : public DrLightObj {
public:
  DrLightObjLocalIBL();
  ~DrLightObjLocalIBL() override;
  void updateIBL();

  mm::Vec3 unknown30;                   // Inferred role: zero cleared vector; original member name unknown.
  grlib::CGLibTextureBuffer *unknown40; // Inferred role: cube map texture; original member name unknown.
  int unknown48;                        // Inferred role: last usable mipmap level; original member name unknown.
  mm::Mat44 unknown50[3];               // Inferred role: SH matrices per color channel; original member name unknown.
  mm::Vec3 unknown110;                  // Inferred role: position; original member name unknown.
  f32 unknown120;                       // Inferred role: radius; original member name unknown.
  u32 unknown124;                       // Inferred role: influence shape; original member name unknown.
  u32 unknown128;                       // Inferred role: setting value; original member name unknown.
  mm::Vec3 unknown130;                  // Inferred role: influence size; original member name unknown.
  mm::Mat44 unknown140;                 // Inferred role: influence matrix; original member name unknown.
  mm::Mat44 unknown180;                 // Inferred role: inverse influence matrix; original member name unknown.
  u32 unknown1c0;                       // Inferred role: projection shape; original member name unknown.
  bool unknown1c4;                      // Inferred role: projection enabled; original member name unknown.
  mm::Mat44 unknown1d0;                 // Inferred role: inverse projection matrix; original member name unknown.
  mm::Vec4 unknown210;                  // Inferred role: inverse projection box max; original member name unknown.
  mm::Vec4 unknown220;                  // Inferred role: inverse projection box min; original member name unknown.
  mm::Vec3 unknown230;                  // Inferred role: setting vector; original member name unknown.
  void *unknown240;                     // Inferred role: setting pointer; original member name unknown.
};

static_assert(offsetof(DrLightObjLocalIBL, unknown30) == 0x30, "");
static_assert(offsetof(DrLightObjLocalIBL, unknown40) == 0x40, "");
static_assert(offsetof(DrLightObjLocalIBL, unknown48) == 0x48, "");
static_assert(offsetof(DrLightObjLocalIBL, unknown50) == 0x50, "");
static_assert(offsetof(DrLightObjLocalIBL, unknown110) == 0x110, "");
static_assert(offsetof(DrLightObjLocalIBL, unknown120) == 0x120, "");
static_assert(offsetof(DrLightObjLocalIBL, unknown124) == 0x124, "");
static_assert(offsetof(DrLightObjLocalIBL, unknown128) == 0x128, "");
static_assert(offsetof(DrLightObjLocalIBL, unknown130) == 0x130, "");
static_assert(offsetof(DrLightObjLocalIBL, unknown140) == 0x140, "");
static_assert(offsetof(DrLightObjLocalIBL, unknown180) == 0x180, "");
static_assert(offsetof(DrLightObjLocalIBL, unknown1c0) == 0x1c0, "");
static_assert(offsetof(DrLightObjLocalIBL, unknown1c4) == 0x1c4, "");
static_assert(offsetof(DrLightObjLocalIBL, unknown1d0) == 0x1d0, "");
static_assert(offsetof(DrLightObjLocalIBL, unknown210) == 0x210, "");
static_assert(offsetof(DrLightObjLocalIBL, unknown220) == 0x220, "");
static_assert(offsetof(DrLightObjLocalIBL, unknown230) == 0x230, "");
static_assert(offsetof(DrLightObjLocalIBL, unknown240) == 0x240, "");
static_assert(sizeof(DrLightObjLocalIBL) == 0x250, "");

} // namespace ml
