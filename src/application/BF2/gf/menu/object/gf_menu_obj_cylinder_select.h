#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {
class GfMenuCallContext;

class GfMenuObjCylinderSelect : public GfMenuObject {
public:
  static void open(GfMenuCallContext *context, u32 cylinder);
  static void close(GfMenuCallContext *context);
  void initialize() override;
  void finalize() override;
  void update() override;
};

} // namespace gf
