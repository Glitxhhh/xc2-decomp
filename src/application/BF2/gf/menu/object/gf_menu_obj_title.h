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
  bool seqConfirmNewGame();

  static bool isEnableNewGame();
  static bool isEnableNewGameAdv();
  static bool isEnableContinue();
  static bool isEnableOption();
  static void setDispMode(u32 handle, int mode);
  static void setInputMode(u32 handle, int mode);

  static bool s_NoSaveData;

  u8 _24[0x48 - 0x24];
  u32 unknown48; // Inferred role: call context type returned with the confirmation result; original member name unknown.
  u8 _4c[0x58 - 0x4c];
  GfMenuSequence<GfMenuObjTitle, 4> unknown58; // Inferred role: queued steps; original member name unknown.
  bool unknown1b8;                             // Inferred role: confirmation window opened; original member name unknown.
};

static_assert(offsetof(GfMenuObjTitle, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjTitle, unknown58) == 0x58, "");
static_assert(offsetof(GfMenuObjTitle, unknown1b8) == 0x1b8, "");

} // namespace gf
