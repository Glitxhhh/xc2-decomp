#pragma once
#include "layer/layer_sort_obj.h"

namespace layer {

class LayerObj;

class LayerObjSortTexObj : public LayerSortObj {
public:
  LayerObjSortTexObj(LayerObj *obj) : LayerSortObj(obj) {}
  void finalRender() override;
};

} // namespace layer
