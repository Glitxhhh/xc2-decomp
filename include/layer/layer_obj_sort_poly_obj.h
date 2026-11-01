#pragma once
#include "layer/layer_sort_obj.h"

namespace layer {

class LayerObj;

class LayerObjSortPolyObj : public LayerSortObj {
public:
  LayerObjSortPolyObj(LayerObj *obj) : LayerSortObj(obj) {}
  void finalRender() override;
};

} // namespace layer
