#pragma once
#include <stddef.h>

#include "rcha/rcha_anm.h"
#include "rcha/rcha_node.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

// Declared from the symbols _ZN7CRchaExC1Ev (0x710069eb34), _ZN7CRchaEx5setupEN3mtl12ALLOC_HANDLEEPKv (0x710069f438) and
// the vtable _ZTV7CRchaEx (0x71011a77c0); its size is the allocation size in CharaEvaPlayer::play.
class CRchaEx : public RchaNode {
public:
  static const int NAME_COUNT = 29;

  // Slots of unknown19a4, in the order of the names (dmy and the ptExAnm/ tracks) that setup looks for.
  enum {
    ANM_DMY = 0,
    ANM_DYNAMICS_BLEND = 1,
    ANM_WEAPON_DISP = 2,
    ANM_WEAPON_MOUNT = 3,
    ANM_WEAPON_BATTLE = 4,
    ANM_WEAPON_SP_MOT = 5,
    ANM_WEAPON_TRANSLATE_X = 6,
    ANM_WEAPON_TRANSLATE_Y = 7,
    ANM_WEAPON_TRANSLATE_Z = 8,
    ANM_WEAPON_ROTATE_X = 9,
    ANM_WEAPON_ROTATE_Y = 10,
    ANM_WEAPON_ROTATE_Z = 11,
    ANM_WEAPON_SCALE = 12,
    ANM_FOOT_EFFECT_L = 13,
    ANM_FOOT_EFFECT_R = 14,
    ANM_AO_ACTIONID = 15,
    ANM_AO_FACE_PRISET_TYPE = 16,
    ANM_AO_EYE_TYPE = 17,
    ANM_AO_TRANSLATE_X = 18,
    ANM_AO_TRANSLATE_Y = 19,
    ANM_AO_TRANSLATE_Z = 20,
    ANM_AO_ROTATE_X = 21,
    ANM_AO_ROTATE_Y = 22,
    ANM_AO_ROTATE_Z = 23,
    ANM_AO_SCALE = 24,
    ANM_AOTGT_ENABLE = 25,
    ANM_AOTGT_TRANSLATE_X = 26,
    ANM_AOTGT_TRANSLATE_Y = 27,
    ANM_AOTGT_TRANSLATE_Z = 28,
  };

  CRchaEx();
  virtual void clear();
  virtual bool setup(mtl::ALLOC_HANDLE handle, const void *data);
  static bool hasAnm(const void *data);
  f32 getValue(int slot, f32 frame, f32 defaultValue) const;
  int getValueInt(int slot, f32 frame, int defaultValue) const;
  bool getVisible(int &visible, const char *name, f32 frame) const;
  bool getDynamicsBlend(f32 &blend, f32 frame) const;
  bool getWeaponDisp(int &disp, f32 frame) const;
  bool getWeaponMount(int &mount, f32 frame) const;
  bool getWeaponBattle(int &battle, f32 frame) const;
  bool getWeaponSpMotion(f32 frame) const;
  void getWeaponPos(mm::Vec3 &pos, f32 frame) const;
  void getWeaponRot(mm::Vec3 &rot, f32 frame) const;
  void getWeaponScl(f32 &scale, f32 frame) const;
  bool getFootEffectL(int &effect, f32 frame) const;
  bool getFootEffectR(int &effect, f32 frame) const;
  int getActionType(f32 frame) const;
  int getFacePrisetType(f32 frame) const;
  int getEyeType(f32 frame) const;
  void getObjPos(mm::Vec3 &pos, f32 frame) const;
  void getObjRot(mm::Vec3 &rot, f32 frame) const;
  void getObjScl(f32 &scale, f32 frame) const;
  bool isTargetEnable(f32 frame) const;
  void getTarget(mm::Vec3 &target, f32 frame) const;

private:
  // Inferred helper: reads the track of a slot as an int when the resource has it; original name unknown.
  bool unknown001(int &value, int slot, f32 frame) const {
    int index = unknown19a4[slot];
    if (index >= 0) {
      value = unknown10[index].getValueInt(frame);
      return true;
    }
    return false;
  }

  bool unknown19a0;            // Inferred role: set up; original member name unknown.
  int unknown19a4[NAME_COUNT]; // Inferred role: track index of each name; original member name unknown.

  friend struct CRchaExLayout;
};

struct CRchaExLayout {
  static_assert(offsetof(CRchaEx, unknown19a0) == 0x19a0, "");
  static_assert(offsetof(CRchaEx, unknown19a4) == 0x19a4, "");
  static_assert(sizeof(CRchaEx) == 0x1a18, "");
};
