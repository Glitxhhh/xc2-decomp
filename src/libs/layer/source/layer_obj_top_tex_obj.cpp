#include "layer/layer_obj_top_tex_obj.h"

#include "grlib/cglib_texture_buffer.h"
#include "layer/layer_manager.h"
#include "layer/layer_obj_manager.h"
#include "layer/layer_obj_util.h"
#include "layer/layer_render_view.h"
#include "layer/layer_shd_manager.h"
#include "layer/layer_sort_man.h"
#include "types.h"

namespace layer {

void LayerObjTopTexObj::finalRender() {
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
  shader->setupShader(&unknown278);
  shader->setupTexture(*unknown270, static_cast<LayerSamplerType>(unknownc6), 0);
  shader->renderQuadsIndex();
}

LayerObjTopTexObj::~LayerObjTopTexObj() {
  baseRelease();
  releaseWorkBuffer();
}

void LayerObjTopTexObj::createWorkBuffer() {
  unknown278.setup(0x80);
  u32 width = 0x40;
  u32 height = 0x40;
  if (unknown270->isInitialized()) {
    width = unknown270->getWidth();
    height = unknown270->getHeight();
  }
  unknown005(width, height);
}

void LayerObjTopTexObj::releaseWorkBuffer() { unknown278.release(); }

void LayerObjTopTexObj::applyParams(const LayerRenderView *view, const LayerResMatrix &matrix, const LayerResColor &color) {
  unknown250 = view->unknown08;
  unknown170.unknown001();
  LayerObjUtil::calcDispInfo(unknown170, matrix, unknown180);
  if (unknowna8 & 0x90000) {
    return;
  }
  updateDefUniformBlock(unknown278, matrix, color, nullptr);
}

void LayerObjTopTexObj::setDrawList(LayerSortMan *sortMan, bool is3D) {
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

} // namespace layer
