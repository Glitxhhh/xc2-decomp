#include "gf/menu/object/gf_menu_obj_operation_info.h"

#include "gf/menu/gf_menu_types.h"
#include "types.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x47;

void GfMenuObjOperationInfo::finalize() { GfMenuObject::finalize(); }

void GfMenuObjOperationInfo::update() { GfMenuObject::update(); }

void GfMenuObjOperationInfo::close() { GF_MENU_REQUEST_EVENT(unknown001, GfMenuTypes::unknown003_34); }

void GfMenuObjOperationInfo::setDisp(bool isDisp) { unknown154(unknown001, isDisp); }

} // namespace gf
