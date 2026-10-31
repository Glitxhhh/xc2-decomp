// No game string names this file: named after its header and gf_quest_manager.cpp in the same directory (game string C:/Monolithsoft/BF2/prog/application/BF2/gf/game/quest/gf_quest_manager.cpp).
#include "gf/game/quest/gf_quest_target.h"

#include "gf/data/gf_bdat_quest.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_data_quest.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/quest/gf_quest_info.h"
#include "gf/game/quest/gf_quest_task.h"
#include "gf/game/quest/gf_quest_task_param.h"
#include "gf/game/quest/gf_quest_util.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_manager.h"
#include "mm_mtl/algorithm.h"
#include "mm_mtl/fixed_vector.h"

namespace gf {

namespace {

// Inferred role: frames after which a target cache expires; original constant name unknown.
constexpr u16 TARGET_CACHE_LIFE_FRAMES = 300;

// Inferred role: frames an empty quest target cache waits before it takes the progress quest again; original constant name unknown.
constexpr u8 TARGET_CACHE_REFRESH_FRAMES = 31;

// Inferred role: target matched against the quest tasks by the GfQuestTarget::getIconType* functions; original type name unknown.
struct unknown001 {
  unknown001() : unknown00(INVALID_HANDLE), unknown08(0), unknown0c(), unknown10(0), unknown14(false), unknown18(0), unknown1c(0), unknown20(0), unknown24(0), unknown28(gmk::GMK_TYPE_INVALID) {}

  // Inferred helper: sets a reach place target; original name unknown.
  void unknown008(u32 category, u32 placeId, QuestID quest, u32 mapId, bool isCheckCurrent) {
    unknown18 = 2;
    unknown08 = placeId;
    unknown0c = quest;
    unknown10 = mapId;
    unknown20 = category;
    unknown14 = isCheckCurrent;
  }

  // Inferred helper: sets a collect target; original name unknown.
  void unknown009(u32 type, u32 id, QuestID quest, u32 mapId, bool isCheckCurrent) {
    unknown18 = 1;
    unknown08 = id;
    unknown0c = quest;
    unknown10 = mapId;
    unknown1c = type;
    unknown14 = isCheckCurrent;
  }

  // Inferred helper: sets a battle target; original name unknown.
  void unknown010(u32 type, u32 id, QuestID quest, GF_OBJ_HANDLE *handle, bool isCheckCurrent) {
    unknown18 = 3;
    unknown24 = type;
    unknown08 = id;
    unknown0c = quest;
    unknown00 = handle;
    unknown14 = isCheckCurrent;
  }

  // Inferred helper: sets a talk target; original name unknown.
  void unknown011(GF_OBJ_HANDLE *handle, u32 npcId, QuestID quest, u32 mapId, bool isCheckCurrent) {
    unknown18 = 4;
    unknown08 = npcId;
    unknown0c = quest;
    unknown10 = mapId;
    unknown00 = handle;
    unknown14 = isCheckCurrent;
  }

  // Inferred helper: sets a gimmick target when the object is bound to a gimmick; original name unknown.
  void unknown012(GF_OBJ_HANDLE *handle, QuestID quest, u32 mapId, bool isCheckCurrent) {
    gmk::AGmkBase *gmkInst = gmk::getBindedGmkInst(handle);
    if (gmkInst != nullptr) {
      unknown18 = 5;
      unknown08 = gmkInst->unknown20.unknown18;
      unknown0c = quest;
      unknown10 = mapId;
      unknown00 = handle;
      unknown28 = gmkInst->getGmkType();
      unknown14 = isCheckCurrent;
    }
  }

  // Inferred helper: sets a field object target, collected as an item; original name unknown.
  void unknown013(GF_OBJ_HANDLE *handle, QuestID quest, bool isCheckCurrent) {
    gmk::AGmkBase *gmkInst = gmk::getBindedGmkInst(handle);
    unknown18 = 1;
    unknown08 = gmkInst->unknown20.unknown10->id;
    unknown0c = quest;
    unknown00 = handle;
    unknown14 = isCheckCurrent;
  }

