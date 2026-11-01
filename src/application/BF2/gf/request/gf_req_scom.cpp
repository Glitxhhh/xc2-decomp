#include "gf/request/gf_req_scom.h"

#include <math.h>

#include "fw/fw_update_info.h"
#include "gf/data/gf_character_id.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_en_book.h"
#include "gf/data/gf_data_map.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_data_util.h"
#include "gf/data/gf_object_type.h"
#include "gf/event/gf_event.h"
#include "gf/field/gf_field_bgm.h"
#include "gf/field/gf_field_gimmick.h"
#include "gf/field/gf_field_manager.h"
#include "gf/game/auto_talk/gf_auto_talk.h"
#include "gf/game/event/gf_game_event.h"
#include "gf/game/gf_game_camera.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_mount.h"
#include "gf/game/gf_game_obj.h"
#include "gf/game/gf_game_party.h"
#include "gf/game/gf_game_scene.h"
#include "gf/game/gf_game_speed.h"
#include "gf/game/gf_game_util.h"
#include "gf/game/kizunaring/gf_kizunaring_manager.h"
#include "gf/game/mercenaries/gf_game_mercenaries.h"
#include "gf/game/quest/gf_quest_manager.h"
#include "gf/game/quest/gf_quest_task.h"
#include "gf/game/salvage/gf_salvage_voice.h"
#include "gf/gf_allocator.h"
#include "gf/map/gf_map_manager.h"
#include "gf/menu/gf_menu_fade.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_util.h"
#include "gf/request/gf_req_command.h"
#include "gf/request/gf_scom.h"
#include "gf/scom/gf_scom_enbook.h"
#include "gf/scom/gf_scom_obj.h"
#include "mm_mtl/fixed_list.h" // IWYU pragma: keep
#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/fixed_vector.h"

