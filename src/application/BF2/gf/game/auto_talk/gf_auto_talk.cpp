#include "gf/game/auto_talk/gf_auto_talk.h"

#include "fw/fw_update_info.h"

namespace gf {

void GfAutoTalkManager::destroy() { delete get(); }

bool GfAutoTalkManager::isInitialized() { return get() != nullptr; }

void GfAutoTalkManager::update(const fw::UpdateInfo &info) {
  GfAutoTalkManager *manager = get();
  if (manager != nullptr) {
    manager->update(info.unknown04);
  }
}

void GfAutoTalkManager::update(f32 deltaTime) {
  if (nullptr != unknown28) {
    (this->*unknown28)(deltaTime);
  }
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfAutoTalkManager>::~PtrSingleton();
