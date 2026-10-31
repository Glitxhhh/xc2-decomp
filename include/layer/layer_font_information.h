#pragma once
#include "mm_mtl/vector.h"
#include "types.h"

namespace layer {

class LayerFontInformation {
public:
  // Inferred layout of an information entry (0x24 bytes, from the allocation size); original type and member names unknown.
  struct unknown001 {
    u8 _00[0x24];
  };

  LayerFontInformation(u32 num);
  ~LayerFontInformation();

  mm::mtl::Vector<unknown001> unknown00; // Inferred role: information entries; original member name unknown.
};

static_assert(sizeof(LayerFontInformation::unknown001) == 0x24, "");
static_assert(sizeof(LayerFontInformation) == 0x28, "");

} // namespace layer
