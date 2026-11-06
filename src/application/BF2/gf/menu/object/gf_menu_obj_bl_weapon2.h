#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "types.h"

namespace gf {
class GfMenuCallContext;

class GfMenuObjBlWeapon2 : public GfMenuObject {
public:
  struct OpenParam {
    u16 unknown00; // Inferred role: open mode; original member name unknown.
    u32 unknown04; // Inferred role: weapon; original member name unknown.
  };

  // Inferred role: layer parameter built from OpenParam; original type name unknown.
  struct unknown002 {
    u16 unknown00; // Inferred role: open mode; original member name unknown.
    u16 unknown02; // Inferred role: weapon; original member name unknown.
  };

  static void registOpenParam(const OpenParam &param);
  static void openForShop(u32 weapon);
  static bool attach(GfMenuCallContext *context);
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle);
  static int setFadeOut(u32 handle);
  static bool isSameWeapon(u32 blade, u32 chip);
  static bool isDownWeapon(u32 blade, u32 chip);
  void initialize() override;
  void finalize() override;
  void update() override;
  void openCharChange();
  bool seqStart();
  bool seqSrcLeave();
  bool seqSrcAppear();
  bool seqDstResume();
  bool seqEnd();

  u8 _24[0x58 - 0x24];
  GfMenuSequence<GfMenuObjBlWeapon2, 8> unknown58; // Inferred role: weapon change steps; original member name unknown.
  bool unknown2e8;                                 // Inferred role: control started flag; original member name unknown.
  u8 _2e9[0x308 - 0x2e9];
};

static_assert(offsetof(GfMenuObjBlWeapon2::OpenParam, unknown04) == 0x04, "");
static_assert(sizeof(GfMenuObjBlWeapon2::OpenParam) == 0x08, "");
static_assert(offsetof(GfMenuObjBlWeapon2::unknown002, unknown02) == 0x02, "");
static_assert(sizeof(GfMenuObjBlWeapon2::unknown002) == 0x04, "");
static_assert(offsetof(GfMenuObjBlWeapon2, unknown58) == 0x58, "");
static_assert(offsetof(GfMenuObjBlWeapon2, unknown2e8) == 0x2e8, "");
static_assert(sizeof(GfMenuObjBlWeapon2) == 0x308, "");

} // namespace gf
