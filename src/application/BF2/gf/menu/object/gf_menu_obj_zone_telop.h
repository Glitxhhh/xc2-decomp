#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuCallContext;

class GfMenuObjZoneTelop : public GfMenuObject {
public:
  void initialize() override;
  void finalize() override;
  static void open(GfMenuCallContext *context, u16 zone);
  static void close(f32 wait);
  bool seqFadeIn();
  bool seqFadeOut();

  u8 _24[0x188 - 0x24];
  bool unknown188; // Inferred role: fade control started flag; original member name unknown.
  f32 unknown18c;  // Inferred role: fade out time; original member name unknown.
};

static_assert(offsetof(GfMenuObjZoneTelop, unknown188) == 0x188, "");
static_assert(offsetof(GfMenuObjZoneTelop, unknown18c) == 0x18c, "");

} // namespace gf
