#include "layer/layer_obj_top_mem_obj.h"

#include <string.h>

#include "grlib/cglib_texture_buffer.h"
#include "layer/layer_base.h"
#include "layer/layer_manager.h"
#include "layer/layer_obj_util.h"
#include "layer/layer_render_view.h"
#include "layer/layer_shd_manager.h"
#include "layer/layer_sort_man.h"
#include "mm_math/mm_col4.h"

namespace layer {

LayerObjTopMemObj::LayerObjTopMemObj(u32 width, u32 height, LayerMemType type) : unknown258(this) {
  unknowna8 |= 0x20000;
  unknown740 = width;
  unknown744 = height;
  unknown748 = 0;
  unknown74c = 0;
  unknown750 = type;
  unknown18 = LAYER_OBJ_TYPE_MEM;
  unknown250 = nullptr;
  unknown238 = nullptr;
  unknown270 = 0xc;
  createWorkBuffer();
}

void LayerObjTopMemObj::createWorkBuffer() {
  unknown640.setup(0x80);
  unknown180.unknown08 = 1.0f;
  unknown180.unknown0c = static_cast<f32>(unknown744) / static_cast<f32>(unknown740);
  if (unknown740 > unknown744) {
    unknown180.unknown00 = 1.0f;
    unknown180.unknown04 = static_cast<f32>(unknown744) / static_cast<f32>(unknown740);
  } else {
    unknown180.unknown00 = static_cast<f32>(unknown740) / static_cast<f32>(unknown744);
    unknown180.unknown04 = 1.0f;
  }
  unknown180.unknown10 = 0;
  unknown180.unknown12 = 0;
  unknown180.unknown14 = unknown740;
  unknown180.unknown16 = unknown744;
  u32 size;
  if (unknown750 == LAYER_MEM_TYPE_UNKNOWN_2) {
    size = 2 * unknown740 * unknown744;
  } else {
    size = unknown740 * unknown744;
    if (unknown750 == LAYER_MEM_TYPE_UNKNOWN_3) {
      unknown748 = size + (0x100 - size % 0x100) % 0x100;
      u32 secondSize = (unknown740 >> 1) * (unknown744 >> 1) * 2;
      unknown74c = secondSize + (0x10 - secondSize % 0x10) % 0x10;
      size = unknown748 + unknown74c;
    } else {
      size *= 3;
    }
  }
  size += (0x10 - size % 0x10) % 0x10;
  unknown6a0[0].setup(size);
  unknown6a0[1].setup(size);
  unknown678.setup(0x10);
  unknown6f0[0].setup(0x10);
  memset(unknown6f0[0].m_mapping, 0, 0x10);
  unknown6f0[1].setup(0x10);
  memset(unknown6f0[1].m_mapping, 0, 0x10);
}

LayerObjTopMemObj::~LayerObjTopMemObj() {
  baseRelease();
  releaseWorkBuffer();
}

void LayerObjTopMemObj::releaseWorkBuffer() {
  unknown278.release();
  unknown640.release();
  unknown678.release();
  unknown6a0[0].release();
  unknown6a0[1].release();
  unknown6f0[0].release();
  unknown6f0[1].release();
}

void LayerObjTopMemObj::resourceInit() {
  if (unknown270 & 0x8) {
    unknown270 &= ~0x8;
    unknown278.setTextureInfo(unknown740, unknown744, GRL_SURFACE_FORMAT_RGBA8, false, 0);
    unknown278.clearTexture(mm::Col4(0.0f, 0.0f, 0.0f, 0.0f), static_cast<GrlClaerMask>(0xf));
    u32 *info = static_cast<u32 *>(unknown678.m_mapping);
    info[0] = unknown740;
    info[1] = unknown744;
    if (unknown750 == LAYER_MEM_TYPE_UNKNOWN_3) {
      info[2] = unknown740 >> 1;
      info[3] = unknown744 >> 1;
    } else {
      info[2] = unknown740;
      info[3] = unknown744;
    }
    unknown678.updateData();
  }
}

void *LayerObjTopMemObj::getBuffer() { return unknown6a0[static_cast<u32>(LayerManager::s_nDebIdx)].m_mapping; }

void LayerObjTopMemObj::updateBufer() {
  u32 index = LayerManager::s_nDebIdx;
  memset(unknown6f0[index].m_mapping, 0, 0x10);
  unknown6f0[index].updateData();
  unknown6a0[index].updateData();
}

void LayerObjTopMemObj::setRender(bool render) {
  if (render) {
    unknown270 |= 0x4;
  } else {
    unknown270 &= ~0x4;
  }
}

bool LayerObjTopMemObj::isRender() const { return (unknown270 >> 2) & 0x1; }

void LayerObjTopMemObj::applyParams(const LayerRenderView *view, const LayerResMatrix &matrix, const LayerResColor &color) {
  unknown250 = view->unknown08;
  unknown170.unknown001();
  LayerObjUtil::calcDispInfo(unknown170, matrix, unknown180);
  if (unknowna8 & 0x90000) {
    return;
  }
  updateDefUniformBlock(unknown640, matrix, color, nullptr);
}

void LayerObjTopMemObj::setDrawList(LayerSortMan *sortMan, bool is3D) {
  if (unknowna8 & 0x90000) {
    return;
  }
  if (is3D) {
    if (unknowna8 & 0x400) {
      LayerManager::get()->unknown60->unknown10->set3DSpace(&unknown258, unknown200);
    } else if (!isClip()) {
      sortMan->set2DSpace(&unknown258, unknownc0);
    }
  } else if (!isClip()) {
    sortMan->set2DSpace(&unknown258, unknownc0);
  }
}

void LayerObjTopMemObj::lastRender() {
  LayerShdManager *shader = LayerManager::get()->unknown58;
  if (!shader->unknown002(unknown248, unknown250)) {
    return;
  }
  shader->unknown003(LayerShdManager::s_resDefBlend[unknownc5]);
  shader->unknown004(this);
  shader->unknown4f2 = 1;
  shader->setSecTexture(unknown220[2]);
  shader->setupVertex(static_cast<LayerDefVertType>(1));
  shader->unknown4f0 = 1;
  shader->setupShader(&unknown640);
  shader->setupTexture(*unknown278.unknown70, static_cast<LayerSamplerType>(unknownc6), 0);
  shader->renderQuadsIndex();
}

void LayerObjTopMemObj::finalRender() {
  setupRender();
  if (isRender()) {
    lastRender();
  }
}

} // namespace layer
