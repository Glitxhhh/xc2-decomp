#include "gf/menu/object/gf_menu_obj_arts_palette.h"

#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/object/gf_menu_obj_blade_change.h"
#include "gf/menu/object/gf_menu_obj_special_gauge.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/fixstr.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_object_acc.h"

namespace gf {

constexpr u32 BATTLE_STATE_NORMAL = 0;
constexpr u32 BATTLE_STATE_UNKNOWN_1 = 1;

// Inferred role: range effect state and arts info display flag when the palette is reset; original name unknown.
static const GfMenuObjArtsPalette::MainListener::unknown006 unknown007 = {0, 1};

// Inferred role: ui event type; original name unknown.
constexpr u16 unknown003 = 0x10b;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown004 = 0x101;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown005 = 0x100;

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x27;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x10a;

GfMenuObjArtsPalette::GfMenuObjArtsPalette(u32 handle) : GfMenuObject(handle), unknown40(this), unknown2d0(this), unknown560(this), unknown808(this) {
  for (u32 i = 0; i < 3; i++) {
    unknown24[i] = -1;
  }
  unknown7f0[0] = &unknown40;
  unknown7f0[1] = &unknown2d0;
  unknown7f0[2] = &unknown560;
  for (u32 i = 0; i < 3; i++) {
    unknown30[i] = 0;
  }
}

void GfMenuObjArtsPalette::finalize() { GfMenuObject::finalize(); }

void GfMenuObjArtsPalette::push(unsigned int slot) { unknown149(unknown001, unknown002, slot); }

void GfMenuObjArtsPalette::startChainAttack() { unknown157(unknown001, unknown003, 1); }

void GfMenuObjArtsPalette::exitChainAttack() { unknown144(unknown001, unknown003); }

void GfMenuObjArtsPalette::close() { unknown145(unknown001, unknown004); }

void GfMenuObjArtsPalette::open() { unknown145(unknown001, unknown005); }

void GfMenuObjArtsPalette::pushReverseBtn(u32 button) { unknown149(unknown001, 0x10d, button); }

void GfMenuObjArtsPalette::reverse(bool isReverse) { unknown150(unknown001, 0x10c, isReverse); }

void GfMenuObjArtsPalette::dispInfo(bool isDisp) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid() && !acc.isTerm()) {
    acc.setDispChild(isDisp, "LAY_arts_info");
    GfMenuObjBladeChange::dispInfo(isDisp);
  }
}

GfMenuObjArtsPalette::~GfMenuObjArtsPalette() { ; }

void GfMenuObjArtsPalette::update() {
  unknown7f0[0]->unknown003();
  unknown7f0[1]->unknown003();
  unknown7f0[2]->unknown003();
  unknown808.unknown003();
  GfMenuObject::update();
}

void GfMenuObjArtsPalette::updateArtsIconDisp(u32 slot) {
  mm::mtl::FixStr<32> name;
  name.format("LAY_arts_icon@%02d", slot + 1);
  ui::UIObjectAcc icon(unknown18, name.c_str());
  if ((unknown30[slot] & 3) == 3) {
    icon.setMulColor("white");
  } else {
    icon.setMulColor("gray");
  }
}

