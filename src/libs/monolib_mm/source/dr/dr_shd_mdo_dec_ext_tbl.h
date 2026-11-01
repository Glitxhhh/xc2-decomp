#pragma once
#include <stddef.h>

#include "grlib/cglib_dec_shd_ext_tbl.h"
#include "types.h"

namespace ml {
class DrShdMdoDecRes;

class DrShdMdoDecExtTbl : public grlib::CGLibDecShdExtTbl {
public:
  DrShdMdoDecExtTbl();
  ~DrShdMdoDecExtTbl();
  void setTextureParam(int num);
  u32 getValGlobalParam(int index);
  void bindShader();
  void setShaderParamAdd(u32 *param, u32 *globalParam);

  DrShdMdoDecRes *unknown18; // Inferred role: dec res; original member name unknown.
  u32 *unknown20;            // Inferred role: shader param add; original member name unknown.
  u32 *unknown28;            // Inferred role: global params; original member name unknown.
  u8 _30[0x36 - 0x30];
  u8 unknown36; // Inferred role: texture count; original member name unknown.
  u8 _37[0x38 - 0x37];
};

static_assert(offsetof(DrShdMdoDecExtTbl, unknown18) == 0x18, "");
static_assert(offsetof(DrShdMdoDecExtTbl, unknown28) == 0x28, "");
static_assert(offsetof(DrShdMdoDecExtTbl, unknown36) == 0x36, "");
static_assert(sizeof(DrShdMdoDecExtTbl) == 0x38, "");

} // namespace ml
