#include "gf/menu/object/gf_menu_obj_event_skip.h"

#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: call id of the event skip layout; original name unknown.
constexpr u32 CALL_UNKNOWN_47 = 47;

GfMenuObjEventSkip::GfMenuObjEventSkip(u32 handle) : GfMenuObject(handle) {}

GfMenuObjEventSkip::~GfMenuObjEventSkip() { ; }

void GfMenuObjEventSkip::initialize() {
  ui::UIObjectAcc acc(unknown18);
  u32 main = acc.searchChild("LAY_main");
  if (ui::UIObjectAcc(main).isValid()) {
// __LINE__ must be 72 as in the original file: it is the line argument of operator new.
#line 72
    ListListener *listener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ListListener(this);
    listener->addRef();
    ui::UIEventManager::get()->registObjectListener(main, listener);
    if (listener != nullptr) {
      listener->release();
    }
    attachExternalCall(CALL_UNKNOWN_47, main);
  }
  GfMenuObject::initialize();
}

void GfMenuObjEventSkip::finalize() { GfMenuObject::finalize(); }

void GfMenuObjEventSkip::update() { GfMenuObject::update(); }

void GfMenuObjEventSkip::close() { unknown143(CALL_UNKNOWN_47, GfMenuTypes::unknown003_34); }

u32 GfMenuObjEventSkip::setupScreen(u32 screen) { return screen; }

void GfMenuObjEventSkip::open(GfMenuCallContext *context) {
  u32 object = getAttachedObject(CALL_UNKNOWN_47);
  if (ui::UIObjectAcc(object).isValid()) {
    if (!ui::UIObjectAcc(object).isTerm()) {
      startCallContext(context, CALL_UNKNOWN_47, object);
      ui::EventData event;
      event.unknown00 = GfMenuTypes::unknown003_33;
      sendEvent(object, event, 0.0f);
      GfMenuObjUtil::playSE(3);
    }
  }
}

} // namespace gf
