#pragma once

#include "dr/dr_mdo_ctl_seam.h"

namespace ml {
class DrResMdoSeamWrkMpf;

class DrMdoCtlSeamMpfMap : public DrMdoCtlSeam {
public:
  void releaseMpfMap();
  DrResMdoSeamWrkMpf *createFreeSeamMpf();
  void releaseFreeSeamMpf(DrResMdoSeamWrkMpf *mpf);
  void updateMpfMap();
  void readMpfMapCheck();
  void updateMpfMapRenderList();
  void createAllpfMapDisplayList();
  void renderMpfMapDisplayList();
  void createMpfMapDisplayList();
};

} // namespace ml
