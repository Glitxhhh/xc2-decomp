#pragma once
#include <stddef.h>

#include "gf/gf_state.h"
#include "gf/object/component/enemy/gf_enemy_state_battle.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
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

class StateFieldWallAdsorptionUnderGround : public GfStateBase {
  GF_STATE_CLASS(StateFieldWallAdsorptionUnderGround, GfComBehaviorPc)
  void enter(GfComBehaviorPc *behavior, ai::State *previous);
  void leave(GfComBehaviorPc *behavior, ai::State *next);
  void update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info);

  f32 unknown18;      // Inferred role: wall float at enter; original member name unknown.
  mm::Vec3 unknown20; // Inferred role: accumulated movement; original member name unknown.
  mm::Quat unknown30; // Inferred role: rotation; original member name unknown.
};

static_assert(offsetof(StateFieldWallAdsorptionUnderGround, unknown18) == 0x18, "");
static_assert(offsetof(StateFieldWallAdsorptionUnderGround, unknown20) == 0x20, "");
static_assert(offsetof(StateFieldWallAdsorptionUnderGround, unknown30) == 0x30, "");
static_assert(sizeof(StateFieldWallAdsorptionUnderGround) == 0x40, "");

} // namespace pc
} // namespace gf
