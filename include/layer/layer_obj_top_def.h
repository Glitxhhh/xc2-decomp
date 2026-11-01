#pragma once
#include <stddef.h>

#include "layer/layer_obj_sort_def.h"
#include "layer/layer_obj_work.h"

namespace layer {

class LayerObjTopDef : public LayerObjWork {
public:
  LayerObjTopDef(const char *name);
  LayerObjTopDef(const void *data);
  ~LayerObjTopDef() override;
  void workIconCreate();
  void setDrawList(LayerSortMan *sortMan, bool is3D) override;
  void updateResCheck();
  void alphaRender();
  void lastRender();
  void finalRender();

  LayerObjSortDef unknown308; // Inferred role: sort object; original member name unknown.
};

static_assert(offsetof(LayerObjTopDef, unknown308) == 0x308, "");

} // namespace layer
