#include "gf/menu/object/gf_menu_obj_zone_map.h"

#include "gf/gf_allocator.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/list/gf_menu_zone_map_list.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_object.h"
#include "ui/list/ui_select_obj_list.h"

namespace gf {

GfMenuObjZoneMap::GfMenuObjZoneMap(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(1.0f), unknown48(nullptr), unknown50(nullptr), unknown70(false), unknown98(nullptr), unknown3100(0),
      unknown3124(false), unknown3125(false), unknown3128(nullptr), unknown3130(this), unknown33c0(false), unknown33c8(nullptr), unknown33d0(0) {
  unknown58.setAllocator(getAllocator(ALLOCATOR_DEFAULT));
}

GfMenuObjZoneMap::~GfMenuObjZoneMap() {
  if (unknown58.size() != 0) {
    unknown58.destroy();
  }
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(unknown48);
  mm::mtl::safeRelease(unknown50);
  mm::mtl::safeRelease(unknown98);
  mm::mtl::safeRelease(unknown3128);
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjZoneMap>(const mm::mtl::Delegate<bool()> *);
