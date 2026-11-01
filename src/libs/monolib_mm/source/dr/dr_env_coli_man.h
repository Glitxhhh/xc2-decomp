#pragma once
#include <stddef.h>

#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {
class DrEnvColiObj;
class DrMan;

struct DrEnvColiResult {
  s32 unknown00; // Inferred role: bgm id; original member name unknown.
  s32 unknown04; // Inferred role: layer id; original member name unknown.
  s32 unknown08; // Inferred role: reverb id; original member name unknown.
  s32 unknown0c; // Inferred role: cave id; original member name unknown.
  s32 unknown10; // Inferred role: area id; original member name unknown.
  u8 _14[0x18 - 0x14];
  s32 unknown18; // Inferred role: wind id; original member name unknown.
  u8 : 2;
  u8 unknown1c_2 : 1; // Inferred role: room; original member name unknown.
};

static_assert(offsetof(DrEnvColiResult, unknown18) == 0x18, "");

class DrEnvColiMan {
public:
  DrEnvColiObj *createObj(const void *data);
  bool testEnvColi(DrEnvColiResult *result, const mm::Vec3 &position, f32 radius);
  void clear();
  void updateTime(bool isReset);
  void updateCloudFade(bool isReset, bool isForce);
  void updateRainDropFade(bool isReset);

  DrEnvColiObj *unknown00[2]; // Inferred role: object list (first and last); original member name unknown.
  DrEnvColiObj *unknown10[2]; // Inferred role: object list (first and last); original member name unknown.
  DrEnvColiObj *unknown20[2]; // Inferred role: object list (first and last); original member name unknown.
  DrMan *unknown30;           // Inferred role: dr manager; original member name unknown.
  u8 _38[0x48 - 0x38];
  DrEnvColiResult unknown48; // Inferred role: result; original member name unknown.
  f32 unknown68;             // Inferred role: time; original member name unknown.
  f32 unknown6c;             // Inferred role: weather fade ratio; original member name unknown.
  f32 unknown70;             // Inferred role: weather fade frame; original member name unknown.
  u8 _74[0x78 - 0x74];
  f32 unknown78; // Inferred role: rain drop fade ratio; original member name unknown.
  f32 unknown7c; // Inferred role: rain drop fade frame; original member name unknown.
  u8 _80[0x84 - 0x80];
  f32 unknown84; // Inferred role: cloud fade frame; original member name unknown.
  f32 unknown88; // Inferred role: cloud fade ratio; original member name unknown.
};

static_assert(offsetof(DrEnvColiMan, unknown10) == 0x10, "");
static_assert(offsetof(DrEnvColiMan, unknown20) == 0x20, "");
static_assert(offsetof(DrEnvColiMan, unknown30) == 0x30, "");
static_assert(offsetof(DrEnvColiMan, unknown48) == 0x48, "");
static_assert(offsetof(DrEnvColiMan, unknown68) == 0x68, "");
static_assert(offsetof(DrEnvColiMan, unknown78) == 0x78, "");
static_assert(offsetof(DrEnvColiMan, unknown84) == 0x84, "");

} // namespace ml