  GF_OBJ_HANDLE *unknown00; // Inferred role: object; original member name unknown.
  u32 unknown08;            // Inferred role: id; original member name unknown.
  QuestID unknown0c;        // Inferred role: quest; original member name unknown.
  u32 unknown10;            // Inferred role: map id; original member name unknown.
  bool unknown14;           // Inferred role: compare with the current quests; original member name unknown.
  u32 unknown18;            // Inferred role: target type (1 collect, 2 reach, 3 battle, 4 talk, 5 gimmick); original member name unknown.
  u32 unknown1c;            // Inferred role: collect type; original member name unknown.
  u32 unknown20;            // Inferred role: reach category; original member name unknown.
  u32 unknown24;            // Inferred role: battle type; original member name unknown.
  gmk::GmkType unknown28;   // Inferred role: gimmick type; original member name unknown.
};

static_assert(offsetof(unknown001, unknown08) == 0x08, "");
static_assert(offsetof(unknown001, unknown0c) == 0x0c, "");
static_assert(offsetof(unknown001, unknown10) == 0x10, "");
static_assert(offsetof(unknown001, unknown14) == 0x14, "");
static_assert(offsetof(unknown001, unknown18) == 0x18, "");
static_assert(offsetof(unknown001, unknown1c) == 0x1c, "");
static_assert(offsetof(unknown001, unknown20) == 0x20, "");
static_assert(offsetof(unknown001, unknown24) == 0x24, "");
static_assert(offsetof(unknown001, unknown28) == 0x28, "");
static_assert(sizeof(unknown001) == 0x30, "");

// Inferred role: battle task data; original type name unknown.
struct unknown002 {
  unknown002(u32 battle) {
    QuestListAcc *questListAcc = QuestListAcc::get();
    unknown00 = questListAcc->getBattleTimeCount(battle);
    unknown04 = questListAcc->getBattleCount(battle);
    unknown08 = questListAcc->getBattleCountFlag(battle);
    unknown0c = questListAcc->getBattleEnemyGroupID(battle);
    unknown10 = questListAcc->getBattleEnemyID(battle);
    unknown14 = questListAcc->getBattleEnemySpeciesID(battle);
    unknown18 = questListAcc->getBattleReduceEnemyHP(battle);
  }

