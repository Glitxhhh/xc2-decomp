#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjHelpHud : public GfMenuObject {
public:
  void initialize() override;
  void finalize() override;
  void enable();
  void disable();
  static void ctrlFadeOut(u32 handle);
  static void ctrlFadeIn(u32 handle);
  bool seqPageFadeIn();
  bool seqPageFadeOut();

  u8 _24[0x2c0 - 0x24];
  bool unknown2c0; // Inferred role: page fade control started flag; original member name unknown.
};

static_assert(offsetof(GfMenuObjHelpHud, unknown2c0) == 0x2c0, "");

} // namespace gf
