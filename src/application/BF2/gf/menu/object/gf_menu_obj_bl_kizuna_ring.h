#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "types.h"

namespace ui {
class UIObjectAcc;
} // namespace ui

namespace gf {
class GfMenuCallContext;
struct GAME_VOICE_HANDLE;

class GfMenuObjBlKizunaRing : public GfMenuObject {
public:
  struct OpenParam {
    u16 unknown00; // Inferred role: open mode; original member name unknown.
    u32 unknown04; // Inferred role: blade; original member name unknown.
  };

  static void registOpenParam(const OpenParam &param);
  static void openForMercenary(u32 handle, u32 blade, u16 group);
  static bool attach(GfMenuCallContext *context);
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle);
  static int setFadeOut(u32 handle);
  void initialize() override;
  void finalize() override;
  void update() override;
  static bool isLockPos(int index);
  static bool isScreenLR(u32 screen);
  static void setupCircle(ui::UIObjectAcc &);
  static void refreshRing(ui::UIObjectAcc &acc);
  bool seqEnd();
  bool seqWait();
  bool seqWaitVoice();

  u8 _24[0x1a0 - 0x24];
  GfMenuSequence<GfMenuObjBlKizunaRing, 8> unknown1a0; // Inferred role: achievement steps; original member name unknown.
  u8 _430[0x438 - 0x430];
  int unknown438; // Inferred role: open mode, 0 from the main menu; original member name unknown.
  u8 _43c[0x458 - 0x43c];
  GAME_VOICE_HANDLE *unknown458; // Inferred role: blade voice; original member name unknown.
  u8 _460[0x470 - 0x460];
};

static_assert(offsetof(GfMenuObjBlKizunaRing::OpenParam, unknown04) == 0x04, "");
static_assert(sizeof(GfMenuObjBlKizunaRing::OpenParam) == 0x08, "");
static_assert(offsetof(GfMenuObjBlKizunaRing, unknown1a0) == 0x1a0, "");
static_assert(offsetof(GfMenuObjBlKizunaRing, unknown438) == 0x438, "");
static_assert(offsetof(GfMenuObjBlKizunaRing, unknown458) == 0x458, "");
static_assert(sizeof(GfMenuObjBlKizunaRing) == 0x470, "");

} // namespace gf
