#include "device/nx/dev_file_archive_nx.h"

#include <string.h>

#include "ml/file_handle_th.h"
#include "mm_mtl/fixstr.h" // IWYU pragma: keep
#include "mm_mtl/internal/fixed_object_allocator.h"
#include "mm_mtl/tuple.h" // IWYU pragma: keep
#include "nn/fs.h"        // IWYU pragma: keep
#include "nn/result.h"

namespace ml {

void DevFileArchiveNx::Param::finalize() {
  CS cs(unknown1800);
  while (!unknown29b8.empty()) {
    unknown002 *file = unknown29b8.pop_back();
    nn::fs::CloseFile(file->unknown001);
    unknown1828.deallocate(file);
  }
}

DevFileArchiveNx::Param::unknown002 *DevFileArchiveNx::Param::findThreadFilehandle(u64 threadId, const mm::mtl::FixStr<256> &path) {
  CS cs(unknown1800);
  for (unknown002 *file : unknown29b8) {
    if (file->unknown00 == threadId && strcmp(file->unknown002.c_str(), path.c_str()) == 0) {
      return file;
    }
  }
  return nullptr;
}

nn::fs::FileHandle *DevFileArchiveNx::Param::addThreadFilehandle(u64 threadId, const mm::mtl::FixStr<256> &path) {
  CS cs(unknown1800);
  for (unknown002 *opened : unknown29b8) {
    if (opened->unknown00 == threadId && strcmp(opened->unknown002.c_str(), path.c_str()) == 0) {
      return &opened->unknown001;
    }
  }
  unknown002 *file = unknown1828.allocate();
  file->unknown00 = threadId;
  file->unknown002 = path;
  if (!nn::fs::OpenFile(&file->unknown001, path.c_str(), 1).IsSuccess()) {
    unknown1828.deallocate(file);
    return nullptr;
  }
  unknown29b8.push(file);
  return &file->unknown001;
}

u32 DevFileArchiveNx::addressAlignment() { return 16; }

DevFileJobTh *DevFileArchiveNx::createLoader(mtl::ALLOC_HANDLE handle) { return new (handle) DevFileJobTh(); }

DevFileJobTh *DevFileArchiveNx::createWriter(mtl::ALLOC_HANDLE handle) { return nullptr; }

DevFileJobTh *DevFileArchiveNx::createFileValid(mtl::ALLOC_HANDLE handle) { return new (handle) DevFileJobValidArcNxTh(); }

bool DevFileArchiveNx::rfClose(FileHandleTh *handle) {
  unknown001 *channel = get()->unknown20->unknown0000 + handle->unknown1d4;
  mm::threading::WriteLockGuard guard(channel->unknown1a8);
  if (channel->unknown10f) {
    handle->unknown94 |= 0x10000;
    handle->unknown60 = nullptr;
    channel->unknown110 = true;
  } else {
    if (channel->unknown10d) {
      channel->unknown10d = false;
    }
    nn::fs::CloseFile(channel->unknown00);
    channel->unknown10c = false;
  }
  return false;
}

bool DevFileArchiveNx::rfIsUsedChannel(u32 channel) { return (unknown20->unknown0000 + channel)->unknown10c; }

} // namespace ml

template mm::mtl::PtrSingleton<ml::DevFileArchiveNx>::~PtrSingleton();
template mm::mtl::Tuple<unsigned long, nn::fs::FileHandle, mm::mtl::FixStr<256>> *
mm::mtl::FixedObjectAllocator<mm::mtl::Tuple<unsigned long, nn::fs::FileHandle, mm::mtl::FixStr<256>>, 16>::allocate();