  u32 unknown00; // Inferred role: time count; original member name unknown.
  u32 unknown04; // Inferred role: count; original member name unknown.
  u32 unknown08; // Inferred role: count flag; original member name unknown.
  u32 unknown0c; // Inferred role: enemy group id; original member name unknown.
  u32 unknown10; // Inferred role: enemy id; original member name unknown.
  u32 unknown14; // Inferred role: enemy species id; original member name unknown.
  u32 unknown18; // Inferred role: reduce enemy hp; original member name unknown.
};

// Inferred role: collects the uncompleted tasks of the target quest matching the target type; original name unknown.
bool unknown003(mm::mtl::FixedVector<QuestTaskParam, QUEST_TASK_COUNT> &tasks, const unknown001 &target) {
  for (u32 taskIndex = 0; taskIndex < QUEST_TASK_COUNT; taskIndex++) {
    QuestTaskParam param(target.unknown0c, taskIndex, TASK_STATE_NONE);
    if (param.unknown10 == 0) {
      break;
    }
    if (!GfQuestTask::isEnableTaskCondition(param) || GfQuestInfo::isCompleteTask(param)) {
      continue;
    }
    switch (target.unknown18) {
    case 1:
      if (param.unknown10 == TASK_TYPE_COLLECT) {
        tasks.push_back(param);
      }
      break;
    case 2:
      if (param.unknown10 == TASK_TYPE_REACH) {
        tasks.push_back(param);
      }
      break;
    case 3:
      if (param.unknown10 == TASK_TYPE_BATTLE || param.unknown10 == TASK_TYPE_COLLECT) {
        tasks.push_back(param);
      }
      break;
    case 4:
      if (param.unknown10 == TASK_TYPE_UNKNOWN_2 || param.unknown10 == TASK_TYPE_COLLECT || param.unknown10 == TASK_TYPE_TALK || param.unknown10 == TASK_TYPE_CONDITION) {
        tasks.push_back(param);
      }
      break;
    case 5:
      if (param.unknown10 == TASK_TYPE_GIMMICK || param.unknown10 == TASK_TYPE_COLLECT) {
        tasks.push_back(param);
      }
      break;
    }
  }
  return !tasks.empty();
}

// Inferred role: icon type of a matched target quest (1 scenario, 3 current quest); original name unknown.
int unknown004(const unknown001 &target) {
  if (GfDataQuest::getQuestCategory(target.unknown0c) == QTYPE_MAIN) {
    return 1;
  }
  int iconType = 3;
  if (target.unknown14 && !(GfQuestManager::getCurrentQuest(QTYPE_NONE) == target.unknown0c || GfQuestManager::getProgressCurrentQuest(QTYPE_NONE) == target.unknown0c)) {
    QuestID linked = toQuestID(QuestListAcc::get()->getListLinkedQuestID(target.unknown0c));
    if (!(GfQuestManager::getCurrentQuest(QTYPE_NONE) == linked || GfQuestManager::getProgressCurrentQuest(QTYPE_NONE) == linked)) {
      iconType = 0;
    }
  }
  return iconType;
}

// Inferred role: icon type of a collect task for the target; original name unknown.
int unknown005(u32 collect, const unknown001 &target) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  if (u32 tresure = questListAcc->getCollectTresureID(collect)) {
    if (target.unknown1c == 1 && target.unknown08 == tresure) {
      return unknown004(target);
    }
  } else if (u32 enemy = questListAcc->getCollectEnemyID(collect)) {
    if (target.unknown1c == 3 && target.unknown08 == enemy) {
      return unknown004(target);
    }
  } else if (u32 npc = questListAcc->getCollectNpcID(collect)) {
    if (questListAcc->getCollectMapID(collect) == target.unknown10 && npc == target.unknown08) {
      return unknown004(target);
    }
  } else if (u32 item = questListAcc->getCollectItemID(collect)) {
    if (target.unknown1c != 3 && item == target.unknown08) {
      return unknown004(target);
    }
  }
  return 0;
}

// Inferred role: icon type of a condition task for the target; original name unknown.
int unknown014(u32 condition, const unknown001 &target) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  u32 mapId = questListAcc->getConditionMapID(condition);
  if (mapId != 0 && mapId != target.unknown10) {
    return 0;
  }
  if (GfObjUtil::getObjType(target.unknown00) == OBJECT_TYPE_NPC || target.unknown18 == 4) {
    u32 npcId = questListAcc->getConditionNpcID(condition);
    if (npcId == 0 || npcId != target.unknown08) {
      return 0;
    }
  }
  if (target.unknown00 != INVALID_HANDLE) {
    GfObjSetupNpc *setup = GfObjUtil::getObjSetup<GfObjSetupNpc>(target.unknown00);
    if (setup != nullptr && setup->isEvent()) {
      return 0;
    }
  }
  return unknown004(target);
}

// Inferred role: icon type of a talk task for the target (2 when the quest can be ordered); original name unknown.
int unknown015(u32 talk, const unknown001 &target) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  if (questListAcc->getTalkMapID(talk) == target.unknown10 && questListAcc->getTalkNpcID(talk) == target.unknown08) {
    QSTATE state = GfQuestInfo::getState(target.unknown0c);
    if (state == QSTATE_NOT_ORDER) {
      if (GfQuestInfo::isParent(target.unknown0c)) {
        return 2;
      }
    } else if (state != QSTATE_ORDER) {
      return 0;
    }
  } else {
    u32 group;
    u32 npcIndex;
    if (!GfQuestUtil::getDummyTalkGroup(group, npcIndex, target.unknown10, target.unknown08, target.unknown0c) || GfQuestInfo::isDummuTalkGroupFlag(group, npcIndex) ||
        GfQuestInfo::getState(target.unknown0c) != QSTATE_ORDER) {
      return 0;
    }
  }
  return unknown004(target);
}

// Inferred role: icon type of a reach task for the target, per reach category; original name unknown.
int unknown016(u32 reach, const unknown001 &target) {
  if (target.unknown20 == 0) {
    return 0;
  }
  QuestListAcc *questListAcc = QuestListAcc::get();
  if (questListAcc->getReachMapID(reach) != target.unknown10) {
    return 0;
  }
  u32 category = questListAcc->getReachCategory(reach);
  u32 placeId = questListAcc->getReachPlaceID(reach);
  switch (category) {
  case 1:
    if (target.unknown20 == 1 && placeId == target.unknown08) {
      return unknown004(target);
    }
    break;
  case 2:
    if (target.unknown20 == 2 && placeId == target.unknown08) {
      return unknown004(target);
    }
    break;
  case 3:
    if (target.unknown20 == 3 && placeId == target.unknown08) {
      return unknown004(target);
    }
    break;
  }
  return 0;
}

