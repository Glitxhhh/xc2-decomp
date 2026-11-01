#include "gf/object/component/pc/gf_pc_property_battle.h"

#include "battle/character/battle_character.h"
#include "battle/character/character_manager_battle.h"
#include "battle/character/character_parameter_battle.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/gf_obj.h"

namespace gf {
namespace pc {

GfPropertyBattle::GfPropertyBattle() {
  unknown08 = -1;
  unknown0c = 0;
  unknown10 = 1.0f;
  unknown14 = 0;
  unknown17 = false;
  unknown18 = false;
}

void GfPropertyBattle::setup(const GfComPropertyPc &property) { unknown08 = btl::CharacterManager::get()->Register(static_cast<GfObj *>(property.unknown08)->unknownf8, false); }

void GfPropertyBattle::cleanup(const GfComPropertyPc &property) {
  if (unknown08 >= 0) {
    btl::CharacterManager::get()->Release(unknown08, static_cast<GfObj *>(property.unknown08)->unknownf8);
    unknown08 = -1;
  }
}

void GfPropertyBattle::flush(const GfComPropertyPc &property) {}

const btl::CharacterParameter *GfPropertyBattle::GetCharacterParameterConst() const {
  int id = unknown08;
  btl::BattleCharacter *character = btl::CharacterManager::get()->GetCharacterConst(id);
  return character->GetCharacterParameterConst(true);
}

const btl::PlayerParameter *GfPropertyBattle::GetPlayerParameterConst() const { return static_cast<const btl::PlayerParameter *>(GetCharacterParameterConst()); }

void GfPropertyBattle::SetStartCondition(MsgPcBattleStart &message) {
  unknown14 = message.unknown08;
  unknown15 = message.unknown0c;
  unknown16 = message.unknown10;
}

} // namespace pc
} // namespace gf
