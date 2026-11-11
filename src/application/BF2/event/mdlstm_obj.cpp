#include "event/mdlstm_obj.h"

#include "dr/dr_stm_read_obj.h"
#include "event/alpha_manager.h"
#include "event/alpha_obj.h"
#include "event/extend.h"
#include "event/mdlstm_data.h"
#include "event/model_manager.h"
#include "event/model_obj.h"
#include "event/model_util.h"
#include "mm_mtl/singleton.h"

namespace event {

MdlstmObj::MdlstmObj()
    : unknown08(0), unknown0c(STATE_UNKNOWN_0), unknown10(0.0f), _98(0), _9c(0), _a0(0), _a4(false), _a5(false), _a8(0), _b0(nullptr), _b8(nullptr), _c0(nullptr), _c8(nullptr), _d0(nullptr),
      unknownd8(nullptr), unknowne0(nullptr) {}

// The empty statement makes the body non-trivial, which keeps the vtable pointer stores of the original.
MdlstmObj::~MdlstmObj() { ; }

void MdlstmObj::destroy() { finishFree(); }

void MdlstmObj::finishFree() {
  if (unknowne0 != nullptr) {
    mm::mtl::Singleton<AlphaManager>::getPtr()->setAlpha(unknowne0->getHandle(), ALPHA_ATTR_UNKNOWN_2, 0.0f, 1.0f);
  }
  if (unknowne0 != nullptr) {
    mm::mtl::Singleton<ModelManager>::getPtr()->destroyModel(unknowne0, unknownec);
    unknowne0 = nullptr;
  }
  if (unknownd8 != nullptr) {
    mm::mtl::Singleton<ModelManager>::getPtr()->destroyModel(unknownd8, unknownec);
    unknownd8 = nullptr;
  }
  _c0 = nullptr;
  _c8 = nullptr;
  _b0 = nullptr;
  _b8 = nullptr;
  if (_d0 != nullptr) {
    _d0->release();
    _d0 = nullptr;
  }
  unknowne8 = 0;
  _a8 = 0;
  unknown08 = 0;
  unknown0c = STATE_UNKNOWN_0;
  unknown10 = 0.0f;
  unknown14.clear();
  _98 = 0;
  _9c = 0;
  _a0 = 0;
  _a4 = false;
  _a5 = false;
}

void MdlstmObj::init(f32 frame, const char *path, u32 value, bool isActive, int param) {
  unknown10 = frame;
  unknown08 |= 1;
  unknown14 = path;
  _98 = 0;
  _9c = 0;
  _a0 = 0;
  _a4 = false;
  _a5 = isActive;
  _a8 = value;
  _b0 = nullptr;
  _c0 = nullptr;
  unknowne0 = nullptr;
  unknowne8 = 0;
  unknownec = param;
  unknown0c = STATE_UNKNOWN_1;
  MdlstmData::Info info = {};
  if (mm::mtl::Singleton<MdlstmData>::getPtr()->getReplaceInfo(info, unknown14.c_str())) {
    _98 = info.unknown84;
    _9c = info.unknown88;
    _a0 = info.unknown8c;
    _a4 = info.unknown90;
  }
}

void MdlstmObj::init(f32 frame, MODEL_TYPE type, u32 id, u32 value, bool isActive, int param) {
  unknown10 = frame;
  unknown08 &= ~1;
  unknown14.clear();
  _98 = type;
  _9c = id;
  _a0 = 0;
  _a4 = false;
  _a5 = isActive;
  _a8 = value;
  _b0 = nullptr;
  _c0 = nullptr;
  unknowne0 = nullptr;
  unknowne8 = 0;
  unknownec = param;
  unknown0c = STATE_UNKNOWN_1;
}

void MdlstmObj::finishLoaded() { unknown0c = STATE_UNKNOWN_4; }

void MdlstmObj::finishDelay() { unknown0c = STATE_UNKNOWN_6; }

void MdlstmObj::finishBusy() {
  ModelUtil::setupRenderState(unknowne0->getHandle());
  unknown0c = STATE_UNKNOWN_7;
}

void MdlstmObj::load() { unknown0c = STATE_UNKNOWN_2; }

void MdlstmObj::dispose() {
  unknown0c = STATE_UNKNOWN_9;
  unknowne8 = 1;
}

bool MdlstmObj::isLoaded() const { return unknown0c > STATE_UNKNOWN_3; }

bool MdlstmObj::isDisposeable(ModelObj *model) const { return unknown0c == STATE_UNKNOWN_8 && unknowne0 == model; }

bool MdlstmObj::isActive() const { return unknown0c != STATE_UNKNOWN_0; }

bool MdlstmObj::isLoading(f32 threshold) const {
  if (unknown10 <= threshold && static_cast<u32>(unknown0c - STATE_UNKNOWN_1) < 6) {
    return true;
  }
  return false;
}

bool MdlstmObj::isBuildable(const char *name, u32 value) const {
  if (unknown0c != STATE_UNKNOWN_7 || !(unknown08 & 1) || _a8 != value)
    return false;
  return __builtin_strcmp(unknown14.c_str(), name) == 0;
}

bool MdlstmObj::isBuildable(MODEL_TYPE type, u32 id, u32 value) const {
  if (unknown0c != STATE_UNKNOWN_7 || (unknown08 & 1) || _a8 != value || _98 != static_cast<u32>(type) || _9c != id) {
    return false;
  }
  return true;
}

bool MdlstmObj::checkByHandle(gf::GF_OBJ_HANDLE *handle) const {
  if (unknownd8 != nullptr && unknownd8->getHandle() == handle) {
    return true;
  }
  if (unknowne0 != nullptr && unknowne0->getHandle() == handle) {
    return true;
  }
  return false;
}

void MdlstmObj::OnResEvent(const PARAM &param) {
  if (__builtin_strcmp(param.path, mm::mtl::Singleton<Extend>::getPtr()->mdo(unknown14.c_str())) == 0) {
    unknown08 &= ~2;
    unknown08 |= 8;
  } else if (__builtin_strcmp(param.path, mm::mtl::Singleton<Extend>::getPtr()->arc(unknown14.c_str())) == 0) {
    unknown08 &= ~4;
    unknown08 |= 0x10;
  }
}

} // namespace event
