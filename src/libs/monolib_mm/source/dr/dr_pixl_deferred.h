#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {

class DrMan;
class DrPixlMan;
class DrPixlRenderTarget;

class DrPixlDeferred {
public:
  void displayUpdate();
  void globalIBLRender();
  void lastDeferredRender();
  void fastDeferredRender(int cate);
  void shadowTexRender(int cate);
  void debugRender();
  grlib::CGLibTextureBuffer *getShadowMapTexture() const;
  void shadowBuffBegin();
  void shadowBuffClear();
  void releaseColorBuff();
  void lgtCalcRender();
  DrPixlRenderTarget *getTemporalInputShadowMap();
  DrPixlRenderTarget *getTemporalOutputShadowMap();
  DrPixlRenderTarget *getTemporalOutputShadowMap() const;
  DrPixlRenderTarget *getTemporalHistoryShadowMap();

  u8 _00[0x08];
  DrMan *unknown08; // Inferred role: driver manager; original member name unknown.
  u8 _10[0x18 - 0x10];
  DrPixlMan *unknown18; // Inferred role: pixl man; original member name unknown.
  DrPixlRenderTarget *m_temporalInputShadowMap;
  DrPixlRenderTarget *unknown28[2]; // Inferred role: temporal shadow buffers; original member name unknown.
  s32 unknown38;                    // Inferred role: temporal shadow state; original member name unknown.
};

static_assert(offsetof(DrPixlDeferred, unknown08) == 0x08, "");
static_assert(offsetof(DrPixlDeferred, unknown18) == 0x18, "");
static_assert(offsetof(DrPixlDeferred, m_temporalInputShadowMap) == 0x20, "");
static_assert(offsetof(DrPixlDeferred, unknown28) == 0x28, "");
static_assert(offsetof(DrPixlDeferred, unknown38) == 0x38, "");

} // namespace ml
