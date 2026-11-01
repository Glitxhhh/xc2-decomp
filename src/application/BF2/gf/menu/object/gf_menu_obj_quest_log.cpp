#include "gf/menu/object/gf_menu_obj_quest_log.h"

#include "gf/menu/gf_menu_flag.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/sound/gf_sound.h"
#include "types.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x20;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x101;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown003 = 0x104;

void GfMenuObjQuestLog::finalize() { GfMenuObject::finalize(); }

void GfMenuObjQuestLog::lockLogOpen() { GfMenuFlag::set1(0x20, 1); }

void GfMenuObjQuestLog::unlockLogOpen() { GfMenuFlag::set1(0x20, 0); }

bool GfMenuObjQuestLog::seqLogNextEnd() {
  ui::UIObjectAcc acc(unknown18, "LAY_log");
  enableInput(acc.unknown10);
  return true;
}

bool GfMenuObjQuestLog::seqLogStart() {
  ui::UIObjectAcc acc(unknown18, "LAY_log");
  enableInput(acc.unknown10);
  return true;
}

bool GfMenuObjQuestLog::seqTitleEndWait() {
  ui::UIObjectAcc acc(unknown18, "IMG_title_base");
  bool isEnd;
  if (acc.isPlayingAnimation()) {
    isEnd = false;
  } else {
    acc.setDisp(false);
    isEnd = true;
  }
  return isEnd;
}

bool GfMenuObjQuestLog::seqOrderWait() {
  ui::UIObjectAcc acc(unknown18, "TXT_order");
  return !GfMenuObjUtil::isBusyCtrl(GfMenuObjUtil::getCtrlID(acc.unknown10));
}

bool GfMenuObjQuestLog::seqTitleFadeInScenario() {
  unknown005("TXT_title_sub_scenario");
  return true;
}

bool GfMenuObjQuestLog::seqTitleFadeInText() {
  unknown005("TXT_title");
  if (!unknown818) {
    GfMenuObjUtil::playJingle(7);
  }
  return true;
}

bool GfMenuObjQuestLog::seqLogOut() {
  ui::UIObjectAcc acc(unknown18, "LAY_log");
  bool isEnd;
  if (!unknown810) {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown10 = 0;
    param.unknown04 = 1;
    param.unknown0d = true;
    param.unknown08 = GfMenuObjUtil::getCtrlID(acc.unknown10);
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    isEnd = false;
    unknown810 = true;
  } else if (!GfMenuObjUtil::isBusyCtrl(GfMenuObjUtil::getCtrlID(acc.unknown10))) {
    isEnd = true;
    unknown810 = false;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjQuestLog::seqTitleFadeOutScenario() {
  unknown004("TXT_title_sub_scenario");
  return true;
}

bool GfMenuObjQuestLog::seqTitleFadeInNormal() {
  unknown005("TXT_title_sub_normal");
  return true;
}

bool GfMenuObjQuestLog::seqTitleFadeOutNormal() {
  unknown004("TXT_title_sub_normal");
  return true;
}

bool GfMenuObjQuestLog::seqTitleFadeOutText() {
  unknown004(nullptr);
  return true;
}

void GfMenuObjQuestLog::changeActiveQuest() { unknown147(unknown001, "LAY_log", unknown002); }

void GfMenuObjQuestLog::updateTask() { unknown147(unknown001, "LAY_log", unknown003); }

void GfMenuObjQuestLog::closeLog() { unknown148(unknown001, "LAY_log", GfMenuTypes::unknown003_34); }

void GfMenuObjQuestLog::openLog() { unknown148(unknown001, "LAY_log", GfMenuTypes::unknown003_33); }

} // namespace gf
