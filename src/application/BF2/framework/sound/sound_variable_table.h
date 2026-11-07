#pragma once
#include <stddef.h>

#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {

// Layout evidence: the constructor (1.0.0: 0x71001acbfc) stores the root of the tree at 0x00, zeroes the count at 0x08 and stores the
// process allocator at 0x10; the tree is a mm::mtl::Map<mm::mtl::FixStr<64>, int> (the destructor frees its nodes) and gf::GfComSound
// places its next member 0x20 bytes after the table.
class SoundVariableTable {
public:
  void setVariable(const char *name, int value);

  void *unknown00;                // Inferred role: root node of the variable tree; original member name unknown.
  u32 unknown08;                  // Inferred role: variable count; original member name unknown.
  mm::mtl::IAllocator *unknown10; // Inferred role: allocator; original member name unknown.
  u8 _18[0x20 - 0x18];
};

static_assert(offsetof(SoundVariableTable, unknown08) == 0x08, "");
static_assert(offsetof(SoundVariableTable, unknown10) == 0x10, "");
static_assert(sizeof(SoundVariableTable) == 0x20, "");

} // namespace fw
