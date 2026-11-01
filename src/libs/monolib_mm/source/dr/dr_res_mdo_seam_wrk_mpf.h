#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {
class DrMdoCtlSeamMpfMap;
class DrResMdoSeamMemObj;
struct MdoWrkMatRes;

class DrResMdoSeamWrkMpf {
public:
  void releaseCache(DrMdoCtlSeamMpfMap *ctl);

  u8 _00[0x08 - 0x00];
  DrResMdoSeamWrkMpf *unknown08; // Inferred role: next object; original member name unknown.
  DrResMdoSeamWrkMpf *unknown10; // Inferred role: previous object; original member name unknown.
  DrResMdoSeamMemObj *unknown18; // Inferred role: memory object; original member name unknown.
  u8 _20[0x4c - 0x20];
  u16 unknown4c; // Inferred role: mpf map index; original member name unknown.
  u8 _4e[0x70 - 0x4e];
  MdoWrkMatRes *unknown70; // Inferred role: material work; original member name unknown.
  u8 _78[0xe8 - 0x78];
  s32 unknowne8; // Inferred role: memory size; original member name unknown.
  u8 _ec[0xf0 - 0xec];
};

static_assert(offsetof(DrResMdoSeamWrkMpf, unknown08) == 0x08, "");
static_assert(offsetof(DrResMdoSeamWrkMpf, unknown18) == 0x18, "");
static_assert(offsetof(DrResMdoSeamWrkMpf, unknown4c) == 0x4c, "");
static_assert(offsetof(DrResMdoSeamWrkMpf, unknown70) == 0x70, "");
static_assert(offsetof(DrResMdoSeamWrkMpf, unknowne8) == 0xe8, "");
static_assert(sizeof(DrResMdoSeamWrkMpf) == 0xf0, "");

} // namespace ml
