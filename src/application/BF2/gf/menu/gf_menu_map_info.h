#pragma once
#include <stddef.h>

#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

class GfMenuMapInfo : public mm::mtl::PtrSingleton<GfMenuMapInfo> {
public:
  // Layout evidence: getMapArea(int, u32) at 0x71003c8658 returns the elements of 0x48 bytes of the map asset and
  // getMapAreaFromName(int, const char *, MapAreaInfo &) copies one of them into a MapAreaInfo.
  struct MapAreaInfo {
    char unknown00[0x20]; // Inferred role: area name; original member name unknown.
    f32 unknown20;        // Inferred role: minimum x; original member name unknown.
    f32 unknown24;        // Inferred role: minimum y; original member name unknown.
    f32 unknown28;        // Inferred role: minimum z; original member name unknown.
    f32 unknown2c;        // Inferred role: maximum x; original member name unknown.
    f32 unknown30;        // Inferred role: maximum y; original member name unknown.
    f32 unknown34;        // Inferred role: maximum z; original member name unknown.
    u8 _38[0x48 - 0x38];
  };

  static void setCurrentMap(u32 map);
  static u32 getMapAreaCount(int index);
  static const MapAreaInfo *getMapArea(int index, u32 areaIndex);
  static const MapAreaInfo *getMapAreaFromName(int index, const char *name);
  static int getMapInfoIndex(const char *name);
};

static_assert(offsetof(GfMenuMapInfo::MapAreaInfo, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuMapInfo::MapAreaInfo, unknown34) == 0x34, "");
static_assert(sizeof(GfMenuMapInfo::MapAreaInfo) == 0x48, "");

} // namespace gf
