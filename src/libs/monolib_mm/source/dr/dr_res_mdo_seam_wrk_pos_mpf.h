#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {
class DrResMdoSeamMemObj;

class DrResMdoSeamWrkPosMpf {
public:
  // Inferred role: header of the position data of an etc mpf; original type name unknown.
  struct unknown001 {
    u8 _00[0x04];
    u32 unknown04; // Inferred role: first table offset; original member name unknown.
    u8 _08[0x0c - 0x08];
    u32 unknown0c; // Inferred role: second table offset; original member name unknown.
    u32 unknown10; // Inferred role: position num; original member name unknown.
  };

  DrResMdoSeamWrkPosMpf();
  u32 getDataSize() const;
  void setupMpfBasePos(const u8 *data);
  void setupMpfEtcPos(int index, DrResMdoSeamMemObj *memObj);
  void changeMemCall();

  const u8 *unknown00;           // Inferred role: first position table; original member name unknown.
  const u8 *unknown08;           // Inferred role: second position table; original member name unknown.
  const u8 *unknown10;           // Inferred role: position data; original member name unknown.
  u32 unknown18;                 // Inferred role: position num; original member name unknown.
  DrResMdoSeamMemObj *unknown20; // Inferred role: memory object; original member name unknown.
  s32 unknown28;                 // Inferred role: etc position index; original member name unknown.
};

static_assert(offsetof(DrResMdoSeamWrkPosMpf, unknown08) == 0x08, "");
static_assert(offsetof(DrResMdoSeamWrkPosMpf, unknown10) == 0x10, "");
static_assert(offsetof(DrResMdoSeamWrkPosMpf, unknown18) == 0x18, "");
static_assert(offsetof(DrResMdoSeamWrkPosMpf, unknown20) == 0x20, "");
static_assert(offsetof(DrResMdoSeamWrkPosMpf, unknown28) == 0x28, "");

} // namespace ml
