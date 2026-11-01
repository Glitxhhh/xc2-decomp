#include "dr/dr_mdo_ctl_seam_env_map.h"

#include "dr/dr_res_mdo_seam_mem_man.h"
#include "dr/dr_res_mdo_seam_wrk_env.h"

namespace ml {
class DrResMdoSeamMemObj;

DrMdoCtlSeamEnvMap::DrMdoCtlSeamEnvMap(int viewNum) : DrMdoCtlSeam(viewNum) {}

void DrMdoCtlSeamEnvMap::releaseEnvMap() {
  DrResMdoSeamWrkEnv *env = unknown370.unknown10.unknown00;
  while (env != nullptr) {
    DrResMdoSeamWrkEnv *next = env->unknown08;
    releaseFreeSeamEnvMap(env);
    env = next;
  }
  unknownc50 = 0;
}

DrResMdoSeamWrkEnv *DrMdoCtlSeamEnvMap::createFreeSeamEnvMap() { return unknown370.unknown001(); }

void DrMdoCtlSeamEnvMap::releaseFreeSeamEnvMap(DrResMdoSeamWrkEnv *env) {
  DrResMdoSeamMemObj *mem = env->unknown60;
  if (env->unknown58 != nullptr) {
    unknownba0[env->unknown50 >> 5] &= ~(1 << (env->unknown50 & 0x1f));
    unknownc50 += env->unknown70;
    releaseBaseMapSeamMat(env->unknown58);
    env->release();
    unknownc08--;
  }
  unknown370.unknown002(env);
  if (mem != nullptr) {
    env->unknown60 = nullptr;
    unknown6e0.releaseFreeObj(mem);
  }
}

void DrMdoCtlSeamEnvMap::createEnvDisplayList(DrResMdoSeamWrkEnv *wrk) { wrk->setDispState(); }

void DrMdoCtlSeamEnvMap::updateEnvMap() {
  readEnvMapCheck();
  if (((unknownc7c >> 12) & 1) == 0) {
    updateEnvMapRenderList();
  }
}

} // namespace ml
