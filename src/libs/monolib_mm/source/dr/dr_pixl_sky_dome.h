#pragma once

#include <stddef.h>

#include "types.h"

namespace mm {
struct Vec4;
} // namespace mm

namespace ml {

class DrMan;
class DrResUseQueryObj;

class DrPixlSkyDome {
public:
  ~DrPixlSkyDome();
  void update();
  void luminanceRender();
  void baseRender();
  void godRayRender();
  void updateUniform();
  void renderColorBackground(const mm::Vec4 &color);
  void renderBackgroundCube();

  DrMan *unknown00;            // Inferred role: dr man; original member name unknown.
  DrResUseQueryObj *unknown08; // Inferred role: occlusion query; original member name unknown.
  f32 unknown10;               // Inferred role: sky visibility; original member name unknown.
  s32 unknown14;               // Inferred role: visibility reset frames; original member name unknown.
};

static_assert(offsetof(DrPixlSkyDome, unknown00) == 0x00, "");
static_assert(offsetof(DrPixlSkyDome, unknown08) == 0x08, "");
static_assert(offsetof(DrPixlSkyDome, unknown10) == 0x10, "");
static_assert(offsetof(DrPixlSkyDome, unknown14) == 0x14, "");

} // namespace ml
