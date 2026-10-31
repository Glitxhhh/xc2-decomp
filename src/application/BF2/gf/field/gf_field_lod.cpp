#include "gf/field/gf_field_lod.h"

#include "bdat.h"
#include "framework/effect/effect_manager.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_game_flag.h"
#include "mm_mtl/vector.h" // IWYU pragma: keep

namespace gf {

constexpr int unknown002 = 0x9631; // Inferred role: first game flag of the anim reverse states; original name unknown.
constexpr int unknown003 = 0x9230; // Inferred role: first game flag of the fade states; original name unknown.

void GfFieldLodEffect::disposeAsset() {
  disposeInst(false);
  unknown2a = false;
  for (u32 i = 0; i < sizeof(unknown00) / sizeof(unknown00[0]); i++) {
    unknown00[i] = nullptr;
  }
}

void GfFieldLodEffect::disposeInst(bool isDead) {
  if (unknown2c != 0) {
    if (isDead) {
      fw::EffectManager::get()->dead(unknown2c);
    } else {
      fw::EffectManager::get()->remove(unknown2c);
    }
    unknown2c = 0;
  }
}

int GfFieldLod::findBdatIdByLodId(u16 lodId) const {
  for (u64 i = 0; i < 0x400; i++) {
    if (unknown08[i] == lodId) {
      return unknown808 + static_cast<int>(i);
    }
  }
  return unknown808 - 1;
}

bool GfFieldLod::isAnimReverse(int bdatId) const { return GfGameFlag::getLocal(1, bdatId + unknown002 - unknown808) != 0; }

bool GfFieldLod::isFadeOut(int bdatId) const {
  int top = unknown808;
  return GfGameFlag::getLocal(1, bdatId + unknown003 - top) == 0;
}

bool GfFieldLod::isAnimReverseOfInit(int bdatId) { return Bdat::getFlagVal(GfDataBdat::getFP(BDAT_FLD_LODLIST), "flag", bdatId, "AnimReverse") != 0; }

bool GfFieldLod::isVisibleOfInit(int bdatId) { return Bdat::getFlagVal(GfDataBdat::getFP(BDAT_FLD_LODLIST), "flag", bdatId, "Visible") != 0; }

const mm::mtl::RTTI *GfFieldLodColiAnim::ColiUserData::getRTTI() const { return &m_rtti; }

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfFieldLod>::~PtrSingleton();
template void mm::mtl::Vector<gf::GfFieldLodColiAnim::PosInfo>::push_back(const gf::GfFieldLodColiAnim::PosInfo &);
template void mm::mtl::Vector<gf::GfFieldLodColiAnim::PosInfo>::expand(size_t, size_t);
