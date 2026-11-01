#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "types.h"

namespace gf {

class GfMenuCallContext;

class GfMenuObjBladeName : public GfMenuObject {
public:
  // Inferred helper: zooms in the blade name text and its shadow; original name unknown.
  void unknown002() {
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 0x10000000;
    param.unknown50 = "cmn_fade_motion_zoom";
    param.unknown58 = "fade_in";
    param.unknown14 = 10;
    GfMenuObjUtil::startCtrl(unknown18, param, "TXT_bl_name");
    GfMenuObjUtil::startCtrl(unknown18, param, "TXT_bl_name_shadow");
  }

  void initialize() override;
  void finalize() override;
  static void open(GfMenuCallContext *context);
  static void pause(GfMenuCallContext *context);
  static void close();
  bool seqApperNormal();
  bool seqApperRare();
  bool seqApperName();
  bool seqLeave();

  u8 _24[0x2b8 - 0x24];
  bool unknown2b8; // Inferred role: leave control started flag; original member name unknown.
};

static_assert(offsetof(GfMenuObjBladeName, unknown2b8) == 0x2b8, "");

} // namespace gf
