#include "gf/object/component/pc/gf_pc_state_util_field.h"

#include "framework/object/component_object.h"
#include "framework/object/updatable_object.h"
#include "framework/reference_frame.h"
#include "fw/fw_transform.h"
#include "gf/camera/gf_camera_player.h"
#include "gf/game/gf_game_player_camera.h"
#include "gf/game/gf_game_player_formation.h"
#include "gf/game/gf_game_ride.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/behavior/plugin/gf_plugin_manager.h"
#include "gf/object/component/env_sensor/gf_com_env_sensor.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/component/gf_component.h"
#include "gf/object/component/pc/field/gf_pc_param_field.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/param/gf_pc_param.h"
#include "gf/object/component/pc/plugin/gf_pc_access_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_dead_col_check_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_fall_into_coli_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_lure_plugin.h"
#include "gf/object/component/pc/plugin/gf_pc_water_in_plugin.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_property.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_plane.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/bitflag.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/rtti.h"

namespace gf {
namespace pc {

bool StateUtilField::execAsmCmd(GfComAsm &comAsm, ASM_CMD_ID_FIELD id) { return comAsm.execCmd(getASMCmdNameField(id), ANIM_LAYER_BASE); }

bool StateUtilField::testVechile(GfComBehaviorPc &behavior) { return GfGameRide::isVehicle(static_cast<GfObj *>(behavior.unknown08)->unknownf8); }

bool StateUtilField::isWalkMode(GfComPropertyPc &property) { return property.unknown310.unknown10_0; }

bool StateUtilField::isStop(GfComPropertyPc &property, u32 noInputFrameCount) { return property.unknown310.unknown001()->stopCnt <= noInputFrameCount; }

bool StateUtilField::testAutoRun(GfComPropertyPc &property) { return property.unknown310.unknown11_0; }

bool StateUtilField::isTurnEndRange(GfComPropertyPc &property) {
  f32 angle = calcInputDiffAngle(property);
  return property.unknown310.unknown001()->turnEndAngle >= angle;
}

bool StateUtilField::isInputInverseDir(GfComPropertyPc &property) {
  mm::Vec3 input = property.unknown2b0 * property.unknown60.unknown04 + property.unknown2d0 * property.unknown60.unknown00;
  return input.x * property.unknown1e0.x + input.y * property.unknown1e0.y + input.z * property.unknown1e0.z < 0.0f;
}

bool StateUtilField::isBackRange(GfComPropertyPc &property) { return calcInputDiffAngle(property) >= property.unknown310.unknown001()->backAngle; }

bool StateUtilField::isBackRangeAir(GfComPropertyPc &property) { return calcInputDiffAngleVel(property) >= property.unknown310.unknown001()->backAngle; }

bool StateUtilField::ignoreOnGroundJump(GfComPropertyPc &property, f32 time) { return time < property.unknown310.unknown001()->ignoreTimeJump; }

void StateUtilField::setIdleStatus(GfComPropertyPc &property, bool isIdle) {
  if (isIdle) {
    property.unknown310.unknown10_2 = true;
  } else {
    property.unknown310.unknown10_2 = false;
  }
}

void StateUtilField::setAirStatus(GfComBehaviorPc &behavior, bool isAir) {
  GfComPropertyPc *property = behavior.getProperty();
  if (isAir) {
    property->unknown310.unknown11_1 = true;
  } else {
    property->unknown310.unknown11_1 = false;
  }
}

void StateUtilField::setSpecialActStatus(GfComBehaviorPc &behavior, bool isSpecialAct) {
  GfComPropertyPc *property = behavior.getProperty();
  if (isSpecialAct) {
    property->unknown310.unknown11_2 = true;
  } else {
    property->unknown310.unknown11_2 = false;
  }
}

bool StateUtilField::isWallUpMove(GfPropertyField::WALL_MOVE_MODE mode) {
  return (mode == GfPropertyField::WALL_MOVE_MODE_UP || mode == GfPropertyField::WALL_MOVE_MODE_UP_RIGHT) | (mode == GfPropertyField::WALL_MOVE_MODE_UP_LEFT);
}

ASM_CMD_ID_FIELD StateUtilField::getAsmID(GfPropertyField::WALL_MOVE_MODE mode) {
  switch (mode) {
  case GfPropertyField::WALL_MOVE_MODE_UP:
  case GfPropertyField::WALL_MOVE_MODE_UP_RIGHT:
  case GfPropertyField::WALL_MOVE_MODE_UP_LEFT:
    return ASM_CMD_ID_FIELD_CLIMBUP;
  case GfPropertyField::WALL_MOVE_MODE_RIGHT:
    return ASM_CMD_ID_FIELD_CLIMBRIGHT;
  case GfPropertyField::WALL_MOVE_MODE_DOWN_RIGHT:
  case GfPropertyField::WALL_MOVE_MODE_DOWN:
  case GfPropertyField::WALL_MOVE_MODE_DOWN_LEFT:
    return ASM_CMD_ID_FIELD_CLIMBDOWN;
  case GfPropertyField::WALL_MOVE_MODE_LEFT:
    return ASM_CMD_ID_FIELD_CLIMBLEFT;
  default:
    return ASM_CMD_ID_FIELD_CLIMBIDLE;
  }
}

void StateUtilField::resetCameraForWall(GfComBehaviorPc &behavior, Timing timing) {
  if (!behavior.getProperty()->unknown111_2) {
    return;
  }
  static const ResetCameraWallTiming CAMERA_TIMINGS[] = {RESET_CAMERA_WALL_TIMING_UNDER_GROUND, RESET_CAMERA_WALL_TIMING_GROUND, RESET_CAMERA_WALL_TIMING_AIR};
  GfGamePlayerCamera::resetCameraClimb(CAMERA_TIMINGS[timing]);
}

void StateUtilField::notifyRiderEvent(GfComBehaviorPc &behavior, VehicleEvent event) {
  MsgPcFieldNotifyRiderEvent message(event);
  StateUtil::sendMessageToRider(behavior, message);
}

bool StateUtilField::isBackMove(GfComPropertyPc &property) {
  return property.unknown1e0.x * property.unknown80.x + property.unknown1e0.y * property.unknown80.y + property.unknown1e0.z * property.unknown80.z < 0.0f;
}

bool StateUtilField::isInterruptionWater(GfComPropertyPc &property) {
  f32 depth = property.unknown118 - property.unknown2f0;
  return 0.2f <= property.unknown160.y - depth;
}

bool StateUtilField::isSwimFromAir(GfComPropertyPc &property) {
  const WaterCommonParam *param = property.unknown310.unknown002();
  return property.unknown90 >= param->waterDiveMinSpeed;
}

bool StateUtilField::isWallFall(GfComPropertyPc &property) {
  property.getEnvSensor();
  GfComBehaviorPc *behavior = property.unknown08->getComponent<GfComBehaviorPc>();
  return (StateUtil::getClimbWallInfo(*behavior) == nullptr) | property.unknown60.unknown08.test(INPUT_ID_WALL_RELEASE);
}

bool StateUtilField::ignoreSlideJump(GfComPropertyPc &property, f32 time) { return time <= property.unknown001()->ignoreLandTime; }

bool StateUtilField::isFallFromSlideState(GfComPropertyPc &property) {
  EnviromentSensor *sensor = property.getEnvSensor();
  if (!sensor->unknown24_0) {
    return true;
  }
  const SlideParam *param = property.unknown001();
  return property.unknown160.y - sensor->unknown30.unknown00.y >= param->fallDistance;
}

void StateUtilField::setAsmSpeedSlideBrake(GfComPropertyPc &property) { property.unknown08->getComponent<GfComAsm>()->setVariable("V_speed", property.unknownc0 * 60.0f * 60.0f / 1000.0f); }

bool StateUtilField::isSlideStop(GfComPropertyPc &property) {
  const SlideParam *param = property.unknown001();
  return property.unknownc0 <= param->stopVel;
}

f32 StateUtilField::getChildFrameHeight(GfComponent &component) {
  GfComTransform *transform = mm::mtl::dynamicCast<GfComTransform>(component.unknown08->unknown38[GfComTransform::COMPONENT_INDEX]);
  fw::ReferenceFrame *frame = transform->unknown18.operator->();
  frame->syncLocalTransform();
  return frame->unknown20.unknown00.y;
}

void StateUtilField::setChildFrameHeight(GfComponent &component, f32 height) {
  GfComTransform *transform = mm::mtl::dynamicCast<GfComTransform>(component.unknown08->unknown38[GfComTransform::COMPONENT_INDEX]);
  fw::ReferenceFrame *frame = transform->unknown18.operator->();
  frame->invalidateWorld();
  frame->unknown20.unknown00.y = height;
}

bool StateUtilField::isWallIdleMotion(GfComAsm &comAsm) {
  const char *stateName = comAsm.getStateName(ANIM_LAYER_BASE);
  bool isIdle = false;
  if (stateName != nullptr) {
    if (__builtin_strcmp(stateName, "S_climbidle_base") == 0 || __builtin_strcmp(stateName, "S_climbidle_mirror") == 0) {
      isIdle = true;
    }
  }
  return isIdle;
}

void StateUtilField::notifyTurn(GfComBehaviorPc &behavior) {
  if (behavior.getProperty()->unknown38 == 0) {
    GfGamePlayerFormation *formation = GfGamePlayerFormation::get();
    formation->unknown234 = !formation->unknown234;
  }
}

bool StateUtilField::isEnableWallPrepare(GfComPropertyPc &property) {
  if (property.unknown38 == 0) {
    return false;
  }
  GF_OBJ_HANDLE *handle = GfGamePlayerFormation::get()->unknown1a0[property.unknown38 - 2].unknown08;
  if (handle == INVALID_HANDLE) {
    return false;
  }
  return GfObjUtil::getProperty(handle)->unknown18->unknown00 == PROPERTY_MOVE_CLIMB;
}

bool StateUtilField::isWallDetach(GfComPropertyPc &property) {
  EnviromentSensor *sensor = property.getEnvSensor();
  if (!sensor->unknown24_0 || ((sensor->unknown30.unknown30 >> 4) & 1) != 0) {
    return false;
  }
  const mm::Plane &plane = sensor->unknown30.unknown10;
  const mm::Vec3 &position = property.unknown160;
  f32 dot = position.x * plane.normal.x + position.y * plane.normal.y + position.z * plane.normal.z;
  return plane.distance + dot < -property.unknown310.unknown38;
}

void StateUtilField::setEnableFallIntoColi(GfComBehaviorPc &behavior, bool isEnable) {
  FallIntoColiPlugin *plugin = behavior.unknown10.unknown001<FallIntoColiPlugin>(9);
  if (plugin != nullptr) {
    plugin->setActivate(isEnable);
  }
}

void StateUtilField::setAccessFlag(GfComBehaviorPc &behavior, bool isEnable) {
  AccessPlugin *plugin = behavior.unknown10.unknown001<AccessPlugin>(4);
  if (plugin != nullptr) {
    plugin->setActivate(isEnable);
  }
}

void StateUtilField::setEnableLure(GfComBehaviorPc &behavior, bool isEnable) {
  LurePlugin *plugin = behavior.unknown10.unknown001<LurePlugin>(15);
  if (plugin != nullptr) {
    plugin->setActivate(isEnable);
  }
}

void StateUtilField::setEnableDeadColCheck(GfComBehaviorPc &behavior, bool isEnable) {
  DeadColCheckPlugin *plugin = behavior.unknown10.unknown001<DeadColCheckPlugin>(19);
  if (plugin != nullptr) {
    plugin->setActivate(isEnable);
  }
}

void StateUtilField::setEnableWaterIn(GfComBehaviorPc &behavior, bool isEnable) {
  WaterInPlugin *plugin = behavior.unknown10.unknown001<WaterInPlugin>(18);
  if (plugin != nullptr) {
    plugin->setActivate(isEnable);
  }
}

} // namespace pc
} // namespace gf
