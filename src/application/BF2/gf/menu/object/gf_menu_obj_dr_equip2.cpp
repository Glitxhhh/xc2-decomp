#include "gf/menu/object/gf_menu_obj_dr_equip2.h"

#include "gf/menu/object/gf_menu_obj_util.h"

namespace gf {

void GfMenuObjDrEquip2::finalize() { GfMenuObject::finalize(); }

void GfMenuObjDrEquip2::update() { GfMenuObject::update(); }

void GfMenuObjDrEquip2::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjDrEquip2::setFadeIn(u32 handle, u32 type) {
  int ctrl = -1;
  if (type == 0) {
    ctrl = GfMenuObjUtil::unknown002(handle);
  } else if (type == 1) {
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_in_l_early");
    param.unknown04 = 1;
    ctrl = GfMenuObjUtil::startCtrl(handle, param, nullptr);
  }
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjDrEquip2::setFadeOut(u32 handle, u32 type) {
  int ctrl = -1;
  if (type == 0) {
    ctrl = GfMenuObjUtil::unknown003(handle);
  } else if (type == 1) {
    GfMenuObjUtil::CtrlParam param;
    param.unknown004("fade_out_l_early");
    param.unknown14 = 10;
    param.unknown04 = 2;
    ctrl = GfMenuObjUtil::startCtrl(handle, param, nullptr);
  }
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

} // namespace gf
