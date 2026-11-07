#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "types.h"

namespace gf {
class GfMenuCallContext;

class GfMenuObjTitle : public GfMenuObject {
public:
  static bool attach(GfMenuCallContext *context);
  void initialize() override;
  void finalize() override;
  void update() override;

  static bool isEnableNewGame();
  static bool isEnableNewGameAdv();
  static bool isEnableContinue();
  static bool isEnableOption();
  static void setDispMode(u32 handle, int mode);

  static bool s_NoSaveData;

  u8 _24[0x58 - 0x24];
  GfMenuSequence<GfMenuObjTitle, 4> unknown58; // Inferred role: queued steps; original member name unknown.
};

static_assert(offsetof(GfMenuObjTitle, unknown58) == 0x58, "");

} // namespace gf
