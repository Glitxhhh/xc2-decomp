#include "gf/menu/object/gf_menu_obj_dr_kizuna_ring.h"

#include "gf/game/gf_game_util.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/reference_object.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjDrKizunaRing::GfMenuObjDrKizunaRing(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown38(false), unknown3c(0), unknown40(-1), unknown48(nullptr), unknown50(nullptr), unknown60(0), unknown68(this), unknown2f8(0),
      unknown300(nullptr), unknown308(nullptr), unknown310(0) {}

GfMenuObjDrKizunaRing::~GfMenuObjDrKizunaRing() {
  mm::mtl::safeRelease(unknown50);
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown48);
  mm::mtl::safeRelease(unknown300);
  mm::mtl::safeRelease(unknown308);
}

void GfMenuObjDrKizunaRing::finalize() { GfMenuObject::finalize(); }

void GfMenuObjDrKizunaRing::update() {
  unknown68.unknown003();
  GfMenuObject::update();
}

bool GfMenuObjDrKizunaRing::isLockPos(int index) { return index % 6 == 0; }

bool GfMenuObjDrKizunaRing::isScreenLR(u32 screen) { return screen < 3; }

void GfMenuObjDrKizunaRing::setupCircle(ui::UIObjectAcc &, u32) {}

void GfMenuObjDrKizunaRing::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjDrKizunaRing::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::unknown002(handle);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjDrKizunaRing::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::unknown003(handle);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

bool GfMenuObjDrKizunaRing::seqWait() {
  ui::UIObjectAcc acc(unknown18);
  ui::UIObjectAcc scale(acc.searchChild("LAY_scale"));
  enableInput(scale.unknown10);
  return true;
}

bool GfMenuObjDrKizunaRing::seqExecSkill() {
  u32 driver = GfMenuReference::getReferenceDriverID(0);
  GfGameUtil::execDriverSkillLevelUp(driver, GfMenuReference::getReferenceNumber(0), GfMenuReference::getReferenceNumber(1), GfMenuReference::getReferenceNumber(2) != 0);
  return true;
}

bool GfMenuObjDrKizunaRing::seqCircleAnime() {
  ui::UIObjectAcc acc(unknown18);
  ui::UIObjectAcc main(acc.searchChild("LAY_dr_main"));
  u32 driver = GfMenuReference::getReferenceDriverID(0);
  u32 level = unknown001(driver, GfMenuReference::getReferenceNumber(2) != 0);
  ui::UIObjectAcc effect(main.searchChild("IMG_ring_eff"));
  bool isEnd;
  if (unknown2f8 == 0) {
    effect.startAnimation(level == 1 ? "lineb" : "linec", false);
    GfMenuObjUtil::playSE(16);
    isEnd = false;
    unknown2f8++;
  } else if (!effect.isPlayingAnimation()) {
    isEnd = true;
    unknown2f8 = 0;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjDrKizunaRing::seqUnlockAnime() {
  ui::UIObjectAcc acc(unknown18);
  ui::UIObjectAcc main(acc.searchChild("LAY_dr_main"));
  ui::UIObjectAcc lock(main.searchChild("IMG_lock_open"));
  bool isEnd;
  if (unknown2f8 == 0) {
    u32 driver = GfMenuReference::getReferenceDriverID(0);
    const char *name = unknown001(driver, GfMenuReference::getReferenceNumber(2) != 0) == 1 ? "lock2" : "lock3";
    lock.startAnimation("skill_open", false);
    lock.setDisp(true);
    mm::Rect<s16> rect;
    main.getLayoutRect(name, rect);
    mm::Pnt<s16> center;
    center.x = rect.x + rect.width / 2;
    center.y = rect.y + rect.height / 2;
    lock.setPosCenter(center);
    GfMenuObjUtil::playSE(15);
    isEnd = false;
    unknown2f8++;
  } else if (!lock.isPlayingAnimation()) {
    isEnd = true;
    unknown2f8 = 0;
  } else {
    isEnd = false;
  }
  return isEnd;
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuSequence<gf::GfMenuObjDrKizunaRing, 8>>(const mm::mtl::Delegate<bool()> *);
template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjDrKizunaRing>(const mm::mtl::Delegate<bool()> *);
