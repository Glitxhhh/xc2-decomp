#pragma once
#include "mm/mm_std_base.h"
#include "mm_math/mm_quat.h"
#include "types.h"

namespace mm {

// __LINE__ must be 86 as in the original header: it is the line argument of the assert.
#line 85
inline void Quat::inverse(Quat &qa) {
  MM_ASSERT(!qa.isZero());
  f32 scale = 1.0f / (qa.x * qa.x + qa.y * qa.y + qa.z * qa.z + qa.w * qa.w);
  qa.x = -(qa.x * scale);
  qa.y = -(qa.y * scale);
  qa.z = -(qa.z * scale);
  qa.w = qa.w * scale;
}

} // namespace mm
