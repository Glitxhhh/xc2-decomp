#pragma once
#include "types.h"

namespace ui {
class UIObjectNumberPlugin;
} // namespace ui

namespace gf {

class GfMenuObjMainMenu2 {
public:
  struct OpenParam {
    u32 unknown00; // Inferred role: page; original member name unknown.
  };

  static void registOpenParam(const OpenParam &param);
  static void sendEvent(u32 handle, u32 type, u32 param);
  static void setCloseKeyEnable(bool enable);
  static void closeCharChange();
  static void openMainMenu();
  static void setContentsIcon(ui::UIObjectNumberPlugin *plugin, u32 icon);
  static void disableCharChange();
  static void setSubLayer(u32 layer);
  static void setGuideText(u32 text);
  static void dispCloseButton();
  static void execMapJump();
};

} // namespace gf
