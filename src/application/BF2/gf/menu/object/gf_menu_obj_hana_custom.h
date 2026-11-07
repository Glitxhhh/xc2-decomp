#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "types.h"

namespace ui {
class UIObjectAcc;
} // namespace ui

namespace gf {

class GfMenuObjHanaCustom : public GfMenuObject {
public:
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle, u32 unknown);
  static int setFadeOut(u32 handle, u32 unknown);
  void initialize() override;
  void finalize() override;
  void update() override;
  static u32 convPartsId(u32 partsId);
  static bool isExpandParts(u32 partsId);
  static void refreshPlanLine(ui::UIObjectAcc &);

  u8 _24[0xa8 - 0x24];
  GfMenuSequence<GfMenuObjHanaCustom, 8> unknown0a8; // Inferred role: queued steps; original member name unknown.
};

static_assert(offsetof(GfMenuObjHanaCustom, unknown0a8) == 0xa8, "");

} // namespace gf
