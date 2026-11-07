#include "gf/menu/object/gf_menu_obj_dr_equip.h"

#include "types.h"
#include "ui/ui_object_acc.h"

namespace gf {
class GfMenuCallContext;

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x7b;

void GfMenuObjDrEquip::finalize() { GfMenuObject::finalize(); }

void GfMenuObjDrEquip::update() {
  unknown50.unknown003();
  GfMenuObject::update();
}

bool GfMenuObjDrEquip::attach(GfMenuCallContext *context) { return unknown153(context, unknown001); }

void GfMenuObjDrEquip::suspendInput() {
  GfMenuObject::disableFSSwitching();
  ui::UIObjectAcc acc(unknown18);
  GfMenuObject::disableInput(acc.searchChild("LAY_main"));
  GfMenuObject::disableInput(acc.searchChild("LAY_item"));
}

void GfMenuObjDrEquip::resumeInput() {
  GfMenuObject::enableFSSwitching();
  ui::UIObjectAcc acc(unknown18);
  GfMenuObject::enableInput(acc.searchChild("LAY_main"));
  GfMenuObject::enableInput(acc.searchChild("LAY_item"));
}

bool GfMenuObjDrEquip::seqStartOpen() {
  suspendInput();
  unknown2e0 = -1;
  return true;
}

bool GfMenuObjDrEquip::seqEndOpen() {
  resumeInput();
  return true;
}

bool GfMenuObjDrEquip::seqStartClose() {
  unknown2e0 = -1;
  return true;
}

bool GfMenuObjDrEquip::seqEndClose() {
  ui::UIObjectAcc acc(unknown18, "LAY_main");
  GfMenuObject::termCallContext(acc.unknown10);
  ui::UIObjectAcc main(unknown18, "LAY_main");
  main.setTerm();
  return true;
}

bool GfMenuObjDrEquip::seqAppearPhase1() { return unknown002(1); }

bool GfMenuObjDrEquip::seqLeavePhase1() { return unknown002(2); }

} // namespace gf
