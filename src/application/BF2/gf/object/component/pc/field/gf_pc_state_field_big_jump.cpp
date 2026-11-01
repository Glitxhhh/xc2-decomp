#include "gf/object/component/pc/field/gf_pc_state_field_big_jump.h"

#include "framework/object/updatable_object.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "gf/scom/gf_scom_obj.h"

namespace gf {
namespace pc {

void StateFieldBigJump::leave(GfComBehaviorPc *behavior, ai::State *next) {
  StateUtilField::notifySkillAct(*behavior, false);
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  const MsgPcFieldNotifyBigJump *info = property->unknown310.getBigJumpInfo();
  if (info != nullptr) {
    if (property->unknown111_2) {
      SCOM_QUEST_GIMMICK::createJump(info->unknown3c, 0.0f);
    }
    property->unknown310.setBigJumpInfo(nullptr);
  }
  StateUtil::setEnableGravity(*behavior, true);
  StateUtilField::setSpecialActStatus(*behavior, false);
}

} // namespace pc
} // namespace gf
