#include "gf/menu/object/gf_menu_obj_button_challenge.h"

#include "gf/menu/gf_menu_types.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x1c;

GfMenuObjButtonChallenge::GfMenuObjButtonChallenge(u32 handle) : GfMenuObject(handle) {}

GfMenuObjButtonChallenge::~GfMenuObjButtonChallenge() { ; }

void GfMenuObjButtonChallenge::finalize() { GfMenuObject::finalize(); }

void GfMenuObjButtonChallenge::update() { GfMenuObject::update(); }

void GfMenuObjButtonChallenge::cancel(GfMenuCallContext *context) {
  if (context != nullptr) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
    if (acc.isValid()) {
      ui::EventData event;
      event.unknown00 = GfMenuTypes::unknown003_34;
      ui::UIManager::get()->requestObjectEvent(acc.unknown10, event, 0.0f);
      GfMenuObject::nextCallContext(context, unknown001);
    }
  }
}

} // namespace gf
