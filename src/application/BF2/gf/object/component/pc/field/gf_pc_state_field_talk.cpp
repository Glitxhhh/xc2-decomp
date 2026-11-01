#include "gf/object/component/pc/field/gf_pc_state_field_talk.h"

#include "framework/message/message_object.h"
#include "framework/object/updatable_object.h"
#include "gf/game/gf_game_manager.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/behavior/gf_com_behavior.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_asm_cmd_id_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace pc {

void StateFieldTalk::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  unknown18 = INVALID_HANDLE;
  GfObj *target = StateUtilField::getAccessTarget(*behavior);
  if (target != nullptr) {
    unknown18 = target->unknownf8;
    MsgPcFieldNotifyAction message(0);
    static_cast<GfObj *>(behavior->unknown08)->sendMessage(target, message);
  }
  StateUtilField::setAccessFlag(*behavior, false);
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  property->unknown80 = mm::Vec3::zero;
  property->unknown94 = 0.0f;
  StateUtilField::setSpecialActStatus(*behavior, true);
  StateUtilField::execAsmCmd(*behavior->unknown08->getComponent<GfComAsm>(), ASM_CMD_ID_FIELD_IDLE);
  StateUtil::setEnableDownIK(*behavior, true);
}

void StateFieldTalk::leave(GfComBehaviorPc *behavior, ai::State *next) {
  GfObj *target = GfObjUtil::getObj(unknown18);
  if (target != nullptr) {
    MsgPcFieldNotifyAction message(1);
    static_cast<GfObj *>(behavior->unknown08)->sendMessage(target, message);
  }
  StateUtilField::setSpecialActStatus(*behavior, false);
  fw::Message message(0x100001a, 0x20);
  StateUtil::broadcastPlayer(*behavior, message);
  StateUtil::setEnableDownIK(*behavior, false);
}

void StateFieldTalk::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  if (!GfGameManager::isPlayerPause()) {
    GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
    const char *stateName = comAsm->getStateName(ANIM_LAYER_BASE);
    bool isIdle = __builtin_strcmp(stateName, "S_idle") == 0;
    bool isTalkEnd = __builtin_strcmp(stateName, "S_talkA_02") == 0;
    if ((isIdle | isTalkEnd) || StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_IDLE)) {
      reqState(STATE_ID_FIELD_IDLE);
    }
  }
}

} // namespace pc
} // namespace gf
