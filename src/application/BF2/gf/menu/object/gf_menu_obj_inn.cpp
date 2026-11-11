#include "gf/menu/object/gf_menu_obj_inn.h"

#include "gf/data/gf_data_driver.h"
#include "gf/game/gf_game_party.h"
#include "gf/menu/adapter/gf_menu_char_data_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_fade.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_driver_list.h"
#include "gf/menu/object/gf_menu_obj_common_detail.h"
#include "gf/menu/object/gf_menu_obj_common_text.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_col4.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/ctrl/ui_ctrl_slide_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjInn::GfMenuObjInn(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr), unknown48(nullptr), unknown50(nullptr), unknown58(nullptr), unknown88(1), unknown98(false),
      unknown0a0(this) {}

GfMenuObjInn::~GfMenuObjInn() {
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown48);
  mm::mtl::safeRelease(unknown58);
  mm::mtl::safeRelease(unknown50);
}

bool GfMenuObjInn::isEnableLevelUp() {
  mm::mtl::FixedVector<u16, 16> drivers;
  GfPartySelect::getDriverList(drivers, GfPartySelect::LIST_TYPE_UNKNOWN_2, 0);
  for (u32 i = 0; i < drivers.size(); i++) {
    if (GfDataDriver::isEnableLevelUp(drivers[i])) {
      return true;
    }
  }
  return false;
}

void GfMenuObjInn::finalize() { GfMenuObject::finalize(); }

void GfMenuObjInn::update() {
  unknown0a0.unknown003();
  GfMenuObject::update();
}

void GfMenuObjInn::setupLvSelectAdapter(ui::UIObjectAcc &acc, ui::UISelectObjList *list) {
  mm::mtl::FixStr<32> name;
  name = "LAY_lv_select_num@01";
  GfMenuObjUtil::setChildDisp(acc.unknown10, name.c_str(), false);
  name = "LAY_lv_select_num@02";
  GfMenuObjUtil::setChildDisp(acc.unknown10, name.c_str(), false);
  name = "LAY_lv_select_num@03";
  GfMenuObjUtil::setChildDisp(acc.unknown10, name.c_str(), false);
  name = "TXT_lv_select_info_num@01";
  GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild(name.c_str()), 0x23, 0, true);
  name = "TXT_lv_select_info_num@02";
  GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild(name.c_str()), 0x15, 0, true);
  name = "TXT_lv_select_info_num@03";
  GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild(name.c_str()), 0x13, 0, true);
}

void GfMenuObjInn::detailOpen(GfMenuObjInn *object, ui::UIObjectAcc &acc, const char *layout, u32 driver) {
  object->unknown30->reset();
  GfMenuObjCommonDetail::OpenParam param;
  param.unknown00.push_back(0x10c);
  param.unknown1c = 0;
  param.unknown28 = true;
  param.unknown30 = 0;
  acc.getLayoutRect(layout, param.unknown20);
  GfMenuReference::setReferenceDriverID(0, driver);
  GfMenuObjCommonDetail::open(object->unknown30, param);
}

void GfMenuObjInn::setupLvUpAdapter(ui::UIObjectAcc &acc) {
  mm::mtl::FixStr<32> name;
  name.format("IMG_lv_up_bustup");
  GfMenuCharDataAdapter::createFromReferenceDriver(acc.searchChild(name.c_str()), 0x1c, 0, true);
}

void GfMenuObjInn::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjInn::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 1, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjInn::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 2, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

bool GfMenuObjInn::seqFadeOut() {
  GfMenuFade::setFade(2, 60, mm::Col4::black);
  return true;
}

bool GfMenuObjInn::seqFadeOutWait() {
  ui::UIObjectAcc acc(unknown18);
  bool isEnd;
  if (GfMenuFade::isFading(2)) {
    isEnd = false;
  } else {
    closeFSLayer(acc.unknown10, true, true);
    isEnd = true;
  }
  return isEnd;
}

void GfMenuObjInn::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(true);
    break;
  case GfMenuTypes::unknown003_33:
    break;
  case GfMenuTypes::unknown003_34:
    unknown20->unknown0a0.unknown005();
    unknown20->unknown0a0.unknown002(&GfMenuObjInn::seqFadeOut);
    unknown20->unknown0a0.unknown002(&GfMenuObjInn::seqFadeOutWait);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjInn::ManualListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  ui::UIObjectAcc owner(unknown20->unknown18);
  switch (event.unknown00) {
  case 1: {
    GfMenuObjUtil::setChildDisp(handle, "IMG_dr_cursor", true);
    GfMenuObjUtil::CursorParam param;
    param.unknown00 = acc.getParentHandle();
    param.unknown04 = handle;
    param.unknown08 = "LAY_dr@%02d";
    param.unknown1a = 1;
    param.unknown20.unknown18 = 5;
    unknown20->unknown40 = GfMenuObjUtil::createCursor(param);
    unknown20->unknown40->open(0);
    acc.setDisp(false);
    break;
  }
  case 6: {
    u32 index = event.unknown08;
    unknown20->unknown48->setIndex(index);
    u32 selected = unknown20->unknown48->getIndex(true);
    unknown20->unknown40->inputChange(selected);
    break;
  }
  case 8:
    switch (event.unknown0c) {
    case 1: {
      GfMenuDriverList *drivers = unknown20->unknown48;
      if (!GfDataDriver::isEnableLevelUp(drivers->getContents(drivers->getIndex(false)).unknown00)) {
        break;
      }
      if (unknown20->unknown88 != 2) {
        unknown20->unknown28->reset();
        GfMenuObjCommonText::open(unknown20->unknown28, 0xf, 0);
        GfMenuObject::setCallContextEventHandler(unknown20->unknown28, handle);
        GfMenuObject::disableInput(handle);
        break;
      }
      unknown164(handle, GfMenuTypes::unknown003_34);
      unknown163(owner.searchChild("LAY_lv_select"), GfMenuTypes::unknown003_33, 0);
      u32 index = unknown20->unknown48->getIndex(true);
      unknown163(owner.searchChild("LAY_dr_list"), 0x101, index);
      break;
    }
    case 2:
      unknown164(handle, GfMenuTypes::unknown003_34);
      unknown163(owner.searchChild("LAY_mode_select"), GfMenuTypes::unknown003_33, 0);
      break;
    }
    break;
  case GfMenuTypes::unknown003_33:
    GfMenuObject::setupInputSelectionFromList(handle, *unknown20->unknown48);
    GfMenuObject::enableInput(handle);
    acc.setDisp(true);
    break;
  case GfMenuTypes::unknown003_34:
    GfMenuObject::disableInput(handle);
    acc.setDisp(false);
    break;
  case 0x41:
    if (unknown20->unknown28 == nullptr) {
      break;
    }
    if (unknown20->unknown28->unknown0c == event.unknown08) {
      if (event.unknown10_u16 == 0) {
        unknown164(handle, GfMenuTypes::unknown003_34);
        unknown163(owner.searchChild("LAY_dr_list"), 0x103, 0);
        GfMenuDriverList *drivers = unknown20->unknown48;
        unknown20->unknown8c = drivers->getContents(drivers->getIndex(false)).unknown00;
        u32 maxLevel;
        GfDataDriver::getEnableLevel(unknown20->unknown90, maxLevel, unknown20->unknown8c);
        GfMenuReference::setReferenceDriverID(0, unknown20->unknown8c);
        unknown163(owner.searchChild("LAY_lv_up"), GfMenuTypes::unknown003_33, 0);
      } else {
        GfMenuObject::enableInput(handle);
      }
    }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjInn>(const mm::mtl::Delegate<bool()> *);
