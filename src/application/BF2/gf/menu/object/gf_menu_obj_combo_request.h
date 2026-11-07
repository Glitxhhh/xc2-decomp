#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {
class GfMenuCallContext;

class GfMenuObjComboRequest : public GfMenuObject {
public:
  GfMenuObjComboRequest(u32 handle);
  ~GfMenuObjComboRequest() override;
  static void attachComboRequest(GfMenuCallContext *context);
  void initialize() override;
  void finalize() override;
  void update() override;
};

} // namespace gf
