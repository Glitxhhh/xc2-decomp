#include "rcha/rcha_eff.h"

#include "mm_math/mm_col4.h"
#include "mm_math/mm_vec3.h"
#include "rcha/rcha_anm.h"

void RchaEff::clear() { RchaNode::clear(); }

int RchaEff::getValueInt(int slot, f32 frame, int defaultValue) const {
  if (unknown19a4[slot] >= 0) {
    return unknown10[unknown19a4[slot]].getValueInt(frame);
  }
  return defaultValue;
}

f32 RchaEff::getValue(int slot, f32 frame, f32 defaultValue) const {
  if (unknown19a4[slot] >= 0) {
    return unknown10[unknown19a4[slot]].getValue(frame);
  }
  return defaultValue;
}

bool RchaEff::getPos(mm::Vec3 &pos, f32 frame) const {
  pos.x = getValue(EFF_TRANSLATE_X, frame, 0.0f);
  pos.y = getValue(EFF_TRANSLATE_Y, frame, 0.0f);
  pos.z = getValue(EFF_TRANSLATE_Z, frame, 0.0f);
  return true;
}

bool RchaEff::getRot(mm::Vec3 &rot, f32 frame) const {
  rot.x = getValue(EFF_ROTATE_X, frame, 0.0f);
  rot.y = getValue(EFF_ROTATE_Y, frame, 0.0f);
  rot.z = getValue(EFF_ROTATE_Z, frame, 0.0f);
  return true;
}

bool RchaEff::getScl(mm::Vec3 &scale, f32 frame) const {
  scale.x = getValue(EFF_SCALE_X, frame, 0.0f);
  scale.y = getValue(EFF_SCALE_Y, frame, 0.0f);
  scale.z = getValue(EFF_SCALE_Z, frame, 0.0f);
  return true;
}

bool RchaEff::getProgress(int &current, int &total, f32 frame) const {
  current = getValue(EFFATR_SCALE_X, frame, 0.0f);
  total = getValue(EFFATR_SCALE_Y, frame, 0.0f);
  return true;
}

bool RchaEff::getCol(mm::Col4 &color, f32 frame) const {
  color.r = getValue(EFFATR_ROTATE_X, frame, 0.0f);
  color.g = getValue(EFFATR_ROTATE_Y, frame, 0.0f);
  color.b = getValue(EFFATR_ROTATE_Z, frame, 0.0f);
  color.a = getValue(EFFATR_TRANSLATE_Z, frame, 0.0f);
  return true;
}

bool RchaEff::isGenelate(f32 frame) const {
  if (unknown19a4[EFFATR_TRANSLATE_Y] >= 0) {
    return unknown10[unknown19a4[EFFATR_TRANSLATE_Y]].getValue(frame) > 0.8f;
  }
  return false;
}

bool RchaEff::isEnd(f32 frame) const {
  if (unknown19a4[EFFATR_END] >= 0) {
    return unknown10[unknown19a4[EFFATR_END]].getValue(frame) > 0.8f;
  }
  return false;
}

bool RchaEff::isKill(f32 frame) const {
  if (unknown19a4[EFFATR_KILL] >= 0) {
    return unknown10[unknown19a4[EFFATR_KILL]].getValue(frame) > 0.8f;
  }
  return false;
}

bool RchaEff::getSpeed(f32 &speed, f32 frame) const {
  speed = getValue(EFFATR_TRANSLATE_X, frame, 0.0f);
  return true;
}
