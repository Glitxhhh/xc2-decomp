#include "dr/dr_mdo_ctl_seam_inst_map.h"

#include "dr/dr_man.h"
#include "dr/dr_mdo_ctl_seam.h"
#include "dr/dr_mdo_mat.h"
#include "dr/dr_pixl_shadow_cache_obj.h"
#include "dr/dr_res_mdo_seam_mem_man.h"
#include "dr/dr_res_mdo_seam_res.h"
#include "dr/dr_res_mdo_seam_wrk_inst.h"

namespace ml {

DrMdoCtlSeamInstMap::DrMdoCtlSeamInstMap(int viewNum) : DrMdoCtlSeamLowMap(viewNum) {}

namespace {

// Inferred role: header of the fixed animation data of the instance map; original type name unknown.
struct unknown411 {
  u8 _00[0x14];
  u32 unknown14; // Inferred role: offset of the fixed animation infos; original member name unknown.
  u8 _18[0x1c - 0x18];
  u32 unknown1c; // Inferred role: offset of the fixed animation keys; original member name unknown.
  u8 _20[0x24 - 0x20];
  u32 unknown24; // Inferred role: offset of the fixed animation arrays; original member name unknown.
};

} // namespace

void DrMdoCtlSeamInstMap::changeMemInstMapParts(DrResMdoSeamWrkInst *inst) {
  MdoWrkMatRes *matRes = inst->unknown50;
  const u8 *data = inst->unknown108->m_buffer;
  const MdsSeamInstMapHead *head = reinterpret_cast<const MdsSeamInstMapHead *>(data);
  unknown30 = matRes;
  resetInstMapMaterial(matRes, data + head->unknown10, data + head->unknown0c, data + head->unknown44, nullptr, head->unknown24);
  if (head->unknown14 != 0) {
    const unknown411 *block = reinterpret_cast<const unknown411 *>(data + head->unknown14);
    matRes->unknown50 = reinterpret_cast<const u8 *>(block);
    matRes->unknown58 = reinterpret_cast<const MdsFixAnmInf *>(reinterpret_cast<const u8 *>(block) + block->unknown14);
    matRes->unknown60 = reinterpret_cast<const unknown013 *>(reinterpret_cast<const u8 *>(block) + block->unknown1c);
    matRes->unknown68 = reinterpret_cast<const u8 *>(block) + block->unknown24;
  }
}

void DrMdoCtlSeamInstMap::releaseInstMap() {
  DrResMdoSeamWrkInst *inst = unknown300.unknown10.unknown00;
  while (inst != nullptr) {
    DrResMdoSeamWrkInst *next = inst->unknown08;
    releaseFreeSeamInst(inst);
    inst = next;
  }
}

DrResMdoSeamWrkInst *DrMdoCtlSeamInstMap::createFreeSeamInst() { return unknown300.unknown001(); }

void DrMdoCtlSeamInstMap::releaseFreeSeamInst(DrResMdoSeamWrkInst *inst) {
  DrResMdoSeamMemObj *mem = nullptr;
  if (inst->unknown50 != nullptr) {
    mem = inst->unknown108;
    unknownb80[inst->unknown68 >> 5] &= ~(1 << (inst->unknown68 & 0x1f));
    unknownc48 -= inst->unknown84;
    releaseInstMapSeamMat(inst->unknown50);
    inst->releaseCache(this);
    unknownc04--;
  }
  unknown300.unknown002(inst);
  if (mem != nullptr) {
    inst->unknown108 = nullptr;
    unknown6e0.releaseFreeObj(mem);
  }
}

void DrMdoCtlSeamInstMap::callRenderSeamInstMap() { renderSeamInstMap(0); }

void DrMdoCtlSeamInstMap::callGBuffRenderSeamInstMap() { renderSeamInstMap(1); }

void DrMdoCtlSeamInstMap::callLightPrePassRenderSeamInstMap() { renderSeamInstMap(3); }

void DrMdoCtlSeamInstMap::callRefractionRenderSeamInstMap() { renderSeamInstMap(2); }

void DrMdoCtlSeamInstMap::callAlphaRenderSeamInstMap() { renderSeamInstMap(4); }

void DrMdoCtlSeamInstMap::callSpAlphaRenderSeamInstMap() { renderSeamInstMap(5); }

void DrMdoCtlSeamInstMap::createInstRenderDisplayList(const MdsMdlInfoHeader *, int, DrResMdoSeamWrkInst *, _MdoInstanceWork *, grlib::CGLibVtxInstans *, int) {}

void DrMdoCtlSeamInstMap::beginResAll(MdoWrkMatRes *matRes) {
  MdoWrkMatRes *prev = unknown30;
  unknown30 = matRes;
  unknownb38 = prev;
}

void DrMdoCtlSeamInstMap::endResAll() { unknown30 = unknownb38; }

void DrMdoCtlSeamInstMap::updateInstMap(MdoArgSeamUpdate &arg) {
  readInstMapCheck();
  if (((unknownc7c >> 12) & 1) == 0) {
    updateInstMapRenderList(arg);
    createInstMapDisplayList();
  }
}

void DrMdoCtlSeamInstMap::callShadowCacheInstUpdate(u64 flags) {
  unknownc98 &= ~flags;
  for (DrResMdoSeamWrkInst *inst = unknown300.unknown10.unknown00; inst != nullptr; inst = inst->unknown08) {
    if (inst->unknown50 != nullptr) {
      inst->callShadowCacheInstUpdate(flags);
    }
  }
}

void DrMdoCtlSeamInstMap::occInstRender() {
  if (!m_drMan->unknown1d6a) {
    for (DrResMdoSeamWrkInst *inst = unknown300.unknown10.unknown00; inst != nullptr; inst = inst->unknown08) {
      unknown30 = inst->unknown50;
      if (unknown30 != nullptr) {
        inst->occRender();
      }
    }
  }
}

void DrMdoCtlSeamInstMap::callShadowMapRenderSeamInstMap(DrPixlShadowObj *shadow) {
  if (!m_drMan->unknown1d6a) {
    changeSeamMatInfo();
    for (DrResMdoSeamWrkInst *inst = unknown300.unknown10.unknown00; inst != nullptr; inst = inst->unknown08) {
      unknown30 = inst->unknown50;
      if (unknown30 != nullptr && (inst->unknown8a & 0x10) != 0) {
        inst->seachDefShadowInstMapRender(shadow, this);
      }
    }
  }
}

void DrMdoCtlSeamInstMap::callInstShadowCacheRender(DrPixlShadowCacheObj &cache) {
  if ((unknownc98 & cache.unknown8e8) != 0 || m_drMan->unknown1d6a) {
    return;
  }
  changeSeamMatInfo();
  bool isRetry = false;
  for (DrResMdoSeamWrkInst *inst = unknown300.unknown10.unknown00; inst != nullptr; inst = inst->unknown08) {
    unknown30 = inst->unknown50;
    if (unknown30 != nullptr) {
      if (inst->unknown8a & 0x10) {
        isRetry |= inst->seachShadowInstMapRender(cache, this);
      } else {
        isRetry = true;
      }
    }
  }
  if (isRetry) {
    unknownc98 &= ~cache.unknown8e8;
  } else {
    unknownc98 |= cache.unknown8e8;
  }
}

} // namespace ml
