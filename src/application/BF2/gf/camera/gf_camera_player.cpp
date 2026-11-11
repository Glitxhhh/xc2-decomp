#include "gf/camera/gf_camera_player.h"

#include <math.h>

#include "framework/framework.h"
#include "framework/memory/framework_memory.h"
#include "fw/fw_param_manager.h"
#include "fw/fw_transform.h"
#include "gf/camera/gf_camera_player_target.h"
#include "gf/camera/gf_camera_utilities.h"
#include "gf/data/gf_object_type.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"

namespace gf {

PlayerCamera::~PlayerCamera() { ; }

void PlayerCamera::updateViewMatrix() {
  updateCollision2(unknown40, unknown50);
  unknownd0 = m_saveDistance;
  Camera::updateViewMatrix();
}

// __LINE__ must be 233 as in the original file: it is the line argument of the allocation.
mm::mtl::IntrusivePtr<fw::Camera> PlayerCamera::create() {
  const fw::ParamList *paramList = fw::ParamManager::get()->unknown408[19].operator->();
  fw::ParamAdapter adapter;
  adapter.unknown00 = paramList->unknown0c > 0 ? &paramList->unknown10[0] : nullptr;
#line 233
  return new (fw::Framework::getAllocator(), 16, __FILE__, __LINE__) PlayerCamera(adapter);
}

bool PlayerCamera::isResetClimb() {
  f32 yaw = getYaw(PlayerCameraTarget::get()->unknown60, mm::Vec3::unitZ);
  f32 target = unknownb8;
  if (target < 0.0f) {
    target += 6.2831855f;
  }
  f32 diff = fabsf(yaw - target);
  return diff > 1.4835299f && diff < 4.7996554f;
}

void PlayerCamera::setTarget(GF_OBJ_HANDLE *target) {
  if (target != unknown020) {
    GfObjAcc acc(target);
    if (acc.getType() != OBJECT_TYPE_ENEMY) {
      return;
    }
  }
  if (unknowna8 != target) {
    if (unknowna8 == unknown020) {
      if (PlayerCameraTarget::get() == nullptr) {
        return;
      }
    } else {
      unknown5190 = true;
    }
    unknowna8 = target;
  }
}

f32 PlayerCamera::getFov() { return static_cast<const unknown002 *>(fw::ParamManager::get()->unknown408[19]->unknown10->param)->fov; }

const mm::mtl::RTTI *PlayerCamera::getRTTI() const { return &m_rtti; }

const char *PlayerCamera::getName() const { return "PlayerCamera"; }

f32 PlayerCamera::getNearClip() { return 0.4f; }

f32 PlayerCamera::getFarClip() { return 80000.0f; }

bool PlayerCamera::isManual() { return m_manual; }

f32 PlayerCamera::getSaveYaw() const { return m_saveYaw; }

f32 PlayerCamera::getSavePitch() const { return m_savePitch; }

f32 PlayerCamera::getSaveDistance() const { return m_saveDistance; }

f32 PlayerCamera::getSaveHeight() const { return m_saveHeight; }

u32 PlayerCamera::getSaveSide() const { return m_saveSide; }

bool PlayerCamera::isSaveFreeMode() const { return m_manual; }

void PlayerCamera::resetClimb(ResetCameraWallTiming timing) {
  unknown124 = true;
  unknown52c4 = timing;
  unknownf0 = timing == RESET_CAMERA_WALL_TIMING_UNKNOWN_0 ? 0.6666667f : 0.23333335f;
}

f32 PlayerCamera::getYaw(const mm::Vec3 &position, const mm::Vec3 &target) {
  mm::Vec3 from(position.x, 0.0f, position.z);
  mm::Vec3 to(target.x, 0.0f, target.z);
  if ((fabsf(from.x) <= 0.000001f && fabsf(from.z) <= 0.000001f) || (fabsf(to.x) <= 0.000001f && fabsf(to.z) <= 0.000001f)) {
    return m_saveYaw;
  }
  from.unknown001();
  to.unknown001();
  f32 cosine = to.x * from.x + to.y * from.y + to.z * from.z;
  mm::clampRef(cosine, -1.0f, 1.0f);
  f32 angle = mm::acos(cosine);
  mm::Vec3 axis;
  CameraUtilities::getRotateAxis(from, to, axis);
  return axis.y < 0.0f ? 6.2831855f - angle : angle;
}

f32 PlayerCamera::getPitch(const mm::Vec3 &position, const mm::Vec3 &target) {
  f32 yaw = getYaw(position, target);
  mm::Vec3 from = position;
  mm::Vec3 to = target;
  if ((fabsf(from.x) <= 0.000001f && fabsf(from.y) <= 0.000001f && fabsf(from.z) <= 0.000001f) || (fabsf(to.x) <= 0.000001f && fabsf(to.y) <= 0.000001f && fabsf(to.z) <= 0.000001f)) {
    return m_savePitch;
  }
  mm::Quat rotation;
  rotation.x = 0.0f;
  rotation.y = sinf(yaw * -0.5f);
  rotation.z = 0.0f;
  rotation.w = cosf(yaw * -0.5f);
  from = rotation.rotate(from);
  from.unknown001();
  to.unknown001();
  f32 cosine = to.x * from.x + to.y * from.y + to.z * from.z;
  mm::clampRef(cosine, -1.0f, 1.0f);
  f32 angle = mm::acos(cosine);
  mm::Vec3 axis;
  CameraUtilities::getRotateAxis(from, to, axis);
  return axis.x < 0.0f ? -angle : angle;
}

bool PlayerCamera::getHitPosition(const fw::ColiCheckConfig &config, const mm::Vec3 &start, const mm::Vec3 &end, mm::Vec3 &hitPosition) {
  hitPosition = mm::Vec3::zero;
  unknown160.clear();
  if (!fw::ColiCheck::testLineChara(unknown160, start, end, config)) {
    return false;
  }
  mm::Vec3 position = unknown160.getPosition(0);
  mm::Vec3 normal = unknown160.getNormal(0);
  mm::Vec3 direction = end - start;
  direction.unknown001();
  if (normal.x * direction.x + normal.y * direction.y + normal.z * direction.z < 0.0f) {
    hitPosition = position;
    return true;
  }
  return false;
}

void PlayerCamera::resetBattleWarp() {
  PlayerCameraTarget *target = PlayerCameraTarget::get();
  if (target != nullptr) {
    unknown110 = target->unknown20.unknown00;
    unknown100 = unknown110;
    unknown51a0 = unknown100;
  }
}

} // namespace gf

#include "gf/camera/gf_camera_utilities.cpp"
