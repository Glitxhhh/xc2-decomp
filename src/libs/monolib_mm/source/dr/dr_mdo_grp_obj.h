#pragma once
#include "dr/dr_mdl_base.h"
#include "types.h"

namespace ml {

class DrMdlObj;

class DrMdoGrpObj : public DrMdlBase {
public:
  DrMdoGrpObj(int viewNum, u32 num);
  ~DrMdoGrpObj() override;
  void update() override;
  void dispOffUpdate() override;
  void resourceInit() override;
  void shadowRender() override;
  bool shadowCacheRender(DrPixlShadowCacheObj &cache) override;
  void shadowCacheOnlyRender() override;
  void callShadowCacheUpdate(u64 flags) override;
  void occRender() override;
  DrMdlObj *createInstantMdl(const void *data, const char *name, u32 index);
  void callNomSetupRender();
  void callZSortNomZpreePassRender();
  void callZSortThicknessRenderFirst();
  void callZSortThicknessRenderSecond();
  void callZSortNomRender();
  void callZSortGBuffRender();
  void callZSortLightPrePassRender();
  void callZSortNomAlphaRender();
  void callZSortNomSpAlphaRender();
  void callZSortNomRefractionRender();

  u8 _28[0x98 - 0x28];
};

static_assert(sizeof(DrMdoGrpObj) == 0x98, "");

} // namespace ml
