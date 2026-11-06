#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "types.h"

namespace gf {
struct GF_SCOM_HANDLE;

class GfMenuObjBladeSet2 : public GfMenuObject {
public:
  static void sendEvent(u32 handle, u32 type, u32 param, f32 delay);
  static int setFadeIn(u32 handle);
  static int setFadeOut(u32 handle);
  void initialize() override;
  void finalize() override;
  void update() override;
  static void setCloseToReturn();
  static void setCloseToFSClose();
  bool seqWaitCommand();

  u8 _24[0xa0 - 0x24];
  GfMenuSequence<GfMenuObjBladeSet2, 8> unknowna0;  // Inferred role: blade set steps; original member name unknown.
  GF_SCOM_HANDLE *unknown330;                       // Inferred role: pending blade set command; original member name unknown.
  GfMenuSequence<GfMenuObjBladeSet2, 4> unknown338; // Inferred role: image steps; original member name unknown.
};

static_assert(offsetof(GfMenuObjBladeSet2, unknowna0) == 0xa0, "");
static_assert(offsetof(GfMenuObjBladeSet2, unknown330) == 0x330, "");
static_assert(offsetof(GfMenuObjBladeSet2, unknown338) == 0x338, "");
static_assert(sizeof(GfMenuObjBladeSet2) == 0x498, "");

} // namespace gf
