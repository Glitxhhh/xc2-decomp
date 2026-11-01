#pragma once
#include <stddef.h>

#include "types.h"

namespace gf {

// Layout evidence: the constructors of GfFieldLocalSteer (0x710033f554) and GfFieldMoveSpeed (0x710034141c) store the
// TGfTween<float> vtable and initialize the members at 0x10 and 0x14 with 0.5 and 0.
template <typename T> class TGfTween {
public:
  TGfTween() : unknown10(0.5f), unknown14(0.0f) {}
  virtual ~TGfTween() {}

  T unknown08;   // Inferred role: start value; original member name unknown.
  T unknown0c;   // Inferred role: end value; original member name unknown.
  f32 unknown10; // Role and original member name unknown.
  f32 unknown14; // Role and original member name unknown.
};

// Layout evidence: the GfEnemyFieldMoveSpeed constructor (0x710034171c) stores the GfSpeedTween vtable and 0, 1, 0 and 0.5 in
// the members at 0x08 to 0x14.
class GfSpeedTween : public TGfTween<f32> {
public:
  GfSpeedTween() {
    unknown08 = 0.0f;
    unknown0c = 1.0f;
    unknown10 = 0.0f;
    unknown14 = 0.5f;
  }
  ~GfSpeedTween() override {}
};

static_assert(offsetof(GfSpeedTween, unknown08) == 0x08, "");
static_assert(offsetof(GfSpeedTween, unknown14) == 0x14, "");
static_assert(sizeof(GfSpeedTween) == 0x18, "");

} // namespace gf
