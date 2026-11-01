#pragma once
#include <stddef.h>

#include "types.h"

namespace mm {
struct Vec4;
} // namespace mm

namespace grlib {
class CGLibRenderTarget;
} // namespace grlib

namespace ml {

class DrMan;
class DrPixlPostMan;
class DrPixlRenderTarget;

class DrPixlPostObjTSSAO {
public:
  enum BlurAxis {
    BLUR_AXIS_UNKNOWN_1 = 1,
    BLUR_AXIS_UNKNOWN_2 = 2,
  };

  void render_beforeTemporal();
  void passQuaterNormal();
  void passSSAO();
  void passPrevBlur();
  void passTemporalFiltering();
  void render_afterTemporal();
  void passPostBlur();
  void passUpScaling();
  void passBlur_Sub(BlurAxis axis, f32 strength, DrPixlRenderTarget *source, DrPixlRenderTarget *destination, bool flag);
  void passUpScaleToMiddle();
  void update();
  void releaseColorBuff();
  void calcFragCoordToUV(mm::Vec4 &uv, f32 width, f32 height);
  void calcFragCoordToScreen(mm::Vec4 &screen, f32 width, f32 height);

  DrMan *unknown00; // Inferred role: driver manager; original member name unknown.
  u8 _08[0x10 - 0x08];
  DrPixlPostMan *unknown10; // Inferred role: post man; original member name unknown.
  u8 _18[0x20 - 0x18];
  DrPixlRenderTarget *unknown20;    // Inferred role: render target; original member name unknown.
  DrPixlRenderTarget *unknown28[2]; // Inferred role: render targets per buffer; original member name unknown.
  DrPixlRenderTarget *unknown38;    // Inferred role: render target; original member name unknown.
  u8 _40[0x48 - 0x40];
  grlib::CGLibRenderTarget *unknown48;    // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown50[2]; // Inferred role: render targets per buffer; original member name unknown.
  grlib::CGLibRenderTarget *unknown60;    // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown68;    // Inferred role: render target; original member name unknown.
  s32 unknown70;                          // Inferred role: scale; original member name unknown.
};

static_assert(offsetof(DrPixlPostObjTSSAO, unknown10) == 0x10, "");
static_assert(offsetof(DrPixlPostObjTSSAO, unknown20) == 0x20, "");
static_assert(offsetof(DrPixlPostObjTSSAO, unknown28) == 0x28, "");
static_assert(offsetof(DrPixlPostObjTSSAO, unknown38) == 0x38, "");
static_assert(offsetof(DrPixlPostObjTSSAO, unknown48) == 0x48, "");
static_assert(offsetof(DrPixlPostObjTSSAO, unknown50) == 0x50, "");
static_assert(offsetof(DrPixlPostObjTSSAO, unknown60) == 0x60, "");
static_assert(offsetof(DrPixlPostObjTSSAO, unknown70) == 0x70, "");

} // namespace ml
