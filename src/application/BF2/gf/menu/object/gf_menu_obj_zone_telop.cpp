#include "gf/menu/object/gf_menu_obj_zone_telop.h"

#include "gf/menu/gf_menu_order_mgr.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "ui/ui_object_acc.h"

namespace gf {

void GfMenuObjZoneTelop::finalize() { GfMenuObject::finalize(); }

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
