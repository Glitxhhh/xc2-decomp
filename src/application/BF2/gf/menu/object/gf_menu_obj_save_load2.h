#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "types.h"

namespace gf {

class GfMenuObjSaveLoad2 : public GfMenuObject {
public:
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle, u32 type);
  static int setFadeOut(u32 handle, u32 type);
  void initialize() override;
  void finalize() override;
  void update() override;
  struct OpenParam {
    u16 unknown00; // Inferred role: mode; original member name unknown.
  };

  static void registOpenParam(const OpenParam &param);

  u8 _24[0x30 - 0x24];
  GfMenuSequence<GfMenuObjSaveLoad2, 8> unknown30; // Inferred role: queued steps; original member name unknown.
};

static_assert(offsetof(GfMenuObjSaveLoad2, unknown30) == 0x30, "");

} // namespace gf
