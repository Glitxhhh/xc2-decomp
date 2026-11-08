#include "gf/menu/object/gf_menu_obj_button_challenge2.h"

#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "types.h"
#include "ui/ctrl/ui_ctrl_manager.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x4b;

GfMenuObjButtonChallenge2::~GfMenuObjButtonChallenge2() {
  if (unknown3e0.ctrl != nullptr) {
    ui::UICtrlManager::get()->delUpdater(unknown3e0);
  }
  unknown3e0.ctrl = nullptr;
  if (unknown428.ctrl != nullptr) {
    ui::UICtrlManager::get()->delUpdater(unknown428);
  }
  unknown428.ctrl = nullptr;
  if (unknown470.ctrl != nullptr) {
    ui::UICtrlManager::get()->delUpdater(unknown470);
  }
  unknown470.ctrl = nullptr;
}

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

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjButtonChallenge2>(const mm::mtl::Delegate<bool()> *);
