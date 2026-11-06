#include "anm/anm_two_joint_ik_solver.h"

#include "mm/mm_std_base.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace anm {

#line 26
void projectNormal(const mm::Vec3 &normal, const mm::Vec3 &vector, mm::Vec3 *pPerpendicular, mm::Vec3 *pParallel) {
  MM_ASSERT(normal.isUnit());
  f32 dot = normal.x * vector.x + normal.y * vector.y + normal.z * vector.z;
  *pParallel = normal * dot;
  *pPerpendicular = vector - *pParallel;
}

} // namespace anm
