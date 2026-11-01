#include "gf/game/event/gf_evt_se.h"

#include "framework/memory/framework_memory.h"
#include "framework/resource/sound_resource.h"
#include "framework/sound/sound_manager.h"
#include "mm_mtl/reference_object.h"

namespace fw {
enum LOAD_PRIO : int;
enum SoundCategory : int;
} // namespace fw

namespace gf {

GfEvtSe::GfEvtSe() : unknown1c8(false) {}

GfEvtSe::~GfEvtSe() {}

void GfEvtSe::cleanup() {
  destroySe();
  unknown1c8 = true;
}

void GfEvtSe::destroySe() {
  for (unknown001 &se : unknown00) {
    se.unknown10.clear();
    se.unknown08 = nullptr;
    mm::mtl::safeRelease(se.unknown00);
  }
  unknown00.clear();
}

void GfEvtSe::createSe(const char *name) {
  if (name == nullptr || name[0] == '\0') {
    return;
  }

  mm::mtl::FixStr<128> path;
  path.format("sound/se/%s%s", name, ".xsp");
  fw::SoundResource::SetupInfo info;
  // Category 12: the event sound effects.
  info.unknown00 = static_cast<fw::SoundCategory>(12);
  fw::SoundResource *resource = fw::SoundResource::request(fw::FrameworkMemory::getAllocator(8), path.c_str(), info, static_cast<fw::LOAD_PRIO>(10));
  unknown001 se;
  se.unknown10 = name;
  se.unknown00 = resource;
  se.unknown08 = nullptr;
  unknown00.push_back(se);
}

void GfEvtSe::update(const fw::UpdateInfo &) {
  for (unknown001 &se : unknown00) {
    if (se.unknown00 != nullptr && se.unknown08 == nullptr && se.unknown00->valid() && se.unknown00->getAssetData() != nullptr) {
      se.unknown08 = fw::SoundManager::get()->findPack(se.unknown10.c_str(), nullptr);
    }
  }
}

} // namespace gf
