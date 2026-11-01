#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjHelpHud : public GfMenuObject {
public:
  void initialize() override;
  void finalize() override;
  void enable();
  void disable();
  static void ctrlFadeOut(u32 handle);
  static void ctrlFadeIn(u32 handle);
};

} // namespace gf
