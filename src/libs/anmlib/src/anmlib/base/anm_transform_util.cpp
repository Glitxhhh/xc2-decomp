#include "anm/anm_transform_util.h"

#include "anm/anm_qs_transform.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_quat_impl_nx.h"
#include "mm_math/mm_vec3.h"
#include "mm_math/mm_vec4.h"
#include "types.h"

namespace anm {

void TransformUtil::mul(const QsTransform &lhs, const QsTransform &rhs, QsTransform *result) {
  const mm::Quat &q = lhs.unknown10;
  const mm::Vec4 &v = rhs.unknown00;
  f32 tx = (q.y * v.z - q.z * v.y) + q.w * v.x;
  f32 ty = (q.z * v.x - v.z * q.x) + v.y * q.w;
  f32 tz = (v.y * q.x - q.y * v.x) + v.z * q.w;
  f32 tw = (-(v.x * q.x) - q.y * v.y) - v.z * q.z;
  f32 rx = -(q.z * ty) + q.y * tz - q.x * tw + q.w * tx;
  f32 ry = -(q.x * tz) + q.z * tx - q.y * tw + q.w * ty;
  f32 rz = -(q.y * tx) + q.x * ty - q.z * tw + q.w * tz;
  mm::Vec4 translation;
  translation.x = lhs.unknown00.x + rx;
  translation.y = lhs.unknown00.y + ry;
  translation.z = lhs.unknown00.z + rz;
  translation.w = rhs.unknown00.w + lhs.unknown00.w;
  result->unknown00 = translation;
  result->unknown10 = mm::Quat::mul(rhs.unknown10, lhs.unknown10);
  mm::Vec4 scale;
  scale.x = lhs.unknown20.x * rhs.unknown20.x;
  scale.y = lhs.unknown20.y * rhs.unknown20.y;
  scale.z = lhs.unknown20.z * rhs.unknown20.z;
  scale.w = lhs.unknown20.w * rhs.unknown20.w;
  result->unknown20 = scale;
}

void TransformUtil::invert(const QsTransform &transform, QsTransform *result) {
  result->unknown10 = transform.unknown10;
  mm::Quat::inverse(result->unknown10);
  mm::Vec4 negated;
  negated.x = -transform.unknown00.x;
  negated.y = -transform.unknown00.y;
  negated.z = -transform.unknown00.z;
  negated.w = -transform.unknown00.w;
  const mm::Quat &q = result->unknown10;
  f32 tx = q.y * negated.z - q.z * negated.y + q.w * negated.x;
  f32 ty = q.z * negated.x - negated.z * q.x + negated.y * q.w;
  f32 tz = negated.y * q.x - q.y * negated.x + negated.z * q.w;
  f32 tw = -negated.x * q.x - q.y * negated.y - negated.z * q.z;
  result->unknown00.x = -(q.z * ty) + q.y * tz - q.x * tw + q.w * tx;
  result->unknown00.y = -(q.x * tz) + q.z * tx - q.y * tw + q.w * ty;
  result->unknown00.z = -(q.y * tx) + q.x * ty - q.z * tw + q.w * tz;
  result->unknown00.w = negated.w;
  mm::Vec4 scale;
  scale.x = mm::Vec4::unit.x / transform.unknown20.x;
  scale.y = mm::Vec4::unit.y / transform.unknown20.y;
  scale.z = mm::Vec4::unit.z / transform.unknown20.z;
  scale.w = mm::Vec4::unit.w / transform.unknown20.w;
  result->unknown20 = scale;
}

void TransformUtil::calcMatrix(const QsTransform &transform, mm::Mat44 *matrix) {
  f32 scaleX = transform.unknown20.x;
  f32 scaleY = transform.unknown20.y;
  f32 scaleZ = transform.unknown20.z;
  matrix->unknown010(scaleX, scaleY, scaleZ);
  mm::Mat44 rotation;
  mm::unknown001(rotation, transform.unknown10);
  mm::Mat44 result;
  result.unknown008(*matrix, rotation);
  *matrix = result;
  matrix->setTrans(mm::Vec3(transform.unknown00.x, transform.unknown00.y, transform.unknown00.z));
}

} // namespace anm
