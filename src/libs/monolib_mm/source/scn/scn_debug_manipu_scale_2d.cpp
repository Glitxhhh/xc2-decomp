#include "scn/scn_debug_manipu_scale_2d.h"

#include "ml/attr_transform.h"
#include "ml/scn.h"
#include "ml/scn_cam_util.h"
#include "ml/threadval.h"
#include "mm_math/mm_vec3.h"

namespace ml {

ScnDebugManipuScale2D::ScnDebugManipuScale2D(Scn *scn, const mm::Mat44 *matrix, const mm::Vec3 *scale) : ScnDebugManipuObj(SCNMANIPU_UNKNOWN_4, scn, matrix, scale) {
  unknown368 = 4;
  ScnObjCam *cam = scn->getCam(-1);
  if (cam != nullptr) {
    mm::Vec3 screen;
    ScnCamUtil::getScreenPos(screen, cam, false, mm::Vec3::zero);
    f32 x = screen.x > 0.0f ? 0.5f : -0.5f;
    screen.x = static_cast<int>(screen.x + x);
    f32 y = screen.y > 0.0f ? 0.5f : -0.5f;
    y = static_cast<int>(screen.y + y);
    mm::Vec3 position(screen.x, y, 0.0f);
    unknownb0.m_front->unknown00.unknown00 = position;
    unknownb0.m_back->unknown00.unknown00 = position;
  }
  unknown360 = 0;
}

ScnDebugManipuScale2D::~ScnDebugManipuScale2D() {}

} // namespace ml
