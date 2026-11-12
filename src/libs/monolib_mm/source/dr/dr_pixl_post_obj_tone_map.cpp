#include "dr/dr_pixl_post_obj_tone_map.h"

#include "dr/dr_ap_cache.h"
#include "dr/dr_light_man.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_post_man.h"
#include "dr/dr_pixl_render_target.h"
#include "dr/dr_shd_data_list.h"
#include "dr/dr_shd_data_obj.h"
#include "dr/dr_shd_man.h"
#include "grlib/cglib_render_target.h"
#include "grlib/cglib_shader.h"
#include "grlib/cglib_uni_base_utility.h"
#include "mm_math/mm_vec4.h"

namespace ml {

void DrPixlPostObjToneMap::update() {
  if (unknown00->unknown058()) {
    return;
  }
  if ((unknownb4 & 0x10) != 0) {
    updateByCompute();
  } else {
    updateByRenderTarget();
  }
}

DrPixlPostObjToneMap::~DrPixlPostObjToneMap() {
  for (s32 i = 0; i < 6; i++) {
    unknown001(unknown18[i]);
  }
  unknown001(unknown98);
  unknown001(unknowna0);
  unknown48.release();
  unknown70.release();
}

void DrPixlPostObjToneMap::createMeasureLuminance() {
  if ((unknownb4 & 0x10) == 0) {
    creaetMeasureLuminaceByRenderTarget();
  } else {
    createMeasureLuminanceByCompute();
  }
}

void DrPixlPostObjToneMap::createSclDow() {
  unknown18[0]->setRenderTarget();
  DrShdDataList *shdList = unknown00->unknown80->unknown00;
  DrShdDataObj *shader = shdList->getPostShdObj(0);
  shdList->bindQuadsTex();
  shader->setupShader(0u);
  grlib::CGLibUniformEtcUtility uniform(shader);
  uniform.setUseUniformBlock("U_POST");
  u32 paramOffset = uniform.unknown001("gParam");
  mm::Vec4 param = mm::Vec4::zero;
  param.x = unknown00->unknown588->getSkyLuminance();
  uniform.setVec4SetVec4(paramOffset, param);
  uniform.updateData();
  uniform.setUniformBlock();
  int location = (shader->unknown38 + shader->unknown58)->getTextureLocation("s0");
  int depthLocation = (shader->unknown38 + shader->unknown58)->getTextureLocation("gTDownDepth");
  DrPixlRenderTarget *colorBuff = unknown08->unknown7f0->unknown138;
  DrPixlRenderTarget *downDepth = unknown08->unknown7f0->unknown180->getDownDepth();
  DrAPCache *apCache = unknown00->unknown5c0;
  apCache->beginTexSampling(2, 0);
  apCache->setTexture(*colorBuff->unknown70, location);
  apCache->setTexture(*downDepth->unknown70, depthLocation);
  shdList->renderQuads();
  unknown18[0]->setColorInvalidate();
}

} // namespace ml
