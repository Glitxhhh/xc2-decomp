#include "gf/menu/object/gf_menu_obj_target_cursor.h"

#include "mm_mtl/delegate.h" // IWYU pragma: keep
#include "ui/ui_object_acc.h"

namespace gf {

void GfMenuObjTargetCursor::finalize() { GfMenuObject::finalize(); }

void GfMenuObjTargetCursor::disp(bool disp) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x12));
  if (acc.isValid()) {
    acc.setDisp(disp);
  }
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjTargetCursor>(const mm::mtl::Delegate<bool()> *);
