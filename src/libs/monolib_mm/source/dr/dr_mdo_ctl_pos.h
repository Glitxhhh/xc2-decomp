#pragma once
#include <stddef.h>

#include "dr/dr_mdl_obj.h"
#include "dr/dr_res_mdo_inst_anm_obj.h"
#include "types.h"

namespace grlib {
class CGLibVtxInstans;
} // namespace grlib

namespace ml {

class DrCalcCpPlaneObj;
class DrCalcViewWork;
class DrPixlShadowObj;
class DrResMdoInstMdlInfo;
class DrResMdoPntAlphaMan;
class DrResMdoPos;
class DrResMdoPosAddList;
class DrResMdoSortPos;
class DrResWrkClipList;
struct _MdoInstanceWork;
struct MdoArgInst;
struct MdsMdlInfoHeader;
class DrPixlShadowCacheObj;

struct MdsPosRangeTreeData {
  f32 unknown00[3]; // Inferred role: center; original member name unknown.
  f32 unknown0c;    // Inferred role: radius; original member name unknown.
  f32 unknown10;    // Inferred role: squared render distance; original member name unknown.
  u32 unknown14;    // Inferred role: offset of the child tree indices; original member name unknown.
  u8 _18[0x1c - 0x18];
  u16 unknown1c; // Inferred role: child tree count; original member name unknown.
  u16 unknown1e; // Inferred role: position count; original member name unknown.
};

static_assert(offsetof(MdsPosRangeTreeData, unknown0c) == 0x0c, "");
static_assert(offsetof(MdsPosRangeTreeData, unknown10) == 0x10, "");
static_assert(offsetof(MdsPosRangeTreeData, unknown14) == 0x14, "");
static_assert(offsetof(MdsPosRangeTreeData, unknown1c) == 0x1c, "");
static_assert(offsetof(MdsPosRangeTreeData, unknown1e) == 0x1e, "");
static_assert(sizeof(MdsPosRangeTreeData) == 0x20, "");

class DrMdoCtlPos : public DrMdlObj {
public:
  // Inferred role: position resource header; original type name unknown.
  struct unknown017 {
    u8 _00[0x28 - 0x00];
    u32 unknown28; // Inferred role: offset of the range trees; original member name unknown.
    s32 unknown2c; // Inferred role: range tree count; original member name unknown.
  };

  static const int INS_RENDERBUFF_SIZE = 0xbd000;

  ~DrMdoCtlPos() override;
  void update() override;
  void dispOffUpdate() override;
  void resourceInit() override;
  void shadowRender() override;
  bool shadowCacheRender(DrPixlShadowCacheObj &cache) override;
  void shadowCacheAddRender(int index) override;
  void callShadowCacheUpdate(u64 flags) override;
  void occRender() override;
  void setDeleteCall(int deleteCall) override;
  void releasePos();
  void updatePos();
  void createMdlList();
  void beginRenderListPos();
  bool chankRenderMdl(const MdsPosRangeTreeData *tree, MdoArgInst &arg);
  bool clipRenderMdl(const MdsPosRangeTreeData *tree, MdoArgInst &arg);
  void chankShadowRenderMdl(const MdsPosRangeTreeData *tree, DrPixlShadowCacheObj &cache);
  void clipShadowRenderMdl(const MdsPosRangeTreeData *tree, DrPixlShadowCacheObj &cache);
  void nomTreeShadowRenderMdl(const MdsPosRangeTreeData *tree, DrPixlShadowObj *shadow);
  void createRenderDisplayList(const MdsMdlInfoHeader *header, int index, _MdoInstanceWork *work, grlib::CGLibVtxInstans *instans, int count);
  void callDisplistPrePsssRender(int param);
  void callDisplistRender(int param);
  void callZpreePassRenderPosAll();
  void callRenderPosAll();
  void callRefractionRenderPosAll();
  void callThicknessRenderFirstPosAll();
  void callThicknessRenderSecondPosAll();
  void callGBuffRenderPosAll();
  void callLightPrePassRenderPosAll();
  void callAlphaRenderPosAll();
  void callSpAlphaRenderPosAll();
  void createThicknessRenderFirstDisplayList();
  void createThicknessRenderSecondDisplayList();
  void createThicknessRenderDisplayListSub(bool isFirst);
  void createZBuffRenderDisplayList();
  void callPosRender(u32 renderType);

