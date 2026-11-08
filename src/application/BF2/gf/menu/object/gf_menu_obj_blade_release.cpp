#include "gf/menu/object/gf_menu_obj_blade_release.h"

#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/list/gf_menu_blade_list.h"
#include "gf/menu/list/gf_menu_driver_list.h"
#include "gf/menu/list/gf_menu_id_list.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/list/ui_select_obj_list.h"

namespace gf {

GfMenuObjBladeRelease::GfMenuObjBladeRelease(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr), unknown48(nullptr), unknown50(nullptr), unknown58(this), unknown2e8(false),
      unknown2f0(this), unknown450(nullptr), unknown458(false), unknown460(nullptr), unknown468(false), unknown46c(-1), unknown470(nullptr), unknown4a0(false), unknown4a4(0), unknown4a8(0),
      unknown4b0(nullptr) {
  unknown450 = GfMenuItemList::create();
  unknown460 = GfMenuIDList::create();
  unknown470 = GfMenuDriverList::create();
  unknown48 = GfMenuCallContext::create();
  unknown50 = GfMenuCallContext::create();
}

GfMenuObjBladeRelease::~GfMenuObjBladeRelease() {
  mm::mtl::safeRelease(unknown470);
  mm::mtl::safeRelease(unknown460);
  mm::mtl::safeRelease(unknown450);
  mm::mtl::safeRelease(unknown50);
  mm::mtl::safeRelease(unknown48);
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown28);
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjBladeRelease>(const mm::mtl::Delegate<bool()> *);
template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuSequence<gf::GfMenuObjBladeRelease, 8>>(const mm::mtl::Delegate<bool()> *);
