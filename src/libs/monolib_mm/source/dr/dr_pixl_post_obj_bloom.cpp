#include "dr/dr_pixl_post_obj_bloom.h"

#include "dr/dr_ap_cache.h"
#include "dr/dr_ap_gx_type.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_post_obj.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_pixl_render_target.h"
#include "dr/dr_shd_data_list.h"
#include "dr/dr_shd_data_obj.h"
#include "dr/dr_shd_man.h"
#include "grlib/cglib_ctl_shader.h"
#include "grlib/cglib_render_target.h"
#include "grlib/cglib_shader.h"
#include "grlib/cglib_uni_base_utility.h"
#include "mm_mtl/fixed_array.h"
#include "mtl/alloc_handle.h"

namespace ml {

namespace _dppob {

f32 lerp(f32 a, f32 b, f32 t) { return a * (1.0f - t) + b * t; }

} // namespace _dppob

const f32 DrPixlPostObjBloom::BLOOMTEX_SCALE_OLD = 0.5f;
const f32 DrPixlPostObjBloom::BLOOMTEX_SCALE_NEW = 0.25f;
f32 DrPixlPostObjBloom::BLOOMTEX_SCALE = DrPixlPostObjBloom::BLOOMTEX_SCALE_NEW;

DrPixlPostObjBloom::DrPixlPostObjBloom(DrMan *drMan, DrPixlMan *pixlMan, DrPixlPostMan *postMan) : DrPixlPostObj(drMan, pixlMan, postMan) {
  unknown90 = 0;
  unknown94 = 0;
  unknown18 = nullptr;
  unknown20 = nullptr;
  unknown28 = nullptr;
  unknown30 = nullptr;
  for (int i = 0; i < 5; i++) {
    unknown38[i] = nullptr;
  }
  unknown18 = new (unknown00->unknown0c) DrPixlRenderTarget(unknown00);
  unknown20 = new (unknown00->unknown0c) DrPixlRenderTarget(unknown00);
  unknown28 = new (unknown00->unknown0c) DrPixlRenderTarget(unknown00);
  unknown30 = new (unknown00->unknown0c) DrPixlRenderTarget(unknown00);
  for (int i = 0; i < 5; i++) {
    unknown38[i] = new (unknown00->unknown0c) DrPixlRenderTarget(unknown00);
    unknown60[i] = new (unknown00->unknown0c) DrPixlRenderTarget(unknown00);
  }
  for (int i = 0; i < 2; i++) {
    m_lgtDownTarget[i] = new (unknown00->unknown0c) DrPixlRenderTarget(unknown00);
  }
  unknown94 |= 1;
  unknowna8 = 0;
}

void DrPixlPostObjBloom::calculateDownScale() {
  DrPixlPostParm *postParm = unknown00->unknown120[unknown00->unknown1c98];
  if (postParm->unknownf72 && postParm->m_TMAAOn) {
    calculateDownScale_TwoPass();
  } else {
    calculateDownScaleImpl(DOWN_SCALE_TYPE_UNKNOWN_0);
  }
}

void DrPixlPostObjBloom::calculateDownScale_TwoPass() {
  calculateDownScaleImpl(DOWN_SCALE_TYPE_UNKNOWN_1);
  grlib::CGLibCtlShader::setMemoryBarrierBit(2);
  calculateDownScaleImpl(DOWN_SCALE_TYPE_UNKNOWN_2);
}

DrPixlPostObjBloom::~DrPixlPostObjBloom() { releaseBloomTexture(); }

void DrPixlPostObjBloom::releaseBloomTexture() {
  unknown001(unknown18);
  unknown001(unknown20);
  unknown001(unknown28);
  unknown001(unknown30);
  for (int i = 0; i < 5; i++) {
    unknown001(unknown38[i]);
    unknown001(unknown60[i]);
  }
  unknown001(m_lgtDownTarget[0]);
  unknown001(m_lgtDownTarget[1]);
}

void DrPixlPostObjBloom::update() { unknown90 = 0; }

void DrPixlPostObjBloom::calcRender() {
  s32 scaleType = unknown00->unknown120[unknown00->unknown1c98]->unknownf58;
  if (unknowna8 != scaleType) {
    BLOOMTEX_SCALE = scaleType == 1 ? BLOOMTEX_SCALE_NEW : BLOOMTEX_SCALE_OLD;
    releaseColorBuff(true);
    resetColorBuff(true);
    unknown94 |= 1;
    unknowna8 = scaleType;
  }
  DrAPGxType::setupScreenQuads(false);
  calculateDownScale();
  calculateGaussBlur();
}

void DrPixlPostObjBloom::releaseColorBuff(bool isForce) {
  DrPixlPostParm *postParm = unknown00->unknown120[unknown00->unknown1c98];
  if (postParm->unknownfe4 == 3 || isForce) {
    m_lgtDownTarget[0]->releaseTexture();
    m_lgtDownTarget[1]->releaseTexture();
  } else {
    m_lgtDownTarget[DrMan::s_nDblIdx]->releaseTexture();
  }
  if (postParm->unknownfe4 == 2 && !isForce) {
    return;
  }
  unknown18->releaseTexture();
  unknown20->releaseTexture();
  for (int i = 0; i < 5; i++) {
    unknown38[i]->releaseTexture();
    unknown60[i]->releaseTexture();
  }
  unknown28->releaseTexture();
  unknown30->releaseTexture();
}

grlib::CGLibRenderTarget *DrPixlPostObjBloom::getLgtDownTarget() { return m_lgtDownTarget[DrMan::s_nDblIdx]; }

void DrPixlPostObjBloom::bloomLensFlare() {
  DrAPGxType::setupBlend(2);
  unknown38[2]->setRenderTarget();
  setScaleShader(static_cast<DrPixlRenderTarget *>(unknown30));
  unknown38[2]->setColorInvalidate();
  DrAPGxType::setupBlend(0);
}

void DrPixlPostObjBloom::calculateGaussBlur() {
  DrPixlPostParm *postParm = unknown00->unknown120[unknown00->unknown1c98];
  calculateGaussBlurImplPS();
  if (postParm->unknown3e) {
    calculateFlareBuff();
    calculateLensFlare();
    bloomLensFlare();
  }
}

void DrPixlPostObjBloom::calculateFlareBuff() {
  unknown28->setRenderTarget();
  DrShdDataList *shdList = unknown00->unknown80->unknown00;
  DrShdDataObj *shader = shdList->getPostShdObj(8);
  shdList->unknown002(shader);
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  DrAPCache *apCache = unknown00->unknown5c0;
  int location = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
  u32 scaleOffset = uniform.unknown001("gScal");
  u32 ratioOffset = uniform.unknown001("ratio");
  f32 height = static_cast<f32>(unknown18->unknownc0);
  f32 width = static_cast<f32>(unknown18->unknownbc);
  // Sixteen floats although four are used: with f32 work[4] the only difference is the frame (sub sp, sp, #160 instead
  // of the game's #208 in 0x7100854cb0).
  f32 work[16];
  work[0] = (width - 1.0f) / width;
  work[1] = (height - 1.0f) / height;
  work[2] = 1.0f / (width + width);
  work[3] = 1.0f / (height + height);
  uniform.setF32SetVec4(scaleOffset, work);
  DrPixlPostParm *postParm = unknown00->unknown120[unknown00->unknown1c98];
  work[0] = postParm->unknownc8;
  work[1] = postParm->unknowncc * (1.0f / 3.0f);
  uniform.setF32SetVec4(ratioOffset, work);
  apCache->beginTexSampling(2, 1);
  apCache->setTexture(*unknown38[2]->unknown70, location);
  uniform.updateData();
  uniform.setUniformBlock();
  shdList->renderQuads();
  unknown28->setColorInvalidate();
}

} // namespace ml
