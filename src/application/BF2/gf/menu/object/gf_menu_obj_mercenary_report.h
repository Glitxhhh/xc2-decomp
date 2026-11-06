#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "types.h"

namespace gf {
class GfMenuCallContext;

class GfMenuObjMercenaryReport : public GfMenuObject {
public:
  void initialize() override;
  void finalize() override;
  void update() override;
  bool seqCheckAchive();
  bool seqClose();
  bool seqDispInfo();
  bool seqDispReward();
  bool seqEnd();
  bool seqWaitEndKizuna();
  bool seqWaitLoadKizuna();

  u32 unknown24; // Inferred role: team; original member name unknown.
  u8 _28[0x30 - 0x28];
  GfMenuSequence<GfMenuObjMercenaryReport, 10> unknown30; // Inferred role: report steps; original member name unknown.
  bool unknown358;                                        // Inferred role: animation or control started flag; original member name unknown.
  bool unknown359;                                        // Inferred role: reward closed flag; original member name unknown.
  u8 _35a[0x370 - 0x35a];
  GfMenuCallContext *unknown370; // Inferred role: kizuna ring call context; original member name unknown.
};

static_assert(offsetof(GfMenuObjMercenaryReport, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjMercenaryReport, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjMercenaryReport, unknown358) == 0x358, "");
static_assert(offsetof(GfMenuObjMercenaryReport, unknown359) == 0x359, "");
static_assert(offsetof(GfMenuObjMercenaryReport, unknown370) == 0x370, "");
static_assert(sizeof(GfMenuObjMercenaryReport) == 0x378, "");

} // namespace gf
