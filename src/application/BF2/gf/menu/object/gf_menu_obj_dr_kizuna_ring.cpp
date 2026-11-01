#include "gf/menu/object/gf_menu_obj_dr_kizuna_ring.h"

#include "gf/menu/object/gf_menu_obj_util.h"

namespace gf {

void GfMenuObjDrKizunaRing::finalize() { GfMenuObject::finalize(); }

bool GfMenuObjDrKizunaRing::isLockPos(int index) { return index % 6 == 0; }

bool GfMenuObjDrKizunaRing::isScreenLR(u32 screen) { return screen < 3; }

void GfMenuObjDrKizunaRing::setupCircle(ui::UIObjectAcc &, u32) {}

void GfMenuObjDrKizunaRing::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjDrKizunaRing::setFadeIn(u32 handle) {
  GfMenuObjUtil::PresetCtrlParam param;
  param.unknown00 = 6;
  param.unknown04 = 0;
  param.unknown10 = 1;
  int ctrl = GfMenuObjUtil::startPresetCtrl(handle, param);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjDrKizunaRing::setFadeOut(u32 handle) {
  GfMenuObjUtil::PresetCtrlParam param;
  param.unknown00 = 6;
  param.unknown04 = 1;
  param.unknown10 = 2;
  int ctrl = GfMenuObjUtil::startPresetCtrl(handle, param);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

} // namespace gf
