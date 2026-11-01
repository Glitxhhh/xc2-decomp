#pragma once
#include <stddef.h>

#include "dr/dr_shd_mdo_dec_res.h"
#include "grlib/cglib_shd_list.h"
#include "types.h"

namespace ml {
class DrCalcStmListObj;
struct MdsMatTechnique;

class DrShdMdoDecShdObj {
public:
  void update();
  void changeMemShader(const u8 *data, const u8 *vertexData, const MdsMatTechnique *technique);

  DrShdMdoDecShdObj *unknown00;                      // Inferred role: previous shader object; original member name unknown.
  DrShdMdoDecShdObj *unknown08;                      // Inferred role: next shader object; original member name unknown.
  const u8 *unknown10;                               // Inferred role: shader pack data; original member name unknown.
  s32 unknown18;                                     // Inferred role: reference count; original member name unknown.
  DrCalcStmListObj *unknown20;                       // Inferred role: stream list object; original member name unknown.
  grlib::CGLibShdListBase<DrShdMdoDecRes> unknown28; // Inferred role: shader list; original member name unknown.
};

static_assert(offsetof(DrShdMdoDecShdObj, unknown08) == 0x08, "");
static_assert(offsetof(DrShdMdoDecShdObj, unknown10) == 0x10, "");
static_assert(offsetof(DrShdMdoDecShdObj, unknown18) == 0x18, "");
static_assert(offsetof(DrShdMdoDecShdObj, unknown20) == 0x20, "");
static_assert(offsetof(DrShdMdoDecShdObj, unknown28) == 0x28, "");
static_assert(sizeof(DrShdMdoDecShdObj) == 0x80, "");

} // namespace ml
