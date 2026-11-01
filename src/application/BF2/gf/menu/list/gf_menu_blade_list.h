#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_vector.h"
#include "types.h"
#include "ui/list/ui_list_info.h"

namespace gf {

struct MenuBladeInfo {
  u32 unknown00; // Inferred role: blade; original member name unknown.
  u32 unknown04; // Inferred role: creator; original member name unknown.
};

static_assert(sizeof(MenuBladeInfo) == 0x8, "");

class GfMenuBladeList : public ui::UIListInfo<MenuBladeInfo> {
public:
  struct BladeListSetup {
    SetupParam unknown00;                            // Inferred role: param; original member name unknown.
    const mm::mtl::FixedVector<u16, 422> *unknown18; // Inferred role: blades; original member name unknown.
  };

  GfMenuBladeList();
  ~GfMenuBladeList() override;
  static GfMenuBladeList *create();
  void sort(u32 type, bool ascending);
  static bool sortTimeAscending(const MenuBladeInfo &info, const MenuBladeInfo &other);
  static bool sortTimeDescending(const MenuBladeInfo &info, const MenuBladeInfo &other);
  static bool sortNameDescending(const MenuBladeInfo &info, const MenuBladeInfo &other);
  static bool sortNameAscending(const MenuBladeInfo &info, const MenuBladeInfo &other);
  static bool sortRarityAscending(const MenuBladeInfo &info, const MenuBladeInfo &other);
  static bool sortRarityDescending(const MenuBladeInfo &info, const MenuBladeInfo &other);
  static bool sortWeaponAscending(const MenuBladeInfo &info, const MenuBladeInfo &other);
  static bool sortWeaponDescending(const MenuBladeInfo &info, const MenuBladeInfo &other);
  static bool sortAttrAscending(const MenuBladeInfo &info, const MenuBladeInfo &other);
  static bool sortAttrDescending(const MenuBladeInfo &info, const MenuBladeInfo &other);
  static bool sortCreatorAscending(const MenuBladeInfo &info, const MenuBladeInfo &other);
  static bool sortCreatorDescending(const MenuBladeInfo &info, const MenuBladeInfo &other);
  static bool sortGenderDescending(const MenuBladeInfo &info, const MenuBladeInfo &other);
  static bool sortGenderAscending(const MenuBladeInfo &info, const MenuBladeInfo &other);
  void updateOwner();
  void setupFromBladeList(const BladeListSetup &setup);
};

static_assert(offsetof(GfMenuBladeList::BladeListSetup, unknown18) == 0x18, "");
static_assert(sizeof(GfMenuBladeList) == 0x70, "");

} // namespace gf
