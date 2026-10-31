#pragma once
#include "mm_mtl/singleton.h"

namespace gf {

struct GF_OBJ_HANDLE;

class GfGameObjEnemy : public mm::mtl::PtrSingleton<GfGameObjEnemy> {
public:
  void enterEnemyObj(GF_OBJ_HANDLE *handle);
  void leaveEnemyObj(GF_OBJ_HANDLE *handle);
};

} // namespace gf
