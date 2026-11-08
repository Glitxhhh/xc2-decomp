#include "gf/menu/object/gf_menu_obj_mercenary_top.h"

#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/gf_menu_reference_quest.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_blade_list.h"
#include "gf/menu/list/gf_menu_id_list.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_revolve_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: full screen layer id; original name unknown.
constexpr u32 unknown001 = 0x34;

GfMenuObjMercenaryTop::GfMenuObjMercenaryTop(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown48(nullptr), unknown50(nullptr), unknown58(1.0f), unknown60(nullptr), unknown68(nullptr), unknown70(nullptr),
      unknown98(nullptr), unknown0a0(this), unknown330(false), unknown334(0), unknown338(nullptr), unknown340(true) {
  unknown80 = unknown160();
  unknown88 = unknown160();
  unknown90 = unknown161();
  unknown98 = GfMenuCallContext::create();
  unknown338 = GfMenuCallContext::create();
}

GfMenuObjMercenaryTop::~GfMenuObjMercenaryTop() {
  mm::mtl::safeRelease(unknown338);
  mm::mtl::safeRelease(unknown98);
  unknown90 = nullptr;
  unknown88 = nullptr;
  unknown80 = nullptr;
  mm::mtl::safeRelease(unknown70);
  mm::mtl::safeRelease(unknown68);
  mm::mtl::safeRelease(unknown60);
  mm::mtl::safeRelease(unknown50);
  mm::mtl::safeRelease(unknown48);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(unknown40);
}

void GfMenuObjMercenaryTop::registOpenParam(const OpenParam &param) {
  GfMenuTypes::Param layerParam;
  layerParam.set(param);
  GfMenuFullScreen::registLayerParam(unknown001, layerParam);
}

void GfMenuObjMercenaryTop::sendOpenEvent(u32 handle, int type) {
  if (handle == 0) {
    handle = ui::UIObjectAcc(unknown18, "LAY_main").unknown10;
  }
  ui::EventData event;
  event.unknown08 = type;
  event.unknown0c = 0;
  event.unknown00 = GfMenuTypes::unknown003_33;
  GfMenuObject::sendEvent(handle, event, 0.0f);
}

void GfMenuObjMercenaryTop::sendCloseEvent(u32 handle, int type) {
  if (handle == 0) {
    handle = ui::UIObjectAcc(unknown18, "LAY_main").unknown10;
  }
  ui::EventData event;
  event.unknown08 = type;
  event.unknown0c = 0;
  event.unknown00 = GfMenuTypes::unknown003_34;
  GfMenuObject::sendEvent(handle, event, 0.0f);
}

void GfMenuObjMercenaryTop::finalize() { GfMenuObject::finalize(); }

void GfMenuObjMercenaryTop::update() {
  unknown0a0.unknown003();
  GfMenuObject::update();
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjMercenaryTop>(const mm::mtl::Delegate<bool()> *);
