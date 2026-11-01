#pragma once
#include "gf/menu/gf_menu_object.h"

namespace gf {

class GfMenuObjOperationInfo : public GfMenuObject {
public:
  static void close();
  static void setDisp(bool isDisp);
  void initialize() override;
  void finalize() override;
  void update() override;
};

} // namespace gf
