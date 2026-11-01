#pragma once
#include "gf/menu/gf_menu_object.h"

namespace gf {
class GfMenuCallContext;

class GfMenuObjFieldSkill : public GfMenuObject {
public:
  static void attachSkip(GfMenuCallContext *context);
  void initialize() override;
  void finalize() override;
};

} // namespace gf
