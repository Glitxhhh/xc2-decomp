#pragma once
#include <new>
#include <stddef.h>

#include "grlib/cglib_mem_handle.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"
#include "types.h"

namespace grlib {

class CGLibDblUniformBlock;
class CGLibOneUniformBlock;
class CGLibTriUniformBlock;

template <typename T> class CGLibUniformArray {
public:
  CGLibUniformArray() : m_items(nullptr), unknown08(0), unknown0c(0), unknown10(0) {}
  void setupArray(u32 count);
  T &operator[](u32 index) { return m_items[index]; }
  // Inferred helper: releases the items and frees the array, as setupArray and LayerObjTopDef::~LayerObjTopDef do;
  // original name unknown.
  void unknown001() {
    for (u32 i = 0; i < unknown08; i++) {
      m_items[i].release();
    }
    unknown08 = 0;
    if (m_items != nullptr) {
      mtl::MemManager::deallocate(m_items, 0, false);
      m_items = nullptr;
    }
    CGLibMemHandle::free(unknown18);
  }
  // Inferred helper: allocates the unknown0c bytes counted by the caller as the uniform memory, then resets the offset; original name unknown.
  void unknown002() {
    CGLibMemHandle::free(unknown18);
    if (unknown0c != 0) {
      CGLibMemHandle::allocUniform(unknown18, unknown0c);
      unknown10 = unknown0c;
      unknown0c = 0;
    }
    unknown0c = 0;
  }

  T *m_items;
  u32 unknown08; // Inferred role: item count; original member name unknown.
  u32 unknown0c; // Inferred role: uniform memory size, then setup offset; original member name unknown.
  u32 unknown10; // Inferred role: allocated uniform memory size; original member name unknown.
  u8 _14[0x18 - 0x14];
  CGLibMemType unknown18; // Inferred role: mem type; original member name unknown.
};

template <typename T> void CGLibUniformArray<T>::setupArray(u32 count) {
  unknown001();
  unknown08 = count;
  m_items = static_cast<T *>(mtl::MemManager::allocate(CGLibMemHandle::s_hMemHandle, count * sizeof(T), 8, false, "no name", 0));
  for (u32 i = 0; i < unknown08; i++) {
    new (&m_items[i]) T();
  }
}

class CGLibDblUniformArray : public CGLibUniformArray<CGLibDblUniformBlock> {};
class CGLibOneUniformArray : public CGLibUniformArray<CGLibOneUniformBlock> {};
class CGLibTriUniformArray : public CGLibUniformArray<CGLibTriUniformBlock> {};

static_assert(offsetof(CGLibUniformArray<CGLibOneUniformBlock>, unknown08) == 0x08, "");
static_assert(offsetof(CGLibUniformArray<CGLibOneUniformBlock>, unknown0c) == 0x0c, "");
static_assert(offsetof(CGLibUniformArray<CGLibOneUniformBlock>, unknown10) == 0x10, "");
static_assert(offsetof(CGLibUniformArray<CGLibOneUniformBlock>, unknown18) == 0x18, "");
static_assert(sizeof(CGLibUniformArray<CGLibOneUniformBlock>) == 0x28, "");

} // namespace grlib
