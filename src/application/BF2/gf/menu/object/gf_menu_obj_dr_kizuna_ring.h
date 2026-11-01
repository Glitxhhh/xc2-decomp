#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace ui {
class UIObjectAcc;
} // namespace ui

namespace gf {

class GfMenuObjDrKizunaRing : public GfMenuObject {
public:
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle);
  static int setFadeOut(u32 handle);
  void initialize() override;
  void finalize() override;
  static bool isLockPos(int index);
  static bool isScreenLR(u32 screen);
  static void setupCircle(ui::UIObjectAcc &, u32);
};

} // namespace gf
