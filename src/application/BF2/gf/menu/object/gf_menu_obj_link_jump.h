#pragma once
#include "gf/menu/gf_menu_object.h"

namespace gf {

class GfMenuObjLinkJump : public GfMenuObject {
public:
  static void open();
  void initialize() override;
  void finalize() override;
  void update() override;
  static void close();
};

} // namespace gf
