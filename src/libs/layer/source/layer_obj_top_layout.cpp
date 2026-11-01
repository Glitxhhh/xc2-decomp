#include "layer/layer_obj_top_layout.h"

#include <math.h>

#include "dr/dr_draw_work_info.h"
#include "grlib/cglib_dbl_uniform_block.h"
#include "layer/layer_acc_layout_binary.h"
#include "layer/layer_acc_layout_obj.h"
#include "layer/layer_acc_obj_base.h"
#include "layer/layer_base.h"
#include "layer/layer_manager.h"
#include "layer/layer_obj.h"
#include "layer/layer_obj_manager.h"
#include "layer/layer_obj_top_mask_obj.h"
#include "layer/layer_obj_top_tex_obj.h"
#include "layer/layer_obj_util.h"
#include "layer/layer_render_view.h"
#include "layer/layer_res_view_port_info.h"
#include "layer/layer_shd_manager.h"
#include "layer/layer_sort_man.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_pnt.h"
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

void LayerObjTopLayout::apply(LayerSortMan *sortMan, const LayerRenderView *view) {
  updateFast();
  LayerResUpdateInfo info;
  if (!(unknowna8 & 0x10000)) {
    info.unknown50 = true;
    info.unknown00 = unknown20[unknownc2];
    info.unknown54 = static_cast<LAYER_SPACE_TYPE>(unknownc3);
    info.unknown58 = unknownc4;
    info.unknown5c.unknown001();
    info.unknown70 = static_cast<const LayerObjTopMaskObj *>(unknown240);
    updateSpace(info);
    updateBeginLayout(info, view);
    LayerResMatrix matrix;
    if (unknownc3 == LAYER_SPACE_TYPE_UNKNOWN_2) {
      LayerObjUtil::calcLayer3DSpaceTransRotScaleMatrix(matrix, unknownc8[2].unknown00);
    } else {
      LayerObjUtil::calcLayerTransRotScaleLaoutMatrix(matrix, unknownc8[2].unknown00, unknown180);
    }
    info.unknown40 = &matrix;
    info.unknown48 = &unknownc8[2].unknown1c;
    updateEndLayout(view, info);
    unknown170.unknown001();
    LayerObjUtil::calcLayoutDispInfo(unknown170, matrix, unknown180);
    setDrawList(sortMan, true);
  } else {
    info.unknown50 = false;
    info.unknown54 = static_cast<LAYER_SPACE_TYPE>(unknownc3);
    info.unknown58 = unknownc4;
    info.unknown70 = nullptr;
    updateDispOffLayout(info, view);
  }
}

void LayerObjTopLayout::updateFast() {
  addListInfo();
  updatePriTbl();
  updateCtrlSpd(1.0f);
  updateAction();
  updateDefPos();
  updateAnimObj();
}

void LayerObjTopLayout::updateDispOffLayout(LayerResUpdateInfo &info, const LayerRenderView *view) { unknown001(info, view); }

void LayerObjTopLayout::updateSpace(const LayerResUpdateInfo &info) {
  switch (info.unknown54) {
  case LAYER_SPACE_TYPE_UNKNOWN_1:
    LayerObjUtil::calcMatrixToZBuffPos(unknown200, unknown1fc, info.unknown00);
    unknowna8 |= 0x400;
    break;
  case LAYER_SPACE_TYPE_UNKNOWN_2:
    LayerObjUtil::calcMatrixToZBuffPos(unknown200, unknown1fc, info.unknown00);
    unknowna8 |= 0xc00;
    break;
  default:
    unknown1fc = 0.0f;
    break;
  }
}

void LayerObjTopLayout::updateBeginLayout(LayerResUpdateInfo &info, const LayerRenderView *view) {
  unknown001(info, view);
  f32 aspect = 1.0f;
  if (info.unknown5c.unknown00 == -100000.0f) {
    unknown180.unknown10 = 0;
    unknown180.unknown12 = 0;
    unknown180.unknown14 = 0;
    unknown180.unknown16 = 0;
  } else {
    const LayerShdManager *shader = LayerManager::get()->unknown58;
    unknown180.unknown10 = info.unknown5c.unknown08.x * shader->unknown530;
    unknown180.unknown12 = info.unknown5c.unknown08.y * shader->unknown534;
    unknown180.unknown14 = info.unknown5c.unknown00 * shader->unknown530;
    unknown180.unknown16 = info.unknown5c.unknown04 * shader->unknown534;
    unknown180.unknown14 -= unknown180.unknown10;
    unknown180.unknown16 -= unknown180.unknown12;
    if (unknown180.unknown14 != 0) {
      aspect = static_cast<f32>(unknown180.unknown16) / static_cast<f32>(unknown180.unknown14);
    }
  }
  unknown180.unknown0c = aspect;
  LayerBasePos &pos = unknownc8[2].unknown00;
  switch (unknown2a0.unknown20) {
  case LAYER_ANCHOR_UNKNOWN_1:
    if (fabsf(info.unknown5c.unknown00) >= 0.001f) {
      pos.unknown14 = info.unknown5c.unknown08.x / info.unknown5c.unknown00;
    } else {
      pos.unknown14 = 0.0f;
    }
    if (fabsf(info.unknown5c.unknown04) >= 0.001f) {
      pos.unknown18 = info.unknown5c.unknown08.y / info.unknown5c.unknown04;
    } else {
      pos.unknown18 = 0.0f;
    }
    break;
  case LAYER_ANCHOR_UNKNOWN_2:
    if (fabsf(info.unknown5c.unknown00) >= 0.001f) {
      f32 anchor = info.unknown5c.unknown08.x / info.unknown5c.unknown00;
      pos.unknown14 = anchor + (1.0f - anchor) * 0.5f;
    } else {
      pos.unknown14 = 0.0f;
    }
    if (fabsf(info.unknown5c.unknown04) >= 0.001f) {
      f32 anchor = info.unknown5c.unknown08.y / info.unknown5c.unknown04;
      pos.unknown18 = anchor + (1.0f - anchor) * 0.5f;
    } else {
      pos.unknown18 = 0.0f;
    }
    break;
  }
}

