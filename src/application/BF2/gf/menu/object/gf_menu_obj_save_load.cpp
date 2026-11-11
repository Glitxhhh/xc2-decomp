#include "gf/menu/object/gf_menu_obj_save_load.h"

#include "gf/gf_allocator.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "mm_mtl/fixstr.h"
#include "ui/event/ui_event_manager.h"
#include "ui/input/ui_input_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjSaveLoad::GfMenuObjSaveLoad(u32 handle) : GfMenuObject(handle), unknown24(0) {}

GfMenuObjSaveLoad::~GfMenuObjSaveLoad() { ; }

void GfMenuObjSaveLoad::initialize() {
  ui::UIObjectAcc acc(unknown18);
  {
    ui::UIObjectAcc main(acc.unknown10, "LAY_main");
    if (main.isValid()) {
// __LINE__ must be 52 as in the original file: it is the line argument of operator new.
#line 52
      ListListener *listener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ListListener(this);
      listener->addRef();
      ui::UIEventManager::get()->registObjectListener(main.unknown10, listener);
      if (listener != nullptr) {
        listener->release();
      }
      setupInputSelection(main.unknown10, 0, 10);
    }
  }
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < 10; i++) {
    name.format("TXT_slot%d", i);
    ui::UIObjectAcc slot(acc.unknown10, name.c_str());
    if (slot.isValid()) {
      mm::mtl::FixStr<32> text;
      text.format("save %d", i);
      slot.applyText(text.c_str());
    }
  }
  ui::UIInputManager *inputManager = ui::UIInputManager::get();
  inputManager->unknown20 = acc.getDispPriority();
  GfMenuObjOperationInfo::setDisp(false);
  GfMenuObject::initialize();
}

void GfMenuObjSaveLoad::finalize() { GfMenuObject::finalize(); }

void GfMenuObjSaveLoad::update() { GfMenuObject::update(); }

} // namespace gf
