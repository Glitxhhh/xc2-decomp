#include "dr/dr_mdo_ctl_seam_base_map.h"

#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_shadow_cache_obj.h"
#include "dr/dr_res_mdo_seam_mem_man.h"
#include "dr/dr_res_mdo_seam_wrk_base.h"
#include "grlib/cglib_etc_uniform_block.h"
#include "grlib/shd_util.h"
#include "mm_math/mm_mat44.h"

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

void DrMdoCtlSeamBaseMap::callShadowMapRenderSeamBaseMap(DrPixlShadowObj *shadow) {
  if (m_drMan->unknown1d69) {
    return;
  }
  DrCalcViewWork *view = m_drMan->unknown580->unknown10;
  grlib::CGLibEtcUniformBlock uniform;
  grlib::ShdMat44TransposeMat44(reinterpret_cast<f32 *>(uniform.getBuff()), view->unknown40);
  uniform.updateData(sizeof(mm::Mat44));
  unknown170 = &uniform;
  for (DrResMdoSeamWrkBase *base = unknown290.unknown10.unknown00; base != nullptr; base = base->unknown08) {
    unknown30 = base->unknown68;
    if (unknown30 != nullptr && (base->unknowna0 & 8) != 0) {
      changeSeamMatInfo();
      base->seachDefShadowBaseMapRender(shadow, this);
    }
  }
}

void DrMdoCtlSeamBaseMap::callBaseShadowCacheRender(DrPixlShadowCacheObj &cache) {
  if ((unknownc90 & cache.unknown8e8) != 0 || m_drMan->unknown1d69) {
    return;
  }
  bool isRetry = false;
  for (DrResMdoSeamWrkBase *base = unknown290.unknown10.unknown00; base != nullptr; base = base->unknown08) {
    unknown30 = base->unknown68;
    if (unknown30 != nullptr) {
      if (base->unknowna0 & 8) {
        changeSeamMatInfo();
        changeShader(true);
        isRetry |= base->seachShadowBaseMapRender(cache, this);
      } else {
        isRetry = true;
      }
    }
  }
  if (isRetry) {
    unknownc90 &= ~cache.unknown8e8;
  } else {
    unknownc90 |= cache.unknown8e8;
  }
}

} // namespace ml
