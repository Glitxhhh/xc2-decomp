#pragma once
#include "layer/layer_sort_obj.h"

namespace layer {
class LayerObj;

class LayerObjSortFont : public LayerSortObj {
public:
  LayerObjSortFont(LayerObj *obj) : LayerSortObj(obj) {}
  void finalRender() override;
};

} // namespace layer
