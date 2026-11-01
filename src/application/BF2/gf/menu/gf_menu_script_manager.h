#pragma once
#include "mm_mtl/singleton.h"

namespace gf {

class GfMenuScriptManager : public mm::mtl::PtrSingleton<GfMenuScriptManager> {
public:
  static bool isInitialized();
};

} // namespace gf
