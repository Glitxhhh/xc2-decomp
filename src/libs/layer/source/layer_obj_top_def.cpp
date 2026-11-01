#include "layer/layer_obj_top_def.h"

#include <new>

#include "grlib/cglib_dbl_uniform_block.h"
#include "grlib/cglib_texture_buffer.h"
#include "grlib/cglib_uniform_array.h"
#include "grlib/cglib_vtx_instans.h"
#include "layer/layer_acc_obj_base.h"
#include "layer/layer_base.h"
#include "layer/layer_manager.h"
#include "layer/layer_obj_draw.h"
#include "layer/layer_obj_manager.h"
#include "layer/layer_obj_res_tex.h"
#include "layer/layer_obj_util.h"
#include "layer/layer_shd_manager.h"
#include "layer/layer_sort_man.h"
#include "layer/layer_texture_obj.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_pnt.h"
#include "mm_mtl/fixstr.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"
#include "types.h"

namespace layer {

LayerObjTopDef::LayerObjTopDef(const char *name) : unknown308(this) {
  unknownb8 = nullptr;
  unknown18 = LAYER_OBJ_TYPE_OBJ;
  unknown258 = name;
  unknown290 = nullptr;
  unknowna8 |= 0x60000;
}

LayerObjTopDef::LayerObjTopDef(const void *data) : unknown308(this) {
  unknownb8 = data;
  unknown18 = LAYER_OBJ_TYPE_OBJ;
  unknowna8 |= 0x20000;
  unknown290 = nullptr;
  workIconCreate();
}

void LayerObjTopDef::workIconCreate() {
  const unknown013 *header = static_cast<const unknown013 *>(unknownb8);
  const u8 *base = static_cast<const u8 *>(unknownb8);
  const unknown014 *drawData = reinterpret_cast<const unknown014 *>(base + header->unknown14);
  const unknown016 *drawList = reinterpret_cast<const unknown016 *>(base + header->unknown1c);
  const unknown016 *iconList = reinterpret_cast<const unknown016 *>(base + header->unknown20);
  const unknown015 *placeData = reinterpret_cast<const unknown015 *>(base + header->unknown18);
  const u8 *drawEntries = reinterpret_cast<const u8 *>(drawList) + drawList->unknown00;
  const u8 *placeTable = reinterpret_cast<const u8 *>(placeData) + placeData->unknown04;
  const unknown017 *icons = reinterpret_cast<const unknown017 *>(reinterpret_cast<const u8 *>(iconList) + iconList->unknown00);
  const LyrMeshData *meshes = reinterpret_cast<const LyrMeshData *>(reinterpret_cast<const u8 *>(drawData) + drawData->unknown00);
  if (header->unknown24 != 0) {
    unknown278 = LayerManager::get()->unknown58->unknown40->createTextureObj(base + header->unknown24);
    unknown288 = unknown278->unknown2c;
  } else {
    unknown288 = 0;
  }
  u32 size =
      sizeof(unknown002) + header->unknown28 * sizeof(unknown003) + iconList->unknown04 * sizeof(u32) + drawList->unknown04 * sizeof(unknown009) + unknown288 * sizeof(grlib::CGLibTextureBuffer *);
  u32 actionSize = 0;
  if (header->unknown08 & 0x20) {
    actionSize = calcActionWorkSize(static_cast<const u8 *>(unknownb8) + header->unknown34);
    size += actionSize;
  }
  if (header->unknown08 & 0x4) {
    unknowna8 |= 0x2;
    size += sizeof(unknown008) + sizeof(grlib::CGLibVtxInstans);
  }
  if (header->unknown08 & 0x10) {
    u32 color = header->unknown30;
    setInitMulCol(mm::Col4((color & 0xff) / 255.0f, ((color >> 8) & 0xff) / 255.0f, ((color >> 16) & 0xff) / 255.0f, (color >> 24) / 255.0f));
  }
  size += sizeof(grlib::CGLibUniformArray<grlib::CGLibDblUniformBlock>);
  unknown290 = mtl::MemManager::allocate(LayerManager::get()->unknown2c, size, 0x10, false, "no name", 0);
  unknown298 = static_cast<unknown002 *>(unknown290);
  u32 offset = sizeof(unknown002);
  unknown2b0 = reinterpret_cast<unknown003 *>(static_cast<u8 *>(unknown290) + offset);
  offset += header->unknown28 * sizeof(unknown003);
  u32 *iconStates = reinterpret_cast<u32 *>(static_cast<u8 *>(unknown290) + offset);
  offset += iconList->unknown04 * sizeof(u32);
  unknown009 *drawWorks = reinterpret_cast<unknown009 *>(static_cast<u8 *>(unknown290) + offset);
  offset += drawList->unknown04 * sizeof(unknown009);
  unknown2ac = header->unknown38;
  unknown298->unknown00 = reinterpret_cast<const unknown001 *>(static_cast<const u8 *>(unknownb8) + header->unknown0c);
  unknown298->unknown08 = reinterpret_cast<const u8 *>(drawData) + drawData->unknown10;
  unknown298->unknown10 = reinterpret_cast<const u8 *>(drawData) + drawData->unknown08;
  unknown298->unknown18 = reinterpret_cast<const u8 *>(drawData) + drawData->unknown00;
  unknown298->unknown50 = iconList->unknown04;
  unknown298->unknown40 = drawList->unknown04;
  unknown298->unknown28 = placeTable;
  unknown298->unknown20 = reinterpret_cast<const u8 *>(placeData);
  unknown298->unknown30 = reinterpret_cast<const u8 *>(drawData);
  unknown298->unknown38 = drawEntries;
  unknown298->unknown48 = reinterpret_cast<const u8 *>(icons);
  unknown298->unknown60 = iconStates;
  unknown298->unknown70 = drawWorks;
  u16 iconMax = 0;
  if (header->unknown08 & 0x2) {
    iconMax = reinterpret_cast<const unknown018 *>(static_cast<const u8 *>(unknownb8) + header->unknown2c)->unknown00;
  }
  unknown2a6 = iconMax;
  for (s32 i = 0; i < iconList->unknown04; i++) {
    iconStates[i] = 0;
  }
  for (s32 i = 0; i < drawList->unknown04; i++) {
    drawWorks[i].unknown00 = mm::Pnt<f32>(0.0f, 0.0f);
    drawWorks[i].unknown08 = mm::Pnt<f32>(1.0f, 1.0f);
    drawWorks[i].unknown10 = mm::Pnt<f32>(0.0f, 0.0f);
    drawWorks[i].unknown18 = mm::Pnt<f32>(1.0f, 1.0f);
    drawWorks[i].unknown20 = mm::Pnt<f32>(1.0f, 1.0f);
    drawWorks[i].unknown28 = mm::Pnt<f32>(0.0f, 0.0f);
    drawWorks[i].unknown30 = mm::Pnt<f32>(0.0f, 0.0f);
  }
  if (unknown288 != 0) {
    unknown280 = reinterpret_cast<grlib::CGLibTextureBuffer **>(static_cast<u8 *>(unknown290) + offset);
    setupDefTexList();
    offset += unknown288 * sizeof(grlib::CGLibTextureBuffer *);
  }
  if (header->unknown08 & 0x20) {
    setupAction(static_cast<u8 *>(unknown290) + offset, static_cast<const u8 *>(unknownb8) + header->unknown34);
    offset += actionSize;
  }
  if (header->unknown08 & 0x4) {
    unknown008 *instance = reinterpret_cast<unknown008 *>(static_cast<u8 *>(unknown290) + offset);
    offset += sizeof(unknown008);
    instance->unknown00 = reinterpret_cast<grlib::CGLibVtxInstans *>(static_cast<u8 *>(unknown290) + offset);
    new (instance->unknown00) grlib::CGLibVtxInstans();
    offset += sizeof(grlib::CGLibVtxInstans);
    instance->unknown00->createInstansBuffer(0x400);
    unknown298->unknown78 = instance;
  } else {
    unknown298->unknown78 = nullptr;
  }
  unknown298->unknown58 = nullptr;
  grlib::CGLibUniformArray<grlib::CGLibDblUniformBlock> *uniforms = new (static_cast<u8 *>(unknown290) + offset) grlib::CGLibUniformArray<grlib::CGLibDblUniformBlock>();
  uniforms->setupArray(iconList->unknown04);
  uniforms->unknown0c = 0;
  for (s32 i = 0; i < iconList->unknown04; i++) {
    u32 blockSize = LayerObjUtil::getUniformBlockSizeAlOff(static_cast<LayerUniType>(meshes[icons[i].unknown00].unknown02));
    uniforms->unknown0c += (blockSize + (0x100 - blockSize % 0x100) % 0x100) * 2;
  }
  uniforms->unknown002();
  for (s32 i = 0; i < iconList->unknown04; i++) {
    u32 blockSize = LayerObjUtil::getUniformBlockSizeAlOff(static_cast<LayerUniType>(meshes[icons[i].unknown00].unknown02));
    uniforms->unknown0c += (*uniforms)[i].setupArray(blockSize, uniforms->unknown18, uniforms->unknown0c);
  }
  unknown298->unknown68 = uniforms;
  calcFrmParm(header->unknown28);
  unknowna8 |= 0x1;
  unknown180.unknown00 = unknown298->unknown00->unknown10;
  unknown180.unknown04 = unknown298->unknown00->unknown14;
  unknown180.unknown08 = 1.0f;
  unknown180.unknown0c = static_cast<f32>(unknown298->unknown00->unknown0c) / static_cast<f32>(unknown298->unknown00->unknown04);
  unknown180.unknown10 = 0;
  unknown180.unknown12 = 0;
  unknown180.unknown14 = unknown298->unknown00->unknown04;
  unknown180.unknown16 = unknown298->unknown00->unknown0c;
  if (unknown2ac == 5) {
    unknownc6 = LAYER_TEX_FILTER_TYPE_LINEAR;
  }
}

LayerObjTopDef::~LayerObjTopDef() {
  if (unknown290 != nullptr) {
    unknown298->unknown68->unknown001();
  }
  baseRelease();
  workRelease();
}

void LayerObjTopDef::setDrawList(LayerSortMan *sortMan, bool is3D) {
  if (unknowna8 & 0x90000) {
    return;
  }
  if (is3D) {
    if (unknowna8 & 0x400) {
      LayerManager::get()->unknown60->unknown10->set3DSpace(&unknown308, unknown200);
    } else if (!isClip()) {
      sortMan->set2DSpace(&unknown308, unknownc0);
    }
  } else if (!isClip()) {
    sortMan->set2DSpace(&unknown308, unknownc0);
  }
}

void LayerObjTopDef::updateResCheck() {
  if (unknown2c0.updateTexutre(unknown280, unknown278)) {
    unknowna8 &= ~0x400000;
    GrlSurfaceFormat format = unknown280[0]->getFormat();
    if (format == GRL_SURFACE_FORMAT_BPTC_UNORM || format == GRL_SURFACE_FORMAT_BPTC_SIGNED_FLOAT || format == GRL_SURFACE_FORMAT_BPTC_UNSIGNED_FLOAT) {
      unknowna8 |= 0x400000;
    }
  }
}

void LayerObjTopDef::alphaRender() {}

void LayerObjTopDef::lastRender() {}

} // namespace layer
