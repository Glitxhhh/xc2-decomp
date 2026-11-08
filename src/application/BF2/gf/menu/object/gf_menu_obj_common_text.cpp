#include "gf/menu/object/gf_menu_obj_common_text.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_item.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_common_window_param.h"
#include "gf/menu/gf_menu_item_util.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_id_list.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/list/ui_list_info.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x64;

ui::UIListInfo<MenuItemInfo> *GfMenuObjCommonText::s_pItemList;
ui::UIListInfo<MenuID> *GfMenuObjCommonText::s_pSubMenuIDList;

void GfMenuObjCommonText::finalize() { GfMenuObject::finalize(); }

void GfMenuObjCommonText::update() { GfMenuObject::update(); }

void GfMenuObjCommonText::sendEvent(u32 handle, u32 type, u32 param, f32 delay) { unknown140(handle, type, param, delay); }

int GfMenuObjCommonText::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 1, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjCommonText::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 2, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

void GfMenuObjCommonText::close() { unknown143(unknown001, GfMenuTypes::unknown003_34); }

void GfMenuObjCommonText::open(GfMenuCallContext *context, u32 window, u32 param) {
  u8 *windowBdat = GfDataBdat::getFP(BDAT_MNU_CMN_WINDOW);
  if (windowBdat != nullptr) {
    u8 *textBdat = GfDataBdat::getFP(BDAT_MENU_CMNWINDOW);
    if (textBdat != nullptr) {
      MenuCommonWindowParam windowParam;
      u16 title = Bdat::getVal(windowBdat, "title", window).valueU16;
      if (title != 0) {
        windowParam.unknown00 = textBdat;
        windowParam.unknown08 = title;
      }
      u16 text = Bdat::getVal(windowBdat, "text", window).valueU16;
      if (text != 0) {
        windowParam.unknown10 = textBdat;
        windowParam.unknown18 = text;
      }
      u16 ok = Bdat::getVal(windowBdat, "select_ok_txt", window).valueU16;
      if (ok != 0) {
        windowParam.unknown20 = textBdat;
        windowParam.unknown28 = ok;
      }
      u16 cancel = Bdat::getVal(windowBdat, "select_cancel_txt", window).valueU16;
      if (cancel != 0) {
        windowParam.unknown30 = textBdat;
        windowParam.unknown38 = cancel;
      }
      windowParam.unknown3c = Bdat::getVal(windowBdat, "type", window).valueU8;
      windowParam.unknown40 = Bdat::getVal(windowBdat, "select", window).valueU8;
      windowParam.unknown44 = param;
      windowParam.unknown48 = 0;
      open(context, windowParam);
    }
  }
}

void GfMenuObjCommonText::openItem(GfMenuCallContext *context, u32 window, u32 item) {
  u8 *windowBdat = GfDataBdat::getFP(BDAT_MNU_CMN_WINDOW);
  if (windowBdat != nullptr) {
    u8 *textBdat = GfDataBdat::getFP(BDAT_MENU_CMNWINDOW);
    if (textBdat != nullptr) {
      MenuCommonWindowParam windowParam;
      windowParam.unknown00 = textBdat;
      windowParam.unknown08 = Bdat::getVal(windowBdat, "title", window).valueU16;
      {
        u8 itemType = GfDataItem::getItemType(item);
        ui::UIStr name;
        GfMenuItemUtil::getItemName(itemType, item, name);
        windowParam.unknown10 = name.getMsgFP();
        windowParam.unknown18 = name.getMsgID();
      }
      windowParam.unknown3c = Bdat::getVal(windowBdat, "type", window).valueU8;
      windowParam.unknown40 = Bdat::getVal(windowBdat, "select", window).valueU8;
      windowParam.unknown48 = 0;
      open(context, windowParam);
    }
  }
}

void GfMenuObjCommonText::openError(GfMenuCallContext *context, u32 error, u32 param) {
  u8 *errorBdat = GfDataBdat::getFP(BDAT_MNU_MSG_ERROR_INFO);
  if (errorBdat != nullptr) {
    u8 *textBdat = GfDataBdat::getFP(BDAT_MENU_ERROR_INFO_MS);
    if (textBdat != nullptr) {
      MenuCommonWindowParam windowParam;
      u16 name = Bdat::getVal(errorBdat, "name", error).valueU16;
      if (name != 0) {
        windowParam.unknown10 = textBdat;
        windowParam.unknown18 = name;
      }
      windowParam.unknown44 = param;
      windowParam.unknown48 = 1;
      open(context, windowParam);
    }
  }
}

