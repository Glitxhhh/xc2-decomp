#pragma once
#include <stddef.h>

#include "fw/fw_param_manager.h"
#include "types.h"

namespace fw {
class Reflection;
struct UpdateInfo;
} // namespace fw

namespace gf {

class GfMoveFallControler {
public:
  // Field names and offsets from the reflection built by createReflection.
  struct Param {
    f32 accel;
    f32 speedMax;
  };

  struct Packet {
    Packet() : unknown08() {}

    f32 unknown00;              // Inferred role: vertical speed; original member name unknown.
    fw::ParamAdapter unknown08; // Inferred role: fall param; original member name unknown.
  };

  static void createReflection(fw::Reflection *reflection, const char *name, u32 index);
  void update(const fw::UpdateInfo &info, Packet &packet);
};

static_assert(offsetof(GfMoveFallControler::Param, speedMax) == 0x04, "");
static_assert(sizeof(GfMoveFallControler::Param) == 0x08, "");
static_assert(offsetof(GfMoveFallControler::Packet, unknown08) == 0x08, "");
static_assert(sizeof(GfMoveFallControler::Packet) == 0x10, "");

} // namespace gf
