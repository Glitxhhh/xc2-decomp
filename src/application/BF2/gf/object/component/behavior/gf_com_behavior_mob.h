#pragma once
#include <stddef.h>

#include "ai/ai_state_hfsm.h"
#include "gf/field/gf_field_move_speed.h"
#include "gf/object/component/behavior/gf_com_behavior.h"
#include "gmk/gmk_squad.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace mm {
struct Quat;
} // namespace mm

namespace fw {
class ColiMoveObject;
class MessageObject;
} // namespace fw

namespace gmk {
class AGmkBase;
} // namespace gmk

namespace navi {
class NvmshAcObj;
} // namespace navi

namespace gf {

struct MsgDebugActivateComponentWindow;

namespace mob {

// The original enumerator names are unknown. The states registered by GfComBehaviorMob::createFsm are noted for each id.
enum STATE_ID {
  STATE_ID_UNKNOWN_0 = 0, // StateIdle
  STATE_ID_UNKNOWN_1 = 1, // StateMove
  STATE_ID_UNKNOWN_2 = 2, // npc::StateAreaMove
  STATE_ID_UNKNOWN_3 = 3, // StateSquadMember
  STATE_ID_UNKNOWN_4 = 4, // npc::StateReaction
  STATE_ID_UNKNOWN_5 = 5, // npc::StateBattle
};

} // namespace mob

// Layout from its constructor (0x710052b4c4), destructor and cleanup: the navi mesh object at 0xa8, the squad navi at 0xc0,
// the velocity at 0x100 read by recieveMessage, the state machine at 0x5328 and the listener at 0x53c0.
class GfComBehaviorMob : public GfComBehavior {
public:
  class Listener {
  public:
    virtual void onWkStandbyLogout();

    GfComBehaviorMob *unknown08; // Inferred role: owner; original member name unknown.
  };

  void procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message);
  void procMsgObjectGetVelocity(fw::MessageObject *sender, MsgObjectGetVelocity &message);
  void cleanup();
  const mm::Vec3 &getPos() const;
  const mm::Quat &getRot() const;
  fw::ColiMoveObject *getColiObject() const;
  gmk::AGmkBase *getBindedGmkInst() const;
  bool isSquadMember() const;
  void initMoveSpeed(f32 time);
  void setStateId(mob::STATE_ID stateId);
  void disposeNaviMeshObj();
  void disposeFsm();
  void disposeSquadNavi();
  void setActivateCollison(bool isActivate);
  u32 getStateId() const;

  u8 _98[0xa8 - 0x98];
  navi::NvmshAcObj *unknowna8; // Inferred role: navi mesh object; original member name unknown.
  u8 _b0[0xb8 - 0xb0];
  void *unknownb8;             // Role and original member name unknown.
  gmk::GmkSquadNavi unknownc0; // Inferred role: squad navi; original member name unknown.
  mm::Vec3 unknown100;         // Inferred role: velocity; original member name unknown.
  u8 _110[0x1e0 - 0x110];
  GfFieldMoveSpeed unknown1e0; // Inferred role: move speed; original member name unknown.
  u8 _210[0x5328 - 0x210];
  ai::Hfsm unknown5328; // Inferred role: state machine; original member name unknown.
  bool unknown53b0;     // Inferred role: state machine is not set up, true by default; original member name unknown.
  void *unknown53b8;    // Inferred role: viewer; original member name unknown.
  Listener unknown53c0; // Inferred role: listener; original member name unknown.
  u8 _53d0[0x53e0 - 0x53d0];
};

static_assert(sizeof(GfComBehaviorMob::Listener) == 0x10, "");
static_assert(offsetof(GfComBehaviorMob, unknowna8) == 0xa8, "");
static_assert(offsetof(GfComBehaviorMob, unknownb8) == 0xb8, "");
static_assert(offsetof(GfComBehaviorMob, unknownc0) == 0xc0, "");
static_assert(offsetof(GfComBehaviorMob, unknown100) == 0x100, "");
static_assert(offsetof(GfComBehaviorMob, unknown1e0) == 0x1e0, "");
static_assert(offsetof(GfComBehaviorMob, unknown5328) == 0x5328, "");
static_assert(offsetof(GfComBehaviorMob, unknown53b0) == 0x53b0, "");
static_assert(offsetof(GfComBehaviorMob, unknown53b8) == 0x53b8, "");
static_assert(offsetof(GfComBehaviorMob, unknown53c0) == 0x53c0, "");
static_assert(sizeof(GfComBehaviorMob) == 0x53e0, "");

} // namespace gf
