#include "gf/menu/object/gf_menu_obj_party_status2.h"

#include <string.h>

#include "gf/menu/adapter/gf_menu_adapter.h"
#include "gf/menu/gf_menu_types.h"
#include "mm_mtl/reference_object.h"
#include "types.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x5d;

GfMenuObjPartyStatus2::GfMenuObjPartyStatus2(u32 handle) : GfMenuObject(handle), unknown24(false), unknown28(nullptr), unknown30(-1) { memset(unknown34, 0xff, sizeof(unknown34)); }

GfMenuObjPartyStatus2::~GfMenuObjPartyStatus2() { mm::mtl::safeRelease(unknown28); }

void GfMenuObjPartyStatus2::finalize() { GfMenuObject::finalize(); }

void GfMenuObjPartyStatus2::update() { GfMenuObject::update(); }

void GfMenuObjPartyStatus2::sendEvent(u32 handle, u32 type, u32 param) {
  if (handle != 0) {
    unknown140(handle, type, param, 0.0f);
  }
}

void GfMenuObjPartyStatus2::close() { GF_MENU_REQUEST_EVENT(unknown001, GfMenuTypes::unknown003_34); }

void GfMenuObjPartyStatus2::disp(bool isDisp) { unknown154(unknown001, isDisp); }

void GfMenuObjPartyStatus2::open() { GF_MENU_REQUEST_EVENT(unknown001, GfMenuTypes::unknown003_33); }

} // namespace gf
