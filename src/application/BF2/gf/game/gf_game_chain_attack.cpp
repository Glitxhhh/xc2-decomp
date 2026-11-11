#include "gf/game/gf_game_chain_attack.h"

#include "gf/game/gf_game_mount.h"
#include "gf/game/gf_game_obj.h"
#include "gf/game/gf_game_party.h"
#include "gf/game/sequential_play/gf_play_factory.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_manager.h"

namespace gf {

constexpr s32 CHAIN_ATTACK_STATE_UNKNOWN_2 = 2; // Inferred role: chain attack state play; original name unknown.

GfChainAttack::GfChainAttack() : m_state(0) {
  unknown10.clear();
  for (u32 index = 3; index > 0; index--) {
    m_driverByPartyId[index - 1] = unknown020;
  }
}

GfChainAttack::~GfChainAttack() {}

bool GfChainAttack::isLoadingDrivers() const {
  for (u32 index = 0; index < 3; index++) {
    if (m_driverByPartyId[index] != unknown020 && !GfGameObj::isValidGameObj(m_driverByPartyId[index], true, nullptr)) {
      return true;
    }
  }
  return false;
}

void GfChainAttack::updateForSetup(const fw::UpdateInfo &) {
  if (GfMenuManager::isOpenBtlModelView() && !isLoadingDrivers()) {
    m_state = CHAIN_ATTACK_STATE_UNKNOWN_2;
    unknown10.bind(this, &GfChainAttack::updateForPlay);
  }
}

void GfChainAttack::updateForPlay(const fw::UpdateInfo &) {}

void GfChainAttack::update(const fw::UpdateInfo &info) {
  if (unknown10.isValid()) {
    unknown10(info);
  }
}

GfChainAttack *GfChainAttack::create() {
  if (!GfPlayFactory::createChainAttack()) {
    return nullptr;
  }
  GfChainAttack *chainAttack = get();
  if (chainAttack == nullptr) {
#line 128
    chainAttack = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfChainAttack();
  }
  return chainAttack;
}

void GfChainAttack::destroy() {
  GfChainAttack *chainAttack = get();
  if (chainAttack != nullptr) {
    chainAttack->finish();
    delete chainAttack;
  }
}

void GfChainAttack::finish() {
  for (u32 index = 0; index < 3; index++) {
    if (m_driverByPartyId[index] != unknown020) {
      GfGameObj::destroyGameObj(m_driverByPartyId[index], 0.0f);
      m_driverByPartyId[index] = unknown020;
    }
  }
  GfMenuManager::closeBtlModelView();
  unknown10.clear();
  m_state = 0;
}

s32 GfChainAttack::getState() const { return m_state; }

GF_OBJ_HANDLE *GfChainAttack::getDriverByPartyId(u32 partyId) const { return m_state == CHAIN_ATTACK_STATE_UNKNOWN_2 ? m_driverByPartyId[partyId] : unknown020; }

GF_OBJ_HANDLE *GfChainAttack::getDriverByGameDriver(GF_OBJ_HANDLE *handle) const {
  u32 partyId = GfGameParty::getPartyId(handle);
  return m_state == CHAIN_ATTACK_STATE_UNKNOWN_2 ? m_driverByPartyId[partyId] : unknown020;
}

GfWeapon *GfChainAttack::getWeaponByPartyId(u32 partyId) const { return GfMountManager::getGfWeapon(getDriverByPartyId(partyId), GFATTACH_UNKNOWN_0); }

GfWeapon *GfChainAttack::getWeaponByGameDriver(GF_OBJ_HANDLE *handle) const { return GfMountManager::getGfWeapon(getDriverByGameDriver(handle), GFATTACH_UNKNOWN_0); }

} // namespace gf
