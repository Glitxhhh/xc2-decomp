#include "layer/layer_obj_top_layout.h"

#include "dr/dr_draw_work_info.h"
#include "layer/layer_acc_layout_binary.h"
#include "layer/layer_acc_obj_base.h"
#include "layer/layer_base.h"
#include "layer/layer_manager.h"
#include "layer/layer_obj.h"
#include "layer/layer_obj_manager.h"
#include "layer/layer_obj_top_tex_obj.h"
#include "layer/layer_obj_util.h"
#include "layer/layer_shd_manager.h"
#include "layer/layer_sort_man.h"
#include "types.h"

namespace layer {

LayerObjTopLayout::LayerObjTopLayout(const void *data) : unknown400(this) {
  unknown18 = LAYER_OBJ_TYPE_LAYOUT;
  unknowna8 |= 0x20000;
  workLayoutCreate(data);
}

void LayerObjTopLayout::workLayoutCreate(const void *data) {
  unknownb8 = data;
  const u8 *base = static_cast<const u8 *>(data);
  const LayerAccLayoutBinary::unknown002 *header = static_cast<const LayerAccLayoutBinary::unknown002 *>(data);
  unknown2a0.unknown00 = base + header->unknown14;
  const LyrLayoutPosData *pos = reinterpret_cast<const LyrLayoutPosData *>(base + header->unknown1c);
  unknown2a0.unknown08 = pos;
  const LayerAccLayoutBinary::unknown003 *resNames = reinterpret_cast<const LayerAccLayoutBinary::unknown003 *>(base + header->unknown10);
  const LayerAccLayoutBinary::unknown001 *resTable = reinterpret_cast<const LayerAccLayoutBinary::unknown001 *>(base + resNames->unknown00);
  s32 posNum = header->unknown20;
  for (s32 i = 0; i < posNum; i++, pos++) {
    if (pos->unknown00 & 0x2) {
      u32 resOffset = resTable[pos->unknown0c].unknown04;
      LayerObj *object = static_cast<LayerObj *>(LayerObjManager::createStaticObj(static_cast<const u8 *>(unknownb8) + resOffset));
      f32 info[4];
      LayerObjUtil::getLayoutInfo(
          info, pos, static_cast<LayerCenterType>(object->unknown180.unknown18), static_cast<u16>(object->unknown180.unknown14), static_cast<u16>(object->unknown180.unknown16));
      object->setInitPosScl(info[0], info[1], info[2], info[3]);
      unknown258.unknown002(object);
    }
  }
  unknown180.unknown00 = 1.0f;
  unknown180.unknown04 = 1.0f;
  unknown180.unknown08 = 1.0f;
  unknown180.unknown0c = 1.0f;
  unknown180.unknown10 = 0;
  unknown180.unknown12 = 0;
  unknown180.unknown14 = 0;
  unknown180.unknown16 = 0;
}

LayerObjTopLayout::LayerObjTopLayout() : unknown400(this) {
  unknown18 = LAYER_OBJ_TYPE_LAYOUT;
  unknowna8 |= 0x20000;
}

LayerObjTopLayout::~LayerObjTopLayout() {
  baseRelease();
  workLayoutRelease();
  workListRelease();
}

void LayerObjTopLayout::setDrawList(LayerSortMan *sortMan, bool is3D) {
  if (unknowna8 & 0x90000) {
    return;
  }
  LayerSortMan *listSortMan = sortMan;
  bool listIs3D = is3D;
  if (unknown2a0.unknown30 != nullptr) {
    listSortMan = unknown2a0.unknown30;
    listIs3D = !(unknowna8 & 0x400) && is3D;
    listSortMan->begin(LayerManager::get()->unknown60->unknown00->unknownb0);
  }
  LayerBase *node = unknown258.unknown00;
  while (node != nullptr) {
    LayerBase *next = node->unknown10;
    static_cast<LayerObj *>(node)->setDrawList(listSortMan, listIs3D);
    node = next;
  }
  if (unknown2a0.unknown30 != nullptr) {
    listSortMan->end();
    if (is3D && (unknowna8 & 0x400)) {
      LayerManager::get()->unknown60->unknown10->set3DSpace(&unknown400, unknown200);
    } else {
      sortMan->set2DSpace(&unknown400, unknownc0);
    }
  } else if (unknown2a0.unknown118.unknown00 & 0x4) {
    if (is3D && (unknowna8 & 0x400)) {
      LayerManager::get()->unknown60->unknown10->set3DSpace(&unknown400, unknown200);
    } else {
      sortMan->set2DSpace(&unknown400, unknownc0);
    }
  }
}

void LayerObjTopLayout::finalRender() {
  if (unknown2a0.unknown30 != nullptr) {
    unknown2a0.unknown30->finalRender();
  }
  if ((unknown2a0.unknown118.unknown00 & 0xc) == 0xc) {
    LayerShdManager *shader = LayerManager::get()->unknown58;
    shader->setShaderMaskOff();
    shader->setupMainRenderTarget();
    shader->resetViewPort();
    LayerObjTopTexObj *texture = unknown2a0.unknown118.unknown20;
    if (!(texture->unknowna8 & 0x90000)) {
      texture->finalRender();
    }
  }
}

} // namespace layer
