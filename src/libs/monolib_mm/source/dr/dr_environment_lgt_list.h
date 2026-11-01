#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {
class DrLightObj;
struct LgtObjData;
struct LgtPosData;

class DrEnvironmentLgtList {
public:
  void setLgtObjData(const LgtObjData *data);
  void setLgtPosData(const LgtPosData *data);
  void setLightObj(DrLightObj *lightObj);

  const LgtObjData *unknown00; // Inferred role: light object data; original member name unknown.
  const LgtPosData *unknown08; // Inferred role: light position data; original member name unknown.
  DrLightObj *unknown10;       // Inferred role: light object; original member name unknown.
  f32 unknown18;               // Inferred role: check result weight, set to 1.0 by the DrEnvironmentObjLgt check callbacks; original member name unknown.
  int unknown1c;               // Inferred role: index of the list, bit of DrEnvironmentObjLgt::unknown188; original member name unknown.
};

static_assert(offsetof(DrEnvironmentLgtList, unknown08) == 0x08, "");
static_assert(offsetof(DrEnvironmentLgtList, unknown10) == 0x10, "");
static_assert(offsetof(DrEnvironmentLgtList, unknown18) == 0x18, "");
static_assert(offsetof(DrEnvironmentLgtList, unknown1c) == 0x1c, "");
static_assert(sizeof(DrEnvironmentLgtList) == 0x20, "");

} // namespace ml
