#include "gf/menu/object/gf_menu_obj_dr_arts_set.h"

#include "gf/menu/object/gf_menu_obj_util.h"

namespace gf {
class GfMenuCallContext;

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x5b;

void GfMenuObjDrArtsSet::finalize() { GfMenuObject::finalize(); }

void GfMenuObjDrArtsSet::update() { GfMenuObject::update(); }

void GfMenuObjDrArtsSet::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjDrArtsSet::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 0, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjDrArtsSet::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 1, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

bool GfMenuObjDrArtsSet::attach(GfMenuCallContext *context) { return unknown153(context, unknown001); }

} // namespace gf
