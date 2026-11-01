#pragma once
#include <stddef.h>

#include "framework/message/message_object.h"
#include "types.h"

namespace gf {

enum {
  MSG_GAME_TALK_ACTION = 0x100002d,
  MSG_GAME_LIP_ACTION = 0x100002e,
  MSG_GAME_SET_LIP_WEIGHT = 0x100002f,
};

struct MsgGameTalkAction : fw::Message {
  MsgGameTalkAction(u32 action, bool isDirect) : fw::Message(MSG_GAME_TALK_ACTION, 0x40), action(action), isDirect(isDirect), isSuccess(false) {}

  u32 action;
  bool isDirect;
  bool isSuccess;
};

struct MsgGameLipAction : fw::Message {
  MsgGameLipAction(u32 action) : fw::Message(MSG_GAME_LIP_ACTION, 0x40), action(action) {}

  u32 action;
};

struct MsgGameSetLipWeight : fw::Message {
  f32 unknown08; // Inferred role: lip sync weight; original member name unknown.
};

static_assert(offsetof(MsgGameSetLipWeight, unknown08) == 0x08, "");

} // namespace gf
