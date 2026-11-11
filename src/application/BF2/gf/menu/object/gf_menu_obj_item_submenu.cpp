#include "gf/menu/object/gf_menu_obj_item_submenu.h"

#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/plugin/ui_object_dock_plugin.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x6e;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x101;

GfMenuObjItemSubmenu::GfMenuObjItemSubmenu(u32 handle) : GfMenuObject(handle), unknown2c(0) {}

GfMenuObjItemSubmenu::~GfMenuObjItemSubmenu() { ; }

void GfMenuObjItemSubmenu::initialize() {
  ui::UIObjectAcc acc(unknown18);
  u32 main = acc.searchChild("LAY_main");
// __LINE__ must be 81 as in the original file: it is the line argument of operator new.
#line 81
  MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  mainListener->addRef();
  ui::UIEventManager::get()->registObjectListener(main, mainListener);
  if (mainListener != nullptr) {
    mainListener->release();
  }
  attachExternalCall(unknown001, main);
  u32 itemSubmenu = acc.searchChild("LAY_item_submenu");
// __LINE__ must be 87 as in the original file: it is the line argument of operator new.
#line 87
  SubmenuListener *submenuListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SubmenuListener(this);
  submenuListener->addRef();
  ui::UIEventManager::get()->registObjectListener(itemSubmenu, submenuListener);
  if (submenuListener != nullptr) {
    submenuListener->release();
  }
  GfMenuObject::initialize();
}

void GfMenuObjItemSubmenu::finalize() { GfMenuObject::finalize(); }

void GfMenuObjItemSubmenu::update() { GfMenuObject::update(); }

void GfMenuObjItemSubmenu::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjItemSubmenu::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::unknown002(handle);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjItemSubmenu::setFadeOut(u32 handle, bool unknown) {
  GfMenuObjUtil::PresetCtrlParam param;
  param.unknown04 = 1;
  param.unknown00 = 6;
  param.unknown10 = 1;
  if (unknown) {
    param.unknown0c = true;
  }
  int ctrl = GfMenuObjUtil::startPresetCtrl(handle, param);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

void GfMenuObjItemSubmenu::returnItemSubMenu() { GF_MENU_REQUEST_EVENT(unknown001, unknown002); }

void GfMenuObjItemSubmenu::setupSubmenu(ui::UIObjectAcc &acc) {
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < 2; i++) {
    name.format("IMG_it_slicon@%02d", i + 1);
    ui::UIObjectAcc icon(acc.searchChild(name.c_str()));
    icon.setImageIndex(i);
    name.format("LAY_it_sellectbase@%02d", i + 1);
    ui::UIObjectDockPlugin *plugin = ui::UIObjectDockPlugin::create(acc.searchChild(name.c_str()), 0, 0, icon.unknown10);
    plugin->unknown24 = 1;
    mm::mtl::safeRelease(plugin);
  }
}

void GfMenuObjItemSubmenu::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    GfMenuObjOperationInfo::add(acc.searchChild("LAY_item_submenu"), 0, 0, 0);
    setFadeIn(handle);
    break;
  case 2:
    setFadeOut(handle, true);
    break;
  case 3:
    if (event.unknown08 == 2) {
      GfMenuObjOperationInfo::remove(acc.searchChild("LAY_item_submenu"), 0, 0, 0);
      acc.setDisp(false);
      acc.setTerm();
    }
    break;
  case GfMenuTypes::unknown003_33:
    acc.setDisp(true);
    break;
  case GfMenuTypes::unknown003_34:
    setFadeOut(handle, false);
    break;
  case GfMenuTypes::unknown003_257:
    GfMenuObjOperationInfo::add(acc.searchChild("LAY_item_submenu"), 0, 0, 0);
    GfMenuObjOperationInfo::setGuideText(0x16, 0);
    unknown163(acc.searchChild("LAY_item_submenu"), GfMenuTypes::unknown003_258, 0);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf
