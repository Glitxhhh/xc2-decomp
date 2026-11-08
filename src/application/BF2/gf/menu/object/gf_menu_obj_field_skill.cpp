#include "gf/menu/object/gf_menu_obj_field_skill.h"

#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/list/gf_menu_field_skill_list.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/delegate.h" // IWYU pragma: keep
#include "mm_mtl/reference_object.h"
#include "types.h"

namespace gf {
class GfMenuCallContext;

// Inferred role: skip call id; original name unknown.
constexpr u32 unknown001 = 0x32;

GfMenuObjFieldSkill::~GfMenuObjFieldSkill() {
  unknown50 = nullptr;
  unknown38 = nullptr;
  unknown40 = nullptr;
  unknown28 = nullptr;
  unknown30 = nullptr;
  mm::mtl::safeRelease(unknown48);
}

void GfMenuObjFieldSkill::finalize() { GfMenuObject::finalize(); }

void GfMenuObjFieldSkill::attachSkip(GfMenuCallContext *context) {
  if (GfMenuObjUtil::checkCCStart(context)) {
    unknown152(context, unknown001);
  }
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjFieldSkill>(const mm::mtl::Delegate<bool()> *);
