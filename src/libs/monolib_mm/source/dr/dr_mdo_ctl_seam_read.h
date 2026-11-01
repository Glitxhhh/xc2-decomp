#pragma once

#include "dr/dr_mdo_ctl_seam_light.h"

namespace ml {

class DrMdoCtlSeamRead : public DrMdoCtlSeamLight {
public:
  DrMdoCtlSeamRead(int viewNum);
  void updateReadList();
  void updateReadCall();
};

} // namespace ml
