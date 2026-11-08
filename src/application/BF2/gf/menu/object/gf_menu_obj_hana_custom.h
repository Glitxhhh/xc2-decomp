#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace mm {
namespace mtl {
class ReferenceObject;
} // namespace mtl
} // namespace mm

namespace ui {
class UIObjectAcc;
class UISelectObjList;
} // namespace ui

namespace gf {

class GfMenuCallContext;
class GfMenuIDList;
class GfMenuItemList;
class GfMenuReferenceItem;
class GfMenuReferenceNumber;

class GfMenuObjHanaCustom : public GfMenuObject {
public:
  GfMenuObjHanaCustom(u32 handle);
  ~GfMenuObjHanaCustom() override;
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle, u32 unknown);
  static int setFadeOut(u32 handle, u32 unknown);
  void initialize() override;
  void finalize() override;
  void update() override;
  static u32 convPartsId(u32 partsId);
  static bool isExpandParts(u32 partsId);
  static void refreshPlanLine(ui::UIObjectAcc &);

  u8 _24[0x28 - 0x24];
  GfMenuIDList *unknown28;                           // Inferred role: identifiers; original member name unknown.
  GfMenuIDList *unknown30;                           // Inferred role: identifiers; original member name unknown.
  ui::UISelectObjList *unknown38;                    // Inferred role: list objects; original member name unknown.
  mm::mtl::ReferenceObject *unknown40;               // Inferred role: reference-counted object; type and original member name unknown.
  GfMenuIDList *unknown48[7];                        // Inferred role: identifiers; original member name unknown.
  u32 unknown80;                                     // Role and original member name unknown, cleared by the constructor.
  u32 unknown84;                                     // Role and original member name unknown, cleared by the constructor.
  GfMenuItemList *unknown88;                         // Inferred role: items; original member name unknown.
  ui::UISelectObjList *unknown90;                    // Inferred role: list objects; original member name unknown.
  mm::mtl::ReferenceObject *unknown98;               // Inferred role: reference-counted object; type and original member name unknown.
  GfMenuCallContext *unknown0a0;                     // Inferred role: call context; original member name unknown.
  GfMenuSequence<GfMenuObjHanaCustom, 8> unknown0a8; // Inferred role: queued steps; original member name unknown.
  u32 unknown338;                                    // Role and original member name unknown.
  u8 _33c[0x340 - 0x33c];
  GfMenuReferenceItem *unknown340; // Inferred role: reference item; original member name unknown.
  void *unknown348;                // Role, type and original member name unknown, cleared by the constructor.
  u32 unknown350;                  // Role and original member name unknown, cleared by the constructor.
  u8 _354[0x358 - 0x354];
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown358; // Inferred role: reference number; original member name unknown.
};

static_assert(offsetof(GfMenuObjHanaCustom, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjHanaCustom, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjHanaCustom, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjHanaCustom, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjHanaCustom, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjHanaCustom, unknown80) == 0x80, "");
static_assert(offsetof(GfMenuObjHanaCustom, unknown88) == 0x88, "");
static_assert(offsetof(GfMenuObjHanaCustom, unknown90) == 0x90, "");
static_assert(offsetof(GfMenuObjHanaCustom, unknown98) == 0x98, "");
static_assert(offsetof(GfMenuObjHanaCustom, unknown0a0) == 0xa0, "");
static_assert(offsetof(GfMenuObjHanaCustom, unknown0a8) == 0xa8, "");
static_assert(offsetof(GfMenuObjHanaCustom, unknown338) == 0x338, "");
static_assert(offsetof(GfMenuObjHanaCustom, unknown340) == 0x340, "");
static_assert(offsetof(GfMenuObjHanaCustom, unknown348) == 0x348, "");
static_assert(offsetof(GfMenuObjHanaCustom, unknown350) == 0x350, "");
static_assert(offsetof(GfMenuObjHanaCustom, unknown358) == 0x358, "");
static_assert(sizeof(GfMenuObjHanaCustom) == 0x360, "");

} // namespace gf
