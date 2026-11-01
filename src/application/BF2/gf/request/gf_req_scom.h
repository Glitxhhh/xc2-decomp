#pragma once
#include <stddef.h>

#include "gf/data/gf_data_blade.h"
#include "gf/game/gf_game_voice.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gf/object/component/property/gf_com_property.h"
#include "gf/request/gf_scom.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
enum LangType : u32;
} // namespace fw

namespace gf {

struct GAME_VOICE_HANDLE;
struct GF_SCOM_HANDLE;
struct GF_OBJ_HANDLE;
struct ParamObj;
enum OPTMNT : u32;

class SCOM_ADD_TRUST : public SCOM {
public:
  SCOM_ADD_TRUST(GF_SCOM_HANDLE *handle, u32 blade, u32 point) : SCOM(handle, SCOM_TYPE_UNKNOWN_64, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(point), unknown20(blade) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(u32 blade, u32 point);

  u32 unknown1c; // Inferred role: trust point; original member name unknown.
  u32 unknown20; // Inferred role: blade; original member name unknown.
};

class SCOM_SET_TRUST_FOR_DEBUG : public SCOM {
public:
  SCOM_SET_TRUST_FOR_DEBUG(GF_SCOM_HANDLE *handle, u32 blade, u32 point) : SCOM(handle, SCOM_TYPE_UNKNOWN_65, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(point), unknown20(blade) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(u32 blade, u32 point);

  u32 unknown1c; // Inferred role: trust point; original member name unknown.
  u32 unknown20; // Inferred role: blade; original member name unknown.
};

static_assert(offsetof(SCOM_SET_TRUST_FOR_DEBUG, unknown1c) == 0x1c, "");
static_assert(offsetof(SCOM_SET_TRUST_FOR_DEBUG, unknown20) == 0x20, "");
static_assert(sizeof(SCOM_SET_TRUST_FOR_DEBUG) == 0x28, "");

class SCOM_MISSION_COMPLETE : public SCOM {
public:
  SCOM_MISSION_COMPLETE(GF_SCOM_HANDLE *handle, u32 mission) : SCOM(handle, SCOM_TYPE_UNKNOWN_80, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(mission) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(u32 mission);

  u32 unknown1c; // Inferred role: mercenaries mission; original member name unknown.
};

static_assert(offsetof(SCOM_MISSION_COMPLETE, unknown1c) == 0x1c, "");
static_assert(sizeof(SCOM_MISSION_COMPLETE) == 0x20, "");

class SCOM_ADD_ITEM {
public:
  static GF_SCOM_HANDLE *create(u32 item, int num);
};

class SCOM_ADD_ETHER : public SCOM {
public:
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(int ether);

  int unknown1c; // Inferred role: ether; original member name unknown.
};

static_assert(offsetof(SCOM_ADD_ETHER, unknown1c) == 0x1c, "");
static_assert(sizeof(SCOM_ADD_ETHER) == 0x20, "");

class SCOM_LEVELUP_DEVELOP : public SCOM {
public:
  SCOM_LEVELUP_DEVELOP(GF_SCOM_HANDLE *handle) : SCOM(handle, SCOM_TYPE_UNKNOWN_12, SCOM_EXEC_UNKNOWN_0, 1) {}
  bool exec(const fw::UpdateInfo &info) override;
  static void create();
};

class SCOM_ADD_EXP {
public:
  static GF_SCOM_HANDLE *createInnExp(u32 exp);
};

class SCOM_POPUP {
public:
  static void createQuest(QuestID quest);
  static void createDevelop(u32 location, u32 level);
  static void createAffinity(u32 blade, u32 driver, u32 trustRank);
  static bool createAchievement(u32 blade, u32 achievement, u32 level);
  static void createIdea(u32 driver, u32 idea, u32 level);
  static void createArts(u32 driver, u32 arts);
  static void createCrystalOK(u32 item);
  static void createMercenaryReturn(u32 map, u32 teamID);
};

class SCOM_TARGET_UI : public SCOM {
public:
  SCOM_TARGET_UI(GF_SCOM_HANDLE *handle, GF_OBJ_HANDLE *target) : SCOM(handle, SCOM_TYPE_UNKNOWN_47, SCOM_EXEC_UNKNOWN_0, 1), unknown20(target) {}
  bool exec(const fw::UpdateInfo &info) override;
  static void create(GF_OBJ_HANDLE *target);

  u8 _1c[0x20 - 0x1c];
  GF_OBJ_HANDLE *unknown20; // Inferred role: target; original member name unknown.
};

class SCOM_PARTY_ADD {
public:
  // Inferred role: kind of a queued party change (1 add blade, 2 remove blade, 3 add driver, 4 remove driver); original enum and enumerator names unknown.
  enum unknown001 {
    unknown001_1 = 1,
    unknown001_2 = 2,
    unknown001_3 = 3,
    unknown001_4 = 4,
  };

  // Inferred role: queued party change; original type name unknown.
  struct unknown002 {
    u32 unknown00;        // Inferred role: blade; original member name unknown.
    u32 unknown04;        // Inferred role: driver; original member name unknown.
    int unknown08;        // Inferred role: slot or party id; original member name unknown.
    bool unknown0c;       // Inferred role: keep as reserve; original member name unknown.
    bool unknown0d;       // Inferred role: release; original member name unknown.
    bool unknown0e;       // Inferred role: make current; original member name unknown.
    unknown001 unknown10; // Inferred role: change kind; original member name unknown.
  };

