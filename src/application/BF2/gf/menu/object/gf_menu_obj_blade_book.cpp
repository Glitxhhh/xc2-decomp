#include "gf/menu/object/gf_menu_obj_blade_book.h"

#include "gf/menu/list/gf_menu_blade_list.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/list/ui_select_obj_list.h"

namespace gf {

GfMenuObjBladeBook::GfMenuObjBladeBook(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(this), unknown2d0(false), unknown2d8(nullptr), unknown2e0(0, 0), unknown2f0() {}

GfMenuObjBladeBook::~GfMenuObjBladeBook() {
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown28);
}

} // namespace gf
