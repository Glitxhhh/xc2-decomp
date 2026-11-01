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
struct MsgObjectNotifyHealHp;
struct MsgPcFieldRelaySurvive;

namespace pc {

class StateFieldWaterDead : public GfStateBase {
  GF_STATE_CLASS(StateFieldWaterDead, GfComBehaviorPc)
  void enter(GfComBehaviorPc *behavior, ai::State *previous);
  void leave(GfComBehaviorPc *behavior, ai::State *next);
  void update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info);
  void onAlive(GfComBehaviorPc *behavior, MsgObjectNotifyHealHp &message);
  bool recieveMessage(void *owner, fw::MessageObject *sender, fw::Message &message) override;
  void procMsgObjectNotifyHealHp(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgObjectNotifyHealHp &message);
  void procMsgPcFieldRelaySurvive(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgPcFieldRelaySurvive &message);
};

static_assert(sizeof(StateFieldWaterDead) == 0x18, "");

} // namespace pc
} // namespace gf