namespace gf {

static const u32 unknown001 = 4; // Inferred role: object attribute bit cleared when destroying a game object; original name unknown.
static const u32 unknown002 = 4; // Inferred role: game speed layer set by the speed command; original name unknown.
static const u32 unknown003 = 1; // Inferred role: game speed layer set by the local speed command; original name unknown.

SCOM::SCOM(GF_SCOM_HANDLE *handle, SCOM_TYPE type, SCOM_EXEC exec, u16 unknown10) : unknown08(handle), unknown10(unknown10), unknown14(exec), unknown18(type) {}

GF_OBJ_HANDLE *SCOM::getObjHandle() const { return INVALID_HANDLE; }

GF_SCOM_HANDLE *GfReqSmallCom::allocate() {
  s64 handle = unknownd868++;
  if (handle == -1) {
    handle++;
    unknownd868++;
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(handle);
}

GF_SCOM_HANDLE *GfReqSmallCom::addRequest(SCOM *scom) {
  get()->unknown08.push_back(scom);
  return scom->unknown08;
}

GF_SCOM_HANDLE *GfReqSmallCom::addRequestParallel(SCOM *scom) {
  GfReqSmallCom *smallCom = get();
  if (!smallCom->unknownd870) {
    smallCom->unknown4828.push_back(scom);
  } else {
    smallCom->unknown9048.push_back(scom);
  }
  return scom->unknown08;
}

bool SCOM_ENBOOK_IN_BATTLE::exec(const fw::UpdateInfo &) {
  GfDataEnBook::setAttackFlag(unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_ENBOOK_IN_BATTLE::create(GF_OBJ_HANDLE *handle) {
  DataParamAcc acc(handle);
#line 4274
  SCOM_ENBOOK_IN_BATTLE *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ENBOOK_IN_BATTLE(GfReqSmallCom::get()->allocate(), acc.isValid() ? acc.getBdatId() : 0);
  return GfReqSmallCom::addRequestParallel(command);
}

bool SCOM_ENBOOK_BOSS_TIME::exec(const fw::UpdateInfo &) {
  GfDataEnBook::setClearNamedTime(unknown1c, unknown20);
  return true;
}

GF_SCOM_HANDLE *SCOM_ENBOOK_BOSS_TIME::create(GF_OBJ_HANDLE *handle, u32 time) {
  DataParamAcc acc(handle);
#line 4289
  SCOM_ENBOOK_BOSS_TIME *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ENBOOK_BOSS_TIME(GfReqSmallCom::get()->allocate(), acc.isValid() ? acc.getBdatId() : 0, time);
  return GfReqSmallCom::addRequestParallel(command);
}

bool SCOM_ENBOOK_DEFEAT_ENEMY::exec(const fw::UpdateInfo &) {
  GfDataEnBook::incDefeatNum(unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_ENBOOK_DEFEAT_ENEMY::create(GF_OBJ_HANDLE *handle) {
  DataParamAcc acc(handle);
#line 4304
  SCOM_ENBOOK_DEFEAT_ENEMY *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ENBOOK_DEFEAT_ENEMY(GfReqSmallCom::get()->allocate(), acc.isValid() ? acc.getBdatId() : 0);
  return GfReqSmallCom::addRequestParallel(command);
}

bool SCOM_ENBOOK_DEAD_PLAYER::exec(const fw::UpdateInfo &) {
  GfDataEnBook::incDeadNum(unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_ENBOOK_DEAD_PLAYER::create(GF_OBJ_HANDLE *handle) {
  DataParamAcc acc(handle);
#line 4319
  SCOM_ENBOOK_DEAD_PLAYER *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ENBOOK_DEAD_PLAYER(GfReqSmallCom::get()->allocate(), acc.isValid() ? acc.getBdatId() : 0);
  return GfReqSmallCom::addRequestParallel(command);
}

bool SCOM_ADD_TRUST::exec(const fw::UpdateInfo &) {
  if (unknown20 == 0) {
    mm::mtl::FixedVector<u16, 422> blades;
    GfDataBlade::getListPartyAll(blades);
    for (const u16 *it = blades.begin(); it != blades.end(); ++it) {
      GfGameUtil::addTrustPoint(*it, unknown1c);
    }
  } else {
    GfGameUtil::addTrustPoint(unknown20, unknown1c);
  }
  return true;
}

GF_SCOM_HANDLE *SCOM_ADD_TRUST::create(u32 blade, u32 point) {
  if (point != 0) {
#line 535
    SCOM_ADD_TRUST *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ADD_TRUST(GfReqSmallCom::get()->allocate(), blade, point);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

bool SCOM_TARGET_UI::exec(const fw::UpdateInfo &) {
  GfGameManager::setTargetUI(unknown20);
  return true;
}

void SCOM_TARGET_UI::create(GF_OBJ_HANDLE *target) {
#line 1942
  SCOM_TARGET_UI *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_TARGET_UI(GfReqSmallCom::get()->allocate(), target);
  GfReqSmallCom::addRequestParallel(command);
}

SCOM_REFRESH_COMPASS::SCOM_REFRESH_COMPASS(GF_SCOM_HANDLE *handle) : SCOM(handle, SCOM_TYPE_UNKNOWN_78, SCOM_EXEC_UNKNOWN_0, 1), unknown28(3) {}

GF_SCOM_HANDLE *SCOM_REFRESH_COMPASS::create() {
  if (get() == nullptr) {
#line 4841
    SCOM_REFRESH_COMPASS *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_REFRESH_COMPASS(GfReqSmallCom::get()->allocate());
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

bool SCOM_REFRESH_COMPASS::exec(const fw::UpdateInfo &) {
  if (--unknown28 > 0) {
    return false;
  }
  GfQuestManager::requestRefreshQuestTaskState();
  return true;
}

SCOM_BATTLE_TASK_RESET::SCOM_BATTLE_TASK_RESET(GF_SCOM_HANDLE *handle) : SCOM(handle, SCOM_TYPE_UNKNOWN_78, SCOM_EXEC_UNKNOWN_0, 1), unknown28(3) {}

bool SCOM_BATTLE_TASK_RESET::exec(const fw::UpdateInfo &) {
  if (--unknown28 > 0) {
    return false;
  }
  GfQuestManager::resetBattleTaskForBattleEnd();
  return true;
}

SCOM_FSKILLMAX_FOR_DEBUG::SCOM_FSKILLMAX_FOR_DEBUG(GF_SCOM_HANDLE *handle) : SCOM(handle, SCOM_TYPE_UNKNOWN_74, SCOM_EXEC_UNKNOWN_0, 1) {
  GfDataBlade::getListParty(unknown20);
  GfDataBlade::getListReserver(unknown20);
}

bool SCOM_FSKILLMAX_FOR_DEBUG::exec(const fw::UpdateInfo &) {
  if (unknown20.empty()) {
    return true;
  }
  GfKizunaringBlade::completeAllAchievementForDebug(unknown20.back());
  unknown20.pop_back();
  return unknown20.empty();
}

void SCOM_FSKILLMAX_FOR_DEBUG::create() {
#line 4345
  SCOM_FSKILLMAX_FOR_DEBUG *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_FSKILLMAX_FOR_DEBUG(GfReqSmallCom::get()->allocate());
  GfReqSmallCom::addRequestParallel(command);
}

SCOM_SOLO_REX::SCOM_SOLO_REX(GF_SCOM_HANDLE *handle, bool isSolo) : SCOM(handle, SCOM_TYPE_UNKNOWN_78, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(isSolo) {}

bool SCOM_SOLO_REX::exec(const fw::UpdateInfo &) {
  for (u32 i = 0; i < BLADE_COUNT; i++) {
    u32 blade = GfDataBlade::getBladeID(i);
    if (blade == 0) {
      continue;
    }
    u32 creator = GfDataBlade::getCreator(blade);
    if (creator == 0 || creator == DRIVER_REX) {
      continue;
    }
    if (!GfDataBlade::isDummyBlade(blade)) {
      GfDataBlade::setUnselect(blade, unknown1c);
    }
  }
  return true;
}

GF_SCOM_HANDLE *SCOM_SOLO_REX::create(bool isSolo) {
#line 4901
  SCOM_SOLO_REX *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_SOLO_REX(GfReqSmallCom::get()->allocate(), isSolo);
  return GfReqSmallCom::addRequest(command);
}

SCOM_CURRENT_BLADE::SCOM_CURRENT_BLADE(GF_SCOM_HANDLE *handle, u32 blade) : SCOM(handle, SCOM_TYPE_UNKNOWN_78, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(blade) {}

bool SCOM_CURRENT_BLADE::exec(const fw::UpdateInfo &) {
  int slot = GfDataBlade::getDriverSetID(unknown1c);
  u32 driver = GfDataBlade::getSetDriver(unknown1c);
  if (slot >= 0 && slot < static_cast<int>(SET_BLADE_NUM_MAX) && driver != 0) {
    GfDataDriver::setEquipBlade(driver, true, slot);
  }
  if (unknown1c == BLADE_HOMURA) {
    GfDataBlade::setHikariCurrent(false);
  } else if (unknown1c == BLADE_HIKARI) {
    GfDataBlade::setHikariCurrent(true);
  }
  return true;
}

GF_SCOM_HANDLE *SCOM_CURRENT_BLADE::create(u32 blade) {
  SCOM_PARTY_ADD::setCurrentBlade(blade);
#line 4737
  SCOM_CURRENT_BLADE *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_CURRENT_BLADE(GfReqSmallCom::get()->allocate(), blade);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_ZONE::exec(const fw::UpdateInfo &) {
  if (!GfGameManager::isControlFree()) {
    return false;
  }
  u32 map = GfGameManager::getMapID();
  if (map == unknown1c && !GfDataMap::isMapCompleteFlag(map)) {
    GfDataMap::setMapCompleteFlag(unknown1c);
  }
  return true;
}

void SCOM_ZONE::create(u32 map) {
#line 4259
  SCOM_ZONE *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ZONE(GfReqSmallCom::get()->allocate(), map);
  GfReqSmallCom::addRequestParallel(command);
}

bool SCOM_LEVELUP_DEVELOP::exec(const fw::UpdateInfo &) {
  if (!GfGameManager::isControlFree()) {
    return false;
  }
  GfGameUtil::execDevelopLevelUp();
  return true;
}

void SCOM_LEVELUP_DEVELOP::create() {
#line 431
  SCOM_LEVELUP_DEVELOP *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_LEVELUP_DEVELOP(GfReqSmallCom::get()->allocate());
  GfReqSmallCom::addRequestParallel(command);
}

bool SCOM_DESTROY_GAME_OBJ::exec(const fw::UpdateInfo &) {
  GfGameObj::destroyGameObjWithAttribute(unknown20, unknown28, unknown2c);
  return true;
}

void SCOM_DESTROY_GAME_OBJ::create(GF_OBJ_HANDLE *handle, f32 fadeTime, u32 attribute) {
  GfObjAcc acc(handle);
  acc.setFlag(OBJ_FLAG_UI_HIDDEN, true);
  acc.setAttribute(acc.getAttribute() & ~unknown001);
#line 692
  SCOM_DESTROY_GAME_OBJ *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_DESTROY_GAME_OBJ(GfReqSmallCom::get()->allocate(), handle, fadeTime, attribute);
  GfReqSmallCom::addRequestParallel(command);
}

SCOM_OBJ_VFADE_OFF::SCOM_OBJ_VFADE_OFF(GF_SCOM_HANDLE *handle, GF_OBJ_HANDLE *target) : SCOM(handle, SCOM_TYPE_UNKNOWN_67, SCOM_EXEC_UNKNOWN_0, 1), unknown20(target) {}

bool SCOM_OBJ_VFADE_OFF::exec(const fw::UpdateInfo &) {
  GfObjUtil::setVolumeFadeUserFlag(unknown20, false);
  return true;
}

GF_SCOM_HANDLE *SCOM_OBJ_VFADE_OFF::create(GF_OBJ_HANDLE *handle) {
  if (handle != INVALID_HANDLE) {
#line 1305
    SCOM_OBJ_VFADE_OFF *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_OBJ_VFADE_OFF(GfReqSmallCom::get()->allocate(), handle);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

bool SCOM_ADD_SP::exec(const fw::UpdateInfo &) {
  u32 driverId = unknown20;
  if (driverId == 0) {
    if (unknown28 == INVALID_HANDLE) {
      driverId = 0;
    } else {
      GfObjAcc acc(unknown28);
      driverId = acc.getDriverId();
    }
  }
  GfGameUtil::addSP(driverId, unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_ADD_SP::create(GF_OBJ_HANDLE *handle, int skillPoint) {
  if (skillPoint != 0) {
#line 348
    SCOM_ADD_SP *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ADD_SP(GfReqSmallCom::get()->allocate(), skillPoint, 0, handle);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

GF_SCOM_HANDLE *SCOM_ADD_SP::create(u32 driver, int skillPoint) {
  if (skillPoint != 0) {
#line 353
    SCOM_ADD_SP *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ADD_SP(GfReqSmallCom::get()->allocate(), skillPoint, driver, INVALID_HANDLE);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

bool SCOM_ADD_IDEA::exec(const fw::UpdateInfo &) {
  u32 driverId = unknown20;
  if (driverId == 0) {
    if (unknown28 == INVALID_HANDLE) {
      driverId = 0;
    } else {
      GfObjAcc acc(unknown28);
      driverId = acc.getDriverId();
    }
  }
  GfGameUtil::addIdeaPoint(driverId, unknown24, unknown1c);
  return true;
}

bool SCOM_EXEC_DRIVER_ARTS_LVUP::exec(const fw::UpdateInfo &) {
  u32 driverId = unknown20;
  if (driverId == 0) {
    if (unknown28 == INVALID_HANDLE) {
      driverId = 0;
    } else {
      GfObjAcc acc(unknown28);
      driverId = acc.getDriverId();
    }
  }
  GfGameUtil::execDriverArtsLevelUp(driverId, unknown24, unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_EXEC_DRIVER_ARTS_LVUP::create(u32 level, u32 arts, GF_OBJ_HANDLE *handle) {
  if (level != 0) {
#line 265
    SCOM_EXEC_DRIVER_ARTS_LVUP *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_EXEC_DRIVER_ARTS_LVUP(GfReqSmallCom::get()->allocate(), level, 0, arts, handle);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

GF_SCOM_HANDLE *SCOM_EXEC_DRIVER_ARTS_LVUP::create(u32 level, u32 arts, u32 driver) {
  if (level != 0) {
#line 270
    SCOM_EXEC_DRIVER_ARTS_LVUP *command =
        new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_EXEC_DRIVER_ARTS_LVUP(GfReqSmallCom::get()->allocate(), level, driver, arts, INVALID_HANDLE);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

bool SCOM_EXEC_LVUP::exec(const fw::UpdateInfo &) {
  u32 driverId = unknown20;
  if (driverId == 0) {
    if (unknown28 == INVALID_HANDLE) {
      driverId = 0;
    } else {
      GfObjAcc acc(unknown28);
      driverId = acc.getDriverId();
    }
  }
  GfGameUtil::execLevelUp(driverId, unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_EXEC_LVUP::create(u32 level, GF_OBJ_HANDLE *handle) {
  if (level != 0) {
#line 238
    SCOM_EXEC_LVUP *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_EXEC_LVUP(GfReqSmallCom::get()->allocate(), level, 0, handle);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

GF_SCOM_HANDLE *SCOM_EXEC_LVUP::create(u32 level, u32 driver) {
  if (level != 0) {
#line 243
    SCOM_EXEC_LVUP *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_EXEC_LVUP(GfReqSmallCom::get()->allocate(), level, driver, INVALID_HANDLE);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

SCOM_OBJ_ALPHA::SCOM_OBJ_ALPHA(GF_SCOM_HANDLE *handle, GF_OBJ_HANDLE *target, f32 time, f32 alpha)
    : SCOM(handle, SCOM_TYPE_UNKNOWN_40, SCOM_EXEC_UNKNOWN_0, 1), unknown20(target), unknown28(time), unknown2c(0.0f), unknown30(alpha), unknown34(-1.0f) {}

bool SCOM_OBJ_ALPHA::exec(const fw::UpdateInfo &info) {
  GfObjAcc acc(unknown20);
  if (!acc.isValid()) {
    return true;
  }
  if (unknown34 < 0.0f) {
    unknown34 = acc.getAlphaNormal();
  }
  f32 time = unknown28;
  f32 alpha = unknown30;
  f32 startAlpha = unknown34;
  if (time > 0.000001f && fabsf(alpha - startAlpha) >= 0.000001f) {
    f32 elapsed = info.unknown04 + unknown2c;
    if (elapsed > time) {
      elapsed = time;
    }
    unknown2c = elapsed;
    acc.setAlphaNormal(alpha * (elapsed / time) + startAlpha * (1.0f - elapsed / time));
    if (unknown2c < unknown28) {
      return false;
    }
  } else {
    acc.setAlphaNormal(alpha);
  }
  return true;
}

GF_SCOM_HANDLE *SCOM_OBJ_ALPHA::create(GF_OBJ_HANDLE *handle, f32 time, f32 alpha) {
  if (handle != INVALID_HANDLE) {
#line 1268
    SCOM_OBJ_ALPHA *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_OBJ_ALPHA(GfReqSmallCom::get()->allocate(), handle, time, alpha);
    return GfReqSmallCom::addRequestParallel(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

mm::mtl::FixedQueue<SCOM_PARTY_ADD::unknown002, 16> SCOM_PARTY_ADD::s_info;

void SCOM_PARTY_ADD::addBlade(u32 blade, u32 driver, int slot) {
  if (blade == 0) {
    return;
  }
  unknown002 info = {GfDataBlade::getActBlade2CommonBlade(blade), driver, slot, true, false, false, unknown001_1};
  s_info.push(info);
  create();
}

void SCOM_PARTY_ADD::removeBlade(u32 blade, bool isForce) {
  if (blade == 0) {
    return;
  }
  unknown002 info = {GfDataBlade::getActBlade2CommonBlade(blade), 0, -1, isForce, false, false, unknown001_2};
  s_info.push_front(info);
  create();
}

void SCOM_PARTY_ADD::removeBlade(u32 driver, int slot, bool isForce) {
  DataParamAcc acc(OBJECT_TYPE_DRIVER, driver, GIMMICK_TYPE_NONE);
  if (acc.isValid()) {
    u32 blade = acc.getBlade(slot, false);
    if (blade != 0) {
      removeBlade(blade, isForce);
    }
  }
}

void SCOM_PARTY_ADD::releaseBlade(u32 blade) {
  if (blade == 0) {
    return;
  }
  unknown002 info = {GfDataBlade::getActBlade2CommonBlade(blade), 0, -1, false, true, false, unknown001_2};
  s_info.push(info);
  create();
}

void SCOM_PARTY_ADD::addDriver(u32 driver, u32 partyId) {
  unknown002 info = {0, driver, static_cast<int>(partyId), true, false, false, unknown001_3};
  s_info.push(info);
  if (driver == DRIVER_NIA) {
    removeBlade(BLADE_UNKNOWN_1011, false);
  }
  create();
}

void SCOM_PARTY_ADD::removeDriver(u32 driver, bool isForce) {
  unknown002 info = {0, driver, -1, isForce, false, false, unknown001_4};
  s_info.push(info);
  create();
}

void SCOM_PARTY_ADD::setCurrentBlade(u32 blade) {
  for (mm::mtl::FixedQueue<unknown002, 16>::iterator it = s_info.begin(); it != s_info.end(); ++it) {
    unknown002 &info = *it;
    if (info.unknown10 == unknown001_1 && info.unknown00 == blade) {
      info.unknown0e = true;
      return;
    }
  }
  SCOM_EXEC_CURRENT_BLADE::create(blade);
}

void SCOM_PARTY_ADD::initialize() { s_info.clear(); }

SCOM_EXEC_CURRENT_BLADE::SCOM_EXEC_CURRENT_BLADE(GF_SCOM_HANDLE *handle, u32 blade) : SCOM(handle, SCOM_TYPE_UNKNOWN_78, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(blade) {}

bool SCOM_EXEC_CURRENT_BLADE::exec(const fw::UpdateInfo &) {
  u32 driver = GfDataBlade::getSetDriver(unknown1c);
  if (driver != 0) {
    int bladeSet = GfDataDriver::getSetIdByBlade(driver, unknown1c);
    if (bladeSet >= 0) {
      GF_OBJ_HANDLE *handle = GfGameParty::getHandleDriverByBdatID(driver);
      if (!GfObjUtil::isValid(handle)) {
        DataParamAcc paramAcc(OBJECT_TYPE_DRIVER, DRIVER_REX, GIMMICK_TYPE_NONE);
        paramAcc.setBladeSet(bladeSet);
      } else {
        GfGameUtil::setBladeSelect(handle, bladeSet);
        RQ_SETUP_PARTY info;
        GfGameParty::getCurrentPartyInfo(info);
        GfReqCommand::reqChangeParty(info);
      }
    }
  }
  return true;
}

GF_SCOM_HANDLE *SCOM_EXEC_CURRENT_BLADE::create(u32 blade) {
#line 4942
  SCOM_EXEC_CURRENT_BLADE *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_EXEC_CURRENT_BLADE(GfReqSmallCom::get()->allocate(), blade);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_QUEST_REACH::checkEventScequence() const {
  if (!GfGameManager::isInnerState(GF_STATE_EVENT)) {
    return true;
  }
  if (GfGameEvent::get() != nullptr && GfGameEvent::get()->unknown1914 >= GfGameEvent::PLAY_STATE_PLAY) {
    return true;
  }
  return false;
}

bool SCOM_QUEST_REACH::exec(const fw::UpdateInfo &) {
  if (unknown1c == unknown001_3 && !checkEventScequence()) {
    return false;
  }
  GfQuestTask::completeReachTask(unknown1c, unknown20);
  return true;
}

void SCOM_QUEST_REACH::createDiscoverLandmark(u32 landmark) {
#line 1723
  SCOM_QUEST_REACH *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_QUEST_REACH(GfReqSmallCom::get()->allocate(), unknown001_1, landmark);
  GfReqSmallCom::addRequestParallel(command);
  createArriveLandmark(landmark);
}

void SCOM_QUEST_REACH::createArriveLandmark(u32 landmark) {
#line 1730
  SCOM_QUEST_REACH *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_QUEST_REACH(GfReqSmallCom::get()->allocate(), unknown001_2, landmark);
  GfReqSmallCom::addRequestParallel(command);
}

void SCOM_QUEST_REACH::createArrivePlace(u32 place) {
#line 1736
  SCOM_QUEST_REACH *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_QUEST_REACH(GfReqSmallCom::get()->allocate(), unknown001_3, place);
  GfReqSmallCom::addRequestParallel(command);
}

void SCOM_SALVAGER_POINT::setPoint(u32 point) { GfDataUtil::setSalvagerPoint(point); }

void SCOM_RANDOM_INN::setRandom() { GfDataUtil::setRandomInn(); }

bool SCOM_ADD_MONEY::exec(const fw::UpdateInfo &) {
  GfGameUtil::addMoney(unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_ADD_MONEY::create(int money) {
  if (money != 0) {
#line 117
    SCOM_ADD_MONEY *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ADD_MONEY(GfReqSmallCom::get()->allocate(), money);
    return GfReqSmallCom::addRequest(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

bool SCOM_ADD_COIN::exec(const fw::UpdateInfo &) {
  GfGameUtil::addCoin(unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_ADD_COIN::create(int coin) {
  if (coin != 0) {
#line 132
    SCOM_ADD_COIN *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ADD_COIN(GfReqSmallCom::get()->allocate(), coin);
    return GfReqSmallCom::addRequest(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

bool SCOM_ADD_DEVELOP::exec(const fw::UpdateInfo &) {
  GfGameUtil::addDevelopPoint(unknown20, unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_ADD_DEVELOP::create(u32 nation, u32 point) {
  if (nation != 0 && point != 0) {
#line 409
    SCOM_ADD_DEVELOP *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ADD_DEVELOP(GfReqSmallCom::get()->allocate(), nation, point);
    return GfReqSmallCom::addRequest(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

void SCOM_ADD_DEVELOP::createGmk(u32 fieldZone, u32 point) { create(GfDataMap::getFieldZoneId(fieldZone), point); }

bool SCOM_ACCESS_TARGET::exec(const fw::UpdateInfo &) {
  GfGameManager::setAccessTarget(unknown20);
  return true;
}

GF_SCOM_HANDLE *SCOM_ACCESS_TARGET::create(GF_OBJ_HANDLE *target) {
#line 1925
  SCOM_ACCESS_TARGET *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ACCESS_TARGET(GfReqSmallCom::get()->allocate(), target);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_GAME_SPEED::exec(const fw::UpdateInfo &) {
  GfGameSpeed::setLayerSpeed(unknown002, unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_GAME_SPEED::create(f32 speed) {
#line 675
  SCOM_GAME_SPEED *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_GAME_SPEED(GfReqSmallCom::get()->allocate(), speed);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_INTERVAL_SPEED::exec(const fw::UpdateInfo &) {
  GfGameSpeed::setIntervalSpeed(unknown1c, unknown20);
  return true;
}

GF_SCOM_HANDLE *SCOM_INTERVAL_SPEED::create(f32 speed, f32 time) {
#line 661
  SCOM_INTERVAL_SPEED *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_INTERVAL_SPEED(GfReqSmallCom::get()->allocate(), speed, time);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_SET_CAMTYPE::exec(const fw::UpdateInfo &) {
  GfGameCamera::setCameraControlType(unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_SET_CAMTYPE::create(int type) {
#line 1996
  SCOM_SET_CAMTYPE *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_SET_CAMTYPE(GfReqSmallCom::get()->allocate(), type);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_QUEST_EVENT::exec(const fw::UpdateInfo &) {
  GfQuestTask::completeEventTask(unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_QUEST_EVENT::create(u32 event) {
#line 1908
  SCOM_QUEST_EVENT *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_QUEST_EVENT(GfReqSmallCom::get()->allocate(), event);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_QUEST_ORDER::exec(const fw::UpdateInfo &) {
  GfQuestManager::openOrder(unknown1c, false);
  return true;
}

GF_SCOM_HANDLE *SCOM_QUEST_ORDER::create(QuestID quest) {
#line 1688
  SCOM_QUEST_ORDER *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_QUEST_ORDER(GfReqSmallCom::get()->allocate(), quest);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_ITEM_USE::exec(const fw::UpdateInfo &) {
  GfQuestTask::completeItemUseTask(unknown1c, unknown20);
  return true;
}

GF_SCOM_HANDLE *SCOM_ITEM_USE::create(u32 item, u32 count) {
#line 1751
  SCOM_ITEM_USE *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ITEM_USE(GfReqSmallCom::get()->allocate(), item, count);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_DESTROY_FIELD_OBJ::exec(const fw::UpdateInfo &) {
  GfFieldManager::destroyObj();
  return true;
}

GF_SCOM_HANDLE *SCOM_DESTROY_FIELD_OBJ::create() {
#line 898
  SCOM_DESTROY_FIELD_OBJ *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_DESTROY_FIELD_OBJ(GfReqSmallCom::get()->allocate());
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_DESTROY_MAP_OBJ::exec(const fw::UpdateInfo &) {
  GfMapManager::destroyObj();
  return true;
}

GF_SCOM_HANDLE *SCOM_DESTROY_MAP_OBJ::create() {
#line 914
  SCOM_DESTROY_MAP_OBJ *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_DESTROY_MAP_OBJ(GfReqSmallCom::get()->allocate());
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_STOP_LAYER::exec(const fw::UpdateInfo &) {
  GfGameUtil::changeStopLayer(unknown20, unknown28);
  return true;
}

GF_SCOM_HANDLE *SCOM_STOP_LAYER::create(GF_OBJ_HANDLE *target, bool stop) {
#line 1136
  SCOM_STOP_LAYER *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_STOP_LAYER(GfReqSmallCom::get()->allocate(), target, stop);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_SET_IDEA_POINT_FOR_DEBUG::exec(const fw::UpdateInfo &) {
  GfGameUtil::setIdeaPointForDebug(unknown20, unknown24, unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_SET_IDEA_POINT_FOR_DEBUG::create(u32 driver, u32 idea, int point) {
  if (point != 0) {
#line 394
    SCOM_SET_IDEA_POINT_FOR_DEBUG *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_SET_IDEA_POINT_FOR_DEBUG(GfReqSmallCom::get()->allocate(), driver, idea, point);
    return GfReqSmallCom::addRequest(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

bool SCOM_BATTLE_BGM::exec(const fw::UpdateInfo &) { return true; }

GF_SCOM_HANDLE *SCOM_BATTLE_BGM::create(u32 bgm) {
  GfFieldBgm::get()->setRscBattleBgmID(bgm);
#line 3473
  SCOM_BATTLE_BGM *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_BATTLE_BGM(GfReqSmallCom::get()->allocate(), bgm);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_COLI_CHAR_VALID::exec(const fw::UpdateInfo &) {
  GfObjAcc acc(unknown20);
  acc.setCollisionChar(unknown28);
  return true;
}

GF_SCOM_HANDLE *SCOM_COLI_CHAR_VALID::create(GF_OBJ_HANDLE *target, bool isEnable) {
#line 1151
  SCOM_COLI_CHAR_VALID *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_COLI_CHAR_VALID(GfReqSmallCom::get()->allocate(), target, isEnable);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_CREATE_GMK_SET::exec(const fw::UpdateInfo &) {
  GfFieldGimmick::createGmkSet(unknown1c);
  GfAutoTalkManager::get()->create();
  return true;
}

GF_SCOM_HANDLE *SCOM_CREATE_GMK_SET::create(u32 gimmickSet) {
#line 1226
  SCOM_CREATE_GMK_SET *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_CREATE_GMK_SET(GfReqSmallCom::get()->allocate(), gimmickSet);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_DESTROY_GMK_SET::exec(const fw::UpdateInfo &) {
  GfFieldGimmick::disposeGmkSet(unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_DESTROY_GMK_SET::create(u32 gimmickSet) {
#line 1210
  SCOM_DESTROY_GMK_SET *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_DESTROY_GMK_SET(GfReqSmallCom::get()->allocate(), gimmickSet);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_REBUILD::exec(const fw::UpdateInfo &) {
  GfObjUtil::rebuild(unknown20);
  return true;
}

GF_SCOM_HANDLE *SCOM_REBUILD::create(GF_OBJ_HANDLE *target) {
#line 3402
  SCOM_REBUILD *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_REBUILD(GfReqSmallCom::get()->allocate(), target);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_ADD_MERCENARIES_POINT::exec(const fw::UpdateInfo &) {
  GfGameMercenaries::addPoint(unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_ADD_MERCENARIES_POINT::create(u32 point) {
  if (point != 0) {
#line 446
    SCOM_ADD_MERCENARIES_POINT *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_ADD_MERCENARIES_POINT(GfReqSmallCom::get()->allocate(), point);
    return GfReqSmallCom::addRequest(command);
  }
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

bool SCOM_SET_MERCENARIES_LEVEL::exec(const fw::UpdateInfo &) {
  GfGameMercenaries::setLevel(unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_SET_MERCENARIES_LEVEL::create(u32 level) {
#line 460
  SCOM_SET_MERCENARIES_LEVEL *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_SET_MERCENARIES_LEVEL(GfReqSmallCom::get()->allocate(), level);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_EXEC_MOUNT::exec(const fw::UpdateInfo &) {
  GfMountManager::execMount(unknown20, GFATTACH_WEAPON, unknown28);
  return true;
}

GF_SCOM_HANDLE *SCOM_EXEC_MOUNT::create(GF_OBJ_HANDLE *target, OPTMNT mountType) {
#line 1165
  SCOM_EXEC_MOUNT *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_EXEC_MOUNT(GfReqSmallCom::get()->allocate(), target, mountType);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_RESET_MOUNT::exec(const fw::UpdateInfo &) {
  GfMountManager::resetMount(unknown20, GFATTACH_WEAPON, unknown28);
  return true;
}

GF_SCOM_HANDLE *SCOM_RESET_MOUNT::create(GF_OBJ_HANDLE *target, OPTMNT mountType) {
#line 1178
  SCOM_RESET_MOUNT *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_RESET_MOUNT(GfReqSmallCom::get()->allocate(), target, mountType);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_VALID_LOCAL_SPEED::exec(const fw::UpdateInfo &) {
  GfGameUtil::changeStopLayer(unknown20, unknown2c);
  if (unknown28 >= 0.0f) {
    GfGameSpeed::setLayerSpeed(unknown003, unknown28);
  }
  return true;
}

GF_SCOM_HANDLE *SCOM_VALID_LOCAL_SPEED::create(GF_OBJ_HANDLE *target, bool stop, f32 speed) {
#line 1195
  SCOM_VALID_LOCAL_SPEED *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_VALID_LOCAL_SPEED(GfReqSmallCom::get()->allocate(), target, stop, speed);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_LOADING::exec(const fw::UpdateInfo &) {
  if (GfMenuFade::isInitialized()) {
    GfMenuFade::setLoading(unknown1c, unknown20);
    return true;
  }
  return false;
}

GF_SCOM_HANDLE *SCOM_LOADING::create(u32 type, bool isDisp) {
#line 991
  SCOM_LOADING *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_LOADING(GfReqSmallCom::get()->allocate(), type, isDisp);
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_STOP_BATTLE::exec(const fw::UpdateInfo &) {
  GfGameScene *scene = GfGameScene::get();
  if (scene != nullptr) {
    if (!GfGameManager::isBattle()) {
      scene->setForceStopBattle(false);
      return true;
    }
    scene->setForceStopBattle(true);
  }
  return false;
}

GF_SCOM_HANDLE *SCOM_STOP_BATTLE::create() {
#line 4237
  SCOM_STOP_BATTLE *command = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SCOM_STOP_BATTLE(GfReqSmallCom::get()->allocate());
  return GfReqSmallCom::addRequest(command);
}

bool SCOM_ADD_ETHER::exec(const fw::UpdateInfo &) {
  GfGameUtil::addEther(unknown1c);
  return true;
}

GF_SCOM_HANDLE *SCOM_ADD_ETHER::create(int ether) {
  GfGameUtil::addEther(ether);
  return reinterpret_cast<GF_SCOM_HANDLE *>(-1);
}

GAME_VOICE_HANDLE *SCOM_SALVAGE_VOICE::create(GF_OBJ_HANDLE *handle, CV_SALVAGE voice) { return GfSalvageVoice::playVoice(handle, voice); }

GAME_VOICE_HANDLE *SCOM_SALVAGE_VOICE::createResult(GF_OBJ_HANDLE *handle, CV_SALVAGE_RESULT voice) { return GfSalvageVoice::playResultVoice(handle, voice); }

bool SCOM_SALVAGE_VOICE::isPlayEnd(GAME_VOICE_HANDLE *voice) { return GfGameVoice::getResult(voice) != VOICE_RESULT_PLAY; }

bool GfReqSmallCom::isExistCommand() {
  GfReqSmallCom *smallCom = get();
  if (smallCom->unknown08.size() != 0) {
    return true;
  }

  return smallCom->unknown4828.size() != 0;
}

} // namespace gf

template mm::mtl::FixedList<gf::SCOM *, 1024>::iterator mm::mtl::FixedList<gf::SCOM *, 1024>::erase(mm::mtl::FixedList<gf::SCOM *, 1024>::iterator);

template mm::mtl::PtrSingleton<gf::GfReqSmallCom>::~PtrSingleton();

template mm::mtl::PtrSingleton<gf::SCOM_PARTY_ADD>::~PtrSingleton();
