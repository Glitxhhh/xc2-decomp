#pragma once

#include <stddef.h>

namespace mm {
struct Vec4;
} // namespace mm

namespace ml {

class DrMan;
class DrResUseQueryObj;

class DrPixlSkyDome {
public:
  ~DrPixlSkyDome();
  void luminanceRender();
  void baseRender();
  void godRayRender();
  void renderColorBackground(const mm::Vec4 &color);
  void renderBackgroundCube();

  DrMan *unknown00;            // Inferred role: dr man; original member name unknown.
  DrResUseQueryObj *unknown08; // Inferred role: occlusion query; original member name unknown.
};

static_assert(offsetof(DrPixlSkyDome, unknown00) == 0x00, "");
static_assert(offsetof(DrPixlSkyDome, unknown08) == 0x08, "");

} // namespace ml
