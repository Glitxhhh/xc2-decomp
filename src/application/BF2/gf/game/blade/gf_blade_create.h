#pragma once
#include <stddef.h>

#include "types.h"

namespace gf {

struct SDataBlade;

// Layout from GfBladeCreate's accessors (0x7100301e80-0x7100301fd4); the members between the ones below are not reconstructed yet. The size is between 0xa50 and 0xa58: isResultRare reads 0xa4c,
// GfMenuObjBladeCreate embeds the object at 0x80 and stores its next member at 0xae0, and createBladeNewVersion puts another local 0xa58 after its GfBladeCreateInfo local (sp+0x8c0).
// setupAddBooster (0x7100301ec4, not matched yet) shows a FixedVector<u32, 128> of boosters at 0x08 and an SDataIdea at 0x210.
class GfBladeCreateInfo {
public:
  void clear();

  u32 unknown00; // Inferred role: driver; original member name unknown.
  u32 unknown04; // Inferred role: core crystal; original member name unknown.
  u8 _08[0x244 - 0x08];
  bool unknown244; // Inferred role: rare result; original member name unknown.
  u8 _245[0xa3a - 0x245];
  bool unknowna3a; // Inferred role: result valid; original member name unknown.
  u8 _a3b[0xa4c - 0xa3b];
  int unknowna4c; // Inferred role: rare blade of the result; original member name unknown.
};

static_assert(offsetof(GfBladeCreateInfo, unknown04) == 0x04, "");
static_assert(offsetof(GfBladeCreateInfo, unknown244) == 0x244, "");
static_assert(offsetof(GfBladeCreateInfo, unknowna3a) == 0xa3a, "");
static_assert(offsetof(GfBladeCreateInfo, unknowna4c) == 0xa4c, "");

// GfBladeCreateInfo is a base class: the game's GfBladeCreate constructor (0x71003011a0) is a tail call to the base-object constructor _ZN2gf17GfBladeCreateInfoC2Ev.
class GfBladeCreate : public GfBladeCreateInfo {
public:
  void clear();
  void setupDriver(u32 driver);
  bool setupCoreCrystal(u32 crystal);
  void setupAddBooster(u32 booster);
  bool isEnableAddBlade() const;
  bool isResultRare() const;
  bool getResultBlade(SDataBlade &blade) const;
  static void setupSDataBlade(SDataBlade &blade, const GfBladeCreateInfo &info);
};

} // namespace gf
