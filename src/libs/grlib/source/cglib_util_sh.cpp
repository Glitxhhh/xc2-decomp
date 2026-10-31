#include "grlib/cglib_util_sh.h"

#include <math.h>

#include "mm_math/mm_vec3.h"

namespace grlib {

// Layout evidence: grlib::sgFace2DMapping (0x71011b1050, 0x120 bytes) is read by TexelCoordToVect (0x71007ac120) as
// three 16-byte vectors per cube map face (offsets 0x0, 0x10 and 0x20, stride 0x30).
mm::Vec3 sgFace2DMapping[6][3] = {
    {mm::Vec3(0.0f, 0.0f, -1.0f), mm::Vec3(0.0f, -1.0f, 0.0f), mm::Vec3(1.0f, 0.0f, 0.0f)},
    {mm::Vec3(0.0f, 0.0f, 1.0f), mm::Vec3(0.0f, -1.0f, 0.0f), mm::Vec3(-1.0f, 0.0f, 0.0f)},
    {mm::Vec3(1.0f, 0.0f, 0.0f), mm::Vec3(0.0f, 0.0f, 1.0f), mm::Vec3(0.0f, 1.0f, 0.0f)},
    {mm::Vec3(1.0f, 0.0f, 0.0f), mm::Vec3(0.0f, 0.0f, -1.0f), mm::Vec3(0.0f, -1.0f, 0.0f)},
    {mm::Vec3(1.0f, 0.0f, 0.0f), mm::Vec3(0.0f, -1.0f, 0.0f), mm::Vec3(0.0f, 0.0f, 1.0f)},
    {mm::Vec3(-1.0f, 0.0f, 0.0f), mm::Vec3(0.0f, -1.0f, 0.0f), mm::Vec3(0.0f, 0.0f, -1.0f)},
};

void CGLibUtilSH::TexelCoordToVect(mm::Vec3 &vector, int face, f32 u, f32 v, int size) {
  f32 s = (u + 0.5f) * 2.0f / size - 1.0f;
  f32 t = (v + 0.5f) * 2.0f / size - 1.0f;
  const mm::Vec3 *mapping = sgFace2DMapping[face];
  vector.x = s * mapping[0].x;
  vector.y = s * mapping[0].y;
  vector.z = s * mapping[0].z;
  vector += mapping[1] * t;
  vector.x = mapping[2].x + vector.x;
  vector.y = mapping[2].y + vector.y;
  vector.z = mapping[2].z + vector.z;
  f32 length = sqrtf(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
  if (length <= 0.000001f) {
    vector = mm::Vec3::zero;
  } else {
    f32 scale = 1.0f / length;
    vector.x = scale * vector.x;
    vector.y = scale * vector.y;
    vector.z = scale * vector.z;
  }
}

} // namespace grlib
