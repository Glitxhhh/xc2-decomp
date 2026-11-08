#include "gf/menu/object/gf_menu_obj_hana_submenu.h"

#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_char_select.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x71;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x101;

GfMenuObjHanaSubmenu::GfMenuObjHanaSubmenu(u32 handle) : GfMenuObject(handle), unknown28(nullptr), unknown30(0) {}

GfMenuObjHanaSubmenu::~GfMenuObjHanaSubmenu() { mm::mtl::safeRelease(unknown28); }

void GfMenuObjHanaSubmenu::finalize() { GfMenuObject::finalize(); }

void GfMenuObjHanaSubmenu::update() { GfMenuObject::update(); }

void GfMenuObjHanaSubmenu::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjHanaSubmenu::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 1, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjHanaSubmenu::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 2, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

void GfMenuObjHanaSubmenu::returnHanaSubMenu() { GF_MENU_REQUEST_EVENT(unknown001, unknown002); }

void GfMenuObjHanaSubmenu::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    GfMenuObjOperationInfo::add(acc.searchChild("LAY_sub_menu"), 0, 0, 0);
    GfMenuObjOperationInfo::setGuideText(10, 0);
    setFadeIn(handle);
    break;
  case 3:
    if (event.unknown08 == 2) {
      GfMenuObjOperationInfo::remove(acc.searchChild("LAY_sub_menu"), 0, 0, 0);
      acc.setDisp(false);
      acc.setTerm();
      GfMenuObjCharSelect::returnSubMenu();
    }
    break;
  case GfMenuTypes::unknown003_33:
    acc.setDisp(true);
    break;
  case GfMenuTypes::unknown003_34:
    setFadeOut(handle);
    break;
  case GfMenuTypes::unknown003_257:
    GfMenuObjOperationInfo::add(acc.searchChild("LAY_sub_menu"), 0, 0, 0);
    GfMenuObjOperationInfo::setGuideText(10, 0);
    GfMenuObjCharSelect::dispOnChar(1);
    unknown163(acc.searchChild("LAY_sub_menu"), GfMenuTypes::unknown003_258, 0);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}
} // namespace gf
