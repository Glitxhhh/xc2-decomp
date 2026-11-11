#pragma once
#include <stddef.h>

#include "dr/dr_res_mdo_seam_res.h"
#include "types.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace ml {
class DrMdoCtlSeamInstMap;
class DrPixlShadowCacheObj;
class DrPixlShadowObj;
class DrResMdoSeamWrkPosInst;
struct MdoWrkMatRes;
struct unknown721;
class DrResMdoVertex;
class DrResMdoInstAnmObj;

class DrResMdoSeamWrkInst : public unknown133<DrResMdoSeamWrkInst> {
public:
  // Inferred role: header of the instance map data; original type name unknown.
  struct unknown001 {
    u8 _00[0x2c];
    s32 unknown2c; // Inferred role: model index offset; original member name unknown.
  };

  // Inferred role: model info of the instance map; original type name unknown.
  struct unknown002 {
    u8 _00[0x20];
  };

  DrResMdoSeamWrkInst();
  virtual ~DrResMdoSeamWrkInst();
  void release();
  void beginMdl();
  void linkReadMdl();
  void linkReadMdl(u32 index);
  u32 isSubMdl(u32 index);
  void releaseCache(DrMdoCtlSeamInstMap *ctl);
  void callShadowCacheInstUpdate(u64 mask);
  void occRender();
  void seachDefShadowInstMapRender(DrPixlShadowObj *shadow, DrMdoCtlSeamInstMap *ctl);
  bool seachShadowInstMapRender(DrPixlShadowCacheObj &cache, DrMdoCtlSeamInstMap *ctl);
  unknown002 *getMdlInfo();
  bool setEtcPosCache(mtl::ALLOC_HANDLE handle, int index, DrResMdoSeamMemObj *memObj, const DrResMdoInstAnmObj *anm);

  const unknown721 *unknown18; // Inferred role: instance map entry; original member name unknown.
  const unknown001 *unknown20; // Inferred role: instance map header; original member name unknown.
  u8 _28[0x50 - 0x28];
  MdoWrkMatRes *unknown50;   // Inferred role: material work; original member name unknown.
  void *unknown58;           // Inferred role: allocated work; original member name unknown.
  DrResMdoVertex *unknown60; // Inferred role: vertex; original member name unknown.
  u32 unknown68;             // Inferred role: inst map index; original member name unknown.
  u8 _6c[0x70 - 0x6c];
  u32 unknown70; // Inferred role: position model count; original member name unknown.
  u32 unknown74; // Inferred role: unknown, cleared by the constructor; original member name unknown.
  u8 _78[0x84 - 0x78];
  s32 unknown84; // Inferred role: memory size; original member name unknown.
  s16 unknown88; // Inferred role: read count; original member name unknown.
  u16 unknown8a; // Inferred role: state flags; original member name unknown.
  u8 _8c[0x98 - 0x8c];
  u32 unknown98; // Inferred role: unknown, cleared by the constructor; original member name unknown.
  u8 _9c[0xc8 - 0x9c];
  u32 *unknownc8;       // Inferred role: read model bit table; original member name unknown.
  const u32 *unknownd0; // Inferred role: sub model bit table; original member name unknown.
  u8 _d8[0x108 - 0xd8];
  DrResMdoSeamMemObj *unknown108; // Inferred role: memory object; original member name unknown.
  u8 _110[0x118 - 0x110];
  DrResMdoSeamWrkPosInst *unknown118; // Inferred role: position objects; original member name unknown.
  u8 _120[0x128 - 0x120];
  DrResMdoSeamWrkPosInst *unknown128; // Inferred role: current position object; original member name unknown.
  DrResMdoSeamWrkInst *unknown130;    // Inferred role: linked inst map; original member name unknown.
  u8 _138[0x140 - 0x138];
  s32 unknown140; // Inferred role: position object count; original member name unknown.
  s32 unknown144; // Inferred role: unknown, cleared by the constructor; original member name unknown.
  u8 _148[0x14c - 0x148];
  s32 unknown14c; // Inferred role: model info count; original member name unknown.
  u16 unknown150; // Inferred role: model info index; original member name unknown.
  u8 _152[0x156 - 0x152];
  u16 unknown156; // Inferred role: shadow flags; original member name unknown.
  u32 unknown158; // Inferred role: shadow cache flags; original member name unknown.
  u8 _15c[0x1a0 - 0x15c];
  unknown002 *unknown1a0; // Inferred role: model infos; original member name unknown.
  u8 _1a8[0x1b0 - 0x1a8];
  void *unknown1b0; // Inferred role: unknown work, cleared by the constructor; original member name unknown.
  void *unknown1b8; // Inferred role: unknown work, cleared by the constructor; original member name unknown.
  u8 _1c0[0x1c8 - 0x1c0];
};

static_assert(offsetof(DrResMdoSeamWrkInst, unknown20) == 0x20, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown18) == 0x18, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown50) == 0x50, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown68) == 0x68, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown84) == 0x84, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown108) == 0x108, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown88) == 0x88, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknownc8) == 0xc8, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknownd0) == 0xd0, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown150) == 0x150, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown14c) == 0x14c, "");
static_assert(offsetof(DrResMdoSeamWrkInst, unknown1a0) == 0x1a0, "");
static_assert(sizeof(DrResMdoSeamWrkInst::unknown002) == 0x20, "");
static_assert(sizeof(DrResMdoSeamWrkInst) == 0x1c8, "");

} // namespace ml
