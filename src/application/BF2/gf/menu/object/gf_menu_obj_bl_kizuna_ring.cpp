#include "gf/menu/object/gf_menu_obj_bl_kizuna_ring.h"

#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"

namespace gf {
class GfMenuCallContext;

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x6a;

// Inferred role: menu id; original name unknown.
constexpr u32 unknown002 = 0x22;

void GfMenuObjBlKizunaRing::registOpenParam(const OpenParam &param) {
  GfMenuTypes::Param layerParam;
  OpenParam &data = layerParam.get<OpenParam>();
  data.unknown00 = param.unknown00;
  data.unknown04 = param.unknown04;
  GfMenuFullScreen::registLayerParam(getMenuLayerID(unknown002), layerParam);
}

void GfMenuObjBlKizunaRing::finalize() { GfMenuObject::finalize(); }

void GfMenuObjBlKizunaRing::openForMercenary(u32 handle, u32 blade, u16 group) {
  OpenParam param;
  param.unknown00 = 1;
  param.unknown04 = blade;
  registOpenParam(param);
  changeFSSubLayer(handle, group, getMenuLayerID(unknown002), true);
}

bool GfMenuObjBlKizunaRing::isLockPos(int index) { return index % 10 == 0; }

bool GfMenuObjBlKizunaRing::isScreenLR(u32 screen) { return screen < 4; }

void GfMenuObjBlKizunaRing::setupCircle(ui::UIObjectAcc &) {}

void GfMenuObjBlKizunaRing::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjBlKizunaRing::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 1, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjBlKizunaRing::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 2, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

bool GfMenuObjBlKizunaRing::attach(GfMenuCallContext *context) { return unknown151(context, unknown001); }

} // namespace gf
