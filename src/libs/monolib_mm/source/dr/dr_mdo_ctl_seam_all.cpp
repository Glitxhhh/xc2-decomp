#include "dr/dr_man.h"
#include "dr/dr_mdo_ctl_seam.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_shadow_cache_man.h"
#include "dr/dr_res_mdo_seam_read.h"
#include "types.h"

namespace ml {

DrMdoCtlSeamAll::DrMdoCtlSeamAll(const void *data, const char *path, DrMan *man, int viewNum) : DrMdoCtlSeam(viewNum) {
  m_drMan = man;
  setupSeamMapHead(data, path);
}

DrMdoCtlSeamAll::~DrMdoCtlSeamAll() { releaseSeamAll(); }

u32 DrMdoCtlSeamAll::getSeamBaseMdlMax() const { return unknown1a8->m_seamBaseMdlMax; }

u32 DrMdoCtlSeamAll::getSeamInstMdlMax() const { return unknown1a8->m_seamInstMdlMax; }

u32 DrMdoCtlSeamAll::getSeamMpfMdlMax() const { return unknown1a8->m_seamMpfMdlMax; }

u32 DrMdoCtlSeamAll::getSeamTextureMax() const { return unknown1a8->m_seamTextureMax; }

u32 DrMdoCtlSeamAll::getSeamVertexMax() const { return unknown1a8->m_seamVertexMax; }

u32 DrMdoCtlSeamAll::getSeamEtcPosDataMax() const { return unknown1a8->m_seamEtcPosDataMax; }

u32 DrMdoCtlSeamAll::getSeamMpfPosDataMax() const { return unknown1a8->m_seamMpfPosDataMax; }

u32 DrMdoCtlSeamAll::getSeamColiMax() const { return unknown1a8->m_seamColiMax; }

u32 DrMdoCtlSeamAll::getSeamShaderMax() const { return unknown1a8->m_seamShaderMax; }

bool DrMdoCtlSeamAll::isReadSafe() const { return (unknownc7c >> 11) & 1; }

bool DrMdoCtlSeamAll::isRenderSafe() const { return (unknownc7c >> 15) & 1; }

void DrMdoCtlSeamAll::setSelectIdDisp(int id, bool isOff) {
  if (isOff) {
    m_drMan->offGblIdx(id);
    return;
  }
  m_drMan->setGblIdx(id);
}

void DrMdoCtlSeamAll::setMdlReadOff(bool isOff) {
  u32 flags = unknownc7c & ~0x200u;
  if (isOff) {
    flags = unknownc7c | 0x200;
  }
  unknownc7c = flags;
}

void DrMdoCtlSeamAll::debugRender() {}

void DrMdoCtlSeamAll::setClearResource(bool isClear) {}

void DrMdoCtlSeamAll::noOffScreenUpdate() {
  unknownc16++;
  if (!unknowncd0.isRead()) {
    unknowncd0.release();
    if (unknownc16 > 3) {
      unknown20 |= unknown038_3 | unknown038_3 << 1;
    }
  }
  if (((unknownc7c >> 12) & 1) == 0) {
    unknownc7c |= 0x1000;
    if (unknown1a == 0) {
      m_drMan->unknown78->unknown800->delShadowCacheUpdate();
    }
  }
}

void DrMdoCtlSeamAll::setDeleteCall(int deleteCall) {
  unknownc7c |= 0x40000000 << deleteCall;
  unknowncd0.readCancel();
  resourceRelease();
}

} // namespace ml
