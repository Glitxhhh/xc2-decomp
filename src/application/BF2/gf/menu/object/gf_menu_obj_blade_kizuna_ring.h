#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace ui {
class UIObjectAcc;
} // namespace ui

namespace gf {

class GfMenuObjBladeKizunaRing : public GfMenuObject {
public:
  struct Achievement {
    Achievement(u16 line, u16 level, u16 state) : unknown00(line), unknown02(level), unknown04(state) {}

    u16 unknown00; // Inferred role: achievement line; original member name unknown.
    u16 unknown02; // Inferred role: achievement level; original member name unknown.
    u16 unknown04; // Inferred role: release state, 1 to order and 3 to release; original member name unknown.
  };

  static void close();
  static void open();
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle);
  static int setFadeOut(u32 handle);
  static void setupName(ui::UIObjectAcc &acc);
  static int getAchievementList(mm::mtl::FixedVector<Achievement, 50> &list);
  void initialize() override;
  void finalize() override;
  void update() override;
  bool seqComplete();

  u8 _24[0x48 - 0x24];
  int unknown48; // Inferred role: control id of the achievement icon; original member name unknown.
  int unknown4c; // Inferred role: completion state, 1 to start the next icon and 2 to wait for it; original member name unknown.
  u8 _50[0x58 - 0x50];
  mm::mtl::FixedVector<Achievement, 50> unknown58;        // Inferred role: achievements to complete; original member name unknown.
  GfMenuSequence<GfMenuObjBladeKizunaRing, 8> unknown190; // Inferred role: steps; original member name unknown.
};

static_assert(sizeof(GfMenuObjBladeKizunaRing::Achievement) == 6, "");
static_assert(offsetof(GfMenuObjBladeKizunaRing, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjBladeKizunaRing, unknown4c) == 0x4c, "");
static_assert(offsetof(GfMenuObjBladeKizunaRing, unknown58) == 0x58, "");
static_assert(offsetof(GfMenuObjBladeKizunaRing, unknown190) == 0x190, "");
static_assert(sizeof(GfMenuObjBladeKizunaRing) == 0x420, "");

} // namespace gf
