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

class StateFieldOnGround : public GfStateBase {
  GF_STATE_CLASS(StateFieldOnGround, GfComBehaviorPc)
  void enter(GfComBehaviorPc *behavior, ai::State *previous);
  void leave(GfComBehaviorPc *behavior, ai::State *next);
  void update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info);

  bool unknown18; // Inferred role: set when the next state keeps the access flag; original member name unknown.
  bool unknown19; // Inferred role: set when the next state keeps the lure; original member name unknown.
  u8 _1a[0x20 - 0x1a];
};

static_assert(offsetof(StateFieldOnGround, unknown18) == 0x18, "");
static_assert(offsetof(StateFieldOnGround, unknown19) == 0x19, "");
static_assert(sizeof(StateFieldOnGround) == 0x20, "");

} // namespace pc
} // namespace gf
