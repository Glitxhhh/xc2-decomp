#pragma once
#include "gf/menu/gf_menu_object.h"

namespace gf {
class GfMenuCallContext;

class GfMenuObjDrEquip : public GfMenuObject {
public:
  static bool attach(GfMenuCallContext *context);
  void initialize() override;
  void finalize() override;
};

} // namespace gf
