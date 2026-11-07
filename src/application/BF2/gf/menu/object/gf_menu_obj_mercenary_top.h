#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "types.h"

namespace gf {

class GfMenuObjMercenaryTop : public GfMenuObject {
public:
  struct OpenParam {
    u32 unknown00; // Role and original member name unknown.
  };

  static void registOpenParam(const OpenParam &param);
  void sendOpenEvent(u32 handle, int type);
  void sendCloseEvent(u32 handle, int type);
  void initialize() override;
  void finalize() override;
  void update() override;

  u8 _24[0xa0 - 0x24];
  GfMenuSequence<GfMenuObjMercenaryTop, 8> unknown0a0; // Inferred role: queued steps; original member name unknown.
};

static_assert(offsetof(GfMenuObjMercenaryTop, unknown0a0) == 0xa0, "");

} // namespace gf
