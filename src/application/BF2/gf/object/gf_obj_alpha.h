#pragma once
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;
class GfObjAcc;
class GfComProperty;

class GfObjAlpha {
public:
  static void updateCamera(GF_OBJ_HANDLE *handle, f32 deltaTime, bool isForce);
  static bool isNearCamera(const GfObjAcc &acc);
  static f32 getTotalAlpha(const GfComProperty *property);
};

} // namespace gf
