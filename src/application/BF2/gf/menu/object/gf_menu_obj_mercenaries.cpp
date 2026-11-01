#include "gf/menu/object/gf_menu_obj_mercenaries.h"

#include "gf/menu/adapter/gf_menu_game_adapter.h"
#include "gf/menu/adapter/gf_menu_mercenaries_adapter.h"
#include "gf/menu/adapter/gf_menu_zone_adapter.h"
#include "gf/menu/gf_menu_fade.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_col4.h"
#include "ui/ui_object_acc.h"

namespace gf {

void GfMenuObjMercenaries::finalize() { GfMenuObject::finalize(); }

void GfMenuObjMercenaries::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjMercenaries::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 5, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjMercenaries::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 6, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

void GfMenuObjMercenaries::setupLocationSelect(ui::UIObjectAcc &acc) { GfMenuZoneAdapter::createFromReferenceZone(acc.searchChild("TXT_loc_select_name"), 0, false); }

void GfMenuObjMercenaries::setupLocationZone(ui::UIObjectAcc &acc, u16 zone) {
  GfMenuZoneAdapter::create(acc.searchChild("IMG_loc_flag_logo"), 2, zone, false);
  GfMenuZoneAdapter::create(acc.searchChild("IMG_loc_flag_dev_lv"), 3, zone, false);
  GfMenuZoneAdapter::create(acc.searchChild("LAY_loc_flag_notice"), 5, zone, false);
}

void GfMenuObjMercenaries::setupMission(ui::UIObjectAcc &acc) {
  GfMenuZoneAdapter::createFromReferenceZone(acc.searchChild("TXT_mis_location"), 0, false);
  GfMenuZoneAdapter::createFromReferenceZone(acc.searchChild("IMG_mis_flag_logo"), 2, false);
  GfMenuZoneAdapter::createFromReferenceZone(acc.searchChild("IMG_mis_flag_dev_lv"), 3, false);
}

void GfMenuObjMercenaries::setupMercenaries(ui::UIObjectAcc &acc) {
  GfMenuGameAdapter::create(acc.searchChild("TXT_root_mer_lv_num"), 0xb, false);
  ui::UIObjectAcc exp(acc.searchChild("IMG_root_mer_exp"));
  exp.setExtType(1);
  GfMenuGameAdapter::create(exp.unknown10, 0xc, false);
  GfMenuMercenariesAdapter::createFromReferenceTeam(acc.searchChild("TXT_root_select_unit_name"), 0, false);
  GfMenuMercenariesAdapter::createFromReferenceTeam(acc.searchChild("IMG_root_select_unit_symbol"), 2, false);
}

bool GfMenuObjMercenaries::seqRewardStart() {
  ui::UIObjectAcc reward(unknown18, "LAY_reward");
  u32 handle = reward.unknown10;
  GfMenuObjUtil::setChildDisp(handle, "LAY_reward_complete", false);
  GfMenuObjUtil::setChildDisp(handle, "LAY_reward_result", false);
  GfMenuObjUtil::setChildDisp(handle, "LAY_reward_notice", false);
  GfMenuFade::setFade(2, 30, mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  return true;
}

bool GfMenuObjMercenaries::seqRewardStart2() {
  ui::UIObjectAcc reward(unknown18, "LAY_reward");
  u32 handle = reward.unknown10;
  bool isEnd;
  if (GfMenuFade::isFading(2)) {
    isEnd = false;
  } else {
    reward.setDisp(true);
    reward.setAlpha(1.0f);
    GfMenuObjUtil::setChildDisp(handle, "LAY_reward_notice", true);
    ui::UIObjectAcc notice(handle, "LAY_reward_notice");
    notice.setAlpha(1.0f);
    GfMenuFade::setFade(2, 20, mm::Col4(0.0f, 0.0f, 0.0f, 0.0f));
    isEnd = true;
  }
  return isEnd;
}

bool GfMenuObjMercenaries::seqRewardStart3() {
  ui::UIObjectAcc reward(unknown18, "LAY_reward");
  u32 handle = reward.unknown10;
  bool isEnd;
  if (GfMenuFade::isFading(2)) {
    isEnd = false;
  } else {
    GfMenuObjOperationInfo::open(handle, 0, 0, 0);
    enableInput(handle);
    isEnd = true;
  }
  return isEnd;
}

bool GfMenuObjMercenaries::seqRewardComp2() {
  ui::UIObjectAcc reward(unknown18, "LAY_reward");
  bool isEnd;
  if (GfMenuObjUtil::isBusyCtrl(unknown378)) {
    isEnd = false;
  } else {
    GfMenuObjUtil::CtrlParam param;
    ui::UIObjectAcc complete(unknown18, "LAY_reward_complete");
    param.unknown08 = 0x80000;
    param.unknown0c = 1;
    param.unknown00 = 0.4f;
    param.unknown2c = 1.0f;
    unknown378 = GfMenuObjUtil::startCtrl(complete.unknown10, param, nullptr);
    isEnd = true;
  }
  return isEnd;
}

bool GfMenuObjMercenaries::seqRewardComp3() {
  ui::UIObjectAcc reward(unknown18, "LAY_reward");
  bool isEnd;
  if (GfMenuObjUtil::isBusyCtrl(unknown378)) {
    isEnd = false;
  } else {
    ui::UIObjectAcc complete(unknown18, "LAY_reward_complete");
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 0;
    param.unknown00 = 0.5f;
    unknown378 = GfMenuObjUtil::startCtrl(complete.unknown10, param, nullptr);
    isEnd = true;
  }
  return isEnd;
}

bool GfMenuObjMercenaries::seqRewardComp4() {
  ui::UIObjectAcc reward(unknown18, "LAY_reward");
  u32 handle = reward.unknown10;
  bool isEnd;
  if (GfMenuObjUtil::isBusyCtrl(unknown378)) {
    isEnd = false;
  } else {
    GfMenuObjUtil::CtrlParam param;
    ui::UIObjectAcc notice(unknown18, "LAY_reward_notice");
    param.unknown08 = 2;
    param.unknown00 = 0.5f;
    GfMenuObjUtil::startCtrl(notice.unknown10, param, nullptr);
    GfMenuObjUtil::setChildDisp(handle, "LAY_reward_result", true);
    ui::UIObjectAcc result(unknown18, "LAY_reward_result");
    param.unknown08 = 1;
    param.unknown00 = 0.5f;
    unknown378 = GfMenuObjUtil::startCtrl(result.unknown10, param, nullptr);
    isEnd = true;
  }
  return isEnd;
}

bool GfMenuObjMercenaries::seqRewardComp5() {
  ui::UIObjectAcc reward(unknown18, "LAY_reward");
  u32 handle = reward.unknown10;
  bool isEnd;
  if (GfMenuObjUtil::isBusyCtrl(unknown378)) {
    isEnd = false;
  } else {
    enableInput(handle);
    isEnd = true;
  }
  return isEnd;
}

} // namespace gf
