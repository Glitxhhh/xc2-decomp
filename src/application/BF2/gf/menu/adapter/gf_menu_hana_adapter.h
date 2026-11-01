#pragma once
#include "gf/menu/adapter/gf_menu_adapter.h"
#include "types.h"

namespace gf {

class GfMenuHanaAdapter : public GfMenuAdapter {
public:
  static u32 getSortTableId(u32 type);
  static u32 getMakeSortTableId(u32 type);
};

} // namespace gf
