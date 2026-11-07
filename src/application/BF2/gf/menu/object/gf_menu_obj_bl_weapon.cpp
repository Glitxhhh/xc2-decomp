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

void GfMenuObjBlWeapon::update() {
  unknown50.unknown003();
  GfMenuObject::update();
}

void GfMenuObjBlWeapon::suspendInput() {
  GfMenuObject::disableFSSwitching();
  ui::UIObjectAcc acc(unknown18);
  GfMenuObject::disableInput(acc.searchChild("LAY_main"));
  GfMenuObject::disableInput(acc.searchChild("LAY_item_list"));
}

void GfMenuObjBlWeapon::resumeInput() {
  GfMenuObject::enableFSSwitching();
  ui::UIObjectAcc acc(unknown18);
  GfMenuObject::enableInput(acc.searchChild("LAY_main"));
  GfMenuObject::enableInput(acc.searchChild("LAY_item_list"));
}

bool GfMenuObjBlWeapon::seqStartOpen() {
  suspendInput();
  unknown2e0 = -1;
  return true;
}

bool GfMenuObjBlWeapon::seqEndOpen() {
  resumeInput();
  return true;
}

bool GfMenuObjBlWeapon::seqStartClose() {
  unknown2e0 = -1;
  return true;
}

bool GfMenuObjBlWeapon::seqEndClose() {
  ui::UIObjectAcc acc(unknown18, "LAY_main");
  GfMenuObject::termCallContext(acc.unknown10);
  ui::UIObjectAcc main(unknown18, "LAY_main");
  main.setTerm();
  return true;
}

bool GfMenuObjBlWeapon::seqAppearPhase1() { return unknown002(1); }

bool GfMenuObjBlWeapon::seqLeavePhase1() { return unknown002(2); }

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjBlWeapon>(const mm::mtl::Delegate<bool()> *);
