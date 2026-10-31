#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

class GfMenuSoundManager : public mm::mtl::PtrSingleton<GfMenuSoundManager> {
public:
  static u32 playJingle(u32 id);
  bool isSpecInJingle(u32 id);
  bool isSpecOutJingle(u32 id);
};

} // namespace gf
