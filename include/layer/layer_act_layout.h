#pragma once
#include "layer/layer_obj_layout.h"
#include "types.h"

namespace layer {

class LayerActLayout : public LayerObjLayout {
public:
  LayerActLayout();
  void updatePartsAction(const LyrActionData *action) override;
  u32 calcLayoutActionWorkSize(const u8 *data);
  void setupLayoutAction(u8 *work, const u8 *data);
  bool actcmd_notcmd01(const u8 *&cmd);
  bool actcmd_notcmd02(const u8 *&cmd);
  bool actcmd_notcmd03(const u8 *&cmd);

  static bool (LayerActLayout::*s_pCallActCmd[])(const u8 *&cmd);
};

} // namespace layer
