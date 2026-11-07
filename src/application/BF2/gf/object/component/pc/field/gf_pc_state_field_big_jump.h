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

class StateFieldBigJump : public GfStateBase {
  GF_STATE_CLASS(StateFieldBigJump, GfComBehaviorPc)
  void enter(GfComBehaviorPc *behavior, ai::State *previous);
  void leave(GfComBehaviorPc *behavior, ai::State *next);
  void update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info);

  f32 unknown18;      // Inferred role: elapsed time; original member name unknown.
  f32 unknown1c;      // Inferred role: ascent time; original member name unknown.
  f32 unknown20;      // Inferred role: time the horizontal move and turn start; original member name unknown.
  f32 unknown24;      // Inferred role: jump time; original member name unknown.
  f32 unknown28;      // Inferred role: initial vertical speed; original member name unknown.
  mm::Vec3 unknown30; // Inferred role: start position; original member name unknown.
  mm::Quat unknown40; // Inferred role: start rotation; original member name unknown.
  mm::Quat unknown50; // Inferred role: target rotation; original member name unknown.
  bool unknown60;     // Inferred role: jump motion running; original member name unknown.
  u8 _61[0x70 - 0x61];
};

static_assert(offsetof(StateFieldBigJump, unknown18) == 0x18, "");
static_assert(offsetof(StateFieldBigJump, unknown30) == 0x30, "");
static_assert(offsetof(StateFieldBigJump, unknown40) == 0x40, "");
static_assert(offsetof(StateFieldBigJump, unknown50) == 0x50, "");
static_assert(offsetof(StateFieldBigJump, unknown60) == 0x60, "");
static_assert(sizeof(StateFieldBigJump) == 0x70, "");

} // namespace pc
} // namespace gf
