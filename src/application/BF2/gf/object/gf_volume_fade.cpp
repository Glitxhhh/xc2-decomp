#include "gf/object/gf_volume_fade.h"

#include "gf/object/gf_obj_setup.h"

namespace gf {

GfVolumeFade::GfVolumeFade(GF_OBJ_HANDLE *handle, ml::ScnObjModel *model) : unknown00(handle), unknown08(model) { initializeParam(); }

void GfVolumeFade::initializeParam() {
  for (u32 acc = 0; acc < 5; acc++) {
    for (u32 parts = 0; parts < 6; parts++) {
      unknown14[acc][parts] = 1.0f;
    }
  }
  unknown140 = VFEFF_UNKNOWN_0;
  unknown10 = true;
}

f32 GfVolumeFade::getFadeRatio(VFACC acc, VFPARTS parts) const {
  if (parts != VFPARTS_UNKNOWN_FFFFFFFF) {
    return unknown14[acc][parts];
  }
  f32 total = 0.0f;
  for (u32 i = 0; i < 6; i++) {
    total += unknown14[acc][i];
  }
  return total / 6.0f;
}

f32 GfVolumeFade::getFadeRatioForParts(VFPARTS parts) const {
  f32 ratio = 1.0f;
  for (u32 acc = 0; acc < 5; acc++) {
    ratio *= getFadeRatio(static_cast<VFACC>(acc), parts);
  }
  return ratio;
}

} // namespace gf
