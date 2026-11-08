#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace ui {
class UICtrlCursorSelect;
} // namespace ui

namespace gf {
class GfMenuBladeList;
class GfMenuCallContext;

class GfMenuObjBladeSet : public GfMenuObject {
public:
  GfMenuObjBladeSet(u32 handle);
  ~GfMenuObjBladeSet() override;
  static bool checkBladeRelease(u32 blade);
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle);
  static int setFadeOut(u32 handle);
  static u32 setEmptyTeamId();
  static bool isMenuBtnEnable(int menu, u32 blade, const GfMenuBladeList *list);
  static void setMenuBtnStat(int menu, u32 blade, const GfMenuBladeList *list);
  void initialize() override;
  void finalize() override;
  void update() override;
  struct OpenParam;

  static void registOpenParam(const OpenParam &);

  u32 unknown24;  // Role and original member name unknown, cleared by the constructor.
  u32 unknown28;  // Role and original member name unknown, cleared by the constructor.
  u32 unknown2c;  // Role and original member name unknown, cleared by the constructor.
  u32 unknown30;  // Role and original member name unknown, cleared by the constructor.
  bool unknown34; // Role and original member name unknown, cleared by the constructor.
  bool unknown35; // Role and original member name unknown, set by the constructor.
  u8 _36[0x38 - 0x36];
  u32 unknown38; // Role and original member name unknown, cleared by the constructor.
  u8 _3c[0x40 - 0x3c];
  GfMenuCallContext *unknown40;      // Inferred role: call context; original member name unknown.
  GfMenuCallContext *unknown48;      // Inferred role: call context; original member name unknown.
  GfMenuBladeList *unknown50;        // Inferred role: blades; original member name unknown.
  ui::UICtrlCursorSelect *unknown58; // Inferred role: blade cursor; original member name unknown.
  GfMenuBladeList *unknown60;        // Inferred role: blades; original member name unknown.
  ui::UICtrlCursorSelect *unknown68; // Inferred role: blade cursor; original member name unknown.
  GfMenuBladeList *unknown70;        // Inferred role: blades; original member name unknown.
  ui::UICtrlCursorSelect *unknown78; // Inferred role: blade cursor; original member name unknown.
  GfMenuBladeList *unknown80;        // Inferred role: blades; original member name unknown.
  ui::UICtrlCursorSelect *unknown88; // Inferred role: blade cursor; original member name unknown.
};

static_assert(offsetof(GfMenuObjBladeSet, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjBladeSet, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjBladeSet, unknown2c) == 0x2c, "");
static_assert(offsetof(GfMenuObjBladeSet, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjBladeSet, unknown34) == 0x34, "");
static_assert(offsetof(GfMenuObjBladeSet, unknown35) == 0x35, "");
static_assert(offsetof(GfMenuObjBladeSet, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjBladeSet, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjBladeSet, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjBladeSet, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuObjBladeSet, unknown58) == 0x58, "");
static_assert(offsetof(GfMenuObjBladeSet, unknown60) == 0x60, "");
static_assert(offsetof(GfMenuObjBladeSet, unknown68) == 0x68, "");
static_assert(offsetof(GfMenuObjBladeSet, unknown70) == 0x70, "");
static_assert(offsetof(GfMenuObjBladeSet, unknown78) == 0x78, "");
static_assert(offsetof(GfMenuObjBladeSet, unknown80) == 0x80, "");
static_assert(offsetof(GfMenuObjBladeSet, unknown88) == 0x88, "");

} // namespace gf
