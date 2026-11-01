#include "dr/dr_pixl_post_obj_motion_blur.h"

#include "dr/dr_ap_gx_type.h"
#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_post_obj.h"
#include "dr/dr_pixl_post_parm.h"
#include "grlib/cglib_render_target.h"
#include "mm_mtl/fixed_array.h"

namespace ml {

DrPixlPostObjMotionBlur::~DrPixlPostObjMotionBlur() {
  unknown001(unknown28);
  unknown001(unknown30);
  unknown001(unknown20);
}

void DrPixlPostObjMotionBlur::debugRender() {}

void DrPixlPostObjMotionBlur::resetColorBuff() { calcBludBuffColorBuff(); }

void DrPixlPostObjMotionBlur::releaseColorBuff() {
  unknown28->releaseTexture();
  unknown30->releaseTexture();
  unknown20->releaseTexture();
}

void DrPixlPostObjMotionBlur::render() {
  DrAPGxType::setupScreenQuads(false);
  calcBlurWork();
  calcObjMotionBlur();
  renderCalcBlur();
  lastRender();
}

void DrPixlPostObjMotionBlur::calcObjMotionBlur() {
  DrPixlPostParm *postParm = unknown00->unknown120[unknown00->unknown1c98];
  if (!unknown00->unknown580->unknown10->unknown9a9 && postParm->unknown1cd && 0.0f < postParm->unknown1ec) {
    calcVelocityBlur();
  }
  unknown00->blurCallBackRender();
  unknown28->setColorInvalidate();
}
} // namespace ml
