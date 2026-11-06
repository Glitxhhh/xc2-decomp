#pragma once
#include "framework/memory/allocator.h"
#include "framework/reflection.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/map.h"
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

  // Inferred role: header of a resolved param binary; original type name unknown.
  struct unknown006 {
    u32 unknown00;         // Inferred role: entry count; original member name unknown.
    unknown005 *unknown08; // Inferred role: entries; original member name unknown.
  };

  explicit ParamList(const unknown006 *binary) : unknown0c(0), unknown10(nullptr) {
    if (binary != nullptr) {
      unknown0c = binary->unknown00;
      unknown10 = binary->unknown08;
    }
  }

  u32 unknown0c;                               // Inferred role: count; original member name unknown.
  unknown005 *unknown10;                       // Inferred role: entries; original member name unknown.
  mm::mtl::IntrusivePtr<Reflection> unknown18; // Inferred role: reflection of the entries; original member name unknown.
};

static_assert(offsetof(ParamList::unknown006, unknown08) == 0x08, "");

static_assert(offsetof(ParamList, unknown0c) == 0x0c, "");
static_assert(offsetof(ParamList, unknown10) == 0x10, "");
static_assert(offsetof(ParamList, unknown18) == 0x18, "");
static_assert(sizeof(ParamList) == 0x20, "");

class ParamAdapter {
public:
  template <typename T> const T *get() const { return unknown00 != nullptr ? static_cast<const T *>(unknown00->param) : nullptr; }

  const ParamList::unknown005 *unknown00; // Inferred role: entry; original member name unknown.
};

static_assert(sizeof(ParamAdapter) == 0x08, "");

class ParamManager : public mm::mtl::PtrSingleton<ParamManager> {
public:
  // Layout from the node size (0xb8) and the node destructor that releases the pointer at the start of the value.
  struct RefInfo {
    mm::mtl::IntrusivePtr<Reflection> unknown00; // Inferred role: reflection; original member name unknown.
    mm::mtl::FixStr<128> unknown08;              // Inferred role: file name; original member name unknown.
  };

  // Layout from the node size (0xb8) and the node destructor that releases the pointer at the start of the value.
  struct ParamInfo {
    mm::mtl::IntrusivePtr<ParamList> unknown00; // Inferred role: param list; original member name unknown.
    mm::mtl::FixStr<128> unknown08;             // Inferred role: file name; original member name unknown.
  };

  ParamManager() : unknown808(Allocator::getDebAllocator()), unknown820(Allocator::getDebAllocator()) {}

  void addReflectionFileName(Reflection &reflection, const char *name);

  mm::mtl::IntrusivePtr<Reflection> unknown08[128];      // Inferred role: reflections, released from 0x400 down by the destructor; element type and original member name unknown.
  mm::mtl::IntrusivePtr<ParamList> unknown408[128];      // Inferred role: param lists indexed by the ParamBuilder::create id, released from 0x800 down by the destructor; original member name unknown.
  mm::mtl::Map<const Reflection *, RefInfo> unknown808;  // Inferred role: reflection file names; original member name unknown.
  mm::mtl::Map<const ParamList *, ParamInfo> unknown820; // Inferred role: param list file names; original member name unknown.
};

static_assert(sizeof(ParamManager::RefInfo) == 0x90, "");
static_assert(sizeof(ParamManager::ParamInfo) == 0x90, "");
static_assert(offsetof(ParamManager, unknown08) == 0x08, "");
static_assert(offsetof(ParamManager, unknown408) == 0x408, "");
static_assert(offsetof(ParamManager, unknown808) == 0x808, "");
static_assert(offsetof(ParamManager, unknown820) == 0x820, "");
static_assert(sizeof(ParamManager) == 0x838, "");

} // namespace fw
