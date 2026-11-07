#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "types.h"

namespace gf {

class GfMenuObjMercenaryRoot : public GfMenuObject {
public:
  static void closeBg();
  void initialize() override;
  void finalize() override;
  void update() override;

  u8 _24[0x28 - 0x24];
  GfMenuSequence<GfMenuObjMercenaryRoot, 4> unknown28; // Inferred role: queued steps; original member name unknown.
};

static_assert(offsetof(GfMenuObjMercenaryRoot, unknown28) == 0x28, "");

} // namespace gf
