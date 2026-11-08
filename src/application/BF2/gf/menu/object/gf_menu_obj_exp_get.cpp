#include "gf/menu/object/gf_menu_obj_exp_get.h"

namespace gf {

GfMenuObjExpGet::GfMenuObjExpGet(u32 handle) : GfMenuObject(handle) {}

GfMenuObjExpGet::~GfMenuObjExpGet() {
  GfMenuManyObjects::destroy<ExpGetInfo>(GfMenuManyObjects::unknown001_4);
  GfMenuManyObjects::destroy<ExpGetInfo>(GfMenuManyObjects::unknown001_5);
}

void GfMenuObjExpGet::finalize() { GfMenuObject::finalize(); }

void GfMenuObjExpGet::update() { GfMenuObject::update(); }

} // namespace gf

template void gf::GfMenuManyObjects::remove<gf::GfMenuObjExpGet::ExpGetInfo>(u32, u32);
template void mm::mtl::Queue<gf::GfMenuObjExpGet::ExpGetInfo>::push_back(const gf::GfMenuObjExpGet::ExpGetInfo &);
template void mm::mtl::Queue<gf::GfMenuObjExpGet::ExpGetInfo>::expand(size_t, size_t);
