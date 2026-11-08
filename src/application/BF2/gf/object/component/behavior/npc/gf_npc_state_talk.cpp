#include "gf/object/component/behavior/npc/gf_npc_state_talk.h"

#include "framework/coli/coli_object.h"
#include "gf/field/gf_field_exec_cmd_turn.h"
#include "gf/object/component/behavior/gf_com_behavior_npc.h"
#include "gf/object/component/gf_com_collider.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace gf {
namespace npc {

StateTalk::StateTalk() : unknown18(), unknown50(nullptr), unknown60(false) {}

void StateTalk::leave(GfComBehaviorNpc *behavior, ai::State *next) { setCollideNpcMob(true); }

void StateTalk::update(GfComBehaviorNpc *behavior, const fw::UpdateInfo &info) {
  if (unknown50) {
    (this->*unknown50)(*behavior, info);
  }
}

void StateTalk::setCollideNpcMob(GF_OBJ_HANDLE *handle, bool isCollide) {
  GfObjAcc acc(handle);
  GfObj *obj = acc.getObj();
  if (obj != nullptr) {
    GfComCollider *collider = obj->getComponent<GfComCollider>();
    if (collider != nullptr) {
      for (fw::ColiObject *&coli : collider->unknown18) {
        if (coli != nullptr) {
          u32 flag = coli->getHitMaterialFlag();
          if (isCollide) {
            flag |= 0x40000;
          } else {
            flag &= ~0x40000;
          }
          coli->setHitMaterialFlag(flag);
        }
      }
    }
  }
}

void StateTalk::seqWaitTurnEnd(GfComBehaviorNpc &behavior, const fw::UpdateInfo &info) {
  if (behavior.unknown2e0.unknown6c) {
    reqState(STATE_ID_UNKNOWN_0);
  }
}

} // namespace npc
} // namespace gf
