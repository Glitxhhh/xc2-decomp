#include "dr/dr_mdo_ctl_seam_low_map.h"

#include "dr/dr_res_mdo_seam_mem_man.h"
#include "dr/dr_res_mdo_seam_wrk_low.h"

namespace ml {
class DrResMdoSeamMemObj;

void DrMdoCtlSeamLowMap::releaseLowMap() {
  DrResMdoSeamWrkLow *low = unknown2c8.unknown10.unknown00;
  while (low != nullptr) {
    DrResMdoSeamWrkLow *next = low->unknown08;
    releaseFreeSeamLow(low);
    low = next;
  }
  unknownc44 = 0;
}

DrResMdoSeamWrkLow *DrMdoCtlSeamLowMap::createFreeSeamLow() { return unknown2c8.unknown001(); }

void DrMdoCtlSeamLowMap::releaseFreeSeamLow(DrResMdoSeamWrkLow *low) {
  DrResMdoSeamMemObj *mem = low->unknown30;
  if (low->unknown28 != nullptr) {
    unknownb70[low->unknowna0 >> 5] &= ~(1 << (low->unknowna0 & 0x1f));
    unknownc44 -= low->unknownb0;
    releaseBaseMapSeamMat(low->unknown28);
    low->release();
    unknownc02--;
  }
  unknown2c8.unknown002(low);
  if (mem != nullptr) {
    low->unknown30 = nullptr;
    unknown6e0.releaseFreeObj(mem);
  }
}

void DrMdoCtlSeamLowMap::callRenderSeamLowMap() { renderSeamLowMap(0); }

void DrMdoCtlSeamLowMap::callGBuffRenderSeamLowMap() { renderSeamLowMap(1); }

void DrMdoCtlSeamLowMap::callLightPrePassRenderSeamLowMap() { renderSeamLowMap(3); }

void DrMdoCtlSeamLowMap::callRefractionRenderSeamLowMap() { renderSeamLowMap(2); }

void DrMdoCtlSeamLowMap::callAlphaRenderSeamLowMap() { renderSeamLowMap(4); }

void DrMdoCtlSeamLowMap::callSpAlphaRenderSeamLowMap() { renderSeamLowMap(5); }

void DrMdoCtlSeamLowMap::createLowDisplayList() {}

void DrMdoCtlSeamLowMap::updateLowMap() {
  readLowMapCheck();
  if (((unknownc7c >> 12) & 1) == 0) {
    updateLowMapRenderList();
  }
}

} // namespace ml
