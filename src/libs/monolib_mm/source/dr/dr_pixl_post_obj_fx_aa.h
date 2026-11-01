#pragma once
#include <stddef.h>

#include "dr/dr_pixl_post_obj.h"
#include "types.h"

namespace grlib {
class CGLibRenderTarget;
} // namespace grlib

namespace ml {

class DrPixlPostObjFxAA : public DrPixlPostObj {
public:
  ~DrPixlPostObjFxAA();
  void releaseColorBuff();
  void update();
  void resetColorBuff();
  void render();
  void calcScale();
  void calcLuminosity();

  grlib::CGLibRenderTarget *unknown18; // Inferred role: render target; original member name unknown.
  f32 unknown20;                       // Inferred role: screen width; original member name unknown.
  f32 unknown24;                       // Inferred role: screen height; original member name unknown.
};

static_assert(offsetof(DrPixlPostObjFxAA, unknown18) == 0x18, "");
static_assert(offsetof(DrPixlPostObjFxAA, unknown20) == 0x20, "");
static_assert(offsetof(DrPixlPostObjFxAA, unknown24) == 0x24, "");

} // namespace ml
