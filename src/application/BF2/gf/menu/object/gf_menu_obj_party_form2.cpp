#include "gf/menu/object/gf_menu_obj_party_form2.h"

#include "mm_mtl/delegate.h" // IWYU pragma: keep
#include "types.h"

namespace gf {

GfMenuObjPartyForm2::GfMenuObjPartyForm2(u32 handle)
    : GfMenuObject(handle), unknown38(false), unknown40(0), unknown48(0), unknown50(0), unknown58(0), unknown60(0xff), unknown64(0xff), unknown68(this), unknown2f8(0), unknown2fc(-1), unknown300(-1),
      unknown304(-1), unknown308(0), unknown310(0), unknown318(0) {}

GfMenuObjPartyForm2::~GfMenuObjPartyForm2() {}

u32 GfMenuObjPartyForm2::getCursorID(u32 index) {
  u32 id = 0x61;
  if (index == 1) {
    id = 0x62;
  }
  if (index != 0) {
    return id;
  }
  return 0x61;
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjPartyForm2>(const mm::mtl::Delegate<bool()> *);
