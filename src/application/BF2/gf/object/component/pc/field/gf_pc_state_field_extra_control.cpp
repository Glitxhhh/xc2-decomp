#include "gf/object/component/pc/field/gf_pc_state_field_extra_control.h"

#include "framework/object/updatable_object.h"
#include "gf/game/gf_game_manager.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_state_util.h"

namespace gf {
namespace pc {

void StateFieldExtraControl::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  unknown18 = MODE_UNKNOWN_FFFFFFFF;
  const char *stateName = behavior->unknown08->getComponent<GfComAsm>()->getStateName(ANIM_LAYER_BASE);
  if (stateName != nullptr) {
    if (__builtin_strcmp(stateName, "S_idle") == 0) {
      setMode(behavior, MODE_UNKNOWN_2);
    } else if (__builtin_strcmp(stateName, "S_move") == 0) {
      setMode(behavior, MODE_UNKNOWN_0);
    } else if (__builtin_strcmp(stateName, "S_walkendL") == 0 || __builtin_strcmp(stateName, "S_walkendR") == 0) {
      setMode(behavior, MODE_UNKNOWN_1);
    } else if (__builtin_strcmp(stateName, "S_talkA_02") == 0) {
      setMode(behavior, MODE_UNKNOWN_3);
    }
  }
  behavior->getProperty()->unknown94 = 0.0f;
}

void StateFieldExtraControl::leave(GfComBehaviorPc *behavior, ai::State *next) { StateUtil::setEnableDownIK(*behavior, false); }

void StateFieldExtraControl::setMode(GfComBehaviorPc *behavior, Mode mode) {
  if (unknown18 == mode) {
    return;
  }
  if (mode == MODE_UNKNOWN_2) {
    GfGameManager::setGmkTutorialMoverOK(true);
    StateUtil::setEnableDownIK(*behavior, true);
    StateUtil::setEnableDownIK(*behavior, true);
  } else if (mode == MODE_UNKNOWN_3) {
    StateUtil::setEnableDownIK(*behavior, true);
  }
  unknown18 = mode;
}

} // namespace pc
} // namespace gf
