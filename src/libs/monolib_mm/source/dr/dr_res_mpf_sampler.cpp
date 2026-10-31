#include "dr/dr_res_mpf_sampler.h"

#include "dr/dr_man.h"
#include "dr/dr_mdo_shd_set.h"
#include "grlib/cglib_sampler.h"
#include "mtl/alloc_handle.h"

namespace ml {

DrResMpfSampler::DrResMpfSampler(const MdsMpfMatInfoHeader *header) {
  for (int i = 0; i < 3; i++) {
    unknown08[i] = nullptr;
  }
  setupSampler(header);
}

void DrResMpfSampler::setupSampler(const MdsMpfMatInfoHeader *header) {
  samplerRelease();
  for (int i = 0; i < 3; i++) {
    unknown08[i] = new (DrMan::getIns()->unknown10) grlib::CGLibSampler();
    u16 flags;
    switch (i) {
    case 0:
      flags = header->unknown16;
      break;
    case 1:
      flags = header->unknown1a;
      break;
    case 2:
      flags = header->unknown1e;
      break;
    default:
      flags = 0;
      break;
    }
    unknown08[i]->initSampler(GRL_TEX_CLAMP_CLAMP, GRL_TEX_MAG_FILTER_LINEAR);
    GrlTexClamp clampS = GRL_TEX_CLAMP_REPEAT;
    if (!(flags & 1)) {
      clampS = (flags & 4) ? GRL_TEX_CLAMP_MIRRORED_REPEAT : GRL_TEX_CLAMP_CLAMP;
    }
    GrlTexClamp clampT = GRL_TEX_CLAMP_REPEAT;
    if (!(flags & 2)) {
      clampT = (flags & 8) ? GRL_TEX_CLAMP_MIRRORED_REPEAT : GRL_TEX_CLAMP_CLAMP;
    }
    unknown08[i]->setClamp(clampS, clampT, GRL_TEX_CLAMP_CLAMP);
    if (flags & 0x10) {
      unknown08[i]->setFilter(GRL_TEX_MAG_FILTER_NEAREST, GRL_TEX_MIN_FILTER_UNKNOWN_2, GRL_TEX_ANISO_RATIO_UNKNOWN_0);
    } else {
      unknown08[i]->setFilter(GRL_TEX_MAG_FILTER_LINEAR, GRL_TEX_MIN_FILTER_UNKNOWN_5, GRL_TEX_ANISO_RATIO_UNKNOWN_0);
    }
    unknown08[i]->updateData();
  }
}

DrResMpfSampler::~DrResMpfSampler() { samplerRelease(); }

void DrResMpfSampler::samplerRelease() {
  for (int i = 0; i < 3; i++) {
    if (unknown08[i] != nullptr) {
      delete unknown08[i];
      unknown08[i] = nullptr;
    }
  }
}

} // namespace ml
