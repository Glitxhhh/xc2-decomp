#include "gf/menu/object/gf_menu_obj_main_submenu.h"

#include <string.h>

#include "gf/data/gf_data_util.h"
#include "gf/game/gf_game_manager.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/reference_object.h"
#include "ui/event/ui_event_data.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjMainSubmenu::GfMenuObjMainSubmenu(u32 handle) : GfMenuObject(handle), unknown24(0), unknown28(0), unknown2c(0), unknown30(nullptr), unknown64(true), unknown68(nullptr), unknown70(-1) {
  memset(unknown74, 0xff, sizeof(unknown74));
}

GfMenuObjMainSubmenu::~GfMenuObjMainSubmenu() {
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown68);
}

void GfMenuObjMainSubmenu::finalize() { GfMenuObject::finalize(); }

void GfMenuObjMainSubmenu::update() { GfMenuObject::update(); }

bool GfMenuObjMainSubmenu::isEnableSkipTime() {
  if (GfDataUtil::getScenarioFlag() > 0xfbc && GfDataUtil::getScenarioFlag() < 0xfc9 && GfGameManager::getMapID() == 10) {
    return false;
  }
  return true;
}

void GfMenuObjMainSubmenu::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1: {
    ui::EventData sendData;
    sendData.unknown00 = GfMenuTypes::unknown003_33;
    GfMenuObject::sendEvent(acc.unknown10, sendData, 0.0f);
    break;
  }
  case 2: {
    ui::EventData sendData;
    sendData.unknown00 = GfMenuTypes::unknown003_34;
    sendData.unknown08 = 1;
    GfMenuObject::sendEvent(acc.unknown10, sendData, 0.0f);
    break;
  }
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObjMainMenu2::setCloseKeyEnable(true);
      GfMenuObject::enableInput(acc.searchChild("LAY_item_list"));
    } else if (event.unknown08 == 2) {
      acc.setTerm();
    }
    break;
  case GfMenuTypes::unknown003_33: {
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown00 = 6;
    param.unknown04 = 0;
    param.unknown10 = 1;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    break;
  }
  case GfMenuTypes::unknown003_34: {
    if (!unknown20->unknown64) {
      ui::EventData sendData;
      sendData.unknown00 = 3;
      sendData.unknown08 = 2;
      ui::UIManager::get()->requestObjectEvent(handle, sendData, 0.0f);
    } else {
      bool unknown = event.unknown08 == 1;
      GfMenuObjUtil::PresetCtrlParam param;
      param.unknown04 = 1;
      param.unknown00 = 6;
      param.unknown10 = 2;
      param.unknown0c = unknown;
      GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    }
    ui::EventData sendData;
    sendData.unknown00 = GfMenuTypes::unknown003_34;
    GfMenuObject::sendEvent(acc.searchChild("LAY_item_list"), sendData, 0.0f);
    break;
  }
  case 0x24: {
    GfMenuObject::disableInput(acc.searchChild("LAY_item_list"));
    GfMenuObjUtil::PresetCtrlParam param;
    param.unknown00 = 6;
    param.unknown04 = 1;
    param.unknown10 = 2;
    GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
    unknown20->unknown64 = false;
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf
