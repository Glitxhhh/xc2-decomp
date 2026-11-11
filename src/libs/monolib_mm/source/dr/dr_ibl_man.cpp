#include "dr/dr_ibl_man.h"

#include "dr/dr_ibl_obj.h"
#include "dr/dr_man.h"
#include "mtl/alloc_handle.h"

namespace ml {

DrIBLMan::DrIBLMan(DrMan *man, int index) : unknown00(man), unknown08(index), unknown910(nullptr) {}

bool DrIBLMan::isValid() const { return unknown910 != nullptr; }

void DrIBLMan::releaseObj(DrIBLObj *obj) { obj->unknown58 |= 2; }

DrIBLObj *DrIBLMan::createObj(const void *data) {
  DrIBLObj *obj = new (DrMan::get()->unknown0c) DrIBLObj(data);
  unknown250[DrMan::s_nDblStockIdx].push_back(obj);
  return obj;
}

grlib::CGLibTextureBuffer *DrIBLMan::getAlbedoTexture() const {
  if (unknown910 != nullptr) {
    return unknown910->getAlbedoTexture();
  }
  return nullptr;
}

grlib::CGLibTextureBuffer *DrIBLMan::getNormalTexture() const {
  if (unknown910 != nullptr) {
    return unknown910->getNormalTexture();
  }
  return nullptr;
}

grlib::CGLibTextureBuffer *DrIBLMan::debug_getAlbedoTexture(u32 index) const {
  if (!unknown10.empty()) {
    return (*unknown10.begin())->debug_getAlbedoTexture(index);
  }
  return nullptr;
}

grlib::CGLibTextureBuffer *DrIBLMan::debug_getNormalTexture(u32 index) const {
  if (!unknown10.empty()) {
    return (*unknown10.begin())->debug_getNormalTexture(index);
  }
  return nullptr;
}

} // namespace ml

// The game builds these files in one unit with this one.
#include "dr_ibl_obj.cpp"
