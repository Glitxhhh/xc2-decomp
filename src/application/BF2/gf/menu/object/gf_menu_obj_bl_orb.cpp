#include "gf/menu/object/gf_menu_obj_bl_orb.h"

#include "types.h"

namespace gf {
class GfMenuCallContext;

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x7d;

void GfMenuObjBlOrb::finalize() { GfMenuObject::finalize(); }

bool GfMenuObjBlOrb::attach(GfMenuCallContext *context) { return unknown153(context, unknown001); }

} // namespace gf
