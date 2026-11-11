#pragma once
#include <stddef.h>

#include "rcha/rcha_anm.h"
#include "rcha/rcha_node.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

class RchaChrEff : public RchaNode {
public:
  static const int NAME_COUNT = 20;

  // Slots of unknown19a4, in the order of the names (chrEff/ tracks) that setup looks for.
  enum {
    CHREFF_VOLUME_FADE = 0,
    CHREFF_VOLUME_FADE_ID = 1,
    CHREFF_VOLUME_FADE_UVW_SCALE_X = 2,
    CHREFF_VOLUME_FADE_UVW_SCALE_Y = 3,
    CHREFF_VOLUME_FADE_UVW_SCALE_Z = 4,
    CHREFF_VOLUME_FADE_CENTER_POS_X = 5,
    CHREFF_VOLUME_FADE_CENTER_POS_Y = 6,
    CHREFF_VOLUME_FADE_CENTER_POS_Z = 7,
    CHREFF_VOLUME_FADE_DISTANCE = 8,
    CHREFF_VOLUME_FADE_DIRECTIVITY = 9,
    CHREFF_VOLUME_FADE_MESH_NO = 10,
    CHREFF_VOLUME_FADE_RATIO = 11,
    CHREFF_RIM_BLOOM = 12,
    CHREFF_RIM_BLOOM_ID = 13,
    CHREFF_AFTER_IMAGE = 14,
    CHREFF_AFTER_IMAGE_ID1 = 15,
    CHREFF_AFTER_IMAGE_ID2 = 16,
    CHREFF_AFTER_IMAGE_CAPTURE_FRAME = 17,
    CHREFF_AFTER_IMAGE_EXIST_FRAME = 18,
    CHREFF_AFTER_IMAGE_FADE_OUT_FRAME = 19,
  };

  RchaChrEff();
  virtual void clear();
  virtual bool setup(mtl::ALLOC_HANDLE handle, const void *data);
  static bool hasAnm(const void *data);
  f32 getValue(int slot, f32 frame, f32 defaultValue) const;
  int getValueInt(int slot, f32 frame, int defaultValue) const;
  bool getVolumeFade(int &type, f32 frame) const;
  bool getVolumeFadeId(int &id, f32 frame) const;
  void getVolumeFadeUVWScale(mm::Vec3 &scale, f32 frame) const;
  void getVolumeFadeCenterPos(mm::Vec3 &pos, f32 frame) const;
  bool getVolumeFadeDistance(f32 &distance, f32 frame) const;
  bool getVolumeFadeDirectivity(f32 &directivity, f32 frame) const;
  bool getVolumeFadeMesh(int &mesh, f32 frame) const;
  bool getVolumeFadeRatio(f32 &ratio, f32 frame) const;
  bool getRimBloom(int &type, f32 frame) const;
  bool getRimBloomId(int &id, f32 frame) const;
  bool getAfterImage(int &type, f32 frame) const;
  bool getAfterImageId1(int &id, f32 frame) const;
  bool getAfterImageId2(int &id, f32 frame) const;
  bool getAfterImageCaptureFrame(f32 &captureFrame, f32 frame) const;
  bool getAfterImageExistFrame(f32 &existFrame, f32 frame) const;
  bool getAfterImageFadeOutFrame(f32 &fadeOutFrame, f32 frame) const;

private:
  // Inferred helpers: read the track of a slot as an int or a float when the resource has it; original names unknown.
  bool unknown001(int &value, int slot, f32 frame) const {
    int index = unknown19a4[slot];
    if (index >= 0) {
      value = unknown10[index].getValueInt(frame);
      return true;
    }
    return false;
  }

  bool unknown002(f32 &value, int slot, f32 frame) const {
    int index = unknown19a4[slot];
    if (index >= 0) {
      value = unknown10[index].getValue(frame);
      return true;
    }
    return false;
  }

  bool unknown19a0;            // Inferred role: has any named track; original member name unknown.
  int unknown19a4[NAME_COUNT]; // Inferred role: track index of each name; original member name unknown.

  friend struct RchaChrEffLayout;
};

struct RchaChrEffLayout {
  static_assert(offsetof(RchaChrEff, unknown19a0) == 0x19a0, "");
  static_assert(offsetof(RchaChrEff, unknown19a4) == 0x19a4, "");
  static_assert(sizeof(RchaChrEff) == 0x19f8, "");
};
