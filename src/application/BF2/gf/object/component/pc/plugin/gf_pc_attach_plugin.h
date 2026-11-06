#pragma once

#include "gf/object/component/behavior/plugin/gf_plugin.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h" // IWYU pragma: keep

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {
namespace pc {

class AttachPlugin : public Plugin {
  GF_PLUGIN(GfComBehaviorPc)

public:
  virtual bool setup(GfComBehaviorPc &behavior);
  virtual void cleanup(GfComBehaviorPc &behavior);
  virtual void update(GfComBehaviorPc &behavior, const fw::UpdateInfo &info);
};

} // namespace pc
} // namespace gf
