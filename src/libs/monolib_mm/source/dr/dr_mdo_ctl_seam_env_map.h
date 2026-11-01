#pragma once

#include "dr/dr_mdo_ctl_seam_mpf_map.h"

namespace ml {

class DrResMdoSeamWrkEnv;

class DrMdoCtlSeamEnvMap : public DrMdoCtlSeamMpfMap {
public:
  DrMdoCtlSeamEnvMap(int viewNum);
  void releaseEnvMap();
  void releaseFreeSeamEnvMap(DrResMdoSeamWrkEnv *env);
  DrResMdoSeamWrkEnv *createFreeSeamEnvMap();
  void updateEnvMap();
  void readEnvMapCheck();
  void updateEnvMapRenderList();
  void createEnvDisplayList(DrResMdoSeamWrkEnv *wrk);
  void callRenderSeamEnvMap();
  void callGBuffRenderSeamEnvMap();
  void callLightPrePassRenderSeamEnvMap();
  void callAlphaRenderSeamEnvMap();
  void callSpAlphaRenderSeamEnvMap();
  void callRefractionRenderSeamEnvMap();
};

} // namespace ml