  static void addBlade(u32 blade, u32 driver, int slot);
  static GF_SCOM_HANDLE *create();
  static void removeBlade(u32 blade, bool isForce);
  static void removeBlade(u32 driver, int slot, bool isForce);
  static void releaseBlade(u32 blade);
  static void addDriver(u32 driver, u32 partyId);
  static void removeDriver(u32 driver, bool isForce);
  static void setCurrentBlade(u32 blade);
  static void initialize();

  static mm::mtl::FixedQueue<unknown002, 16> s_info;
};

static_assert(offsetof(SCOM_PARTY_ADD::unknown002, unknown0c) == 0x0c, "");
static_assert(offsetof(SCOM_PARTY_ADD::unknown002, unknown10) == 0x10, "");
static_assert(sizeof(SCOM_PARTY_ADD::unknown002) == 0x14, "");

class SCOM_EXEC_CURRENT_BLADE : public SCOM {
public:
  SCOM_EXEC_CURRENT_BLADE(GF_SCOM_HANDLE *handle, u32 blade);
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(u32 blade);

  u32 unknown1c; // Inferred role: blade; original member name unknown.
};

static_assert(offsetof(SCOM_EXEC_CURRENT_BLADE, unknown1c) == 0x1c, "");
static_assert(sizeof(SCOM_EXEC_CURRENT_BLADE) == 0x20, "");

class SCOM_CURRENT_BLADE : public SCOM {
public:
  SCOM_CURRENT_BLADE(GF_SCOM_HANDLE *handle, u32 blade);
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(u32 blade);

  u32 unknown1c; // Inferred role: blade; original member name unknown.
};

static_assert(offsetof(SCOM_CURRENT_BLADE, unknown1c) == 0x1c, "");
static_assert(sizeof(SCOM_CURRENT_BLADE) == 0x20, "");

class SCOM_PARTY_LEADER {
public:
  static void create(u32 objectType, u32 leader);
};

class SCOM_REFRESH_COMPASS : public SCOM, public mm::mtl::PtrSingleton<SCOM_REFRESH_COMPASS> {
public:
  SCOM_REFRESH_COMPASS(GF_SCOM_HANDLE *handle);
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create();

  int unknown28; // Inferred role: wait count; original member name unknown.
};

static_assert(offsetof(SCOM_REFRESH_COMPASS, unknown28) == 0x28, "");
static_assert(sizeof(SCOM_REFRESH_COMPASS) == 0x30, "");

class SCOM_BATTLE_TASK_RESET : public SCOM, public mm::mtl::PtrSingleton<SCOM_BATTLE_TASK_RESET> {
public:
  SCOM_BATTLE_TASK_RESET(GF_SCOM_HANDLE *handle);
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create();

  int unknown28; // Inferred role: wait count; original member name unknown.
};

static_assert(offsetof(SCOM_BATTLE_TASK_RESET, unknown28) == 0x28, "");
static_assert(sizeof(SCOM_BATTLE_TASK_RESET) == 0x30, "");

class SCOM_FSKILLMAX_FOR_DEBUG : public SCOM {
public:
  SCOM_FSKILLMAX_FOR_DEBUG(GF_SCOM_HANDLE *handle);
  bool exec(const fw::UpdateInfo &info) override;
  static void create();

  mm::mtl::FixedVector<u16, BLADE_COUNT> unknown20; // Inferred role: blades left to complete; original member name unknown.
};

static_assert(offsetof(SCOM_FSKILLMAX_FOR_DEBUG, unknown20) == 0x20, "");
static_assert(sizeof(SCOM_FSKILLMAX_FOR_DEBUG) == 0x378, "");

class SCOM_SOLO_REX : public SCOM {
public:
  SCOM_SOLO_REX(GF_SCOM_HANDLE *handle, bool isSolo);
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(bool isSolo);

  bool unknown1c; // Inferred role: solo flag; original member name unknown.
};

static_assert(offsetof(SCOM_SOLO_REX, unknown1c) == 0x1c, "");
static_assert(sizeof(SCOM_SOLO_REX) == 0x20, "");

enum CV_SALVAGE {};
enum CV_SALVAGE_RESULT {};

class SCOM_SALVAGE_VOICE {
public:
  static GAME_VOICE_HANDLE *create(GF_OBJ_HANDLE *handle, CV_SALVAGE voice);
  static GAME_VOICE_HANDLE *createResult(GF_OBJ_HANDLE *handle, CV_SALVAGE_RESULT voice);
  static bool isPlayEnd(GAME_VOICE_HANDLE *voice);
};

class SCOM_FIELD_VOICE {
public:
  static void create(CV_FIELD voice, CV_PRIO priority);
  static void createLevelup(const ParamObj &paramObj);
  static void createBadWeather();
  static void createTime(CV_FIELD voice);
};

class SCOM_ZONE : public SCOM {
public:
  SCOM_ZONE(GF_SCOM_HANDLE *handle, u32 map) : SCOM(handle, SCOM_TYPE_UNKNOWN_66, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(map) {}
  bool exec(const fw::UpdateInfo &info) override;
  static void create(u32 map);

  u32 unknown1c; // Inferred role: map; original member name unknown.
};

class SCOM_HOMURI_PARTS {
public:
  static void create(u32 partyId, bool isVisible, f32 alpha);
};

class SCOM_SALVAGER_POINT {
public:
  static void setPoint(u32 point);
};

class SCOM_RANDOM_INN {
public:
  static void setRandom();
};

class SCOM_MAXIMUM_HEAL : public SCOM {
public:
  SCOM_MAXIMUM_HEAL(GF_SCOM_HANDLE *handle, GF_OBJ_HANDLE *target) : SCOM(handle, SCOM_TYPE_UNKNOWN_8, SCOM_EXEC_UNKNOWN_0, 1), unknown20(target) {}
  bool exec(const fw::UpdateInfo &info) override;
  static void create(GF_OBJ_HANDLE *handle);

