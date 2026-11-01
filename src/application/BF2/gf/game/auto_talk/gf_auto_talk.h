#pragma once
#include <stddef.h>

#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GfSetupParam;

class GfAutoTalkManager : public mm::mtl::PtrSingleton<GfAutoTalkManager> {
public:
  void create();
  static void build(const GfSetupParam &param);
  static void destroy();
  static bool isInitialized();
  static void update(const fw::UpdateInfo &info);
  void update(f32 deltaTime);

  u8 _08[0x28 - 0x08];
  void (GfAutoTalkManager::*unknown28)(f32 deltaTime); // Inferred role: current sequence (seqInit, seqUpdate); original member name unknown.
};

static_assert(offsetof(GfAutoTalkManager, unknown28) == 0x28, "");
static_assert(sizeof(GfAutoTalkManager) == 0x38, "");

} // namespace gf
