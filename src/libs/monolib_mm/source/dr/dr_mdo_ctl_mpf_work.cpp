#include "dr/dr_mdo_ctl_mpf_work.h"

#include <math.h>

#include "dr/dr_res_mdo_pnt_alpha.h"
#include "ml/rand.h"

namespace ml {

void DrMdoCtlMpfWindCalc::init() {
  for (int i = 0; i < 3; i++) {
    unknown00[i] = mm::Vec3(0.0f, i, 0.0f);
    unknown30[i] = mm::Vec3::zero;
  }
  unknown70 = mm::Mat44::identity;
  unknownb0 = mm::Mat44::identity;
  f32 x = (mtRand() % 100) * 0.01f - 0.5f;
  f32 z = (mtRand() % 100) * 0.01f - 0.5f;
  unknown60 = mm::Vec3(x, 0.0f, z);
  if (!(fabsf(unknown60.x) <= 0.000001f && fabsf(unknown60.y) <= 0.000001f && fabsf(unknown60.z) <= 0.000001f)) {
    unknown60.unknown001();
  } else {
    unknown60 = mm::Vec3(0.0f, 0.0f, 1.0f);
  }
}

DrMdoCtlMpfWork::DrMdoCtlMpfWork() {}

int DrMdoCtlMpfWork::calcRenderListWork(int count, const MdsMpfObjData *data) {
  int size = count * 0x1d0;
  return size + DrResMdoPntAlphaMan::getWrkSize(0x80);
}

void DrMdoCtlMpfWork::changeMemWork(const MdsMpfObjData *data) { unknown38 = data; }

u32 DrMdoCtlMpfWork::getObjChk(int index) { return unknown20[index].unknown20; }

} // namespace ml
