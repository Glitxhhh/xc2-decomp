#include "dr/dr_pixl_post_obj_volume.h"

#include "dr/dr_ap_cache.h"
#include "dr/dr_ap_gx_type.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_post_obj.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_pixl_render_target.h"
#include "dr/dr_shd_data_list.h"
#include "dr/dr_shd_data_obj.h"
#include "dr/dr_shd_man.h"
#include "grlib/cglib_ctl_shader.h"
#include "grlib/cglib_render_target.h"
#include "grlib/cglib_shader.h"
#include "mm_mtl/fixed_array.h"

namespace ml {

void DrPixlPostObjVolume::calculateSclDown() {
  if (unknown00->unknown120[unknown00->unknown1c98]->m_TMAAOn) {
    calculateSclDown_Temporal();
  } else {
    calculateSclDown_NonTemporal();
  }
}

void DrPixlPostObjVolume::volumeRender() {
  DrAPGxType::setupScreenQuads(false);
  calculateSclDown();
  grlib::CGLibCtlShader::setMemoryBarrierBit(2);
  calculateVolume();
}

DrPixlPostObjVolume::~DrPixlPostObjVolume() {
  unknown001(unknown18[0]);
  unknown001(unknown18[1]);
  unknown001(unknown28);
}

void DrPixlPostObjVolume::resetColorBuff() { calcColorBuff(); }

void DrPixlPostObjVolume::update() {}

void DrPixlPostObjVolume::releaseColorBuff() {
  if (unknown18[0] != nullptr) {
    unknown18[0]->releaseTexture();
  }
  if (unknown18[1] != nullptr) {
    unknown18[1]->releaseTexture();
  }
  unknown28->releaseTexture();
}

void DrPixlPostObjVolume::calculateSclDown_NonTemporal() {
  DrPixlRenderTarget *source = unknown08->unknown7f0->unknown00[7][0];
  source->setColorInvalidate();
  grlib::CGLibRenderTarget *target = unknown18[DrMan::s_nDblIdx];
  target->setRenderTarget();
  DrShdDataList *shdList = unknown00->unknown80->unknown00;
  DrShdDataObj *shader = shdList->getSelectShdObj(0);
  shdList->unknown002(shader);
  int location = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
  DrAPCache *apCache = unknown00->unknown5c0;
  apCache->beginTexSampling(2, 1);
  apCache->setTexture(*source->unknown70, location);
  shdList->renderQuads();
  target->setColorInvalidate();
}

} // namespace ml