void LayerObjTopLayout::updateEndLayout(const LayerRenderView *view, LayerResUpdateInfo &info) {
  if (unknown3f8 != nullptr) {
    delete unknown3f8;
    unknown3f8 = nullptr;
  }
  LayerRenderView layoutView;
  const LayerRenderView *listView;
  if (unknown2a0.unknown118.unknown00 & 0x4) {
    LayerObjUtil::calcLayerRenderView(layoutView, unknown2a0.unknown38, unknown3f0, unknown2a0.unknown118.unknown04, view, info.unknown40);
    unknown2a0.unknown38.unknown10 = unknown2a0.unknown118.unknown18;
    unknown2a0.unknown38.unknown20 = unknown2a0.unknown118.unknown28;
    unknown2a0.unknown38.unknown30 = 0;
    listView = &layoutView;
  } else if (unknowna8 & 0x10) {
    LayerObjUtil::calcLayerRenderView(layoutView, unknown2a0.unknown38, unknown3f0, unknown2a0.unknown10, view, info.unknown40);
    unknown2a0.unknown38.unknown10 = nullptr;
    unknown2a0.unknown38.unknown30 = 0;
    listView = &layoutView;
  } else {
    unknown3f8 = unknown3f0;
    unknown3f0 = nullptr;
    listView = view;
  }
  LayerBase *node = unknown258.unknown00;
  while (node != nullptr) {
    LayerBase *next = node->unknown10;
    static_cast<LayerObj *>(node)->applyEnd(info, listView);
    node = next;
  }
  if (unknown2a0.unknown118.unknown00 & 0x4) {
    unknown2a0.unknown118.unknown20->applyEnd(info, view);
  }
}

void LayerObjTopLayout::applyBegin(LayerResUpdateInfo &info, const LayerRenderView *view) {
  updateFast();
  LayerResUpdateInfo child;
  if (!info.unknown50 || (unknowna8 & 0x10000)) {
    unknowna8 |= 0x10000;
    child.unknown50 = false;
    child.unknown70 = nullptr;
    updateDispOffLayout(child, view);
    return;
  }
  LAYER_SPACE_TYPE space = info.unknown54;
  if (space == LAYER_SPACE_TYPE_UNKNOWN_0) {
    space = static_cast<LAYER_SPACE_TYPE>(unknownc3);
  }
  child.unknown5c.unknown001();
  child.unknown50 = true;
  const LayerObjTopMaskObj *mask = static_cast<const LayerObjTopMaskObj *>(unknown240);
  if (mask == nullptr) {
    mask = info.unknown70;
  }
  child.unknown70 = mask;
  if (info.unknown54 == LAYER_SPACE_TYPE_UNKNOWN_0) {
    child.unknown54 = static_cast<LAYER_SPACE_TYPE>(unknownc3);
    child.unknown00 = unknown20[unknownc2];
  } else {
    child.unknown54 = info.unknown54;
    child.unknown00.unknown009(unknown20[unknownc2], info.unknown00);
  }
  if (unknownc4 == 5) {
    child.unknown58 = info.unknown58;
  } else {
    child.unknown58 = unknownc4;
  }
  updateSpace(child);
  updateBeginLayout(child, view);
  if (space == LAYER_SPACE_TYPE_UNKNOWN_2) {
    LayerObjUtil::calcLayer3DSpaceTransRotScaleMatrix(unknown1dc, unknownc8[2].unknown00);
  } else {
    LayerObjUtil::calcLayerTransRotScaleLaoutMatrix(unknown1dc, unknownc8[2].unknown00, unknown180);
  }
  LayerObjUtil::calcLayoutDispInfo(info.unknown5c, unknown1dc, unknown180);
}

void LayerObjTopLayout::applyEnd(LayerResUpdateInfo &info, const LayerRenderView *view) {
  if (unknowna8 & 0x10000) {
    return;
  }
  LayerResMatrix matrix;
  LayerObjUtil::calcLayerMatrix(matrix, unknown1dc, *info.unknown40);
  LayerResColor color;
  LayerObjUtil::calcLayerColor(color, unknownc8[2].unknown1c, *info.unknown48);
  LayerResUpdateInfo child;
  child.unknown40 = &matrix;
  child.unknown48 = &color;
  child.unknown50 = true;
  child.unknown58 = unknownc4;
  const LayerObjTopMaskObj *mask = static_cast<const LayerObjTopMaskObj *>(unknown240);
  if (mask == nullptr) {
    mask = info.unknown70;
  }
  child.unknown70 = mask;
  updateEndLayout(view, child);
  unknown170.unknown001();
  LayerObjUtil::calcLayoutDispInfo(unknown170, matrix, unknown180);
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
