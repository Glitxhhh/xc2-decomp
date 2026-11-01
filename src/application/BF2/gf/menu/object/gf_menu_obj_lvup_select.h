#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {
class GfMenuCallContext;

class GfMenuObjLvupSelect : public GfMenuObject {
public:
  static void openLevelSelect(GfMenuCallContext *context, u32 level);
  static void openLevelup(GfMenuCallContext *context, u32 level, u32 levelMax);
  void initialize() override;
  void finalize() override;
};

} // namespace gf
