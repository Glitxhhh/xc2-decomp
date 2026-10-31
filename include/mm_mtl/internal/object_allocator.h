#pragma once
#include <stddef.h>

#include "mm_mtl/array.h"
#include "mm_mtl/construct.h"
#include "mm_mtl/reserved_bitflag.h"
#include "types.h"

namespace mm {
namespace mtl {

template <typename T> class ObjectAllocator {
public:
  void destroy() {
    for (u32 i = 0; i < m_capacity; i++) {
      if (unknown18.getLocal(i)) {
        destruct(unknown001(i));
        unknown18.clrLocal(i);
      }
    }
    m_allocated = 0;
    unknown00.destroy();
    unknown18.destroy();
    m_capacity = 0;
  }

  // Inferred role: address of the slot at index; original name unknown.
  T *unknown001(u32 index) {
    u32 offset = index * sizeof(T);
    return reinterpret_cast<T *>(&unknown00[offset / 8]);
  }

  Array<u64> unknown00;      // Inferred role: object storage in 8 byte units; original member name unknown.
  ReservedBitflag unknown18; // Inferred role: used-slot bitflag; original member name unknown.
  u32 m_allocated;
  u32 m_capacity;
};

static_assert(offsetof(ObjectAllocator<u32>, unknown18) == 0x18, "");
static_assert(offsetof(ObjectAllocator<u32>, m_allocated) == 0x30, "");
static_assert(offsetof(ObjectAllocator<u32>, m_capacity) == 0x34, "");
static_assert(sizeof(ObjectAllocator<u32>) == 0x38, "");

} // namespace mtl
} // namespace mm
