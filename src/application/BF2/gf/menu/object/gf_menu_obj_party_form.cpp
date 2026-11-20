#include "gf/menu/object/gf_menu_obj_party_form.h"

#include "gf/data/gf_data_driver.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/fixstr.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: animation of each selection state; original name unknown.
static const char *const unknown001[] = {"none", "select", "hold"};

// Inferred role: finds the background image of a party member slot; original name unknown.
static u32 unknown002(u32 handle, const char *format, u32 index) {
  mm::mtl::FixStr<32> name;
  name.format(format, index + 1, "bg");
  return ui::UIObjectAcc(handle).searchChild(name.c_str());
}

// Inferred role: finds the layout of a party member slot, the name formatted with the index plus one; original name unknown. Evidence: the same sequence (string,
// temporary UIObjectAcc, searchChild) is in DriverFormListener::reciveEvent (0x71004a7158), BladeFormListener::reciveEvent (three sites from 0x71004a77b4) and
// initialize (0x71004a6918).
static u32 unknown003(u32 handle, const char *format, u32 index) {
  mm::mtl::FixStr<32> name;
  name.format(format, index + 1);
  return ui::UIObjectAcc(handle).searchChild(name.c_str());
}

void GfMenuObjPartyForm::selectDriver(u32 handle, u32 index, u32 state) {
  ui::UIObjectAcc image(unknown002(handle, "IMG_driver%02d_%s", index));
  if (image.isValid()) {
    image.startAnimation(unknown001[state], false);
  }
}

void GfMenuObjPartyForm::selectBlade(u32 handle, u32 index, u32 state) {
  ui::UIObjectAcc image(unknown002(handle, "IMG_blade%02d_%s", index));
  if (image.isValid()) {
    image.startAnimation(unknown001[state], false);
  }
}

GfMenuObjPartyForm::GfMenuObjPartyForm(u32 handle) : GfMenuObject(handle) {}

GfMenuObjPartyForm::~GfMenuObjPartyForm() {}

void GfMenuObjPartyForm::finalize() { GfMenuObject::finalize(); }

void GfMenuObjPartyForm::update() { GfMenuObject::update(); }

void GfMenuObjPartyForm::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 1;
    param.unknown00 = 0.5f;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    break;
  }
  case 2: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 2;
    param.unknown14 = 1;
    param.unknown00 = 0.5f;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjPartyForm::DriverFormListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    GfMenuObject::setupInputSelection(acc.unknown10, 0, unknown28->unknown00.size());
    unknown28->unknownd0 = 0xffffffff;
    break;
  case 8: {
    u64 params = event.unknown08_u64;
    u32 index = params;
    u32 type = params >> 32;
    switch (type) {
    case 1:
      if (unknown0c == 0) {
        unknown28->unknownd0 = index;
        selectDriver(acc.unknown10, index, 2);
        unknown0c = 1;
      } else if (unknown0c == 1) {
        u32 selected = unknown28->unknownd0;
        if (selected == index) {
          GfMenuObjUtil::playSECommon(2);
          return;
        }
        swapDriver(unknown28, selected, index);
        selectDriver(acc.unknown10, unknown28->unknownd0, 0);
        unknown28->unknownd0 = 0xffffffff;
        unknown0c = 0;
      }
      break;
    case 2:
      if (unknown0c == 1) {
        u32 selected = unknown28->unknownd0;
        if (index == selected) {
          selectDriver(acc.unknown10, index, 1);
        } else {
          selectDriver(acc.unknown10, selected, 0);
        }
        unknown28->unknownd0 = 0xffffffff;
        unknown0c = 0;
      } else {
        GfMenuObject::returnFSSubLayer(acc.unknown10, 1);
      }
      break;
    case 3:
      GfMenuObject::closeFSLayer(acc.unknown10, true, true);
      break;
    case 9:
      if (unknown0c == 0) {
        mm::mtl::FixedVector<u16, 422> blades;
        bool hasBlade = GfDataDriver::getSetBlade(blades, unknown28->unknown00[static_cast<int>(index)].unknown00);
        if (hasBlade) {
          unknown28->unknownd0 = index;
          ui::EventData next;
          next.unknown00 = 0x21;
          GfMenuObject::sendEvent(acc.searchSibiling("LAY_blade"), next, 0.0f);
          GfMenuObject::disableInput(acc.unknown10);
          GfMenuObjUtil::playSECommonDecide();
          return;
        }
      }
      GfMenuObjUtil::playSECommon(2);
      return;
    }
    GfMenuObjUtil::playSECommonFromInput(type);
    break;
  }
  case 6: {
    u32 index = event.unknown08;
    u32 previous = event.unknown0c;
    ui::UIObjectAcc cursor(acc.unknown10, "IMG_dr_cursor");
    if (cursor.isValid()) {
      ui::UIObjectAcc driver(unknown003(acc.unknown10, "LAY_driver%02d", index));
      if (driver.isValid()) {
        GfMenuObjUtil::setDockPos(cursor.unknown10, driver.unknown10, 4, true);
        GfMenuObjUtil::addPos(cursor.unknown10, 0, -10);
        if (index != unknown28->unknownd0) {
          selectDriver(acc.unknown10, index, 1);
        }
        if (previous != 0xffffffff && previous != unknown28->unknownd0) {
          selectDriver(acc.unknown10, previous, 0);
        }
      }
    }
    break;
  }
  case 0x21:
    GfMenuObject::enableInput(acc.unknown10);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf
