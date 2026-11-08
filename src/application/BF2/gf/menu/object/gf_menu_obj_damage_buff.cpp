#include "gf/menu/object/gf_menu_obj_damage_buff.h"

#include "gf/menu/gf_menu_types.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: call id passed to getAttachedObject in close(); taken from the game disassembly, original name unknown.
constexpr u32 unknown001 = 0x2d;

GfMenuObjDamageBuff::GfMenuObjDamageBuff(u32 handle) : GfMenuObject(handle) {}

GfMenuObjDamageBuff::~GfMenuObjDamageBuff() { GfMenuManyObjects::destroy<DamageInfo>(GfMenuManyObjects::unknown001_1); }

void GfMenuObjDamageBuff::finalize() { GfMenuObject::finalize(); }

void GfMenuObjDamageBuff::close(u32 handle) {
  ui::UIObjectAcc root(getAttachedObject(unknown001));
  if (!root.isValid()) {
    return;
  }
  if (root.isTerm()) {
    return;
  }
  ui::UIObjectAcc acc(handle);
  if (!acc.isValid()) {
    return;
  }
  if (!acc.isDuplicate()) {
    return;
  }
  // The game builds a third temporary here and destroys it before sendEvent; using acc moves the destructor after the call.
  ui::EventData event;
  event.unknown00 = GfMenuTypes::unknown003_34;
  event.unknown08_u16 = ui::UIObjectAcc(handle).getDuplicateIndex();
  sendEvent(root.unknown10, event, 0.0f);
}

void GfMenuObjDamageBuff::update() { GfMenuObject::update(); }

} // namespace gf

template void gf::GfMenuManyObjects::remove<gf::GfMenuObjDamageBuff::DamageInfo>(u32, u32);
template void mm::mtl::Queue<gf::GfMenuObjDamageBuff::DamageInfo>::push_back(const gf::GfMenuObjDamageBuff::DamageInfo &);
template void mm::mtl::Queue<gf::GfMenuObjDamageBuff::DamageInfo>::expand(size_t, size_t);
