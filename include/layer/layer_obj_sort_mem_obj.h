#pragma once
#include "layer/layer_sort_obj.h"

namespace layer {

class LayerObj;

class LayerObjSortMemObj : public LayerSortObj {
public:
  LayerObjSortMemObj(LayerObj *obj) : LayerSortObj(obj) {}
  void finalRender() override;
};

} // namespace layer
