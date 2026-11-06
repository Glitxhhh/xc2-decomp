#pragma once
#include "gf/data/gf_data_system.h"
#include "types.h"
#include <stddef.h>

namespace gf {

constexpr float VOLUME_SCALE = 255.0f;

struct SSoundUiOption {
  SSoundUiOption() { clear(); }
  void clear();
  bool isDirty(const SSoundUiOption &other);

  u16 unknown00; // Inferred role: event voice volume; original member name unknown.
  u16 unknown02; // Inferred role: event cs volume; original member name unknown.
  u16 unknown04; // Inferred role: event bgm volume; original member name unknown.
  u16 unknown06; // Inferred role: event se volume; original member name unknown.
  u16 unknown08; // Inferred role: game bgm volume; original member name unknown.
  u16 unknown0a; // Inferred role: game env volume; original member name unknown.
  u16 unknown0c; // Inferred role: game weather volume; original member name unknown.
  u16 unknown0e; // Inferred role: game se volume; original member name unknown.
  u16 unknown10; // Inferred role: player voice volume; original member name unknown.
  u16 unknown12; // Inferred role: enemy voice volume; original member name unknown.
  u16 unknown14; // Inferred role: nare voice volume; original member name unknown.
  u16 unknown16; // Inferred role: system volume; original member name unknown.
  u16 unknown18; // Inferred role: menu bgm volume; original member name unknown.
  u16 _1a;
  bool _1c;
  u8 _1d;
};

static_assert(offsetof(SSoundUiOption, unknown18) == 0x18, "");
static_assert(offsetof(SSoundUiOption, _1a) == 0x1a, "");
static_assert(offsetof(SSoundUiOption, _1c) == 0x1c, "");
static_assert(sizeof(SSoundUiOption) == 0x1e, "");

struct SDataOption {
  SDataOption() : unknown00(SAVE_DATA_VERSION), _04(0), _08(0), _09(0), _0a(0), _0b(true), _0c() {}

  u32 unknown00; // Inferred role: version; original member name unknown.
  u32 _04;
  u8 _08;
  u8 _09;
  u8 _0a;
  bool _0b;
  u8 _0c[0x4c - 0x0c];
  SSoundUiOption unknown4c; // Inferred role: sound and screen options; original member name unknown.
  u8 _6a[0x88 - 0x6a];
};

static_assert(offsetof(SDataOption, _08) == 0x08, "");
static_assert(offsetof(SDataOption, _0c) == 0x0c, "");
static_assert(offsetof(SDataOption, unknown4c) == 0x4c, "");
static_assert(offsetof(SDataOption, _6a) == 0x6a, "");
static_assert(sizeof(SDataOption) == 0x88, "");

} // namespace gf
