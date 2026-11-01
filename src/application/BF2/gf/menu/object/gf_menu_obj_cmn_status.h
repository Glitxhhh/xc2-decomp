#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjCmnStatus : public GfMenuObject {
public:
  void initialize() override;
  void update() override;
  static bool isOpenDrStatus();
  static bool isOpenBlStatus();
  static void setInputEnable();
  static void setInputDisable();
  static void openDrStatus(u32 driver, int page);
  static void closeDrStatus();
  static void openBlStatus(u32 blade, int page);
  static void closeBlStatus();

  static bool s_DispFlag[2];
};

} // namespace gf
