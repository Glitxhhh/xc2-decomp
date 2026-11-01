#include "dr/dr_gpu_check_render.h"

#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_man.h"
#include "dr/dr_mdl_man.h"
#include "dr/dr_mdo_vertex_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_shd_data_list.h"
#include "dr/dr_shd_data_obj.h"
#include "dr/dr_shd_man.h"
#include "grlib/cglib_ctl_vertex.h"
#include "grlib/cglib_shader.h"
#include "grlib/cglib_vtx_instans.h"
#include "grlib/shd_util.h"
#include "mm_math/mm_mat44.h"

namespace ml {

DrGpuCheckRender::DrGpuCheckRender() { unknown18.setup(0x80); }

DrGpuCheckRender::~DrGpuCheckRender() {}

void DrGpuCheckRender::beginUpdate() {
  unknown00 = DrMan::get()->unknown580->unknown10;
  unknown10 = DrMan::get()->unknown88->unknown008->unknown10;
  unknown50 = unknown10->getNextInstansBuff();
  s32 offset = unknown10->unknown08;
  unknown58 = offset;
  unknown5c = offset;
  unknown64 = 1;
}

void DrGpuCheckRender::endUpdate() {
  if (unknown58 != unknown5c) {
    unknown10->unknown08 = unknown58 - unknown5c + unknown10->unknown08;
  }
}

void DrGpuCheckRender::beginRender(bool isDblDepth) {
  DrMan::get()->unknown78->depCheckBegin(isDblDepth);
  unknown00 = DrMan::get()->unknown580->unknown10;
  unknown08 = DrMan::get()->unknown80->unknown00;
  DrShdDataObj *shader = unknown08->getSelectShdObj(8);
  unknown60 = shader->getDeclarationOfs("EFFMODE");
  unknown08->bindShdDepthCheck();
  shader->setDeclarationIdx(unknown60, 1);
  unknown64 = 1;
  shader->setupShader(0u);
  u32 staticOfs = (shader->unknown38 + shader->unknown58)->getUniformBlockOfs("U_Static");
  unknown00->unknown7b0.setUniformBlock(staticOfs);
  f32 *buff = static_cast<f32 *>(unknown18.getBuff());
  grlib::ShdMat44TransposeMat34(buff, unknown00->unknown40);
  grlib::ShdMat44TransposeMat44(buff + 12, unknown00->unknown180);
  f32 width = DrMan::get()->unknown5b8->unknown28;
  f32 height = DrMan::get()->unknown5b8->unknown2c;
  f32 invX = 1.0f / unknown00->unknown180.rows[0][0];
  f32 invY = 1.0f / unknown00->unknown180.rows[1][1];
  buff[28] = invX / width * 0.5f;
  buff[29] = invY / height * 0.5f;
  buff[30] = 0.0f;
  buff[31] = 0.0f;
  unknown18.updateData();
  unknown18.setUniformBlock((shader->unknown38 + shader->unknown58)->getUniformBlockOfs("U_Sub"));
}

void DrGpuCheckRender::endRender() { DrMan::get()->unknown78->depCheckEnd(); }

void DrGpuCheckRender::render(u32 offset, int mode) {
  if (unknown64 != mode) {
    DrShdDataObj *shader = unknown08->getSelectShdObj(8);
    shader->setDeclarationIdx(unknown60, mode);
    shader->setupShader(0u);
    if (mode == 1) {
      unknown08->bindShdDepthCheck();
    } else {
      unknown08->bindShdBoxVertex();
    }
    unknown64 = mode;
  }
  grlib::CGLibCtlVertex::setInstanceVertex(*unknown10, 16, offset, 1, 1);
  if (mode == 1) {
    unknown08->renderQuads();
  } else {
    unknown08->renderBox();
  }
}

} // namespace ml
