#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "types.h"

namespace gf {

class GfMenuObjPouch2 : public GfMenuObject {
public:
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle, u32 type);
  static int setFadeOut(u32 handle, u32 type);
  void initialize() override;
  void finalize() override;
  void update() override;

  u8 _24[0x130 - 0x24];
  GfMenuSequence<GfMenuObjPouch2, 8> unknown130; // Inferred role: queued steps; original member name unknown.
};

static_assert(offsetof(GfMenuObjPouch2, unknown130) == 0x130, "");

} // namespace gf
