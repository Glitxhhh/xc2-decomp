#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "types.h"

namespace ui {
class UIObjectAcc;
} // namespace ui

namespace gf {

class GfMenuObjDrArtsSet2 : public GfMenuObject {
public:
  static void moveRight(ui::UIObjectAcc &acc);
  static void moveLeft(ui::UIObjectAcc &acc);
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle, u32 dir, const char *child);
  static int setFadeOut(u32 handle, u32 dir, const char *child);
  static void setFadeInBG(u32 handle);
  static void setFadeOutBG(u32 handle);
  void initialize() override;
  void finalize() override;
  void update() override;

  u8 _24[0xf8 - 0x24];
  GfMenuSequence<GfMenuObjDrArtsSet2, 4> unknown0f8; // Inferred role: queued steps; original member name unknown.
};

static_assert(offsetof(GfMenuObjDrArtsSet2, unknown0f8) == 0xf8, "");

} // namespace gf
