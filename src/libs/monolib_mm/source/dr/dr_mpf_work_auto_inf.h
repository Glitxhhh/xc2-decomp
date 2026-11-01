#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

struct _MPFWorkAutoInf {
  u16 unknown00; // Inferred role: point count; original member name unknown.
  u16 unknown02; // Inferred role: state flags, bit 1 is in use; original member name unknown.
  f32 unknown04; // Inferred role: auto parameter copied from the owner; original member name unknown.
  f32 unknown08; // Inferred role: auto parameter copied from the owner; original member name unknown.
  f32 unknown0c; // Inferred role: auto parameter copied from the owner; original member name unknown.
  f32 unknown10; // Inferred role: auto parameter copied from the owner; original member name unknown.
  s16 unknown14; // Inferred role: auto parameter copied from the owner; original member name unknown.
  s16 unknown16; // Inferred role: auto parameter copied from the owner; original member name unknown.
  s16 unknown18; // Inferred role: auto parameter copied from the owner; original member name unknown.
  s16 unknown1a; // Inferred role: spare point count; original member name unknown.
  s32 unknown1c; // Inferred role: block size; original member name unknown.
  u8 _20[0x28 - 0x20];
  _MPFWorkAutoInf *unknown28; // Inferred role: first link of the work list; original member name unknown.
  _MPFWorkAutoInf *unknown30; // Inferred role: second link of the work list; original member name unknown.
  _MPFWorkAutoInf *unknown38; // Inferred role: following block; original member name unknown.
  _MPFWorkAutoInf *unknown40; // Inferred role: preceding block; original member name unknown.
};

static_assert(offsetof(_MPFWorkAutoInf, unknown02) == 0x02, "");
static_assert(offsetof(_MPFWorkAutoInf, unknown04) == 0x04, "");
static_assert(offsetof(_MPFWorkAutoInf, unknown10) == 0x10, "");
static_assert(offsetof(_MPFWorkAutoInf, unknown14) == 0x14, "");
static_assert(offsetof(_MPFWorkAutoInf, unknown1a) == 0x1a, "");
static_assert(offsetof(_MPFWorkAutoInf, unknown1c) == 0x1c, "");
static_assert(offsetof(_MPFWorkAutoInf, unknown28) == 0x28, "");
static_assert(offsetof(_MPFWorkAutoInf, unknown30) == 0x30, "");
static_assert(offsetof(_MPFWorkAutoInf, unknown38) == 0x38, "");
static_assert(offsetof(_MPFWorkAutoInf, unknown40) == 0x40, "");

} // namespace ml
