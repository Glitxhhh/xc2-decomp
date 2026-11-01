#pragma once
#include <stddef.h>

#include "types.h"

namespace layer {

// Evidence: LayerAccLayoutObj::setViewPort writes four floats at LayerObjLayout+0x2b0, which
// LayerObjTopLayout::updateEndLayout passes to LayerObjUtil::calcLayerRenderView as a LayerViewPort.
struct LayerViewPort {
  f32 unknown00; // Inferred role: x; original member name unknown.
  f32 unknown04; // Inferred role: y; original member name unknown.
  f32 unknown08; // Inferred role: width; original member name unknown.
  f32 unknown0c; // Inferred role: height; original member name unknown.
};

static_assert(offsetof(LayerViewPort, unknown0c) == 0x0c, "");
static_assert(sizeof(LayerViewPort) == 0x10, "");

} // namespace layer
