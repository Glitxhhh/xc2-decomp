#include "gf/menu/object/gf_menu_obj_bl_custom_top.h"

#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/list/gf_menu_blade_list.h"
#include "gf/menu/object/gf_menu_obj_bl_orb.h"
#include "gf/menu/object/gf_menu_obj_bl_weapon.h"
#include "gf/menu/object/gf_menu_obj_blade_set.h"
#include "gf/menu/object/gf_menu_obj_common_jog.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_revolve_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjBlCustomTop::GfMenuObjBlCustomTop(u32 handle) : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr), unknown50(nullptr), unknown58(this) {}

GfMenuObjBlCustomTop::~GfMenuObjBlCustomTop() {
  mm::mtl::safeRelease(unknown48);
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown38);
}

void GfMenuObjBlCustomTop::finalize() { GfMenuObject::finalize(); }

void GfMenuObjBlCustomTop::update() {
  unknown58.unknown003();
  GfMenuObject::update();
}

void GfMenuObjBlCustomTop::suspendInput() {
  GfMenuObject::disableFSSwitching();
  if (unknown40 != nullptr) {
    GfMenuObjCommonJog::disable(unknown40);
  }
  ui::UIObjectAcc acc(unknown18);
  GfMenuObject::disableInput(acc.searchChild("LAY_main"));
  GfMenuObject::disableInput(acc.searchChild("LAY_bl_select"));
}

void GfMenuObjBlCustomTop::resumeInput() {
  GfMenuObject::enableFSSwitching();
  if (unknown40 != nullptr && unknown40->isActive()) {
    GfMenuObjCommonJog::enable(unknown40);
  }
  ui::UIObjectAcc acc(unknown18);
  GfMenuObject::enableInput(acc.searchChild("LAY_main"));
  GfMenuObject::enableInput(acc.searchChild("LAY_bl_select"));
}

bool GfMenuObjBlCustomTop::seqStartOpen() {
  suspendInput();
  unknown2e8 = -1;
  return true;
}

bool GfMenuObjBlCustomTop::seqAppearPhase1() {
  if (unknown2e8 == -1) {
    ui::UIObjectAcc acc(unknown18, "LAY_main");
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 1;
    param.unknown00 = 0.25f;
    unknown2e8 = GfMenuObjUtil::startCtrl(acc.searchChild("IMG_bg"), param, nullptr);
  }
  if (GfMenuObjUtil::isBusyCtrl(unknown2e8)) {
    return false;
  }
  unknown2e8 = -1;
  return true;
}

bool GfMenuObjBlCustomTop::seqAppearPhase2() {
  if (unknown2e8 == -1) {
    ui::UIObjectAcc acc(unknown18, "LAY_index");
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown10 = 0;
    param.unknown00 = 1;
    param.unknown04 = 0;
    unknown2e8 = GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
  }
  if (GfMenuObjUtil::isBusyCtrl(unknown2e8)) {
    return false;
  }
  unknown2e8 = -1;
  return true;
}

bool GfMenuObjBlCustomTop::seqAppearPhase4() {
  if (unknown2e8 == -1) {
    ui::UIObjectAcc acc(unknown18, "LAY_main");
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 1;
    param.unknown00 = 0.25f;
    unknown2e8 = GfMenuObjUtil::startCtrl(acc.searchChild("LAY_blade"), param, nullptr);
  }
  if (GfMenuObjUtil::isBusyCtrl(unknown2e8)) {
    return false;
  }
  unknown2e8 = -1;
  return true;
}

bool GfMenuObjBlCustomTop::seqEndOpen() {
  resumeInput();
  return true;
}

bool GfMenuObjBlCustomTop::seqStartAddLayer() {
  suspendInput();
  unknown2e8 = -1;
  return true;
}

bool GfMenuObjBlCustomTop::seqAddLayerPhase2() {
  GfMenuObject::enableFSSwitching();
  GfMenuObject::changeFSSubLayer(unknown18, 2, unknown2ec, true);
  if (unknown50 == nullptr) {
    unknown50 = GfMenuCallContext::create();
  }
  ui::UIObjectAcc acc(unknown18);
  GfMenuObject::enableInput(acc.searchChild("LAY_bl_select"));
  return true;
}

