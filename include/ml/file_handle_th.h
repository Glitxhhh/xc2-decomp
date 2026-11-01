#pragma once
#include <stddef.h>

#include "mm_mtl/allocator.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"
#include "types.h"

namespace ml {

class IWorkEvent;
struct DevFileParamTh;
enum CBM : int;

class FileHandleTh {
public:
  enum FTYPE {
    FTYPE_UNKNOWN_1 = 1, // Inferred role: buffer allocated from the memory handle.
    FTYPE_UNKNOWN_2 = 2, // Inferred role: buffer allocated from an allocator.
  };

  FileHandleTh(const DevFileParamTh &param);
  ~FileHandleTh() {
    releaseBuffer();
    unknown1f4 = false;
    unknown1e0 = 0;
  }

  void releaseBuffer() {
    if (unknown00 == FTYPE_UNKNOWN_1) {
      if (unknown08 != nullptr && unknown70 == nullptr) {
        if (mtl::MemManager::valid(unknown2c, true)) {
          if (unknown08 == nullptr) {
            return;
          }
          mtl::MemManager::deallocate(unknown08, 0, false);
        }
        unknown08 = nullptr;
      }
    } else if (unknown00 == FTYPE_UNKNOWN_2) {
      if (unknown08 != nullptr && unknown70 == nullptr) {
        if (unknown30 != nullptr) {
          static_cast<mm::mtl::IAllocator *>(unknown30)->deallocate(unknown08);
        }
        unknown08 = nullptr;
      }
    }
  }

  void setup(const DevFileParamTh &param);

  bool addCurrentPtr(int offset);
  bool setCurrentPtr(int offset);
  void setReadAdr(int size, void *buffer, int alignedSize);
  void setTime(u64 time);
  bool call(CBM cbm);

  FTYPE unknown00; // Inferred role: buffer type; original member name unknown.
  void *unknown08; // Inferred role: read buffer; original member name unknown.
  s32 unknown10;   // Inferred role: allocated size; original member name unknown.
  s32 unknown14;   // Inferred role: read offset; original member name unknown.
  s32 unknown18;   // Inferred role: read size; original member name unknown.
  s32 unknown1c;   // Role and original member name unknown.
  s32 unknown20;   // Role and original member name unknown.
  s32 unknown24;   // Role and original member name unknown.
  s32 m_currentPtr;
  mtl::ALLOC_HANDLE unknown2c;            // Inferred role: mem handle; original member name unknown.
  void *unknown30;                        // Inferred role: file size, or the allocator of the buffer; original member name unknown.
  mm::mtl::FixedVector<u32, 8> unknown38; // Role and original member name unknown.
  IWorkEvent *unknown60;                  // Inferred role: event listener; original member name unknown.
  void *unknown68;                        // Inferred role: event; original member name unknown.
  void **unknown70;                       // Inferred role: loaded data output; original member name unknown.
  s32 *unknown78;                         // Inferred role: loaded size output; original member name unknown.
  s32 unknown80;                          // Role and original member name unknown.
  u64 unknown88;                          // Role and original member name unknown.
  u32 unknown90;                          // Role and original member name unknown.
  u32 unknown94;                          // Inferred role: state flags; original member name unknown.
  mm::mtl::FixStr<256> unknown98;         // Inferred role: path; original member name unknown.
  mm::mtl::FixStr<32> unknown19c;         // Role and original member name unknown.
  u64 m_time;
  u64 unknown1c8;  // Inferred role: file time; original member name unknown.
  s32 unknown1d0;  // Role and original member name unknown.
  u32 unknown1d4;  // Inferred role: file channel; original member name unknown.
  s32 unknown1d8;  // Role and original member name unknown.
  u64 unknown1e0;  // Role and original member name unknown.
  s32 unknown1e8;  // Inferred role: job state (2 loaded, 4 load failed); original member name unknown.
  s32 unknown1ec;  // Role and original member name unknown.
  s32 unknown1f0;  // Role and original member name unknown.
  bool unknown1f4; // Role and original member name unknown.
  u8 _1f5[0x200 - 0x1f5];
};

static_assert(offsetof(FileHandleTh, unknown08) == 0x08, "");
static_assert(offsetof(FileHandleTh, unknown10) == 0x10, "");
static_assert(offsetof(FileHandleTh, unknown18) == 0x18, "");
static_assert(offsetof(FileHandleTh, unknown20) == 0x20, "");
static_assert(offsetof(FileHandleTh, m_currentPtr) == 0x28, "");
static_assert(offsetof(FileHandleTh, unknown2c) == 0x2c, "");
static_assert(offsetof(FileHandleTh, unknown30) == 0x30, "");
static_assert(offsetof(FileHandleTh, unknown38) == 0x38, "");
static_assert(offsetof(FileHandleTh, unknown60) == 0x60, "");
static_assert(offsetof(FileHandleTh, unknown68) == 0x68, "");
static_assert(offsetof(FileHandleTh, unknown80) == 0x80, "");
static_assert(offsetof(FileHandleTh, unknown88) == 0x88, "");
static_assert(offsetof(FileHandleTh, unknown94) == 0x94, "");
static_assert(offsetof(FileHandleTh, unknown98) == 0x98, "");
static_assert(offsetof(FileHandleTh, unknown19c) == 0x19c, "");
static_assert(offsetof(FileHandleTh, m_time) == 0x1c0, "");
static_assert(offsetof(FileHandleTh, unknown1c8) == 0x1c8, "");
static_assert(offsetof(FileHandleTh, unknown1d4) == 0x1d4, "");
static_assert(offsetof(FileHandleTh, unknown1e0) == 0x1e0, "");
static_assert(offsetof(FileHandleTh, unknown1e8) == 0x1e8, "");
static_assert(offsetof(FileHandleTh, unknown1f4) == 0x1f4, "");
static_assert(sizeof(FileHandleTh) == 0x200, "");

} // namespace ml
