#include "dr/dr_pixl_post_obj_depthof_field.h"

#include "dr/dr_ap_cache.h"
#include "dr/dr_ap_gx_type.h"
#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_pixl_render_target.h"
#include "dr/dr_res_filter_data.h"
#include "dr/dr_shd_data_list.h"
#include "dr/dr_shd_data_obj.h"
#include "dr/dr_shd_man.h"
#include "grlib/cglib_render_target.h"
#include "grlib/cglib_shader.h"
#include "grlib/cglib_uni_base_utility.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_array.h"

namespace ml {

DrPixlPostObjDepthofField::~DrPixlPostObjDepthofField() {
  unknown001(unknown18);
  unknown001(unknown20);
  unknown001(unknown28);
  unknown001(unknown30);
  unknown001(unknown38);
  unknown001(unknown48);
  unknown001(unknown40);
}

void DrPixlPostObjDepthofField::update() {
  s32 pixlLv = unknown00->unknown120[unknown00->unknown1c98]->unknown238;
  if (unknown50 != pixlLv) {
    unknown50 = pixlLv;
    if (pixlLv == 0) {
      unknown54 = 1.0f;
    } else if (pixlLv == 1) {
      unknown54 = 2.0f;
    } else {
      unknown54 = 4.0f;
    }
    resetColorBuff();
  }
  unknown59 = false;
  DrPixlPostParm *postParm = unknown00->unknown120[unknown00->unknown1c98];
  if (postParm->m_colTblOn) {
    DrResFilterData *filterData = unknown00->unknown98;
    f32 ratio = filterData->unknown10[filterData->unknown100].unknown34;
    unknown59 = postParm->unknown274;
    if (ratio == 1.0f && postParm->unknown278 == postParm->unknown26c && filterData->unknown10[filterData->unknown100].unknown26 == postParm->unknown278 &&
        filterData->unknown10[filterData->unknown100].unknown24 == postParm->unknown278) {
      unknown59 = false;
    }
  }
}

void DrPixlPostObjDepthofField::render() {
  if (unknown00->unknown120[unknown00->unknown1c98]->unknown21c) {
    renderDepthSample();
    renderDepthAllSample();
  }
  renderDofScaleDown();
  renderDofPass();
  renderCalc();
}

void DrPixlPostObjDepthofField::releaseColorBuff() {
  unknown18->releaseTexture();
  unknown20->releaseTexture();
  unknown28->releaseTexture();
  unknown30->releaseTexture();
  unknown38->releaseTexture();
  unknown48->releaseTexture();
}

void DrPixlPostObjDepthofField::renderDofScaleDown() {
  DrAPGxType::setupScreenQuads(false);
  unknown18->setRenderTarget();
  DrAPCache *apCache = unknown00->unknown5c0;
  DrPixlPostParm *postParm = unknown00->unknown120[unknown00->unknown1c98];
  DrShdDataList *shdList = unknown00->unknown80->unknown00;
  DrShdDataObj *shader = shdList->getPostShdObj(0x22);
  u32 downSec = postParm->unknown21b ? 1 : 2;
  shader->setDeclarationIdx(shader->getDeclarationOfs("DOWN_SEC"), downSec);
  shdList->bindTriangleTex();
  shader->setupShader(0u);
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  int frameLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
  int colorLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("s1");
  u32 scaleOffset = uniform.unknown001("gScal");
  u32 ratioOffset = uniform.unknown001("ratio");
  u32 dofParamOffset = uniform.unknown001("dofpam");
  f32 width = static_cast<f32>(unknown00->unknown5b8->unknown18);
  f32 height = static_cast<f32>(unknown00->unknown5b8->unknown1c);
  f32 scaleU = (width - 1.0f) / width;
  f32 scaleV = (height - 1.0f) / height;
  f32 work[8];
  if (!postParm->unknown21b) {
    work[0] = scaleU;
    work[1] = scaleV;
    work[2] = 1.0f / (width + width) - 1.0f / static_cast<f32>(unknown18->unknownbc);
    work[3] = 1.0f / (height + height) - 1.0f / static_cast<f32>(unknown18->unknownc0);
  } else {
    work[0] = 1.0f;
    work[1] = 1.0f;
    work[2] = (1.0f / static_cast<f32>(unknown18->unknownbc)) * -0.5f;
    work[3] = (1.0f / static_cast<f32>(unknown18->unknownc0)) * -0.5f;
  }
  uniform.setF32SetVec4(scaleOffset, work);
  DrCalcViewWork *viewWork = unknown00->unknown580->unknown10;
  f32 focus = postParm->unknown224 / viewWork->unknown430.x + viewWork->unknown430.y;
  f32 range = postParm->unknown228 / viewWork->unknown430.x;
  work[0] = -focus;
  work[1] = -1.0f / range;
  work[2] = postParm->unknown234;
  work[3] = postParm->unknown22c;
  uniform.setF32SetVec4(ratioOffset, work);
  work[0] = -focus;
  work[1] = -1.0f / range;
  work[2] = postParm->unknown21c ? 1.0f : 0.0f;
  work[3] = 0.0f;
  uniform.setF32SetVec4(dofParamOffset, work);
  int ratioLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("ratTex");
  apCache->beginTexSampling(2, 0);
  apCache->setTexture(*unknown48->unknown70, ratioLocation);
  if (!postParm->unknown21b) {
    u32 ofsOffset = uniform.unknown001("ofs[0]");
    f32 ofsU = scaleU / width;
    f32 ofsV = scaleV / height;
    work[0] = ofsU;
    work[1] = -ofsV;
    work[2] = ofsU * 3.0f;
    work[3] = -ofsV;
    work[4] = ofsU * 3.0f;
    work[5] = ofsV * -3.0f;
    work[6] = ofsU;
    work[7] = ofsV * -3.0f;
    uniform.setF32SetF32Array(ofsOffset, work, 8);
    apCache->beginTexSampling(2, 1);
  } else {
    apCache->beginTexSampling(2, 0);
  }
  apCache->setTexture(*unknown08->unknown7f0->unknown138->unknown70, frameLocation);
  wkPixlManRes *res = unknown08->unknown7f0;
  DrPixlRenderTarget *colorBuff = postParm->m_TMAAOn ? res->unknown00[13][DrMan::s_nDblIdx] : res->unknown00[4][0];
  apCache->setTexture(*colorBuff->unknown70, colorLocation);
  uniform.updateData();
  uniform.setUniformBlock();
  shdList->renderTriangle();
  unknown18->setColorInvalidate();
}

void DrPixlPostObjDepthofField::renderCalc() {
  DrAPGxType::setupBlend(1);
  unknown08->unknown7f0->unknown138->setRenderTarget();
  DrShdMan *shdMan = unknown00->unknown80;
  DrAPCache *apCache = unknown00->unknown5c0;
  DrPixlPostParm *postParm = unknown00->unknown120[unknown00->unknown1c98];
  DrShdDataList *shdList = shdMan->unknown00;
  DrShdDataObj *shader = shdList->getPostShdObj(0x15);
  u32 autoFocus = postParm->unknown21c ? 1 : 2;
  shader->setDeclarationIdx(shader->getDeclarationOfs("AUTO_FOCUS"), autoFocus);
  shdList->bindTriangleTex();
  shader->setupShader(0u);
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  int colorLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
  int blurLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("s1");
  u32 sclOffset = uniform.unknown001("scl");
  u32 ratioOffset = uniform.unknown001("ratio");
  f32 width = static_cast<f32>(unknown30->unknownbc);
  f32 height = static_cast<f32>(unknown30->unknownc0);
  f32 work[4];
  work[0] = (width - 1.0f) / width;
  work[1] = (height - 1.0f) / height;
  work[2] = 1.0f / (width + width);
  work[3] = 1.0f / (height + height);
  uniform.setF32SetVec4(sclOffset, work);
  DrCalcViewWork *viewWork = unknown00->unknown580->unknown10;
  f32 focus = postParm->unknown224 / viewWork->unknown430.x + viewWork->unknown430.y;
  f32 range = postParm->unknown228 / viewWork->unknown430.x;
  work[0] = -focus;
  work[1] = -1.0f / range;
  work[2] = postParm->unknown234;
  work[3] = postParm->unknown22c;
  uniform.setF32SetVec4(ratioOffset, work);
  wkPixlManRes *res = unknown08->unknown7f0;
  DrPixlRenderTarget *colorBuff = postParm->m_TMAAOn ? res->unknown00[13][DrMan::s_nDblIdx] : res->unknown00[4][0];
  apCache->beginTexSampling(2, 0);
  apCache->setTexture(*colorBuff->unknown70, colorLocation);
  apCache->beginTexSampling(2, 1);
  apCache->setTexture(*unknown30->unknown70, blurLocation);
  if (postParm->unknown21c) {
    int ratioLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("ratTex");
    apCache->beginTexSampling(2, 0);
    apCache->setTexture(*unknown48->unknown70, ratioLocation);
  }
  uniform.updateData();
  uniform.setUniformBlock();
  shdList->renderTriangle();
  DrAPGxType::setupBlend(0);
}

} // namespace ml
