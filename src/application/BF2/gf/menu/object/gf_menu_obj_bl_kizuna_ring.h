#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace ui {
class UIObjectAcc;
} // namespace ui

namespace gf {
class GfMenuCallContext;

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
  static bool isLockPos(int index);
  static bool isScreenLR(u32 screen);
  static void setupCircle(ui::UIObjectAcc &);
};

static_assert(offsetof(GfMenuObjBlKizunaRing::OpenParam, unknown04) == 0x04, "");
static_assert(sizeof(GfMenuObjBlKizunaRing::OpenParam) == 0x08, "");

} // namespace gf
