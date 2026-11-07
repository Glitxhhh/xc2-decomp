#include "gf/menu/object/gf_menu_obj_party_form2.h"

#include "mm_mtl/delegate.h" // IWYU pragma: keep
#include "types.h"

namespace gf {

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