  u8 _190[0x1a0 - 0x190];
  u32 unknown1a0; // Inferred role: render count; original member name unknown.
  u8 _1a4[0x1a8 - 0x1a4];
  const unknown017 *unknown1a8; // Inferred role: position resource header; original member name unknown.
  u8 _1b0[0x1c8 - 0x1b0];
  const MdsPosRangeTreeData *unknown1c8; // Inferred role: range trees; original member name unknown.
  u8 _1d0[0x1d8 - 0x1d0];
  s32 unknown1d8; // Inferred role: position count; original member name unknown.
  u8 _1dc[0x1e0 - 0x1dc];
  DrResMdoPos *unknown1e0;       // Inferred role: positions; original member name unknown.
  DrResMdoInstAnmObj unknown1e8; // Inferred role: inst anm object; original member name unknown.
  DrResWrkClipList *unknown218;  // Inferred role: clip list; original member name unknown.
  void *unknown220;              // Inferred role: work memory; original member name unknown.
  void **unknown228;             // Inferred role: allocated buffers; original member name unknown.
  void *unknown230;              // Inferred role: allocated memory; original member name unknown.
  s32 unknown238;                // Inferred role: allocated buffer count; original member name unknown.
  u8 _23c[0x248 - 0x23c];
  s32 unknown248; // Inferred role: render buffer offset; original member name unknown.
  u8 _24c[0x250 - 0x24c];
  DrResMdoPosAddList *unknown250;  // Inferred role: add list; original member name unknown.
  DrResMdoInstMdlInfo *unknown258; // Inferred role: inst mdl info; original member name unknown.
  u16 unknown260;                  // Inferred role: render list count; original member name unknown.
  u16 unknown262;                  // Inferred role: second render list count; original member name unknown.
  u8 _264[0x268 - 0x264];
  DrResMdoSortPos *unknown268; // Inferred role: z sort object; original member name unknown.
  DrResMdoPos **unknown270;    // Inferred role: render positions; original member name unknown.
  u8 _278[0x2a8 - 0x278];
  DrResMdoPntAlphaMan *unknown2a8; // Inferred role: pnt alpha man; original member name unknown.
  u8 _2b0[0x2c0 - 0x2b0];
  void *unknown2c0; // Inferred role: first render list entry; original member name unknown.
  u8 _2c8[0x2d8 - 0x2c8];
  u32 unknown2d8; // Inferred role: render list size; original member name unknown.
  u8 _2dc[0x2e0 - 0x2dc];
  u64 unknown2e0[6]; // Inferred role: render list values cleared every frame; original member name unknown.
  u8 _310[0x340 - 0x310];
  u64 unknown340;             // Inferred role: render list value cleared every frame; original member name unknown.
  DrCalcViewWork *unknown348; // Inferred role: view work; original member name unknown.
  u8 _350[0x358 - 0x350];
  DrCalcCpPlaneObj *unknown358; // Inferred role: clip plane object; original member name unknown.
  u32 unknown360;               // Inferred role: render count; original member name unknown.
  u8 _364[0x368 - 0x364];
  u64 unknown368; // Inferred role: shadow cache mask; original member name unknown.
  u64 unknown370; // Inferred role: shadow cache render mask; original member name unknown.
  u32 unknown378; // Inferred role: shadow cache render count; original member name unknown.
};

static_assert(offsetof(DrMdoCtlPos, unknown1a0) == 0x1a0, "");
static_assert(offsetof(DrMdoCtlPos, unknown1a8) == 0x1a8, "");
static_assert(offsetof(DrMdoCtlPos, unknown1c8) == 0x1c8, "");
static_assert(offsetof(DrMdoCtlPos, unknown1d8) == 0x1d8, "");
static_assert(offsetof(DrMdoCtlPos, unknown1e0) == 0x1e0, "");
static_assert(offsetof(DrMdoCtlPos, unknown1e8) == 0x1e8, "");
static_assert(offsetof(DrMdoCtlPos, unknown218) == 0x218, "");
static_assert(offsetof(DrMdoCtlPos, unknown238) == 0x238, "");
static_assert(offsetof(DrMdoCtlPos, unknown248) == 0x248, "");
static_assert(offsetof(DrMdoCtlPos, unknown250) == 0x250, "");
static_assert(offsetof(DrMdoCtlPos, unknown258) == 0x258, "");
static_assert(offsetof(DrMdoCtlPos, unknown260) == 0x260, "");
static_assert(offsetof(DrMdoCtlPos, unknown268) == 0x268, "");
static_assert(offsetof(DrMdoCtlPos, unknown2a8) == 0x2a8, "");
static_assert(offsetof(DrMdoCtlPos, unknown2c0) == 0x2c0, "");
static_assert(offsetof(DrMdoCtlPos, unknown2d8) == 0x2d8, "");
static_assert(offsetof(DrMdoCtlPos, unknown2e0) == 0x2e0, "");
static_assert(offsetof(DrMdoCtlPos, unknown340) == 0x340, "");
static_assert(offsetof(DrMdoCtlPos, unknown348) == 0x348, "");
static_assert(offsetof(DrMdoCtlPos, unknown358) == 0x358, "");
static_assert(offsetof(DrMdoCtlPos, unknown360) == 0x360, "");
static_assert(offsetof(DrMdoCtlPos, unknown368) == 0x368, "");
static_assert(offsetof(DrMdoCtlPos, unknown370) == 0x370, "");
static_assert(offsetof(DrMdoCtlPos, unknown378) == 0x378, "");

} // namespace ml
