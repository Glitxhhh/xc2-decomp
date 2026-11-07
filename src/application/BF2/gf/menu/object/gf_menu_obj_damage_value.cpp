#include "gf/menu/object/gf_menu_obj_damage_value.h"

namespace gf {

GfMenuObjDamageValue::GfMenuObjDamageValue(u32 handle) : GfMenuObject(handle) {}

void GfMenuObjDamageValue::finalize() { GfMenuObject::finalize(); }

void GfMenuObjDamageValue::update() { GfMenuObject::update(); }

} // namespace gf
