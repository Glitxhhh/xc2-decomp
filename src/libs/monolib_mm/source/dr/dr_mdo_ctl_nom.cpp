#include "dr/dr_mdo_ctl_nom.h"

#include "cloud/cloud_mdl_data_obj.h"
#include "dr/dr_ap_cache.h"
#include "dr/dr_man.h"
#include "dr/dr_mdl_base.h"
#include "dr/dr_mdo_ctl.h"
#include "dr/dr_mdo_mat.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_shadow_cache_man.h"
#include "dr/dr_res_mdo_light.h"
#include "dr/dr_res_mdo_lod_obj.h"
#include "dr/dr_res_mdo_shd_obj.h"
#include "dr/dr_res_mdo_vtx_mesh_obj.h"
#include "grlib/cglib_ctl_shader.h"
#include "mm_math/mm_col3.h"

namespace ml {

// Inferred role: weight vertex render type of each render type; original name unknown.
static const u8 unknown135[] = {0, 3, 2, 4, 1, 1};

DrMdoCtlNom::~DrMdoCtlNom() {
  if ((unknownfc & unknown027_8) && unknown1a == 0) {
    m_drMan->unknown78->unknown800->delShadowCacheUpdate();
  }
  releaseNom();
}

void DrMdoCtlNom::setDeleteCall(int deleteCall) {
  DrMdlBase::setDeleteCall(deleteCall);
  if (unknown210 != nullptr) {
    unknown210->setCallDisp(false);
  }
  if (unknown1e0 != nullptr) {
    unknown1e0->setDisp(false);
  }
}

void DrMdoCtlNom::setDisp(bool isDisp) {
  DrMdlBase::setDisp(isDisp);
  if (unknown1e0 != nullptr) {
    unknown1e0->setDisp(isDisp);
  }
}

void DrMdoCtlNom::callShadowCacheUpdate(u64 flags) { unknown230 &= ~flags; }

void DrMdoCtlNom::updateRimBloomParams() {
  if (getRimBloomWrk(2) != nullptr) {
    unknown091 *dst = getRimBloomWrk(2);
    unknown091 *src = getRimBloomWrk(DrMan::s_nDblStockIdx);
    if (src->unknown1c & 1) {
      dst->unknown00 = src->unknown00;
    }
    if (src->unknown1c & 2) {
      dst->unknown0c = src->unknown0c;
    }
    if (src->unknown1c & 4) {
      dst->unknown10 = src->unknown10;
    }
    if (src->unknown1c & 8) {
      dst->unknown14 = src->unknown14;
    }
    src->unknown1c = 0;
  }
}

void DrMdoCtlNom::updateShdMdl() {
  if (unknown1d0 != nullptr && unknown1d0->update(unknown30->unknown88)) {
    unknown20 &= ~0x60;
  }
}

void DrMdoCtlNom::callZSortLightPrePassRender() {
  if ((unknownf8 & unknown028_3) == 0) {
    return;
  }
  nomCallRender(3);
}

void DrMdoCtlNom::callZSortNomAlphaRender() {
  if ((unknownf8 & unknown028_4) != 0) {
    nomCallRender(4);
  }
  if (unknown1d8 != nullptr) {
    unknown1d8->alpRender();
  }
}

void DrMdoCtlNom::callZSortNomSpAlphaRender() {
  if ((unknownf8 & unknown028_5) == 0) {
    return;
  }
  nomCallRender(5);
}

void DrMdoCtlNom::callZSortGBuffRender() {
  if ((unknownf8 & unknown028_1) == 0) {
    return;
  }
  nomCallRender(1);
}

void DrMdoCtlNom::callZSortNomRefractionRender() {
  if ((unknownf8 & unknown028_2) == 0) {
    return;
  }
  nomCallRender(2);
}

void DrMdoCtlNom::callLastAlphaNomRender() {
  if ((unknownf8 & unknown028_25) == 0) {
    return;
  }
  lastAlphaCallRender();
}

void DrMdoCtlNom::callFastAlphaNomRender() {
  if ((unknownf8 & unknown028_26) == 0) {
    return;
  }
  fastAlphaCallRender();
}

void DrMdoCtlNom::callCldBackAlphaNomRender() {
  if ((unknownf8 & unknown028_27) == 0) {
    return;
  }
  cldBackAlphaCallRender();
}

void DrMdoCtlNom::nomCallRender(int pass) {
  if (m_nodeMax != 0) {
    grlib::CGLibCtlShader::setMemoryBarrierBit(1);
    if (pass == 0) {
      u32 lodFlags = unknown1f0->unknown1c;
      if (unknown1d8 != nullptr) {
        lodFlags |= unknown1d8->isRender();
      }
      createWeightVtx(0, unknown100, lodFlags, false);
      createWeightVtx(0, unknown100, lodFlags, true);
    } else {
      createWeightVtx(unknown135[pass], unknown100, unknown1f0->unknown1c, false);
    }
    grlib::CGLibCtlShader::setMemoryBarrierBit(0x21);
  }
  if (pass == 0 && (unknownf8 & unknown028_21) == 0) {
    DrAPCache *cache = m_drMan->unknown5c0;
    beginSetup();
    cache->beginMdlZRender();
    zPrePassRender();
    cache->endMdlZRender();
  }
  unknownf4 = pass;
  unknownf2 = unknown098[pass];
  beginSetup();
  const MdsMdlTopHeader *top = unknown30->unknown168;
  for (int i = 0; i < unknown30->unknown170; i++, top++) {
    DrResChkList **lists = unknown190[i];
    DrResChkList *list = lists[unknownf4];
    if (list != nullptr) {
      nomRender(top, list);
    }
  }
}

void DrMdoCtlNom::lastAlphaCallRender() {
  unknown002();
  const MdsMdlTopHeader *top = unknown30->unknown168;
  for (int i = 0; i < unknown30->unknown170; i++, top++) {
    DrResChkList *list = unknown1b8->unknown20[i];
    if (list != nullptr) {
      nomRender(top, list);
    }
  }
}

void DrMdoCtlNom::fastAlphaCallRender() {
  unknown002();
  const MdsMdlTopHeader *top = unknown30->unknown168;
  for (int i = 0; i < unknown30->unknown170; i++, top++) {
    DrResChkList *list = unknown1b8->unknown18[i];
    if (list != nullptr) {
      nomRender(top, list);
    }
  }
}

void DrMdoCtlNom::cldBackAlphaCallRender() {
  unknown002();
  const MdsMdlTopHeader *top = unknown30->unknown168;
  for (int i = 0; i < unknown30->unknown170; i++, top++) {
    DrResChkList *list = unknown1b8->unknown28[i];
    if (list != nullptr) {
      nomRender(top, list);
    }
  }
}

} // namespace ml
