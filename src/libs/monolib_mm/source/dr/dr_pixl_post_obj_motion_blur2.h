#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibVtxVertex;
} // namespace grlib

namespace ml {
class DrMan;
class DrPixlMan;
class DrPixlPostMan;
class DrPixlRenderTarget;

class DrPixlPostObjMotionBlur2 {
public:
  DrPixlPostObjMotionBlur2(DrMan *drMan, DrPixlMan *pixlMan, DrPixlPostMan *postMan);
  ~DrPixlPostObjMotionBlur2();
  void resetColorBuff();
  void calcBludBuffColorBuff();
  void update();
  void render();
  void calcBlurWork();
  void calcObjMotionBlur();
  void renderCalcBlur();
  void lastRender();
  void calcVelocityBlur();
  void calcMaxVelocityPerTile();
  void calcBlurMask();
  void releaseColorBuff();

  DrMan *unknown00; // Inferred role: driver manager; original member name unknown.
  u8 _08[0x20 - 0x08];
  DrPixlRenderTarget *unknown20;    // Inferred role: render target; original member name unknown.
  DrPixlRenderTarget *unknown28;    // Inferred role: render target; original member name unknown.
  DrPixlRenderTarget *unknown30;    // Inferred role: render target; original member name unknown.
  DrPixlRenderTarget *unknown38;    // Inferred role: render target; original member name unknown.
  DrPixlRenderTarget *unknown40;    // Inferred role: render target; original member name unknown.
  DrPixlRenderTarget *unknown48;    // Inferred role: render target; original member name unknown.
  grlib::CGLibVtxVertex *unknown50; // Inferred role: vertex; original member name unknown.
  grlib::CGLibVtxVertex *unknown58; // Inferred role: vertex; original member name unknown.
  u8 _60[0x64 - 0x60];
  bool unknown64; // Inferred role: blur enable; original member name unknown.
  u8 _65[0x68 - 0x65];
};

static_assert(offsetof(DrPixlPostObjMotionBlur2, unknown20) == 0x20, "");
static_assert(offsetof(DrPixlPostObjMotionBlur2, unknown48) == 0x48, "");
static_assert(offsetof(DrPixlPostObjMotionBlur2, unknown58) == 0x58, "");
static_assert(offsetof(DrPixlPostObjMotionBlur2, unknown64) == 0x64, "");
static_assert(sizeof(DrPixlPostObjMotionBlur2) == 0x68, "");

} // namespace ml
