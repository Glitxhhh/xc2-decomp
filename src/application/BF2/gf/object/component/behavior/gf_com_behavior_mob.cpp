#include "gf/object/component/behavior/gf_com_behavior_mob.h"

#include "ai/ai_state.h"
#include "framework/coli/coli_object.h"
#include "framework/navi/navi_manager.h"
#include "framework/object/updatable_object.h"
#include "framework/reference_frame.h"
#include "fw/fw_transform.h"
#include "gf/object/component/behavior/mob/gf_mob_state_idle.h"
#include "gf/object/component/behavior/mob/gf_mob_state_move.h"
#include "gf/object/component/behavior/mob/gf_mob_state_squad_member.h"
#include "gf/object/component/behavior/npc/gf_npc_state_area_move.h"
#include "gf/object/component/behavior/npc/gf_npc_state_battle.h"
#include "gf/object/component/behavior/npc/gf_npc_state_reaction.h"
#include "gf/object/component/behavior/plugin/gf_plugin_manager.h"
#include "gf/object/component/gf_com_collider.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_setup.h"
#include "gmk/gmk_manager.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/rtti.h"
#include "mm_mtl/vector.h"
#include "navi/nvmsh_ac_obj.h"

namespace gf {

void GfComBehaviorMob::procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message) {}

void GfComBehaviorMob::procMsgObjectGetVelocity(fw::MessageObject *sender, MsgObjectGetVelocity &message) { message.unknown10 = unknown100; }

void GfComBehaviorMob::cleanup() {
  unknownb8 = nullptr;
  disposeNaviMeshObj();
  disposeFsm();
  unknown10.cleanup();
}

const mm::Vec3 &GfComBehaviorMob::getPos() const { return unknown08->getComponent<GfComTransform>()->unknown001()->getSyncedWorldTransform().unknown00; }

const mm::Quat &GfComBehaviorMob::getRot() const { return unknown08->getComponent<GfComTransform>()->unknown001()->getSyncedWorldTransform().unknown10; }

fw::ColiMoveObject *GfComBehaviorMob::getColiObject() const {
  GfComCollider *collider = unknown08->getComponent<GfComCollider>();
  if (collider != nullptr) {
    fw::ColiObject *coli = collider->unknown18[0];
    if (coli != nullptr) {
      return mm::mtl::dynamicCast<fw::ColiMoveObject>(coli);
    }
  }

  return nullptr;
}

gmk::AGmkBase *GfComBehaviorMob::getBindedGmkInst() const { return gmk::getBindedGmkInst(static_cast<GfObj *>(unknown08)->unknownf8); }

bool GfComBehaviorMob::isSquadMember() const { return unknownc0.unknown001() && unknownc0.unknown28 != 0; }

void GfComBehaviorMob::initMoveSpeed(f32 time) {
  GfObjSetupMob *setup = mm::mtl::dynamicCast<GfObjSetupMob>(GfObjManager::getObjInfo(static_cast<GfObj *>(unknown08)->unknownf8)->unknown30);
  f32 rate = setup->unknown90 * 0.01f;
  unknown1e0.setSpeedKmph(unknown1e0.unknown08 * rate, time);
}

void GfComBehaviorMob::setStateId(mob::STATE_ID stateId) {
  if (getStateId() != stateId) {
    unknown5328.setState(stateId);
  }
}

void GfComBehaviorMob::disposeNaviMeshObj() {
  fw::NaviManager::get()->releaseObject(unknowna8);
  unknowna8 = nullptr;
}

void GfComBehaviorMob::disposeFsm() {
  if (!unknown53b0) {
    unknown53b0 = true;
    unknown5328.cleanup();
  }
}

void GfComBehaviorMob::disposeSquadNavi() { unknownc0.dispose(); }

void GfComBehaviorMob::setActivateCollison(bool isActivate) {
  fw::ColiMoveObject *coli = getColiObject();
  if (coli != nullptr) {
    coli->setActivate(isActivate);
  }
}

u32 GfComBehaviorMob::getStateId() const {
  if (unknown5328.m_pState != nullptr) {
    return unknown5328.m_pState->unknown08;
  }

  return ai::INVALID_STATE_ID;
}

void GfComBehaviorMob::createNaviMeshObj() {
  disposeNaviMeshObj();
  unknowna8 = fw::NaviManager::get()->createObject();
  if (unknowna8 != nullptr) {
    unknowna8->setMeshNum(0);
    unknowna8->unknown10 |= 2;
  }
  unknownb0 = 0;
}

void GfComBehaviorMob::createFsm() {
  disposeFsm();
  unknown5328.beginSetup(this, 6, 1);
  unknown5328.registerState<mob::StateIdle>(mob::STATE_ID_UNKNOWN_0, -1);
  unknown5328.registerState<mob::StateMove>(mob::STATE_ID_UNKNOWN_1, -1);
  unknown5328.registerState<npc::StateAreaMove<GfComBehaviorMob>>(mob::STATE_ID_UNKNOWN_2, -1);
  unknown5328.registerState<mob::StateSquadMember>(mob::STATE_ID_UNKNOWN_3, -1);
  unknown5328.registerState<npc::StateReaction<GfComBehaviorMob>>(mob::STATE_ID_UNKNOWN_4, -1);
  unknown5328.registerState<npc::StateBattle<GfComBehaviorMob>>(mob::STATE_ID_UNKNOWN_5, -1);
  unknown5328.endSetup();
  unknown53b0 = false;
}

void GfComBehaviorMob::Listener::onWkStandbyLogout() { unknown08->unknown53b8 = nullptr; }

} // namespace gf
