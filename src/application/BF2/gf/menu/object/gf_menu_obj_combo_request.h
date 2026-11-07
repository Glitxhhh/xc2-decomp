#pragma once
#include "gf/menu/gf_menu_object.h"

namespace gf {
class GfMenuCallContext;

class GfMenuObjComboRequest : public GfMenuObject {
public:
  static void attachComboRequest(GfMenuCallContext *context);
  void initialize() override;
  void finalize() override;
  void update() override;
};

} // namespace gf
