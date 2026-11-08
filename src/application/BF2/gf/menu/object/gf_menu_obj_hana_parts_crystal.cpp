#include "gf/menu/object/gf_menu_obj_hana_parts_crystal.h"

#include "gf/game/gf_game_util_hana.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/list/gf_menu_id_list.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/util/gf_item_util.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_cursor_color.h"
#include "ui/list/ui_select_obj_list.h"

namespace gf {

GfMenuObjHanaPartsCrystal::GfMenuObjHanaPartsCrystal(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr), unknown48(nullptr), unknown50(nullptr), unknown58(nullptr) {}

GfMenuObjHanaPartsCrystal::~GfMenuObjHanaPartsCrystal() {
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown48);
  mm::mtl::safeRelease(unknown50);
  mm::mtl::safeRelease(unknown58);
  unknown60 = nullptr;
  unknown68 = nullptr;
}

void GfMenuObjHanaPartsCrystal::finalize() { GfMenuObject::finalize(); }

void GfMenuObjHanaPartsCrystal::update() { GfMenuObject::update(); }

u32 GfMenuObjHanaPartsCrystal::getCrystalItemCount(u32 item) { return GfItemUtil::getItemBoxCount(item); }

RESULT_HANA GfMenuObjHanaPartsCrystal::crystalParts(u32 type, u32 parts) {
  switch (type) {
  case 1:
  case 2:
  case 3:
  case 6:
  case 9:
    GfGameUtilHana::execConvertToEther(parts);
    break;
  }
  return RESULT_HANA_UNKNOWN_8;
}

void GfMenuObjHanaPartsCrystal::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjHanaPartsCrystal::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 1, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjHanaPartsCrystal::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 2, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

} // namespace gf
