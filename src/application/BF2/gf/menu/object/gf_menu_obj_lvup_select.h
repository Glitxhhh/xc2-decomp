#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "types.h"

namespace gf {
class GfMenuCallContext;

class GfMenuObjLvupSelect : public GfMenuObject {
public:
  static void openLevelSelect(GfMenuCallContext *context, u32 level);
  static void openLevelup(GfMenuCallContext *context, u32 level, u32 levelMax);
  void initialize() override;
  void finalize() override;
  void update() override;

  u8 _24[0x28 - 0x24];
  GfMenuSequence<GfMenuObjLvupSelect, 8> unknown28; // Inferred role: queued steps; original member name unknown.
};

static_assert(offsetof(GfMenuObjLvupSelect, unknown28) == 0x28, "");

} // namespace gf
