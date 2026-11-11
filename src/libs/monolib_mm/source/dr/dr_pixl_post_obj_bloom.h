#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibRenderTarget;
} // namespace grlib

namespace ml {

class DrMan;

class DrPixlPostObjBloom {
public:
  enum DownScaleType {
    DOWN_SCALE_TYPE_UNKNOWN_0 = 0,
    DOWN_SCALE_TYPE_UNKNOWN_1 = 1,
    DOWN_SCALE_TYPE_UNKNOWN_2 = 2,
  };

  static f32 BLOOMTEX_SCALE;
  static const f32 BLOOMTEX_SCALE_OLD; // Name from the game symbol _ZN2ml18DrPixlPostObjBloom18BLOOMTEX_SCALE_OLDE; also in torna and xc1de.
  static const f32 BLOOMTEX_SCALE_NEW; // Name from the game symbol _ZN2ml18DrPixlPostObjBloom18BLOOMTEX_SCALE_NEWE; also in torna and xc1de.

  ~DrPixlPostObjBloom();
  void resetColorBuff(bool isForce);
  void releaseBloomTexture();
  void update();
  void calcRender();
  void releaseColorBuff(bool isForce);
  grlib::CGLibRenderTarget *getLgtDownTarget();
  void calculateDownScale();
  void calculateDownScale_TwoPass();
  void calculateGaussBlur();
  void calculateDownScaleImpl(DownScaleType type);

  DrMan *unknown00; // Inferred role: driver manager; original member name unknown.
  u8 _08[0x18 - 0x08];
  grlib::CGLibRenderTarget *unknown18; // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown20; // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown28; // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown30; // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown38; // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown40; // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown48; // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown50; // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown58; // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown60; // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown68; // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown70; // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown78; // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget *unknown80; // Inferred role: render target; original member name unknown.
  u8 _88[0x90 - 0x88];
  u32 unknown90; // Inferred role: update request; original member name unknown.
  u32 unknown94; // Inferred role: flags; original member name unknown.
  grlib::CGLibRenderTarget *m_lgtDownTarget[2];
  s32 unknowna8; // Inferred role: bloom scale type; original member name unknown.
};

static_assert(offsetof(DrPixlPostObjBloom, unknown18) == 0x18, "");
static_assert(offsetof(DrPixlPostObjBloom, unknown80) == 0x80, "");
static_assert(offsetof(DrPixlPostObjBloom, unknown90) == 0x90, "");
static_assert(offsetof(DrPixlPostObjBloom, m_lgtDownTarget) == 0x98, "");
static_assert(offsetof(DrPixlPostObjBloom, unknown94) == 0x94, "");
static_assert(offsetof(DrPixlPostObjBloom, unknowna8) == 0xa8, "");

} // namespace ml
