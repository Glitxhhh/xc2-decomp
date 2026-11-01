#include "gf/menu/object/gf_menu_obj_bl_weapon2.h"

#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_data_weapon.h"
#include "gf/data/gf_object_type.h"
#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "ui/ui_manager.h"

namespace gf {
class GfMenuCallContext;

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x68;

// Inferred role: menu id; original name unknown.
constexpr u32 unknown003 = 0x21;

// Inferred role: shop layer; original name unknown.
constexpr u32 unknown004 = 0x2d;

void GfMenuObjBlWeapon2::registOpenParam(const OpenParam &param) {
  GfMenuTypes::Param layerParam;
  unknown002 &data = layerParam.get<unknown002>();
  data.unknown00 = param.unknown00;
  data.unknown02 = param.unknown04;
  GfMenuFullScreen::registLayerParam(getMenuLayerID(unknown003), layerParam);
}

void GfMenuObjBlWeapon2::finalize() { GfMenuObject::finalize(); }

void GfMenuObjBlWeapon2::openForShop(u32 weapon) {
  OpenParam param;
  param.unknown00 = 1;
  param.unknown04 = weapon;
  registOpenParam(param);
  ui::UIManager::get()->createLayer(unknown004);
}

void GfMenuObjBlWeapon2::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjBlWeapon2::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 1, 1);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjBlWeapon2::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 2, 1);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

bool GfMenuObjBlWeapon2::isSameWeapon(u32 blade, u32 chip) {
  DataParamAcc acc(OBJECT_TYPE_BLADE, blade, GIMMICK_TYPE_NONE);
  u32 weapon = GfDataWeapon::getNewWeapon(acc.getEquipWeapon(-1, false), chip);
  return acc.getEquipWeapon(-1, false) == weapon;
}

bool GfMenuObjBlWeapon2::isDownWeapon(u32 blade, u32 chip) {
  DataParamAcc acc(OBJECT_TYPE_BLADE, blade, GIMMICK_TYPE_NONE);
  u32 rank = GfDataWeapon::getRank(acc.getEquipWeapon(-1, false));
  return GfDataWeapon::getRank(GfDataWeapon::getNewWeapon(acc.getEquipWeapon(-1, false), chip)) < rank;
}

bool GfMenuObjBlWeapon2::attach(GfMenuCallContext *context) { return unknown151(context, unknown001); }

} // namespace gf
