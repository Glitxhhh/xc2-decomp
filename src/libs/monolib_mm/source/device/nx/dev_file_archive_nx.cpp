#include "device/nx/dev_file_archive_nx.h"

#include "ml/file_handle_th.h"
#include "mm_mtl/fixstr.h" // IWYU pragma: keep
#include "mm_mtl/internal/fixed_object_allocator.h"
#include "mm_mtl/tuple.h" // IWYU pragma: keep
#include "nn/fs.h"        // IWYU pragma: keep

namespace ml {

u32 DevFileArchiveNx::addressAlignment() { return 16; }

DevFileJobTh *DevFileArchiveNx::createWriter(mtl::ALLOC_HANDLE handle) { return nullptr; }

DevFileJobTh *DevFileArchiveNx::createFileValid(mtl::ALLOC_HANDLE handle) { return new (handle) DevFileJobValidArcNxTh(); }

bool DevFileArchiveNx::rfClose(FileHandleTh *handle) {
  unknown001 *channel = &*get()->unknown20 + handle->unknown1d4;
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

bool DevFileArchiveNx::rfIsUsedChannel(u32 channel) { return (&*unknown20 + channel)->unknown10c; }

} // namespace ml

template mm::mtl::PtrSingleton<ml::DevFileArchiveNx>::~PtrSingleton();
template mm::mtl::Tuple<unsigned long, nn::fs::FileHandle, mm::mtl::FixStr<256>> *
mm::mtl::FixedObjectAllocator<mm::mtl::Tuple<unsigned long, nn::fs::FileHandle, mm::mtl::FixStr<256>>, 16>::allocate();
