#include "gf/menu/object/gf_menu_obj_drop_item.h"

namespace gf {

GfMenuObjDropItem::GfMenuObjDropItem(u32 handle) : GfMenuObject(handle) {}

void GfMenuObjDropItem::finalize() { GfMenuObject::finalize(); }

void GfMenuObjDropItem::update() { GfMenuObject::update(); }

} // namespace gf
