#include "dr/dr_mdo_ctl_seam_base_map.h"

#include "dr/dr_res_mdo_seam_mem_man.h"
#include "dr/dr_res_mdo_seam_wrk_base.h"

namespace ml {
class DrResMdoSeamMemObj;

DrMdoCtlSeamBaseMap::DrMdoCtlSeamBaseMap(int viewNum) : DrMdoCtlSeam(viewNum) {}

void DrMdoCtlSeamBaseMap::releaseBaseMap() {
  DrResMdoSeamWrkBase *base = unknown290.unknown10.unknown00;
  while (base != nullptr) {
    DrResMdoSeamWrkBase *next = base->unknown08;
    releaseFreeSeamBase(base);
    base = next;
  }
  unknownc40 = 0;
}

DrResMdoSeamWrkBase *DrMdoCtlSeamBaseMap::seachBaseIdx(int index) {
  DrResMdoSeamWrkBase *base = unknown290.unknown10.unknown00;
  while (base != nullptr && (base->unknown68 == nullptr || base->unknown84 != index)) {
    base = base->unknown08;
  }
  return base;
}

DrResMdoSeamWrkBase *DrMdoCtlSeamBaseMap::createFreeSeamBase() { return unknown290.unknown001(); }

void DrMdoCtlSeamBaseMap::releaseFreeSeamBase(DrResMdoSeamWrkBase *base) {
  DrResMdoSeamMemObj *mem = nullptr;
  if (base->unknown68 != nullptr) {
    mem = base->unknown158;
    unknownb50[base->unknown84 >> 5] &= ~(1 << (base->unknown84 & 0x1f));
    unknownb60[base->unknown84 >> 5] &= ~(1 << (base->unknown84 & 0x1f));
    unknownc40 -= base->unknownb4;
    releaseBaseMapSeamMat(base->unknown68);
    base->releaseCache(this);
    unknownc00--;
  }
  unknown290.unknown002(base);
  if (mem != nullptr) {
    base->unknown158 = nullptr;
    unknown6e0.releaseFreeObj(mem);
  }
}

void DrMdoCtlSeamBaseMap::callRenderSeamBaseMap() { renderSeamBaseMap(0); }

void DrMdoCtlSeamBaseMap::callGBuffRenderSeamBaseMap() { renderSeamBaseMap(1); }

void DrMdoCtlSeamBaseMap::callLightPrePassRenderSeamBaseMap() { renderSeamBaseMap(3); }

void DrMdoCtlSeamBaseMap::callRefractionRenderSeamBaseMap() { renderSeamBaseMap(2); }

void DrMdoCtlSeamBaseMap::callAlphaRenderSeamBaseMap() { renderSeamBaseMap(4); }

void DrMdoCtlSeamBaseMap::callSpAlphaRenderSeamBaseMap() { renderSeamBaseMap(5); }

void DrMdoCtlSeamBaseMap::createBaseMapDisplayList() {}

void DrMdoCtlSeamBaseMap::updateBaseMap() {
  readBaseMapCheck();
  if (((unknownc7c >> 12) & 1) == 0) {
    updateBaseMapRenderList();
  }
}

void DrMdoCtlSeamBaseMap::callShadowCacheBaseUpdate(u64 flags) {
  unknownc90 &= ~flags;
  for (DrResMdoSeamWrkBase *base = unknown290.unknown10.unknown00; base != nullptr; base = base->unknown08) {
    if (base->unknown68 != nullptr) {
      base->callShadowCacheBaseUpdate(flags);
    }
  }
}

} // namespace ml
