#pragma once
#include <stddef.h>

#include "gf/object/component/behavior/gf_com_behavior.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

class GfComBehaviorUI : public GfComBehavior {
public:
  static mm::mtl::RTTI m_rtti;

  // Layout from GfObjFactory, which sets the first byte before calling setup.
  struct SetupInfo {
    bool unknown00; // Inferred role: eye blink enabled; original member name unknown.
  };

  GfComBehaviorUI();
  ~GfComBehaviorUI() override;
  void setup(const SetupInfo &info);
  void cleanup();
  void update(const fw::UpdateInfo &info) override;
  const mm::mtl::RTTI *getRTTI() const override;
};

static_assert(offsetof(GfComBehaviorUI::SetupInfo, unknown00) == 0x00, "");
static_assert(sizeof(GfComBehaviorUI) == 0x98, "");

} // namespace gf
