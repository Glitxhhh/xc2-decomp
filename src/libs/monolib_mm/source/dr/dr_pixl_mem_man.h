#pragma once
#include <stddef.h>

#include "mm_mtl/singleton.h"
#include "types.h"

namespace ml {

class DrPixlMemMan : public mm::mtl::PtrSingleton<DrPixlMemMan> {
public:
  // Inferred role: memory sizes of one resource category; original type name unknown.
  struct unknown001 {
    u8 _000[0x1a4];
    u32 unknown1a4[6]; // Inferred role: scale down target sizes of the tone map; original member name unknown.
    u8 _1bc[0x210 - 0x1bc];
  };

  DrPixlMemMan();
  virtual ~DrPixlMemMan();
  void setupMemBuff();

  unknown001 unknown008[2]; // Inferred role: memory sizes per resource category; original member name unknown.
  u8 _428[0x434 - 0x428];
  u32 unknown434; // Inferred role: mem1 alpha free; original member name unknown.
};

static_assert(sizeof(DrPixlMemMan::unknown001) == 0x210, "");
static_assert(offsetof(DrPixlMemMan, unknown008) == 0x008, "");
static_assert(offsetof(DrPixlMemMan, unknown434) == 0x434, "");

} // namespace ml
