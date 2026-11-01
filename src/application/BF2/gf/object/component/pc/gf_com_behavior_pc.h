#pragma once
#include <stddef.h>

#include "ai/ai_state.h"
#include "framework/message/message_object.h"
#include "framework/object/component_object.h"
#include "framework/object/updatable_object.h"
#include "gf/object/component/behavior/gf_com_behavior.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_agent.h"
#include "mm_mtl/rtti.h"
#include "mm_mtl/unique_ptr.h"
#include "types.h"

namespace gf {

struct MsgDebugActivateComponentWindow;

enum {
  MSG_PC_GET_STATE = 0x1000005,
};

// Layout evidence: StateFieldWaterNormal::procMsgPcFieldWaterWarp (0x7100561cbc) builds it on the stack and
// GfComBehaviorPc::recieveMessage writes the id of the current state to the member at 0x8.
struct MsgPcGetState : fw::Message {
  MsgPcGetState() : fw::Message(MSG_PC_GET_STATE, 0x40), unknown08(ai::INVALID_STATE_ID) {}

  u32 unknown08; // Inferred role: current state id; original member name unknown.
};

static_assert(offsetof(MsgPcGetState, unknown08) == 0x08, "");

class GfComBehaviorPc : public GfComBehavior {
public:
  static mm::mtl::RTTI m_rtti;

  void procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message);
  void setEnableAgentField(bool isEnable);
  void setEnableAgentBattle(bool isEnable);

  GfComPropertyPc *getProperty() const { return mm::mtl::dynamicCast<GfComPropertyPc>(unknown08->unknown38[GfComPropertyPc::COMPONENT_INDEX]); }

  mm::mtl::UniquePtr<pc::Agent> unknown98; // Inferred role: agent, tested by setEnableAgentField; original member name unknown.
};

static_assert(offsetof(GfComBehaviorPc, unknown98) == 0x98, "");

} // namespace gf
