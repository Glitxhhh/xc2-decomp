#include "dr/dr_mdo_ctl_seam.h"

#include "dr/dr_res_mdo_seam_coli.h"
#include "dr/dr_res_mdo_seam_res.h"

#include "dr/dr_ap_cache.h"
#include "dr/dr_man.h"

namespace ml {

void *DrMdoCtlSeam::getColiListTbl() { return unknown640[DrMan::s_nDblIdx]; }

u32 DrMdoCtlSeam::getColiListMax() { return unknown650[DrMan::s_nDblIdx]; }

u32 DrMdoCtlSeam::isRead(int index) const {
  if (((unknownc7c >> 28) & 1) == 0) {
    return unknownd1a & (1 << index);
  }
  return 0;
}

void DrMdoCtlSeam::setErrCode(int code, int param) {
  unknowncae[unknowncac] = code;
  unknowncb8[unknowncac] = param;
  s16 next = unknowncac + 1;
  if (next > 3) {
    next = 0;
  }
  unknowncac = next;
}

void DrMdoCtlSeam::releaseFreeSeamTexture(DrResMdoSeamTexture *texture, bool isAll) {
  if (isAll) {
    texture->release();
    unknown1b0.unknown002(texture);
  } else {
    DrResMdoSeamMemObj *mem = texture->unknown88;
    DrResMdoSeamMemObj *heightMem = texture->unknown90;
    unknownbe0[texture->unknown9e] = 0;
    texture->release();
    texture->unknown88 = nullptr;
    unknown1b0.unknown002(texture);
    if (mem != nullptr) {
      unknown6e0.releaseFreeObj(mem);
    }
    if (heightMem != nullptr) {
      unknown6e0.releaseFreeObj(heightMem);
    }
  }
}

int DrMdoCtlSeam::calcSemaAlignment(u32 size, u32 alignment) {
  u32 remainder = size % alignment;
  int padding = 0;
  if (remainder != 0) {
    padding = alignment - remainder;
  }
  return padding + size;
}

void DrMdoCtlSeam::releaseFreeSeamTexList(DrResMdoSeamTexList *texList, bool isAll) {
  if (isAll) {
    texList->release();
    unknown1e8.unknown002(texList);
  } else {
    DrResMdoSeamMemObj *mem = texList->unknown18;
    unknownbf0[texList->unknown3c] = 0;
    texList->release();
    texList->unknown18 = nullptr;
    unknown1e8.unknown002(texList);
    if (mem != nullptr) {
      unknown6e0.releaseFreeObj(mem);
    }
  }
}

void DrMdoCtlSeam::releaseFreeSeamVertex(DrResMdoSeamVertex *vertex, bool isAll) {
  if (isAll) {
    vertex->release();
    unknown220.unknown002(vertex);
  } else {
    DrResMdoSeamMemObj *mem = vertex->unknown18;
    unknownbd0[vertex->unknown2c] = 0;
    vertex->release();
    vertex->unknown18 = nullptr;
    unknown220.unknown002(vertex);
    if (mem != nullptr) {
      unknown6e0.releaseFreeObj(mem);
    }
  }
}

DrResMdoSeamTexture *DrMdoCtlSeam::createFreeSeamTexture() { return unknown1b0.unknown001(); }

DrResMdoSeamTexList *DrMdoCtlSeam::createFreeSeamTexList() { return unknown1e8.unknown001(); }

DrResMdoSeamVertex *DrMdoCtlSeam::createFreeSeamVertex() { return unknown220.unknown001(); }

DrResMdoSeamColi *DrMdoCtlSeam::createFreeSeamCollision() { return unknown258.unknown001(); }

void DrMdoCtlSeam::seamZPrePassBegin() {
  unknownf2 = 0;
  unknown001();
  m_drMan->unknown5c0->setupCulling(DR_AP_CULL_TYPE_OFF);
}

void DrMdoCtlSeam::seamZPrePassEnd() {}

void DrMdoCtlSeam::seamThicknessPassEnd(bool value) {}

} // namespace ml
