#pragma once
#include "mm_mtl/singleton.h"

namespace gf {

class GfMenuManyObjects : public mm::mtl::PtrSingleton<GfMenuManyObjects> {
public:
  static bool isInitialized();
};

} // namespace gf
