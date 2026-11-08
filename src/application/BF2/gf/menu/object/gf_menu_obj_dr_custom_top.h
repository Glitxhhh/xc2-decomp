#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "types.h"

namespace ui {
class UICtrlRevolveSelect;
class UISelectObjList;
} // namespace ui

namespace gf {
class GfMenuCallContext;
class GfMenuDriverList;

class GfMenuObjDrCustomTop : public GfMenuObject {
public:
  GfMenuObjDrCustomTop(u32 handle);
  ~GfMenuObjDrCustomTop() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  void suspendInput();
  void resumeInput();
  bool seqStartOpen();
  bool seqAppearPhase1();
  bool seqAppearPhase2();
  bool seqAppearPhase4();
  bool seqEndOpen();
  bool seqStartAddLayer();
  bool seqAddLayerPhase3_DrEquip();
  bool seqAddLayerPhase3_DrArtsSet();
  bool seqAddLayerPhase4();

  u8 _24[0x28 - 0x24];
  GfMenuDriverList *unknown28;                       // Inferred role: drivers; original member name unknown.
  ui::UISelectObjList *unknown30;                    // Inferred role: driver objects; original member name unknown.
  ui::UICtrlRevolveSelect *unknown38;                // Inferred role: driver ring control; original member name unknown.
  GfMenuCallContext *unknown40;                      // Inferred role: common jog call context; original member name unknown.
  GfMenuCallContext *unknown48;                      // Inferred role: driver detail call context; original member name unknown.
  GfMenuCallContext *unknown50;                      // Inferred role: call context of the layer being added; original member name unknown.
  GfMenuSequence<GfMenuObjDrCustomTop, 8> unknown58; // Inferred role: queued steps; original member name unknown.
  int unknown2e8;                                    // Inferred role: control of the current step, -1 when idle; original member name unknown.
};

static_assert(offsetof(GfMenuObjDrCustomTop, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjDrCustomTop, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjDrCustomTop, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjDrCustomTop, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjDrCustomTop, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjDrCustomTop, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuObjDrCustomTop, unknown58) == 0x58, "");
static_assert(offsetof(GfMenuObjDrCustomTop, unknown2e8) == 0x2e8, "");

} // namespace gf
