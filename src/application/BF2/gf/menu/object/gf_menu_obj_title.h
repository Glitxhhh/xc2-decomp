#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {
class GfMenuCallContext;

class GfMenuObjTitle : public GfMenuObject {
public:
  static bool attach(GfMenuCallContext *context);
  void initialize() override;
  void finalize() override;

  static bool isEnableNewGame();
  static bool isEnableNewGameAdv();
  static bool isEnableContinue();
  static bool isEnableOption();
  static void setDispMode(u32 handle, int mode);

  static bool s_NoSaveData;
};

} // namespace gf
