#include "framework/primitive.h"

#include <math.h>

#include "mm_math/mm_mat44.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_quat.h"

namespace fw {

// Inferred helper: quaternion of the rotation of a matrix; original name unknown. Evidence: inlined in PrimCapsule::setup
// (1.0.0: 0x7100197934), whose stack holds the four values and the pointers to the four components below the quaternion of the caller.
static void unknown001(mm::Quat &rotation, const mm::Mat44 &matrix) {
  f32 values[4];
  values[0] = ((matrix.rows[0][0] - matrix.rows[1][1]) - matrix.rows[2][2]) + 1.0f;
  values[1] = ((matrix.rows[1][1] - matrix.rows[0][0]) - matrix.rows[2][2]) + 1.0f;
  values[2] = (-matrix.rows[0][0] - matrix.rows[1][1]) + matrix.rows[2][2] + 1.0f;
  values[3] = matrix.rows[0][0] + matrix.rows[1][1] + matrix.rows[2][2] + 1.0f;
  u32 largest = 0;
  if (values[1] > values[0]) {
    largest = 1;
  }
  if (values[2] > values[largest]) {
    largest = 2;
  }
  if (values[3] > values[largest]) {
    largest = 3;
  }
  if (values[largest] < 0.0f) {
    rotation = mm::Quat::identity;
  } else {
    f32 *components[4] = {&rotation.x, &rotation.y, &rotation.z, &rotation.w};
    f32 root = sqrtf(values[largest]);
    *components[largest] = root * 0.5f;
    f32 scale = 0.25f / (root * 0.5f);
    switch (largest) {
    case 3:
      rotation.x = scale * (matrix.rows[1][2] - matrix.rows[2][1]);
      rotation.y = scale * (matrix.rows[2][0] - matrix.rows[0][2]);
      rotation.z = scale * (matrix.rows[0][1] - matrix.rows[1][0]);
      break;
    case 1:
      rotation.x = scale * (matrix.rows[0][1] + matrix.rows[1][0]);
      rotation.z = scale * (matrix.rows[1][2] + matrix.rows[2][1]);
      rotation.w = scale * (matrix.rows[2][0] - matrix.rows[0][2]);
      break;
    case 2:
      rotation.x = scale * (matrix.rows[2][0] + matrix.rows[0][2]);
      rotation.y = scale * (matrix.rows[1][2] + matrix.rows[2][1]);
      rotation.w = scale * (matrix.rows[0][1] - matrix.rows[1][0]);
      break;
    default:
      rotation.y = scale * (matrix.rows[0][1] + matrix.rows[1][0]);
      rotation.z = scale * (matrix.rows[2][0] + matrix.rows[0][2]);
      rotation.w = scale * (matrix.rows[1][2] - matrix.rows[2][1]);
      break;
    }
  }
}

void PrimCapsule::setup(const mm::Vec3 &start, const mm::Vec3 &end, f32 radius) {
  set(start, end);
  this->unknown30 = radius;
}

void PrimCapsule::setup(const mm::Mat44 &matrix, f32 length, f32 radius) {
  mm::Quat rotation;
  unknown001(rotation, matrix);
  mm::Vec3 position(matrix.rows[3][0], matrix.rows[3][1], matrix.rows[3][2]);
  setup(position, rotation, length, radius);
}

f32 PrimCapsule::getHeight() const {
  f32 x = start.x - end.x;
  f32 y = start.y - end.y;
  f32 z = start.z - end.z;
  return sqrtf(x * x + y * y + z * z);
}

void PrimCapsule::getRot(mm::Quat &rotation) const {
  const mm::Vec3 &axis = mm::Vec3::unitY;
  f32 dot = axis.x * direction.x + axis.y * direction.y + axis.z * direction.z;
  if (!(dot < -0.9999f)) {
    f32 x = axis.y * direction.z - direction.y * axis.z;
    f32 y = direction.x * axis.z - axis.x * direction.z;
    f32 z = axis.x * direction.y - direction.x * axis.y;
    f32 value = dot + 1.0f;
    value = value + value;
    f32 length = sqrtf(value);
    f32 scale = 1.0f / length;
    rotation.x = x * scale;
    rotation.y = y * scale;
    rotation.z = z * scale;
    rotation.w = length * 0.5f;
  } else {
    rotation.x = 0.0f;
    rotation.y = 1.0f;
    rotation.z = 0.0f;
    rotation.w = 0.0f;
  }
}

void PrimCapsule::getCenter(mm::Vec3 &center) const {
  center.x = end.x + start.x;
  center.y = end.y + start.y;
  center.z = end.z + start.z;
  center *= 0.5f;
}

void PrimCapsule::getMat(mm::Mat44 &matrix) const {
  mm::Quat rotation;
  getRot(rotation);
  mm::Vec3 center;
  getCenter(center);
  mm::unknown001(matrix, rotation);
  matrix.setTrans(center);
}

bool PrimCapsule::isCollide(const PrimCapsule &capsule) const { return getNearestLength(*this, capsule) <= unknown30 + capsule.unknown30; }

bool PrimCapsule::isCollide(const PrimSphere &sphere) const { return getNearestLength(*this, sphere.unknown00) <= unknown30 + sphere.unknown10; }

PrimCapsule &PrimCapsule::add(const mm::Vec3 &offset) {
  set(start + offset, offset + end);
  return *this;
}

void PrimSphere::setup(const mm::Vec3 &center, f32 radius) {
  this->unknown00 = center;
  this->unknown10 = radius;
}

void PrimSphere::getCenter(mm::Vec3 &center) const { center = this->unknown00; }

bool PrimSphere::isCollide(const PrimSphere &sphere) const {
  f32 distance = sphere.unknown10 + unknown10;
  f32 x = unknown00.x - sphere.unknown00.x;
  f32 y = unknown00.y - sphere.unknown00.y;
  f32 z = unknown00.z - sphere.unknown00.z;
  return x * x + y * y + z * z <= distance * distance;
}

bool PrimSphere::isCollide(const PrimCapsule &capsule) const { return mm::Line2::getNearestLength(capsule, unknown00) <= capsule.unknown30 + unknown10; }

PrimSphere &PrimSphere::add(const mm::Vec3 &offset) {
  unknown00 += offset;
  return *this;
}

} // namespace fw
