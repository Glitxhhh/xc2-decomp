#include "grlib/cglib_util_pixel.h"

namespace grlib {

f32 CGLibUtilPixel::convF16toF32(u16 value) {
  u32 exponent = (value >> 10) & 0x1f;
  u32 bits;
  if (exponent == 0x1f) {
    bits = 0x7f800000;
  } else if (exponent == 0) {
    bits = 0;
  } else {
    bits = exponent * 0x800000 + 0x38000000;
  }
  bits |= ((value & 0x8000) << 16) | ((value & 0x3ff) << 13);
  return *reinterpret_cast<f32 *>(&bits);
}
u16 CGLibUtilPixel::convF32toF16(f32 value) {
  u32 bits = *reinterpret_cast<u32 *>(&value);
  u32 exponent = (bits >> 23) & 0xff;
  u32 mantissa;
  u32 half;
  if (exponent == 0xff) {
    mantissa = (bits >> 13) & 0x3ff;
    half = 0x7c00;
  } else if (exponent < 0x66) {
    mantissa = 0;
    half = 0;
  } else if (exponent >= 0x8f) {
    mantissa = 0;
    half = 0x7c00;
  } else if (exponent < 0x71) {
    mantissa = (((bits & 0x7fffff) | 0x800000) >> (0x71 - exponent)) >> 13;
    half = 0;
  } else {
    mantissa = 0;
    half = exponent * 0x400 - 0x1c000;
  }
  return mantissa | ((bits >> 16) & 0x8000) | half;
}

} // namespace grlib
