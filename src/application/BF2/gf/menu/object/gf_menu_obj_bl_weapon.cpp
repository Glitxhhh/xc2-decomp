#include "gf/menu/object/gf_menu_obj_bl_weapon.h"

#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_data_weapon.h"
#include "gf/data/gf_object_type.h"
#include "types.h"

namespace gf {
class GfMenuCallContext;

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x7c;

void GfMenuObjBlWeapon::finalize() { GfMenuObject::finalize(); }

bool GfMenuObjBlWeapon::isSameWeapon(u32 blade, u32 chip) {
  DataParamAcc acc(OBJECT_TYPE_BLADE, blade, GIMMICK_TYPE_NONE);
  u32 weapon = GfDataWeapon::getNewWeapon(acc.getEquipWeapon(-1, false), chip);
  return acc.getEquipWeapon(-1, false) == weapon;
}

bool GfMenuObjBlWeapon::attach(GfMenuCallContext *context) { return unknown153(context, unknown001); }

} // namespace gf