bool GfMenuObjBlCustomTop::seqAddLayerPhase3_BlWeapon() { return GfMenuObjBlWeapon::attach(unknown50); }

bool GfMenuObjBlCustomTop::seqAddLayerPhase3_BlOrb() { return GfMenuObjBlOrb::attach(unknown50); }

bool GfMenuObjBlCustomTop::seqAddLayerPhase4() { return unknown50->isTerm(); }

bool GfMenuObjBlCustomTop::seqEndAddLayer() {
  mm::mtl::safeRelease(unknown50);
  resumeInput();
  return true;
}

void GfMenuObjBlCustomTop::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    unknown20->unknown58.unknown002(&GfMenuObjBlCustomTop::seqStartOpen);
    unknown20->unknown58.unknown002(&GfMenuObjBlCustomTop::seqAppearPhase1);
    unknown20->unknown58.unknown002(&GfMenuObjBlCustomTop::seqAppearPhase2);
    unknown20->unknown58.unknown002(&GfMenuObjBlCustomTop::seqAppearPhase3);
    unknown20->unknown58.unknown002(&GfMenuObjBlCustomTop::seqAppearPhase4);
    unknown20->unknown58.unknown002(&GfMenuObjBlCustomTop::seqEndOpen);
    break;
  case 2: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 2;
    param.unknown00 = 0.25f;
    param.unknown14 = 1;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    break;
  }
  case 3:
    GfMenuObject::enableFSSwitching();
    GfMenuObject::returnFSSubLayer(acc.unknown10, 1);
    break;
  case 8:
    if (event.unknown0c == 2) {
      GfMenuObjUtil::CtrlParam param;
      param.unknown08 = 2;
      param.unknown00 = 0.25f;
      GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
      GfMenuObjCommonJog::close(unknown20->unknown40);
      unknown20->suspendInput();
    }
    break;
  default:
    if (event.unknown00 == 0x41) {
      u32 call = event.unknown08;
      u32 layer = event.unknown14;
      if (unknown20->unknown40 == nullptr || unknown20->unknown40->unknown0c != call || event.unknown10_u16 != 3) {
        break;
      }
      if ((layer & 0xffff) == 6) {
        GfMenuObjBladeSet::OpenParam param;
        param.unknown00 = 0;
        param.unknown04 = unknown20->unknown28->getContents(unknown20->unknown28->getIndex(false)).unknown00;
        GfMenuObjBladeSet::registOpenParam(param);
        GfMenuObject::changeFSSubLayer(acc.unknown10, 1, 6, true);
        GfMenuObjCommonJog::close(unknown20->unknown40);
      } else if ((layer & 0xffff) == 0x22) {
        GfMenuObject::changeFSSubLayer(acc.unknown10, 1, 0x22, true);
        GfMenuObjCommonJog::close(unknown20->unknown40);
      } else {
        unknown20->unknown2ec = layer;
        unknown20->unknown58.unknown002(&GfMenuObjBlCustomTop::seqStartAddLayer);
        unknown20->unknown58.unknown002(&GfMenuObjBlCustomTop::seqAddLayerPhase1);
        unknown20->unknown58.unknown002(&GfMenuObjBlCustomTop::seqAddLayerPhase2);
        if ((layer & 0xffff) == 0x24) {
          unknown20->unknown58.unknown002(&GfMenuObjBlCustomTop::seqAddLayerPhase3_BlWeapon);
        } else if ((layer & 0xffff) == 0x26) {
          unknown20->unknown58.unknown002(&GfMenuObjBlCustomTop::seqAddLayerPhase3_BlOrb);
        }
        unknown20->unknown58.unknown002(&GfMenuObjBlCustomTop::seqAddLayerPhase4);
        unknown20->unknown58.unknown002(&GfMenuObjBlCustomTop::seqAddLayerPhase5);
        unknown20->unknown58.unknown002(&GfMenuObjBlCustomTop::seqEndAddLayer);
      }
      break;
    }
  case 4:
  case 5:
  case 6:
  case 7:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjBlCustomTop>(const mm::mtl::Delegate<bool()> *);