void GfMenuObjCommonText::openMissionStop(GfMenuCallContext *context, u32 mission, u32 param) {
  u32 handle = getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    bool isTerm = ui::UIObjectAcc(handle).isTerm();
    if (context != nullptr && !isTerm) {
      u8 *windowBdat = GfDataBdat::getFP(BDAT_MNU_CMN_WINDOW);
      if (windowBdat != nullptr) {
        u16 text = Bdat::getVal(windowBdat, "text", mission).valueU16;
        if (text == 0) {
          context->abort();
        } else {
          u16 textId;
          {
            ui::UIStr str(GfDataBdat::getFP(BDAT_MENU_CMNWINDOW), text);
            textId = registString(str);
          }
          ui::EventData event;
          event.unknown00 = 0x21;
          event.unknown08 = param;
          event.unknown0c_u16 = textId;
          event.unknown0e = Bdat::getVal(windowBdat, "type", mission).valueU8;
          event.unknown10_u16 = Bdat::getVal(windowBdat, "select", mission).valueU8;
          event.unknown16 = 2;
          GfMenuObject::sendEvent(handle, event, 0.0f);
          startCallContext(context, unknown001, handle);
        }
      }
    }
  }
}

void GfMenuObjCommonText::openKizunaDialog(GfMenuCallContext *context, const OpenKizunaParam &param) {
  u32 handle = getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    bool isTerm = ui::UIObjectAcc(handle).isTerm();
    if (context != nullptr && !isTerm && GfDataBdat::getFP(BDAT_MNU_CMN_WINDOW) != nullptr) {
      u16 textId;
      {
        ui::UIStr str(param.unknown00, param.unknown08);
        textId = registString(str);
      }
      ui::EventData event;
      event.unknown0c = 0;
      event.unknown00 = 0x21;
      event.unknown08 = param.unknown0c;
      event.unknown0c_u16 = textId;
      event.unknown16 = 3;
      GfMenuObject::sendEvent(handle, event, 0.0f);
      startCallContext(context, unknown001, handle);
    }
  }
}

void GfMenuObjCommonText::openGetItem(GfMenuCallContext *context, const GfMenuItemList *items) {
  u32 handle = getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    bool isTerm = ui::UIObjectAcc(handle).isTerm();
    if (context != nullptr && !isTerm) {
      s_pItemList->clear();
      for (u32 i = 0; i < items->getSize(); i++) {
        s_pItemList->addContents(items->getContents(i));
      }
      ui::EventData event;
      event.unknown00 = 0x21;
      event.unknown16 = 4;
      GfMenuObject::sendEvent(handle, event, 0.033333335f);
      startCallContext(context, unknown001, handle);
    }
  }
}

void GfMenuObjCommonText::openSubMenu(GfMenuCallContext *context, const GfMenuIDList *list) {
  u32 handle = getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    bool isTerm = ui::UIObjectAcc(handle).isTerm();
    if (context != nullptr && !isTerm) {
      s_pSubMenuIDList->clear();
      for (u32 i = 0; i < list->getSize(); i++) {
        s_pSubMenuIDList->addContents(list->getContents(i));
      }
      ui::EventData event;
      event.unknown00 = 0x21;
      event.unknown16 = 5;
      GfMenuObject::sendEvent(handle, event, 0.0f);
      startCallContext(context, unknown001, handle);
    }
  }
}

void GfMenuObjCommonText::openSelectItem(GfMenuCallContext *context, const GfMenuItemList *list) {
  u32 handle = getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    bool isTerm = ui::UIObjectAcc(handle).isTerm();
    if (context != nullptr && !isTerm) {
      s_pItemList->clear();
      for (u32 i = 0; i < list->getSize(); i++) {
        s_pItemList->addContents(list->getContents(i));
      }
      ui::EventData event;
      event.unknown00 = 0x21;
      event.unknown08 = 1;
      event.unknown16 = 5;
      GfMenuObject::sendEvent(handle, event, 0.0f);
      startCallContext(context, unknown001, handle);
    }
  }
}

void GfMenuObjCommonText::openOwnerChange(GfMenuCallContext *context, u32 driver, u32 other) {
  u32 handle = getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    bool isTerm = ui::UIObjectAcc(handle).isTerm();
    if (context != nullptr && !isTerm) {
      GfMenuReference::setReferenceDriverID(4, driver);
      GfMenuReference::setReferenceDriverID(5, other);
      ui::EventData event;
      event.unknown08_u16 = 0;
      event.unknown00 = 0x21;
      event.unknown16 = 7;
      GfMenuObject::sendEvent(handle, event, 0.0f);
      startCallContext(context, unknown001, handle);
    }
  }
}

void GfMenuObjCommonText::openNumSelect(GfMenuCallContext *context, const OpenNumSelectParam &param) {
  u32 handle = getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    bool isTerm = ui::UIObjectAcc(handle).isTerm();
    if (context != nullptr && !isTerm) {
      ui::EventData event;
      event.unknown0c = 0;
      event.unknown00 = 0x21;
      event.unknown08_u16 = param.unknown00;
      event.unknown0a = param.unknown04;
      event.unknown0c_u16 = param.unknown08;
      event.unknown10 = param.unknown0c;
      event.unknown16 = 8;
      GfMenuObject::sendEvent(handle, event, 0.0f);
      startCallContext(context, unknown001, handle);
    }
  }
}

} // namespace gf
