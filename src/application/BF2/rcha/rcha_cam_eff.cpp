#include "rcha/rcha_cam_eff.h"

#include "rcha/rcha_anm.h"

int RchaCamEff::getValueInt(int slot, f32 frame, int defaultValue) const {
  if (unknown19a4[slot] >= 0) {
    return unknown10[unknown19a4[slot]].getValueInt(frame);
  }
  return defaultValue;
}

f32 RchaCamEff::getValue(int slot, f32 frame, f32 defaultValue) const {
  if (unknown19a4[slot] >= 0) {
    return unknown10[unknown19a4[slot]].getValue(frame);
  }
  return defaultValue;
}

bool RchaCamEff::isEnableColFilter(f32 frame) const {
  if (unknown19a4[CAMATR_COL_FILTER] >= 0) {
    return unknown10[unknown19a4[CAMATR_COL_FILTER]].getValue(frame) > 0.9f;
  }
  return false;
}

bool RchaCamEff::getColFilter(int &filter, f32 frame) const {
  int index = unknown19a4[CAMATR_COL_FILTER];
  if (index >= 0) {
    filter = unknown10[index].getValueInt(frame);
    return true;
  }
  return false;
}

int RchaCamEff::getNearColFilter(f32 frame) const { return getValueInt(CAMATR_COL_FILTER_NEAR, frame, 0); }

int RchaCamEff::getFarColFilter(f32 frame) const { return getValueInt(CAMATR_COL_FILTER_FAR, frame, 0); }

f32 RchaCamEff::getFrColFilter(f32 frame) const { return getValue(CAMATR_COL_FILTER_FR, frame, 0.0f); }
