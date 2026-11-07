#pragma once
#include <string.h>

#include "mm_math/mm_mat44.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace anm {
struct QsTransform;
} // namespace anm

namespace fw {

struct Transform {
  static void mul(const Transform &transform, const Transform &other, Transform *result);
  static void invert(const Transform &transform, Transform *result);

  // Inferred affine matrix conversion in AttachActorBase::render and the
  // AttachActorCS/Gf bone getters; original helper name unknown.
  void unknown001(mm::Mat44 &matrix) const {
    mm::unknown001(matrix, unknown10);
    mm::Vec3 translation;
    memcpy(&translation, &unknown00, sizeof(f32) * 3);
    matrix.setTrans(translation);
  }

  mm::Vec3 unknown00; // Inferred role: position; original member name unknown.
  mm::Quat unknown10; // Inferred role: rotation; original member name unknown.
};

static_assert(sizeof(Transform) == 0x20, "");

class TransformUtil {
public:
  static void mul(const Transform &transform, const anm::QsTransform &other, f32 scale, Transform *result);
};

} // namespace fw
