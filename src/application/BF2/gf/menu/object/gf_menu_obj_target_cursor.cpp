#include "gf/menu/object/gf_menu_obj_target_cursor.h"

#include "mm_mtl/delegate.h" // IWYU pragma: keep
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjTargetCursor::GfMenuObjTargetCursor(u32 handle)
    : GfMenuObject(handle), unknown24(0), unknown28(-1), unknown30(0), unknown38(0), unknown40(this), unknown2d0(this), unknown560(false), unknown564(0), unknown568(false) {}

GfMenuObjTargetCursor::~GfMenuObjTargetCursor() {}

void GfMenuObjTargetCursor::finalize() { GfMenuObject::finalize(); }

void GfMenuObjTargetCursor::disp(bool disp) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x12));
  if (acc.isValid()) {
    acc.setDisp(disp);
  }
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjTargetCursor>(const mm::mtl::Delegate<bool()> *);