  u8 _1c[0x20 - 0x1c];
  GF_OBJ_HANDLE *unknown20; // Inferred role: target; original member name unknown.
};

static_assert(offsetof(SCOM_MAXIMUM_HEAL, unknown20) == 0x20, "");
static_assert(sizeof(SCOM_MAXIMUM_HEAL) == 0x28, "");

class SCOM_ADD_IDEA : public SCOM {
public:
  SCOM_ADD_IDEA(GF_SCOM_HANDLE *handle, int point, u32 driver, u32 idea, GF_OBJ_HANDLE *target)
      : SCOM(handle, SCOM_TYPE_UNKNOWN_9, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(point), unknown20(driver), unknown24(idea), unknown28(target) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(GF_OBJ_HANDLE *handle, u32 idea, int point);

  int unknown1c;            // Inferred role: idea point; original member name unknown.
  u32 unknown20;            // Inferred role: driver; original member name unknown.
  u32 unknown24;            // Inferred role: idea; original member name unknown.
  GF_OBJ_HANDLE *unknown28; // Inferred role: driver object; original member name unknown.
};

static_assert(offsetof(SCOM_ADD_IDEA, unknown1c) == 0x1c, "");
static_assert(offsetof(SCOM_ADD_IDEA, unknown20) == 0x20, "");
static_assert(offsetof(SCOM_ADD_IDEA, unknown24) == 0x24, "");
static_assert(offsetof(SCOM_ADD_IDEA, unknown28) == 0x28, "");
static_assert(sizeof(SCOM_ADD_IDEA) == 0x30, "");

class SCOM_EXEC_DRIVER_ARTS_LVUP : public SCOM {
public:
  SCOM_EXEC_DRIVER_ARTS_LVUP(GF_SCOM_HANDLE *handle, u32 level, u32 driver, u32 arts, GF_OBJ_HANDLE *target)
      : SCOM(handle, SCOM_TYPE_UNKNOWN_54, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(level), unknown20(driver), unknown24(arts), unknown28(target) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(u32 level, u32 arts, GF_OBJ_HANDLE *handle);
  static GF_SCOM_HANDLE *create(u32 level, u32 arts, u32 driver);

  u32 unknown1c;            // Inferred role: level; original member name unknown.
  u32 unknown20;            // Inferred role: driver; original member name unknown.
  u32 unknown24;            // Inferred role: arts; original member name unknown.
  GF_OBJ_HANDLE *unknown28; // Inferred role: driver object; original member name unknown.
};

static_assert(offsetof(SCOM_EXEC_DRIVER_ARTS_LVUP, unknown1c) == 0x1c, "");
static_assert(offsetof(SCOM_EXEC_DRIVER_ARTS_LVUP, unknown20) == 0x20, "");
static_assert(offsetof(SCOM_EXEC_DRIVER_ARTS_LVUP, unknown24) == 0x24, "");
static_assert(offsetof(SCOM_EXEC_DRIVER_ARTS_LVUP, unknown28) == 0x28, "");
static_assert(sizeof(SCOM_EXEC_DRIVER_ARTS_LVUP) == 0x30, "");

class SCOM_OBJ_ALPHA : public SCOM {
public:
  SCOM_OBJ_ALPHA(GF_SCOM_HANDLE *handle, GF_OBJ_HANDLE *target, f32 time, f32 alpha);
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(GF_OBJ_HANDLE *handle, f32 time, f32 alpha);

  u8 _1c[0x20 - 0x1c];
  GF_OBJ_HANDLE *unknown20; // Inferred role: target; original member name unknown.
  f32 unknown28;            // Inferred role: fade time; original member name unknown.
  f32 unknown2c;            // Inferred role: elapsed time; original member name unknown.
  f32 unknown30;            // Inferred role: target alpha; original member name unknown.
  f32 unknown34;            // Inferred role: start alpha; original member name unknown.
};

static_assert(offsetof(SCOM_OBJ_ALPHA, unknown20) == 0x20, "");
static_assert(offsetof(SCOM_OBJ_ALPHA, unknown28) == 0x28, "");
static_assert(offsetof(SCOM_OBJ_ALPHA, unknown2c) == 0x2c, "");
static_assert(offsetof(SCOM_OBJ_ALPHA, unknown30) == 0x30, "");
static_assert(offsetof(SCOM_OBJ_ALPHA, unknown34) == 0x34, "");
static_assert(sizeof(SCOM_OBJ_ALPHA) == 0x38, "");

class SCOM_OBJ_VFADE_OFF : public SCOM {
public:
  SCOM_OBJ_VFADE_OFF(GF_SCOM_HANDLE *handle, GF_OBJ_HANDLE *target);
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(GF_OBJ_HANDLE *handle);

  u8 _1c[0x20 - 0x1c];
  GF_OBJ_HANDLE *unknown20; // Inferred role: target; original member name unknown.
};

static_assert(offsetof(SCOM_OBJ_VFADE_OFF, unknown20) == 0x20, "");
static_assert(sizeof(SCOM_OBJ_VFADE_OFF) == 0x28, "");

class SCOM_ADD_WP : public SCOM {
public:
  // Inferred role: weapon point target (0 driver, 1 driver object, 2 reserve blades, 3 driver bdat id); original enum and enumerator names unknown.
  enum unknown004 {
    unknown004_0 = 0,
    unknown004_1 = 1,
    unknown004_2 = 2,
    unknown004_3 = 3,
  };

