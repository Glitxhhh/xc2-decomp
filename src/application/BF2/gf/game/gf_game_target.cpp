// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/gf/game/gf_game_target.cpp.
#include "gf/game/gf_game_target.h"

#include "gf/game/gf_game_inside_battle_lock.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_util.h"

namespace gf {

bool isEnableTargetBattle(GF_OBJ_HANDLE *handle) {
  GfObj *obj = GfObjUtil::getObj(handle);
  if (obj == nullptr || (GfGameInsideBattleLock::get()->unknown20 && !GfGameInsideBattleLock::isInside(handle))) {
    return false;
  }
  return (obj->unknown110 & 4) != 0;
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfGameTarget>::~PtrSingleton();
