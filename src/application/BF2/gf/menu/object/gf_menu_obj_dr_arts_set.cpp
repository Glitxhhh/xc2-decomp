#include "gf/menu/object/gf_menu_obj_dr_arts_set.h"

#include "gf/menu/adapter/gf_menu_weapon_type_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/ctrl/ui_ctrl_slide_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x5b;

GfMenuObjDrArtsSet::GfMenuObjDrArtsSet(u32 handle) : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown48(nullptr), unknownc8(nullptr) {}

GfMenuObjDrArtsSet::~GfMenuObjDrArtsSet() {
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown30);
  unknown38 = nullptr;
  unknown40 = nullptr;
  mm::mtl::safeRelease(unknown48);
  mm::mtl::safeRelease(unknownc8);
}

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

void GfMenuObjDrArtsSet::setupWpnType(ui::UIObjectAcc &acc, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number) {
  GfMenuWeaponTypeAdapter::createFromReferenceDriverWpnType(acc.searchChild("TXT_cate_name"), 0, 0, number, 0, false);
  GfMenuWeaponTypeAdapter::createFromReferenceDriverWpnType(acc.searchChild("TXT_cate_wp_num"), 2, 0, number, 0, true);
}

bool GfMenuObjDrArtsSet::attach(GfMenuCallContext *context) { return unknown153(context, unknown001); }

void GfMenuObjDrArtsSet::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    GfMenuObjUtil::setChildDisp(handle, "LAY_arts_detail", false);
    unknown163(handle, GfMenuTypes::unknown003_33, 0);
    break;
  case 2:
    GfMenuObjOperationInfo::close();
    GfMenuObject::termCallContext(handle);
    acc.setDisp(false);
    acc.setTerm();
    break;
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObject::returnFSSubLayer(handle, 2);
    }
    break;
  case GfMenuTypes::unknown003_33:
    setFadeIn(handle);
    unknown163(acc.searchChild("LAY_category"), GfMenuTypes::unknown003_33, 0);
    break;
  case GfMenuTypes::unknown003_34:
    GfMenuObjOperationInfo::close();
    setFadeOut(handle);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf
