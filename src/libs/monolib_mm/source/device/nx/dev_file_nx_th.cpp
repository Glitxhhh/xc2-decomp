#include "device/nx/dev_file_nx_th.h"

#include "ml/critical_section.h"
#include "ml/file_handle_th.h"
#include "ml/work_root.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/internal/heap_allocator.h"
#include "mtl/mem_manager.h"
#include "nn/account.h"
#include "nn/fs.h"

namespace ml {

class DevFileBlackListNxTh; // IWYU pragma: keep

namespace dfn_detail {

mm::mtl::HeapAllocator g_allocator;

} // namespace dfn_detail

bool DevFileNxTh::m_mountRom;
bool DevFileNxTh::m_mountSave;
bool DevFileNxTh::m_validuser;
nn::account::UserHandle DevFileNxTh::m_appuser;
mm::mtl::FixStr<256> DevFileNxTh::m_rootPath;

void DevFileNxTh::finalizeSDK() {
  if (m_mountSave) {
    nn::fs::Unmount("save");
  }
  if (m_mountRom) {
    nn::fs::Unmount("rom");
  }
  if (m_validuser) {
    nn::account::CloseUser(m_appuser);
  }
}

void DevFileNxTh::flushSave() {
  if (m_mountSave) {
    nn::fs::CommitSaveData("save");
  }
}

CriticalSection &DevFileNxTh::getLocker() {
  static CriticalSection sect;
  return sect;
}

void *DevFileNxTh::allocate(size_t size) {
  CS cs(getLocker());
  return dfn_detail::g_allocator.allocate(size, 16);
}

void DevFileNxTh::deallocate(void *pointer, size_t size) {
  CS cs(getLocker());
  dfn_detail::g_allocator.deallocate(pointer);
}

u32 DevFileNxTh::addressAlignment() { return 16; }

bool DevFileNxTh::rfIsUsedChannel(u32 channel) { return (&*unknown20 + channel)->unknown10c; }

void DevFileNxTh::setMediaRootPath(const char *path) { m_rootPath = path; }

DevFileJobTh *DevFileNxTh::createFileValid(mtl::ALLOC_HANDLE handle) { return new (handle) DevFileJobValidNxTh(); }

bool DevFileNxTh::readBlock(FileHandleTh *handle, const char *path) {
  void *buffer = mtl::MemManager::allocate(WorkRoot::getMemTMP(), 0x20000, 4, false, "no name", 0);
  bool isRead = readBlockSlice(handle, path, buffer, 0x20000);
  if (buffer != nullptr) {
    mtl::MemManager::deallocate(buffer, 0, false);
  }
  return isRead;
}

bool DevFileNxTh::rfClose(FileHandleTh *handle) {
  unknown001 *channel = &*get()->unknown20 + handle->unknown1d4;
  mm::threading::WriteLockGuard guard(channel->unknown1a8);
  bool isClosed = false;
  if (channel->unknown10f) {
    handle->unknown94 |= 0x10000;
    handle->unknown60 = nullptr;
    channel->unknown110 = true;
  } else {
    if (channel->unknown10d) {
      channel->unknown10d = false;
    }
    nn::fs::CloseFile(channel->unknown00);
    isClosed = true;
    channel->unknown10c = false;
  }
  return isClosed;
}

} // namespace ml

template mm::mtl::PtrSingleton<ml::DevFileNxTh>::~PtrSingleton();
template mm::mtl::PtrSingleton<ml::DevFileBlackListNxTh>::~PtrSingleton();
