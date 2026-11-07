#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "types.h"

namespace gf {

class GfMenuObjPartyForm2 : public GfMenuObject {
public:
  GfMenuObjPartyForm2(u32 handle);
  ~GfMenuObjPartyForm2() override;
  u32 getCursorID(u32 index);

  u8 _24[0x38 - 0x24];
  bool unknown38; // Role and original member name unknown, cleared by the constructor.
  u8 _39[0x40 - 0x39];
  u64 unknown40;                                    // Role and original member name unknown, cleared by the constructor.
  u64 unknown48;                                    // Role and original member name unknown, cleared by the constructor.
  u64 unknown50;                                    // Role and original member name unknown, cleared by the constructor.
  u64 unknown58;                                    // Role and original member name unknown, cleared by the constructor.
  int unknown60;                                    // Role and original member name unknown, 0xff at start.
  int unknown64;                                    // Role and original member name unknown, 0xff at start.
  GfMenuSequence<GfMenuObjPartyForm2, 8> unknown68; // Inferred role: queued steps; original member name unknown.
  u16 unknown2f8;                                   // Role and original member name unknown, cleared by the constructor.
  u8 _2fa[0x2fc - 0x2fa];
  int unknown2fc; // Role and original member name unknown, -1 at start.
  int unknown300; // Role and original member name unknown, -1 at start.
  int unknown304; // Role and original member name unknown, -1 at start.
  u32 unknown308; // Role and original member name unknown, cleared by the constructor.
  u8 _30c[0x310 - 0x30c];
  u64 unknown310; // Role and original member name unknown, cleared by the constructor.
  u64 unknown318; // Role and original member name unknown, cleared by the constructor.
};

static_assert(offsetof(GfMenuObjPartyForm2, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjPartyForm2, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjPartyForm2, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjPartyForm2, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuObjPartyForm2, unknown58) == 0x58, "");
static_assert(offsetof(GfMenuObjPartyForm2, unknown60) == 0x60, "");
static_assert(offsetof(GfMenuObjPartyForm2, unknown64) == 0x64, "");
static_assert(offsetof(GfMenuObjPartyForm2, unknown68) == 0x68, "");
static_assert(offsetof(GfMenuObjPartyForm2, unknown2f8) == 0x2f8, "");
static_assert(offsetof(GfMenuObjPartyForm2, unknown2fc) == 0x2fc, "");
static_assert(offsetof(GfMenuObjPartyForm2, unknown300) == 0x300, "");
static_assert(offsetof(GfMenuObjPartyForm2, unknown304) == 0x304, "");
static_assert(offsetof(GfMenuObjPartyForm2, unknown308) == 0x308, "");
static_assert(offsetof(GfMenuObjPartyForm2, unknown310) == 0x310, "");
static_assert(offsetof(GfMenuObjPartyForm2, unknown318) == 0x318, "");

} // namespace gf
