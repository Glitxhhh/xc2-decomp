#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace ui {
class UIObjectAcc;
} // namespace ui

namespace gf {

class GfMenuObjBladeKizunaRing : public GfMenuObject {
public:
  static void close();
  static void open();
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle);
  static int setFadeOut(u32 handle);
  static void setupName(ui::UIObjectAcc &acc);
  void initialize() override;
  void finalize() override;
};

} // namespace gf