// Inferred role: icon type of a battle task for the target, per battle type (enemy, group, species); original name unknown.
int unknown017(u32 battle, const unknown001 &target) {
  unknown002 data(battle);
  u32 battleType = 1;
  if (data.unknown0c != 0) {
    battleType = 2;
  }
  if (data.unknown14 != 0) {
    battleType = 3;
  }
  bool isMatch = false;
  switch (battleType) {
  case 1:
    if (data.unknown10 == target.unknown08) {
      if (target.unknown00 == INVALID_HANDLE) {
        isMatch = true;
      } else {
        DataParamAcc paramAcc(target.unknown00);
        isMatch = paramAcc.getHp() != 0;
      }
    }
    break;
  case 2:
    if (target.unknown00 != INVALID_HANDLE) {
      DataParamAcc paramAcc(target.unknown00);
      if (paramAcc.getHp() != 0) {
        isMatch = GfQuestUtil::isEnemyGroup(data.unknown0c, paramAcc.getValidBdatId());
      }
    } else {
      isMatch = data.unknown0c == target.unknown08;
    }
    break;
  case 3:
    if (target.unknown00 == INVALID_HANDLE) {
      isMatch = data.unknown14 == target.unknown08;
    } else {
      DataParamAcc paramAcc(target.unknown00);
      if (paramAcc.getHp() != 0) {
        isMatch = paramAcc.getGenus() == data.unknown14;
      }
    }
    break;
  }
  if (isMatch) {
    return unknown004(target);
  }
  return 0;
}

// Inferred role: icon type of a gimmick task for the target, per gimmick type; original name unknown.
int unknown018(u32 gimmick, const unknown001 &target) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  if (questListAcc->getGimmickMapID(gimmick) != target.unknown10) {
    return 0;
  }
  if (u32 door = questListAcc->getGimmickDoorGimmickID(gimmick)) {
    if (target.unknown28 == gmk::GMK_TYPE_DOOR && door == target.unknown08) {
      return unknown004(target);
    }
  } else if (u32 elevator = questListAcc->getGimmickElevatorGimmickID(gimmick)) {
    if (target.unknown28 == gmk::GMK_TYPE_ELEVATOR && elevator == target.unknown08) {
      return unknown004(target);
    }
  } else if (u32 jump = questListAcc->getGimmickJumpGimmickID(gimmick)) {
    if (target.unknown28 == gmk::GMK_TYPE_JUMP && jump == target.unknown08) {
      return unknown004(target);
    }
  } else if (u32 warp = questListAcc->getGimmickWarpGimmickID(gimmick)) {
    if (target.unknown28 == gmk::GMK_TYPE_WARP && warp == target.unknown08) {
      return unknown004(target);
    }
  } else if (u32 salvagePoint = questListAcc->getGimmickSalvagePointID(gimmick)) {
    if (target.unknown28 == gmk::GMK_TYPE_SALVAGE && salvagePoint == target.unknown08) {
      return unknown004(target);
    }
  } else if (u32 tboxPop = questListAcc->getGimmickTboxPopID(gimmick)) {
    if (target.unknown28 == gmk::GMK_TYPE_TBOX && tboxPop == target.unknown08) {
      return unknown004(target);
    }
  } else if (u32 mapGimmick = questListAcc->getGimmickMapGimmickID(gimmick)) {
    if (questListAcc->getGimmickMapGmkIconOff(gimmick) == 0 && target.unknown28 == gmk::GMK_TYPE_MAP_GIMMICK && mapGimmick == target.unknown08) {
      return unknown004(target);
    }
  }
  return 0;
}

// Inferred role: icon type of an object for a quest that can be ordered; original name unknown.
int unknown019(GF_OBJ_HANDLE *handle, QuestID quest) {
  GfObjAcc acc(handle);
  if (acc.isValid()) {
    switch (acc.getType()) {
    case OBJECT_TYPE_NPC:
      if (GfQuestInfo::isQuestNotOrder(quest)) {
        return 2;
      }
      if (!GfQuestInfo::isQuestFin(quest)) {
        return GfQuestTarget::getIconTypeTalk(handle, GfQuestInfo::getProgressQuest(quest), GfGameManager::getMapID(), false);
      }
      break;
    case OBJECT_TYPE_FOBJ:
      if (GfQuestInfo::isQuestNotOrder(quest) && !GfGameManager::isEvent(false)) {
        return 2;
      }
      break;
    }
  }
  return 0;
}

