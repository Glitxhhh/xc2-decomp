#include "rcha/rcha_cam.h"

#include "mm_math/mm_vec3.h"
#include "rcha/rcha_anm.h"

int RchaCam::getValueInt(int slot, f32 frame, int defaultValue) const {
  if (unknown19a4[slot] >= 0) {
    return unknown10[unknown19a4[slot]].getValueInt(frame);
  }
  return defaultValue;
}

f32 RchaCam::getValue(int slot, f32 frame, f32 defaultValue) const {
  if (unknown19a4[slot] >= 0) {
    return unknown10[unknown19a4[slot]].getValue(frame);
  }
  return defaultValue;
}

bool RchaCam::getPos(mm::Vec3 *pos, f32 frame) const {
  pos->x = getValue(CAM_TRANSLATE_X, frame, 0.0f);
  pos->y = getValue(CAM_TRANSLATE_Y, frame, 0.0f);
  pos->z = getValue(CAM_TRANSLATE_Z, frame, 0.0f);
  return true;
}

bool RchaCam::getRot(mm::Vec3 *rot, f32 frame) const {
  rot->x = getValue(CAM_ROTATE_X, frame, 0.0f);
  rot->y = getValue(CAM_ROTATE_Y, frame, 0.0f);
  rot->z = getValue(CAM_ROTATE_Z, frame, 0.0f);
  return true;
}

int RchaCam::getRotOrder(f32 frame) const { return getValueInt(CAM_ROTATE_ORDER, frame, 0); }

f32 RchaCam::getFov(f32 frame) const { return getValue(CAMATR_FOV, frame, 30.0f); }

f32 RchaCam::getNear(f32 frame) const { return getValue(CAMATR_NEAR, frame, 0.1f); }

f32 RchaCam::getFar(f32 frame) const { return getValue(CAMATR_FAR, frame, 80000.0f); }

f32 RchaCam::getMBlurStr(f32 frame) const { return getValue(CAMATR_MBLUR_STR, frame, 0.5f); }

bool RchaCam::isEnableMBlur(f32 frame) const {
  if (unknown19a4[CAMATR_MBLUR] >= 0) {
    return unknown10[unknown19a4[CAMATR_MBLUR]].getValue(frame) > 0.9f;
  }
  return false;
}

f32 RchaCam::getMBlurSub(f32 frame) const { return getValue(CAMATR_MBLUR_SUB, frame, 0.1f); }

bool RchaCam::isEnableDOF(f32 frame) const {
  if (unknown19a4[CAMATR_DOF] >= 0) {
    return unknown10[unknown19a4[CAMATR_DOF]].getValue(frame) > 0.9f;
  }
  return false;
}

f32 RchaCam::getDistanceDOF(f32 frame) const { return getValue(CAMATR_DOF_DISTANCE, frame, 20.0f); }

f32 RchaCam::getRangeDOF(f32 frame) const { return getValue(CAMATR_DOF_RANGE, frame, 40.0f); }

f32 RchaCam::getPixelDOF(f32 frame) const { return getValue(CAMATR_DOF_PIXEL, frame, 5.0f); }

f32 RchaCam::getLensDOF(f32 frame) const { return getValue(CAMATR_DOF_LENS, frame, 0.6f); }

f32 RchaCam::getStrengthDOF(f32 frame) const { return getValue(CAMATR_DOF_STRENGTH, frame, 4.0f); }

f32 RchaCam::getBlendDOF(f32 frame) const { return getValue(CAMATR_DOF_BLEND, frame, 1.0f); }

int RchaCam::getPixelLvDOF(f32 frame) const { return getValueInt(CAMATR_DOF_PIXEL_LV, frame, 0); }

bool RchaCam::isHlvDOF(f32 frame) const {
  if (unknown19a4[CAMATR_DOF_HLV] >= 0) {
    return unknown10[unknown19a4[CAMATR_DOF_HLV]].getValue(frame) > 0.9f;
  }
  return false;
}

bool RchaCam::isSMapVis(f32 frame) const {
  if (unknown19a4[CAMATR_SM_VIS] >= 0) {
    return unknown10[unknown19a4[CAMATR_SM_VIS]].getValue(frame) > 0.9f;
  }
  return true;
}

bool RchaCam::isEnableTime(f32 frame) const {
  if (unknown19a4[CAMATR_CLOCK] >= 0) {
    return unknown10[unknown19a4[CAMATR_CLOCK]].getValue(frame) > 0.9f;
  }
  return false;
}

f32 RchaCam::getTimeVal(f32 frame) const {
  f32 time = 0.0f;
  if (unknown19a4[CAMATR_CLOCK_HOUR] >= 0) {
    time = unknown10[unknown19a4[CAMATR_CLOCK_HOUR]].getValue(frame);
    if (time < 0.0f) {
      time = 0.0f;
    } else if (time > 23.999998f) {
      time = 23.999998f;
    }
  }
  return time;
}

bool RchaCam::isEnableWeather(f32 frame) const {
  if (unknown19a4[CAMATR_WTR] >= 0) {
    return unknown10[unknown19a4[CAMATR_WTR]].getValue(frame) > 0.9f;
  }
  return false;
}

bool RchaCam::isCamLgtStop(f32 frame) const {
  if (unknown19a4[CAMATR_CAM_LGT] >= 0) {
    return unknown10[unknown19a4[CAMATR_CAM_LGT]].getValue(frame) > 0.9f;
  }
  return false;
}

int RchaCam::getNearFarType(f32 frame) const { return getValueInt(CAMATR_NEAR_FAR, frame, 0); }

int RchaCam::getWeatherType(f32 frame) const { return getValueInt(CAMATR_WTR_TYPE, frame, 0); }

int RchaCam::getWeatherFrame(f32 frame) const { return getValueInt(CAMATR_WTR_FADE, frame, 0); }
