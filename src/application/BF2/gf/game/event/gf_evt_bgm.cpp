#include "gf/game/event/gf_evt_bgm.h"

#include "fw/fw_update_info.h"
#include "gf/game/event/gf_evt_bgm_task.h"
#include "gf/game/gf_game_scene.h"
#include "gf/gf_allocator.h"
#include "mm_mtl/fixstr.h"

namespace gf {

GfEvtBgm::GfEvtBgm(const GfSetupParam &param) : unknown0c(), m_playState(PLAY_STATE_UNKNOWN_0), unknown478(nullptr), unknown480(nullptr), unknown488(nullptr) { initialize(param); }

GfEvtBgm::~GfEvtBgm() { ; }

void GfEvtBgm::destroy() {
  GfEvtBgm *bgm = get();
  bgm->finalize();
  delete bgm;
}

void GfEvtBgm::initialize(const GfSetupParam &) { m_initialized = true; }

void GfEvtBgm::update(const fw::UpdateInfo &info) { updateBgmTask(info); }

void GfEvtBgm::finalize() { m_initialized = false; }

bool GfEvtBgm::isInitialized() { return m_initialized; }

void GfEvtBgm::setPlayBgmVolume(f32 volume) { unknown0c.unknown44 = volume; }

void GfEvtBgm::setPlayState(PLAY_STATE playState) { m_playState = playState; }

bool GfEvtBgm::isEnableEventBgm() const { return m_playState >= PLAY_STATE_UNKNOWN_2 && m_playState <= PLAY_STATE_UNKNOWN_4; }

void GfEvtBgm::setFadeoutVolume() {
  if (m_playState == PLAY_STATE_UNKNOWN_3 && unknown478 == nullptr) {
    m_playState = PLAY_STATE_UNKNOWN_0;
  }
}

void GfEvtBgm::setPlayParam(const EventBgmSetup &setup) {
  unknown0c = setup;
  if (unknown0c.unknown00.empty() && !setup.unknown60 && setup.unknown65) {
    unknown0c.unknown00 = "SilentBgm";
  }
}

EvtBgmTaskDelayStop::EvtBgmTaskDelayStop(const EventBgmSetup &setup) : unknown08(setup), unknown70(setup.unknown58), unknown74(false) {}

void EvtBgmTaskDelayStop::start(GfEvtBgm *bgm) { bgm->m_playState = GfEvtBgm::PLAY_STATE_UNKNOWN_4; }

bool EvtBgmTaskDelayStop::update(GfEvtBgm *bgm, const fw::UpdateInfo &info) {
  if (!unknown74) {
    unknown70 -= info.unknown04;
    if (unknown70 > 0.0f) {
      return false;
    }
    bgm->setPlayParam(unknown08);
    bgm->m_playState = GfEvtBgm::PLAY_STATE_UNKNOWN_0;
    if (GfGameScene::get() != nullptr) {
      GfGameScene::get()->setForceEventBgm(0.0f);
    }
  }
  return true;
}

void EvtBgmTaskDelayStop::cancel(GfEvtBgm *) { unknown74 = true; }

EvtBgmTaskDelayStop *EvtBgmTaskDelayStop::create(const EventBgmSetup &setup) {
  // __LINE__ must be 392 as in the original file: it is an argument of the allocation.
#line 392
  return new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) EvtBgmTaskDelayStop(setup);
}

EvtBgmTaskDelay::EvtBgmTaskDelay(const EventBgmSetup &setup) : unknown08(setup), unknown70(false) {}

bool EvtBgmTaskDelay::isPlayTask() const { return true; }

void EvtBgmTaskDelay::start(GfEvtBgm *bgm) {
  if (bgm->unknown0c.unknown60) {
    bgm->m_playState = GfEvtBgm::PLAY_STATE_UNKNOWN_2;
    bgm->unknown0c.unknown00 = "";
  } else {
    bgm->m_playState = GfEvtBgm::PLAY_STATE_UNKNOWN_1;
  }
}

bool EvtBgmTaskDelay::update(GfEvtBgm *bgm, const fw::UpdateInfo &info) {
  if (!unknown70) {
    unknown08.unknown54 -= info.unknown04;
    if (unknown08.unknown54 > 0.0f) {
      return false;
    }
    bgm->m_playState = GfEvtBgm::PLAY_STATE_UNKNOWN_3;
    bgm->setPlayParam(unknown08);
    if (unknown08.unknown58 > 0.0f && GfGameScene::get() != nullptr) {
      GfGameScene::get()->setForceEventBgm(unknown08.unknown58);
    }
  }
  return true;
}

void EvtBgmTaskDelay::cancel(GfEvtBgm *) { unknown70 = true; }

EvtBgmTaskDelay *EvtBgmTaskDelay::create(const EventBgmSetup &setup) {
  // __LINE__ must be 347 as in the original file: it is an argument of the allocation.
#line 347
  return new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) EvtBgmTaskDelay(setup);
}

EvtBgmTaskVolume::EvtBgmTaskVolume(const EventBgmSetup &setup) : unknown08(setup.unknown48), unknown0c(setup.unknown44), unknown10(false) {}

bool EvtBgmTaskVolume::isVolumeTask() const { return true; }

void EvtBgmTaskVolume::start(GfEvtBgm *) {}

bool EvtBgmTaskVolume::update(GfEvtBgm *bgm, const fw::UpdateInfo &info) {
  if (unknown10) {
    return true;
  }
  if (info.unknown04 < 1e-06f) {
    return false;
  }
  f32 remain = unknown08 - info.unknown04;
  unknown08 = remain <= 0.0f ? 0.0f : remain;
  f32 diff = unknown0c - bgm->unknown0c.unknown44;
  if (__builtin_fabsf(diff) <= 1e-06f) {
    return true;
  }
  f32 ratio = unknown08 == 0.0f ? 1.0f : info.unknown04 / unknown08;
  bgm->unknown0c.unknown44 += diff * ratio;
  return unknown08 <= 0.0f;
}

void EvtBgmTaskVolume::cancel(GfEvtBgm *) { unknown10 = true; }

EvtBgmTaskVolume *EvtBgmTaskVolume::create(const EventBgmSetup &setup) {
  // __LINE__ must be 437 as in the original file: it is an argument of the allocation.
#line 437
  return new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) EvtBgmTaskVolume(setup);
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfEvtBgm>::~PtrSingleton();
