#pragma once

#include "dr/dr_mdo_ctl_seam_read.h"
#include "types.h"

namespace ml {
class DrMan;

class DrMdoCtlSeamAll : public DrMdoCtlSeamRead {
public:
  DrMdoCtlSeamAll(const void *data, const char *path, DrMan *man, int viewNum);
  ~DrMdoCtlSeamAll() override;
  void update() override;
  void dispOffUpdate() override;
  void noOffScreenUpdate() override;
  void resourceInit() override;
  void shadowRender() override;
  bool shadowCacheRender(DrPixlShadowCacheObj &cache) override;
  void shadowCacheAddRender(int index) override;
  void callShadowCacheUpdate(u64 flags) override;
  void occRender() override;
  void setDeleteCall(int deleteCall) override;
  virtual void debugRender();
  void releaseSeamAll();
  bool callDeleteUpdate();
  u32 getSeamBaseMdlMax() const;
  u32 getSeamInstMdlMax() const;
  u32 getSeamMpfMdlMax() const;
  u32 getSeamTextureMax() const;
  u32 getSeamVertexMax() const;
  u32 getSeamEtcPosDataMax() const;
  u32 getSeamMpfPosDataMax() const;
  u32 getSeamColiMax() const;
  u32 getSeamShaderMax() const;
  void setSelectIdDisp(int id, bool isOff);
  void setMdlReadOff(bool isOff);
  bool isReadSafe() const;
  bool isRenderSafe() const;
  void setClearResource(bool isClear);
  void callZPrePassSeamAll();
  void callThicknessFirstSeamAll();
  void callThicknessSecondSeamAll();
  void callThicknessPassSeamAll(bool isFirst);
  void callRenderSeamAll();
  void callGBuffRenderSeamAll();
  void callLightPrePassRenderSeamAll();
  void callAlphaRenderSeamAll();
  void callSpAlphaRenderSeamAll();
  void callRefractionRenderSeamAll();
  void callRenderSeamEnvMap();
  void callGBuffRenderSeamEnvMap();
  void callLightPrePassRenderSeamEnvMap();
  void callAlphaRenderSeamEnvMap();
  void callSpAlphaRenderSeamEnvMap();
  void callRefractionRenderSeamEnvMap();
};

} // namespace ml
