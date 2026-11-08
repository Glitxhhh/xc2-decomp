#pragma once
#include <stddef.h>

#include "rcha/rcha_node.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

class RchaCam : public RchaNode {
public:
  static const int NAME_COUNT = 30;

  // Slots of unknown19a4, in the order of the names (cam/ and camAtr/ tracks) that setup looks for.
  enum {
    CAM_TRANSLATE_X = 0,
    CAM_TRANSLATE_Y = 1,
    CAM_TRANSLATE_Z = 2,
    CAM_ROTATE_X = 3,
    CAM_ROTATE_Y = 4,
    CAM_ROTATE_Z = 5,
    CAM_ROTATE_ORDER = 6,
    CAMATR_NEAR = 7, // camAtr/translate_x
    CAMATR_FAR = 8,  // camAtr/translate_y
    CAMATR_FOV = 9,  // camAtr/translate_z
    CAMATR_DOF = 10,
    CAMATR_DOF_DISTANCE = 11,
    CAMATR_DOF_RANGE = 12,
    CAMATR_DOF_PIXEL = 13,
    CAMATR_DOF_LENS = 14,
    CAMATR_DOF_STRENGTH = 15,
    CAMATR_DOF_BLEND = 16,
    CAMATR_DOF_PIXEL_LV = 17,
    CAMATR_DOF_HLV = 18,
    CAMATR_MBLUR = 19,
    CAMATR_MBLUR_STR = 20,
    CAMATR_MBLUR_SUB = 21,
    CAMATR_SM_VIS = 22,
    CAMATR_CLOCK = 23,
    CAMATR_CLOCK_HOUR = 24,
    CAMATR_WTR = 25,
    CAMATR_WTR_TYPE = 26,
    CAMATR_WTR_FADE = 27,
    CAMATR_CAM_LGT = 28,
    CAMATR_NEAR_FAR = 29,
  };

  RchaCam();
  virtual ~RchaCam();
  virtual bool setup(mtl::ALLOC_HANDLE handle, const void *data);
  f32 getValue(int slot, f32 frame, f32 defaultValue) const;
  int getValueInt(int slot, f32 frame, int defaultValue) const;
  bool getPos(mm::Vec3 *pos, f32 frame) const;
  bool getRot(mm::Vec3 *rot, f32 frame) const;
  int getRotOrder(f32 frame) const;
  f32 getFov(f32 frame) const;
  f32 getNear(f32 frame) const;
  f32 getFar(f32 frame) const;
  f32 getMBlurStr(f32 frame) const;
  bool isEnableMBlur(f32 frame) const;
  f32 getMBlurSub(f32 frame) const;
  bool isEnableDOF(f32 frame) const;
  f32 getDistanceDOF(f32 frame) const;
  f32 getRangeDOF(f32 frame) const;
  f32 getPixelDOF(f32 frame) const;
  f32 getLensDOF(f32 frame) const;
  f32 getStrengthDOF(f32 frame) const;
  f32 getBlendDOF(f32 frame) const;
  int getPixelLvDOF(f32 frame) const;
  bool isHlvDOF(f32 frame) const;
  bool isSMapVis(f32 frame) const;
  bool isEnableTime(f32 frame) const;
  f32 getTimeVal(f32 frame) const;
  bool isEnableWeather(f32 frame) const;
  bool isCamLgtStop(f32 frame) const;
  int getNearFarType(f32 frame) const;
  int getWeatherType(f32 frame) const;
  int getWeatherFrame(f32 frame) const;

private:
  bool unknown19a0;            // Inferred role: has any named track; original member name unknown.
  int unknown19a4[NAME_COUNT]; // Inferred role: track index of each name; original member name unknown.

  friend struct RchaCamLayout;
};

struct RchaCamLayout {
  static_assert(offsetof(RchaCam, unknown19a0) == 0x19a0, "");
  static_assert(offsetof(RchaCam, unknown19a4) == 0x19a4, "");
  static_assert(sizeof(RchaCam) == 0x1a20, "");
};
