#include "gf/menu/object/gf_menu_obj_party_status.h"

#include "types.h"

namespace gf {

// Inferred role: combo request call id; original name unknown.
constexpr u32 unknown001 = 0x3e;

void GfMenuObjPartyStatus::finalize() { GfMenuObject::finalize(); }

void GfMenuObjPartyStatus::update() { GfMenuObject::update(); }

void GfMenuObjPartyStatus::attachComboRequest(GfMenuCallContext *context) { unknown152(context, unknown001); }

} // namespace gf
