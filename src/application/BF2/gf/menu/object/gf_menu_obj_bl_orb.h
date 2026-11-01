#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "types.h"
#include "ui/ui_object_acc.h"

namespace gf {
class GfMenuCallContext;

class GfMenuObjBlOrb : public GfMenuObject {
public:
  // Inferred helper: runs a quarter second control on the main layout and waits for its end; original name unknown.
  bool unknown002(u32 method) {
    if (unknown2e8 == -1) {
      ui::UIObjectAcc acc(unknown18, "LAY_main");
      GfMenuObjUtil::CtrlParam param;
      param.unknown08 = method;
      param.unknown00 = 0.25f;
      unknown2e8 = GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    }
    if (GfMenuObjUtil::isBusyCtrl(unknown2e8)) {
      return false;
    }
    unknown2e8 = -1;
    return true;
  }

  static bool attach(GfMenuCallContext *context);
  void initialize() override;
  void finalize() override;
  void suspendInput();
  void resumeInput();
  bool seqStartOpen();
  bool seqEndOpen();
  bool seqStartClose();
  bool seqEndClose();
  bool seqAppearPhase1();
  bool seqLeavePhase1();

  u8 _24[0x2e8 - 0x24];
  int unknown2e8; // Inferred role: control of the appear and leave phases, -1 when idle; original member name unknown.
};

static_assert(offsetof(GfMenuObjBlOrb, unknown2e8) == 0x2e8, "");

} // namespace gf
