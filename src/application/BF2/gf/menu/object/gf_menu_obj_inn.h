#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "types.h"

namespace gf {

class GfMenuObjInn : public GfMenuObject {
public:
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle);
  static int setFadeOut(u32 handle);
  void initialize() override;
  void finalize() override;
  bool seqFadeOut();
  bool seqFadeOutWait();
  void update() override;

  u8 _24[0xa0 - 0x24];
  GfMenuSequence<GfMenuObjInn, 8> unknown0a0; // Inferred role: queued steps; original member name unknown.
};

static_assert(offsetof(GfMenuObjInn, unknown0a0) == 0xa0, "");

} // namespace gf
