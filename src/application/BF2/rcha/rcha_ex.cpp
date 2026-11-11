#include "rcha/rcha_ex.h"

#include "ml/ml_mem.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"
#include "mtl/alloc_handle.h"

CRchaEx::CRchaEx() : unknown19a0(false) {
  for (int i = 0; i < NAME_COUNT; i++) {
    unknown19a4[i] = -1;
  }
}

bool CRchaEx::hasAnm(const void *data) {
  if (data == nullptr) {
    return false;
  }
  CRchaEx anm;
  anm.setup(ml::MlMem::getDebugMem(), data);
  return anm.unknown19a0;
}

void CRchaEx::clear() {
  RchaNode::clear();
  unknown19a0 = false;
}

f32 CRchaEx::getValue(int slot, f32 frame, f32 defaultValue) const {
  if (unknown19a4[slot] >= 0) {
    return unknown10[unknown19a4[slot]].getValue(frame);
  }
  return defaultValue;
}

int CRchaEx::getValueInt(int slot, f32 frame, int defaultValue) const {
  if (unknown19a4[slot] >= 0) {
    return unknown10[unknown19a4[slot]].getValueInt(frame);
  }
  return defaultValue;
}

bool CRchaEx::getVisible(int &visible, const char *name, f32 frame) const {
  visible = 0;
  mm::mtl::FixStr<64> key("ptVisAnm/");
  key += name;
  u32 hash = hashStr(key.c_str());
  for (int i = 0; i < unknown1990; i++) {
    if (unknown10[i].unknown84 == hash) {
      visible = unknown10[i].getValue(frame);
      return true;
    }
  }
  return false;
}

bool CRchaEx::getDynamicsBlend(f32 &blend, f32 frame) const {
  int index = unknown19a4[ANM_DYNAMICS_BLEND];
  if (index >= 0) {
    blend = unknown10[index].getValue(frame);
    return true;
  }
  return false;
}

bool CRchaEx::getWeaponDisp(int &disp, f32 frame) const { return unknown001(disp, ANM_WEAPON_DISP, frame); }

bool CRchaEx::getWeaponMount(int &mount, f32 frame) const { return unknown001(mount, ANM_WEAPON_MOUNT, frame); }

bool CRchaEx::getWeaponBattle(int &battle, f32 frame) const { return unknown001(battle, ANM_WEAPON_BATTLE, frame); }

bool CRchaEx::getWeaponSpMotion(f32 frame) const {
  if (unknown19a4[ANM_WEAPON_SP_MOT] >= 0) {
    return unknown10[unknown19a4[ANM_WEAPON_SP_MOT]].getValueInt(frame) != 0;
  }
  return false;
}

void CRchaEx::getWeaponPos(mm::Vec3 &pos, f32 frame) const {
  pos.x = getValue(ANM_WEAPON_TRANSLATE_X, frame, 0.0f);
  pos.y = getValue(ANM_WEAPON_TRANSLATE_Y, frame, 0.0f);
  pos.z = getValue(ANM_WEAPON_TRANSLATE_Z, frame, 0.0f);
}

void CRchaEx::getWeaponRot(mm::Vec3 &rot, f32 frame) const {
  rot.x = getValue(ANM_WEAPON_ROTATE_X, frame, 0.0f) * mm::DEG_TO_RAD;
  rot.y = getValue(ANM_WEAPON_ROTATE_Y, frame, 0.0f) * mm::DEG_TO_RAD;
  rot.z = getValue(ANM_WEAPON_ROTATE_Z, frame, 0.0f) * mm::DEG_TO_RAD;
}

void CRchaEx::getWeaponScl(f32 &scale, f32 frame) const { scale = getValue(ANM_WEAPON_SCALE, frame, 1.0f); }

bool CRchaEx::getFootEffectL(int &effect, f32 frame) const { return unknown001(effect, ANM_FOOT_EFFECT_L, frame); }

bool CRchaEx::getFootEffectR(int &effect, f32 frame) const { return unknown001(effect, ANM_FOOT_EFFECT_R, frame); }

int CRchaEx::getActionType(f32 frame) const { return getValueInt(ANM_AO_ACTIONID, frame, -1); }

int CRchaEx::getFacePrisetType(f32 frame) const { return getValueInt(ANM_AO_FACE_PRISET_TYPE, frame, -1); }

int CRchaEx::getEyeType(f32 frame) const { return getValueInt(ANM_AO_EYE_TYPE, frame, -1); }

void CRchaEx::getObjPos(mm::Vec3 &pos, f32 frame) const {
  pos.x = getValue(ANM_AO_TRANSLATE_X, frame, 0.0f);
  pos.y = getValue(ANM_AO_TRANSLATE_Y, frame, 0.0f);
  pos.z = getValue(ANM_AO_TRANSLATE_Z, frame, 0.0f);
}

void CRchaEx::getObjRot(mm::Vec3 &rot, f32 frame) const {
  rot.x = getValue(ANM_AO_ROTATE_X, frame, 0.0f) * mm::DEG_TO_RAD;
  rot.y = getValue(ANM_AO_ROTATE_Y, frame, 0.0f) * mm::DEG_TO_RAD;
  rot.z = getValue(ANM_AO_ROTATE_Z, frame, 0.0f) * mm::DEG_TO_RAD;
}

void CRchaEx::getObjScl(f32 &scale, f32 frame) const { scale = getValue(ANM_AO_SCALE, frame, 1.0f); }

bool CRchaEx::isTargetEnable(f32 frame) const {
  if (unknown19a4[ANM_AOTGT_ENABLE] >= 0) {
    return unknown10[unknown19a4[ANM_AOTGT_ENABLE]].getValueInt(frame) == 1;
  }
  return false;
}

void CRchaEx::getTarget(mm::Vec3 &target, f32 frame) const {
  target.x = getValue(ANM_AOTGT_TRANSLATE_X, frame, 0.0f);
  target.y = getValue(ANM_AOTGT_TRANSLATE_Y, frame, 0.0f);
  target.z = getValue(ANM_AOTGT_TRANSLATE_Z, frame, 0.0f);
}
