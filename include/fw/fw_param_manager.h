#pragma once
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/reference_object.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace fw {

class ParamList : public mm::mtl::ReferenceObject {
public:
  // Inferred role: entry; original type name unknown.
  struct unknown005 {
    u8 _00[0x08 - 0x00];
    const void *param;
  };

  u32 unknown0c;         // Inferred role: count; original member name unknown.
  unknown005 *unknown10; // Inferred role: entries; original member name unknown.
};

static_assert(offsetof(ParamList, unknown0c) == 0x0c, "");
static_assert(offsetof(ParamList, unknown10) == 0x10, "");

class ParamAdapter {
public:
  template <typename T> const T *get() const { return unknown00 != nullptr ? static_cast<const T *>(unknown00->param) : nullptr; }

  const ParamList::unknown005 *unknown00; // Inferred role: entry; original member name unknown.
};

static_assert(sizeof(ParamAdapter) == 0x08, "");

class ParamManager : public mm::mtl::PtrSingleton<ParamManager> {
public:
  u8 _08[0x430 - 0x08];
  mm::mtl::IntrusivePtr<ParamList> unknown430; // Inferred role: pc param list; original member name unknown.
  mm::mtl::IntrusivePtr<ParamList> unknown438; // Inferred role: formation param list; original member name unknown.
  mm::mtl::IntrusivePtr<ParamList> unknown440; // Inferred role: lure param list; original member name unknown.
  u8 _448[0x458 - 0x448];
  mm::mtl::IntrusivePtr<ParamList> unknown458; // Inferred role: battle water dead warp param list, read by TaskFieldCheckWarpBattleWaterDead::onCreate; original member name unknown.
  mm::mtl::IntrusivePtr<ParamList> unknown460; // Inferred role: eye blink param list; original member name unknown.
  mm::mtl::IntrusivePtr<ParamList> unknown468; // Inferred role: unique motion param list; original member name unknown.
  u8 _470[0x488 - 0x470];
  mm::mtl::IntrusivePtr<ParamList> unknown488; // Inferred role: field AI param list, read by AIAgentField::setup; original member name unknown.
  mm::mtl::IntrusivePtr<ParamList> unknown490; // Inferred role: pc collision param list, read by gf::getPcColiParameter; original member name unknown.
  u8 _498[0x4a8 - 0x498];
  mm::mtl::IntrusivePtr<ParamList> unknown4a8; // Inferred role: menu param list; original member name unknown.
  mm::mtl::IntrusivePtr<ParamList> unknown4b0; // Inferred role: enemy move param list, read by gf::getEnemeyMoveParam; original member name unknown.
  u8 _4b8[0x4c8 - 0x4b8];
  mm::mtl::IntrusivePtr<ParamList> unknown4c8; // Inferred role: effect param list; original member name unknown.
};

static_assert(offsetof(ParamManager, unknown430) == 0x430, "");
static_assert(offsetof(ParamManager, unknown438) == 0x438, "");
static_assert(offsetof(ParamManager, unknown440) == 0x440, "");
static_assert(offsetof(ParamManager, unknown458) == 0x458, "");
static_assert(offsetof(ParamManager, unknown460) == 0x460, "");
static_assert(offsetof(ParamManager, unknown468) == 0x468, "");
static_assert(offsetof(ParamManager, unknown488) == 0x488, "");
static_assert(offsetof(ParamManager, unknown490) == 0x490, "");
static_assert(offsetof(ParamManager, unknown4a8) == 0x4a8, "");
static_assert(offsetof(ParamManager, unknown4b0) == 0x4b0, "");
static_assert(offsetof(ParamManager, unknown4c8) == 0x4c8, "");

} // namespace fw
