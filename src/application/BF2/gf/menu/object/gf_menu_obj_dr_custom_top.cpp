#include "gf/menu/object/gf_menu_obj_dr_custom_top.h"

#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/object/gf_menu_obj_common_jog.h"
#include "gf/menu/object/gf_menu_obj_dr_arts_set.h"
#include "gf/menu/object/gf_menu_obj_dr_equip.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "ui/ui_object_acc.h"

namespace gf {

void GfMenuObjDrCustomTop::finalize() { GfMenuObject::finalize(); }

void GfMenuObjDrCustomTop::update() {
  unknown58.unknown003();
  GfMenuObject::update();
}

void GfMenuObjDrCustomTop::suspendInput() {
  GfMenuObject::disableFSSwitching();
  if (unknown40.get() != nullptr) {
    GfMenuObjCommonJog::disable(unknown40.get());
  }
  ui::UIObjectAcc acc(unknown18);
  GfMenuObject::disableInput(acc.searchChild("LAY_main"));
  GfMenuObject::disableInput(acc.searchChild("LAY_dr_select"));
}

void GfMenuObjDrCustomTop::resumeInput() {
  GfMenuObject::enableFSSwitching();
  if (unknown40.get() != nullptr && unknown40.get()->isActive()) {
    GfMenuObjCommonJog::enable(unknown40.get());
  }
  ui::UIObjectAcc acc(unknown18);
  GfMenuObject::enableInput(acc.searchChild("LAY_main"));
  GfMenuObject::enableInput(acc.searchChild("LAY_dr_select"));
}

bool GfMenuObjDrCustomTop::seqStartOpen() {
  suspendInput();
  unknown2e8 = -1;
  return true;
}

bool GfMenuObjDrCustomTop::seqAppearPhase1() {
  if (unknown2e8 == -1) {
    ui::UIObjectAcc acc(unknown18, "LAY_main");
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 1;
    param.unknown00 = 0.25f;
    unknown2e8 = GfMenuObjUtil::startCtrl(acc.searchChild("IMG_bg"), param, nullptr);
  }
  if (GfMenuObjUtil::isBusyCtrl(unknown2e8)) {
    return false;
  }
  unknown2e8 = -1;
  return true;
}

bool GfMenuObjDrCustomTop::seqAppearPhase2() {
  if (unknown2e8 == -1) {
    ui::UIObjectAcc acc(unknown18, "LAY_index");
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown10 = 0;
    param.unknown00 = 1;
    param.unknown04 = 0;
    unknown2e8 = GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
  }
  if (GfMenuObjUtil::isBusyCtrl(unknown2e8)) {
    return false;
  }
  unknown2e8 = -1;
  return true;
}

bool GfMenuObjDrCustomTop::seqAppearPhase4() {
  if (unknown2e8 == -1) {
    ui::UIObjectAcc acc(unknown18, "LAY_main");
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 1;
    param.unknown00 = 0.25f;
    unknown2e8 = GfMenuObjUtil::startCtrl(acc.searchChild("LAY_driver"), param, nullptr);
  }
  if (GfMenuObjUtil::isBusyCtrl(unknown2e8)) {
    return false;
  }
  unknown2e8 = -1;
  return true;
}

bool GfMenuObjDrCustomTop::seqEndOpen() {
  resumeInput();
  return true;
}

bool GfMenuObjDrCustomTop::seqStartAddLayer() {
  suspendInput();
  unknown2e8 = -1;
  return true;
}

bool GfMenuObjDrCustomTop::seqAddLayerPhase3_DrEquip() { return GfMenuObjDrEquip::attach(unknown50); }

bool GfMenuObjDrCustomTop::seqAddLayerPhase3_DrArtsSet() { return GfMenuObjDrArtsSet::attach(unknown50); }

bool GfMenuObjDrCustomTop::seqAddLayerPhase4() { return unknown50->isTerm(); }

} // namespace gf
