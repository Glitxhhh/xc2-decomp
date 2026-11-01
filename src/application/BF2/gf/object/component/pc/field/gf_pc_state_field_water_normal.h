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
struct MsgObjectNotifyDead;
struct MsgPcFieldRelaySurvive;
struct MsgPcFieldWaterWarp;
struct MsgPcFieldWaterWarpBuddy;

namespace pc {

class StateFieldWaterNormal : public GfStateBase {
  GF_STATE_CLASS(StateFieldWaterNormal, GfComBehaviorPc)
  void enter(GfComBehaviorPc *behavior, ai::State *previous);
  void leave(GfComBehaviorPc *behavior, ai::State *next);
  void update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info);
  void onDead(GfComBehaviorPc *behavior, MsgObjectNotifyDead &message);
  bool recieveMessage(void *owner, fw::MessageObject *sender, fw::Message &message) override;
  void procMsgPcFieldWaterWarp(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgPcFieldWaterWarp &message);
  void procMsgPcFieldWaterWarpBuddy(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgPcFieldWaterWarpBuddy &message);
  void procMsgObjectNotifyDead(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgObjectNotifyDead &message);
  void procMsgPcFieldRelaySurvive(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgPcFieldRelaySurvive &message);
};

static_assert(sizeof(StateFieldWaterNormal) == 0x18, "");

} // namespace pc
} // namespace gf
