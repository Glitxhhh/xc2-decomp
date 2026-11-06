#include "dr/dr_res_mdo_vtx_mesh_obj.h"

#include <string.h>

#include "dr/dr_man.h"
#include "dr/dr_res_mdo_vertex.h"
#include "grlib/cglib_vtx_vertex.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace ml {

void DrResMdoVtxMeshObj::updateInit(const mm::Mat44 &matrix) {
  u32 flags = unknown74;
  u32 startBit = 0x10000 << DrMan::s_nDblIdx;
  if (flags & startBit) {
    flags &= ~startBit;
    unknown74 = flags;
    unknown70 = true;
  }
  u32 stopBit = 0x40000 << DrMan::s_nDblIdx;
  bool isStop = (flags & stopBit) != 0;
  if (isStop) {
    flags &= ~stopBit;
    unknown74 = flags;
    unknown70 = false;
  }
  if (!isStop && unknown70 && unknown130 > 0.01f) {
    unknown74 = (unknown74 & ~0xd) | 1;
  } else if (unknown74 & 1) {
    unknown74 |= 8;
    if (unknown74 & 4) {
      unknown74 &= ~1;
    }
  }
  if (!(unknown74 & 1)) {
    if (unknown74 & 2) {
      releaseWork();
    }
    unknown74 &= ~0xf;
  } else if (!(unknown74 & 2)) {
    unknown10.setup(unknown84 << 5);
    unknown10.updateData();
    unknown38.setup(0x130);
    unknown78 = mtl::MemManager::allocate(DrMan::get()->unknown14, static_cast<size_t>(unknown84) << 3, 4, false, "no name", 0);
    unknown74 |= 2;
    memcpy(&unknowna0, &matrix, sizeof(mm::Mat44));
  }
}

DrResMdoVtxMeshObj::~DrResMdoVtxMeshObj() { releaseWork(); }

void DrResMdoVtxMeshObj::setActive(bool isActive, u32 index) {
  if (isActive) {
    if (!unknown70) {
      unknown74 |= 0x10000 << DrMan::s_nDblStockIdx;
      unknown74 &= ~(0x40000 << DrMan::s_nDblIdx);
      unknown84 = index;
    }
  } else {
    unknown74 |= 0x40000 << DrMan::s_nDblStockIdx;
    unknown74 &= ~(0x10000 << DrMan::s_nDblIdx);
  }
}

void DrResMdoVtxMeshObj::update(const mm::Mat44 &matrix, f32 param2, f32 param3) {
  updateInit(matrix);
  if ((unknown74 & 1) && unknown80 != 0) {
    updateCount(param3);
    updateUniform(matrix, param2, param3);
    memcpy(&unknowna0, &matrix, sizeof(mm::Mat44));
  }
}

void DrResMdoVtxMeshObj::release(DrResMdoVtxMeshObj *&obj) {
  if (obj != nullptr) {
    obj->~DrResMdoVtxMeshObj();
    obj = nullptr;
  }
}

void DrResMdoVtxMeshObj::resourceInit(DrResMdoVertex *vertex) {
  unknown056 *uniformVertex = vertex->unknown70;
  unknown00 = uniformVertex->unknown00;
  unknown08 = uniformVertex->unknown08;
  unknown80 = unknown00->unknown08;
}

void DrResMdoVtxMeshObj::releaseWork() {
  unknown10.release();
  unknown38.release();
  if (unknown78 != nullptr) {
    mtl::MemManager::deallocate(unknown78, 0, false);
    unknown78 = nullptr;
  }
}

bool DrResMdoVtxMeshObj::isRender() const {
  if (!(unknown74 & 1)) {
    return false;
  }
  if (unknown8c == 0 && unknown94 == 0) {
    return false;
  }
  return true;
}

u32 DrResMdoVtxMeshObj::setup(const u8 *, u8 *) { return 0x140; }

u32 DrResMdoVtxMeshObj::calcWorkSize(const u8 *) { return 0x140; }

} // namespace ml
