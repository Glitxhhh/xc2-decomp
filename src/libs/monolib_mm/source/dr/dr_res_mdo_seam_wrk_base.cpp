#include "dr/dr_res_mdo_seam_wrk_base.h"

#include <string.h>

#include "dr/dr_mdo_ctl_seam_base_map.h"
#include "dr/dr_mdo_mat.h"
#include "dr/dr_res_mdo_seam_wrk_base_vertex.h"
#include "dr/dr_res_mdo_vertex.h"

namespace ml {

DrResMdoSeamWrkBaseVertex::DrResMdoSeamWrkBaseVertex() : unknown00(nullptr), unknown08(nullptr) {}

void DrResMdoSeamWrkBaseVertex::release() {
  DrResMdoVertex *vertex = unknown08;
  if (vertex != nullptr) {
    vertex->vertexRelease();
    ::operator delete(vertex);
    unknown08 = nullptr;
  }
  unknown00 = nullptr;
}

void DrResMdoSeamWrkBaseVertex::changeMemVertex() { unknown08->changeMemVertex(unknown00->m_buffer); }

DrResMdoSeamWrkBase::DrResMdoSeamWrkBase()
    : unknown68(nullptr), unknown70(nullptr), unknown78(nullptr), unknown98(0), unknowna0(0), unknownb0(0), unknownb4(0), unknowne0(nullptr), unknowne8(nullptr), unknown158(nullptr),
      unknown168(nullptr), unknown17a(0), unknown17c(0), unknown17e(0) {}

DrResMdoSeamWrkBase::~DrResMdoSeamWrkBase() { release(); }

void DrResMdoSeamWrkBase::releaseCache(DrMdoCtlSeamBaseMap *ctl) {
  if (unknown78 != nullptr) {
    for (int i = 0; i < unknown17e; i++) {
      DrResMdoSeamMemObj *memObj = unknown78[i].unknown00;
      unknown78[i].release();
      if (memObj != nullptr) {
        ctl->releaseFreeSeamMemObj(memObj);
      }
    }
  }
  unknown78 = nullptr;
  unknowne0 = nullptr;
  unknowne8 = nullptr;
  unknown17e = 0;
  release();
}

void DrResMdoSeamWrkBase::beginBaseMapRenderList() {
  unknown94 = 0;
  unknown170 = 0;
  unknown8c = 0;
  unknown90 = 0;
  memset(unknown110, 0, unknown174);
}

void DrResMdoSeamWrkBase::callShadowCacheBaseUpdate(u64 mask) {
  for (int i = 0; i < 0x24; i++) {
    if ((1ull << i) & mask) {
      memset(unknownf0[i], 0, unknownf8);
    }
  }
  unknown98 &= ~mask;
}

void DrResMdoSeamWrkBase::beginRender() {
  unknown178 = -1;
  unknown68->unknownc8 = nullptr;
}

void DrResMdoSeamWrkBase::endRender() { unknown68->unknownc8 = nullptr; }

void DrResMdoSeamWrkBase::selectVertex(int index) {
  if (unknown178 != index) {
    unknown68->unknownc8 = unknown78[index].unknown08;
    unknown68->unknownc8->unknown4e = -1;
    unknown178 = index;
  }
}

void DrResMdoSeamWrkBase::seachDefShadowBaseMapRender(DrPixlShadowObj *shadow, DrMdoCtlSeamBaseMap *ctl) {
  if (!(unknown20->unknown00 & 4)) {
    beginRender();
    seachDefShadowBaseMapRenderChild(shadow, ctl, unknown38);
    endRender();
  }
}

void DrResMdoSeamWrkBase::stockRenderListBaseMap(int base, u32 kind, u32 index, u32 vertex, bool isAlpha, int unknown) {
  unknown504 *entry = &unknown150[unknown170];
  int slot = base + kind;
  if (isAlpha) {
    if (unknown128[slot] == nullptr) {
      unknown118[unknown138[kind] + unknown68->unknown30 * kind] = entry;
      unknown138[kind]++;
    } else {
      unknown128[slot]->unknown04 = unknown170 + 1;
    }
    unknown128[slot] = entry;
  } else {
    if (unknown120[slot] == nullptr) {
      unknown110[unknown130[kind] + unknown68->unknown30 * kind] = entry;
      unknown130[kind]++;
    } else {
      unknown120[slot]->unknown04 = unknown170 + 1;
    }
    unknown120[slot] = entry;
  }
  entry->unknown08 = unknown;
  entry->unknown00 = index;
  entry->unknown06 = vertex;
  entry->unknown04 = 0;
  unknown170++;
}

} // namespace ml
