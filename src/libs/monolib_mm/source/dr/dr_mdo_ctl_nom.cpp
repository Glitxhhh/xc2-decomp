#include "dr/dr_mdo_ctl_nom.h"

#include "dr/dr_man.h"
#include "dr/dr_mdo_mat.h"
#include "dr/dr_res_mdo_shd_obj.h"
#include "dr/dr_res_mdo_vtx_mesh_obj.h"
#include "mm_math/mm_col3.h"

namespace ml {

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

} // namespace ml