  SCOM_ADD_WP(GF_SCOM_HANDLE *handle, GF_OBJ_HANDLE *object, int weaponPoint, u32 weaponType, unknown004 target)
      : SCOM(handle, SCOM_TYPE_UNKNOWN_7, SCOM_EXEC_UNKNOWN_0, 1), unknown20(object), unknown28(weaponPoint), unknown2c(weaponType), unknown30(target) {}
  SCOM_ADD_WP(GF_SCOM_HANDLE *handle, int driver, int weaponPoint, u32 weaponType, unknown004 target)
      : SCOM(handle, SCOM_TYPE_UNKNOWN_7, SCOM_EXEC_UNKNOWN_0, 1), unknown20_int(driver), unknown28(weaponPoint), unknown2c(weaponType), unknown30(target) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(int weaponPoint, u32 weaponType);
  static GF_SCOM_HANDLE *createForReserve(int weaponPoint);
  static GF_SCOM_HANDLE *createForObject(GF_OBJ_HANDLE *handle, int weaponPoint, u32 weaponType);
  static GF_SCOM_HANDLE *createForBdatid(int driver, int weaponPoint, u32 weaponType);

  u8 _1c[0x20 - 0x1c];
  union {
    GF_OBJ_HANDLE *unknown20; // Inferred role: driver object; original member name unknown.
    int unknown20_int;        // Inferred role: driver bdat id, read when unknown30 is unknown004_3; original member name unknown.
  };
  int unknown28;        // Inferred role: weapon point; original member name unknown.
  u32 unknown2c;        // Inferred role: weapon type; original member name unknown.
  unknown004 unknown30; // Inferred role: target kind; original member name unknown.
};

static_assert(offsetof(SCOM_ADD_WP, unknown20) == 0x20, "");
static_assert(offsetof(SCOM_ADD_WP, unknown28) == 0x28, "");
static_assert(offsetof(SCOM_ADD_WP, unknown2c) == 0x2c, "");
static_assert(offsetof(SCOM_ADD_WP, unknown30) == 0x30, "");
static_assert(sizeof(SCOM_ADD_WP) == 0x38, "");

class SCOM_ADD_SP : public SCOM {
public:
  SCOM_ADD_SP(GF_SCOM_HANDLE *handle, int skillPoint, u32 driver, GF_OBJ_HANDLE *target)
      : SCOM(handle, SCOM_TYPE_UNKNOWN_8, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(skillPoint), unknown20(driver), unknown28(target) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(GF_OBJ_HANDLE *handle, int skillPoint);
  static GF_SCOM_HANDLE *create(u32 driver, int skillPoint);

  int unknown1c; // Inferred role: skill point; original member name unknown.
  u32 unknown20; // Inferred role: driver; original member name unknown.
  u8 _24[0x28 - 0x24];
  GF_OBJ_HANDLE *unknown28; // Inferred role: driver object; original member name unknown.
};

static_assert(offsetof(SCOM_ADD_SP, unknown1c) == 0x1c, "");
static_assert(offsetof(SCOM_ADD_SP, unknown20) == 0x20, "");
static_assert(offsetof(SCOM_ADD_SP, unknown28) == 0x28, "");
static_assert(sizeof(SCOM_ADD_SP) == 0x30, "");

class SCOM_EXEC_LVUP : public SCOM {
public:
  SCOM_EXEC_LVUP(GF_SCOM_HANDLE *handle, u32 level, u32 driver, GF_OBJ_HANDLE *target)
      : SCOM(handle, SCOM_TYPE_UNKNOWN_5, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(level), unknown20(driver), unknown28(target) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(u32 level, GF_OBJ_HANDLE *handle);
  static GF_SCOM_HANDLE *create(u32 level, u32 driver);

  u32 unknown1c; // Inferred role: level; original member name unknown.
  u32 unknown20; // Inferred role: driver; original member name unknown.
  u8 _24[0x28 - 0x24];
  GF_OBJ_HANDLE *unknown28; // Inferred role: driver object; original member name unknown.
};

static_assert(offsetof(SCOM_EXEC_LVUP, unknown1c) == 0x1c, "");
static_assert(offsetof(SCOM_EXEC_LVUP, unknown20) == 0x20, "");
static_assert(offsetof(SCOM_EXEC_LVUP, unknown28) == 0x28, "");
static_assert(sizeof(SCOM_EXEC_LVUP) == 0x30, "");

class SCOM_ADD_MONEY : public SCOM {
public:
  SCOM_ADD_MONEY(GF_SCOM_HANDLE *handle, int money) : SCOM(handle, SCOM_TYPE_UNKNOWN_1, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(money) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(int money);

  int unknown1c; // Inferred role: money; original member name unknown.
};

static_assert(offsetof(SCOM_ADD_MONEY, unknown1c) == 0x1c, "");
static_assert(sizeof(SCOM_ADD_MONEY) == 0x20, "");

class SCOM_ADD_COIN : public SCOM {
public:
  SCOM_ADD_COIN(GF_SCOM_HANDLE *handle, int coin) : SCOM(handle, SCOM_TYPE_UNKNOWN_2, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(coin) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(int coin);

  int unknown1c; // Inferred role: coin; original member name unknown.
};

static_assert(offsetof(SCOM_ADD_COIN, unknown1c) == 0x1c, "");
static_assert(sizeof(SCOM_ADD_COIN) == 0x20, "");

class SCOM_ADD_DEVELOP : public SCOM {
public:
  SCOM_ADD_DEVELOP(GF_SCOM_HANDLE *handle, u32 nation, u32 point) : SCOM(handle, SCOM_TYPE_UNKNOWN_11, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(point), unknown20(nation) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(u32 nation, u32 point);
  static void createGmk(u32 fieldZone, u32 point);

  u32 unknown1c; // Inferred role: point; original member name unknown.
  u32 unknown20; // Inferred role: nation; original member name unknown.
};

static_assert(offsetof(SCOM_ADD_DEVELOP, unknown1c) == 0x1c, "");
static_assert(offsetof(SCOM_ADD_DEVELOP, unknown20) == 0x20, "");
static_assert(sizeof(SCOM_ADD_DEVELOP) == 0x28, "");

class SCOM_ACCESS_TARGET : public SCOM {
public:
  SCOM_ACCESS_TARGET(GF_SCOM_HANDLE *handle, GF_OBJ_HANDLE *target) : SCOM(handle, SCOM_TYPE_UNKNOWN_46, SCOM_EXEC_UNKNOWN_0, 1), unknown20(target) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(GF_OBJ_HANDLE *target);

