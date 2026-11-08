#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace ui {
class UICtrlCursorSelect;
class UIObjectAcc;
} // namespace ui

namespace gf {
class GfMenuBladeList;
class GfMenuCallContext;
class GfMenuDriverList;

class GfMenuObjCharSelect : public GfMenuObject {
public:
  ~GfMenuObjCharSelect() override;

  struct OpenCustomizeParam {
    u32 unknown00; // Inferred role: customize type, 0 driver and 1 blade; original member name unknown.
    u32 unknown04; // Inferred role: character; original member name unknown.
  };

  // Inferred helper: starts the fade out control shared by setFadeOut and setFadeOutSub; original name unknown.
  static int unknown005(u32 handle, u32 type) {
    GfMenuObjUtil::CtrlParam param;
    if (type == 0) {
      param.unknown08 = 2;
      param.unknown00 = GfMenuObjUtil::getPresetCtrlTime(6);
      param.unknown0c = 1;
    } else {
      param.unknown08 = 0x10000000;
      param.unknown50 = "cmn_fade_motion_lr";
      param.unknown58 = type == 2 ? "fade_out_r_early" : "fade_out_l_early";
      param.unknown11 = true;
      param.unknown14 = 10;
    }
    param.unknown04 = 2;
    return GfMenuObjUtil::startCtrl(handle, param, nullptr);
  }

  // Inferred role: layer parameter built from OpenCustomizeParam; original type name unknown.
  struct unknown003 {
    u16 unknown00; // Inferred role: customize type; original member name unknown.
    u32 unknown04; // Inferred role: character; original member name unknown.
  };

  static void registOpenCustomizeParam(const OpenCustomizeParam &param);
  static void openBladeCustomize(u32 handle, u32 blade, u16 group);
  static void openDriverCustomize(u32 handle, u32 driver, u16 group);
  static bool attach(GfMenuCallContext *context);
  static void returnSubMenu();
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeOut(u32 handle, u32 type);
  static void setFadeOutSub(u32 handle, u32 type);
  static void dispOnCopyChar(ui::UIObjectAcc &acc, u32 type);
  static void dispOffCopyChar(ui::UIObjectAcc &acc, u32 type);
  static int setFadeIn(u32 handle, u32 type);
  void initialize() override;
  void finalize() override;
  bool seqSpHikariToHomura();
  bool seqSpHomuraToHikari();
  void update() override;
  bool seqStreamWaitStatDrBefore();
  bool seqStreamWaitStatBlBefore();
  bool seqConfSpecialWaitError();
  bool seqReturn();
  bool seqReturnChange();
  bool seqSpNiaChangeDr();
  static void dispOnChar(u32 type);
  static void dispOffChar(u32 type);
  static void execCharPosScale(u32 type);

  u8 _24[0x28 - 0x24];
  GfMenuDriverList *unknown28;                         // Inferred role: party drivers; original member name unknown.
  mm::mtl::FixedArray<GfMenuBladeList *, 3> unknown30; // Inferred role: blade lists of the party; original member name unknown.
  ui::UICtrlCursorSelect *unknown48;                   // Inferred role: character cursor; original member name unknown.
  mm::mtl::FixedVector<u16, 422> unknown50;            // Inferred role: reserve blades; original member name unknown.
  u8 _3a8[0x430 - 0x3a8];
  GfMenuSequence<GfMenuObjCharSelect, 8> unknown430; // Inferred role: character select steps; original member name unknown.
  bool unknown6c0;                                   // Inferred role: character select steps request flag; original member name unknown.
  u8 _6c1[0x6e0 - 0x6c1];
  GfMenuCallContext *unknown6e0; // Inferred role: call context; original member name unknown.
  u8 _6e8[0x6f0 - 0x6e8];
  mm::mtl::FixedVector<u32, 5> unknown6f0; // Inferred role: sub menu characters; original member name unknown.
  mm::mtl::FixedVector<u32, 3> unknown710; // Inferred role: sub menu characters; original member name unknown.
  mm::mtl::FixedVector<u32, 4> unknown728; // Inferred role: sub menu characters; original member name unknown.
  u8 _740[0x770 - 0x740];
};

static_assert(offsetof(GfMenuObjCharSelect::OpenCustomizeParam, unknown04) == 0x04, "");
static_assert(sizeof(GfMenuObjCharSelect::OpenCustomizeParam) == 0x08, "");
static_assert(offsetof(GfMenuObjCharSelect::unknown003, unknown04) == 0x04, "");
static_assert(sizeof(GfMenuObjCharSelect::unknown003) == 0x08, "");
static_assert(offsetof(GfMenuObjCharSelect, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjCharSelect, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjCharSelect, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjCharSelect, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuObjCharSelect, unknown430) == 0x430, "");
static_assert(offsetof(GfMenuObjCharSelect, unknown6c0) == 0x6c0, "");
static_assert(offsetof(GfMenuObjCharSelect, unknown6e0) == 0x6e0, "");
static_assert(offsetof(GfMenuObjCharSelect, unknown6f0) == 0x6f0, "");
static_assert(offsetof(GfMenuObjCharSelect, unknown710) == 0x710, "");
static_assert(offsetof(GfMenuObjCharSelect, unknown728) == 0x728, "");
static_assert(sizeof(GfMenuObjCharSelect) == 0x770, "");

} // namespace gf
