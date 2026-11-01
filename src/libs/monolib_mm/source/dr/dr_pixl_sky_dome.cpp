#include "dr/dr_pixl_sky_dome.h"

#include "dr/dr_ap_gx_type.h"
#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_fog_man.h"
#include "dr/dr_light_man.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_res_use_query_obj.h"
#include "dr/dr_shd_data_list.h"
#include "dr/dr_shd_data_obj.h"
#include "dr/dr_shd_man.h"
#include "grlib/cglib_uni_base_utility.h"
#include "mm_math/mm_col3.h"
#include "mm_math/mm_vec4.h"
#include "types.h"

namespace ml {

void DrPixlSkyDome::luminanceRender() {
  DrFogMan *fogMan = unknown00->unknown590;
  if (fogMan->isFogOn() && fogMan->unknownd1) {
    DrPixlPostParm *postParm = unknown00->unknown120[unknown00->unknown1c98];
    DrLightMan *lightMan = unknown00->unknown588;
    f32 ratio = postParm->unknown46c;
    f32 otherRatio = postParm->unknown468;
    mm::Vec4 color;
    color.x = ratio * lightMan->unknown12c.r + otherRatio * lightMan->unknown120.r;
    color.y = ratio * lightMan->unknown12c.g + otherRatio * lightMan->unknown120.g;
    color.z = ratio * lightMan->unknown12c.b + otherRatio * lightMan->unknown120.b;
    color.w = 0.0f;
    renderColorBackground(color);
  }
}

DrPixlSkyDome::~DrPixlSkyDome() {
  if (unknown08 != nullptr) {
    delete unknown08;
    unknown08 = nullptr;
  }
}

void DrPixlSkyDome::renderColorBackground(const mm::Vec4 &color) {
  DrShdDataList *shdList = unknown00->unknown80->unknown00;
  DrShdDataObj *shader = shdList->getPostShdObj(18);
  shader->setDeclarationIdx(shader->getDeclarationOfs("DEB_SKY_VISIBILITY"), 2);
  shader->setDeclarationIdx(shader->getDeclarationOfs("DEB_SKY_AMBIENT"), 1);
  shader->setDeclarationIdx(shader->getDeclarationOfs("OUTPUT_VELOCITY"), 2);
  DrCalcViewWork *viewWork = unknown00->unknown580->unknown10;
  DrAPGxType::setupStencilTest(true, false, 2, false, 0, 0, 2, 0, 0, 0);
  DrAPGxType::setupBlend(0);
  shdList->bindShdVertex();
  shader->setupShader(0u);
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  u32 projOffset = uniform.unknown001("proj");
  u32 ambientOffset = uniform.unknown001("cSkyAmbient");
  uniform.setMat44SetMat44(projOffset, viewWork->unknown1c0);
  uniform.setF32SetVec4(ambientOffset, &color.x);
  uniform.updateData();
  uniform.setUniformBlock();
  shdList->renderQuads();
}

void DrPixlSkyDome::renderBackgroundCube() {}

} // namespace ml
