#pragma once
#include <stddef.h>

#include "gf/data/gf_data_idea.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace gf {

struct SDataBlade;

// Layout from GfBladeCreate's accessors (0x7100301e80-0x7100301fd4); the members between the ones below are not reconstructed yet. The size is between 0xa50 and 0xa58: isResultRare reads 0xa4c,
// GfMenuObjBladeCreate embeds the object at 0x80 and stores its next member at 0xae0, and createBladeNewVersion puts another local 0xa58 after its GfBladeCreateInfo local (sp+0x8c0).
// setupAddBooster (0x7100301ec4) shows a FixedVector<u32, 128> of boosters at 0x08 and an SDataIdea at 0x210.
class GfBladeCreateInfo {
public:
  void clear();
  bool getBladeName(u8 *&bdat, u32 &textId) const;

  static const u32 BOOSTER_UNKNOWN_128 = 128; // Inferred role: booster max; original name unknown.

  u32 unknown00;                                            // Inferred role: driver; original member name unknown.
  u32 unknown04;                                            // Inferred role: core crystal; original member name unknown.
  mm::mtl::FixedVector<u32, BOOSTER_UNKNOWN_128> unknown08; // Inferred role: boosters; original member name unknown.
  SDataIdea unknown210;                                     // Inferred role: idea levels added by the boosters; original member name unknown.
  u8 _230[0x244 - 0x230];
  bool unknown244; // Inferred role: rare result; original member name unknown.
  u8 _245[0x27c - 0x245];
  u32 unknown27c; // Inferred role: blade name text id, read by getBladeName (1.0.0: 0x71003027f4); original member name unknown.
  u8 _280[0x32c - 0x280];
  u32 unknown32c; // Inferred role: driver blade name text id, tested by getBladeName for a rare result (1.0.0: 0x710030280c); original member name unknown.
  u8 _330[0xa3a - 0x330];
  bool unknowna3a; // Inferred role: result valid; original member name unknown.
  u8 _a3b[0xa4c - 0xa3b];
  int unknowna4c; // Inferred role: rare blade of the result; original member name unknown.
};

static_assert(offsetof(GfBladeCreateInfo, unknown04) == 0x04, "");
static_assert(offsetof(GfBladeCreateInfo, unknown08) == 0x08, "");
static_assert(offsetof(GfBladeCreateInfo, unknown210) == 0x210, "");
static_assert(offsetof(GfBladeCreateInfo, unknown244) == 0x244, "");
static_assert(offsetof(GfBladeCreateInfo, unknown27c) == 0x27c, "");
static_assert(offsetof(GfBladeCreateInfo, unknown32c) == 0x32c, "");
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
