#include "dr/dr_shd_data_list.h"

#include <string.h>

#include "dr/dr_man.h"
#include "dr/dr_res_shd.h"
#include "dr/dr_shd_data_obj.h"
#include "grlib/cglib_ctl_shader.h"
#include "grlib/cglib_ctl_vertex.h"
#include "grlib/cglib_one_uniform_block.h"
#include "grlib/cglib_shd_list.h"
#include "ml/file_res_th.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace ml {

void DrShdDataObj::createShader(DrShdDataList *list, int type, int index) {
  if (type == 2) {
    return;
  }
  unknown68[0] = &list->unknown68[index];
  u8 next = DrShdDataList::s_etcNextVertex[index];
  unknown68[1] = next == 0xff ? nullptr : &list->unknown68[next];
}

DrShdDataList::DrShdDataList(DrMan *drMan) : unknown00(nullptr), unknown08(drMan), unknown10(nullptr), unknown620(nullptr) {
  memset(unknown18, 0, sizeof(unknown18));
  unknown618 = new (unknown08->unknown0c) grlib::CGLibShdListBase<DrShdDataObj>();
  createWork();
  createShader();
}

DrShdDataList::~DrShdDataList() {
  releaseShader();
  for (int i = 0; i < 12; i++) {
    unknown638[i].release();
  }
  for (int i = 0; i < 8; i++) {
    unknown818[i].release();
  }
  unknown958.release();
  unknown980.release();
  for (int i = 0; i < 91; i++) {
    unknown68[i].clearWork();
  }
  unknown9a8.unknown001();
  if (unknown618 != nullptr) {
    delete unknown618;
    unknown618 = nullptr;
  }
}

void DrShdDataList::releaseShader() {
  if (unknown10 != nullptr) {
    unknown618->release();
    if (unknown10 != nullptr) {
      mtl::MemManager::deallocate(unknown10, 0, false);
      unknown10 = nullptr;
    }
  }
  if (unknown00 != nullptr) {
    unknown00->Release();
    unknown00 = nullptr;
  }
}

void DrShdDataList::reloadShader(int type) { createShader(); }

DrShdDataObj *DrShdDataList::getDebugShdObj(int index) { return &unknown18[0][index]; }

DrShdDataObj *DrShdDataList::getSelectShdObj(int index) { return &unknown18[1][index]; }

DrShdDataObj *DrShdDataList::getShadowShdObj(int index) { return &unknown18[2][index]; }

DrShdDataObj *DrShdDataList::getPostShdObj(int index) { return &unknown18[3][index]; }

DrShdDataObj *DrShdDataList::getSteamShdObj(int index) { return &unknown18[4][index]; }

DrShdDataObj *DrShdDataList::getMpfShdObj(int index) { return &unknown18[5][index]; }

DrShdDataObj *DrShdDataList::getPreShdObj(int index) { return &unknown18[6][index]; }

DrShdDataObj *DrShdDataList::getComputeObj(int index) { return &unknown18[9][index]; }

DrShdDataObj *DrShdDataList::getCateShdObj(int category, int index) { return &unknown18[category][index]; }

DrResShdMpf *DrShdDataList::getMpfObj(int index) { return &unknown620[index]; }

DrResShdPrePass *DrShdDataList::getPrePassObj(int index) { return &unknown628[index]; }

DrResShdShw *DrShdDataList::getShwObj(int index) { return &unknown630[index]; }

DrResShdStreamOut *DrShdDataList::getStmOutObj(int index) { return &unknown9d0[index]; }

DrResShdObjMot *DrShdDataList::getObjMotBlurObj(int index) { return &unknown9d8[index]; }

void DrShdDataList::bindShdVertex() { grlib::CGLibCtlVertex::setVertex(unknown638[0]); }

void DrShdDataList::bindShdSphereVertex() { grlib::CGLibCtlVertex::setVertex(unknown638[5]); }

void DrShdDataList::bindShdSpotVertex() { grlib::CGLibCtlVertex::setVertex(unknown638[7]); }

void DrShdDataList::bindQuadsTex() { grlib::CGLibCtlVertex::setVertex(unknown638[1]); }

