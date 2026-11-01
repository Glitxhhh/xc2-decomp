#pragma once

#include "dr/dr_mdo_ctl_seam.h"
#include "types.h"

namespace ml {
class DrPixlShadowCacheObj;
class DrPixlShadowObj;
class DrResMdoSeamWrkBase;

class DrMdoCtlSeamBaseMap : public DrMdoCtlSeam {
public:
  DrMdoCtlSeamBaseMap(int viewNum);
  void updateBaseMap();
  void readBaseMapCheck();
  void updateBaseMapRenderList();
  void callRenderSeamBaseMap();
  void callGBuffRenderSeamBaseMap();
  void callLightPrePassRenderSeamBaseMap();
  void callRefractionRenderSeamBaseMap();
  void callAlphaRenderSeamBaseMap();
  void callSpAlphaRenderSeamBaseMap();
  void renderSeamBaseMap(int renderType);
  void createBaseMapDisplayList();
  void releaseBaseMap();
  DrResMdoSeamWrkBase *seachBaseIdx(int index);
  void releaseFreeSeamBase(DrResMdoSeamWrkBase *base);
  DrResMdoSeamWrkBase *createFreeSeamBase();
  void callShadowCacheBaseUpdate(u64 flags);
  void createBaseZPrePassDisplayList();
  void createBaseThicknesPassDisplayList(bool isFirst);
  void callShadowMapRenderSeamBaseMap(DrPixlShadowObj *shadow);
  void callBaseShadowCacheRender(DrPixlShadowCacheObj &cache);
};

} // namespace ml
