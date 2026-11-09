#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/list/ui_list_info.h"

namespace gf {

class GfMenuCallContext;
class GfMenuDriverList;
class GfMenuIDList;
class GfMenuItemList;
struct MenuCommonWindowParam;
struct MenuID;
struct MenuDriverInfo;
struct MenuItemInfo;

class GfMenuObjCommonText : public GfMenuObject {
public:
  static void sendEvent(u32 handle, u32 type, u32 param, f32 delay);
  static int setFadeIn(u32 handle);
  static int setFadeOut(u32 handle);
  void initialize() override;
  void finalize() override;
  void update() override;
  struct OpenKizunaParam {
    u8 *unknown00; // Inferred role: bdat; original member name unknown.
    u32 unknown08; // Inferred role: text id; original member name unknown.
    u32 unknown0c; // Inferred role: condition; original member name unknown.
  };
  struct OpenNumSelectParam {
    u32 unknown00; // Inferred role: first value of the number selection; original member name unknown.
    u32 unknown04; // Inferred role: second value of the number selection; original member name unknown.
    u32 unknown08; // Inferred role: third value of the number selection; original member name unknown.
    u32 unknown0c; // Inferred role: fourth value of the number selection; original member name unknown.
  };

  static void close();
  static void setupDialog(u32 handle);
  static void open(GfMenuCallContext *context, const MenuCommonWindowParam &param);
  static void open(GfMenuCallContext *context, u32 window, u32 param);
  static void openError(GfMenuCallContext *context, u32 error, u32 param);
  static void openItem(GfMenuCallContext *context, u32 window, u32 item);
  static void openMissionStop(GfMenuCallContext *context, u32 mission, u32 param);
  static void openSelectItem(GfMenuCallContext *context, const GfMenuItemList *list);
  static void openDrChange(GfMenuCallContext *context, u32 driver, const GfMenuDriverList *list);
  static void openGetItem(GfMenuCallContext *context, const GfMenuItemList *items);
  static void openSubMenu(GfMenuCallContext *context, const GfMenuIDList *list);
  static void openKizunaDialog(GfMenuCallContext *context, const OpenKizunaParam &param);
  static void openOwnerChange(GfMenuCallContext *context, u32 driver, u32 other);
  static void openNumSelect(GfMenuCallContext *context, const OpenNumSelectParam &param);

  static ui::UIListInfo<MenuItemInfo> *s_pItemList;
  static ui::UIListInfo<MenuID> *s_pSubMenuIDList;
  static ui::UIListInfo<MenuDriverInfo> *s_pChangeDrList;
};

} // namespace gf
