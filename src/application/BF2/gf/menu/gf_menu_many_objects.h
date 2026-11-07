#pragma once
#include <stddef.h>

#include "mm_mtl/singleton.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

struct GfSetupParam;

class GfMenuManyObjects : public mm::mtl::PtrSingleton<GfMenuManyObjects> {
public:
  GfMenuManyObjects(const GfSetupParam &param);
  ~GfMenuManyObjects();
  static void build(const GfSetupParam &param);
  static void destroy();
  void initialize(const GfSetupParam &param);
  void finalize();
  static bool isInitialized();
  void postUpdate(const fw::UpdateInfo &info);

  bool unknown08;     // Inferred role: initialized; original member name unknown.
  void *unknown10[9]; // Inferred role: queued objects of each many-object type; original member name unknown.
};

static_assert(offsetof(GfMenuManyObjects, unknown08) == 0x08, "");
static_assert(offsetof(GfMenuManyObjects, unknown10) == 0x10, "");
static_assert(sizeof(GfMenuManyObjects) == 0x58, "");

} // namespace gf
