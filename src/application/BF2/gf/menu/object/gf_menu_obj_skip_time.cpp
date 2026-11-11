#include "gf/menu/object/gf_menu_obj_skip_time.h"

#include "gf/field/gf_field_time.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/event/ui_event_data.h"
#include "ui/plugin/ui_object_time_plugin.h"
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjSkipTime::GfMenuObjSkipTime(u32 handle) : GfMenuObject(handle), unknown28(nullptr), unknown30(), unknown34() {}

GfMenuObjSkipTime::~GfMenuObjSkipTime() { mm::mtl::safeRelease(unknown28); }

void GfMenuObjSkipTime::finalize() { GfMenuObject::finalize(); }

void GfMenuObjSkipTime::update() { GfMenuObject::update(); }

void GfMenuObjSkipTime::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjSkipTime::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 1, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjSkipTime::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 2, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

void GfMenuObjSkipTime::rotHand(ui::UIObjectAcc &acc, u32 value) { acc.setRot(static_cast<f32>(value) * -0.2617994f); }

void GfMenuObjSkipTime::setTime(ui::UIObjectTimePlugin *plugin, GameTime &time) {
  plugin->setHour(time.unknown01_4);
  plugin->setMin(time.unknown00_6);
  plugin->setSec(time.unknown00_0);
}

void GfMenuObjSkipTime::refreshSelect(ui::UIObjectAcc &acc, u32 select) {
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < 2; i++) {
    name.format("IMG_tagbase@%02d", i + 1);
    ui::UIObjectAcc tag(acc.searchChild(name.c_str()));
    const char *color = select == i ? "txt_bl_index" : "txt_dr_index";
    tag.setImageIndex(select == i);
    name.format("TXT_sellect@%02d", i + 1);
    ui::UIObjectAcc text(acc.searchChild(name.c_str()));
    GfMenuObjUtil::setColMulandAdd(text.unknown10, color);
  }
}

void GfMenuObjSkipTime::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    GfMenuObjOperationInfo::add(acc.searchChild("LAY_skiptime_main"), 0, 0, 0);
    GfMenuObjOperationInfo::setGuideText(0x38, 0);
    GfMenuObjMainMenu2::setSubIndexText(0x17);
    setFadeIn(handle);
    break;
  case 3:
    if (event.unknown08 == 2) {
      GfMenuObjOperationInfo::remove(acc.searchChild("LAY_skiptime_main"), 0, 0, 0);
      acc.setDisp(false);
      acc.setTerm();
      GfMenuObject::returnFSSubLayer(unknown20);
    }
    break;
  case GfMenuTypes::unknown003_33:
    acc.setDisp(true);
    break;
  case GfMenuTypes::unknown003_34:
    setFadeOut(handle);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf
