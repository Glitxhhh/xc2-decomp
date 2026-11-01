#include "gf/object/component/pc/field/gf_pc_state_field_wall_prepare_jump.h"

#include "framework/object/updatable_object.h"
#include "gf/object/component/behavior/gf_com_behavior.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "gf/object/gf_obj.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace pc {

void StateFieldWallPrepareJump::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  GfObj *target = StateUtilField::getAccessTarget(*behavior);
  if (target != nullptr) {
    MsgPcFieldNotifyAction message(0);
    static_cast<GfObj *>(behavior->unknown08)->sendMessage(target, message);
  }
  StateUtilField::setAccessFlag(*behavior, false);
  StateUtilField::setSpecialActStatus(*behavior, true);
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  property->unknown80 = mm::Vec3::zero;
  property->unknown90 = 0.0f;
  property->unknown94 = 0.0f;
  unknown18 = false;
}

void StateFieldWallPrepareJump::leave(GfComBehaviorPc *behavior, ai::State *next) {
  StateUtilField::setSpecialActStatus(*behavior, false);
  StateUtilField::setAccessFlag(*behavior, false);
}

} // namespace pc
} // namespace gf
