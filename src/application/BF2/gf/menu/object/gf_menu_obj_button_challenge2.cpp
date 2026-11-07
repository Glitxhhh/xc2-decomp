#include "gf/menu/object/gf_menu_obj_button_challenge2.h"

#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "types.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x4b;

void GfMenuObjButtonChallenge2::finalize() { GfMenuObject::finalize(); }

void GfMenuObjButtonChallenge2::update() {
  unknown0a0.unknown003();
  GfMenuObject::update();
}

void GfMenuObjButtonChallenge2::dispRelationHUD(bool) {}

u32 GfMenuObjButtonChallenge2::getResultPoint() const {
  u32 point = unknown98;
  if (unknown90 != 0) {
    point = unknown98 / (unknown94 + 1);
  }
  return point;
}

void GfMenuObjButtonChallenge2::resume(GfMenuCallContext *context) {
  if (GfMenuObjUtil::checkCCNext(context, unknown001)) {
    unknown144(unknown001, 0x101);
  }
}

void GfMenuObjButtonChallenge2::close(GfMenuCallContext *context) {
  if (GfMenuObjUtil::checkCCNext(context, unknown001)) {
    unknown144(unknown001, GfMenuTypes::unknown003_34);
  }
}
} // namespace gf
