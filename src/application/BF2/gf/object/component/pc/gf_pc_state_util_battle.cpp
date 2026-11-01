#include "gf/object/component/pc/gf_pc_state_util_battle.h"

namespace gf {
namespace pc {

namespace {

// Inferred type: one entry of the battle state and battle action correspondence table; original name unknown.
struct unknown001 {
  STATE_ID unknown00;                        // Inferred role: battle state; original member name unknown.
  btl::BattleCharacter::ACTION_ID unknown04; // Inferred role: battle action; original member name unknown.
};

} // namespace

// Inferred role: battle states and actions, indexed by action; original name unknown.
static const unknown001 unknown002[] = {
    {STATE_ID_BATTLE_START, btl::BattleCharacter::ACTION_ID_UNKNOWN_0},
    {STATE_ID_BATTLE_IDLE, btl::BattleCharacter::ACTION_ID_IDLE},
    {STATE_ID_BATTLE_PUT_OUT_WEAPON, btl::BattleCharacter::ACTION_ID_UNKNOWN_2},
    {STATE_ID_BATTLE_PUT_AWAY_WEAPON, btl::BattleCharacter::ACTION_ID_PUT_AWAY_WEAPON},
    {STATE_ID_BATTLE_MOVE, btl::BattleCharacter::ACTION_ID_MOVE},
    {STATE_ID_BATTLE_KIZUNA_MAX, btl::BattleCharacter::ACTION_ID_UNKNOWN_5},
    {STATE_ID_BATTLE_ATTACK, btl::BattleCharacter::ACTION_ID_ATTACK},
    {STATE_ID_BATTLE_ARTS, btl::BattleCharacter::ACTION_ID_ARTS},
    {STATE_ID_BATTLE_BLADE_ARTS, btl::BattleCharacter::ACTION_ID_BLADE_ARTS},
    {STATE_ID_BATTLE_BLADE_CHANGE, btl::BattleCharacter::ACTION_ID_BLADE_CHANGE},
    {STATE_ID_BATTLE_SP_ATTACK, btl::BattleCharacter::ACTION_ID_SP_ATTACK},
    {STATE_ID_BATTLE_SUPPORT, btl::BattleCharacter::ACTION_ID_UNKNOWN_11},
    {STATE_ID_BATTLE_BLADE_GUARD, btl::BattleCharacter::ACTION_ID_UNKNOWN_12},
    {STATE_ID_BATTLE_REPELLED, btl::BattleCharacter::ACTION_ID_UNKNOWN_13},
    {STATE_ID_BATTLE_DOWN, btl::BattleCharacter::ACTION_ID_UNKNOWN_0E},
    {STATE_ID_BATTLE_KNOCK_BACK, btl::BattleCharacter::ACTION_ID_UNKNOWN_15},
    {STATE_ID_BATTLE_BREAK, btl::BattleCharacter::ACTION_ID_UNKNOWN_16},
    {STATE_ID_BATTLE_DEAD, btl::BattleCharacter::ACTION_ID_UNKNOWN_17},
    {STATE_ID_BATTLE_RESCUE, btl::BattleCharacter::ACTION_ID_RESCUE},
};

bool StateUtilBattle::IsBattleState(STATE_ID state) { return state >= STATE_ID_BATTLE && state <= STATE_ID_BATTLE_RESCUE; }

STATE_ID StateUtilBattle::ConversionActionToState(btl::BattleCharacter::ACTION_ID action) { return unknown002[action].unknown00; }

btl::BattleCharacter::ACTION_ID StateUtilBattle::ConversionStateToAction(STATE_ID state) {
  if (state < STATE_ID_BATTLE_START) {
    return btl::BattleCharacter::ACTION_ID_UNKNOWN_0;
  }

  return unknown002[state - STATE_ID_BATTLE_START].unknown04;
}

} // namespace pc
} // namespace gf
