#pragma once
#include <stddef.h>

#include "dr/dr_calc_clip_work.h"
#include "types.h"

namespace mm {
struct Mat44;
} // namespace mm

namespace ml {

class DrCalcClipWorkPlane : public DrCalcClipWork {
public:
  DrCalcClipWorkPlane();
  ~DrCalcClipWorkPlane();
  void setMatrix(const mm::Mat44 &matrix);
  bool clipTest(const mm::Vec3 &position, f32 radius) const override;
  int clipTypeTest(const mm::Vec3 &position, f32 radius) const override;

  unknown001 unknown10[6]; // Inferred role: clip planes; original member name unknown.
};

static_assert(offsetof(DrCalcClipWorkPlane, unknown10) == 0x10, "");
static_assert(sizeof(DrCalcClipWorkPlane) == 0xd0, "");

} // namespace ml
