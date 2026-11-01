#include "dr/dr_pixl_post_obj_motion_blur2.h"

#include "dr/dr_ap_gx_type.h"
#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_pixl_render_target.h"
#include "grlib/cglib_ctl_shader.h"
#include "grlib/cglib_vtx_vertex.h"
#include "mm_mtl/fixed_array.h"

namespace ml {

// Inferred role: deletes an object and clears the pointer; original name unknown.
template <typename T> inline void unknown001(T *&object) {
  T *deleted = object;
  if (deleted != nullptr) {
    delete deleted;
    object = nullptr;
  }
}

DrPixlPostObjMotionBlur2::~DrPixlPostObjMotionBlur2() {
  unknown001(unknown50);
  unknown001(unknown58);
  unknown001(unknown28);
  unknown001(unknown30);
  unknown001(unknown38);
  unknown001(unknown48);
  unknown001(unknown40);
  unknown001(unknown20);
}

void DrPixlPostObjMotionBlur2::resetColorBuff() { calcBludBuffColorBuff(); }

void DrPixlPostObjMotionBlur2::update() {}

void DrPixlPostObjMotionBlur2::releaseColorBuff() {
  unknown28->releaseTexture();
  unknown30->releaseTexture();
  unknown20->releaseTexture();
  unknown38->releaseTexture();
  unknown40->releaseTexture();
  unknown48->releaseTexture();
}

void DrPixlPostObjMotionBlur2::render() {
  DrAPGxType::setupScreenQuads(false);
  calcBlurWork();
  calcObjMotionBlur();
  grlib::CGLibCtlShader::setMemoryBarrierBit(3);
  if (unknown64) {
    renderCalcBlur();
  }
  grlib::CGLibCtlShader::setMemoryBarrierBit(2);
  if (unknown64) {
    lastRender();
  }
}

void DrPixlPostObjMotionBlur2::calcObjMotionBlur() {
  if (!unknown00->unknown580->unknown10->unknown9aa && unknown00->unknown120[unknown00->unknown1c98]->unknown1cd) {
    calcVelocityBlur();
  }
  unknown00->blurCallBackRender();
  calcMaxVelocityPerTile();
  grlib::CGLibCtlShader::setMemoryBarrierBit(2);
  calcBlurMask();
}

} // namespace ml
