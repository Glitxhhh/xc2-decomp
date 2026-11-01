#include "gf/menu/object/gf_menu_obj_bl_equip.h"

#include "gf/menu/object/gf_menu_obj_util.h"

namespace gf {

void GfMenuObjBlEquip::finalize() { GfMenuObject::finalize(); }

void GfMenuObjBlEquip::update() { GfMenuObject::update(); }

void GfMenuObjBlEquip::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjBlEquip::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 1, 1);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjBlEquip::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 2, 1);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

} // namespace gf
