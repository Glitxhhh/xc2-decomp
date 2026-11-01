#include "dr/dr_mdo_ctl_seam_all.h"

#include "cloud/cloud_man.h"
#include "cloud/cloud_mdl_data_obj.h"
#include "cloud/cloud_obj_man.h"
#include "dr/dr_calc_clip_man.h"
#include "dr/dr_calc_man.h"
#include "dr/dr_environment_man.h"
#include "dr/dr_fog_man.h"
#include "dr/dr_global_ibl_man.h"
#include "dr/dr_light_man.h"
#include "dr/dr_man.h"
#include "dr/dr_mdl_man.h"
#include "dr/dr_mdo_ctl_seam.h"
#include "dr/dr_mdo_ctl_seam_env_map.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_shadow_cache_man.h"
#include "dr/dr_res_mdo_seam_read.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace ml {

DrMdoCtlSeamAll::DrMdoCtlSeamAll(const void *data, const char *path, DrMan *man, int viewNum) : DrMdoCtlSeamRead(viewNum) {
  m_drMan = man;
  setupSeamMapHead(data, path);
}

DrMdoCtlSeamAll::~DrMdoCtlSeamAll() { releaseSeamAll(); }

void DrMdoCtlSeamAll::releaseSeamAll() {
  if (unknown1a == 0) {
    m_drMan->unknown78->unknown800->delShadowCacheUpdate();
  }
  releaseBaseMap();
  releaseLowMap();
  releaseInstMap();
  releaseMpfMap();
  releaseEnvMap();
  releaseLight();
  releaseSeam();
}

void DrMdoCtlSeamAll::resourceInit() {
  unknownc7c |= 0x2000;
  if (unknown1a == 0) {
    m_drMan->unknown78->unknown800->addShadowCacheUpdate(false);
  }
  m_drMan->unknown88->addMpfObj();
  const u8 *data = reinterpret_cast<const u8 *>(unknown1a8);
  if (unknown1a8->unknown84 != 0) {
    DrLightMan *lightMan = DrMan::getIns()->unknownc0[unknown1a];
    lightMan->releaseAllAmbLight();
    lightMan->releaseAllDirLight();
    DrMan::getIns()->unknowne0[unknown1a]->releaseAll();
    const void *envData = data + unknown1a8->unknown84;
    unknown3f8 = m_drMan->unknown100[unknown1a]->createObj(envData);
  }
  if (unknown1a8->unknowna8 != 0) {
    unknown408 = m_drMan->unknowna0[unknown1a]->unknown18->createClipObj(data + unknown1a8->unknowna8);
  }
  if (unknown1a8->unknowne8 != 0) {
    const void *cloudData = reinterpret_cast<const u8 *>(unknown1a8) + unknown1a8->unknowne8;
    unknownb30 = cloud::CloudMan::get()->unknown50->createMdlData(cloudData);
  }
  DrGlobalIBLMan *globalIBLMan = m_drMan->unknown160[unknown1a];
  for (int i = 0; i < (unknown6d8 != nullptr ? unknown6d8->unknown00 : 0); i++) {
    u32 offset = unknown6d8->unknown04 + i * sizeof(unknown096);
    const unknown096 *ibl = reinterpret_cast<const unknown096 *>(reinterpret_cast<const u8 *>(unknown6d8) + offset);
    if (ibl->unknown0c != 0) {
      const void *iblData = nullptr;
      if (ibl->unknown08 != 0) {
        iblData = reinterpret_cast<const u8 *>(unknown6d8) + ibl->unknown08;
      }
      unknown420.push_back(globalIBLMan->createObj(iblData));
    }
  }
}

void DrMdoCtlSeamAll::callShadowCacheUpdate(u64 flags) {
  callShadowCacheBaseUpdate(flags);
  callShadowCacheInstUpdate(flags);
}

bool DrMdoCtlSeamAll::callDeleteUpdate() {
  if (((unknownc7c >> 28) & 1) == 0) {
    return true;
  }
  if ((unknownc7c >> 29) & 1) {
    resourceRelease();
    if ((unknownc7c >> 13) & 1) {
      releaseBaseMap();
      releaseLowMap();
      releaseInstMap();
      releaseMpfMap();
      releaseEnvMap();
      releaseLight();
      unknownc7c &= ~0x2000;
    }
  }
  if (unknownb30 != nullptr) {
    unknownb30->setCallDisp(false);
  }
  return false;
}

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

void DrMdoCtlSeamAll::callZPrePassSeamAll() {
  if ((unknownf8 & unknown028_20) == 0 || m_drMan->unknown1d61) {
    return;
  }
  seamZPrePassBegin();
  createBaseZPrePassDisplayList();
  createInstZPrePassDisplayList();
  createMpfZPrePassDisplayList();
  createLowZPrePassDisplayList();
  seamZPrePassEnd();
}

void DrMdoCtlSeamAll::callThicknessFirstSeamAll() { callThicknessPassSeamAll(true); }

void DrMdoCtlSeamAll::callThicknessSecondSeamAll() { callThicknessPassSeamAll(false); }

void DrMdoCtlSeamAll::callRenderSeamAll() {
  if ((unknownf8 & unknown028_0) == 0 || m_drMan->unknown1d61) {
    return;
  }
  unknownf4 = 0;
  unknownf2 = 0;
  unknown001();
  callRenderSeamInstMap();
  callRenderSeamBaseMap();
  callRenderSeamMpfMap();
  callRenderSeamLowMap();
}

