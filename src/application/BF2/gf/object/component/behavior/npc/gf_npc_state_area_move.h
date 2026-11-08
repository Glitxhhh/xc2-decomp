#pragma once
#include <new> // IWYU pragma: keep

#include "ai/ai_state.h"
#include "gf/field/gf_field_exec_cmd.h"
#include "gf/object/component/behavior/gf_com_behavior_npc.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_manager.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

class GfComAsm;

namespace npc {

template <typename T> class StateAreaMove : public ai::State {
public:
  StateAreaMove() : unknown18(), unknown50(nullptr), unknown60(0.0f), unknown64(0.0f) {}
  static ai::State *create(void *buffer) { return new (buffer) StateAreaMove; }
  const char *getName() const override { return "StateAreaMove"; }
  void onEnter(void *owner, ai::State *previous) override;
  void onLeave(void *owner, ai::State *next) override;
  void onStep(void *owner, const void *param) override;
  void seqInitGoalPos(T &behavior, const fw::UpdateInfo &info);
  void seqWaitTurnEnd(T &behavior, const fw::UpdateInfo &info);
  void seqMoveToGoal(T &behavior, const fw::UpdateInfo &info);
  void seqWaitMoveEnd(T &behavior, const fw::UpdateInfo &info);
  void seqIdle(T &behavior, const fw::UpdateInfo &info);

  TFieldExecCmd<GfComAsm> unknown18;                             // Inferred role: asm command; original member name unknown.
  void (StateAreaMove::*unknown50)(T &, const fw::UpdateInfo &); // Inferred role: sequence; original member name unknown.
  f32 unknown60;                                                 // Inferred role: idle time; original member name unknown.
  f32 unknown64;                                                 // Inferred role: elapsed idle time; original member name unknown.
};

template <typename T> void StateAreaMove<T>::onEnter(void *owner, ai::State *previous) {
  gmk::AGmkBase *gmk = static_cast<T *>(owner)->getBindedGmkInst();
  if (gmk != nullptr) {
    switch (gmk->getGmkType()) {
    case gmk::GMK_TYPE_NPC:
    case gmk::GMK_TYPE_MOB:
      if (gmk->unknown08.unknown10->unknown0c != gmk::SHAPE_TYPE_POINT) {
        unknown50 = &StateAreaMove::seqInitGoalPos;
        return;
      }
      break;
    default:
      break;
    }
  }

  reqState(STATE_ID_UNKNOWN_0);
}

template <typename T> void StateAreaMove<T>::onLeave(void *owner, ai::State *next) {}

template <typename T> void StateAreaMove<T>::onStep(void *owner, const void *param) {
  if (unknown50) {
    (this->*unknown50)(*static_cast<T *>(owner), *static_cast<const fw::UpdateInfo *>(param));
  }
}

} // namespace npc
} // namespace gf
