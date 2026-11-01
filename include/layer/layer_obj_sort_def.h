#pragma once
#include "layer/layer_sort_obj.h"

namespace layer {

class LayerObj;

class LayerObjSortDef : public LayerSortObj {
public:
  LayerObjSortDef(LayerObj *obj) : LayerSortObj(obj) {}
  void finalRender() override;
};

} // namespace layer
