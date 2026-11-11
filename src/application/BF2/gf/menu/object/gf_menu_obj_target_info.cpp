#include "gf/menu/object/gf_menu_obj_target_info.h"
#include "gf/menu/gf_menu_types.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjTargetInfo::GfMenuObjTargetInfo(u32 handle) : GfMenuObject(handle) {}

GfMenuObjTargetInfo::~GfMenuObjTargetInfo() { ; }

void GfMenuObjTargetInfo::finalize() { GfMenuObject::finalize(); }

void GfMenuObjTargetInfo::update() { GfMenuObject::update(); }

void GfMenuObjTargetInfo::disp(bool disp) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x11));
  if (acc.isValid()) {
    acc.setDisp(disp);
  }
}

void GfMenuObjTargetInfo::dispAllEnemy(bool disp) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0xc));
  if (acc.isValid()) {
    acc.setDisp(disp);
  }
}

void GfMenuObjTargetInfo::dispAllOther(bool disp) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0xd));
  if (acc.isValid()) {
    acc.setDisp(disp);
  }
}

void GfMenuObjTargetInfo::dispAllSymbol(bool disp) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0xe));
  if (acc.isValid()) {
    acc.setDisp(disp);
  }
}

void GfMenuObjTargetInfo::startOpen(u32 handle, u32 object, int param0, int param1) {
  ui::UIObjectAcc acc(object);
  if (acc.isDuplicate()) {
    ui::EventData event;
    event.unknown00 = 0x100;
    event.unknown08 = param0;
    event.unknown0c = param1;
    event.unknown10 = acc.getDuplicateIndex();
    ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
  }
}

void GfMenuObjTargetInfo::EnemyListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    break;
  case GfMenuTypes::unknown003_256: {
    ui::UIObjectAcc enemy(acc.searchDuplicatedChild("LAY_ene_main", event.unknown10));
    if (enemy.isValid()) {
      enemy.setDisp(true);
    }
    break;
  }
  case GfMenuTypes::unknown003_257: {
    ui::UIObjectAcc enemy(acc.searchDuplicatedChild("LAY_ene_main", event.unknown10));
    if (enemy.isValid()) {
      enemy.setTerm();
      GfMenuObject::termCallContext(enemy.unknown10);
    }
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}
} // namespace gf
