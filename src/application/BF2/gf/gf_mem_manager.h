#pragma once
#include "mm_mtl/singleton.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace gf {

struct GfSetupParam;

class GfMemManager : public mm::mtl::PtrSingleton<GfMemManager> {
public:
  static void buildCoreMemory(const GfSetupParam &param);
  static void destroyCoreMemory();
  static void build(const GfSetupParam &param);
  static void destroy();
  static void initializeGame(mtl::ALLOC_HANDLE handle);
  static void finalizeGame();
};

} // namespace gf
