#include "gf/field/gf_field_lod.h"

#include "bdat.h"
#include "framework/effect/effect_manager.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_game_flag.h"
#include "gf/field/gf_field_manager.h"
#include "gmk/gmk_bdat.h"
#include "mm_math/mm_mat44.h"
#include "mm_mtl/vector.h" // IWYU pragma: keep
#include "scn/scn_obj_acc.h"

namespace fw {
class EffectPack;
} // namespace fw

namespace gf {

constexpr int unknown002 = 0x9631; // Inferred role: first game flag of the anim reverse states; original name unknown.
constexpr int unknown003 = 0x9230; // Inferred role: first game flag of the fade states; original name unknown.

GfFieldLodEffect::GfFieldLodEffect() : unknown2a(false), unknown2c(0), unknown30(FIELD_LOD_STATE_UNKNOWN_5) {
  for (u32 i = 0; i < sizeof(unknown00) / sizeof(unknown00[0]); i++) {
    unknown00[i] = nullptr;
  }
}

void *GfFieldLodEffect::getAsset(GfFieldLodState state) const {
  if (state >= 0 && state < FIELD_LOD_STATE_UNKNOWN_5) {
    return unknown00[state];
  }
  return nullptr;
}

bool GfFieldLodEffect::isAssetExists() const {
  for (u32 i = 0; i < sizeof(unknown00) / sizeof(unknown00[0]); i++) {
    if (unknown00[i] != nullptr) {
      return true;
    }
  }
  return false;
}

bool GfFieldLodEffect::isAssetLoop(GfFieldLodState state) const {
  void *asset = getAsset(state);
  return asset != nullptr && fw::EffectManager::get()->isLoop(asset);
}

void GfFieldLodEffect::createAsset(int bdatId) {
  // Inferred role: lod list column of the effect of each lod state; original name unknown.
  static const char *const unknown004[] = {"effect_anime_normal", "effect_anime_reverse", "effect_visibleON", "effect_visibleOFF", "effect_fadeOUT"};
  disposeAsset();
  unknown2a = true;
  fw::EffectPack *pack = GfFieldManager::getEffectPack();
  if (pack == nullptr) {
    return;
  }
  u8 *bdat = GfDataBdat::getFP(BDAT_FLD_LODLIST);
  for (u32 i = 0; i < sizeof(unknown00) / sizeof(unknown00[0]); i++) {
    const char *name = reinterpret_cast<const char *>(Bdat::getValCheck(bdat, unknown004[i], bdatId, gmk::BDAT_TYPE_STRING));
    if (name != nullptr && name[0] != '\0') {
      void *asset = fw::EffectManager::get()->search(name, pack);
      if (asset != nullptr) {
        unknown00[i] = asset;
      }
    }
  }
  unknown28 = Bdat::getValCheck(bdat, "effect_skipframe", bdatId, gmk::BDAT_TYPE_U16);
}

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

void GfFieldLodEffect::update(const ml::ScnObjAccPartsPos &partsPos) {
  if (unknown2c != 0 && partsPos.isPosAnm()) {
    mm::Mat44 matrix;
    partsPos.getAnmMatrix(&matrix);
    fw::EffectManager::get()->setMatrix(unknown2c, matrix);
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
