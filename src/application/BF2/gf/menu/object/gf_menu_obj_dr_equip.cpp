#include "gf/menu/object/gf_menu_obj_dr_equip.h"

#include "types.h"

namespace gf {
class GfMenuCallContext;

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x7b;

void GfMenuObjDrEquip::finalize() { GfMenuObject::finalize(); }

bool GfMenuObjDrEquip::attach(GfMenuCallContext *context) { return unknown153(context, unknown001); }

} // namespace gf
