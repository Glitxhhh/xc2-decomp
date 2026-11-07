#include "gf/menu/object/gf_menu_obj_party_status.h"

#include <string.h>

#include "types.h"

namespace gf {

// Inferred role: combo request call id; original name unknown.
constexpr u32 unknown001 = 0x3e;

GfMenuObjPartyStatus::GfMenuObjPartyStatus(u32 handle) : GfMenuObject(handle), unknown38(-1), unknown3c(false) { memset(unknown30, 0xff, sizeof(unknown30)); }

GfMenuObjPartyStatus::~GfMenuObjPartyStatus() { ; }

void GfMenuObjPartyStatus::finalize() { GfMenuObject::finalize(); }

void GfMenuObjPartyStatus::update() { GfMenuObject::update(); }

void GfMenuObjPartyStatus::attachComboRequest(GfMenuCallContext *context) { unknown152(context, unknown001); }

} // namespace gf
