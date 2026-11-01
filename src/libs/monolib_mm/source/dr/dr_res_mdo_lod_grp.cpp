#include "dr/dr_res_mdo_lod_grp.h"

#include "dr/dr_res_mdo_lod_parts.h"

namespace ml {

DrResMdoLodGrp::DrResMdoLodGrp() : unknown00(nullptr), unknown08(0), unknown0c(0), unknown10(0) {}

void DrResMdoLodGrp::setup(DrResMdoLodParts *parts, int partsNum, bool isFixed, bool isChange) {
  unknown00 = parts;
  unknown08 = partsNum;
  unknown10 = 0;
  if (isFixed) {
    unknown10 |= 1;
    if (isChange) {
      unknown10 |= 0x10;
    }
  } else {
    switch (parts->unknown18->unknown16) {
    case 1:
      unknown10 |= 4;
      break;
    case 0:
      unknown10 |= 8;
      break;
    }
  }
}

} // namespace ml
