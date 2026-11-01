#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "gf/menu/gf_menu_object.h"

#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/gf_menu_types.h"
#include "ui/event/ui_event_data.h"
#include "ui/plugin/ui_object_number_plugin.h"
#include "ui/ui_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: full screen layer index; original name unknown.
constexpr u32 unknown001 = 1;
// Inferred role: attached call id; original name unknown.
constexpr u32 unknown002 = 0x5f;

void GfMenuObjMainMenu2::registOpenParam(const OpenParam &param) {
  GfMenuTypes::Param layerParam;
  layerParam.set(param);
  GfMenuFullScreen::registLayerParam(GfMenuFullScreen::getScreenLayerID(unknown001), layerParam);
}

void GfMenuObjMainMenu2::sendEvent(u32 handle, u32 type, u32 param) {
  if (handle != 0) {
    unknown140(handle, type, param, 0.0f);
  }
}

void GfMenuObjMainMenu2::setCloseKeyEnable(bool enable) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown002));
  if (acc.isValid()) {
    GfMenuObject::setInputActionEnable(acc.searchChild("LAY_close"), 3, enable);
  }
}

void GfMenuObjMainMenu2::closeCharChange() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown002));
  if (acc.isValid()) {
    ui::UIObjectAcc change(acc.searchChild("LAY_chr_change"));
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_34;
    ui::UIManager::get()->requestObjectEvent(change.unknown10, event, 0.0f);
  }
}

void GfMenuObjMainMenu2::openMainMenu() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown002));
  if (acc.isValid()) {
    ui::EventData event;
    event.unknown00 = 0x105;
    ui::UIManager::get()->requestObjectEvent(acc.unknown10, event, 0.0f);
  }
}

void GfMenuObjMainMenu2::setContentsIcon(ui::UIObjectNumberPlugin *plugin, u32 icon) { plugin->setNumber(icon); }

void GfMenuObjMainMenu2::disableCharChange() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown002));
  if (acc.isValid()) {
    ui::UIObjectAcc change(acc.searchChild("LAY_chr_change"));
    ui::EventData event;
    event.unknown00 = 0x109;
    ui::UIManager::get()->requestObjectEvent(change.unknown10, event, 0.0f);
    GfMenuObject::disableInput(change.unknown10);
  }
}

void GfMenuObjMainMenu2::setSubLayer(u32 layer) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown002));
  if (acc.isValid()) {
    sendEvent(acc.unknown10, 0x108, layer);
  }
}

void GfMenuObjMainMenu2::setGuideText(u32 text) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown002));
  if (acc.isValid()) {
    sendEvent(acc.unknown10, 0x10a, text);
  }
}

void GfMenuObjMainMenu2::dispCloseButton() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown002));
  if (acc.isValid()) {
    sendEvent(acc.searchChild("LAY_close"), 0x10d, 0);
  }
}

void GfMenuObjMainMenu2::execMapJump() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown002));
  if (acc.isValid()) {
    sendEvent(acc.unknown10, 0x10e, 0);
  }
}

} // namespace gf