  GF_OBJ_HANDLE *unknown20; // Inferred role: target; original member name unknown.
};

static_assert(offsetof(SCOM_ACCESS_TARGET, unknown20) == 0x20, "");
static_assert(sizeof(SCOM_ACCESS_TARGET) == 0x28, "");

class SCOM_SET_FLAG : public SCOM {
public:
  SCOM_SET_FLAG(GF_SCOM_HANDLE *handle, u32 size, u32 index, u32 value) : SCOM(handle, SCOM_TYPE_UNKNOWN_48, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(size), unknown20(index), unknown24(value) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(u32 size, u32 index, u32 value);

  u32 unknown1c; // Inferred role: flag size in bits; original member name unknown.
  u32 unknown20; // Inferred role: flag index; original member name unknown.
  u32 unknown24; // Inferred role: flag value; original member name unknown.
};

static_assert(offsetof(SCOM_SET_FLAG, unknown1c) == 0x1c, "");
static_assert(offsetof(SCOM_SET_FLAG, unknown20) == 0x20, "");
static_assert(offsetof(SCOM_SET_FLAG, unknown24) == 0x24, "");
static_assert(sizeof(SCOM_SET_FLAG) == 0x28, "");

class SCOM_CHAR_DEAD : public SCOM {
public:
  SCOM_CHAR_DEAD(GF_SCOM_HANDLE *handle, GF_OBJ_HANDLE *target, const MsgObjectNotifyDead &message);
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(GF_OBJ_HANDLE *target, const MsgObjectNotifyDead &message);

