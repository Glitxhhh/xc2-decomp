#include "gf/object/component/behavior/gf_com_behavior_npc.h"

#include "ai/ai_state.h"
#include "bdat.h"
#include "framework/coli/coli_object.h"
#include "framework/navi/navi_manager.h"
#include "framework/object/updatable_object.h"
#include "framework/reference_frame.h"
#include "fw/fw_transform.h"
#include "gf/asset/gf_asset_def.h"
#include "gf/asset/gf_asset_manager.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_game_flag.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/gf_com_collider.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_util.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_blade.h"
#include "gmk/gmk_manager.h"
#include "mm_mtl/rtti.h"
#include "mm_mtl/vector.h"

namespace gf {

constexpr int unknown001 = 0xa396; // Inferred role: first game flag of the talk bonus states; original name unknown.

void GfComBehaviorNpc::BdatInfo::create(const CBdatWrapper &bdat, int id, const GfComBehaviorNpc &npc) {
  unknown00 = bdat.getValCheck("ShopID", id, gmk::BDAT_TYPE_U16);
  u16 closeRange = bdat.getValCheck("CloseRange", id, gmk::BDAT_TYPE_U16);
  unknown04 = static_cast<f32>(closeRange * closeRange);
  unknown08 = static_cast<f32>(static_cast<u16>(bdat.getValCheck("MoveSpeed", id, gmk::BDAT_TYPE_U16)));
  u16 reactionRange = bdat.getValCheck("ReactionRange", id, gmk::BDAT_TYPE_U16);
  unknown0c = static_cast<f32>(reactionRange * reactionRange);
  unknown10 = bdat.getValCheck("ReactionPercent", id, gmk::BDAT_TYPE_U16);
  unknown12 = bdat.getValCheck("ReactionMot", id, gmk::BDAT_TYPE_U16);
  unknown14 = bdat.getValCheck("BattleReaction", id, gmk::BDAT_TYPE_U16);
  unknown16 = bdat.getValCheck("BattleMot", id, gmk::BDAT_TYPE_U16);

  gmk::AGmkBase *gmk = npc.getBindedGmkInst();
  switch (gmk->getGmkType()) {
  case gmk::GMK_TYPE_NPC:
  case gmk::GMK_TYPE_ROUTED_NPC:
    unknown18 = bdat.getValCheck("EventID", id, gmk::BDAT_TYPE_U16);
    break;
  case gmk::GMK_TYPE_BLADE:
    if (static_cast<gmk::GmkBlade *>(gmk)->unknown50 != 0) {
      unknown18 = GfDataBlade::getNormalTalk(static_cast<gmk::GmkBlade *>(gmk)->unknown50);
    }
    break;
  default:
    break;
  }

  if (unknown18 != 0) {
    u8 *talk = GfDataBdat::getFP(BDAT_EVT_LIST_TLK01);
    if (Bdat::getIdTop(talk) <= unknown18 && unknown18 < Bdat::getIdTop(talk) + Bdat::getIdCount(talk) && unknown00 == 0) {
      unknown1a = true;
    }
  }
}

int GfComBehaviorNpc::BdatInfo::getTalkBonusFlagId() const {
  u8 *talk = GfDataBdat::getFP(BDAT_EVT_LIST_TLK01);
  u16 event = unknown18;
  return event + unknown001 - Bdat::getIdTop(talk);
}

bool GfComBehaviorNpc::BdatInfo::isIconTalkBonus() const {
  if (!unknown1a) {
    return false;
  }
  return GfGameFlag::getLocal(1, getTalkBonusFlagId()) == 0;
}

void GfComBehaviorNpc::BdatInfo::setTalkBonusFlag() const { GfGameFlag::setLocal(1, getTalkBonusFlagId(), 1); }

f32 GfComBehaviorNpc::BdatInfo::getDistYThreshold() { return 2.0f; }

void GfComBehaviorNpc::procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message) {}

void GfComBehaviorNpc::procMsgPcGetLookPoint(fw::MessageObject *sender, MsgPcGetLookPoint &message) {
  if (unknown1b8.get() != nullptr) {
    message.unknown10 = unknown1b8->getSyncedWorldTransform().unknown00;
    message.unknown20 = true;
  }
}

void GfComBehaviorNpc::procMsgObjectGetVelocity(fw::MessageObject *sender, MsgObjectGetVelocity &message) { message.unknown10 = unknownf0; }

void GfComBehaviorNpc::disposeNaviMeshObj() {
  fw::NaviManager::get()->releaseObject(unknownb8);
  unknownb8 = nullptr;
}

gmk::AGmkBase *GfComBehaviorNpc::getBindedGmkInst() const { return gmk::getBindedGmkInst(static_cast<GfObj *>(unknown08)->unknownf8); }

void GfComBehaviorNpc::setGoalPos(const mm::Vec3 &position) { unknownc0 = position; }

GfComAsm *GfComBehaviorNpc::getComAsm() const { return unknown08->getComponent<GfComAsm>(); }

bool GfComBehaviorNpc::isNullNpc() const { return !GfAssetManager::isExist(GfObjUtil::getAssetHandle(static_cast<GfObj *>(unknown08)->unknownf8), static_cast<GfFileIdx>(6)); }

fw::ColiMoveObject *GfComBehaviorNpc::getColiObject() const {
  GfComCollider *collider = unknown08->getComponent<GfComCollider>();
  if (collider != nullptr) {
    fw::ColiObject *coli = collider->unknown18[0];
    if (coli != nullptr) {
      return mm::mtl::dynamicCast<fw::ColiMoveObject>(coli);
    }
  }

  return nullptr;
}

void GfComBehaviorNpc::disposeFsm() {
  if (!unknown190) {
    unknown190 = true;
    unknown108.cleanup();
  }
}

u32 GfComBehaviorNpc::getStateId() const {
  if (unknown108.m_pState != nullptr) {
    return unknown108.m_pState->unknown08;
  }

  return ai::INVALID_STATE_ID;
}

void GfComBehaviorNpc::setActivateCollison(bool isActivate) {
  fw::ColiMoveObject *coli = getColiObject();
  if (coli != nullptr) {
    coli->setActivate(isActivate);
  }
}

void GfComBehaviorNpc::Listener::onWkStandbyLogout() { unknown08->unknown198 = nullptr; }

} // namespace gf
