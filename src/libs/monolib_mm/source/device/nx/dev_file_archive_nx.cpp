#include "device/nx/dev_file_archive_nx.h"

#include "mm_mtl/fixstr.h" // IWYU pragma: keep
#include "mm_mtl/internal/fixed_object_allocator.h"
#include "mm_mtl/tuple.h" // IWYU pragma: keep
#include "nn/fs.h"        // IWYU pragma: keep

namespace ml {

u32 DevFileArchiveNx::addressAlignment() { return 16; }

DevFileJobTh *DevFileArchiveNx::createWriter(mtl::ALLOC_HANDLE handle) { return nullptr; }

bool DevFileArchiveNx::rfIsUsedChannel(u32 channel) { return (&*unknown20 + channel)->unknown10c; }

} // namespace ml

template mm::mtl::PtrSingleton<ml::DevFileArchiveNx>::~PtrSingleton();
template mm::mtl::Tuple<unsigned long, nn::fs::FileHandle, mm::mtl::FixStr<256>> *
mm::mtl::FixedObjectAllocator<mm::mtl::Tuple<unsigned long, nn::fs::FileHandle, mm::mtl::FixStr<256>>, 16>::allocate();
