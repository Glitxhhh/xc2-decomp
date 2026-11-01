#include "gf/object/component/pc/field/gf_pc_state_field_on_ground.h"

#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "gf/object/component/pc/plugin/gf_pc_access_plugin.h"

namespace gf {
namespace pc {

void StateFieldOnGround::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  StateUtilField::setAccessFlag(*behavior, true);
  StateUtil::setEnableFootStep(*behavior, true);
  unknown18 = false;
  unknown19 = false;
  StateUtilField::setEnableLure(*behavior, true);
  AccessPlugin *plugin = behavior->unknown001<AccessPlugin>(4);
  if (plugin != nullptr) {
    plugin->unknown28 = 46;
  }
}

void StateFieldOnGround::leave(GfComBehaviorPc *behavior, ai::State *next) {
  if (!unknown18) {
    StateUtilField::setAccessFlag(*behavior, false);
  }
  StateUtil::setEnableFootStep(*behavior, false);
  if (!unknown19) {
    StateUtilField::setEnableLure(*behavior, false);
  }
  AccessPlugin *plugin = behavior->unknown001<AccessPlugin>(4);
  if (plugin != nullptr) {
    plugin->unknown28 = 0;
  }
}

} // namespace pc
} // namespace gf