// Inferred role: icon type of a talk target; original name unknown.
int unknown006(const unknown001 &target) {
  mm::mtl::FixedVector<QuestTaskParam, QUEST_TASK_COUNT> tasks;
  if (!unknown003(tasks, target)) {
    return 0;
  }
  for (const QuestTaskParam &task : tasks) {
    switch (task.unknown10) {
    case TASK_TYPE_TALK: {
      int iconType = unknown015(task.unknown14, target);
      if (iconType != 0) {
        return iconType;
      }
      break;
    }
    case TASK_TYPE_COLLECT: {
      int iconType = unknown005(task.unknown14, target);
      if (iconType != 0) {
        return iconType;
      }
      break;
    }
    case TASK_TYPE_CONDITION: {
      int iconType = unknown014(task.unknown14, target);
      if (iconType != 0) {
        return iconType;
      }
      break;
    }
    }
  }
  return 0;
}

// Inferred role: icon type of an object for one quest; original name unknown.
int unknown007(GF_OBJ_HANDLE *handle, QuestID quest) {
  GfObjAcc acc(handle);
  if (acc.isValid()) {
    switch (acc.getType()) {
    case OBJECT_TYPE_ENEMY: {
      int iconType = GfQuestTarget::getIconTypeBattle(1, acc.getEnArrangeId(), quest, handle, false);
      if (iconType != 0) {
        return iconType;
      }
      iconType = GfQuestTarget::getIconTypeBattle(2, acc.getEnArrangeId(), quest, handle, false);
      if (iconType != 0) {
        return iconType;
      }
      iconType = GfQuestTarget::getIconTypeBattle(3, acc.getEnArrangeId(), quest, handle, false);
      if (iconType != 0) {
        return iconType;
      }
      break;
    }
    case OBJECT_TYPE_NPC:
      return GfQuestTarget::getIconTypeTalk(handle, quest, GfGameManager::getMapID(), false);
    case OBJECT_TYPE_GIMMICK:
      return GfQuestTarget::getIconTypeGimmick(handle, quest, GfGameManager::getMapID(), false);
    case OBJECT_TYPE_FOBJ:
      return GfQuestTarget::getIconTypeFieldObj(handle, quest, GfGameManager::getMapID(), false);
    }
  }
  return 0;
}

} // namespace

GfQuestTarget::GfQuestTarget() { GfQuestManager::addEvent(this); }

GfQuestTarget::~GfQuestTarget() { GfQuestManager::removeEvent(this); }

void GfQuestTarget::update(const fw::UpdateInfo &) {
  for (mm::mtl::FixedList<TargetCache, 512>::iterator it = unknown10.begin(); it != unknown10.end(); ++it) {
    TargetCache &cache = *it;
    if (!cache.unknown16 && ++cache.unknown14 > TARGET_CACHE_LIFE_FRAMES) {
      cache.unknown16 = true;
    }
  }
  for (mm::mtl::FixedList<TargetCache, 512>::iterator it = unknown10.begin(); it != unknown10.end(); ++it) {
    if (it->unknown16) {
      unknown10.erase(it);
      return;
    }
  }
}

void GfQuestTarget::gevMapjump(GEV event, const MapjumpCallbackInfo &) {
  if (event == GEV_MAPJUMP_CHANGE_MAP) {
    unknown10.clear();
  }
}

void GfQuestTarget::destroyTargetQuest(QuestID quest) {
  for (mm::mtl::FixedList<TargetCache, 512>::iterator it = unknown10.begin(); it != unknown10.end(); ++it) {
    TargetCache &cache = *it;
    if (cache.unknown10 == quest) {
      cache.unknown16 = true;
    }
  }
}

void GfQuestTarget::qevChangeTaskState(const QuestTaskParam &param) { destroyTargetQuest(param.unknown04); }

void GfQuestTarget::qevChangeQuestState(const QuestStateParam &param) { destroyTargetQuest(param.unknown04); }

void GfQuestTarget::qevOrderQuest(const QuestOrderParam &param) { destroyTargetQuest(GfDataQuest::getListNextQuestA(param.unknown04)); }

