#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {
class GfMenuCallContext;

class GfMenuObjBlWeapon : public GfMenuObject {
public:
  static bool attach(GfMenuCallContext *context);
  bool isSameWeapon(u32 blade, u32 chip);
  void initialize() override;
  void finalize() override;
};

} // namespace gf
