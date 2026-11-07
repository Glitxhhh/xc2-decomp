#include "gf/menu/object/gf_menu_obj_exp_get.h"

namespace gf {

GfMenuObjExpGet::GfMenuObjExpGet(u32 handle) : GfMenuObject(handle) {}

void GfMenuObjExpGet::finalize() { GfMenuObject::finalize(); }

void GfMenuObjExpGet::update() { GfMenuObject::update(); }

} // namespace gf