void DrMdoCtlSeamAll::callGBuffRenderSeamAll() {
  if ((unknownf8 & unknown028_1) == 0 || m_drMan->unknown1d61) {
    return;
  }
  unknownf4 = 1;
  unknownf2 = 7;
  unknown001();
  callGBuffRenderSeamInstMap();
  callGBuffRenderSeamBaseMap();
  callGBuffRenderSeamLowMap();
}

void DrMdoCtlSeamAll::callLightPrePassRenderSeamAll() {
  if ((unknownf8 & unknown028_3) == 0 || m_drMan->unknown1d61) {
    return;
  }
  unknownf4 = 3;
  unknownf2 = 4;
  unknown001();
  callLightPrePassRenderSeamBaseMap();
  callLightPrePassRenderSeamInstMap();
  callLightPrePassRenderSeamLowMap();
}

void DrMdoCtlSeamAll::callAlphaRenderSeamAll() {
  if ((unknownf8 & unknown028_4) == 0 || m_drMan->unknown1d61) {
    return;
  }
  unknownf4 = 4;
  unknownf2 = 1;
  unknown001();
  callAlphaRenderSeamLowMap();
  callAlphaRenderSeamBaseMap();
  callAlphaRenderSeamInstMap();
}

void DrMdoCtlSeamAll::callSpAlphaRenderSeamAll() {
  if ((unknownf8 & unknown028_5) == 0 || m_drMan->unknown1d61) {
    return;
  }
  unknownf4 = 5;
  unknownf2 = 1;
  unknown001();
  callSpAlphaRenderSeamLowMap();
  callSpAlphaRenderSeamBaseMap();
  callSpAlphaRenderSeamInstMap();
}

void DrMdoCtlSeamAll::callRefractionRenderSeamAll() {
  if ((unknownf8 & unknown028_2) == 0 || m_drMan->unknown1d61) {
    return;
  }
  unknownf4 = 2;
  unknownf2 = 8;
  unknown001();
  callRefractionRenderSeamInstMap();
  callRefractionRenderSeamBaseMap();
  callRefractionRenderSeamLowMap();
}

void DrMdoCtlSeamAll::callThicknessPassSeamAll(bool isFirst) {
  if ((unknownf8 & unknown028_6) == 0 || m_drMan->unknown1d61) {
    return;
  }
  seamThicknessPassBegin(isFirst);
  createBaseThicknesPassDisplayList(isFirst);
  createInstThicknessPassDisplayList(isFirst);
  seamThicknessPassEnd(isFirst);
}

void DrMdoCtlSeamAll::callRenderSeamEnvMap() {
  if ((unknownf8 & unknown028_0) == 0 || m_drMan->unknown1d61) {
    return;
  }
  unknownf4 = 0;
  unknownf2 = 0;
  unknown001();
  DrMdoCtlSeamEnvMap::callRenderSeamEnvMap();
}

void DrMdoCtlSeamAll::callGBuffRenderSeamEnvMap() {
  if ((unknownf8 & unknown028_1) == 0 || m_drMan->unknown1d61) {
    return;
  }
  unknownf4 = 1;
  unknownf2 = 7;
  unknown001();
  DrMdoCtlSeamEnvMap::callGBuffRenderSeamEnvMap();
}

void DrMdoCtlSeamAll::callLightPrePassRenderSeamEnvMap() {
  if ((unknownf8 & unknown028_3) == 0 || m_drMan->unknown1d61) {
    return;
  }
  unknownf4 = 3;
  unknownf2 = 4;
  unknown001();
  DrMdoCtlSeamEnvMap::callLightPrePassRenderSeamEnvMap();
}

void DrMdoCtlSeamAll::callAlphaRenderSeamEnvMap() {
  if ((unknownf8 & unknown028_4) == 0 || m_drMan->unknown1d61) {
    return;
  }
  unknownf4 = 4;
  unknownf2 = 1;
  unknown001();
  DrMdoCtlSeamEnvMap::callAlphaRenderSeamEnvMap();
}

void DrMdoCtlSeamAll::callSpAlphaRenderSeamEnvMap() {
  if ((unknownf8 & unknown028_5) == 0 || m_drMan->unknown1d61) {
    return;
  }
  unknownf4 = 5;
  unknownf2 = 1;
  unknown001();
  DrMdoCtlSeamEnvMap::callSpAlphaRenderSeamEnvMap();
}

void DrMdoCtlSeamAll::callRefractionRenderSeamEnvMap() {
  if ((unknownf8 & unknown028_2) == 0 || m_drMan->unknown1d61) {
    return;
  }
  unknownf4 = 2;
  unknownf2 = 8;
  unknown001();
  DrMdoCtlSeamEnvMap::callRefractionRenderSeamEnvMap();
}

void DrMdoCtlSeamAll::shadowCacheAddRender(int index) {
  if ((unknown20 & unknown038_0) == 0 || ((unknownc7c >> 28) & 1) != 0) {
    return;
  }
  m_drMan->unknown78->setupShadowUnifrom(index);
  callInstShadowCacheAddRender(index);
}

void DrMdoCtlSeamAll::occRender() {
  if ((unknown20 & unknown038_0) == 0 || ((unknownc7c >> 28) & 1) != 0) {
    return;
  }
  occInstRender();
}

} // namespace ml
