#include "ml/dev_file_th.h"

#include "device/nx/dev_file_nx_th.h"
#include "ml/dev_file_accessor.h"
#include "ml/dev_file_job_th.h"
#include "ml/file_handle_th.h"
#include "ml/lib_main.h"
#include "ml/reslist.h"
#include "ml/work_obj.h"
#include "ml/work_root.h"
#include "ml/work_system.h"
#include "mm_mtl/algorithm.h"
#include "mm_mtl/construct.h"
#include "mm_mtl/fixstr.h"
#include "mtl/mem_manager.h"
#include "nn/fs.h"

namespace ml {

namespace dvfl_detail {

mm::mtl::FixedVector<LoadMediaParam, 8> g_loadMedia;
mm::mtl::FixedVector<IDevFileEvent *, 8> g_FileEventListener;

void clearLoadMedia() { g_loadMedia.clear(); }

} // namespace dvfl_detail

DevFileTh::~DevFileTh() {}

namespace {

// Inferred role: replaces the backslashes of a path by slashes; original name unknown.
template <int LEN> void unknown108(mm::mtl::FixStr<LEN> &path) {
  for (int i = 0; i < path.length(); i++) {
    if (path[i] == '\\') {
      path[i] = '/';
    }
  }
}

} // namespace

void DevFileTh::makeMediaFileName(mm::mtl::FixStr<256> &fileName, const char *directory, const char *path) {
  if (getMediaType(path) != MEDIA_UNKNOWN_0) {
    fileName = path;
    return;
  }
  fileName = directory;
  if (fileName.length() != 0) {
    unknown108(fileName);
    if (fileName[fileName.length() - 1] == '/') {
      fileName.resize(fileName.length() - 1);
    }
  }
  if (path[0] == '\\' || path[0] == '/') {
    fileName += path;
  } else {
    fileName += "/";
    fileName += path;
  }
  unknown108(fileName);
}

void DevFileTh::flushSave() {
  if (DevFileNxTh::m_mountSave) {
    nn::fs::CommitSaveData("save");
  }
}

FileHandleTh *DevFileTh::checkValidFile(const char *path, IWorkEvent *event) {
  DevFileTh *file = get();
  if (file == nullptr) {
    return nullptr;
  }
  return file->unknown1c0->checkValidFile(path, event);
}

bool DevFileTh::writeFileBlock(const char *path, const void *data, u32 size, int priority) {
  DevFileTh *file = get();
  if (file == nullptr) {
    return false;
  }
  return file->unknown1c0->writeFileBlock(path, data, size, priority);
}

FileHandleTh *DevFileTh::readFile(const DevFileParamTh &param) {
  DevFileTh *file = get();
  if (file == nullptr) {
    return nullptr;
  }
  return file->unknown1c0->readFile(param);
}

FileHandleTh *DevFileTh::rfOpen(const DevFileParamTh &param) {
  DevFileTh *file = get();
  if (file == nullptr) {
    return nullptr;
  }
  return file->unknown1c0->rfOpen(param);
}

FileHandleTh *DevFileTh::writeFile(const char *path, IWorkEvent *event, const void *data, int size, int priority) {
  DevFileTh *file = get();
  if (file == nullptr) {
    return nullptr;
  }
  return file->unknown1c0->writeFile(path, event, data, size, priority);
}

void DevFileTh::rfCancel(FileHandleTh *handle) {
  DevFileTh *file = get();
  if (file != nullptr) {
    file->unknown1c0->rfCancel(handle);
  }
}

bool DevFileTh::rfRead(FileHandleTh *handle, const DevFileParamTh &param) {
  DevFileTh *file = get();
  if (file == nullptr) {
    return false;
  }
  return file->unknown1c0->rfRead(handle, param);
}

bool DevFileTh::rfIsBusy(FileHandleTh *handle) {
  DevFileTh *file = get();
  if (file == nullptr) {
    return false;
  }
  return file->unknown1c0->rfIsBusy(handle);
}

bool DevFileTh::isBusy() {
  DevFileTh *file = get();
  if (file == nullptr) {
    return false;
  }
  return file->unknown1c0->isBusy();
}

bool DevFileTh::getFilesBlock(char *&files, int &num, mtl::ALLOC_HANDLE handle, const char *path, const char *extension) {
  DevFileTh *file = get();
  if (file == nullptr) {
    return false;
  }
  return file->unknown1c0->getFilesBlock(files, num, handle, path, extension);
}

bool DevFileTh::deleteFileBlock(const char *path) {
  DevFileTh *file = get();
  if (file == nullptr) {
    return false;
  }
  return file->unknown1c0->deleteFileBlock(path);
}

bool DevFileTh::rfClose(FileHandleTh *handle) {
  DevFileTh *file = get();
  if (file != nullptr) {
    file->unknown1c0->rfClose(handle);
  }
  return false;
}

bool DevFileTh::rfIsBusy() {
  DevFileTh *file = get();
  if (file == nullptr) {
    return false;
  }
  return file->unknown1c0->rfIsBusy();
}

void DevFileTh::cancel(FileHandleTh *handle, bool isForce) {
  DevFileTh *file = get();
  if (file != nullptr) {
    file->unknown1c0->cancelRequest(handle);
  }
}

bool DevFileTh::isValidHandle(FileHandleTh *handle) {
  DevFileTh *file = get();
  if (file != nullptr) {
    file->unknown1c0->isValidHandle(handle);
  }
  return false;
}

bool DevFileTh::isLoading(FileHandleTh *handle) {
  DevFileTh *file = get();
  if (file == nullptr) {
    return false;
  }
  return file->unknown1c0->isLoading(handle);
}

void DevFileTh::Impl::registAccessor(MEDIA media, DevFileAccessor *accessor) { unknown588b0[media] = accessor; }

void DevFileTh::Impl::removeAccessor(MEDIA media) { unknown588b0[media] = nullptr; }

void DevFileTh::Impl::registArchiveAccessor(MEDIA media, DevFileAccessor *accessor) { unknown588f0[media] = accessor; }

void DevFileTh::Impl::removeArchiveAccessor(MEDIA media) { unknown588f0[media] = nullptr; }

void DevFileTh::Impl::suspendThread() {}

bool DevFileTh::Impl::isSuspendThread() { return false; }

void DevFileTh::Impl::resumeThread() {}

void DevFileTh::Impl::setSuspend(bool suspend) {}

bool DevFileTh::Impl::isSuspend() const { return false; }

bool DevFileTh::Impl::isInitialized() { return m_initialized; }

namespace {

typedef mm::mtl::FixedList<DevFileJobTh *, 640> unknown003;

// Inferred role: tells whether a job list holds a job of the file handle; original name unknown.
bool unknown004(unknown003 &list, FileHandleTh *handle) {
  for (unknown003::iterator it = list.begin(); it != list.end(); ++it) {
    if ((*it)->unknown10 == handle) {
      return true;
    }
  }
  return false;
}

} // namespace

bool DevFileTh::Impl::isValidHandle(FileHandleTh *handle) {
  CS cs(unknown5a350);
  if (handle != nullptr) {
    if (unknown004(unknown00000, handle) || unknown004(unknown02d20, handle) || unknown004(unknown05a40, handle)) {
      return true;
    }
  }
  return false;
}

void DevFileTh::Impl::cancelRequest(FileHandleTh *handle) {
  CS cs(unknown5a350);
  if (handle != nullptr) {
    bool found = false;
    for (unknown003::iterator it = unknown00000.begin(); it != unknown00000.end(); ++it) {
      if ((*it)->unknown10 == handle) {
        (*it)->unknown18 = true;
        found = true;
        break;
      }
    }
    if (!found) {
      for (unknown003::iterator it = unknown02d20.begin(); it != unknown02d20.end(); ++it) {
        if ((*it)->unknown10 == handle) {
          (*it)->unknown18 = true;
          found = true;
          break;
        }
      }
    }
    if (!found) {
      for (unknown003::iterator it = unknown05a40.begin(); it != unknown05a40.end(); ++it) {
        if ((*it)->unknown10 == handle) {
          (*it)->unknown18 = true;
          break;
        }
      }
    }
    handle->unknown94 |= 0x10000;
  }
}

int DevFileTh::Impl::getFileSize(const char *path, mm::VAL64 *size, const dvfl_detail::LoadMediaParam &param) {
  DevFileAccessor *accessor = unknown588b0[param.unknown00];
  if (accessor != nullptr && accessor->isValid()) {
    return accessor->getFileSize(path, size, param.unknown08.c_str());
  }
  return -1;
}

int DevFileTh::Impl::getArchiveFileSize(const char *path, mm::VAL64 *size, const dvfl_detail::LoadMediaParam &param) {
  DevFileAccessor *accessor = unknown588f0[param.unknown00];
  if (accessor != nullptr) {
    return accessor->getFileSize(path, size, param.unknown08.c_str());
  }
  return -1;
}

void DevFileTh::Impl::rfCancel(FileHandleTh *handle) {
  if (handle != nullptr) {
    CS cs(unknown5a378);
    if ((handle->unknown94 >> 5 & 1) && handle->unknown1d4 != INVALID_FILE_CHANNEL) {
      handle->unknown94 |= 0x10000;
    }
  }
}

bool DevFileTh::Impl::rfIsBusy() {
  CS cs(unknown5a378);
  DevFileAccessor *accessor = unknown588f0[0];
  if (accessor == nullptr) {
    accessor = unknown588b0[0];
  }
  if (accessor != nullptr && accessor->rfIsBusy(nullptr)) {
    return true;
  }
  for (int i = 1; i < 8; i++) {
    accessor = unknown588b0[i];
    if (accessor != nullptr && accessor->rfIsBusy(nullptr)) {
      return true;
    }
  }
  return false;
}

bool DevFileTh::Impl::rfClose(FileHandleTh *handle) {
  CS cs(unknown5a378);
  DevFileAccessor *accessor = unknown005(getMediaType(handle->unknown98.c_str()));
  if (accessor != nullptr) {
    accessor->rfClose(handle);
    mm::mtl::destruct(handle);
  }
  return false;
}

bool DevFileTh::Impl::rfRead(FileHandleTh *handle, const DevFileParamTh &param) {
  CS cs(unknown5a378);
  s32 channel = handle->unknown1d4;
  MEDIA media = getMediaType(handle->unknown98.c_str());
  if (channel != INVALID_FILE_CHANNEL) {
    DevFileAccessor *accessor = unknown005(media);
    if (accessor != nullptr && handle->unknown1f4) {
      return accessor->rfRead(handle, param);
    }
  }
  return false;
}

bool DevFileTh::Impl::rfIsBusy(FileHandleTh *handle) {
  bool isBusy = false;
  if (handle != nullptr) {
    CS cs(unknown5a378);
    s32 channel = handle->unknown1d4;
    MEDIA media = getMediaType(handle->unknown98.c_str());
    if (channel != INVALID_FILE_CHANNEL) {
      DevFileAccessor *accessor = unknown005(media);
      if (accessor != nullptr) {
        isBusy = accessor->rfIsBusy(handle);
      }
    }
  }
  return isBusy;
}

bool DevFileTh::Impl::getFilesBlock(char *&files, int &num, mtl::ALLOC_HANDLE handle, const char *path, const char *extension) {
  DevFileAccessor *accessor = unknown588b0[getMediaType(path)];
  if (accessor != nullptr && accessor->isValid()) {
    return accessor->getFilesBlock(files, num, handle, path, extension);
  }
  return false;
}

bool DevFileTh::Impl::deleteFileBlock(const char *path) {
  DevFileAccessor *accessor = unknown588b0[getMediaType(path)];
  if (accessor != nullptr && accessor->isValid()) {
    return accessor->deleteFileBlock(path);
  }
  return false;
}

bool DevFileTh::Impl::isBusy() {
  CS cs(unknown5a350);
  return unknown00000.size() != 0 || unknown02d20.size() != 0;
}

bool DevFileTh::Impl::isLoading(FileHandleTh *handle) {
  CS cs(unknown5a350);
  for (mm::mtl::FixedList<DevFileJobTh *, 640>::iterator it = unknown02d20.begin(); it != unknown02d20.end(); ++it) {
    if ((*it)->unknown10 == handle) {
      return true;
    }
  }
  return false;
}

bool DevFileTh::isSuspend() {
  DevFileTh *file = get();
  if (file != nullptr) {
    file->unknown1c0->isSuspend();
  }
  return false;
}

bool DevFileTh::setSuspend(bool suspend) {
  DevFileTh *file = get();
  if (file == nullptr) {
    return false;
  }
  file->unknown1c0->setSuspend(suspend);
  return true;
}

void DevFileTh::registAccessor(MEDIA media, DevFileAccessor *accessor) {
  DevFileTh *file = get();
  if (file != nullptr) {
    file->unknown1c0->registAccessor(media, accessor);
  }
}

void DevFileTh::removeAccessor(MEDIA media) {
  DevFileTh *file = get();
  if (file != nullptr) {
    file->unknown1c0->removeAccessor(media);
  }
}

void DevFileTh::registArchiveAccessor(MEDIA media, DevFileAccessor *accessor) {
  DevFileTh *file = get();
  if (file != nullptr) {
    file->unknown1c0->registArchiveAccessor(media, accessor);
  }
}

void DevFileTh::removeArchiveAccessor(MEDIA media) {
  DevFileTh *file = get();
  if (file != nullptr) {
    file->unknown1c0->removeArchiveAccessor(media);
  }
}

bool DevFileTh::initialize() {
  DevFileTh *file = get();
  if (file == nullptr) {
    return false;
  }
  return file->unknown1c0->initialize();
}

bool DevFileTh::finalize() {
  DevFileTh *file = get();
  if (file == nullptr) {
    return true;
  }
  return file->unknown1c0->finalize();
}

bool DevFileTh::wkStandbyLogout() {
  if (unknown60.size() != 0 || WorkSystem::get() != nullptr || LibMain::get() != nullptr) {
    return false;
  }
  if (!finalize()) {
    return false;
  }
  return WorkObj::wkStandbyLogout();
}

void DevFileTh::initializeEnv(const char *path) {
  char buffer[1024] = {};
  initializePath(buffer, false);
}

void DevFileTh::addMediaPath(MEDIA media, const char *path, int priority) {
  if (path != nullptr && path[0] != '\0') {
    dvfl_detail::addMediaPath(media, path, priority);
  }
}

bool DevFileTh::removeFileJob(DevFileJob *job) { return true; }

bool DevFileTh::getReadingInfo(mm::mtl::FixStr<256> &name, f32 &ratio) {
  DevFileTh *file = get();
  if (file != nullptr) {
    file->unknown1c0->getReadingInfo(name, ratio);
  }
  return false;
}

bool DevFileTh::getWritingInfo(mm::mtl::FixStr<256> &name, f32 &ratio) {
  DevFileTh *file = get();
  if (file != nullptr) {
    file->unknown1c0->getWritingInfo(name, ratio);
  }
  return false;
}

void DevFileTh::enableLapTimeForDebug(bool enable) {
  DevFileTh *file = get();
  if (file != nullptr) {
    file->unknown1c0->enableLapTimeForDebug(enable);
  }
}

bool DevFileTh::isLapTimeForDebug() {
  DevFileTh *file = get();
  if (file != nullptr) {
    file->unknown1c0->isLapTimeForDebug();
  }
  return false;
}

bool DevFileTh::entryCb(IWorkEvent *event) {
  DevFileTh *file = get();
  if (file == nullptr) {
    return false;
  }
  file->unknown1c0->unknown5a348 = event;
  return true;
}

bool DevFileTh::removeCb(IWorkEvent *event) {
  DevFileTh *file = get();
  if (file == nullptr) {
    return false;
  }
  file->unknown1c0->unknown5a348 = nullptr;
  return true;
}

void DevFileTh::addEventListener(IDevFileEvent *listener) { dvfl_detail::g_FileEventListener.push_back(listener); }

void DevFileTh::removeEventListener(IDevFileEvent *listener) {
  IDevFileEvent **it = mm::mtl::find(dvfl_detail::g_FileEventListener.begin(), dvfl_detail::g_FileEventListener.end(), listener);
  if (it != dvfl_detail::g_FileEventListener.end()) {
    dvfl_detail::g_FileEventListener.erase(it);
  }
}

bool DevFileTh::isNowSaving() {
  DevFileTh *file = get();
  if (file != nullptr) {
    return file->unknown1c9;
  }
  return false;
}

void DevFileTh::setNowSaving(bool isSaving) {
  DevFileTh *file = get();
  if (file != nullptr) {
    file->unknown1c9 = isSaving;
  }
}

bool DevFileTh::checkValidFileBlock(const char *path) { return getFileSize(path, nullptr) >= 0; }

void DevFileTh::sendCommand(const char *command, const char *argument) {}

void DevFileTh::wkUpdate() {}

bool DevFileTh::icbError(CERR_STRUCT *error) { return true; }

void DevFileTh::icbDecide(CERR_STRUCT *error, ERR_DECIDE decide) {}

bool DevFileReaderTh::asyncUpdate() {
  void *buffer = mtl::MemManager::allocate(WorkRoot::getMemTMP(), 0x80000, 0x1000, false, "no name", 0);
  bool isRead = false;
  for (unknown001 *it = unknown20.begin(); it != unknown20.end(); ++it) {
    unknown10->m_currentPtr = 0;
    if (it->unknown10->readBlockSlice(unknown10, it->unknown08, buffer, 0x80000)) {
      isRead = true;
      break;
    }
    if (unknown18) {
      break;
    }
  }
  if (buffer != nullptr) {
    mtl::MemManager::deallocate(buffer, 0, false);
  }
  if (unknown18) {
    unknown10->unknown94 |= 0x10000;
    unknown10->unknown1e8 = 4;
    return false;
  }
  if (isRead) {
    unknown10->unknown94 |= 0x40000;
    unknown10->unknown1e8 = 2;
    unknown08 = 2;
    return true;
  }
  unknown10->unknown94 |= 0x20000;
  unknown10->unknown1e8 = 4;
  unknown08 = -1;
  return false;
}

} // namespace ml

template mm::mtl::PtrSingleton<ml::DevFileTh>::~PtrSingleton();

template void mm::mtl::UniquePtr<ml::DevFileTh::Impl>::_safe_bool_helper::safe_bool_function() const;

template mm::mtl::FixedVector<ml::IDevFileEvent *, 8>::~FixedVector();

template mm::mtl::FixedVector<ml::dvfl_detail::LoadMediaParam, 8>::~FixedVector();

template ml::dvfl_detail::LoadMediaParam *mm::mtl::FixedVector<ml::dvfl_detail::LoadMediaParam, 8>::insert(ml::dvfl_detail::LoadMediaParam *it, const ml::dvfl_detail::LoadMediaParam &value);

template mm::mtl::FixedVector<ml::dvfl_detail::ReserveArchiveParam, 8>::~FixedVector();
