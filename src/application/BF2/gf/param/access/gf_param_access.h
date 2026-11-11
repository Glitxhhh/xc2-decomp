#pragma once
#include <stddef.h>

#include "types.h"

namespace fw {
class Reflection;
} // namespace fw

namespace gf {

// Field names and offsets from the reflection built by gf::AccessParam::createReflection.
struct AccessParam {
  static void createReflection(fw::Reflection *reflection, const char *name, u32 index);

  // Inferred helper: tests whether a height lies in the range of the access param, shared by gf::pc::isActiveRange and
  // gf::pc::isActiveRangeLure; original name unknown. Only the non short-circuit and matches the game.
  static bool unknown001(f32 value, f32 maximum, f32 minimum) { return (value <= maximum) & (minimum <= value); }

  f32 offsetFront;
  f32 accessRadius;
  f32 accessUpper;
  f32 accessDown;
};

static_assert(offsetof(AccessParam, accessRadius) == 0x04, "");
static_assert(offsetof(AccessParam, accessUpper) == 0x08, "");
static_assert(offsetof(AccessParam, accessDown) == 0x0c, "");
static_assert(sizeof(AccessParam) == 0x10, "");

// Parameters of gf_param_access.cpp; the layouts are not reconstructed yet.

struct LookParam {
  static void createReflection(fw::Reflection *reflection, const char *name, u32 index);
};

struct ItemGetParam {
  static void createReflection(fw::Reflection *reflection, const char *name, u32 index);

  f32 radius;
  f32 upper;
  f32 lower;
};

static_assert(offsetof(ItemGetParam, upper) == 0x04, "");
static_assert(offsetof(ItemGetParam, lower) == 0x08, "");
static_assert(sizeof(ItemGetParam) == 0x0c, "");

} // namespace gf