void GfMenuObjArtsPalette::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 0x100:
    if (GfMenuManager::isBattleState(BATTLE_STATE_NORMAL)) {
      if (unknown10.unknown00 == 0) {
        GfMenuObjUtil::PresetCtrlParam param;
        param.unknown10 = 0;
        param.unknown00 = 0;
        param.unknown04 = 0;
        param.unknown0d = true;
        param.unknown08 = unknown0c;
        unknown0c = GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
        unknown10.unknown00 = 1;
        GfMenuObject::enableInput(acc.unknown10);
      }
      ui::UIObjectAcc range(acc.unknown10, "IMG_elem_range");
      range.startAnimation("loop", false);
      range.setDisp(true);
      unknown20->unknown808.unknown005();
    }
    break;
  case 0x101:
    if (unknown10.unknown00 == 1) {
      GfMenuObjUtil::PresetCtrlParam param;
      param.unknown00 = 0;
      param.unknown04 = 1;
      param.unknown0d = true;
      param.unknown08 = unknown0c;
      param.unknown10 = 10;
      unknown0c = GfMenuObjUtil::startPresetCtrl(acc.unknown10, param);
      unknown10.unknown00 = 0;
      GfMenuObject::disableInput(acc.unknown10);
      ui::UIObjectAcc range(acc.unknown10, "IMG_elem_range");
      range.stopAnimation();
      range.setDisp(false);
      unknown20->unknown808.unknown005();
    }
    break;
  case 0x10a: {
    u32 slot = event.unknown08;
    if (unknown10.unknown00 == 1) {
      if (GfMenuReference::isArtsPaletteEnable(slot) && GfMenuReference::getArtsPaletteInfo(slot).unknown04 == 1.0f) {
        GfMenuObjUtil::playSE(0x23);
        unknown20->unknown30[slot] |= 4;
      } else {
        GfMenuObjUtil::playSE(0x24);
      }
    }
    break;
  }
  case 0x10b:
    unknown20->ctrlPalletteDisp(event.unknown08 == 1, 0);
    break;
  case 0x10c: {
    int isReverse = event.unknown08;
    int ctrl = unknown20->ctrlPalletteDisp(isReverse == 1, 1);
    if (ctrl != -1) {
      GfMenuObject::hookCtrlEvent(acc.unknown10, ctrl);
    }
    if (isReverse == 1) {
      GfMenuObject::sendOpenEvent(acc.searchChild("LAY_reverse"), 0, 0.0f);
    } else {
      acc.setDispChild(true, "IMG_frame");
      GfMenuObject::sendCloseEvent(acc.searchChild("LAY_reverse"), 0, 0.0f);
    }
    GfMenuObjSpecialGauge::reverse(isReverse == 1);
    break;
  }
  case 0x10d:
    GfMenuObject::sendEvent(acc.searchChild("LAY_reverse"), event, 0.0f);
    break;
  case 0xd: {
    int type = event.unknown08;
    int step = event.unknown0c;
    u32 slot = event.unknown10;
    mm::mtl::FixStr<32> name;
    name.format("LAY_arts_icon@%02d", slot + 1);
    ui::UIObjectAcc icon(acc.unknown10, name.c_str());
    switch (step) {
    case 0: {
      name.format("LAY_recast@%02d", slot + 1);
      ui::UIObjectAcc recast(acc.unknown10, name.c_str());
      name.format("IMG_arts_eff@%02d", slot + 1);
      ui::UIObjectAcc effect(acc.unknown10, name.c_str());
      if (type == 1) {
        GfMenuObjUtil::playSE(0x22);
        recast.setDisp(false);
        if (effect.isValid() && unknown20->unknown24[slot] == -1) {
          effect.setDisp(true);
          unknown20->unknown7f0[slot]->unknown005();
          unknown20->unknown7f0[slot]->addAnimJob(effect.unknown10, "standbye");
        }
        unknown20->unknown30[slot] |= 1;
      } else {
        if ((unknown20->unknown30[slot] & 4) == 0) {
          effect.setDisp(false);
        } else {
          effect.startAnimation("select", false);
          unknown20->unknown30[slot] &= ~4;
        }
        recast.setDisp(true);
        unknown20->unknown7f0[slot]->unknown005();
        if (unknown20->unknown24[slot] != -1) {
          GfMenuObjUtil::stopCtrl(unknown20->unknown24[slot]);
          unknown20->unknown24[slot] = -1;
        }
        unknown20->unknown30[slot] &= ~1;
      }
      unknown20->updateArtsIconDisp(slot);
      break;
    }
    case 1:
      if (type == 5) {
        unknown20->unknown30[slot] |= 2;
      } else {
        unknown20->unknown30[slot] &= ~2;
      }
      unknown20->updateArtsIconDisp(slot);
      break;
    case 2:
      if (type == 5) {
        {
          ui::UIObjectAcc range(acc.unknown10, "IMG_elem_range");
          unknown20->unknown808.addAnimJob(range.unknown10, "start");
          unknown20->unknown808.addAnimJob(range.unknown10, "loop");
        }
        ui::UIObjectAcc rangeIcon(acc.unknown10, "IMG_elem_range_icon");
        GfMenuObjUtil::CtrlParam param;
        param.unknown08 = 0x10000000;
        param.unknown11 = true;
        param.unknown04 = 1;
        param.unknown50 = "mnu004_range_anim_elem";
        param.unknown58 = "start";
        param.unknown14 = 12;
        int ctrl = GfMenuObjUtil::startCtrl(rangeIcon.unknown10, param, nullptr);
        GfMenuObject::hookCtrlEvent(acc.unknown10, ctrl);
      } else {
        {
          ui::UIObjectAcc range(acc.unknown10, "IMG_elem_range");
          range.startAnimation("loop", false);
          unknown20->unknown808.unknown005();
        }
        ui::UIObjectAcc rangeIcon(acc.unknown10, "IMG_elem_range_icon");
        int ctrl = GfMenuObjUtil::getCtrlID(rangeIcon.unknown10);
        if (ctrl != -1) {
          GfMenuObjUtil::stopCtrl(ctrl);
        }
      }
      break;
    }
    break;
  }
  case 1:
    acc.setDisp(false);
    unknown0c = -1;
    unknown10 = unknown007;
    GfMenuObject::disableInput(acc.unknown10);
    break;
  case 3:
    if (event.unknown08 == 1) {
      ui::UIObjectAcc icon(acc.unknown10, "IMG_elem_range_icon");
      GfMenuObjUtil::CtrlParam param;
      param.unknown08 = 0x10000000;
      param.unknown50 = "mnu004_range_anim_elem";
      param.unknown58 = "loop";
      param.unknown11 = true;
      param.unknown10 = true;
      param.unknown14 = 8;
      GfMenuObjUtil::startCtrl(icon.unknown10, param, nullptr);
    } else if (event.unknown08 == 8) {
      acc.setDispChild(false, "IMG_frame");
    } else if (event.unknown08 == 10) {
      if (!GfMenuManager::isBattleState(BATTLE_STATE_UNKNOWN_1)) {
        unknown20->unknown30[0] &= ~4;
        unknown20->unknown30[1] &= ~4;
        unknown20->unknown30[2] &= ~4;
      }
    }
    break;
  case 8:
    if (event.unknown0c == 9) {
      int isDisp = unknown10.unknown04;
      GfMenuObjArtsPalette::dispInfo(isDisp == 0);
      unknown10.unknown04 = isDisp == 0;
    }
    break;
  case 0xc:
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuSequence<gf::GfMenuObjArtsPalette, 4>>(const mm::mtl::Delegate<bool()> *);
template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuSequence<gf::GfMenuObjArtsPalette, 8>>(const mm::mtl::Delegate<bool()> *);
