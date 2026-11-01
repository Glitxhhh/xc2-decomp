#include "gf/object/component/pc/field/gf_pc_state_field_on_wall.h"

#include "framework/message/message_object.h"
#include "framework/object/updatable_object.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_pc_asm_cmd_id_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"

namespace gf {
namespace pc {

bool StateFieldOnWall::recieveMessage(void *owner, fw::MessageObject *sender, fw::Message &message) {
  if (message.unknown00 == MSG_PC_FIELD_WALL_JUMP) {
    procMsgPcFieldWallJump(static_cast<GfComBehaviorPc *>(owner), sender, static_cast<MsgPcFieldWallJump &>(message));
    return true;
  }

  return false;
}

void StateFieldOnWall::procMsgPcFieldWallJump(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgPcFieldWallJump &message) {
  if (StateUtilField::execAsmCmd(*behavior->unknown08->getComponent<GfComAsm>(), ASM_CMD_ID_FIELD_CLIMBJUMP_00)) {
    message.unknown08 = true;
    reqState(STATE_ID_FIELD_WALL_JUMP_START);
  }
}

} // namespace pc
} // namespace gf