void DrShdDataList::bindTriangle() { grlib::CGLibCtlVertex::setVertex(unknown638[2]); }

void DrShdDataList::bindTriangleTex() { grlib::CGLibCtlVertex::setVertex(unknown638[3]); }

void DrShdDataList::bindShdBoxVertex() { grlib::CGLibCtlVertex::setVertex(unknown638[4]); }

void DrShdDataList::bindShdCylinderVertex() { grlib::CGLibCtlVertex::setVertex(unknown638[6]); }

void DrShdDataList::bindShdRainDropVertex() { grlib::CGLibCtlVertex::setVertex(unknown638[8]); }

void DrShdDataList::bindShdEffVtx() { grlib::CGLibCtlVertex::setVertex(unknown638[9]); }

void DrShdDataList::bindShdDepthCheck() { grlib::CGLibCtlVertex::setVertex(unknown638[10]); }

void DrShdDataList::bindPlaneVertex() { grlib::CGLibCtlVertex::setVertex(unknown638[11]); }

void DrShdDataList::renderQuads() { unknown818[0].drawIndex(); }

void DrShdDataList::renderInstQuads(int instanceCount) { unknown818[0].drawInsIndex(instanceCount); }

void DrShdDataList::renderTriangle() { unknown818[1].drawIndex(); }

void DrShdDataList::renderSphere() { unknown818[3].drawIndex(); }

void DrShdDataList::renderSpotMdl() { unknown818[5].drawIndex(); }

void DrShdDataList::renderBox() { unknown818[2].drawIndex(); }

void DrShdDataList::renderCylinder() { unknown818[4].drawIndex(); }

void DrShdDataList::renderRainDrop() { unknown818[6].drawIndex(); }

void DrShdDataList::renderEffVtx(int instanceCount) { unknown818[7].drawInsIndex(instanceCount); }

void DrShdDataList::renderPoint(int count) { grlib::CGLibCtlVertex::renderVertex(GRL_PRIMITIVE_POINTS, count); }

void DrShdDataList::renderPoint(int count, int instanceCount) { grlib::CGLibCtlVertex::renderInstanceVertex(GRL_PRIMITIVE_POINTS, count, instanceCount); }

DrResFetch *DrShdDataList::getFetchShader(int index) { return &unknown68[index]; }

DrResFetch *DrShdDataList::getSubFetchShader(int index) {
  u8 next = s_etcNextVertex[index];
  return next == 0xff ? nullptr : &unknown68[next];
}

grlib::CGLibOneUniformBlock *DrShdDataList::getAlphaTestUniform(f32 alphaRef) {
  u32 index = static_cast<s32>(alphaRef * 10.0f);
  if (index > 10) {
    index = 10;
  }
  return &unknown9a8.m_items[index];
}

DrShdDataObj::DrShdDataObj() {
  unknown68[0] = nullptr;
  unknown68[1] = nullptr;
}

DrShdDataObj::~DrShdDataObj() {}

void DrShdDataObj::release() {}

void DrShdDataObj::setupShader(u32 index) { grlib::CGLibCtlShader::setShader(*this, *unknown68[index]); }

void DrShdDataObj::setupShader(DrResFetch *fetch) { grlib::CGLibCtlShader::setShader(*this, *fetch); }

void DrShdDataObj::setupComputeShader() { grlib::CGLibCtlShader::setComputeShader(*this); }

} // namespace ml

template class grlib::CGLibShdListBase<ml::DrShdDataObj>;

// clang-format off
#include "dr_shd_fetch_man.cpp"
#include "dr_shd_fetch_obj.cpp"
#include "dr_shd_lgt_man.cpp"
#include "dr_shd_lgt_obj.cpp"
#include "dr_shd_lgt_tile_based_dr.cpp"
#include "dr_shd_man.cpp"
#include "dr_shd_mdo_man.cpp"
#include "dr_shd_mdo_ext_tbl_obj.cpp"
#include "dr_shd_mdo_dec_ext_tbl.cpp"
#include "dr_shd_mdo_dec_res.cpp"
// clang-format on
