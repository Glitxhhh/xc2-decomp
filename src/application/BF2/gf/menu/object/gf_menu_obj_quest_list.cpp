#include "gf/menu/object/gf_menu_obj_quest_list.h"

#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/list/gf_menu_quest_list.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/list/ui_select_obj_list.h"

namespace gf {

GfMenuObjQuestList::GfMenuObjQuestList(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr), unknown48(nullptr), unknown58(0), unknown5c(0), unknown60(0), unknown68(nullptr),
      unknown70(nullptr), unknown78(nullptr), unknown80(nullptr), unknown88(nullptr), unknown0a0(nullptr), unknown0b0(this), unknown340(0), unknown344(0), unknown358(nullptr), unknown360(true) {
  unknown0a0 = GfMenuCallContext::create();
  unknown0a8 = GfMenuCallContext::create();
}

GfMenuObjQuestList::~GfMenuObjQuestList() {
  unknown90 = nullptr;
  unknown98 = nullptr;
  unknown348 = nullptr;
  unknown350 = nullptr;
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown68);
  mm::mtl::safeRelease(unknown70);
  mm::mtl::safeRelease(unknown78);
  mm::mtl::safeRelease(unknown80);
  mm::mtl::safeRelease(unknown88);
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown48);
  mm::mtl::safeRelease(unknown0a0);
  mm::mtl::safeRelease(unknown0a8);
  mm::mtl::safeRelease(unknown358);
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjQuestList>(const mm::mtl::Delegate<bool()> *);
