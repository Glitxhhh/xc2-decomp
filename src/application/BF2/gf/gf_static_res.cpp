#include "gf/gf_static_res.h"

#include "framework/resource/common_resource.h"
#include "framework/resource/resource_manager.h"
#include "gf/gf_manager.h"
#include "gf/sound/gf_sound.h"
#include "ml/ml_mem.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"
#include "types.h"

namespace gf {

mtl::ALLOC_HANDLE GfStaticRes::s_hMem;
mm::mtl::FixedList<GfStaticRes::ResourceInfo, 64> GfStaticRes::s_aResource;

void GfStaticRes::initialize() {
  s_hMem = mtl::MemManager::create(ml::MlMem::getProductMem(), 0x200000, "GfStatic", false);
  loadRequest();
  while (!isLoaFinish()) {
    GfSleep(1);
  }
}

void GfStaticRes::loadRequest() {
  loadStaticRes("/param/common.prm");
  loadStaticRes("/param/pc.prm");
  loadStaticRes("/param/camera.prm");
  loadStaticRes("/param/menu.prm");
  loadStaticRes("/param/event.prm");
  loadStaticRes("/param/effect.prm");
  loadStaticRes("/param/pad.pdp");
  loadStaticRes("/camera/params.gca");
  u32 count = getSoundSourceCount();
  for (u32 i = 0; i < count; i++) {
    loadStaticRes(getSoundSourceFileName(i));
  }
}

bool GfStaticRes::isLoaFinish() { return fw::ResourceManager::get()->isLoaded(); }

void GfStaticRes::loadStaticRes(const char *path) {
  fw::CommonResource *resource = fw::CommonResource::request(s_hMem, path, 10, false);
  if (resource != nullptr) {
    ResourceInfo info;
    info.unknown00 = resource;
    info.unknown08 = path;
    s_aResource.push_back(info);
  }
}

fw::CommonResource *GfStaticRes::search(const char *path) { return fw::CommonResource::search(s_hMem, path); }

} // namespace gf
