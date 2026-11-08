#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;

// Layout evidence: the constructor (0x71003419d4) initializes the members up to 0x30, dispose (0x7100341a8c) reads the
// handle at 0x00, the index at 0x08 and the fade time at 0x18 and clears the flag at 0x30, and the destructors of its
// owners (GfComBehaviorNpc at 0x2a0) call dispose.
class GfFieldLookIk {
public:
  ~GfFieldLookIk() { dispose(); }

  void dispose();

  GF_OBJ_HANDLE *unknown00; // Inferred role: object; original member name unknown.
  u32 unknown08;            // Inferred role: index of the look solver in the plugin of the object; original member name unknown.
  f32 unknown0c;            // Inferred role: look range; original member name unknown.
  f32 unknown10;            // Role and original member name unknown.
  f32 unknown14;            // Role and original member name unknown.
  f32 unknown18;            // Inferred role: fade time; original member name unknown.
  bool unknown1c;           // Inferred role: look enabled; original member name unknown.
  mm::Vec3 unknown20;       // Inferred role: current look target; original member name unknown.
  bool unknown30;           // Inferred role: look active; original member name unknown.
};

static_assert(offsetof(GfFieldLookIk, unknown08) == 0x08, "");
static_assert(offsetof(GfFieldLookIk, unknown0c) == 0x0c, "");
static_assert(offsetof(GfFieldLookIk, unknown18) == 0x18, "");
static_assert(offsetof(GfFieldLookIk, unknown1c) == 0x1c, "");
static_assert(offsetof(GfFieldLookIk, unknown20) == 0x20, "");
static_assert(offsetof(GfFieldLookIk, unknown30) == 0x30, "");
static_assert(sizeof(GfFieldLookIk) == 0x40, "");

} // namespace gf
