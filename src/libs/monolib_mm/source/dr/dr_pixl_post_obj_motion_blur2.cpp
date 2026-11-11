#include "dr/dr_pixl_post_obj_motion_blur2.h"

#include "dr/dr_ap_gx_type.h"
#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_pixl_render_target.h"
#include "grlib/cglib_ctl_shader.h"
#include "grlib/cglib_vtx_vertex.h"
#include "mm_mtl/fixed_array.h"
#include "mtl/alloc_handle.h"

namespace ml {

// Inferred role: deletes an object and clears the pointer; original name unknown.
template <typename T> inline void unknown001(T *&object) {
  T *deleted = object;
  if (deleted != nullptr) {
    delete deleted;
    object = nullptr;
  }
}

DrPixlPostObjMotionBlur2::DrPixlPostObjMotionBlur2(DrMan *drMan, DrPixlMan *pixlMan, DrPixlPostMan *postMan)
    : DrPixlPostObj(drMan, pixlMan, postMan), unknown20(nullptr), unknown28(nullptr), unknown30(nullptr), unknown60(0), unknown64(true) {
  unknown28 = new (unknown00->unknown0c) DrPixlRenderTarget(unknown00);
  unknown30 = new (unknown00->unknown0c) DrPixlRenderTarget(unknown00);
  unknown38 = new (unknown00->unknown0c) DrPixlRenderTarget(unknown00);
  unknown48 = new (unknown00->unknown0c) DrPixlRenderTarget(unknown00);
  unknown40 = new (unknown00->unknown0c) DrPixlRenderTarget(unknown00);
  unknown20 = new (unknown00->unknown0c) DrPixlRenderTarget(unknown00);
  for (s32 i = 0; i < 2; i++) {
    unknown50[i] = new (unknown00->unknown0c) grlib::CGLibVtxVertex();
  }
  calcBludBuffColorBuff();
  unknown18 = 0.0f;
  unknown1c = 0.0f;
}

void DrPixlPostObjMotionBlur2::debugRender() {
  if (unknown00->unknown120[unknown00->unknown1c98]->isMotBlur2() && unknown00->unknown120[unknown00->unknown1c98]->unknown1000) {
    s32 width = unknown00->unknown5b8->unknown28;
    s32 height = unknown00->unknown5b8->unknown2c;
    unknown00->unknown78->debugRender(*unknown48->unknown70, 0, 0, width, height, false, false, 0.2f, true);
  }
}

DrPixlPostObjMotionBlur2::~DrPixlPostObjMotionBlur2() {
  for (int i = 0; i < 2; i++) {
    unknown001(unknown50[i]);
  }
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
