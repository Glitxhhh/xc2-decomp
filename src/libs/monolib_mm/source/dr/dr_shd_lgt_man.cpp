#include "dr/dr_shd_lgt_man.h"

#include "dr/dr_ap_gx_type.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_shd_lgt_clustered.h"
#include "dr/dr_shd_lgt_global_ibl.h"
#include "dr/dr_shd_lgt_hybrid.h"
#include "dr/dr_shd_lgt_obj.h"
#include "grlib/cglib_ctl_shader.h"
#include "grlib/cglib_shd_list.h"
#include "ml/file_res_th.h"
#include "ml/scn.h"
#include "ml/work_util.h"
#include "mtl/alloc_handle.h"

namespace ml {

DrShdLgtMan::DrShdLgtMan(DrMan *drMan) : unknown00(drMan), unknown08(nullptr), m_hybridLight(nullptr), unknown60(nullptr) {
  unknown10 = new (unknown00->unknown0c) grlib::CGLibShdListBase<DrShdLgtObj>();
  unknown30.setLgtVertexParam();
  releaseLightShader();
  reloadShader(0);
  m_hybridLight = new (drMan->unknown0c) DrShdLgtHybrid(drMan);
  unknown58 = new (drMan->unknown0c) DrShdLgtGlobalIBL(drMan);
  unknown60 = new (drMan->unknown0c) DrShdLgtClustered(drMan, true);
}

void DrShdLgtMan::releaseLightShader() {
  unknown10->release();
  if (unknown08 != nullptr) {
    unknown08->Release();
    unknown08 = nullptr;
  }
}

void DrShdLgtMan::reloadShader(int) {
  Scn *scn = Scn::get();
  if (scn != nullptr) {
    unknown08 = scn->allocEntryRes("/monolib/shader/shd_lgt.wishp");
  }
  if (unknown08 == nullptr) {
    unknown08 = new (WorkUtil::getWorkMem()) FileResTh();
    unknown08->loadBlock(unknown00->unknown1c, "/monolib/shader/shd_lgt.wishp", 0x1000, 0);
  }
  createLightShader();
}

DrShdLgtMan::~DrShdLgtMan() {
  releaseLightShader();
  unknown30.clearWork();
  if (m_hybridLight != nullptr) {
    delete m_hybridLight;
    m_hybridLight = nullptr;
  }
  if (unknown58 != nullptr) {
    delete unknown58;
    unknown58 = nullptr;
  }
  if (unknown60 != nullptr) {
    delete unknown60;
    unknown60 = nullptr;
  }
  if (unknown10 != nullptr) {
    delete unknown10;
    unknown10 = nullptr;
  }
}

DrShdLgtHybrid *DrShdLgtMan::getHybridLight() { return m_hybridLight; }

const char *DrShdLgtMan::getDeclarationName(DECLARATION type) const { return s_DeclarationNames[type]; }

void DrShdLgtMan::renderBegin() {
  unknown42 = 0xffff;
  unknown44 = 0xffff;
  unknown48 = 0xffffffff;
  unknown40 = 1;
}

void DrShdLgtMan::beforeUpdateCate(int viewNum) { unknown58->update(viewNum); }

void DrShdLgtMan::resetColorBuff(int index) {
  DrShdLgtGlobalIBL *globalIBL = unknown58;
  if (globalIBL != nullptr) {
    globalIBL->resetColorBuff(index);
  }
}

void DrShdLgtMan::setupLocalIBLShader(DrShdLgtObj *obj) { grlib::CGLibCtlShader::setShader(*obj, unknown30); }

void DrShdLgtMan::setupGlobalIBLShader(DrShdLgtObj *obj) { grlib::CGLibCtlShader::setShader(*obj, unknown30); }

DrShdLgtObj *DrShdLgtMan::getGlobalIBLShader(GIBL_SHADER_TYPE type) { return &unknown18[1][type]; }

DrShdLgtObj *DrShdLgtMan::getComputeShader(COMP_SHADER_TYPE type) { return &unknown18[2][type]; }

void DrShdLgtMan::stockBegin() {
  m_hybridLight->stockBegin();
  unknown60->stockBegin();
}

void DrShdLgtMan::stockEnd() {
  m_hybridLight->stockEnd();
  unknown60->stockEnd();
}

void DrShdLgtMan::updateCate(int cate) {
  m_hybridLight->update();
  unknown60->update();
}

void DrShdLgtMan::setupCate(int cate) {
  m_hybridLight->setupCate(cate);
  unknown60->setupCate(cate);
}

void DrShdLgtMan::addViewInfo(int cate) {
  m_hybridLight->addViewInfo(cate);
  unknown60->addViewInfo(cate);
}

void DrShdLgtMan::delViewInfo(int cate) {
  m_hybridLight->delViewInfo(cate);
  unknown60->delViewInfo(cate);
  unknown58->delViewInfo(cate);
}

bool DrShdLgtMan::createLightShader() {
  if (unknown10->createPacShader(unknown08->unknownc8, 0x3f3, true)) {
    for (s32 i = 0; i < unknown10->unknown54; i++) {
      unknown18[i] = unknown10->unknown004(i);
    }
    return true;
  }
  return false;
}

void DrShdLgtMan::setupLgtBuff() {
  if (unknown48 != 0) {
    unknown48 = 0;
    DrAPGxType::setupCullingOff();
    DrAPGxType::setupBlend(7);
    unknown00->unknown78->selectLightRenderTarget();
  }
}

} // namespace ml
