#include "dr/dr_pixl_post_obj_tssao.h"

#include "dr/dr_man.h"
#include "dr/dr_pixl_post_man.h"
#include "dr/dr_pixl_post_obj.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_pixl_render_target.h"
#include "grlib/cglib_ctl_shader.h"
#include "mm_math/mm_vec4.h"
#include "mm_mtl/fixed_array.h"

namespace ml {

DrPixlPostObjTSSAO::~DrPixlPostObjTSSAO() {
  if (unknown48 != nullptr) {
    delete unknown48;
    unknown48 = nullptr;
  }
  if (unknown68 != nullptr) {
    delete unknown68;
    unknown68 = nullptr;
  }
  if (unknown60 != nullptr) {
    delete unknown60;
    unknown60 = nullptr;
  }
  if (unknown40 != nullptr) {
    delete unknown40;
    unknown40 = nullptr;
  }
  if (unknown38 != nullptr) {
    delete unknown38;
    unknown38 = nullptr;
  }
  if (unknown28[0] != nullptr) {
    delete unknown28[0];
    unknown28[0] = nullptr;
  }
  if (unknown50[0] != nullptr) {
    delete unknown50[0];
    unknown50[0] = nullptr;
  }
  if (unknown28[1] != nullptr) {
    delete unknown28[1];
    unknown28[1] = nullptr;
  }
  if (unknown50[1] != nullptr) {
    delete unknown50[1];
    unknown50[1] = nullptr;
  }
  if (unknown20 != nullptr) {
    delete unknown20;
    unknown20 = nullptr;
  }
}

void DrPixlPostObjTSSAO::calcFragCoordToUV(mm::Vec4 &uv, f32 width, f32 height) {
  uv.x = 1.0f / width;
  uv.y = 1.0f / height;
  uv.z = static_cast<f32>(unknown70) / width;
  uv.w = static_cast<f32>(unknown70) / height;
}

void DrPixlPostObjTSSAO::calcFragCoordToScreen(mm::Vec4 &screen, f32 width, f32 height) {
  screen.x = 2.0f / width;
  screen.y = 2.0f / height;
  screen.z = (static_cast<f32>(unknown70) + static_cast<f32>(unknown70)) / width - 1.0f;
  screen.w = (static_cast<f32>(unknown70) + static_cast<f32>(unknown70)) / height - 1.0f;
}

void DrPixlPostObjTSSAO::render_beforeTemporal() {
  DrPixlPostParm *postParm = unknown00->unknown120[unknown00->unknown1c98];
  if (!postParm->unknown174) {
    return;
  }
  if (postParm->unknownfb1) {
    passQuaterNormal();
  }
  passSSAO();
  grlib::CGLibCtlShader::setMemoryBarrierBit(2);
  passPrevBlur();
  passTemporalFiltering();
}

void DrPixlPostObjTSSAO::passPrevBlur() {
  f32 strength = unknown00->unknown120[unknown00->unknown1c98]->unknownf94;
  passBlur_Sub(BLUR_AXIS_UNKNOWN_1, strength, unknown20, unknown38, false);
  grlib::CGLibCtlShader::setMemoryBarrierBit(2);
  passBlur_Sub(BLUR_AXIS_UNKNOWN_2, strength, unknown38, unknown20, false);
}

void DrPixlPostObjTSSAO::render_afterTemporal() {
  DrPixlPostParm *postParm = unknown00->unknown120[unknown00->unknown1c98];
  if (!postParm->unknown174) {
    return;
  }
  passPostBlur();
  passUpScaleToMiddle();
}

void DrPixlPostObjTSSAO::passPostBlur() {
  f32 strength = unknown00->unknown120[unknown00->unknown1c98]->unknown188;
  DrPixlRenderTarget *source = unknown28[DrMan::s_nDblIdx];
  f32 weight[4];
  for (s32 i = 0; i < 4; i++) {
    weight[i] = DrPixlPostObj::gaussianDistribution(static_cast<f32>(i), 0.0f, 1.0f);
  }
  passBlur_Sub(BLUR_AXIS_UNKNOWN_1, strength, source, unknown38, false);
  grlib::CGLibCtlShader::setMemoryBarrierBit(2);
  passBlur_Sub(BLUR_AXIS_UNKNOWN_2, strength, unknown38, source, false);
}

void DrPixlPostObjTSSAO::passUpScaling() { passUpScaleToMiddle(); }

void DrPixlPostObjTSSAO::update() { unknown10->setDownDepth(); }

void DrPixlPostObjTSSAO::releaseColorBuff() {
  DrPixlPostParm *postParm = unknown00->unknown120[unknown00->unknown1c98];
  if (postParm->unknownfe4 == 3) {
    unknown28[0]->releaseTexture();
    unknown50[0]->releaseTexture();
    unknown28[1]->releaseTexture();
    unknown50[1]->releaseTexture();
  } else {
    unknown28[DrMan::s_nDblIdx]->releaseTexture();
    unknown50[DrMan::s_nDblIdx]->releaseTexture();
    if (postParm->unknownfe4 == 2) {
      return;
    }
  }
  unknown20->releaseTexture();
  unknown38->releaseTexture();
  if (unknown60 != nullptr) {
    unknown60->releaseTexture();
  }
  if (unknown68 != nullptr) {
    unknown68->releaseTexture();
  }
  unknown48->releaseTexture();
}

} // namespace ml
