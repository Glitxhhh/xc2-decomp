#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {
class GfMenuCallContext;

class GfMenuObjCharSelect : public GfMenuObject {
public:
  struct OpenCustomizeParam {
    u32 unknown00; // Inferred role: customize type, 0 driver and 1 blade; original member name unknown.
    u32 unknown04; // Inferred role: character; original member name unknown.
  };

  // Inferred role: layer parameter built from OpenCustomizeParam; original type name unknown.
  struct unknown003 {
    u16 unknown00; // Inferred role: customize type; original member name unknown.
    u32 unknown04; // Inferred role: character; original member name unknown.
  };

  static void registOpenCustomizeParam(const OpenCustomizeParam &param);
  static void openBladeCustomize(u32 handle, u32 blade, u16 group);
  static void openDriverCustomize(u32 handle, u32 driver, u16 group);
  static bool attach(GfMenuCallContext *context);
  static void returnSubMenu();
  static void sendEvent(u32 handle, u32 type, u32 param);
  void initialize() override;
  void finalize() override;
  bool seqSpHikariToHomura();
  bool seqSpHomuraToHikari();
};

static_assert(offsetof(GfMenuObjCharSelect::OpenCustomizeParam, unknown04) == 0x04, "");
static_assert(sizeof(GfMenuObjCharSelect::OpenCustomizeParam) == 0x08, "");
static_assert(offsetof(GfMenuObjCharSelect::unknown003, unknown04) == 0x04, "");
static_assert(sizeof(GfMenuObjCharSelect::unknown003) == 0x08, "");

} // namespace gf
