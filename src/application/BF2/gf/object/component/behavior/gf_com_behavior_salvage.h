#pragma once
#include <stddef.h>

#include "gf/object/component/behavior/gf_com_behavior.h"
#include "mm_mtl/delegate.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

// Layout from its constructor (0x710057e7d0) and procAnimCallback: the salvage state callback at 0x98, bound by the
// salvage states (StateSalvageClimbStart::onEnter).
class GfComBehaviorSalvage : public GfComBehavior {
public:
  static mm::mtl::RTTI m_rtti;

  GfComBehaviorSalvage();
  ~GfComBehaviorSalvage() override;
  void setup();
  void cleanup();
  void update(const fw::UpdateInfo &info) override;
  void procAnimCallback(GfComAsm *comAsm, const CallBackCache &cache) override;
  const mm::mtl::RTTI *getRTTI() const override;

  mm::mtl::Delegate<void()> unknown98; // Inferred role: salvage state animation callback; original member name unknown.
};

static_assert(offsetof(GfComBehaviorSalvage, unknown98) == 0x98, "");
static_assert(sizeof(GfComBehaviorSalvage) == 0xb8, "");

} // namespace gf
