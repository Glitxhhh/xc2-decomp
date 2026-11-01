#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {
class GfMenuBladeList;

class GfMenuObjBladeSet : public GfMenuObject {
public:
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
};

} // namespace gf
