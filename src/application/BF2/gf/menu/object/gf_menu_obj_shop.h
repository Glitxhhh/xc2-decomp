#pragma once
#include <stddef.h>

#include "gf/game/quest/gf_quest_task_param.h"
#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace gf {

class GfMenuCallContext;
class GfMenuIDList;
class GfMenuReferenceNumber;

class GfMenuObjShop : public GfMenuObject {
public:
  struct OpenParam {
    u32 unknown00; // Inferred role: shop; original member name unknown.
  };

  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjShop *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjShop *unknown20; // Inferred role: owner; original member name unknown.
  };

  static void open(GfMenuCallContext *context, const OpenParam &param);
  static void close(GfMenuCallContext *context);
  static u32 getSellItemTypeMax();
  static void dispBlade(bool isDisp);
  void initialize() override;
  void finalize() override;
  void update() override;
  void refreshItemList();
  void sendEnableEvent(u32 handle);
  void sendExitEvent(u32 handle);
  void sendCloseEvent(u32 handle);
  void sendOpenEvent(u32 handle, int value);
  void sendReturnEvent(u32 handle, int value);
  void addCallContextResult(u32 type, u32 value);
  void reqRefreshItemList();
  void openOrbError(u32 error);
  bool seqWaitFSClose();
  bool seqEndDialog();
  bool seqIntervalSleep();
  bool seqWaitLoadBlWeapon();
  bool seqWaitEndBlWeapon();
  bool seqStartSleepFade();
  bool seqWaitSleepFade();
  bool seqStartLevelUp();
  bool seqEnd();
  u32 getShopSubLayer(u32 handle);
  u32 getShopSubActLayer(u32 handle);
  void openNumSelect(u32 owner, u32 value, bool isFlag);
  bool getExcTaskQuestAdditionalValue(u32 id, u32 &value);
  bool seqEndRecipeIndexOpen();
  void setFilterIndex();
  static int getSpecialShop(u32 shop);
  static bool isShopWeapon(u32 shop);
  void setupExcItem();

  u32 unknown24; // Inferred role: shop id; original member name unknown.
  int unknown28; // Inferred role: shop kind; original member name unknown.
  u32 unknown2c; // Inferred role: shop icon; original member name unknown.
  u32 unknown30; // Inferred role: shop table id; original member name unknown.
  int unknown34; // Inferred role: special shop id; original member name unknown.
  u32 unknown38; // Inferred role: cleared when the shop opens; original member name unknown.
  u8 _3c[0x59 - 0x3c];
  bool unknown59; // Inferred role: item list refresh request; original member name unknown.
  u8 _5a[0x60 - 0x5a];
  mm::mtl::FixedVector<u32, 22> unknown60; // Inferred role: sell filters; original member name unknown.
  u32 unknownc0;                           // Inferred role: current sell filter index; original member name unknown.
  u8 _c4[0xd0 - 0xc4];
  u32 unknownd0; // Inferred role: number select owner; original member name unknown.
  u8 _d4[0xfc - 0xd4];
  int unknownfc; // Inferred role: orb recipe index type; original member name unknown.
  u8 _100[0x14c - 0x100];
  u32 unknown14c;           // Inferred role: orb item sort index; original member name unknown.
  GfMenuIDList *unknown150; // Inferred role: exchange task list; original member name unknown.
  u8 _158[0x168 - 0x158];
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown168[26]; // Inferred role: reference numbers shown by the texts; original member name unknown.
  u8 _238[0x240 - 0x238];
  bool unknown240; // Inferred role: cloud sea inn flag pending; original member name unknown.
  u8 _241[0x248 - 0x241];
  GfMenuSequence<GfMenuObjShop, 8> unknown248; // Inferred role: shop steps; original member name unknown.
  int unknown4d8;                              // Inferred role: sleep interval frames; original member name unknown.
  bool unknown4dc;                             // Inferred role: sleep fade started flag; original member name unknown.
  u8 _4dd[0x4e0 - 0x4dd];
  u32 unknown4e0; // Inferred role: call result type; original member name unknown.
  int unknown4e4; // Inferred role: call result value; original member name unknown.
  u8 _4e8[0x4f8 - 0x4e8];
  u32 unknown4f8; // Inferred role: dialog object; original member name unknown.
  u8 _4fc[0x548 - 0x4fc];
  QuestTaskParam unknown548; // Inferred role: linked exchange quest task; original member name unknown.
  int unknown568;            // Inferred role: exchange task index type; original member name unknown.
  u8 _56c[0x570 - 0x56c];
  GfMenuCallContext *unknown570; // Inferred role: blade weapon call context; original member name unknown.
  u8 _578[0x580 - 0x578];
};

static_assert(offsetof(GfMenuObjShop::MainListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjShop::MainListener) == 0x28, "");
static_assert(offsetof(GfMenuObjShop, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjShop, unknown2c) == 0x2c, "");
static_assert(offsetof(GfMenuObjShop, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjShop, unknown34) == 0x34, "");
static_assert(offsetof(GfMenuObjShop, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjShop, unknown14c) == 0x14c, "");
static_assert(offsetof(GfMenuObjShop, unknown150) == 0x150, "");
static_assert(offsetof(GfMenuObjShop, unknown168) == 0x168, "");
static_assert(offsetof(GfMenuObjShop, unknown548) == 0x548, "");
static_assert(offsetof(GfMenuObjShop, unknown568) == 0x568, "");
static_assert(offsetof(GfMenuObjShop, unknown59) == 0x59, "");
static_assert(offsetof(GfMenuObjShop, unknown60) == 0x60, "");
static_assert(offsetof(GfMenuObjShop, unknownc0) == 0xc0, "");
static_assert(offsetof(GfMenuObjShop, unknown248) == 0x248, "");
static_assert(offsetof(GfMenuObjShop, unknown4d8) == 0x4d8, "");
static_assert(offsetof(GfMenuObjShop, unknown4f8) == 0x4f8, "");
static_assert(offsetof(GfMenuObjShop, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjShop, unknownd0) == 0xd0, "");
static_assert(offsetof(GfMenuObjShop, unknownfc) == 0xfc, "");
static_assert(offsetof(GfMenuObjShop, unknown240) == 0x240, "");
static_assert(offsetof(GfMenuObjShop, unknown4dc) == 0x4dc, "");
static_assert(offsetof(GfMenuObjShop, unknown4e0) == 0x4e0, "");
static_assert(offsetof(GfMenuObjShop, unknown570) == 0x570, "");
static_assert(sizeof(GfMenuObjShop) == 0x580, "");

} // namespace gf
