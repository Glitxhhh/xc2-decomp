#pragma once
#include <stddef.h>

#include "gf/gf_state.h"
#include "gf/object/component/enemy/gf_enemy_state_battle.h"
#include "types.h"

namespace ai {
class State;
} // namespace ai

namespace fw {
struct UpdateInfo;
class MessageObject;
} // namespace fw

namespace gf {

class GfComBehaviorPc;
struct MsgObjectNotifyHealHp;
struct MsgPcFieldRelaySurvive;

namespace pc {

class StateFieldDead : public GfStateBase {
  GF_STATE_CLASS(StateFieldDead, GfComBehaviorPc)
  void enter(GfComBehaviorPc *behavior, ai::State *previous);
  void leave(GfComBehaviorPc *behavior, ai::State *next);
  void update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info);
  void onAlive(GfComBehaviorPc *behavior, MsgObjectNotifyHealHp &message);
  bool recieveMessage(void *owner, fw::MessageObject *sender, fw::Message &message) override;
  void procMsgObjectNotifyHealHp(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgObjectNotifyHealHp &message);
  void procMsgPcFieldRelaySurvive(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgPcFieldRelaySurvive &message);

  bool unknown18; // Inferred role: down pose pending; original member name unknown.
  u8 _19[0x20 - 0x19];
};

static_assert(offsetof(StateFieldDead, unknown18) == 0x18, "");
static_assert(sizeof(StateFieldDead) == 0x20, "");

} // namespace pc
} // namespace gf