void GfQuestTarget::qevCompleteChildQuest(const QuestCompleteChildParam &param) { destroyTargetQuest(param.unknown04); }

void GfQuestTarget::qevChangeCurrentQuest(const QuestChangeParam &param) {
  destroyTargetQuest(param.unknown08);
  destroyTargetQuest(param.unknown04);
}

void GfQuestTarget::qevChangeTaskCondition(const QuestTaskParam &param) { destroyTargetQuest(param.unknown04); }

GfQuestTarget::TargetCache *GfQuestTarget::getTargetCache(GF_OBJ_HANDLE *handle) {
  ParamObj object = {handle, 0, 0};
  mm::mtl::FixedList<TargetCache, 512>::iterator it = mm::mtl::find_if(unknown10.begin(), unknown10.end(), [object](const TargetCache &cache) { return cache == object; });
  if (it == unknown10.end()) {
    return nullptr;
  }
  return &*it;
}

void GfQuestTarget::entryTargetCache(GF_OBJ_HANDLE *handle, QuestID quest) {
  if (unknown10.size() != 512) {
    unknown10.push_back(TargetCache(handle, quest));
  }
}

int GfQuestTarget::getIconTypeReachPlace(u32 category, u32 placeId, QuestID quest, u32 mapId, bool isCheckCurrent) {
  unknown001 target;
  if (mapId == 0) {
    mapId = GfGameManager::getMapID();
  }
  target.unknown008(category, placeId, quest, mapId, isCheckCurrent);
  mm::mtl::FixedVector<QuestTaskParam, QUEST_TASK_COUNT> tasks;
  if (unknown003(tasks, target)) {
    for (const QuestTaskParam &task : tasks) {
      int iconType = unknown016(task.unknown14, target);
      if (iconType != 0) {
        return iconType;
      }
    }
  }
  return 0;
}

int GfQuestTarget::getIconTypeCollect(u32 type, u32 id, QuestID quest, u32 mapId, bool isCheckCurrent) {
  unknown001 target;
  if (mapId == 0) {
    mapId = GfGameManager::getMapID();
  }
  target.unknown009(type, id, quest, mapId, isCheckCurrent);
  mm::mtl::FixedVector<QuestTaskParam, QUEST_TASK_COUNT> tasks;
  if (unknown003(tasks, target)) {
    for (const QuestTaskParam &task : tasks) {
      int iconType = unknown005(task.unknown14, target);
      if (iconType != 0) {
        return iconType;
      }
    }
  }
  return 0;
}

int GfQuestTarget::getIconTypeBattle(u32 type, u32 id, QuestID quest, GF_OBJ_HANDLE *handle, bool isCheckCurrent) {
  unknown001 target;
  target.unknown010(type, id, quest, handle, isCheckCurrent);
  mm::mtl::FixedVector<QuestTaskParam, QUEST_TASK_COUNT> tasks;
  if (unknown003(tasks, target)) {
    for (const QuestTaskParam &task : tasks) {
      switch (task.unknown10) {
      case TASK_TYPE_BATTLE: {
        int iconType = unknown017(task.unknown14, target);
        if (iconType != 0) {
          return iconType;
        }
        break;
      }
      case TASK_TYPE_COLLECT: {
        int iconType = getIconTypeCollect(3, target.unknown08, task.unknown04, 0, target.unknown14);
        if (iconType != 0) {
          return iconType;
        }
        break;
      }
      }
    }
  }
  return 0;
}

int GfQuestTarget::getIconTypeTalk(u32 npcId, QuestID quest, u32 mapId, bool isCheckCurrent) {
  unknown001 target;
  if (mapId == 0) {
    mapId = GfGameManager::getMapID();
  }
  target.unknown011(INVALID_HANDLE, npcId, quest, mapId, isCheckCurrent);
  return unknown006(target);
}

int GfQuestTarget::getIconTypeTalk(GF_OBJ_HANDLE *handle, QuestID quest, u32 mapId, bool isCheckCurrent) {
  DataParamAcc paramAcc(handle);
  unknown001 target;
  u32 npcId = paramAcc.getValidBdatId();
  if (mapId == 0) {
    mapId = GfGameManager::getMapID();
  }
  target.unknown011(handle, npcId, quest, mapId, isCheckCurrent);
  return unknown006(target);
}

