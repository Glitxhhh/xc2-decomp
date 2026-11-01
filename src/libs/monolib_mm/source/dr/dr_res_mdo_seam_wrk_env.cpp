#include "dr/dr_res_mdo_seam_wrk_env.h"

#include "dr/dr_man.h"
#include "mtl/mem_manager.h"

namespace ml {

DrResMdoSeamWrkEnv::~DrResMdoSeamWrkEnv() { release(); }

void DrResMdoSeamWrkEnv::release() {
  if (unknown58 != nullptr) {
    mtl::MemManager::deallocate(unknown58, 0, false);
    unknown58 = nullptr;
  }
  if (unknown38[0] != nullptr) {
    mtl::MemManager::deallocate(unknown38[0], 0, false);
    unknown38[0] = nullptr;
  }
  if (unknown38[1] != nullptr) {
    mtl::MemManager::deallocate(unknown38[1], 0, false);
    unknown38[1] = nullptr;
  }
  if (unknown28 != nullptr) {
    mtl::MemManager::deallocate(unknown28, 0, false);
    unknown28 = nullptr;
  }
  unknown48[0] = 0;
  unknown48[1] = 0;
  unknown6c = 0;
  unknown60 = nullptr;
}

void DrResMdoSeamWrkEnv::setDispState() { unknown6c |= 1 << DrMan::s_nDblNowIdx; }

u32 DrResMdoSeamWrkEnv::chkDispState() { return unknown6c & (1 << DrMan::s_nDblNowIdx); }

u8 *DrResMdoSeamWrkEnv::getDisplayWrk() { return unknown38[DrMan::s_nDblNowIdx]; }

int DrResMdoSeamWrkEnv::getDisplayWrkSize() { return unknown48[DrMan::s_nDblNowIdx]; }

void DrResMdoSeamWrkEnv::setDisplayWrk(u8 *work, int size) {
  int index = DrMan::s_nDblNowIdx;
  unknown38[index] = work;
  unknown48[index] = size;
}

void DrResMdoSeamWrkEnv::changeMemCall(const MdsSeamEnvMapHead *head) {
  unknown18 = head;
  unknown6c &= ~3u;
}

void DrResMdoSeamWrkEnv::setInfo(const mm::Vec3 &position, const mm::Vec3 &scale, bool isEnable, u32 flags) {
  unknown68 = flags;
  unknown74 = isEnable;
  unknown80 = position;
  unknown90 = scale;
}

} // namespace ml
