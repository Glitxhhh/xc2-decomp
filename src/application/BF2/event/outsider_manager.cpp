#include "event/outsider_manager.h"

#include "event/alpha_manager.h"
#include "event/alpha_obj.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_util.h"
#include "mm_mtl/singleton.h"

namespace event {

OutsiderManager::OutsiderManager() : unknown10(), unknown14(0), unknown18(OBJ_TYPE_NONE) {}

void OutsiderManager::clear() {
  if (unknown14 & FLAG_ACTIVE) {
    update(false);
  }
  unknown20.clear();
  unknown18 = OBJ_TYPE_NONE;
  unknown14 = 0;
}

void OutsiderManager::update(bool isHide) {
  if (unknown20.getType() < OutsiderField::TYPE_CIRCLE) {
    return;
  }
  if (unknown18 & OBJ_TYPE_NPC) {
    updateSub(isHide, gmk::GMK_TYPE_NPC);
  }
  if (unknown18 & OBJ_TYPE_ROUTED_NPC) {
    updateSub(isHide, gmk::GMK_TYPE_ROUTED_NPC);
  }
  if (unknown18 & OBJ_TYPE_ENEMY) {
    updateSub(isHide, gmk::GMK_TYPE_ENEMY);
  }
  if (unknown18 & OBJ_TYPE_ROUTED_ENEMY) {
    updateSub(isHide, gmk::GMK_TYPE_ROUTED_ENEMY);
  }
  if (unknown18 & OBJ_TYPE_ROUTED_MAP_OBJ) {
    updateSub(isHide, gmk::GMK_TYPE_ROUTED_MAP_OBJ);
  }
  if (unknown18 & OBJ_TYPE_MOB) {
    updateSub(isHide, gmk::GMK_TYPE_MOB);
  }
  if (unknown18 & OBJ_TYPE_ROUTED_MOB) {
    updateSub(isHide, gmk::GMK_TYPE_ROUTED_MOB);
  }
}

void OutsiderManager::update() {
  if (unknown14 & FLAG_ACTIVE) {
    unknown20.update();
    if (unknown20.getRadius() > 0.0f) {
      update(true);
    }
  }
}

void OutsiderManager::updateSub(bool isHide, gf::GF_OBJ_HANDLE *handle) {
  gf::GfComTransform *transform = gf::GfObjUtil::getObj(handle)->getComponent<gf::GfComTransform>();
  if (!isHide) {
    mm::mtl::Singleton<AlphaManager>::getPtr()->setAlpha(handle, ALPHA_ATTR_UNKNOWN_0, 1.0f, 1.0f);
    return;
  }
  f32 alpha = gf::GfObjAcc(handle).getAlphaEvent();
  if (unknown20.isInside(transform->getPosition())) {
    alpha = __builtin_fmaxf(alpha - 0.1f, 0.0f);
  } else {
    alpha = __builtin_fminf(alpha + 0.1f, 1.0f);
  }
  mm::mtl::Singleton<AlphaManager>::getPtr()->setAlpha(handle, ALPHA_ATTR_UNKNOWN_0, alpha, 1.0f);
}

void OutsiderManager::render() {
  if (isDisp() && (unknown14 & FLAG_ACTIVE)) {
    unknown20.draw();
  }
}

void OutsiderManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_INIT:
  case MSG_TYPE_END_SCENE:
  case MSG_TYPE_CLEAR:
    clear();
    break;
  case MSG_TYPE_UPDATE:
    update();
    break;
  case MSG_TYPE_RENDER:
    render();
    break;
  default:
    break;
  }
}

void OutsiderManager::defineTgt(OBJ_TYPE targets) { unknown18 = targets; }

void OutsiderManager::defineFld(OutsiderField::TYPE type, const mm::Vec3 &pos, f32 radius) { unknown20.setField(type, pos, radius); }

void OutsiderManager::setActive(bool isActive) {
  if (isActive) {
    unknown14 |= FLAG_ACTIVE;
  } else {
    clear();
  }
}

void OutsiderManager::setDisp(bool isDisp) { unknown10.set(DISP_FLAG_DISP, isDisp); }

bool OutsiderManager::isDisp() const { return unknown10.test(DISP_FLAG_DISP); }

} // namespace event
