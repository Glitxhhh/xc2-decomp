#pragma once
#include "layer/layer_obj_work.h"
#include "types.h"

namespace layer {

class LayerActDef : public LayerObjWork {
public:
  LayerActDef();
  void updatePartsAction(const LyrActionData *action) override;
  u32 calcDefActionWorkSize(const u8 *data);
  void setupDefAction(u8 *work, const u8 *data);
  bool actcmd_iconnum(const u8 *&cmd);
  bool actcmd_animicon(const u8 *&cmd);
  bool actcmd_animdef(const u8 *&cmd);
  bool actcmd_animfrm(const u8 *&cmd);

  static bool (LayerActDef::*s_pCallActCmd[])(const u8 *&cmd);
};

} // namespace layer
