#include "gf/menu/object/gf_menu_obj_help_hud.h"

#include "gf/menu/object/gf_menu_obj_util.h"
#include "types.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x84;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x101;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown003 = 0x102;

void GfMenuObjHelpHud::finalize() { GfMenuObject::finalize(); }

void GfMenuObjHelpHud::enable() { unknown144(unknown001, unknown002); }

void GfMenuObjHelpHud::disable() { unknown144(unknown001, unknown003); }

void GfMenuObjHelpHud::ctrlFadeOut(u32 handle) {
  GfMenuObjUtil::CtrlParam param;
  param.unknown08 = 2;
  param.unknown00 = 0.1f;
  param.unknown14 = 2;
  GfMenuObjUtil::startCtrl(handle, param, nullptr);
}

void GfMenuObjHelpHud::ctrlFadeIn(u32 handle) {
  GfMenuObjUtil::CtrlParam param;
  param.unknown08 = 1;
  param.unknown00 = 0.1f;
  GfMenuObjUtil::startCtrl(handle, param, nullptr);
}

} // namespace gf
