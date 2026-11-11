#pragma once

#include "dr/dr_mdl_obj.h"
#include "types.h"

namespace ml {
class DrMan;

class DrMdoCtlDammy : public DrMdlObj {
public:
  DrMdoCtlDammy(const void *data, DrMan *drMan, int viewNum);
  ~DrMdoCtlDammy() override;
  void resourceInit() override;
  void update() override;
  void dispOffUpdate() override;

  u8 _190[0x1b0 - 0x190];
};

static_assert(sizeof(DrMdoCtlDammy) == 0x1b0, "");

} // namespace ml
