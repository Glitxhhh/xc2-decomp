#include "gf/menu/object/gf_menu_obj_dr_arts_set2.h"

#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/list/gf_menu_arts_list.h"
#include "gf/menu/list/gf_menu_blade_list.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_pnt.h"
#include "mm_mtl/reference_object.h"
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjDrArtsSet2::GfMenuObjDrArtsSet2(u32 handle)
    : GfMenuObject(handle), unknown0b8(nullptr), unknown0c0(nullptr), unknown0c8(nullptr), unknown0d0(-1), unknown0d4(-1), unknown0d8(nullptr), unknown0e0(false), unknown0e8(nullptr),
      unknown0f0(nullptr), unknown0f8(this), unknown258(false) {
  unknown0e8 = GfMenuBladeList::create();
  unknown0f0 = GfMenuItemList::create();
}

GfMenuObjDrArtsSet2::~GfMenuObjDrArtsSet2() {
  unknown0a0 = nullptr;
  unknown0a8 = nullptr;
  mm::mtl::safeRelease(unknown0f0);
  mm::mtl::safeRelease(unknown0e8);
  mm::mtl::safeRelease(unknown0b8);
  mm::mtl::safeRelease(unknown0c8);
  mm::mtl::safeRelease(unknown0c0);
  mm::mtl::safeRelease(unknown0d8);
}
void GfMenuObjDrArtsSet2::finalize() { GfMenuObject::finalize(); }

void GfMenuObjDrArtsSet2::update() {
  unknown0f8.unknown003();
  GfMenuObject::update();
}

void GfMenuObjDrArtsSet2::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjDrArtsSet2::setFadeIn(u32 handle, u32 dir, const char *child) {
  GfMenuObjUtil::CtrlParam param;
  param.unknown08 = 0x10000000;
  param.unknown50 = "cmn_fade_motion_lr";
  param.unknown58 = dir != 0 ? "fade_in_r_early" : "fade_in_l_early";
  param.unknown04 = 1;
  param.unknown11 = true;
  int ctrl = GfMenuObjUtil::startCtrl(handle, param, child);
  if (child != nullptr) {
    GfMenuObject::hookCtrlEvent(handle, ctrl);
  }
  return ctrl;
}

int GfMenuObjDrArtsSet2::setFadeOut(u32 handle, u32 dir, const char *child) {
  GfMenuObjUtil::CtrlParam param;
  param.unknown08 = 0x10000000;
  param.unknown50 = "cmn_fade_motion_lr";
  param.unknown58 = dir != 0 ? "fade_out_r_early" : "fade_out_l_early";
  param.unknown04 = 2;
  param.unknown11 = true;
  param.unknown14 = 10;
  int ctrl = GfMenuObjUtil::startCtrl(handle, param, child);
  if (child != nullptr) {
    GfMenuObject::hookCtrlEvent(handle, ctrl);
  }
  return ctrl;
}

void GfMenuObjDrArtsSet2::setFadeInBG(u32 handle) {
  GfMenuObjUtil::CtrlParam param;
  param.unknown08 = 1;
  param.unknown00 = GfMenuObjUtil::getCtrlMotionTime("cmn_fade_motion_lr", "fade_in_r_early");
  param.unknown04 = 1;
  param.unknown11 = true;
  GfMenuObjUtil::startCtrl(handle, param, nullptr);
}

void GfMenuObjDrArtsSet2::setFadeOutBG(u32 handle) {
  GfMenuObjUtil::CtrlParam param;
  param.unknown08 = 2;
  param.unknown00 = GfMenuObjUtil::getCtrlMotionTime("cmn_fade_motion_lr", "fade_in_r_early");
  param.unknown04 = 1;
  param.unknown11 = true;
  GfMenuObjUtil::startCtrl(handle, param, nullptr);
}

void GfMenuObjDrArtsSet2::moveRight(ui::UIObjectAcc &acc) {
  mm::Pnt<s16> pos;
  acc.getPos(pos);
  pos.x += 0x10;
  acc.setPos(pos);
}

void GfMenuObjDrArtsSet2::moveLeft(ui::UIObjectAcc &acc) {
  mm::Pnt<s16> pos;
  acc.getPos(pos);
  pos.x -= 0x10;
  acc.setPos(pos);
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjDrArtsSet2>(const mm::mtl::Delegate<bool()> *);
