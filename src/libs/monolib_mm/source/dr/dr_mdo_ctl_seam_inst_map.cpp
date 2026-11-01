#include "dr/dr_mdo_ctl_seam_inst_map.h"

#include "dr/dr_man.h"
#include "dr/dr_res_mdo_seam_mem_man.h"
#include "dr/dr_res_mdo_seam_wrk_inst.h"

namespace ml {
class DrResMdoSeamMemObj;

DrMdoCtlSeamInstMap::DrMdoCtlSeamInstMap(int viewNum) : DrMdoCtlSeam(viewNum) {}

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

struct MdoWrkMatRes;

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

} // namespace ml
