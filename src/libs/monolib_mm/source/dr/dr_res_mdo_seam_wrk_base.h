#pragma once
#include <stddef.h>

#include "dr/dr_res_mdo_seam_res.h"
#include "types.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace grlib {
class CGLibTriUniformArray;
} // namespace grlib

namespace ml {
class DrCalcClipMan;
class DrCalcViewWork;
class DrMdoCtlSeamBaseMap;
class DrPixlShadowCacheObj;
class DrPixlShadowObj;
class DrResMdoAlpTbl;
class DrResMdoSeamWrkBaseVertex;
struct MdoWrkMatRes;
struct MdsSeamBaseMapHead;
struct MdsSeamOfsTexTblData;
class DrResMdoSeamParmRead;

class DrResMdoSeamWrkBase : public unknown133<DrResMdoSeamWrkBase> {
public:
  DrResMdoSeamWrkBase();
  virtual ~DrResMdoSeamWrkBase();
  void release();
  bool update(DrCalcViewWork *view, const DrResMdoSeamParmRead *parmRead, bool isOpen, u32 flags);
  u32 updateRenderList(DrCalcViewWork *view, DrCalcClipMan *clip, u16 *textureFlags, DrResMdoSeamTexture *textures, u16 *texListFlags, DrResMdoSeamTexList *texLists, DrMdoCtlSeamBaseMap *ctl,
                       const MdsSeamOfsTexTblData *table, u32 flags);
  void setupWork(MdoWrkMatRes *matRes, grlib::CGLibTriUniformArray *uniforms, mtl::ALLOC_HANDLE handle, DrMdoCtlSeamBaseMap *ctl, const MdsSeamBaseMapHead *head, u32 max);
  void beginBaseMapRenderList();
  void callShadowCacheBaseUpdate(u64 mask);
  void beginRender();
  void endRender();
  void selectVertex(int index);
  void releaseCache(DrMdoCtlSeamBaseMap *ctl);
  bool seachShadowBaseMapRender(DrPixlShadowCacheObj &cache, DrMdoCtlSeamBaseMap *ctl);
  void seachDefShadowBaseMapRender(DrPixlShadowObj *shadow, DrMdoCtlSeamBaseMap *ctl);

  u8 _18[0x68 - 0x18];
  MdoWrkMatRes *unknown68;              // Inferred role: material work; original member name unknown.
  void *unknown70;                      // Inferred role: allocated buffer; original member name unknown.
  DrResMdoSeamWrkBaseVertex *unknown78; // Inferred role: vertices; original member name unknown.
  u8 _80[0x84 - 0x80];
  u32 unknown84; // Inferred role: base map index; original member name unknown.
  u8 _88[0x8c - 0x88];
  u32 unknown8c; // Inferred role: render count; original member name unknown.
  u32 unknown90; // Inferred role: render count; original member name unknown.
  u32 unknown94; // Inferred role: render count; original member name unknown.
  u64 unknown98; // Inferred role: shadow cache update mask; original member name unknown.
  s32 unknowna0; // Inferred role: state flags, cleared by the constructor; original member name unknown.
  u8 _a4[0xb0 - 0xa4];
  s32 unknownb0; // Inferred role: allocated buffer count; original member name unknown.
  s32 unknownb4; // Inferred role: memory size; original member name unknown.
  u8 _b8[0xe0 - 0xb8];
  void *unknowne0; // Inferred role: unknown, cleared by the constructor; original member name unknown.
  u32 *unknowne8;  // Inferred role: unknown, cleared by the constructor; original member name unknown.
  u8 **unknownf0;  // Inferred role: shadow bit tables; original member name unknown.
  u32 unknownf8;   // Inferred role: shadow bit table size; original member name unknown.
  u8 _fc[0x110 - 0xfc];
  u8 *unknown110; // Inferred role: render list memory; original member name unknown.
  u8 _118[0x158 - 0x118];
  DrResMdoSeamMemObj *unknown158; // Inferred role: memory object; original member name unknown.
  u8 _160[0x168 - 0x160];
  DrResMdoAlpTbl *unknown168; // Inferred role: alpha table; original member name unknown.
  s32 unknown170;             // Inferred role: render list num; original member name unknown.
  s32 unknown174;             // Inferred role: render list size; original member name unknown.
  s16 unknown178;             // Inferred role: selected vertex; original member name unknown.
  s16 unknown17a;             // Inferred role: unknown, cleared by the constructor; original member name unknown.
  s16 unknown17c;             // Inferred role: unknown, cleared by the constructor; original member name unknown.
  s16 unknown17e;             // Inferred role: vertex count; original member name unknown.
};

static_assert(offsetof(DrResMdoSeamWrkBase, unknown68) == 0x68, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknown78) == 0x78, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknown84) == 0x84, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknown8c) == 0x8c, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknown98) == 0x98, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknownb4) == 0xb4, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknown158) == 0x158, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknownf0) == 0xf0, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknown110) == 0x110, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknown170) == 0x170, "");
static_assert(offsetof(DrResMdoSeamWrkBase, unknown178) == 0x178, "");
static_assert(sizeof(DrResMdoSeamWrkBase) == 0x180, "");

} // namespace ml
