#include "dr/dr_res_mdo_lod_parts.h"

namespace ml {

f32 DrResMdoLodParts::PIXEL_RATIO[4] = {0.04f, 0.007f, 0.003f, 0.001f};

DrResMdoLodParts::DrResMdoLodParts() : unknown00(0), unknown08(0), unknown10(1.0f), unknown14(0), unknown18(nullptr) {}

void DrResMdoLodParts::setup(const MdsMdlLodData *lodData) { unknown18 = lodData; }

void DrResMdoLodParts::calcPixel(const DrResMdlLodArg &arg, bool &isDisp) {
  u32 flags = unknown14;
  unknown14 &= ~0x30;
  if ((flags & 2) != 0 && !arg.unknown10) {
    if ((flags & 4) != 0) {
      isDisp = true;
      unknown14 |= 0x20;
    }
    return;
  }
  if (arg.unknown10) {
    if ((unknown14 & 2) != 0) {
      if ((unknown14 & 4) != 0) {
        unknown10 = 1.0f;
      } else {
        unknown10 = 0.0f;
      }
    }
    unknown14 &= ~0xe;
  }
  if (!isDisp && arg.unknown18 >= unknown18->unknown10) {
    isDisp = true;
    unknown14 |= 0x20;
  }
}

void DrResMdoLodParts::calcAutoPixel(const DrResMdlLodArg &arg, bool &isDisp) {
  u32 flags = unknown14;
  unknown14 &= ~0x30;
  if ((flags & 2) != 0 && !arg.unknown10) {
    if ((flags & 4) != 0) {
      isDisp = true;
      unknown14 |= 0x20;
    }
    return;
  }
  if (arg.unknown10) {
    if ((unknown14 & 2) != 0) {
      if ((unknown14 & 4) != 0) {
        unknown10 = 1.0f;
      } else {
        unknown10 = 0.0f;
      }
    }
    unknown14 &= ~0xe;
  }
  if (!isDisp && arg.unknown18 >= PIXEL_RATIO[unknown18->unknown15]) {
    isDisp = true;
    unknown14 |= 0x20;
  }
}

} // namespace ml
