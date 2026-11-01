#pragma once
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

class StateFieldWaterDeadSink : public GfStateBase {
  GF_STATE_CLASS(StateFieldWaterDeadSink, GfComBehaviorPc)
  void enter(GfComBehaviorPc *behavior, ai::State *previous);
  void leave(GfComBehaviorPc *behavior, ai::State *next);
  void update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info);

  f32 unknown18; // Inferred role: elapsed time; original member name unknown.
};

static_assert(sizeof(StateFieldWaterDeadSink) == 0x20, "");

} // namespace pc
} // namespace gf
