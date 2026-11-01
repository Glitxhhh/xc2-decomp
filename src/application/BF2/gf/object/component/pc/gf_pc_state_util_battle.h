#pragma once
#include "battle/character/battle_character.h"
#include "gf/object/component/pc/gf_pc_state_id.h"

namespace gf {
namespace pc {

class StateUtilBattle {
public:
  static bool IsBattleState(STATE_ID state);
  static STATE_ID ConversionActionToState(btl::BattleCharacter::ACTION_ID action);
  static btl::BattleCharacter::ACTION_ID ConversionStateToAction(STATE_ID state);
};

} // namespace pc
} // namespace gf
