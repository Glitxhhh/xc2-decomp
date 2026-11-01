#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibRenderTarget;
} // namespace grlib

namespace ml {
class DrMan;
class DrPixlMan;
class DrPixlPostMan;

class DrPixlPostObjDepthofField {
public:
  DrPixlPostObjDepthofField(DrMan *drMan, DrPixlMan *pixlMan, DrPixlPostMan *postMan);
  ~DrPixlPostObjDepthofField();
  void releaseColorBuff();

  u8 _00[0x18 - 0x00];
  grlib::CGLibRenderTarget *unknown18; // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown20; // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown28; // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown30; // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown38; // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown40; // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown48; // Inferred role: render target; original member name unknown.
  u8 _50[0xc0 - 0x50];
};

static_assert(offsetof(DrPixlPostObjDepthofField, unknown18) == 0x18, "");
static_assert(offsetof(DrPixlPostObjDepthofField, unknown38) == 0x38, "");
static_assert(offsetof(DrPixlPostObjDepthofField, unknown40) == 0x40, "");
static_assert(offsetof(DrPixlPostObjDepthofField, unknown48) == 0x48, "");
static_assert(sizeof(DrPixlPostObjDepthofField) == 0xc0, "");

} // namespace ml
