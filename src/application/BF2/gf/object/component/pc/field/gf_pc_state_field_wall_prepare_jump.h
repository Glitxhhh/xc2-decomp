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
} // namespace fw

namespace gf {

class GfComBehaviorPc;

namespace pc {

class StateFieldWallPrepareJump : public GfStateBase {
  GF_STATE_CLASS(StateFieldWallPrepareJump, GfComBehaviorPc)
  void enter(GfComBehaviorPc *behavior, ai::State *previous);
  void leave(GfComBehaviorPc *behavior, ai::State *next);
  void update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info);
  bool recieveMessage(void *owner, fw::MessageObject *sender, fw::Message &message) override;

  bool unknown18; // Inferred role: wall jump requested; original member name unknown.
  u8 _19[0x20 - 0x19];
};

static_assert(offsetof(StateFieldWallPrepareJump, unknown18) == 0x18, "");
static_assert(sizeof(StateFieldWallPrepareJump) == 0x20, "");

} // namespace pc
} // namespace gf
