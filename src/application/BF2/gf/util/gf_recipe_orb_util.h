#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace gf {

struct OrbRecipe {
  u16 unknown00; // Inferred role: item id; original member name unknown.
  u16 unknown02; // Inferred role: item count; original member name unknown.
};

static_assert(sizeof(OrbRecipe) == 0x4, "");

// Layout evidence: GfRecipeOrbUtil::getRecipeInfo (0x7100362cc8) clears the first 0x10 bytes and the item count at 0x30,
// stores the recipe id at 0x00 and the recipe type at 0x04, the rarity and its count at 0x08, the category and its count at
// 0x0c and the item entries from 0x10 (at most eight).
class RecipeInfo {
public:
  const OrbRecipe *getResultRarity() const;
  const OrbRecipe *getResultColleCategory() const;
  const mm::mtl::FixedVector<OrbRecipe, 8> *getResultItems() const;

  u32 unknown00;                                    // Inferred role: recipe id; original member name unknown.
  u32 unknown04;                                    // Inferred role: recipe type; original member name unknown.
  OrbRecipe m_resultRarity;                         // Rarity (id) and number of the collection items.
  OrbRecipe m_resultColleCategory;                  // Category (id) and number of the collection items.
  mm::mtl::FixedVector<OrbRecipe, 8> m_resultItems; // Items (id) and numbers.
};

static_assert(offsetof(RecipeInfo, m_resultRarity) == 0x08, "");
static_assert(offsetof(RecipeInfo, m_resultColleCategory) == 0x0c, "");
static_assert(offsetof(RecipeInfo, m_resultItems) == 0x10, "");
static_assert(sizeof(RecipeInfo) == 0x38, "");

class GfRecipeOrbUtil {
public:
  static bool getRecipeItemsByItemBox(mm::mtl::FixedVector<OrbRecipe, 128> &items, u32 id);
  static bool isEnabaleOrbRecipeCategory(u32 recipe, const mm::mtl::FixedVector<OrbRecipe, 128> &items);
  static bool isEnabaleOrbRecipeRare(u32 recipe, const mm::mtl::FixedVector<OrbRecipe, 128> &items);
  static bool isEnableRecipe(u32 id);
  static u32 getRecipeID(u32 id);
  static u32 getEquipOrb(u32 id);
  static bool getRecipeInfo(RecipeInfo &info, u32 id);
};

} // namespace gf
