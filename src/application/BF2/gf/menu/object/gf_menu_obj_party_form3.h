#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "types.h"

namespace ui {
class UIObjectAcc;
} // namespace ui

namespace gf {

class GfMenuObjPartyForm3 : public GfMenuObject {
public:
  bool seqWaitOpenEnd();
  struct OpenParam {
    u16 unknown00; // Role and original member name unknown.
  };

  static void registOpenParam(const OpenParam &param);
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle);
  static int setFadeOut(u32 handle);
  void initialize() override;
  void finalize() override;
  void update() override;
  static void setupBGLayout(ui::UIObjectAcc &, u32, bool);

  u8 _24[0x80 - 0x24];
  GfMenuSequence<GfMenuObjPartyForm3, 8> unknown80; // Inferred role: queued steps; original member name unknown.
};

static_assert(offsetof(GfMenuObjPartyForm3, unknown80) == 0x80, "");

} // namespace gf
