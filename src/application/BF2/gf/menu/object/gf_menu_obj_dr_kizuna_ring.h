#pragma once
#include <stddef.h>

#include "gf/data/gf_data_driver_skill.h"
#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "types.h"

namespace ui {
class UIObjectAcc;
} // namespace ui

namespace gf {

class GfMenuObjDrKizunaRing : public GfMenuObject {
public:
  // Inferred helper: number of unlocked skill levels of a driver ring, 0 to 3; original name unknown.
  static u32 unknown001(u32 driver, bool isHidden) {
    u32 level = 0;
    if (GfDataDriverSkill::isSkillLevelUnlock(driver, 1, isHidden)) {
      if (!GfDataDriverSkill::isSkillLevelUnlock(driver, 2, isHidden)) {
        level = 1;
      } else if (!GfDataDriverSkill::isSkillLevelUnlock(driver, 3, isHidden)) {
        level = 2;
      } else {
        level = 3;
      }
    }
    return level;
  }

  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle);
  static int setFadeOut(u32 handle);
  void initialize() override;
  void finalize() override;
  void update() override;
  static bool isLockPos(int index);
  static bool isScreenLR(u32 screen);
  static void setupCircle(ui::UIObjectAcc &, u32);
  bool seqCircleAnime();
  bool seqEndAnime();
  bool seqExecSkill();
  bool seqUnlockAnime();
  bool seqWait();

  u8 _24[0x68 - 0x24];
  GfMenuSequence<GfMenuObjDrKizunaRing, 8> unknown68; // Inferred role: skill learning steps; original member name unknown.
  int unknown2f8;                                     // Inferred role: step state; original member name unknown.
  u8 _2fc[0x318 - 0x2fc];
};

static_assert(offsetof(GfMenuObjDrKizunaRing, unknown68) == 0x68, "");
static_assert(offsetof(GfMenuObjDrKizunaRing, unknown2f8) == 0x2f8, "");
static_assert(sizeof(GfMenuObjDrKizunaRing) == 0x318, "");

} // namespace gf
