#pragma once
#include <stddef.h>

#include "ml/dev_file_accessor.h"
#include "ml/dev_file_job_th.h"
#include "mm_mtl/singleton.h"
#include "mm_mtl/unique_ptr.h"
#include "mm_thread/mm_thread_csection.h"
#include "mtl/alloc_handle.h"
#include "nn/fs.h"
#include "types.h"

namespace ml {

class DevFileArchiveNx : public DevFileAccessor, public mm::mtl::PtrSingleton<DevFileArchiveNx> {
public:
  // Inferred type: file channel; the original type name is unknown.
  struct unknown001 {
    nn::fs::FileHandle unknown00; // Inferred role: file; original member name unknown.
    u8 _008[0x10c - 0x8];
    bool unknown10c; // Inferred role: used; original member name unknown.
    bool unknown10d; // Inferred role: reading; original member name unknown.
    u8 _10e;
    bool unknown10f; // Inferred role: read in progress, the close is deferred; original member name unknown.
    bool unknown110; // Inferred role: close requested; original member name unknown.
    u8 _111[0x1a8 - 0x111];
    mm::threading::ReadWriteLock unknown1a8; // Inferred role: lock; original member name unknown.
    u8 _1c8[0x1d8 - 0x1c8];
  };

  bool initialize() override;
  u32 addressAlignment() override;
  DevFileJobTh *createWriter(mtl::ALLOC_HANDLE handle) override;
  DevFileJobTh *createFileValid(mtl::ALLOC_HANDLE handle) override;
  bool rfClose(FileHandleTh *handle) override;
  bool rfIsUsedChannel(u32 channel) override;

  u8 _10[0x14 - 0x10];
  mtl::ALLOC_HANDLE unknown14; // Inferred role: memory; original member name unknown.
  s32 unknown18;               // Inferred role: state; original member name unknown.
  u8 _1c[0x20 - 0x1c];
  mm::mtl::UniquePtr<unknown001> unknown20; // Inferred role: channels; original member name unknown.
};

static_assert(sizeof(DevFileArchiveNx::unknown001) == 0x1d8, "");
static_assert(offsetof(DevFileArchiveNx::unknown001, unknown10c) == 0x10c, "");
static_assert(offsetof(DevFileArchiveNx::unknown001, unknown110) == 0x110, "");
static_assert(offsetof(DevFileArchiveNx::unknown001, unknown1a8) == 0x1a8, "");
static_assert(offsetof(DevFileArchiveNx, unknown14) == 0x14, "");
static_assert(offsetof(DevFileArchiveNx, unknown20) == 0x20, "");

class DevFileJobValidArcNxTh : public DevFileJobTh {
public:
  bool asyncUpdate() override;
};

} // namespace ml
