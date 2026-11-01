#pragma once
#include <math.h>

#include "mm_math/mm_vec3.h"
#include "types.h"

namespace mm {

struct Plane {
  Plane() {}
  Plane(const Vec3 &normal, f32 distance) : normal(normal), distance(distance) {}

  // Inferred role: normalizes the normal, zero when it is too short; original name unknown.
  void unknown001() {
    f32 length = sqrtf(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
    if (length <= 0.000001f) {
      normal = Vec3::zero;
    } else {
      f32 scale = 1.0f / length;
      normal.x = normal.x * scale;
      normal.y = normal.y * scale;
      normal.z = normal.z * scale;
    }
  }

  // Inferred role: sets the plane from a normal, normalized, and a distance; original name unknown.
  void unknown002(const Vec3 &direction, f32 offset) {
    normal = direction;
    unknown001();
    distance = offset;
  }

  void set(const Vec3 &direction, const Vec3 &position) {
    normal = direction;
    unknown001();
    distance = -(normal.x * position.x + normal.y * position.y + normal.z * position.z);
  }

  Vec3 normal;
  f32 distance;
};

static_assert(sizeof(Plane) == 0x20, "");

} // namespace mm
