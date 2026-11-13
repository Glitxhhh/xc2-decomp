#include "dr/dr_light_obj_global_ibl.h"

#include "mm_math/mm_math.h"

#include "dr/dr_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_res_use_query_obj.h"
#include "grlib/cglib_ctl_vertex.h"

namespace ml {
class DrPixlOccQuery;

DrLightObjGlobalIBL::~DrLightObjGlobalIBL() {
  for (u32 i = 0; i < unknown20.size(); i++) {
    MeshData &mesh = unknown20[i];
    mesh.unknown00.release();
    mesh.unknown28.release();
    if (mesh.unknown110 != nullptr) {
      delete mesh.unknown110;
      mesh.unknown110 = nullptr;
    }
  }
}

int DrLightObjGlobalIBL::getPriority() const { return m_priority; }

void DrLightObjGlobalIBL::bindVertex(u32 index) {
  unknown70 = index;
  grlib::CGLibCtlVertex::setVertex(unknown20[index].unknown00);
}

void DrLightObjGlobalIBL::drawVertex() { unknown20[unknown70].unknown28.drawIndex(); }

void DrLightObjGlobalIBL::beginOccQuery() {
  DrPixlOccQuery *occQuery = DrMan::getIns()->unknown78->unknown7f8;
  unknown20[unknown70].unknown110->begin(occQuery);
}

void DrLightObjGlobalIBL::endOccQuery() { unknown20[unknown70].unknown110->end(); }

f32 DrLightObjGlobalIBL::calcSimilarity(const DrLightObjGlobalIBL &other) const {
  f32 similarity = 0.0f;
  for (int i = 0; i < 16; i++) {
    similarity += mm::fabs(unknown410[i] - other.unknown410[i]);
  }
  return similarity;
}

} // namespace ml

template void mm::mtl::Vector<ml::DrLightObjGlobalIBL *>::extend(size_t, size_t);
template void mm::mtl::Vector<ml::DrLightObjGlobalIBL *>::resize(size_t);
template void mm::mtl::Vector<ml::DrLightObjGlobalIBL::MeshData>::destroy();
