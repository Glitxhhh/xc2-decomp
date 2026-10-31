#pragma once
#include <stddef.h>

#include "types.h"

namespace gf {
namespace pc {

// Field names and offsets from the reflection built by gf::pc::FieldParam::createReflection.
struct FieldParam {
  f32 accelThreshold;
  u32 stopCnt;
  f32 turnAngle;
  f32 turnEndAngle;
  f32 turnInputThreshold;
  f32 backAngle;
  f32 ignoreTimeJump;
  f32 waterSlow;
  f32 poisonSlow;
  f32 stopMotionThreshold;
  f32 stopMotionThresholdWater;
};

static_assert(offsetof(FieldParam, stopCnt) == 0x04, "");
static_assert(offsetof(FieldParam, turnEndAngle) == 0x0c, "");
static_assert(offsetof(FieldParam, backAngle) == 0x14, "");
static_assert(offsetof(FieldParam, ignoreTimeJump) == 0x18, "");
static_assert(offsetof(FieldParam, stopMotionThresholdWater) == 0x28, "");
static_assert(sizeof(FieldParam) == 0x2c, "");

// Field names and offsets from the reflection built by gf::pc::WaterCommonParam::createReflection.
struct WaterCommonParam {
  f32 sinkTime;
  f32 sinkDepth;
  f32 swimEnableSpeed;
  f32 swimSinkTime;
  f32 riseBrakeHeight;
  f32 swimMotionMin;
  f32 waterHoleDiveTime;
  f32 waterDeadVelMin;
  f32 waterDiveMinSpeed;
};

static_assert(offsetof(WaterCommonParam, waterDiveMinSpeed) == 0x20, "");
static_assert(sizeof(WaterCommonParam) == 0x24, "");

} // namespace pc
} // namespace gf
