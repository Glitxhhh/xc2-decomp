#include "scn/scn_debug_manipu_trans.h"

namespace ml {

ScnDebugManipuTrans::ScnDebugManipuTrans(Scn *scn, const mm::Mat44 *matrix, const mm::Vec3 *scale) : ScnDebugManipuObj(SCNMANIPU_TRANS, scn, matrix, scale) {
  unknown380 = 0;
  unknown388 = 7;
}

ScnDebugManipuTrans::~ScnDebugManipuTrans() {}

} // namespace ml
