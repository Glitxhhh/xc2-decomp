#include "gf/game/gf_game_voice.h"

#include <string.h>

#include "framework/lang_util.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "gf/object/gf_obj_handle.h"
#include "ml/rand.h"
#include "mm_mtl/fixed_list.h" // IWYU pragma: keep
#include "mm_mtl/fixstr.h"

namespace gf {

class VoiceInfo; // IWYU pragma: keep

namespace {

// Inferred role: middle number of the field voice name per CV_FIELD; original name unknown.
const u8 unknown001[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 2, 0};
// Inferred role: number of driver voice variations per CV_FIELD; original name unknown.
const u8 unknown002[] = {2, 1, 1, 2, 2, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1};
// Inferred role: driver voice number per CV_FIELD; original name unknown.
const u8 unknown003[] = {50, 51, 52, 53, 54, 55, 57, 59, 1, 62, 64, 65, 66, 66, 66, 68, 70, 72, 73, 77, 78, 80, 82, 2, 2, 84, 85, 87, 88, 88, 95, 96, 96, 98, 98, 98, 65};
// Inferred role: number of blade voice variations per CV_FIELD; original name unknown.
const u8 unknown004[] = {2, 1, 1, 2, 2, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1};
// Inferred role: blade voice number per CV_FIELD; original name unknown.
const u8 unknown005[] = {50, 51, 52, 53, 54, 56, 58, 59, 1, 61, 63, 65, 66, 66, 66, 67, 69, 71, 73, 79, 79, 81, 83, 2, 2, 84, 85, 86, 88, 88, 94, 97, 97, 98, 98, 98, 65};

// Inferred role: appends a number written with at least two digits; original name unknown.
inline void unknown006(mm::mtl::FixStr<16> &name, u32 number) {
  mm::mtl::FixStr<16> numberStr;
  if (number < 10) {
    numberStr.format("0%d", number);
  } else {
    numberStr.format("%d", number);
  }
  name += numberStr.c_str();
}

} // namespace

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

GAME_VOICE_HANDLE *GfGameVoice::playVoice(GF_OBJ_HANDLE *handle, const char *name, CV_PRIO priority) {
  ParamObj object = {handle, 0, 0};
  return playVoice(object, name, priority);
}

GAME_VOICE_HANDLE *GfGameVoice::playVoice(u32 type, u32 id, const char *name, CV_PRIO priority) {
  ParamObj object = {INVALID_HANDLE, type, id};
  return playVoice(object, name, priority);
}

void GfGameVoice::applyHanaVoiceCondirtion(GfVoiceName &) {}

GAME_VOICE_HANDLE *GfFieldVoice::playVoice(GF_OBJ_HANDLE *handle, CV_FIELD voice, CV_PRIO priority) {
  ParamObj object = {handle, 0, 0};
  return playVoice(object, voice, priority);
}

GAME_VOICE_HANDLE *GfFieldVoice::playVoice(u32 type, u32 id, CV_FIELD voice, CV_PRIO priority) {
  ParamObj object = {INVALID_HANDLE, type, id};
  return playVoice(object, voice, priority);
}

GAME_VOICE_HANDLE *GfFieldVoice::playVoice(const ParamObj &object, CV_FIELD voice, CV_PRIO priority) {
  DataParamAcc acc(object);
  if (acc.getObjType() == OBJECT_TYPE_DRIVER || acc.getObjType() == OBJECT_TYPE_BLADE) {
    u32 middle = unknown001[voice];
    int variation;
    const u8 *numbers;
    if (acc.getObjType() == OBJECT_TYPE_DRIVER) {
      variation = ml::mtRand(unknown002[voice]);
      numbers = unknown003;
    } else {
      variation = ml::mtRand(unknown004[voice]);
      numbers = unknown005;
    }
    u32 number = numbers[voice];
    mm::mtl::FixStr<16> name;
    name = acc.getVoiceStr();
    unknown006(name, number);
    unknown006(name, middle + 1);
    unknown006(name, variation + 1);
    if (strcmp(acc.getVoiceStr(), "15") == 0) {
      name += "a";
    }
    return GfGameVoice::playVoice(object, name.c_str(), priority);
  }
  return nullptr;
}

GAME_VOICE_HANDLE *GfFieldVoice::playVoice(const ParamObj &object, CV_FIELD voice, u32 middle, u32 variation, CV_PRIO priority) {
  DataParamAcc acc(object);
  if (acc.getObjType() == OBJECT_TYPE_DRIVER || acc.getObjType() == OBJECT_TYPE_BLADE) {
    const u8 *numbers = acc.getObjType() == OBJECT_TYPE_DRIVER ? unknown003 : unknown005;
    u32 number = numbers[voice];
    mm::mtl::FixStr<16> name;
    name = acc.getVoiceStr();
    unknown006(name, number);
    unknown006(name, middle + 1);
    unknown006(name, variation + 1);
    if (strcmp(acc.getVoiceStr(), "15") == 0) {
      name += "a";
    }
    u32 id = acc.getObjType() == OBJECT_TYPE_DRIVER ? acc.getValidDriverId() : acc.getValidBdatId();
    return GfGameVoice::playVoice(acc.getObjType(), id, name.c_str(), priority);
  }
  return nullptr;
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfGameVoice>::~PtrSingleton();
template mm::mtl::FixedList<gf::VoiceInfo *, 6>::iterator mm::mtl::FixedList<gf::VoiceInfo *, 6>::erase(mm::mtl::FixedList<gf::VoiceInfo *, 6>::iterator it);
