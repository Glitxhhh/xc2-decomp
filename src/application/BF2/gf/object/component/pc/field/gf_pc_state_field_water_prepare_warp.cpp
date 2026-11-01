#include "gf/object/component/pc/field/gf_pc_state_field_water_prepare_warp.h"

#include "framework/object/updatable_object.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/behavior/gf_com_behavior.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_asm_cmd_id_field.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "gf/object/gf_obj.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace pc {

void StateFieldWaterPrepareWarp::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  GfObj *target = StateUtilField::getAccessTarget(*behavior);
  if (target != nullptr) {
    MsgPcFieldNotifyAction message(0);
    static_cast<GfObj *>(behavior->unknown08)->sendMessage(target, message);
  }
  StateUtilField::setAccessFlag(*behavior, false);
  StateUtilField::setSpecialActStatus(*behavior, true);
  StateUtilField::execAsmCmd(*behavior->unknown08->getComponent<GfComAsm>(), ASM_CMD_ID_FIELD_SWIM_01);
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  property->unknown80 = mm::Vec3::zero;
  property->unknown90 = 0.0f;
  property->unknown94 = 0.0f;
  unknown18 = false;
}

void StateFieldWaterPrepareWarp::leave(GfComBehaviorPc *behavior, ai::State *next) { StateUtilField::setSpecialActStatus(*behavior, false); }

} // namespace pc
} // namespace gf
