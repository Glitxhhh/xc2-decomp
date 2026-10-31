#pragma once
#include <stddef.h>

#include "types.h"

namespace gf {
namespace pc {

// Field names and offsets from the reflection built by gf::pc::SlideParam::createReflection (gf_pc_param.cpp).
struct SlideParam {
  f32 minAngle;
  f32 maxSpeed;
  f32 gravity;
  f32 friction;
  f32 slideFriction;
  f32 stopVel;
  f32 startTime;
  f32 startVel;
  f32 endVel;
  f32 fallDistance;
  f32 slideLandHeight;
  f32 ignoreLandTime;
};

static_assert(offsetof(SlideParam, stopVel) == 0x14, "");
static_assert(offsetof(SlideParam, fallDistance) == 0x24, "");
static_assert(offsetof(SlideParam, ignoreLandTime) == 0x2c, "");
static_assert(sizeof(SlideParam) == 0x30, "");

} // namespace pc
} // namespace gf