  GF_OBJ_HANDLE *unknown20;      // Inferred role: dead object; original member name unknown.
  MsgObjectNotifyDead unknown28; // Inferred role: dead message, without its damage; original member name unknown.
};

static_assert(offsetof(SCOM_CHAR_DEAD, unknown20) == 0x20, "");
static_assert(offsetof(SCOM_CHAR_DEAD, unknown28) == 0x28, "");
static_assert(sizeof(SCOM_CHAR_DEAD) == 0x58, "");

class SCOM_CHAR_DMG {
public:
  static void create(GF_OBJ_HANDLE *target, const MsgObjectNotifyDamage &message);
};

class SCOM_GAME_SPEED : public SCOM {
public:
  SCOM_GAME_SPEED(GF_SCOM_HANDLE *handle, f32 speed) : SCOM(handle, SCOM_TYPE_UNKNOWN_20, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(speed) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(f32 speed);

  f32 unknown1c; // Inferred role: speed; original member name unknown.
};

static_assert(offsetof(SCOM_GAME_SPEED, unknown1c) == 0x1c, "");
static_assert(sizeof(SCOM_GAME_SPEED) == 0x20, "");

class SCOM_INTERVAL_SPEED : public SCOM {
public:
  SCOM_INTERVAL_SPEED(GF_SCOM_HANDLE *handle, f32 speed, f32 time) : SCOM(handle, SCOM_TYPE_UNKNOWN_19, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(speed), unknown20(time) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(f32 speed, f32 time);

  f32 unknown1c; // Inferred role: speed; original member name unknown.
  f32 unknown20; // Inferred role: time; original member name unknown.
};

static_assert(offsetof(SCOM_INTERVAL_SPEED, unknown1c) == 0x1c, "");
static_assert(offsetof(SCOM_INTERVAL_SPEED, unknown20) == 0x20, "");
static_assert(sizeof(SCOM_INTERVAL_SPEED) == 0x28, "");

class SCOM_SET_CAMTYPE : public SCOM {
public:
  SCOM_SET_CAMTYPE(GF_SCOM_HANDLE *handle, int type) : SCOM(handle, SCOM_TYPE_UNKNOWN_49, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(type) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(int type);

  int unknown1c; // Inferred role: camera control type; original member name unknown.
};

static_assert(offsetof(SCOM_SET_CAMTYPE, unknown1c) == 0x1c, "");
static_assert(sizeof(SCOM_SET_CAMTYPE) == 0x20, "");

class SCOM_QUEST_EVENT : public SCOM {
public:
  SCOM_QUEST_EVENT(GF_SCOM_HANDLE *handle, u32 event) : SCOM(handle, SCOM_TYPE_UNKNOWN_45, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(event) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(u32 event);

  u32 unknown1c; // Inferred role: event; original member name unknown.
};

static_assert(offsetof(SCOM_QUEST_EVENT, unknown1c) == 0x1c, "");
static_assert(sizeof(SCOM_QUEST_EVENT) == 0x20, "");

class SCOM_QUEST_ORDER : public SCOM {
public:
  SCOM_QUEST_ORDER(GF_SCOM_HANDLE *handle, QuestID quest) : SCOM(handle, SCOM_TYPE_UNKNOWN_41, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(quest) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(QuestID quest);

  QuestID unknown1c; // Inferred role: quest; original member name unknown.
};

static_assert(offsetof(SCOM_QUEST_ORDER, unknown1c) == 0x1c, "");
static_assert(sizeof(SCOM_QUEST_ORDER) == 0x20, "");

class SCOM_ITEM_USE : public SCOM {
public:
  SCOM_ITEM_USE(GF_SCOM_HANDLE *handle, u32 item, u32 count) : SCOM(handle, SCOM_TYPE_UNKNOWN_68, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(item), unknown20(count) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(u32 item, u32 count);

  u32 unknown1c; // Inferred role: item; original member name unknown.
  u32 unknown20; // Inferred role: count; original member name unknown.
};

static_assert(offsetof(SCOM_ITEM_USE, unknown1c) == 0x1c, "");
static_assert(offsetof(SCOM_ITEM_USE, unknown20) == 0x20, "");
static_assert(sizeof(SCOM_ITEM_USE) == 0x28, "");

class SCOM_DESTROY_FIELD_OBJ : public SCOM {
public:
  SCOM_DESTROY_FIELD_OBJ(GF_SCOM_HANDLE *handle) : SCOM(handle, SCOM_TYPE_UNKNOWN_24, SCOM_EXEC_UNKNOWN_0, 1) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create();
};

static_assert(sizeof(SCOM_DESTROY_FIELD_OBJ) == 0x20, "");

class SCOM_DESTROY_MAP_OBJ : public SCOM {
public:
  SCOM_DESTROY_MAP_OBJ(GF_SCOM_HANDLE *handle) : SCOM(handle, SCOM_TYPE_UNKNOWN_25, SCOM_EXEC_UNKNOWN_0, 1) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create();
};

static_assert(sizeof(SCOM_DESTROY_MAP_OBJ) == 0x20, "");

class SCOM_CREATE_MAP_OBJ : public SCOM {
public:
  SCOM_CREATE_MAP_OBJ(GF_SCOM_HANDLE *handle, u32 mapJump, u32 map) : SCOM(handle, SCOM_TYPE_CREATE_MAP_OBJ, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(mapJump), unknown20(map) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(u32 mapJump, u32 map);

  u32 unknown1c; // Inferred role: map jump; original member name unknown.
  u32 unknown20; // Inferred role: map; original member name unknown.
};

static_assert(offsetof(SCOM_CREATE_MAP_OBJ, unknown1c) == 0x1c, "");
static_assert(offsetof(SCOM_CREATE_MAP_OBJ, unknown20) == 0x20, "");
static_assert(sizeof(SCOM_CREATE_MAP_OBJ) == 0x28, "");

class SCOM_RELOAD_BDAT : public SCOM {
public:
  SCOM_RELOAD_BDAT(GF_SCOM_HANDLE *handle) : SCOM(handle, SCOM_TYPE_UNKNOWN_30, SCOM_EXEC_UNKNOWN_0, 2) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create();
};

static_assert(sizeof(SCOM_RELOAD_BDAT) == 0x20, "");

class SCOM_RELOAD_TEXT : public SCOM {
public:
  SCOM_RELOAD_TEXT(GF_SCOM_HANDLE *handle) : SCOM(handle, SCOM_TYPE_UNKNOWN_31, SCOM_EXEC_UNKNOWN_0, 2) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(fw::LangType type);
};

static_assert(sizeof(SCOM_RELOAD_TEXT) == 0x20, "");

class SCOM_STOP_LAYER : public SCOM {
public:
  SCOM_STOP_LAYER(GF_SCOM_HANDLE *handle, GF_OBJ_HANDLE *target, bool stop) : SCOM(handle, SCOM_TYPE_UNKNOWN_32, SCOM_EXEC_UNKNOWN_0, 1), unknown20(target), unknown28(stop) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(GF_OBJ_HANDLE *target, bool stop);

  GF_OBJ_HANDLE *unknown20; // Inferred role: target; original member name unknown.
  bool unknown28;           // Inferred role: stop; original member name unknown.
};

static_assert(offsetof(SCOM_STOP_LAYER, unknown20) == 0x20, "");
static_assert(offsetof(SCOM_STOP_LAYER, unknown28) == 0x28, "");
static_assert(sizeof(SCOM_STOP_LAYER) == 0x30, "");

class SCOM_SET_IDEA_POINT_FOR_DEBUG : public SCOM {
public:
  SCOM_SET_IDEA_POINT_FOR_DEBUG(GF_SCOM_HANDLE *handle, u32 driver, u32 idea, int point)
      : SCOM(handle, SCOM_TYPE_UNKNOWN_10, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(point), unknown20(driver), unknown24(idea) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(u32 driver, u32 idea, int point);

  int unknown1c; // Inferred role: point; original member name unknown.
  u32 unknown20; // Inferred role: driver; original member name unknown.
  u32 unknown24; // Inferred role: idea; original member name unknown.
};

static_assert(offsetof(SCOM_SET_IDEA_POINT_FOR_DEBUG, unknown1c) == 0x1c, "");
static_assert(offsetof(SCOM_SET_IDEA_POINT_FOR_DEBUG, unknown20) == 0x20, "");
static_assert(offsetof(SCOM_SET_IDEA_POINT_FOR_DEBUG, unknown24) == 0x24, "");
static_assert(sizeof(SCOM_SET_IDEA_POINT_FOR_DEBUG) == 0x28, "");

class SCOM_BATTLE_BGM : public SCOM {
public:
  SCOM_BATTLE_BGM(GF_SCOM_HANDLE *handle, u32 bgm) : SCOM(handle, SCOM_TYPE_UNKNOWN_62, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(bgm) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(u32 bgm);

  u32 unknown1c; // Inferred role: battle bgm; original member name unknown.
};

static_assert(offsetof(SCOM_BATTLE_BGM, unknown1c) == 0x1c, "");
static_assert(sizeof(SCOM_BATTLE_BGM) == 0x20, "");

class SCOM_COLI_CHAR_VALID : public SCOM {
public:
  SCOM_COLI_CHAR_VALID(GF_SCOM_HANDLE *handle, GF_OBJ_HANDLE *target, bool isEnable) : SCOM(handle, SCOM_TYPE_UNKNOWN_33, SCOM_EXEC_UNKNOWN_0, 1), unknown20(target), unknown28(isEnable) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(GF_OBJ_HANDLE *target, bool isEnable);