int GfQuestTarget::getIconTypeGimmick(GF_OBJ_HANDLE *handle, QuestID quest, u32 mapId, bool isCheckCurrent) {
  unknown001 target;
  u32 currentMapId = mapId;
  if (currentMapId == 0) {
    currentMapId = GfGameManager::getMapID();
  }
  target.unknown012(handle, quest, currentMapId, isCheckCurrent);
  mm::mtl::FixedVector<QuestTaskParam, QUEST_TASK_COUNT> tasks;
  if (unknown003(tasks, target)) {
    for (const QuestTaskParam &task : tasks) {
      switch (task.unknown10) {
      case TASK_TYPE_GIMMICK:
        if (target.unknown18 == 5) {
          int iconType = unknown018(task.unknown14, target);
          if (iconType != 0) {
            return iconType;
          }
        }
        break;
      case TASK_TYPE_COLLECT: {
        QuestListAcc *questListAcc = QuestListAcc::get();
        u32 collectType;
        if (questListAcc->getCollectTresureID(task.unknown14) != 0) {
          collectType = 1;
        } else if (questListAcc->getCollectEnemyID(task.unknown14) != 0) {
          collectType = 3;
        } else {
          collectType = 4;
        }
        unknown001 collect;
        collect.unknown009(collectType, target.unknown08, quest, mapId, isCheckCurrent);
        int iconType = unknown005(task.unknown14, collect);
        if (iconType != 0) {
          return iconType;
        }
        break;
      }
      }
    }
  }
  return 0;
}

int GfQuestTarget::getIconTypeFieldObj(GF_OBJ_HANDLE *handle, QuestID quest, u32, bool isCheckCurrent) {
  unknown001 target;
  target.unknown013(handle, quest, isCheckCurrent);
  mm::mtl::FixedVector<QuestTaskParam, QUEST_TASK_COUNT> tasks;
  if (unknown003(tasks, target)) {
    for (const QuestTaskParam &task : tasks) {
      int iconType = unknown005(task.unknown14, target);
      if (iconType != 0) {
        return iconType;
      }
    }
  }
  return 0;
}

int GfQuestTarget::getIconType(GF_OBJ_HANDLE *handle, QuestID quest) {
  if (!quest.empty()) {
    if (!GfQuestInfo::isDispUI(quest) && GfDataQuest::getQuestCategory(quest) != QTYPE_MAIN) {
      return 0;
    }
    if (!GfQuestInfo::isParent(quest)) {
      quest = GfQuestInfo::getParentQuest(quest);
    }
    return unknown019(handle, quest);
  }

  if (quest.empty()) {
    TargetCache *cache = get()->getTargetCache(handle);
    if (cache != nullptr) {
      quest = cache->unknown10;
      cache->unknown14 = 0;
      if (cache->unknown10.empty()) {
        if (++cache->unknown17 < TARGET_CACHE_REFRESH_FRAMES) {
          return 0;
        }
        cache->unknown17 = 0;
        cache->unknown10 = GfQuestManager::getProgressCurrentQuest(QTYPE_NONE);
      }
      quest = cache->unknown10;
      if (quest == GfQuestManager::getProgressCurrentQuest(QTYPE_NONE) && !GfQuestInfo::isDispUI(quest) && GfDataQuest::getQuestCategory(quest) != QTYPE_MAIN) {
        return 0;
      }
      return unknown007(handle, quest);
    }
  }

  quest = GfQuestManager::getProgressCurrentQuest(QTYPE_NONE);
  if (!quest.empty() && (GfQuestInfo::isDispUI(quest) || GfDataQuest::getQuestCategory(quest) == QTYPE_MAIN)) {
    int iconType = unknown007(handle, quest);
    if (iconType != 0) {
      get()->entryTargetCache(handle, quest);
      return iconType;
    }
  }
  u32 orderMax = GfQuestManager::getOrderQuestMax();
  for (u32 i = 0; i < orderMax; i++) {
    quest = GfQuestManager::getOrderQuest(i);
    int iconType = unknown007(handle, quest);
    if (iconType != 0) {
      get()->entryTargetCache(handle, quest);
      return iconType;
    }
  }
  get()->entryTargetCache(handle, toQuestID(0));
  return 0;
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfQuestTarget>::~PtrSingleton();
