#pragma once
#include "gf/gf_state.h"
#include "gf/object/component/enemy/gf_enemy_state_battle.h"

namespace ai {
class State;
} // namespace ai

namespace fw {
struct UpdateInfo;
class MessageObject;
} // namespace fw

namespace gf {

class GfComBehaviorPc;
struct MsgPcFieldNotifyBigJump;

namespace pc {

class StateFieldPrepareBigJump : public GfStateBase {
  GF_STATE_CLASS(StateFieldPrepareBigJump, GfComBehaviorPc)
  void enter(GfComBehaviorPc *behavior, ai::State *previous);
  void leave(GfComBehaviorPc *behavior, ai::State *next);
  void update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info);
  bool recieveMessage(void *owner, fw::MessageObject *sender, fw::Message &message) override;
  void procMsgPcFieldNotifyBigJump(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgPcFieldNotifyBigJump &message);
};

static_assert(sizeof(StateFieldPrepareBigJump) == 0x18, "");

} // namespace pc
} // namespace gf
