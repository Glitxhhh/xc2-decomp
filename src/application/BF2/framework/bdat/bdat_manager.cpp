#include <stddef.h>

#include "bdat.h"
#include "framework/lang_util.h"
#include "fw/fw_bdat_manager.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/hash.h"
#include "mm_mtl/map.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace fw {

struct UpdateInfo;

bool BdatManager::Impl::isMsgFile(const char *name) { return __builtin_strstr(name, "_ms.") != nullptr; }

// The game (0x7100152c60) computes the length of `name` and checks it against the capacity once in each arm, then both arms
// join in the shared strcat of the tail. Written as `if (...) { lang; "/"; } path += name;` the function has 77 instructions
// against the game's 90 (first difference at +0x28, the branch target of the msg test), so `path += name` is written in both arms.
void BdatManager::Impl::makePath(mm::mtl::FixStr<256> &path, const char *name) {
  if (isMsgFile(name)) {
    path += LangUtil::getLangFolder().c_str();
    path += "/";
    path += name;
  } else {
    path += name;
  }
}

void BdatManager::Impl::loadBdatFromMemory(int id, void *data) {
  BdatInfo &info = unknown128[id];
  info.unknown04.clear();
  info.unknown108.clear();
  info.unknown00 = STATE_UNKNOWN_2;
  info.unknown140 = 0;
  info.unknown148 = data;
  info.unknown150 = mtl::ALLOC_HANDLE();
  info.unknown158 = nullptr;
  info.unknown12c = LangUtil::getLangFolder().c_str();
  info.unknown160 = true;
  updateLayer(id, info);
}

BdatManager::Impl::~Impl() {
  for (int i = 0; i < BDAT_UNKNOWN_16; i++) {
    unregistBdat(i);
  }
}

void BdatManager::Impl::unregistBdat(const char *name) {
  int id = find(name);
  if (id >= 0) {
    unregistBdat(id);
  }
}

bool BdatManager::Impl::isExistBdat(int id) const { return unknown128[id].unknown158 != nullptr || unknown128[id].unknown148 != nullptr; }

bool BdatManager::Impl::isEnableBdat(int id) const {
  if (!isExistBdat(id)) {
    return false;
  }

  return unknown128[id].unknown00 == STATE_UNKNOWN_3;
}

unsigned char *BdatManager::Impl::getFp(const char *name) {
  mm::mtl::Map<u32, SheetFpInfo>::iterator it = unknown110.find(mm::mtl::hashStrCrc(name));
  if (it == unknown110.end()) {
    return nullptr;
  }
  return it->second.unknown68;
}

void BdatManager::Impl::update(const UpdateInfo &info) {
  for (int i = 0; i < BDAT_UNKNOWN_16; i++) {
    updateLayer(i, unknown128[i]);
  }
}

void BdatManager::update(const UpdateInfo &info) {
  if (!isFinalized()) {
    // Impl::update, defined in this file, never reads its info parameter, so the game never sets x1 for the tail call
    // (0x7100154240): the compiler erased the argument (ruling 2026-11-13 #6). The original expression cannot be checked;
    // info, the parameter of this function, is the plausible one.
    unknown18->update(info);
  }
}

unsigned char *BdatManager::getFp(const char *name) { return get()->unknown18->getFp(name); }

bool BdatManager::initialize() { return true; }

bool BdatManager::finalize() {
  if (unknown18 != nullptr) {
    delete unknown18;
    unknown18 = nullptr;
  }

  return true;
}

void BdatManager::setBasePath(const char *path) { get()->unknown18->unknown08 = path; }

const char *BdatManager::getLocale() { return LangUtil::getLangFolder().c_str(); }

bool BdatManager::loadBdat(int id, mtl::ALLOC_HANDLE handle, const char *path) { return get()->unknown18->loadBdat(id, handle, path); }

void BdatManager::reloadBdat(int id) { get()->unknown18->reloadBdat(id); }

void BdatManager::loadBdatFromMemory(int id, mtl::ALLOC_HANDLE handle, void *data, size_t size, const char *name) { get()->unknown18->loadBdatFromMemory(id, handle, data, size, name); }

void BdatManager::loadBdatFromMemory(int id, void *data) { get()->unknown18->loadBdatFromMemory(id, data); }

void BdatManager::unregistBdat(int id) { get()->unknown18->unregistBdat(id); }

void BdatManager::unregistBdat(const char *name) { get()->unknown18->unregistBdat(name); }

bool BdatManager::isExistBdat(int id) { return get()->unknown18->isExistBdat(id); }

bool BdatManager::isEnableBdat(int id) { return get()->unknown18->isEnableBdat(id); }

unsigned char *BdatManager::getFp(int table, int id) { return Bdat::getFP(table, id); }

} // namespace fw

typedef mm::mtl::Map<u32, fw::BdatManager::Impl::SheetFpInfo>::tree_type unknown101;

template void unknown101::free_node(unknown101::node *, bool);
template void unknown101::erase(unknown101::node *);
template void unknown101::rebalance_after_erase(unknown101::node *);
template unknown101::node *unknown101::insert(const mm::mtl::MapPair<u32, fw::BdatManager::Impl::SheetFpInfo> &);
template void unknown101::rebalance(unknown101::node *);
