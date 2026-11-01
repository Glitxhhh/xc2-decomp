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
struct MsgObjectNotifyDamage;
struct MsgObjectNotifyDead;
struct MsgPcBattleStart;
struct MsgPcFieldRelaySurvive;

namespace pc {

class StateField : public GfStateBase {
  GF_STATE_CLASS(StateField, GfComBehaviorPc)
  void enter(GfComBehaviorPc *behavior, ai::State *previous);
  void leave(GfComBehaviorPc *behavior, ai::State *next);
  void update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info);
  void onDead(GfComBehaviorPc *behavior, MsgObjectNotifyDead &message);
  bool recieveMessage(void *owner, fw::MessageObject *sender, fw::Message &message) override;
  void procMsgPcBattleStart(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgPcBattleStart &message);
  void procMsgObjectNotifyDamage(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgObjectNotifyDamage &message);
  void procMsgObjectNotifyDead(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgObjectNotifyDead &message);
  void procMsgPcFieldRelaySurvive(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgPcFieldRelaySurvive &message);
};

static_assert(sizeof(StateField) == 0x18, "");

} // namespace pc
} // namespace gf
