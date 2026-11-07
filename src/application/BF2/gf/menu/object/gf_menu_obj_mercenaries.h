#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "types.h"

namespace ui {
class UIObjectAcc;
} // namespace ui

namespace gf {

class GfMenuObjMercenaries : public GfMenuObject {
public:
  static void setupLocationSelect(ui::UIObjectAcc &acc);
  static void setupLocationZone(ui::UIObjectAcc &acc, u16 zone);
  static void setupMission(ui::UIObjectAcc &acc);
  static void setupMercenaries(ui::UIObjectAcc &acc);
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle);
  static int setFadeOut(u32 handle);
  void initialize() override;
  void finalize() override;
  void update() override;
  bool seqRewardStart();
  bool seqRewardStart2();
  bool seqRewardStart3();
  bool seqRewardComp();
  bool seqRewardComp2();
  bool seqRewardComp3();
  bool seqRewardComp4();
  bool seqRewardComp5();

  u8 _24[0xe8 - 0x24];
  GfMenuSequence<GfMenuObjMercenaries, 8> unknown0e8; // Inferred role: queued steps; original member name unknown.
  int unknown378;                                     // Inferred role: control of the reward screen steps; original member name unknown.
};

static_assert(offsetof(GfMenuObjMercenaries, unknown378) == 0x378, "");

} // namespace gf
