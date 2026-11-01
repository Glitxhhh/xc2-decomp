#pragma once
#include "layer/layer_obj_font.h"

namespace layer {

class LayerObjTopFont : public LayerObjFont {
public:
  LayerObjTopFont();
  ~LayerObjTopFont() override;
  void applyParams(const LayerRenderView *view, const LayerResMatrix &matrix, const LayerResColor &color) override;
  void setDrawList(LayerSortMan *sortMan, bool is3D) override;
  void alphaRender();
  void lastRender();
  void finalRender();
};

} // namespace layer
