#pragma once

#include "dr/dr_mdo_ctl_seam.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {
class DrResMdoSeamWrkLight;

class DrMdoCtlSeamLight : public DrMdoCtlSeam {
public:
  void releaseLight();
  DrResMdoSeamWrkLight *createFreeSeamLight();
  void releaseFreeSeamLight(DrResMdoSeamWrkLight *light);
  bool readInstModelCheck(const mm::Vec3 &position, const f32 *max, const f32 *min);
};

} // namespace ml
