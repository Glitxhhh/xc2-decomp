#pragma once
#include "layer/layer_obj_font.h"
#include "types.h"

namespace layer {

class LayerShdManager;

class LayerObjTopFont : public LayerObjFont {
public:
  LayerObjTopFont();
  ~LayerObjTopFont() override;
  void applyPartsSetup() override;
  void applyParams(const LayerRenderView *view, const LayerResMatrix &matrix, const LayerResColor &color) override;
  void setDrawList(LayerSortMan *sortMan, bool is3D) override;
  void alphaRender();
  void lastRender();
  void finalRender();
  void unknown001(LayerShdManager *shader, s16 type);
};

} // namespace layer
