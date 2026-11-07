#include "gf/menu/object/gf_menu_obj_bl_custom_top.h"

#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/object/gf_menu_obj_bl_orb.h"
#include "gf/menu/object/gf_menu_obj_bl_weapon.h"
#include "gf/menu/object/gf_menu_obj_common_jog.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "ui/ui_object_acc.h"

namespace gf {

void GfMenuObjBlCustomTop::finalize() { GfMenuObject::finalize(); }

void GfMenuObjBlCustomTop::update() {
  unknown58.unknown003();
  GfMenuObject::update();
}

void GfMenuObjBlCustomTop::suspendInput() {
  GfMenuObject::disableFSSwitching();
  if (unknown40.get() != nullptr) {
    GfMenuObjCommonJog::disable(unknown40.get());
  }
  ui::UIObjectAcc acc(unknown18);
  GfMenuObject::disableInput(acc.searchChild("LAY_main"));
  GfMenuObject::disableInput(acc.searchChild("LAY_bl_select"));
}

void GfMenuObjBlCustomTop::resumeInput() {
  GfMenuObject::enableFSSwitching();
  if (unknown40.get() != nullptr && unknown40.get()->isActive()) {
    GfMenuObjCommonJog::enable(unknown40.get());
  }
  ui::UIObjectAcc acc(unknown18);
  GfMenuObject::enableInput(acc.searchChild("LAY_main"));
  GfMenuObject::enableInput(acc.searchChild("LAY_bl_select"));
}

bool GfMenuObjBlCustomTop::seqStartOpen() {
  suspendInput();
  unknown2e8 = -1;
  return true;
}

bool GfMenuObjBlCustomTop::seqAppearPhase1() {
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

bool GfMenuObjBlCustomTop::seqAppearPhase2() {
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

bool GfMenuObjBlCustomTop::seqAppearPhase4() {
  if (unknown2e8 == -1) {
    ui::UIObjectAcc acc(unknown18, "LAY_main");
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 1;
    param.unknown00 = 0.25f;
    unknown2e8 = GfMenuObjUtil::startCtrl(acc.searchChild("LAY_blade"), param, nullptr);
  }
  if (GfMenuObjUtil::isBusyCtrl(unknown2e8)) {
    return false;
  }
  unknown2e8 = -1;
  return true;
}

bool GfMenuObjBlCustomTop::seqEndOpen() {
  resumeInput();
  return true;
}

bool GfMenuObjBlCustomTop::seqStartAddLayer() {
  suspendInput();
  unknown2e8 = -1;
  return true;
}

bool GfMenuObjBlCustomTop::seqAddLayerPhase3_BlWeapon() { return GfMenuObjBlWeapon::attach(unknown50); }

bool GfMenuObjBlCustomTop::seqAddLayerPhase3_BlOrb() { return GfMenuObjBlOrb::attach(unknown50); }

bool GfMenuObjBlCustomTop::seqAddLayerPhase4() { return unknown50->isTerm(); }

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjBlCustomTop>(const mm::mtl::Delegate<bool()> *);
