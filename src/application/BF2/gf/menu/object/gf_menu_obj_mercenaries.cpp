#include "gf/menu/object/gf_menu_obj_mercenaries.h"

#include "gf/menu/adapter/gf_menu_zone_adapter.h"
#include "gf/menu/object/gf_menu_obj_util.h"
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

} // namespace gf
