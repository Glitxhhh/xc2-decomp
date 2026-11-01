#include "dr/dr_pixl_post_obj_tone_map.h"

#include "dr/dr_man.h"

namespace ml {

void DrPixlPostObjToneMap::update() {
  if (unknown00->unknown058()) {
    return;
  }
  if ((unknownb4 & 0x10) != 0) {
    updateByCompute();
  } else {
    updateByRenderTarget();
  }
}

} // namespace ml
