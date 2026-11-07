#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuRewriteNumber;

class GfMenuObjPartyStatus2 : public GfMenuObject {
public:
  GfMenuObjPartyStatus2(u32 handle);
  ~GfMenuObjPartyStatus2() override;
  static void close();
  static void disp(bool isDisp);
  static void open();
  static void sendEvent(u32 handle, u32 type, u32 param);
  void initialize() override;
  void finalize() override;
  void update() override;

  bool unknown24;                 // Role and original member name unknown, cleared by the constructor.
  GfMenuRewriteNumber *unknown28; // Inferred role: party status number; original member name unknown.
  int unknown30;                  // Inferred role: control of the first party frame, -1 when idle; original member name unknown.
  int unknown34[2];               // Inferred role: controls of the other party frames, -1 when idle; original member name unknown.
};

static_assert(offsetof(GfMenuObjPartyStatus2, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjPartyStatus2, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjPartyStatus2, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjPartyStatus2, unknown34) == 0x34, "");
static_assert(sizeof(GfMenuObjPartyStatus2) == 0x40, "");

} // namespace gf
