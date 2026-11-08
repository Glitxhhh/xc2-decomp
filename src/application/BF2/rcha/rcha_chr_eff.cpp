#include "rcha/rcha_chr_eff.h"

#include "mm_math/mm_vec3.h"
#include "rcha/rcha_anm.h"

bool RchaChrEff::getVolumeFade(int &type, f32 frame) const { return unknown001(type, CHREFF_VOLUME_FADE, frame); }

int RchaChrEff::getValueInt(int slot, f32 frame, int defaultValue) const {
  if (unknown19a4[slot] >= 0) {
    return unknown10[unknown19a4[slot]].getValueInt(frame);
  }
  return defaultValue;
}

bool RchaChrEff::getVolumeFadeId(int &id, f32 frame) const { return unknown001(id, CHREFF_VOLUME_FADE_ID, frame); }

void RchaChrEff::getVolumeFadeUVWScale(mm::Vec3 &scale, f32 frame) const {
  scale.x = getValue(CHREFF_VOLUME_FADE_UVW_SCALE_X, frame, 0.0f);
  scale.y = getValue(CHREFF_VOLUME_FADE_UVW_SCALE_Y, frame, 0.0f);
  scale.z = getValue(CHREFF_VOLUME_FADE_UVW_SCALE_Z, frame, 0.0f);
}

f32 RchaChrEff::getValue(int slot, f32 frame, f32 defaultValue) const {
  if (unknown19a4[slot] >= 0) {
    return unknown10[unknown19a4[slot]].getValue(frame);
  }
  return defaultValue;
}

void RchaChrEff::getVolumeFadeCenterPos(mm::Vec3 &pos, f32 frame) const {
  pos.x = getValue(CHREFF_VOLUME_FADE_CENTER_POS_X, frame, 0.0f);
  pos.y = getValue(CHREFF_VOLUME_FADE_CENTER_POS_Y, frame, 0.0f);
  pos.z = getValue(CHREFF_VOLUME_FADE_CENTER_POS_Z, frame, 0.0f);
}

bool RchaChrEff::getVolumeFadeDistance(f32 &distance, f32 frame) const { return unknown002(distance, CHREFF_VOLUME_FADE_DISTANCE, frame); }

bool RchaChrEff::getVolumeFadeDirectivity(f32 &directivity, f32 frame) const { return unknown002(directivity, CHREFF_VOLUME_FADE_DIRECTIVITY, frame); }

bool RchaChrEff::getVolumeFadeMesh(int &mesh, f32 frame) const { return unknown001(mesh, CHREFF_VOLUME_FADE_MESH_NO, frame); }

bool RchaChrEff::getVolumeFadeRatio(f32 &ratio, f32 frame) const { return unknown002(ratio, CHREFF_VOLUME_FADE_RATIO, frame); }

bool RchaChrEff::getRimBloom(int &type, f32 frame) const { return unknown001(type, CHREFF_RIM_BLOOM, frame); }

bool RchaChrEff::getRimBloomId(int &id, f32 frame) const { return unknown001(id, CHREFF_RIM_BLOOM_ID, frame); }

bool RchaChrEff::getAfterImage(int &type, f32 frame) const { return unknown001(type, CHREFF_AFTER_IMAGE, frame); }

bool RchaChrEff::getAfterImageId1(int &id, f32 frame) const { return unknown001(id, CHREFF_AFTER_IMAGE_ID1, frame); }

bool RchaChrEff::getAfterImageId2(int &id, f32 frame) const { return unknown001(id, CHREFF_AFTER_IMAGE_ID2, frame); }

bool RchaChrEff::getAfterImageCaptureFrame(f32 &captureFrame, f32 frame) const { return unknown002(captureFrame, CHREFF_AFTER_IMAGE_CAPTURE_FRAME, frame); }

bool RchaChrEff::getAfterImageExistFrame(f32 &existFrame, f32 frame) const { return unknown002(existFrame, CHREFF_AFTER_IMAGE_EXIST_FRAME, frame); }

bool RchaChrEff::getAfterImageFadeOutFrame(f32 &fadeOutFrame, f32 frame) const { return unknown002(fadeOutFrame, CHREFF_AFTER_IMAGE_FADE_OUT_FRAME, frame); }

void RchaChrEff::clear() {
  RchaNode::clear();
  unknown19a0 = false;
}
