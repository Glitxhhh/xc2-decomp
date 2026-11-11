#include "scn/scn_debug_manipu_trans_2d.h"

#include "ml/attr_transform.h"
#include "ml/scn.h"
#include "ml/scn_cam_util.h"
#include "ml/threadval.h"
#include "mm_math/mm_vec3.h"

namespace ml {

ScnDebugManipuTrans2D::ScnDebugManipuTrans2D(Scn *scn, const mm::Mat44 *matrix, const mm::Vec3 *scale) : ScnDebugManipuObj(SCNMANIPU_TRANS_2D, scn, matrix, scale) {
  unknown368 = 4;
  ScnObjCam *cam = scn->getCam(-1);
  if (cam != nullptr) {
    mm::Vec3 screen;
    ScnCamUtil::getScreenPos(screen, cam, false, mm::Vec3::zero);
    f32 x = screen.x > 0.0f ? 0.5f : -0.5f;
    f32 px = static_cast<int>(screen.x + x);
    screen.x = px;
    f32 y = screen.y > 0.0f ? 0.5f : -0.5f;
    y = static_cast<int>(screen.y + y);
    unknownb0.m_front->unknown00.unknown00 = mm::Vec3(px, y, 0.0f);
    unknownb0.m_back->unknown00.unknown00 = mm::Vec3(px, y, 0.0f);
  }
  unknown360 = 0;
}

ScnDebugManipuTrans2D::~ScnDebugManipuTrans2D() {}

} // namespace ml
