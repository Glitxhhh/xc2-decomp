#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ml {

class DrResMdoSeamMemObj;
struct MdoWrkMatRes;
struct MdsSeamEnvMapHead;

class DrResMdoSeamWrkEnv {
public:
  virtual ~DrResMdoSeamWrkEnv();
  void setDispState();
  u32 chkDispState();
  u8 *getDisplayWrk();
  int getDisplayWrkSize();
  void setDisplayWrk(u8 *work, int size);
  void changeMemCall(const MdsSeamEnvMapHead *head);
  void setInfo(const mm::Vec3 &position, const mm::Vec3 &scale, bool isEnable, u32 flags);
  void release();

  DrResMdoSeamWrkEnv *unknown08;      // Inferred role: next object; original member name unknown.
  DrResMdoSeamWrkEnv *unknown10;      // Inferred role: previous object; original member name unknown.
  const MdsSeamEnvMapHead *unknown18; // Inferred role: env map header; original member name unknown.
  u8 _20[0x28 - 0x20];
  void *unknown28; // Inferred role: allocated bit table; original member name unknown.
  u8 _30[0x38 - 0x30];
  u8 *unknown38[2]; // Inferred role: display work per buffer; original member name unknown.
  int unknown48[2]; // Inferred role: display work size per buffer; original member name unknown.
  u32 unknown50;    // Inferred role: env map index; original member name unknown.
  u8 _54[0x58 - 0x54];
  MdoWrkMatRes *unknown58;       // Inferred role: material work; original member name unknown.
  DrResMdoSeamMemObj *unknown60; // Inferred role: memory object; original member name unknown.
  u32 unknown68;                 // Inferred role: info flags; original member name unknown.
  u32 unknown6c;                 // Inferred role: state flags; original member name unknown.
  s32 unknown70;                 // Inferred role: memory size; original member name unknown.
  bool unknown74;                // Inferred role: enable; original member name unknown.
  u8 _75[0x80 - 0x75];
  mm::Vec3 unknown80; // Inferred role: position; original member name unknown.
  mm::Vec3 unknown90; // Inferred role: scale; original member name unknown.
};

static_assert(offsetof(DrResMdoSeamWrkEnv, unknown28) == 0x28, "");

static_assert(offsetof(DrResMdoSeamWrkEnv, unknown18) == 0x18, "");
static_assert(offsetof(DrResMdoSeamWrkEnv, unknown38) == 0x38, "");
static_assert(offsetof(DrResMdoSeamWrkEnv, unknown48) == 0x48, "");
static_assert(offsetof(DrResMdoSeamWrkEnv, unknown68) == 0x68, "");
static_assert(offsetof(DrResMdoSeamWrkEnv, unknown50) == 0x50, "");
static_assert(offsetof(DrResMdoSeamWrkEnv, unknown58) == 0x58, "");
static_assert(offsetof(DrResMdoSeamWrkEnv, unknown70) == 0x70, "");
static_assert(offsetof(DrResMdoSeamWrkEnv, unknown6c) == 0x6c, "");
static_assert(offsetof(DrResMdoSeamWrkEnv, unknown74) == 0x74, "");
static_assert(offsetof(DrResMdoSeamWrkEnv, unknown80) == 0x80, "");
static_assert(offsetof(DrResMdoSeamWrkEnv, unknown90) == 0x90, "");

} // namespace ml
