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

class StateFieldExtraControl : public GfStateBase {
public:
  // Inferred role: motion mode picked from the base layer state name; original enumerator names unknown.
  enum Mode {
    MODE_UNKNOWN_M1 = -1, // set by enter before the state name is tested
    MODE_UNKNOWN_0 = 0,   // S_move
    MODE_UNKNOWN_1 = 1,   // S_walkendL, S_walkendR
    MODE_UNKNOWN_2 = 2,   // S_idle
    MODE_UNKNOWN_3 = 3,   // S_talkA_02
  };

  GF_STATE_CLASS(StateFieldExtraControl, GfComBehaviorPc)
  void enter(GfComBehaviorPc *behavior, ai::State *previous);
  void leave(GfComBehaviorPc *behavior, ai::State *next);
  void update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info);
  void setMode(GfComBehaviorPc *behavior, Mode mode);

  Mode unknown18; // Inferred role: current mode; original member name unknown.
  u8 _1c[0x20 - 0x1c];
};

static_assert(offsetof(StateFieldExtraControl, unknown18) == 0x18, "");
static_assert(sizeof(StateFieldExtraControl) == 0x20, "");

} // namespace pc
} // namespace gf
