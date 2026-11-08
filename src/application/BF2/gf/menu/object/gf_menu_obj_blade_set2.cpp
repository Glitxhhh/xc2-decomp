#include "gf/menu/object/gf_menu_obj_blade_set2.h"

#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_blade_list.h"
#include "gf/menu/list/gf_menu_driver_list.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/request/gf_req_scom.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"

namespace gf {

// Inferred role: layer close destination parameter; original name unknown.
struct unknown001 {
  u32 unknown00; // Inferred role: destination; original member name unknown.
};

// Inferred role: menu id; original name unknown.
constexpr u32 unknown002 = 0x1e;

GfMenuObjBladeSet2::GfMenuObjBladeSet2(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr), unknown48(nullptr), unknown50(nullptr), unknown58(0), unknown60(nullptr), unknown68(0),
      unknown78(false), unknown80(nullptr), unknown88(false), unknown8c(0), unknown90(0), unknown94(0), unknown98(0), unknowna0(this), unknown338(this) {}

GfMenuObjBladeSet2::~GfMenuObjBladeSet2() {
  mm::mtl::safeRelease(unknown80);
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown48);
  mm::mtl::safeRelease(unknown50);
  mm::mtl::safeRelease(unknown60);
}

void GfMenuObjBladeSet2::finalize() { GfMenuObject::finalize(); }

void GfMenuObjBladeSet2::update() {
  unknowna0.unknown003();
  unknown338.unknown003();
  GfMenuObject::update();
}

void GfMenuObjBladeSet2::sendEvent(u32 handle, u32 type, u32 param, f32 delay) { unknown140(handle, type, param, delay); }

int GfMenuObjBladeSet2::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::unknown002(handle);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjBladeSet2::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::unknown003(handle);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

void GfMenuObjBladeSet2::setCloseToFSClose() {
  unknown001 value;
  value.unknown00 = 2;
  GfMenuTypes::Param layerParam;
  layerParam.set(value);
  GfMenuFullScreen::registLayerParam(getMenuLayerID(unknown002), layerParam);
}

void GfMenuObjBladeSet2::setCloseToReturn() {
  unknown001 value;
  value.unknown00 = 1;
  GfMenuTypes::Param layerParam;
  layerParam.set(value);
  GfMenuFullScreen::registLayerParam(getMenuLayerID(unknown002), layerParam);
}

bool GfMenuObjBladeSet2::seqWaitCommand() { return !GfReqSmallCom::get()->isValid(unknown330); }

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuSequence<gf::GfMenuObjBladeSet2, 8>>(const mm::mtl::Delegate<bool()> *);
template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjBladeSet2>(const mm::mtl::Delegate<bool()> *);
