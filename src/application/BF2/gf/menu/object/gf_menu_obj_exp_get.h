#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjExpGet : public GfMenuObject {
public:
  GfMenuObjExpGet(u32 handle);
  void initialize() override;
  void finalize() override;
  void update() override;
  static void closeAll();
};

} // namespace gf
