#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "gf/sound/gf_sound.h"
#include "types.h"

namespace ui {
class UIListInfoBase;
} // namespace ui
namespace gf {

class GfMenuObjLvupMain : public GfMenuObject {
public:
  void initialize() override;
  void finalize() override;
  void update() override;
  void refreshLevelUpInfo();
  bool seqClose2();
  bool seqClose3();
  bool seqEndLevelUp();
  bool seqExecLevelUp();

  u8 _24[0x30 - 0x24];
  ui::UIListInfoBase *unknown30; // Inferred role: driver list; original member name unknown.
  u8 _38[0x50 - 0x38];
  GfMenuSequence<GfMenuObjLvupMain, 8> unknown50; // Inferred role: level up and close steps; original member name unknown.
  u8 _2e0[0x304 - 0x2e0];
  SoundHandle unknown304; // Inferred role: level up jingle; original member name unknown.
};

static_assert(offsetof(GfMenuObjLvupMain, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjLvupMain, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuObjLvupMain, unknown304) == 0x304, "");
static_assert(sizeof(GfMenuObjLvupMain) == 0x310, "");

} // namespace gf
