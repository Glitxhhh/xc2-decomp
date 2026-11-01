#include "gf/menu/object/gf_menu_obj_hana_custom.h"

#include "gf/menu/object/gf_menu_obj_util.h"

namespace gf {

void GfMenuObjHanaCustom::finalize() { GfMenuObject::finalize(); }

u32 GfMenuObjHanaCustom::convPartsId(u32 partsId) {
  if (partsId > 0xf) {
    return partsId - 7;
  }
  return partsId;
}

bool GfMenuObjHanaCustom::isExpandParts(u32 partsId) { return partsId - 9 < 6; }

void GfMenuObjHanaCustom::refreshPlanLine(ui::UIObjectAcc &) {}

void GfMenuObjHanaCustom::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjHanaCustom::setFadeIn(u32 handle, u32 unknown) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 1, unknown);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjHanaCustom::setFadeOut(u32 handle, u32 unknown) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 2, unknown);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

} // namespace gf
