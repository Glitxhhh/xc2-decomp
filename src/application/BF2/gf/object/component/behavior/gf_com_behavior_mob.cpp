#include "gf/object/component/behavior/gf_com_behavior_mob.h"

#include "ai/ai_state.h"
#include "framework/coli/coli_object.h"
#include "framework/navi/navi_manager.h"
#include "framework/object/updatable_object.h"
#include "gf/object/component/gf_com_collider.h"
#include "gf/object/gf_obj.h"
#include "gmk/gmk_manager.h"
#include "mm_mtl/rtti.h"
#include "mm_mtl/vector.h"

namespace gf {

void GfComBehaviorMob::procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message) {}

void GfComBehaviorMob::procMsgObjectGetVelocity(fw::MessageObject *sender, MsgObjectGetVelocity &message) { message.unknown10 = unknown100; }

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

void GfComBehaviorMob::Listener::onWkStandbyLogout() { unknown08->unknown53b8 = nullptr; }

} // namespace gf
