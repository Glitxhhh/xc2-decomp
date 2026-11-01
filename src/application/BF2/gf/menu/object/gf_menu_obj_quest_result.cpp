#include "gf/menu/object/gf_menu_obj_quest_result.h"

#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "types.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x1f;

GfMenuObjQuestResult::GfMenuObjQuestResult(u32 handle) : GfMenuObject(handle) {}

GfMenuObjQuestResult::~GfMenuObjQuestResult() { ; }

void GfMenuObjQuestResult::finalize() { GfMenuObject::finalize(); }

void GfMenuObjQuestResult::update() { GfMenuObject::update(); }

void GfMenuObjQuestResult::close() { unknown143(unknown001, GfMenuTypes::unknown003_34); }

void GfMenuObjQuestResult::fadeOut(u32 handle) {
  GfMenuObjUtil::CtrlParam param;
  param.unknown00 = 0.5f;
  param.unknown08 = 2;
  GfMenuObjUtil::startCtrl(handle, param, nullptr);
}

void GfMenuObjQuestResult::fadeIn(u32 handle) {
  GfMenuObjUtil::CtrlParam param;
  param.unknown00 = 0.5f;
  param.unknown08 = 1;
  GfMenuObjUtil::startCtrl(handle, param, nullptr);
}

} // namespace gf
