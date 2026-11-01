#include "dr/dr_mdo_ctl_seam_mpf_map.h"

#include "dr/dr_res_mdo_seam_mem_man.h"
#include "dr/dr_res_mdo_seam_wrk_mpf.h"

namespace ml {
class DrResMdoSeamMemObj;

void DrMdoCtlSeamMpfMap::releaseMpfMap() {
  DrResMdoSeamWrkMpf *mpf = unknown338.unknown10.unknown00;
  while (mpf != nullptr) {
    DrResMdoSeamWrkMpf *next = mpf->unknown08;
    releaseFreeSeamMpf(mpf);
    mpf = next;
  }
  unknownc40 = 0;
}

void DrMdoCtlSeamMpfMap::createAllpfMapDisplayList() {}

void DrMdoCtlSeamMpfMap::renderMpfMapDisplayList() { createMpfMapDisplayList(); }

void DrMdoCtlSeamMpfMap::releaseFreeSeamMpf(DrResMdoSeamWrkMpf *mpf) {
  DrResMdoSeamMemObj *mem = mpf->unknown18;
  if (mpf->unknown70 != nullptr) {
    unknownb90[mpf->unknown4c >> 5] &= ~(1 << (mpf->unknown4c & 0x1f));
    unknownc4c -= mpf->unknowne8;
    releaseMpfMapSeamMat(mpf->unknown70);
    mpf->releaseCache(this);
    unknownc06--;
  }
  unknown338.unknown002(mpf);
  if (mem != nullptr) {
    mpf->unknown18 = nullptr;
    unknown6e0.releaseFreeObj(mem);
  }
}

void DrMdoCtlSeamMpfMap::updateMpfMap() {
  readMpfMapCheck();
  if (((unknownc7c >> 12) & 1) == 0) {
    updateMpfMapRenderList();
  }
}

DrResMdoSeamWrkMpf *DrMdoCtlSeamMpfMap::createFreeSeamMpf() { return unknown338.unknown001(); }

} // namespace ml
