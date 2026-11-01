#include "layer/layer_obj_top_def.h"

#include "grlib/cglib_dbl_uniform_block.h"
#include "grlib/cglib_texture_buffer.h"
#include "grlib/cglib_uniform_array.h"
#include "layer/layer_base.h"
#include "layer/layer_manager.h"
#include "layer/layer_obj_manager.h"
#include "layer/layer_obj_res_tex.h"
#include "layer/layer_sort_man.h"
#include "mm_mtl/fixstr.h"

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
