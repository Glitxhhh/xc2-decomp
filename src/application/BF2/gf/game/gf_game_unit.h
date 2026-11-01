#pragma once
#include "mm_mtl/fixed_vector.h"

namespace gf {

struct GF_OBJ_HANDLE;
struct RQ_SETUP_PARTY;

class GfGameUnit {
public:
  static void destroyParty(const RQ_SETUP_PARTY &info, mm::mtl::FixedVector<GF_OBJ_HANDLE *, 32> *handles);
};

} // namespace gf
