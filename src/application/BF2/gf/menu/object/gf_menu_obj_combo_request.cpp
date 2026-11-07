#include "gf/menu/object/gf_menu_obj_combo_request.h"

#include "types.h"
#include "ui/ui_object_acc.h"

namespace gf {
class GfMenuCallContext;

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x5c;

void GfMenuObjComboRequest::finalize() { GfMenuObject::finalize(); }

void GfMenuObjComboRequest::update() {
  ui::UIObjectAcc(unknown18).setAlpha(0.0f);
  GfMenuObject::update();
}

void GfMenuObjComboRequest::attachComboRequest(GfMenuCallContext *context) { unknown152(context, unknown001); }

} // namespace gf
