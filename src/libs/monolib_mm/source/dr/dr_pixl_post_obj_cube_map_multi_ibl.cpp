#include "dr/dr_pixl_post_obj_cube_map_multi_ibl.h"

#include "dr/dr_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "mm_mtl/fixed_array.h"

namespace ml {

bool DrPixlPostObjCubeMapMultiIBL::requestIBL(DrRequetIBL &request) {
  if (!unknown00->unknown120[unknown00->unknown1c98]->unknown269 || unknown18.full()) {
    return false;
  }

  int count = 0;
  for (mm::mtl::FixedQueue<DrRequetIBL, 30>::iterator it = unknown18.begin(); it != unknown18.end(); ++it) {
    if ((*it).unknown20 == request.unknown20) {
      if (*(*it).unknown28 == 1) {
        return false;
      }
      if (++count == 4) {
        return false;
      }
    }
  }

  *request.unknown28 = 1;
  unknown18.push(request);
  return true;
}

void DrPixlPostObjCubeMapMultiIBL::cancelIBL(u64 id) {
  for (mm::mtl::FixedQueue<DrRequetIBL, 30>::iterator it = unknown18.begin(); it != unknown18.end(); ++it) {
    if ((*it).unknown20 == id) {
      *(*it).unknown28 = 3;
    }
  }
}

void DrPixlPostObjCubeMapMultiIBL::outputPremToDDS() {}

void DrPixlPostObjCubeMapMultiIBL::update() {}

void DrPixlPostObjCubeMapMultiIBL::debugRender() const {}

u32 DrPixlPostObjCubeMapMultiIBL::getPremMipCount() const { return m_premMipCount; }

} // namespace ml