  GF_OBJ_HANDLE *unknown20; // Inferred role: target; original member name unknown.
  bool unknown28;           // Inferred role: enable; original member name unknown.
};

static_assert(offsetof(SCOM_COLI_CHAR_VALID, unknown20) == 0x20, "");
static_assert(offsetof(SCOM_COLI_CHAR_VALID, unknown28) == 0x28, "");
static_assert(sizeof(SCOM_COLI_CHAR_VALID) == 0x30, "");

class SCOM_CREATE_GMK_SET : public SCOM {
public:
  SCOM_CREATE_GMK_SET(GF_SCOM_HANDLE *handle, u32 gimmickSet) : SCOM(handle, SCOM_TYPE_UNKNOWN_39, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(gimmickSet) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(u32 gimmickSet);

  u32 unknown1c; // Inferred role: gimmick set; original member name unknown.
};

static_assert(offsetof(SCOM_CREATE_GMK_SET, unknown1c) == 0x1c, "");
static_assert(sizeof(SCOM_CREATE_GMK_SET) == 0x20, "");

class SCOM_DESTROY_GMK_SET : public SCOM {
public:
  SCOM_DESTROY_GMK_SET(GF_SCOM_HANDLE *handle, u32 gimmickSet) : SCOM(handle, SCOM_TYPE_UNKNOWN_38, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(gimmickSet) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(u32 gimmickSet);

  u32 unknown1c; // Inferred role: gimmick set; original member name unknown.
};

static_assert(offsetof(SCOM_DESTROY_GMK_SET, unknown1c) == 0x1c, "");
static_assert(sizeof(SCOM_DESTROY_GMK_SET) == 0x20, "");

class SCOM_FIELD_SKILL : public SCOM {
public:
  SCOM_FIELD_SKILL(GF_SCOM_HANDLE *handle, u32 fieldSkill, u32 blade);
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(u32 fieldSkill);
  static GF_SCOM_HANDLE *createWithBlade(u32 fieldSkill, u32 blade);

  u32 unknown1c; // Inferred role: field skill; original member name unknown.
  u32 unknown20; // Inferred role: blade, 0 for every blade of the party; original member name unknown.
};

static_assert(offsetof(SCOM_FIELD_SKILL, unknown1c) == 0x1c, "");
static_assert(offsetof(SCOM_FIELD_SKILL, unknown20) == 0x20, "");
static_assert(sizeof(SCOM_FIELD_SKILL) == 0x28, "");

class SCOM_REBUILD : public SCOM {
public:
  SCOM_REBUILD(GF_SCOM_HANDLE *handle, GF_OBJ_HANDLE *target) : SCOM(handle, SCOM_TYPE_UNKNOWN_58, SCOM_EXEC_UNKNOWN_0, 1), unknown20(target) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(GF_OBJ_HANDLE *target);

  GF_OBJ_HANDLE *unknown20; // Inferred role: target; original member name unknown.
};

static_assert(offsetof(SCOM_REBUILD, unknown20) == 0x20, "");
static_assert(sizeof(SCOM_REBUILD) == 0x28, "");

class SCOM_ADD_MERCENARIES_POINT : public SCOM {
public:
  SCOM_ADD_MERCENARIES_POINT(GF_SCOM_HANDLE *handle, u32 point) : SCOM(handle, SCOM_TYPE_UNKNOWN_59, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(point) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(u32 point);

  u32 unknown1c; // Inferred role: point; original member name unknown.
};

static_assert(offsetof(SCOM_ADD_MERCENARIES_POINT, unknown1c) == 0x1c, "");
static_assert(sizeof(SCOM_ADD_MERCENARIES_POINT) == 0x20, "");

class SCOM_SET_MERCENARIES_LEVEL : public SCOM {
public:
  SCOM_SET_MERCENARIES_LEVEL(GF_SCOM_HANDLE *handle, u32 level) : SCOM(handle, SCOM_TYPE_UNKNOWN_60, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(level) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(u32 level);

  u32 unknown1c; // Inferred role: level; original member name unknown.
};

static_assert(offsetof(SCOM_SET_MERCENARIES_LEVEL, unknown1c) == 0x1c, "");
static_assert(sizeof(SCOM_SET_MERCENARIES_LEVEL) == 0x20, "");

class SCOM_EXEC_MOUNT : public SCOM {
public:
  SCOM_EXEC_MOUNT(GF_SCOM_HANDLE *handle, GF_OBJ_HANDLE *target, OPTMNT mountType) : SCOM(handle, SCOM_TYPE_UNKNOWN_35, SCOM_EXEC_UNKNOWN_0, 1), unknown20(target), unknown28(mountType) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(GF_OBJ_HANDLE *target, OPTMNT mountType);

