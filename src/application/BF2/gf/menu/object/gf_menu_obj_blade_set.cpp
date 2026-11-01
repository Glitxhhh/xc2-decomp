#include "gf/menu/object/gf_menu_obj_blade_set.h"

#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_mercenaries.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/object/gf_menu_obj_util.h"

namespace gf {

void GfMenuObjBladeSet::finalize() { GfMenuObject::finalize(); }

void GfMenuObjBladeSet::update() { GfMenuObject::update(); }

void GfMenuObjBladeSet::registOpenParam(const OpenParam &) {}

u32 GfMenuObjBladeSet::setEmptyTeamId() {
  u32 team = 0;
  for (u32 i = 1; i <= GfDataMercenaries::getTeamNum(); i++) {
    if (GfDataMercenaries::isTeamMemberEmpty(i)) {
      team = i;
      break;
    }
  }
  GfMenuReference::setReferenceTeamID(team);
  return team;
}

void GfMenuObjBladeSet::setMenuBtnStat(int menu, u32 blade, const GfMenuBladeList *list) {
  for (int i = 0; i < 3; i++) {
    int stat = 1;
    if (i == menu) {
      stat = isMenuBtnEnable(i, blade, list) ? 3 : 2;
    }
    GfMenuReference::setReferenceNumber(i + 1, stat);
  }
}

void GfMenuObjBladeSet::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjBladeSet::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 1, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjBladeSet::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 2, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

bool GfMenuObjBladeSet::checkBladeRelease(u32 blade) {
  if (GfDataBlade::isActivateDriver(blade)) {
    return false;
  }
  return !GfDataBlade::isActivateMercenaryTeam(blade);
}

} // namespace gf
