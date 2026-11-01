#pragma once
#include <stddef.h>

#include "gf/gf_state.h"
#include "gf/object/component/enemy/gf_enemy_state_battle.h"
#include "gf/object/component/env_sensor/gf_com_env_sensor.h"
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
struct MsgPcFieldWallJump;

namespace pc {

class StateFieldOnWall : public GfStateBase {
  GF_STATE_CLASS(StateFieldOnWall, GfComBehaviorPc)
  void enter(GfComBehaviorPc *behavior, ai::State *previous);
  void leave(GfComBehaviorPc *behavior, ai::State *next);
  void update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info);
  bool recieveMessage(void *owner, fw::MessageObject *sender, fw::Message &message) override;
  void procMsgPcFieldWallJump(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgPcFieldWallJump &message);

  u8 _18[0x20 - 0x18];
  EnviromentSensor::unknown003 unknown20; // Inferred role: climb wall info; original member name unknown.
};

static_assert(offsetof(StateFieldOnWall, unknown20) == 0x20, "");
static_assert(sizeof(StateFieldOnWall) == 0x50, "");

} // namespace pc
} // namespace gf
