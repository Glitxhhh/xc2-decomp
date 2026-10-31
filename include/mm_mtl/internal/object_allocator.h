#pragma once
#include <new>
#include <stddef.h>

#include "mm/mm_std_base.h"
#include "mm_mtl/array.h"
#include "mm_mtl/construct.h"
#include "mm_mtl/reserved_bitflag.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;

template <typename T> class ObjectAllocator {
public:
  // The assert lines of the game: their constants change the instruction encoding.
#line 113
  void reserve(IAllocator *allocator, u32 size) {
    MM_ASSERT(size != 0);
    MM_ASSERT(allocator != 0);
    MM_ASSERT(m_capacity == 0 && "already reserved!!");
    u32 bytes = size * sizeof(T);
    m_capacity = size;
    u32 count = (bytes + sizeof(u64) - 1) / sizeof(u64);
    unknown00.setAllocator(allocator);
    unknown00.reserve(count);
    unknown18.initialize(allocator, size);
  }

#line 131
  T *allocate() {
    MM_ASSERT(m_allocated <= m_capacity);
    if (m_allocated != m_capacity) {
      for (u32 word = 0; word < unknown18.unknown0c; word++) {
        if (unknown18.m_element[word] != 0xffffffff) {
          u32 last = word * 32 + 32;
          if (last > m_capacity) {
            last = m_capacity;
          }
          for (u32 i = word * 32; i < last; i++) {
            if (!unknown18.getLocal(i)) {
              T *object = unknown001(i);
              if (object != nullptr) {
                new (object) T;
                unknown18.setLocal(i, true);
                m_allocated++;
#line 220
                MM_ASSERT(m_allocated <= m_capacity);
                return object;
              }
            }
          }
        }
      }
    }
    return nullptr;
  }

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
