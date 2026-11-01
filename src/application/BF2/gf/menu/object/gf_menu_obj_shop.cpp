#include "gf/menu/object/gf_menu_obj_shop.h"

#include "gf/menu/adapter/gf_menu_adapter_manager.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x77;
// Inferred role: active adapter category; original name unknown.
constexpr u32 unknown002 = 1;

u32 GfMenuObjShop::getSellItemTypeMax() { return 0xd; }

void GfMenuObjShop::close(GfMenuCallContext *context) {
  if (GfMenuObjUtil::checkCCNext(context, unknown001)) {
    ui::UIObjectAcc acc(context->unknown14);
    if (acc.isValid()) {
      ui::EventData event;
      event.unknown00 = GfMenuTypes::unknown003_34;
      GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
      GfMenuAdapterManager::delActiveCategory(unknown002);
    }
  }
}

void GfMenuObjShop::dispBlade(bool isDisp) { unknown150(unknown001, 0x46, isDisp); }

} // namespace gf
