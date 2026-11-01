#include "gf/asset/gf_asset_pack.h"

#include "gf/asset/gf_asset_manager.h"
#include "gf/asset/gf_asset_pack_info.h"
#include "gf/asset/gf_asset_resource.h"
#include "gf/asset/gf_asset_util.h"
#include "gf/asset/gf_file_size_pool.h"
#include "gf/asset/gf_slot.h"
#include "gf/asset/gf_slot_mapping.h"
#include "gf/sound/gf_sound.h"
#include "gf/util/gf_util.h"
#include "ml/fixed_size_alloc.h"
#include "mm_mtl/algorithm.h"
#include "mm_mtl/fixed_list.h" // IWYU pragma: keep
#include "mm_mtl/hash.h"
#include "mm_mtl/reference_object.h"

namespace gf {

class GfExtendResource : public mm::mtl::ReferenceObject {};

AssetPackInfo::~AssetPackInfo() {
  GfAssetPack **end = unknown10.end();
  for (GfAssetPack **it = unknown10.begin(); it != end; ++it) {
    GfAssetPack *pack = *it;
    pack->unknown254--;
    *it = nullptr;
    GfAssetManager::callEventAssetPack(pack);
    mm::mtl::safeRelease(pack);
  }
}

void AssetPackInfo::setLoadComplete() { unknown307 = false; }

void AssetPackInfo::setupLoadStart() { unknown334 = 0; }

void AssetPackInfo::replaceAssetPack(GfAssetType from, GfAssetType to, GfAssetPack *pack) { unknown308 = to; }

void AssetPackInfo::setExtendResource(u32 index, GfExtendResource *resource) { unknown2e0[index] = resource; }

void AssetPackInfo::releaseExtResource() {
  for (u32 i = 0; i < 4; i++) {
    mm::mtl::safeRelease(unknown2e0[i]);
  }
}

void AssetPackInfo::setNoCache(bool noCache) {
  for (GfAssetPack **it = unknown10.begin(); it != unknown10.end(); ++it) {
    (*it)->unknown239 = noCache;
  }
}

void AssetPackInfo::setUsingGame(bool usingGame) {
  if (usingGame) {
    for (GfAssetPack **it = unknown10.begin(); it != unknown10.end(); ++it) {
      GfAssetPack *pack = *it;
      if (pack != nullptr) {
        pack->createSoundPack();
        pack->addRef();
      }
    }
  } else {
    for (GfAssetPack **it = unknown10.begin(); it != unknown10.end(); ++it) {
      GfAssetPack *pack = *it;
      if (pack != nullptr) {
        pack->destroySoundPack();
        pack->release();
      }
    }
  }
  unknown305 = usingGame;
}

void AssetPackInfo::releaseEmptySlot() {
  for (GfAssetPack **it = unknown10.begin(); it != unknown10.end(); ++it) {
    (*it)->releaseEmptySlot();
  }
}

bool AssetPackInfo::isCached() const {
  if (unknown307) {
    for (GfAssetPack *const *it = unknown10.begin(); it != unknown10.end(); ++it) {
      if (!(*it)->isEnableReload()) {
        return false;
      }
    }
  } else {
    for (GfAssetPack *const *it = unknown10.begin(); it != unknown10.end(); ++it) {
      if (!(*it)->isCached()) {
        return false;
      }
    }
  }
  return true;
}

void AssetPackInfo::applyPreFileSize() {
  for (GfAssetPack *pack : unknown10) {
    pack->applyPreFileSize();
  }
}

bool AssetPackInfo::isPreSizeSizeValid() const {
  for (GfAssetPack *const *it = unknown10.begin(); it != unknown10.end(); ++it) {
    if (!(*it)->isPreSizeSizeValid()) {
      return false;
    }
  }
  return true;
}

void AssetPackInfo::lockEnterRersource() {
  for (GfAssetPack *pack : unknown10) {
    pack->lockEnterRersource();
  }
}

bool AssetPackInfo::isUseSameAsset(const AssetPackInfo *other) const {
  for (GfAssetPack *const *it = unknown10.begin(); it != unknown10.end(); ++it) {
    if (*it != nullptr) {
      for (GfAssetPack *const *otherIt = other->unknown10.begin(); otherIt != other->unknown10.end(); ++otherIt) {
        if (*otherIt != nullptr && *it == *otherIt) {
          return true;
        }
      }
    }
  }
  return false;
}

bool AssetPackInfo::isFullResource() const {
  for (GfAssetPack *const *it = unknown10.begin(); it != unknown10.end(); ++it) {
    if ((*it)->unknown23a) {
      return true;
    }
  }
  return false;
}

bool AssetPackInfo::isExistAssetPack(const GfAssetPack *pack) const {
  if (pack == nullptr) {
    return false;
  }
  for (GfAssetPack *const *it = unknown10.begin(); it != unknown10.end(); ++it) {
    if (*it == pack) {
      return true;
    }
  }
  return false;
}

void AssetPackInfo::setDestroy() {
  if (unknown304) {
    return;
  }
  unknown304 = true;
  GfAssetUtil::addDestroyObject(unknown08, true);
}

GfAssetPack *AssetPackInfo::getAssetPack(GF_SLOT_HANDLE *handle) const {
  for (GfAssetPack *const *it = unknown10.begin(); it != unknown10.end(); ++it) {
    if ((*it)->unknown230 == handle) {
      return *it;
    }
  }
  return nullptr;
}

void AssetPackInfo::setAssetPack(GfAssetType type, GfAssetPack *pack) {
  if (mm::mtl::find(unknown10.begin(), unknown10.end(), pack) != unknown10.end()) {
    return;
  }
  pack->addRef();
  unknown10.push_back(pack);
  pack->unknown254++;
  if (unknown308 == ASSET_TYPE_BASE) {
    unknown308 = type;
  }
}

void AssetPackInfo::setModelName(const char *name) { unknown30c = util::getFilePtrFromPath(name); }

void AssetPackInfo::setMotionName(const char *name) { unknown320 = util::getFilePtrFromPath(name); }

bool AssetPackInfo::getSlotHandle(mm::mtl::FixedVector<GF_SLOT_HANDLE *, 88> &slots) const {
  GfAssetPack *const *end = unknown10.end();
  for (GfAssetPack *const *it = unknown10.begin(); it != end; ++it) {
    GF_SLOT_HANDLE *slot = (*it)->unknown230;
    if (slot != INVALID_SLOT_HANDLE) {
      slots.push_back(slot);
    }
  }
  return !slots.empty();
}

GfAssetType GfAssetPack::getAssetType() const { return m_assetType.unknown00; }

const char *GfAssetPack::getAssetName() const { return m_assetType.unknown08.c_str(); }

void GfAssetPack::lockEnterRersource() {
  unknown2b8 = true;
  m_assetType.unknown108 = true;
}

bool GfAssetPack::setForceDestroy() {
  if (unknown238) {
    return false;
  }
  unknown238 = true;
  return true;
}

void GfAssetPack::setTimeout() { unknown23b = true; }

void GfAssetPack::setResource(GfFileIdx index, GfAssetResource *resource) {
  unknown001 entry;
  entry.unknown00 = resource;
  entry.unknown08 = index;
  unknown18.push_back(entry);
  resource->addRef();
}

void GfAssetPack::releaseResource() {
  destroySoundPack();
  for (unknown001 &entry : unknown18) {
    mm::mtl::safeRelease(entry.unknown00);
  }
  unknown18.clear();
}

void GfAssetPack::updateCacheCount() {
  if (unknown254 == 0) {
    if (unknown27c < 99) {
      unknown27c++;
    }
  } else if (unknown27c != 0) {
    unknown27c = 0;
  }
}

void GfAssetPack::updateReloadCount() {
  u32 userCount = unknown254;
  if (getRefCount() - userCount == 1) {
    if (unknown280 < 99) {
      unknown280++;
    }
  } else if (unknown280 != 0) {
    unknown280 = 0;
  }
}

bool GfAssetPack::isEnableReload() const { return unknown280 > 9; }

void GfAssetPack::releaseSlotHandle() {
  if (unknown230 != reinterpret_cast<GF_SLOT_HANDLE *>(-1)) {
    GfAssetManager::releaseSlotHandle(unknown230);
    unknown230 = reinterpret_cast<GF_SLOT_HANDLE *>(-1);
  }
}

bool GfAssetPack::isPreSizeSizeValid() const {
  for (GfAssetFiles::AssetFile *const *it = m_assetType.unknown50.begin(); it != m_assetType.unknown50.end(); ++it) {
    if ((*it)->unknown94 == -2) {
      return false;
    }
  }
  return !m_assetType.unknown50.empty();
}

bool GfAssetPack::isExistSameAsset(const GfAssetPack &other) const { return m_assetType.isExistSameAsset(other.m_assetType); }

void GfAssetPack::destroySoundPack() {
  if (unknown2b0 != FILE_IDX_NONE && unknown2b4 > 0) {
    unknown2b4--;
    if (unknown2b4 <= 0 && GfSound::get() != nullptr) {
      GfSound::get()->destroyObjSePack(unknown2a8);
    }
  }
}

bool GfAssetPack::isCached() const {
  if (GfAssetManager::getSlotMapping()->isRequest(this)) {
    return false;
  }
  if (unknown254 != 0) {
    return false;
  }
  return unknown27c > 3;
}

void GfAssetPack::applyPreFileSize() { m_assetType.applyPreFileSize(); }

void GfAssetPack::calcAllFileSize() { unknown240 = m_assetType.calcAllFileSize(); }

s64 GfAssetPack::getAllFileSize() {
  if (unknown240 < 0) {
    calcAllFileSize();
  }
  return unknown240;
}

void GfAssetPack::replaceAssetType(const GfAssetFilesInfo &filesInfo) {
  AssetPackInfo *info = GfAssetManager::getAssetPackInfo(filesInfo.unknown00);
  info->unknown308 = filesInfo.unknown08;
  m_assetType.setInitializeParam(filesInfo);
}

void GfAssetFiles::replaceAssetType(GfAssetType type) {
  if (type != ASSET_TYPE_BASE) {
    unknown00 = type;
  }
}

GfAssetFiles::~GfAssetFiles() {
  for (AssetFile **it = unknown50.begin(); it != unknown50.end(); ++it) {
    if (*it != nullptr) {
      delete *it;
      *it = nullptr;
    }
  }
}

void GfAssetFiles::addResourceWithLockAsset(GfFileIdx index, const char *name) {
  unknown108 = false;
  addResource(index, name);
  unknown108 = true;
}

void GfAssetFiles::destroyFileSizeCache() {
  GfFileSizePool *pool = GfFileSizePool::get();
  if (pool == nullptr) {
    return;
  }
  AssetFile **end = unknown50.end();
  for (AssetFile **it = unknown50.begin(); it != end; ++it) {
    AssetFile *file = *it;
    if (file->unknown94 != -2) {
      pool->recalcFileSizeCache(file->unknown08, file->unknown10.c_str());
      file->unknown94 = -2;
      file->unknown08 = pool->requestFileSize(file->unknown10.c_str());
    }
  }
}

void GfAssetFiles::applyPreFileSize() {
  GfFileSizePool *pool = GfFileSizePool::get();
  if (pool == nullptr) {
    return;
  }
  AssetFile **end = unknown50.end();
  for (AssetFile **it = unknown50.begin(); it != end; ++it) {
    if ((*it)->unknown94 == -2) {
      pool->getFileSize((*it)->unknown94, (*it)->unknown08);
    }
  }
}

bool GfAssetFiles::isPreSizeSizeValid() const {
  for (AssetFile *const *it = unknown50.begin(); it != unknown50.end(); ++it) {
    if ((*it)->unknown94 == -2) {
      return false;
    }
  }
  return !unknown50.empty();
}

s64 GfAssetFiles::calcAllFileSize() const {
  s64 total = 0;
  for (AssetFile *const *it = unknown50.begin(); it != unknown50.end(); ++it) {
    s64 size = (*it)->unknown94;
    if (size > 0) {
      if ((size & 0x1fff) != 0) {
        size = size + 0x2000 - (size & 0x1fff);
      }
      total += size;
    }
  }
  return total;
}

s64 GfAssetFiles::calcFileSize(GfFileIdx index) const {
  for (AssetFile *const *it = unknown50.begin(); it != unknown50.end(); ++it) {
    if ((*it)->unknown00 == index && (*it)->unknown94 > 0) {
      return (*it)->unknown94;
    }
  }
  return 0;
}

void GfAssetPack::dispAssetLogForDebug() {}

void GfAssetPack::setLoadComplete() {}

AssetPackValue GfAssetPack::calcAssetPackValue(const char *name, GfAssetType type) {
  AssetPackValue value;
  value.unknown00 = type;
  value.unknown04 = mm::mtl::hashStrCrc(name);
  return value;
}

} // namespace gf

template mm::mtl::FixedList<gf::GfAssetPack *, 1024>::iterator mm::mtl::FixedList<gf::GfAssetPack *, 1024>::erase(mm::mtl::FixedList<gf::GfAssetPack *, 1024>::iterator);
template class ml::fixed_size_alloc_inside<gf::AssetPackInfo, 1024>;
