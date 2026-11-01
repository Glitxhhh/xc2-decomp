#include "gf/object/component/pc/field/gf_pc_state_field_air.h"

#include "ai/ai_state.h"
#include "framework/object/updatable_object.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"

namespace gf {
namespace pc {

void StateFieldAir::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  StateUtil::setEnableGravity(*behavior, false);
  StateUtilField::setEnableFallIntoColi(*behavior, true);
  StateUtilField::setAirStatus(*behavior, true);
  StateUtilField::setEnableWaterIn(*behavior, true);
  StateUtil::setEnableFallDistChecker(*behavior, true);
}

void StateFieldAir::leave(GfComBehaviorPc *behavior, ai::State *next) {
  StateUtilField::setEnableWaterIn(*behavior, false);
  StateUtil::setEnableGravity(*behavior, true);
  StateUtilField::setEnableFallIntoColi(*behavior, false);
  StateUtilField::setAirStatus(*behavior, false);
  StateUtil::setEnableFallDistChecker(*behavior, false);
  if (next != nullptr && next->unknown08 == STATE_ID_FIELD_SLIDE_MOVE) {
    StateUtilField::setSlideDirForce(*behavior->unknown08->getComponent<GfComPropertyPc>());
  }
}

} // namespace pc
} // namespace gf
