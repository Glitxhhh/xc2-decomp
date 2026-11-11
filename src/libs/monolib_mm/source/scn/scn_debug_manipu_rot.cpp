#include "scn/scn_debug_manipu_rot.h"

namespace ml {

ScnDebugManipuRot::ScnDebugManipuRot(Scn *scn, const mm::Mat44 *matrix, const mm::Vec3 *scale) : ScnDebugManipuObj(SCNMANIPU_ROT, scn, matrix, scale) {
  unknown970 = 0;
  unknown990 = 70.0f;
  unknown994 = 80.0f;
}

ScnDebugManipuRot::~ScnDebugManipuRot() {}

} // namespace ml
