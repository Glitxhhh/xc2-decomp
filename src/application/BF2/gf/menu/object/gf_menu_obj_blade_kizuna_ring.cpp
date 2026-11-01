#include "gf/menu/object/gf_menu_obj_blade_kizuna_ring.h"

#include "gf/menu/adapter/gf_menu_char_data_adapter.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "types.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x5a;

void GfMenuObjBladeKizunaRing::finalize() { GfMenuObject::finalize(); }

void GfMenuObjBladeKizunaRing::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjBladeKizunaRing::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 1, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjBladeKizunaRing::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 2, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

void GfMenuObjBladeKizunaRing::close() { unknown142(unknown001, GfMenuTypes::unknown003_34); }

void GfMenuObjBladeKizunaRing::setupName(ui::UIObjectAcc &acc) { GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("TXT_name"), 2, 0, false); }

void GfMenuObjBladeKizunaRing::open() { unknown142(unknown001, GfMenuTypes::unknown003_33); }

} // namespace gf
