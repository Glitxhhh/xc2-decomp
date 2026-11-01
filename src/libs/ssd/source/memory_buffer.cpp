#include <stddef.h>

#include "ssd/ssd_allocator.h"
#include "ssd/ssd_buffer.h"
#include "ssd/ssd_memory_buffer.h"
#include "types.h"

namespace ssd {

// Inferred role: copy size bytes in units of T, then the bytes left over; original name unknown. CopyMemory8/16/32/64
// share this body: they only match as this body optimized on its own, then inlined.
template <typename T> inline void unknown001(const void *source, void *destination, unsigned long size) {
  const T *src = static_cast<const T *>(source);
  T *dst = static_cast<T *>(destination);
  // Unrolled by hand in the original (the game copies four units per iteration while four units remain, then copies
  // one unit per iteration in a loop the compiler unrolled separately).
  while (size >= sizeof(T) * 4) {
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[3] = src[3];
    size -= sizeof(T) * 4;
    src += 4;
    dst += 4;
  }
  while (size >= sizeof(T)) {
    *dst = *src;
    size -= sizeof(T);
    src++;
    dst++;
  }
  if (size > 0) {
    const u8 *srcByte = reinterpret_cast<const u8 *>(src);
    u8 *dstByte = reinterpret_cast<u8 *>(dst);
    while (size > 0) {
      *dstByte = *srcByte;
      size--;
      srcByte++;
      dstByte++;
    }
  }
}

void CopyMemory8(const void *source, void *destination, unsigned long size) { unknown001<u8>(source, destination, size); }

void CopyMemory16(const void *source, void *destination, unsigned long size) { unknown001<u16>(source, destination, size); }

void CopyMemory32(const void *source, void *destination, unsigned long size) { unknown001<u32>(source, destination, size); }

void CopyMemory64(const void *source, void *destination, unsigned long size) { unknown001<u64>(source, destination, size); }

void MemoryBuffer::Alloc(size_t size, size_t alignment, Allocator *allocator) {
  Allocator *buffer = SoundMemory::allocator_;
  if (allocator != nullptr) {
    buffer = allocator;
  }
  unknown18 = buffer;
  Allocator::Block *block = buffer->NewBufferImpl(size, 1, alignment);
  void *data;
  if (block != nullptr) {
    data = block->unknown08;
  } else {
    data = nullptr;
  }
  unknown08 = data;
  unknown10 = size;
}

void MemoryBuffer::Free() {
  if (unknown08 != nullptr) {
    Allocator *allocator = unknown18;
    Allocator::Block *block = allocator->GetMemoryBlock(unknown08);
    allocator->DeleteBufferImpl(block);
    unknown10 = 0;
    unknown18 = nullptr;
    unknown08 = nullptr;
  }
}

} // namespace ssd
