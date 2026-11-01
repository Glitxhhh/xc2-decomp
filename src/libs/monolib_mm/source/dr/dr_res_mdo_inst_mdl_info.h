#pragma once
#include <stddef.h>

#include "mm_mtl/fixstr.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {
class DrResMdoInstMdlObj;

struct DrResMdlInstMdlArg {
  const mm::Vec3 *unknown00; // Inferred role: view pos; original member name unknown.
  const mm::Vec3 *unknown08; // Inferred role: second view pos, nullptr when there is none; original member name unknown.
  bool unknown10;            // Inferred role: disp; original member name unknown.
  s32 unknown14;             // Inferred role: view num; original member name unknown.
  f32 unknown18;             // Inferred role: frame spd; original member name unknown.
  u8 _1c[0x58 - 0x1c];
};

static_assert(offsetof(DrResMdlInstMdlArg, unknown08) == 0x08, "");
static_assert(offsetof(DrResMdlInstMdlArg, unknown10) == 0x10, "");
static_assert(offsetof(DrResMdlInstMdlArg, unknown14) == 0x14, "");
static_assert(offsetof(DrResMdlInstMdlArg, unknown18) == 0x18, "");
static_assert(sizeof(DrResMdlInstMdlArg) == 0x58, "");

class DrResMdoInstMdlInfo {
public:
  // Inferred role: instance model resource header; original type name unknown.
  struct unknown001 {
    u8 _00[0x08];
    s32 unknown08; // Inferred role: model object count; original member name unknown.
  };

  DrResMdoInstMdlInfo();
  ~DrResMdoInstMdlInfo();
  void releaseWork();
  void releaseCall();
  void update(DrResMdlInstMdlArg &arg);
  static int calcWorkSize(const u8 *resource);
  static void release(DrResMdoInstMdlInfo *&info);

  s32 unknown00;                  // Inferred role: model object count; original member name unknown.
  DrResMdoInstMdlObj *unknown08;  // Inferred role: model objects; original member name unknown.
  mm::mtl::FixStr<256> unknown10; // Inferred role: resource folder path; original member name unknown.
  const u8 *unknown118;           // Inferred role: resource; original member name unknown.
  u32 unknown120;                 // Inferred role: state flags; original member name unknown.
};

static_assert(offsetof(DrResMdoInstMdlInfo, unknown08) == 0x08, "");
static_assert(offsetof(DrResMdoInstMdlInfo, unknown10) == 0x10, "");
static_assert(offsetof(DrResMdoInstMdlInfo, unknown118) == 0x118, "");
static_assert(offsetof(DrResMdoInstMdlInfo, unknown120) == 0x120, "");
static_assert(sizeof(DrResMdoInstMdlInfo) == 0x128, "");

} // namespace ml
