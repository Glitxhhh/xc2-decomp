#include "gf/menu/object/gf_menu_obj_blade_name.h"

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x81;

void GfMenuObjBladeName::close() { unknown144(unknown001, GfMenuTypes::unknown003_34); }

void GfMenuObjBladeName::finalize() { GfMenuObject::finalize(); }

void GfMenuObjBladeName::open(GfMenuCallContext *context) {
  if (GfMenuObjUtil::checkCCStart(context)) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
    if (acc.isValid()) {
      ui::EventData event;
      event.unknown00 = GfMenuTypes::unknown003_33;
      GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
      GfMenuObject::startCallContext(context, unknown001, acc.unknown10);
    }
  }
}

void GfMenuObjBladeName::pause(GfMenuCallContext *context) {
  if (GfMenuObjUtil::checkCCNext(context, unknown001)) {
    unknown144(unknown001, 0x101);
  }
}

bool GfMenuObjBladeName::seqApperNormal() {
  ui::UIObjectAcc acc(unknown18, "IMG_bl_name_base");
  acc.setDisp(true);
  acc.startAnimation("common", false);
  return true;
}

bool GfMenuObjBladeName::seqApperRare() {
  ui::UIObjectAcc acc(unknown18, "IMG_bl_name_base");
  acc.setDisp(true);
  acc.startAnimation("rare", false);
  unknown002();
  return true;
}

bool GfMenuObjBladeName::seqApperName() {
  unknown002();
  return true;
}

bool GfMenuObjBladeName::seqLeave() {
  ui::UIObjectAcc acc(unknown18, "LAY_main");
  bool isEnd;
  if (!unknown2b8) {
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 2;
    param.unknown00 = 0.2f;
    param.unknown14 = 10;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    isEnd = false;
    unknown2b8 = true;
  } else if (!GfMenuObjUtil::isBusyCtrl(GfMenuObjUtil::getCtrlID(acc.unknown10))) {
    unknown2b8 = false;
    {
      ui::UIObjectAcc base(unknown18, "IMG_bl_name_base");
      base.setDisp(false);
    }
    acc.setDisp(false);
    GfMenuObject::termCallContext(acc.unknown10);
    isEnd = true;
  } else {
    isEnd = false;
  }
  return isEnd;
}

} // namespace gf
