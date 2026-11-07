#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "types.h"

namespace ui {
class UIObjectAcc;
} // namespace ui

namespace gf {
class GfMenuCallContext;

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
  void refreshRemoveAddOperation(u32 handle, int index);
  bool seqAnnounceChange();

  u8 _24[0x34 - 0x24];
  u32 unknown34; // Inferred role: party member count; original member name unknown.
  u8 _38[0x40 - 0x38];
  int unknown40; // Inferred role: pending slot, -1 when none; original member name unknown.
  u8 _44[0x80 - 0x44];
  GfMenuSequence<GfMenuObjPartyForm3, 8> unknown80; // Inferred role: queued steps; original member name unknown.
  GfMenuCallContext *unknown310;                    // Inferred role: announce call context; original member name unknown.
  bool unknown318;                                  // Inferred role: unused; original member name unknown.
};

static_assert(offsetof(GfMenuObjPartyForm3, unknown34) == 0x34, "");
static_assert(offsetof(GfMenuObjPartyForm3, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjPartyForm3, unknown80) == 0x80, "");
static_assert(offsetof(GfMenuObjPartyForm3, unknown310) == 0x310, "");
static_assert(offsetof(GfMenuObjPartyForm3, unknown318) == 0x318, "");

} // namespace gf
