#include "gf/menu/object/gf_menu_obj_en_book.h"

#include "gf/menu/list/gf_menu_id_list.h"
#include "gf/menu/list/gf_menu_msg_list.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/list/ui_select_obj_list.h"

namespace gf {

GfMenuObjEnBook::GfMenuObjEnBook(u32 handle)
    : GfMenuObject(handle), unknown24(0), unknown28(0), unknown2c(0), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr), unknown48(nullptr), unknown50(nullptr), unknown58(nullptr),
      unknown60(nullptr), unknown68(nullptr), unknown70(nullptr), unknown78(nullptr), unknown80(nullptr), unknown88(0), unknown90(this), unknown320(false) {
  unknown40 = GfMenuMsgList::create();
  unknown50 = GfMenuMsgList::create();
  unknown60 = GfMenuIDList::create();
  unknown68 = GfMenuIDList::create();
}

GfMenuObjEnBook::~GfMenuObjEnBook() {
  mm::mtl::safeRelease(unknown78);
  mm::mtl::safeRelease(unknown70);
  mm::mtl::safeRelease(unknown68);
  mm::mtl::safeRelease(unknown60);
  mm::mtl::safeRelease(unknown58);
  mm::mtl::safeRelease(unknown50);
  mm::mtl::safeRelease(unknown48);
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(unknown30);
}

} // namespace gf