  GF_OBJ_HANDLE *unknown20; // Inferred role: target; original member name unknown.
  OPTMNT unknown28;         // Inferred role: mount type; original member name unknown.
};

static_assert(offsetof(SCOM_EXEC_MOUNT, unknown20) == 0x20, "");
static_assert(offsetof(SCOM_EXEC_MOUNT, unknown28) == 0x28, "");
static_assert(sizeof(SCOM_EXEC_MOUNT) == 0x30, "");

class SCOM_RESET_MOUNT : public SCOM {
public:
  SCOM_RESET_MOUNT(GF_SCOM_HANDLE *handle, GF_OBJ_HANDLE *target, OPTMNT mountType) : SCOM(handle, SCOM_TYPE_UNKNOWN_35, SCOM_EXEC_UNKNOWN_0, 1), unknown20(target), unknown28(mountType) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(GF_OBJ_HANDLE *target, OPTMNT mountType);

  GF_OBJ_HANDLE *unknown20; // Inferred role: target; original member name unknown.
  OPTMNT unknown28;         // Inferred role: mount type; original member name unknown.
};

static_assert(offsetof(SCOM_RESET_MOUNT, unknown20) == 0x20, "");
static_assert(offsetof(SCOM_RESET_MOUNT, unknown28) == 0x28, "");
static_assert(sizeof(SCOM_RESET_MOUNT) == 0x30, "");

class SCOM_VALID_LOCAL_SPEED : public SCOM {
public:
  SCOM_VALID_LOCAL_SPEED(GF_SCOM_HANDLE *handle, GF_OBJ_HANDLE *target, bool stop, f32 speed)
      : SCOM(handle, SCOM_TYPE_UNKNOWN_37, SCOM_EXEC_UNKNOWN_0, 1), unknown20(target), unknown28(speed), unknown2c(stop) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(GF_OBJ_HANDLE *target, bool stop, f32 speed);

  GF_OBJ_HANDLE *unknown20; // Inferred role: target; original member name unknown.
  f32 unknown28;            // Inferred role: speed; original member name unknown.
  bool unknown2c;           // Inferred role: stop; original member name unknown.
};

static_assert(offsetof(SCOM_VALID_LOCAL_SPEED, unknown20) == 0x20, "");
static_assert(offsetof(SCOM_VALID_LOCAL_SPEED, unknown28) == 0x28, "");
static_assert(offsetof(SCOM_VALID_LOCAL_SPEED, unknown2c) == 0x2c, "");
static_assert(sizeof(SCOM_VALID_LOCAL_SPEED) == 0x30, "");

class SCOM_LOADING : public SCOM {
public:
  SCOM_LOADING(GF_SCOM_HANDLE *handle, u32 type, bool isDisp) : SCOM(handle, SCOM_TYPE_UNKNOWN_28, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(type), unknown20(isDisp) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(u32 type, bool isDisp);

  u32 unknown1c;  // Inferred role: loading type; original member name unknown.
  bool unknown20; // Inferred role: display; original member name unknown.
};

static_assert(offsetof(SCOM_LOADING, unknown1c) == 0x1c, "");
static_assert(offsetof(SCOM_LOADING, unknown20) == 0x20, "");
static_assert(sizeof(SCOM_LOADING) == 0x28, "");

class SCOM_STOP_BATTLE : public SCOM {
public:
  SCOM_STOP_BATTLE(GF_SCOM_HANDLE *handle) : SCOM(handle, SCOM_TYPE_UNKNOWN_15, SCOM_EXEC_UNKNOWN_0, 1) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create();
};

static_assert(sizeof(SCOM_STOP_BATTLE) == 0x20, "");

class GfReqSmallCom : public mm::mtl::PtrSingleton<GfReqSmallCom> {
public:
  static GF_SCOM_HANDLE *addRequest(SCOM *scom);
  static GF_SCOM_HANDLE *addRequestParallel(SCOM *scom);
  GF_SCOM_HANDLE *allocate();
  bool isValid(GF_SCOM_HANDLE *handle);
  static bool isExistCommand(SCOM_TYPE type);
  static bool isExistCommand();
  static bool isExistCommandWithoutParallel();

  mm::mtl::FixedList<SCOM *, 1024> unknown08;   // Inferred role: commands; original member name unknown.
  mm::mtl::FixedList<SCOM *, 1024> unknown4828; // Inferred role: parallel commands; original member name unknown.
  mm::mtl::FixedList<SCOM *, 1024> unknown9048; // Inferred role: parallel commands added while updating; original member name unknown.
  s64 unknownd868;                              // Inferred role: next command handle; original member name unknown.
  bool unknownd870;                             // Inferred role: updating parallel commands; original member name unknown.
};

static_assert(offsetof(GfReqSmallCom, unknown08) == 0x08, "");
static_assert(offsetof(GfReqSmallCom, unknown4828) == 0x4828, "");
static_assert(offsetof(GfReqSmallCom, unknown9048) == 0x9048, "");
static_assert(offsetof(GfReqSmallCom, unknownd868) == 0xd868, "");
static_assert(offsetof(GfReqSmallCom, unknownd870) == 0xd870, "");

} // namespace gf
