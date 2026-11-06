#include "gf/object/component/pc/field/gf_pc_state_field_wall_jump_move.h"

#include <math.h>

#include "framework/object/updatable_object.h"
#include "fw/fw_param_manager.h"
#include "fw/fw_update_info.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/env_sensor/gf_com_env_sensor.h"
#include "gf/object/component/pc/field/gf_pc_param_field.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_asm_cmd_id_field.h"
#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "mm_math/mm_plane.h"
#include "mm_mtl/intrusive_ptr.h"

namespace gf {
namespace pc {

void StateFieldWallJumpMove::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  unknown18 = 0.0f;
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  unknown30 = property->unknown160;
  f32 height = property->unknown310.unknown48;
  const MsgPcFieldNotifyWallJump *info = property->unknown310.getWallJumpInfo();
  unknown20 = info->unknown10;
  unknown20.y -= height;
  const EnviromentSensor::unknown003 *wall = StateUtil::getClimbWallInfo(*behavior);
  if (wall != nullptr) {
    unknown20 += wall->unknown00.normal * property->unknown310.unknown18;
  }
  mm::Vec3 diff = unknown20 - unknown30;
  f32 distance = sqrtf(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);
  unknown1c = __builtin_fmaxf(distance / static_cast<const WallCommonParam *>(property->unknown310.unknown08->unknown10[15].param)->jumpSpeed, 1.0f / 30.0f);
  GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
  f32 time = 0.0f;
  comAsm->getPlaybackTime(comAsm->getStateName(ANIM_LAYER_BASE), &time);
  comAsm->setSpeed(time / unknown1c, ANIM_LAYER_BASE);
}

void StateFieldWallJumpMove::leave(GfComBehaviorPc *behavior, ai::State *next) {}

void StateFieldWallJumpMove::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  unknown18 += info.unknown04;
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
  f32 ratio = unknown18 / unknown1c;
  f32 clamped = ratio;
  if (ratio > 1.0f) {
    clamped = 1.0f;
  }
  f32 weight = clamped;
  if (ratio < 0.0f) {
    weight = 0.0f;
  }
  f32 inverse = 1.0f - weight;
  mm::Vec3 position = unknown30 * inverse + unknown20 * weight;
  property->unknown160.y = position.y;
  property->unknown160.x = position.x;
  property->unknown160.z = position.z;
  if (unknown18 >= unknown1c && comAsm->isEnd(ANIM_LAYER_BASE) && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_CLIMBJUMP_02)) {
    reqState(STATE_ID_FIELD_WALL_JUMP_END);
  }
}

} // namespace pc
} // namespace gf
