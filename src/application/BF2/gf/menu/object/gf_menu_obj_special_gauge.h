#pragma once
#include "gf/menu/gf_menu_object.h"

namespace gf {

class GfMenuObjSpecialGauge : public GfMenuObject {
public:
  static void close();
  static void open();
  static void reverse(bool isReverse);
  void initialize() override;
  void finalize() override;
  void update() override;
  static void push();
};

} // namespace gf
