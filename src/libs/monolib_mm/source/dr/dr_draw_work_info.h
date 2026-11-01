#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ml {

class IDrDrawWorkInfo {
public:
  u8 _000[0xb0 - 0x000];
  mm::Vec3 unknownb0; // Inferred role: camera position; original member name unknown.
  u8 _c0[0x560 - 0x0c0];
  int unknown560; // Inferred role: loop; original member name unknown.
  u8 _564[0x580 - 0x564];
};

static_assert(offsetof(IDrDrawWorkInfo, unknownb0) == 0xb0, "");
static_assert(offsetof(IDrDrawWorkInfo, unknown560) == 0x560, "");
static_assert(sizeof(IDrDrawWorkInfo) == 0x580, "");

} // namespace ml
