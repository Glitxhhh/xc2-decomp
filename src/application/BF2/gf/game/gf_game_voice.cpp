#include "gf/game/gf_game_voice.h"

#include "framework/lang_util.h"
#include "mm_mtl/fixed_list.h" // IWYU pragma: keep
#include "mm_mtl/fixstr.h"

namespace gf {

class VoiceInfo; // IWYU pragma: keep

bool GfGameVoice::isInitialized() {
  GfGameVoice *voice = get();
  if (voice != nullptr) {
    return voice->unknown08;
  }
  return false;
}

const mm::mtl::FixStr<16> &GfGameVoice::getLangPath() { return fw::LangUtil::getVoiceFolder(); }

GAME_VOICE_HANDLE *GfGameVoice::createHandle() {
  u64 handle = unknown110 + 1;
  if (handle == 0) {
    handle++;
  }
  unknown110 = handle;
  return reinterpret_cast<GAME_VOICE_HANDLE *>(handle);
}

void GfGameVoice::applyHanaVoiceCondirtion(GfVoiceName &) {}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfGameVoice>::~PtrSingleton();
template mm::mtl::FixedList<gf::VoiceInfo *, 6>::iterator mm::mtl::FixedList<gf::VoiceInfo *, 6>::erase(mm::mtl::FixedList<gf::VoiceInfo *, 6>::iterator it);
