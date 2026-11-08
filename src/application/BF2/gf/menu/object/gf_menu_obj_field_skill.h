#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace gf {
class GfMenuCallContext;
class GfMenuFieldSkillList;
class GfMenuReferenceFs;
class GfMenuReferenceNumber;

class GfMenuObjFieldSkill : public GfMenuObject {
public:
  ~GfMenuObjFieldSkill() override;
  static void attachSkip(GfMenuCallContext *context);
  void initialize() override;
  void finalize() override;
  void update() override;

  u8 _24[0x28 - 0x24];
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown28; // Inferred role: reference number; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown30; // Inferred role: reference number; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown38; // Inferred role: reference number; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown40; // Inferred role: reference number; original member name unknown.
  GfMenuFieldSkillList *unknown48;                        // Inferred role: field skills; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceFs> unknown50;     // Inferred role: field skill reference; original member name unknown.
  u16 unknown58;                                          // Role and original member name unknown, cleared by the constructor.
  bool unknown5a;                                         // Role and original member name unknown, cleared by the constructor.
  u8 _5b[0x5c - 0x5b];
  u16 unknown5c; // Role and original member name unknown, cleared by the constructor.
  u8 _5e[0x70 - 0x5e];
  GfMenuSequence<GfMenuObjFieldSkill, 4> unknown70; // Inferred role: queued steps; original member name unknown.
};

static_assert(offsetof(GfMenuObjFieldSkill, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjFieldSkill, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjFieldSkill, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjFieldSkill, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjFieldSkill, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjFieldSkill, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuObjFieldSkill, unknown58) == 0x58, "");
static_assert(offsetof(GfMenuObjFieldSkill, unknown5a) == 0x5a, "");
static_assert(offsetof(GfMenuObjFieldSkill, unknown5c) == 0x5c, "");
static_assert(offsetof(GfMenuObjFieldSkill, unknown70) == 0x70, "");
static_assert(sizeof(GfMenuObjFieldSkill) == 0x1d0, "");

} // namespace gf
