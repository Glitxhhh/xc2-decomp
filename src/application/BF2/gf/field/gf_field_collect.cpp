#include "gf/field/gf_field_collect.h"

#include "fw/fw_update_info.h"
#include "gf/gf_allocator.h"
#include "gf/object/gf_obj_handle.h"
#include "gmk/gmk_collection.h"
#include "gmk/gmk_manager.h"
#include "mm_mtl/delegate.h" // IWYU pragma: keep

namespace gf {

GfFieldCollect::GfFieldCollect(const GfSetupParam &param) : unknown19(false), unknown20(INVALID_HANDLE), unknown1c0(0.0f), unknown1c4(0.0f), unknown1c8(0) { create(param); }

void GfFieldCollect::seqEnd(f32) {}

void GfFieldCollect::create(const GfSetupParam &) {
  unknown08 = &GfFieldCollect::seqEnd;
  unknown18 = true;
}

GfFieldCollect::~GfFieldCollect() {}

bool GfFieldCollect::isDropitemsEmitted() const {
  u32 count = unknown30.size();
  for (u32 i = 0; i < count; i++) {
    if (!unknown30[i].m_dropitemsEmitted) {
      return false;
    }
  }
  return true;
}

void GfFieldCollect::gevMapjump(GEV event, const MapjumpCallbackInfo &) {
  if (event == GEV_MAPJUMP_START) {
    end();
  }
}

void GfFieldCollect::end() {
  unknown30.clear();
  unknown20 = INVALID_HANDLE;
  unknown08 = &GfFieldCollect::seqEnd;
}

void GfFieldCollect::createDropitemEmitter(const GfDropitemEmitter::CreateInfo &info) {
  unknown30.push_back(GfDropitemEmitter());
  unknown30.back().create(info);
}

void GfFieldCollect::dispose() {
  end();
  if (unknown18) {
    unknown18 = false;
  }
}

void GfFieldCollect::update(f32 deltaTime) {
  size_t count = get()->unknown30.size();
  for (size_t i = 0; i < count; i++) {
    get()->unknown30[i].update(deltaTime);
  }
  if (unknown08) {
    (this->*unknown08)(deltaTime);
  }
}

void GfFieldCollect::build(const GfSetupParam &param) {
  // __LINE__ must be 185 as in the original file: it is the line argument of operator new.
#line 185
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfFieldCollect(param);
}

void GfFieldCollect::destroy() {
  GfFieldCollect *collect = get();
  collect->dispose();
  delete collect;
}

void GfFieldCollect::update(const fw::UpdateInfo &info) {
  if (get() != nullptr && get()->unknown18) {
    get()->update(info.unknown04);
  }
}

void GfFieldCollect::seqWaitDrop(f32) {
  if (!isDropitemsEmitted()) {
    return;
  }
  gmk::GmkCollection *collection = static_cast<gmk::GmkCollection *>(gmk::getBindedGmkInst(unknown20));
  if (collection != nullptr) {
    collection->disposeIcon(true);
  }
  unknown08 = &GfFieldCollect::seqEnd;
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfFieldCollect>::~PtrSingleton();
template float mm::mtl::Delegate<float(float, float, float)>::staticFuncInvoker(const mm::mtl::Delegate<float(float, float, float)> *, float, float, float);
