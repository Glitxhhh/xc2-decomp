#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "types.h"

namespace gf {

class GfMenuObjPopup : public GfMenuObject {
public:
  static void pausePickup();
  static void continuePickup(u32 type);
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle, u32 type);
  static int setFadeOut(u32 handle, u32 type);
  void initialize() override;
  void finalize() override;
  void update() override;
  static void closeAll();

  u8 _24[0x60 - 0x24];
  GfMenuSequence<GfMenuObjPopup, 8> unknown60; // Inferred role: popup steps; original member name unknown.
};

static_assert(offsetof(GfMenuObjPopup, unknown60) == 0x60, "");
static_assert(sizeof(GfMenuObjPopup) == 0x2f0, "");

} // namespace gf
