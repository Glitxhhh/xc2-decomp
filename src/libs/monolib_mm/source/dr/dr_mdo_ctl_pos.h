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
class DrResMdoInstMdlInfo;
struct _MdoInstanceWork;
struct MdsMdlInfoHeader;

class DrMdoCtlPos : public DrMdlObj {
public:
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

  u8 _190[0x1e8 - 0x190];
  DrResMdoInstAnmObj unknown1e8; // Inferred role: inst anm object; original member name unknown.
  u8 _218[0x258 - 0x218];
  DrResMdoInstMdlInfo *unknown258; // Inferred role: inst mdl info; original member name unknown.
  u8 _260[0x348 - 0x260];
  DrCalcViewWork *unknown348; // Inferred role: view work; original member name unknown.
  u8 _350[0x358 - 0x350];
  DrCalcCpPlaneObj *unknown358; // Inferred role: clip plane object; original member name unknown.
  u8 _360[0x368 - 0x360];
  u64 unknown368; // Inferred role: shadow cache mask; original member name unknown.
  u64 unknown370; // Inferred role: shadow cache render mask; original member name unknown.
  u32 unknown378; // Inferred role: shadow cache render count; original member name unknown.
};

static_assert(offsetof(DrMdoCtlPos, unknown1e8) == 0x1e8, "");
static_assert(offsetof(DrMdoCtlPos, unknown258) == 0x258, "");
static_assert(offsetof(DrMdoCtlPos, unknown348) == 0x348, "");
static_assert(offsetof(DrMdoCtlPos, unknown358) == 0x358, "");
static_assert(offsetof(DrMdoCtlPos, unknown368) == 0x368, "");
static_assert(offsetof(DrMdoCtlPos, unknown370) == 0x370, "");
static_assert(offsetof(DrMdoCtlPos, unknown378) == 0x378, "");

} // namespace ml
