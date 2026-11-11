#pragma once
#include <stddef.h>

#include "rcha/rcha_node.h"
#include "types.h"

namespace mm {
struct Col4;
struct Vec3;
} // namespace mm

class RchaEff : public RchaNode {
public:
  static const int NAME_COUNT = 20;

  // Slots of unknown19a4, in the order of the names (eff/ and effAtr/ tracks) that setup looks for.
  enum {
    EFF_TRANSLATE_X = 0,
    EFF_TRANSLATE_Y = 1,
    EFF_TRANSLATE_Z = 2,
    EFF_ROTATE_X = 3,
    EFF_ROTATE_Y = 4,
    EFF_ROTATE_Z = 5,
    EFF_SCALE_X = 6,
    EFF_SCALE_Y = 7,
    EFF_SCALE_Z = 8,
    EFFATR_TRANSLATE_X = 9,
    EFFATR_TRANSLATE_Y = 10,
    EFFATR_TRANSLATE_Z = 11,
    EFFATR_ROTATE_X = 12,
    EFFATR_ROTATE_Y = 13,
    EFFATR_ROTATE_Z = 14,
    EFFATR_SCALE_X = 15,
    EFFATR_SCALE_Y = 16,
    EFFATR_SCALE_Z = 17,
    EFFATR_END = 18,
    EFFATR_KILL = 19,
  };

  RchaEff();
  virtual void clear();
  virtual bool setup(mtl::ALLOC_HANDLE handle, const void *data);
  static bool hasAnm(const void *data);
  f32 getValue(int slot, f32 frame, f32 defaultValue) const;
  int getValueInt(int slot, f32 frame, int defaultValue) const;
  bool getPos(mm::Vec3 &pos, f32 frame) const;
  bool getRot(mm::Vec3 &rot, f32 frame) const;
  bool getScl(mm::Vec3 &scale, f32 frame) const;
  bool getProgress(int &current, int &total, f32 frame) const;
  bool getCol(mm::Col4 &color, f32 frame) const;
  bool isGenelate(f32 frame) const;
  bool isEnd(f32 frame) const;
  bool isKill(f32 frame) const;
  bool getSpeed(f32 &speed, f32 frame) const;

private:
  bool unknown19a0;            // Inferred role: has any named track; original member name unknown.
  int unknown19a4[NAME_COUNT]; // Inferred role: track index of each name; original member name unknown.

  friend struct RchaEffLayout;
};

struct RchaEffLayout {
  static_assert(offsetof(RchaEff, unknown19a0) == 0x19a0, "");
  static_assert(offsetof(RchaEff, unknown19a4) == 0x19a4, "");
  static_assert(sizeof(RchaEff) == 0x19f8, "");
};
