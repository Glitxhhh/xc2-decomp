#pragma once
#include <stddef.h>

#include "dr/dr_pixl_post_obj.h"
#include "mm_math/mm_vec3.h"

namespace grlib {
class CGLibRenderTarget;
} // namespace grlib

namespace ml {

class DrPixlPostObjVolume : public DrPixlPostObj {
public:
  ~DrPixlPostObjVolume();
  void volumeRender();
  void resetColorBuff();
  void calcColorBuff();
  void update();
  void releaseColorBuff();
  void calculateSclDown();
  void calculateSclDown_Temporal();
  void calculateSclDown_NonTemporal();
  void calculateVolume();

  grlib::CGLibRenderTarget *unknown18[2]; // Inferred role: scale down targets; original member name unknown.
  grlib::CGLibRenderTarget *unknown28;    // Inferred role: render target; original member name unknown.
  mm::Vec3 unknown30;                     // Inferred role: pos; original member name unknown.
};

static_assert(offsetof(DrPixlPostObjVolume, unknown18) == 0x18, "");
static_assert(offsetof(DrPixlPostObjVolume, unknown28) == 0x28, "");
static_assert(offsetof(DrPixlPostObjVolume, unknown30) == 0x30, "");

} // namespace ml
