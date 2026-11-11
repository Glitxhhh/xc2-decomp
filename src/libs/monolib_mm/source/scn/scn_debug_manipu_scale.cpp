#include "scn/scn_debug_manipu_scale.h"

#include "mm_math/mm_vec3.h"

namespace ml {

ScnDebugManipuScale::ScnDebugManipuScale(Scn *scn, const mm::Mat44 *matrix, const mm::Vec3 *scale) : ScnDebugManipuObj(SCNMANIPU_SCALE, scn, matrix, scale) {
  unknown380 = 0;
  unknown388 = 7;
  unknown390 = mm::Vec3::zero;
}

ScnDebugManipuScale::~ScnDebugManipuScale() {}

} // namespace ml
