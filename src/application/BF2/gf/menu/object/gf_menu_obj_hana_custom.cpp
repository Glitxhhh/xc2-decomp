#include "gf/menu/object/gf_menu_obj_hana_custom.h"

#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/list/gf_menu_id_list.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/reference_object.h"
#include "ui/list/ui_select_obj_list.h"

namespace gf {

GfMenuObjHanaCustom::GfMenuObjHanaCustom(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr), unknown80(0), unknown84(0), unknown88(nullptr), unknown90(nullptr), unknown98(nullptr),
      unknown0a0(nullptr), unknown0a8(this), unknown340(nullptr), unknown348(nullptr), unknown350(0) {
  for (int i = 0; i < 7; i++) {
    unknown48[i] = nullptr;
  }
}

GfMenuObjHanaCustom::~GfMenuObjHanaCustom() {
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown88);
  mm::mtl::safeRelease(unknown90);
  mm::mtl::safeRelease(unknown98);
  mm::mtl::safeRelease(unknown0a0);
  unknown340 = nullptr;
  unknown358 = nullptr;
  for (int i = 0; i < 7; i++) {
    mm::mtl::safeRelease(unknown48[i]);
  }
}

void GfMenuObjHanaCustom::finalize() { GfMenuObject::finalize(); }

void GfMenuObjHanaCustom::update() {
  unknown0a8.unknown003();
  GfMenuObject::update();
}

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

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjHanaCustom>(const mm::mtl::Delegate<bool()> *);
