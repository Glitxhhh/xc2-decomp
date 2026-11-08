#pragma once
#include <new> // IWYU pragma: keep

#include "ai/ai_state.h"
#include "fw/fw_update_info.h"
#include "gf/field/gf_field_exec_cmd.h"
#include "types.h"

namespace gf {

class GfComAsm;

namespace npc {

template <typename T> class StateBattle : public ai::State {
public:
  StateBattle() : unknown18(), unknown50(nullptr), unknown60(0) {}
  static ai::State *create(void *buffer) { return new (buffer) StateBattle; }
  const char *getName() const override { return "StateBattle"; }
  void onEnter(void *owner, ai::State *previous) override;
  void onLeave(void *owner, ai::State *next) override;
  void onStep(void *owner, const void *param) override;
  static bool isCondMatch(const T &behavior);
  void seqApplyBattleMot(T &behavior, const fw::UpdateInfo &info);
  void seqTurnPc(T &behavior, const fw::UpdateInfo &info);
  void seqUpdateBattleMot(T &behavior, const fw::UpdateInfo &info);
  void seqWaitTurnEnd(T &behavior, const fw::UpdateInfo &info);
  void seqUpdateMove(T &behavior, const fw::UpdateInfo &info);

  TFieldExecCmd<GfComAsm> unknown18;                           // Inferred role: asm command; original member name unknown.
  void (StateBattle::*unknown50)(T &, const fw::UpdateInfo &); // Inferred role: sequence; original member name unknown.
  u32 unknown60;                                               // Role and original member name unknown.
};

template <typename T> void StateBattle<T>::onLeave(void *owner, ai::State *next) {}

template <typename T> void StateBattle<T>::onStep(void *owner, const void *param) {
  unknown18.update(static_cast<const fw::UpdateInfo *>(param)->unknown04);
  if (unknown50) {
    (this->*unknown50)(*static_cast<T *>(owner), *static_cast<const fw::UpdateInfo *>(param));
  }
}

} // namespace npc
} // namespace gf
