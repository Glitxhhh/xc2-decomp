#pragma once

#include "dr/dr_mdo_ctl_seam_inst_map.h"

namespace ml {
class DrResMdoSeamWrkMpf;

class DrMdoCtlSeamMpfMap : public DrMdoCtlSeamInstMap {
public:
  DrMdoCtlSeamMpfMap(int viewNum);
  void releaseMpfMap();
  DrResMdoSeamWrkMpf *createFreeSeamMpf();
  void releaseFreeSeamMpf(DrResMdoSeamWrkMpf *mpf);
  void updateMpfMap();
  void readMpfMapCheck();
  void updateMpfMapRenderList();
  void createAllpfMapDisplayList();
  void renderMpfMapDisplayList();
  void createMpfMapDisplayList();
  void callRenderSeamMpfMap();
  void createMpfZPrePassDisplayList();
};

} // namespace ml
