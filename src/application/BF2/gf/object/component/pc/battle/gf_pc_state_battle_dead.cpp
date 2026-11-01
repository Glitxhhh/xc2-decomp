#include "gf/object/component/pc/battle/gf_pc_state_battle_dead.h"

#include "battle/battle_global.h"
#include "battle/character/battle_character.h"
#include "battle/utility_battle.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/property/gf_com_property.h"

namespace gf {
namespace pc {

bool StateBattleDead::Enter(GfComBehaviorPc *behavior, ai::State *previous) {
  StateUtil::setFallDamageDisable(*behavior, false);
  unknown22 = false;
  return StateBattleActionBase::Enter(behavior, previous);
}

void StateBattleDead::Leave(GfComBehaviorPc *behavior, ai::State *next) { unknown22 = false; }

void StateBattleDead::Update(btl::BattleCharacter *character, GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  StateBattleActionBase::Update(character, behavior, info);
  if (!unknown22) {
    if (!character->IsControlCharacter()) {
      unknown22 = true;
    } else if (btl::BattleGlobal::get()->IsGameOver() && btl::Utility::IsEnableDeadSequence()) {
      MsgObjectNotifyDead message(DEAD_TYPE_UNKNOWN_1, nullptr);
      StateUtil::notifyDead(*behavior, message, true);
      unknown22 = true;
    }
  }
}

} // namespace pc
} // namespace gf
