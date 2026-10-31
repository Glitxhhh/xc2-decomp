#include "device/nx/dev_file_nx_th.h"

#include "ml/critical_section.h"
#include "mm_mtl/internal/heap_allocator.h"
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

} // namespace ml

template mm::mtl::PtrSingleton<ml::DevFileNxTh>::~PtrSingleton();
template mm::mtl::PtrSingleton<ml::DevFileBlackListNxTh>::~PtrSingleton();
