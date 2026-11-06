#include "gf/game/gf_game_ride.h"

#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_scene.h"
#include "gf/game/gf_game_target.h"
#include "gf/gf_allocator.h"
#include "gf/object/component/pc/gf_pc_property_battle.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"

namespace gf {

constexpr u32 MSG_GAME_RIDE_EVENT = 0x1000030;

enum {
  RIDE_EVENT_RIDE_ON = 0,
  RIDE_EVENT_GET_DOWN = 1,
  RIDE_EVENT_GET_DOWN_FORCE = 2,
};

void GfGameRide::build(const GfSetupParam &) {
// __LINE__ of the operator new call is 0x28 in the game.
#line 40
  GfGameRide *ride = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfGameRide();
  ride->setup();
}

void GfGameRide::setup() { GfEvent::addEventCallback(this); }

void GfGameRide::destroy() {
  GfGameRide *ride = get();
  ride->cleanup();
  delete ride;
}

void GfGameRide::cleanup() { GfEvent::removeEventCallback(this); }

bool GfGameRide::testRideOn() {
  GfGameRide *ride = get();
  if (ride->unknown28 != INVALID_HANDLE) {
    return ride->unknown30 != INVALID_HANDLE;
  }

  return false;
}

void GfGameRide::setRideOn(bool isRide) {
  GfGameRide *ride = get();
  if (isRide) {
    ride->rideOn();
  } else {
    ride->getDown(GfGameManager::getPartyLeader());
  }
}

bool GfGameRide::isVehicle(GF_OBJ_HANDLE *handle) {
  if (handle != INVALID_HANDLE) {
    return get()->unknown28 == handle;
  }

  return false;
}

bool GfGameRide::isRider(GF_OBJ_HANDLE *handle) {
  if (handle != INVALID_HANDLE) {
    return get()->unknown30 == handle;
  }

  return false;
}

GfGameRide::GfGameRide() : unknown28(INVALID_HANDLE), unknown30(INVALID_HANDLE) {}

GfGameRide::~GfGameRide() {}

void GfGameRide::resetHandles() {
  unknown28 = INVALID_HANDLE;
  unknown30 = INVALID_HANDLE;
}

void GfGameRide::gevPartyReturnFieldState(u32 state) {
  if (state == 0) {
    GfObjSetup *setup = GfObjUtil::getObjSetup(GfGameManager::getPartyLeaderDriver());
    if (setup != nullptr && GfGameScene::get() != nullptr && GfGameScene::get()->isRideParty(setup->unknown14) && (unknown28 == INVALID_HANDLE || unknown30 == INVALID_HANDLE)) {
      rideOn();
    }
  }
}

bool GfGameRide::recieveMessage(fw::MessageObject *sender, fw::Message &message) {
  if (message.unknown00 == MSG_GAME_RIDE_EVENT) {
    procMsgGameRideEvent(sender, static_cast<MsgGameRideEvent &>(message));
    return true;
  }

  return false;
}

void GfGameRide::procMsgGameRideEvent(fw::MessageObject *, MsgGameRideEvent &message) {
  GfObjSetup *setup = GfObjUtil::getObjSetup(GfGameManager::getPartyLeaderDriver());
  if (setup != nullptr && GfGameScene::get() != nullptr && GfGameScene::get()->isRideParty(setup->unknown14)) {
    switch (message.unknown08) {
    case RIDE_EVENT_RIDE_ON:
      rideOn();
      break;
    case RIDE_EVENT_GET_DOWN: {
      GF_OBJ_HANDLE *driver = GfGameManager::getPartyLeaderDriver();
      getDown(driver);
      if (get()->unknown28 == INVALID_HANDLE || get()->unknown30 == INVALID_HANDLE) {
        GfGameTarget::disableTargetWithoutEnemy();
        GfObj *obj = GfObjUtil::getObj(driver);
        if (obj != nullptr) {
          MsgPcBattleStart start(0);
          sendMessage(obj, start);
        }
      }
      break;
    }
    case RIDE_EVENT_GET_DOWN_FORCE:
      getDown(GfGameManager::getPartyLeaderDriver());
      break;
    }
  }
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfGameRide>::~PtrSingleton();
