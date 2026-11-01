#pragma once
#include <stddef.h>

#include "dr/dr_pixl_post_obj.h"
#include "dr/dr_requet_ibl.h"
#include "mm_mtl/fixed_queue.h"
#include "types.h"

namespace ml {

class DrPixlPostObjCubeMapMultiIBL : public DrPixlPostObj {
public:
  void render();
  bool requestIBL(DrRequetIBL &request);
  void cancelIBL(u64 id);
  void outputPremToDDS();
  void update();
  void debugRender() const;
  u32 getPremMipCount() const;

  mm::mtl::FixedQueue<DrRequetIBL, 30> unknown18; // Inferred role: IBL requests; original member name unknown.
  u8 _5c8[0x5d8 - 0x5c8];
  u32 m_premMipCount;
};

static_assert(offsetof(DrPixlPostObjCubeMapMultiIBL, unknown18) == 0x18, "");
static_assert(offsetof(DrPixlPostObjCubeMapMultiIBL, m_premMipCount) == 0x5d8, "");

} // namespace ml
