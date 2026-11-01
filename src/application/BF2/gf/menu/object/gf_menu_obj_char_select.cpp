#include "gf/menu/object/gf_menu_obj_char_select.h"

#include "gf/game/gf_game_util.h"
#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/gf_menu_types.h"
#include "types.h"

namespace gf {
class GfMenuCallContext;

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x61;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x104;
// Inferred role: customize layer; original name unknown.
constexpr u16 unknown004 = 0x27;

void GfMenuObjCharSelect::finalize() { GfMenuObject::finalize(); }

void GfMenuObjCharSelect::registOpenCustomizeParam(const OpenCustomizeParam &param) {
  GfMenuTypes::Param layerParam;
  unknown003 &data = layerParam.get<unknown003>();
  data.unknown00 = param.unknown00;
  data.unknown04 = param.unknown04;
  GfMenuFullScreen::registLayerParam(unknown004, layerParam);
}

void GfMenuObjCharSelect::openBladeCustomize(u32 handle, u32 blade, u16 group) {
  OpenCustomizeParam param;
  param.unknown00 = 1;
  param.unknown04 = blade;
  registOpenCustomizeParam(param);
  changeFSSubLayer(handle, group, unknown004, true);
}

void GfMenuObjCharSelect::openDriverCustomize(u32 handle, u32 driver, u16 group) {
  OpenCustomizeParam param;
  param.unknown00 = 0;
  param.unknown04 = driver;
  registOpenCustomizeParam(param);
  changeFSSubLayer(handle, group, unknown004, true);
}

bool GfMenuObjCharSelect::seqSpHikariToHomura() {
  GfGameUtil::changeHikariCurrent(false);
  return true;
}

bool GfMenuObjCharSelect::seqSpHomuraToHikari() {
  GfGameUtil::changeHikariCurrent(true);
  return true;
}

void GfMenuObjCharSelect::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

void GfMenuObjCharSelect::returnSubMenu() { unknown142(unknown001, unknown002); }

bool GfMenuObjCharSelect::attach(GfMenuCallContext *context) { return unknown151(context, unknown001); }

} // namespace gf
