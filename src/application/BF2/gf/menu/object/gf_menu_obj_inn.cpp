#include "gf/menu/object/gf_menu_obj_inn.h"

#include "gf/menu/object/gf_menu_obj_util.h"

namespace gf {

void GfMenuObjInn::finalize() { GfMenuObject::finalize(); }

void GfMenuObjInn::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjInn::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 1, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjInn::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 2, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

} // namespace gf
