#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

struct SDataOption;
class GfMenuCallContext;

class GfMenuObjOption : public GfMenuObject {
public:
  static bool attach(GfMenuCallContext *context);
  void initialize() override;
  void finalize() override;

  static void initOptionData(SDataOption &option);
  static int getVolumeValue(u8 level, u8 levelMax);
  static u32 getGammaValue(u8 level, u8 levelMax);
};

} // namespace gf
