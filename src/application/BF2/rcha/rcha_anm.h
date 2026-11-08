#pragma once
#include <stddef.h>

#include "mm_mtl/fixstr.h"
#include "types.h"

// Animation track of the Rcha resources. Declared from the symbols _ZNK7RchaAnm8getValueEf (0x710069ca9c) and
// _ZNK7RchaAnm11getValueIntEf (0x710069ca6c); RchaNode keeps 48 of them. The fields between the name and the hash are
// not reconstructed.
class RchaAnm {
public:
  f32 getValue(f32 frame) const;
  int getValueInt(f32 frame) const;

  mm::mtl::FixStr<64> unknown00; // Inferred role: name; original member name unknown.
  u8 _44[0x84 - 0x44];
  u32 unknown84; // Inferred role: name hash; original member name unknown.
};

static_assert(offsetof(RchaAnm, unknown84) == 0x84, "");
static_assert(sizeof(RchaAnm) == 0x88, "");
