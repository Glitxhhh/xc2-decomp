#include "gf/menu/object/gf_menu_obj_field_skill.h"

#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/delegate.h" // IWYU pragma: keep
#include "types.h"

namespace gf {
class GfMenuCallContext;

// Inferred role: skip call id; original name unknown.
constexpr u32 unknown001 = 0x32;

void GfMenuObjFieldSkill::finalize() { GfMenuObject::finalize(); }

void GfMenuObjFieldSkill::attachSkip(GfMenuCallContext *context) {
  if (GfMenuObjUtil::checkCCStart(context)) {
    unknown152(context, unknown001);
  }
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjFieldSkill>(const mm::mtl::Delegate<bool()> *);
