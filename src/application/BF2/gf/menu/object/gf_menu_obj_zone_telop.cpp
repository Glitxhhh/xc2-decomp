#include "gf/menu/object/gf_menu_obj_zone_telop.h"

#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_order_mgr.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: call id of the zone telop; original name unknown.
constexpr u32 unknown001 = 0x45;

GfMenuObjZoneTelop::GfMenuObjZoneTelop(u32 handle) : GfMenuObject(handle), unknown28(this), unknown188(false), unknown18c(0.0f) {}

GfMenuObjZoneTelop::~GfMenuObjZoneTelop() {}

void GfMenuObjZoneTelop::initialize() {
  ui::UIObjectAcc acc(unknown18);
  u32 main = acc.searchChild("LAY_main");
  if (ui::UIObjectAcc(main).isValid()) {
// __LINE__ must be 70 as in the original file: it is the line argument of operator new.
#line 70
    MainListener *listener = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) MainListener(this);
    listener->addRef();
    ui::UIEventManager::get()->registObjectListener(main, listener);
    if (listener != nullptr) {
      listener->release();
    }
    attachExternalCall(unknown001, main);
  }
  GfMenuObject::initialize();
}

void GfMenuObjZoneTelop::finalize() { GfMenuObject::finalize(); }

void GfMenuObjZoneTelop::update() {
  unknown28.unknown003();
  GfMenuObject::update();
}

bool GfMenuObjZoneTelop::seqFadeIn() {
  ui::UIObjectAcc acc(unknown18, "LAY_main");
  bool isEnd;
  if (!unknown188) {
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 1;
    param.unknown00 = 0.5f;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    isEnd = false;
    unknown188 = true;
  } else if (!GfMenuObjUtil::isBusyCtrl(GfMenuObjUtil::getCtrlID(acc.unknown10))) {
    isEnd = true;
    unknown188 = false;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjZoneTelop::seqFadeOut() {
  ui::UIObjectAcc acc(unknown18, "LAY_main");
  bool isEnd;
  if (!unknown188) {
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 2;
    param.unknown00 = unknown18c;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    isEnd = false;
    unknown188 = true;
  } else if (!GfMenuObjUtil::isBusyCtrl(GfMenuObjUtil::getCtrlID(acc.unknown10))) {
    unknown188 = false;
    termCallContext(acc.unknown10);
    isEnd = true;
    GfMenuOrderMgr::finishOrder(1);
  } else {
    isEnd = false;
  }
  return isEnd;
}

} // namespace gf
