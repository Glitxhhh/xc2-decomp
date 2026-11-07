#include "gf/menu/object/gf_menu_obj_title.h"

#include "gf/menu/object/gf_menu_obj_util.h"

namespace gf {
class GfMenuCallContext;

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x18;

bool GfMenuObjTitle::s_NoSaveData;

void GfMenuObjTitle::finalize() { GfMenuObject::finalize(); }

void GfMenuObjTitle::update() {
  unknown58.unknown003();
  GfMenuObject::update();
}

bool GfMenuObjTitle::isEnableNewGame() { return true; }

bool GfMenuObjTitle::isEnableNewGameAdv() { return false; }

bool GfMenuObjTitle::isEnableContinue() { return !s_NoSaveData; }

bool GfMenuObjTitle::isEnableOption() { return true; }

void GfMenuObjTitle::setDispMode(u32 handle, int mode) {
  if (mode == 0) {
    GfMenuObjUtil::setChildDisp(handle, "LAY_keywait", true);
    GfMenuObjUtil::setChildDisp(handle, "LAY_list", false);
  } else if (mode == 1) {
    GfMenuObjUtil::setChildDisp(handle, "LAY_keywait", false);
    GfMenuObjUtil::setChildDisp(handle, "LAY_list", true);
  } else {
    GfMenuObjUtil::setChildDisp(handle, "LAY_keywait", false);
    GfMenuObjUtil::setChildDisp(handle, "LAY_list", false);
  }
}

bool GfMenuObjTitle::attach(GfMenuCallContext *context) { return unknown151(context, unknown001); }
} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjTitle>(const mm::mtl::Delegate<bool()> *);
