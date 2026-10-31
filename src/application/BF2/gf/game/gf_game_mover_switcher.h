#pragma once
#include "mm_mtl/singleton.h"

namespace gf {

struct GfSetupParam;

class GfGameMoverSwitcher : public mm::mtl::PtrSingleton<GfGameMoverSwitcher> {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
};

} // namespace gf
