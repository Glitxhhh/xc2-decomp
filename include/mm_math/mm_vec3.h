#pragma once
#include <math.h>

#include "types.h"

namespace mm {

inline bool isValidFloat(f32 value) {
  u32 bits = *reinterpret_cast<u32 *>(&value);
  return bits != 0xcccccccc && (bits & 0x7f800000) != 0x7f800000;
}

struct alignas(16) Vec3 {
  static const Vec3 zero;  // Name from the game symbol _ZN2mm4Vec34zeroE; also in torna and xc1de.
  static const Vec3 unit;  // Name from the game symbol _ZN2mm4Vec34unitE; also in torna and xc1de.
  static const Vec3 unitX; // Name from the game symbol _ZN2mm4Vec35unitXE; also in torna and xc1de.
  static const Vec3 unitY; // Name from the game symbol _ZN2mm4Vec35unitYE; also in torna and xc1de.
  static const Vec3 unitZ; // Name from the game symbol _ZN2mm4Vec35unitZE; also in torna and xc1de.

  Vec3() {}
  Vec3(f32 x, f32 y, f32 z) : x(x), y(y), z(z) {}
  // Assigns in the body: a mem-initializer list changes the address order of the Vector copy loops, which the game's code does not have.
  Vec3(const Vec3 &vector) {
    x = vector.x;
    y = vector.y;
    z = vector.z;
  }

  Vec3 &operator=(const Vec3 &vector) {
    x = vector.x;
    y = vector.y;
    z = vector.z;
    return *this;
  }

  Vec3 &operator=(Vec3 &&vector) {
    if (this != &vector) {
      x = vector.x;
      y = vector.y;
      z = vector.z;
    }
    return *this;
  }

  Vec3 operator+(const Vec3 &vector) const { return Vec3(x + vector.x, y + vector.y, z + vector.z); }

  Vec3 operator-(const Vec3 &vector) const { return Vec3(x - vector.x, y - vector.y, z - vector.z); }

  Vec3 operator*(f32 scale) const { return Vec3(x * scale, y * scale, z * scale); }

  Vec3 &operator+=(const Vec3 &vector) {
    x = x + vector.x;
    y = y + vector.y;
    z = z + vector.z;
    return *this;
  }

  Vec3 &operator-=(const Vec3 &vector) {
    x = x - vector.x;
    y = y - vector.y;
    z = z - vector.z;
    return *this;
  }

  Vec3 &operator*=(f32 scale) {
    x = x * scale;
    y = y * scale;
    z = z * scale;
    return *this;
  }

  bool isError() const { return !isValidFloat(x) || !isValidFloat(y) || !isValidFloat(z); }
  // Name from the assertion texts of anm::FootPlacementIKSolver (for example "m_desc.worldUpWS.isUnit()").
  bool isUnit() const { return fabsf(sqrtf(x * x + y * y + z * z) - 1.0f) <= 0.000001f; }
  // Inferred role: normalizes, zero when shorter than 1e-6; original name unknown.
  void unknown001() {
    f32 length = sqrtf(x * x + y * y + z * z);
    if (length <= 0.000001f) {
      *this = zero;
    } else {
      *this *= 1.0f / length;
    }
  }

  f32 x;
  f32 y;
  f32 z;
};

} // namespace mm
