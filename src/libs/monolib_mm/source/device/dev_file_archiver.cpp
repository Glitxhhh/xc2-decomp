#include <stddef.h>

#include "device/dev_file_dic_allocator.h"
#include "mm_mtl/singleton.h" // IWYU pragma: keep
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace ml {

class DevFileArchiver; // IWYU pragma: keep

DevFileDicAllocator::DevFileDicAllocator(mtl::ALLOC_HANDLE mem) : m_mem(mem) {}

void DevFileDicAllocator::setMemHandle(mtl::ALLOC_HANDLE mem) { m_mem = mem; }

void *DevFileDicAllocator::allocate(size_t size, size_t alignment) { return mtl::MemManager::allocate(m_mem, size, alignment, false, "no name", 0); }

void DevFileDicAllocator::deallocate(void *pointer) { mtl::MemManager::deallocate(pointer, 0, false); }

void *DevFileDicAllocator::reallocate(void *pointer, size_t size) {
  if (pointer != nullptr) {
    return mtl::MemManager::reallocate(pointer, size, false);
  }
  return mtl::MemManager::allocate(m_mem, size, 4, false, "no name", 0);
}

} // namespace ml

template mm::mtl::PtrSingleton<ml::DevFileArchiver>::~PtrSingleton();
