#include "layer/layer_obj_top_font.h"

#include "layer/layer_base.h"
#include "layer/layer_manager.h"
#include "layer/layer_obj_manager.h"
#include "layer/layer_sort_man.h"

namespace layer {

LayerObjTopFont::LayerObjTopFont() {
  unknown18 = LAYER_OBJ_TYPE_FONT;
  unknowna8 |= 0x20000;
}

LayerObjTopFont::~LayerObjTopFont() {
  baseRelease();
  workRelease();
}

void LayerObjTopFont::applyParams(const LayerRenderView *view, const LayerResMatrix &matrix, const LayerResColor &color) { updateShaderParms(view, matrix, color); }

void LayerObjTopFont::setDrawList(LayerSortMan *sortMan, bool is3D) {
  if ((unknowna8 & 0x90000) || unknown250 == nullptr) {
    return;
  }
  if (is3D) {
    if (unknowna8 & 0x400) {
      LayerManager::get()->unknown60->unknown10->set3DSpace(unknown250->unknown38, unknown200);
    } else if (!isClip()) {
      sortMan->set2DSpace(unknown250->unknown38, unknownc0);
    }
  } else if (!isClip()) {
    sortMan->set2DSpace(unknown250->unknown38, unknownc0);
  }
}

void LayerObjTopFont::alphaRender() {}

void LayerObjTopFont::lastRender() {}

} // namespace layer
