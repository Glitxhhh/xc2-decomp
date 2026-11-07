#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjDropItem : public GfMenuObject {
public:
  GfMenuObjDropItem(u32 handle);
  void initialize() override;
  void finalize() override;
  void update() override;
  static void closeAll();
};

} // namespace gf
