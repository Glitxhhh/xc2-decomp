#include "gf/menu/object/gf_menu_obj_pouch.h"

#include "gf/data/gf_data_item.h"
#include "gf/menu/adapter/gf_menu_enhance_adapter.h"
#include "gf/menu/adapter/gf_menu_item_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_reference_item.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjPouch::GfMenuObjPouch(u32 handle) : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr), unknown48(0) {}

GfMenuObjPouch::~GfMenuObjPouch() {
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(unknown40);
  unknown50 = nullptr;
}

void GfMenuObjPouch::finalize() { GfMenuObject::finalize(); }

void GfMenuObjPouch::update() { GfMenuObject::update(); }

void GfMenuObjPouch::setupPouch(ui::UIObjectAcc &) {}

void GfMenuObjPouch::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjPouch::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 0, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjPouch::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 1, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

void GfMenuObjPouch::updateItemList(GfMenuItemList *list) {
  list->clear();
  GfMenuItemList::ItemBoxSetup setup;
  setup.unknown28 = true;
  setup.unknown29 = true;
  setup.unknown14 = ItemType::FAVORITE;
  setup.unknown00.unknown08 = 10;
  list->setupFromBox(setup);
}

void GfMenuObjPouch::setupItemList(ui::UIObjectAcc &acc, GfMenuItemList *list) {
  mm::mtl::FixStr<32> name;
  ui::UIObjectAcc category(acc.searchChild("LAY_item_category"));
  category.setDisp(false);
  for (u32 i = 0; i < 10; i++) {
    name.format("TXT_item_name@%02d", i + 1);
    GfMenuItemAdapter *adapter = GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 0, list, i, false);
    name.format("LAY_item@%02d", i + 1);
    adapter->unknown24 = acc.searchChild(name.c_str());
    name.format("TXT_item_num@%02d", i + 1);
    GfMenuItemAdapter::createFromList(acc.searchChild(name.c_str()), 3, list, i, false);
  }
}

void GfMenuObjPouch::setupDescription(ui::UIObjectAcc &acc, mm::mtl::IntrusivePtr<GfMenuReferenceItem> &item) {
  GfMenuEnhanceAdapter::createFromReferenceItem(acc.searchChild("TXT_enhance"), 0, item.get(), true);
}

void GfMenuObjPouch::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    unknown163(handle, GfMenuTypes::unknown003_33, 0);
    break;
  case 2:
    unknown163(handle, GfMenuTypes::unknown003_34, 0);
    break;
  case 3:
    if (event.unknown08 == 1) {
      acc.setDisp(false);
      acc.setTerm();
      GfMenuObject::returnFSSubLayer(handle, 1);
    }
    break;
  case GfMenuTypes::unknown003_33:
    setFadeIn(handle);
    unknown163(acc.searchChild("LAY_pouch"), GfMenuTypes::unknown003_33, 0);
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

void GfMenuObjPouch::DescriptionListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  ui::UIObjectAcc owner(unknown20->unknown18);
  if (event.unknown00 == 1) {
    setupDescription(acc, unknown20->unknown50);
  }
  ui::UIObjectListener::reciveEvent(event, handle);
}
} // namespace gf
