#pragma once
#include <stddef.h>

#include "dr/dr_res_mdo_seam_res.h"
#include "types.h"

namespace grlib {
class CGLibVtxInstans;
} // namespace grlib

namespace ml {
struct MdoWrkMatRes;
struct MdsSeamLowMapHead;

class DrResMdoSeamWrkLow : public unknown133<DrResMdoSeamWrkLow> {
public:
  DrResMdoSeamWrkLow();
  virtual ~DrResMdoSeamWrkLow();
  void release();
  void changeMemCall();

  const MdsSeamLowMapHead *unknown18; // Inferred role: low map header; original member name unknown.
  u8 _20[0x28 - 0x20];
  MdoWrkMatRes *unknown28;       // Inferred role: material work; original member name unknown.
  DrResMdoSeamMemObj *unknown30; // Inferred role: memory object; original member name unknown.
  u8 _38[0x40 - 0x38];
  grlib::CGLibVtxInstans *unknown40; // Inferred role: instance vertex; original member name unknown.
  u8 _48[0x88 - 0x48];
  void *unknown88; // Inferred role: allocated buffer; original member name unknown.
  u8 _90[0x9c - 0x90];
  u32 unknown9c; // Inferred role: state flags; original member name unknown.
  u32 unknowna0; // Inferred role: low map index; original member name unknown.
  u32 unknowna4; // Inferred role: unknown, cleared by the constructor; original member name unknown.
  u32 unknowna8; // Inferred role: unknown, cleared by the constructor; original member name unknown.
  u32 unknownac; // Inferred role: unknown, cleared by the constructor; original member name unknown.
  s32 unknownb0; // Inferred role: memory size; original member name unknown.
  u32 unknownb4; // Inferred role: unknown, cleared by the constructor; original member name unknown.
};

static_assert(offsetof(DrResMdoSeamWrkLow, unknown18) == 0x18, "");
static_assert(offsetof(DrResMdoSeamWrkLow, unknown28) == 0x28, "");
static_assert(offsetof(DrResMdoSeamWrkLow, unknown30) == 0x30, "");
static_assert(offsetof(DrResMdoSeamWrkLow, unknown40) == 0x40, "");
static_assert(offsetof(DrResMdoSeamWrkLow, unknown88) == 0x88, "");
static_assert(offsetof(DrResMdoSeamWrkLow, unknown9c) == 0x9c, "");
static_assert(offsetof(DrResMdoSeamWrkLow, unknowna0) == 0xa0, "");
static_assert(offsetof(DrResMdoSeamWrkLow, unknownb0) == 0xb0, "");
static_assert(sizeof(DrResMdoSeamWrkLow) == 0xb8, "");

} // namespace ml
