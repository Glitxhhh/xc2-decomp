#include "layer/layer_font_draw_buffer.h"

#include <new>
#include <string.h>

#include "grlib/cglib_dbl_uniform_block.h"
#include "grlib/cglib_vtx_one_instans.h"
#include "layer/layer_acc_font_style.h"
#include "layer/layer_font_icon_obj.h"
#include "layer/layer_font_res_obj.h"
#include "layer/layer_manager.h"
#include "layer/layer_obj_font.h"
#include "layer/layer_obj_sort_font.h"
#include "layer/layer_obj_util.h"
#include "mm_math/mm_col4.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace layer {
class LayerSortObj;

void LayerFontDrawBuffer::reset() {
  unknown68 = mm::Col4(1.0f, 1.0f, 1.0f, 0.0f);
  unknown78 = mm::Col4(1.0f, 1.0f, 1.0f, 0.0f);
  unknown4b8 = 0;
  unknown4bc = 0;
  unknown494[0] = -(unknown10->unknown70 * unknown20->unknown0c);
  unknown494[1] = -(unknown10->unknown70 * unknown20->unknown10);
  unknown49c = 0;
  unknown4c0[0] = 0;
  unknown4c0[1] = 0;
}

LayerResFontInfo *LayerFontDrawBuffer::createChar(const u8 *text) {
  LayerTagWork work = {};
  getWorkSize(work, text);
  createWorkBuffer(work, text);
  createWork(text);
  endWorkSetup();
  return unknown4a8;
}

void LayerFontDrawBuffer::createWorkBuffer(const LayerTagWork &work, const u8 *text) {
  u32 size = sizeof(LayerResFontInfo) + sizeof(LayerObjSortFont) + sizeof(grlib::CGLibVtxOneInstans) + sizeof(grlib::CGLibDblUniformBlock) + work.unknown08 * sizeof(u32) +
             (unknown49c + 1) * sizeof(unknown026) + work.unknown14;
  u8 *buffer = static_cast<u8 *>(mtl::MemManager::allocate(LayerManager::get()->unknown2c, size, 0x10, false, "no name", 0));
  unknown4a8 = reinterpret_cast<LayerResFontInfo *>(buffer);
  memset(unknown4a8, 0, sizeof(LayerResFontInfo));
  unknown4a8->unknown08 = unknown10;
  u32 offset = sizeof(LayerResFontInfo);
  unknown4a8->unknown38 = reinterpret_cast<LayerSortObj *>(buffer + offset);
  new (unknown4a8->unknown38) LayerObjSortFont(unknown4b0);
  offset += sizeof(LayerObjSortFont);
  unknown4a8->unknown60 = reinterpret_cast<grlib::CGLibVtxOneInstans *>(buffer + offset);
  offset += sizeof(grlib::CGLibVtxOneInstans);
  unknown4a8->unknown68 = reinterpret_cast<grlib::CGLibDblUniformBlock *>(buffer + offset);
  offset += sizeof(grlib::CGLibDblUniformBlock);
  unknown4a8->unknown20 = reinterpret_cast<u32 *>(buffer + offset);
  unknown4a8->unknown28 = work.unknown08;
  offset += work.unknown08 * sizeof(u32);
  unknown4a8->unknown30 = work.unknown0c;
  unknown4a8->unknown48 = reinterpret_cast<unknown026 *>(buffer + offset);
  unknown4a8->unknown50 = unknown49c;
  offset += (unknown49c + 1) * sizeof(unknown026);
  unknown4a8->unknown10 = buffer + offset;
  unknown4a8->unknown18 = work.unknown14;
  unknown4a8->unknown40 = work.unknown00 + work.unknown04;
  unknown4a8->unknown04 = (work.unknown00 + work.unknown04 + work.unknown0c) * sizeof(unknown001);
  unknown4a8->unknown2c = (work.unknown00 + work.unknown04) * sizeof(unknown001);
  unknown4a8->unknown58 = 0;
  new (unknown4a8->unknown60) grlib::CGLibVtxOneInstans();
  new (unknown4a8->unknown68) grlib::CGLibDblUniformBlock();
  unknown4a8->unknown68->setup(LayerObjUtil::getUniformBlockSizeAlOff(LAYER_UNI_TYPE_UNKNOWN_5));
  unknown4a8->unknown60->createInstansBuffer(unknown4a8->unknown04);
  unknown4a8->unknown00 |= 1;
  unknown4a8->unknown48[0].unknown00 = 0;
  unknown4a8->unknown48[0].unknown04 = -1;
  unknown4a8->unknown48[0].unknown06 = 0;
  unknown4a8->unknown48[0].unknown0c = -1;
  unknown4a8->unknown48[0].unknown0e = 0;
  unknown001 *instances = static_cast<unknown001 *>(unknown4a8->unknown60->getBuff());
  unknown48 = instances;
  unknown50 = instances;
  unknown001 *icons = reinterpret_cast<unknown001 *>(reinterpret_cast<u8 *>(instances) + unknown4a8->unknown2c);
  unknown58 = icons;
  unknown60 = icons;
  for (u32 i = 0; i < unknown4a8->unknown18; i++) {
    unknown4a8->unknown10[i] = text[i];
  }
}

LayerResFontInfo *LayerFontDrawBuffer::createChar(const wchar_t *text) {
  LayerTagWork work = {};
  getWorkSize(work, text);
  createWorkBuffer(work, reinterpret_cast<const u8 *>(text));
  createWork(text);
  endWorkSetup();
  return unknown4a8;
}

void LayerFontDrawBuffer::fontCnt() {
  unknown026 *line = &unknown4a8->unknown48[unknown49c];
  if (line->unknown04 == -1) {
    line->unknown04 = unknown4b8;
  }
  unknown4a8->unknown48[unknown49c].unknown06 = unknown4b8;
  unknown4b8++;
}

void LayerFontDrawBuffer::createFontIcon(u16 code) {
  if (unknown18 != nullptr && unknown49c < unknown20->unknown1a) {
    const LayerFontResObj::unknown002 *texture = unknown10->unknown58;
    f32 uv[6];
    unknown18->getFontUvParms(uv, code);
    unknown001 *instance = unknown60;
    f32 size[2];
    size[0] = uv[0] * unknown20->unknown10;
    size[1] = uv[1] * unknown20->unknown10;
    instance->unknown00[0] = size[0];
    instance->unknown00[1] = size[1];
    instance->unknown00[2] = unknown494[0];
    instance->unknown00[3] = unknown494[1];
    if (unknown38 == 0) {
      instance->unknown00[3] += ((static_cast<f32>(texture->unknown0c) - unknown10->unknown74) * unknown20->unknown10 - uv[1]) * 0.5f;
    } else {
      instance->unknown00[2] += ((static_cast<f32>(texture->unknown08) - unknown10->unknown74) * unknown20->unknown10 - uv[0]) * 0.5f;
    }
    instance->unknown00[4] = uv[2];
    instance->unknown00[5] = uv[3];
    instance->unknown00[6] = uv[4];
    instance->unknown00[7] = uv[5];
    unknown002(unknown60);
    u32 axis = unknown3c;
    if (unknown20->unknown18 >= unknown494[axis] + static_cast<s32>(size[axis])) {
      unknown494[axis] += static_cast<s32>(size[axis]) + unknown20->unknown1e;
      if (unknown4c0[axis] < unknown494[axis]) {
        unknown4c0[axis] = unknown494[axis];
      }
      s32 other = unknown494[unknown40] + static_cast<s32>(size[unknown40]) + unknown20->unknown1c;
      if (unknown4c0[unknown40] < other) {
        unknown4c0[unknown40] = other;
      }
      unknown4a8->unknown48[unknown49c].unknown00 = unknown494[axis];
      unknown026 *line = &unknown4a8->unknown48[unknown49c];
      if (line->unknown0c == -1) {
        line->unknown0c = unknown4bc;
      }
      unknown4a8->unknown48[unknown49c].unknown0e = unknown4bc;
      unknown60++;
      unknown4bc++;
    }
  }
}

void LayerFontDrawBuffer::createLineBreak() {
  const LayerFontResObj::unknown002 *texture = unknown10->unknown58;
  if (unknown38 == 0) {
    unknown494[0] = 0;
    unknown494[1] += static_cast<s32>((static_cast<f32>(texture->unknown0c) - unknown10->unknown74) * unknown20->unknown0c) + unknown20->unknown1c;
  } else {
    unknown494[1] = 0;
    s32 width = static_cast<s32>((static_cast<f32>(texture->unknown08) - unknown10->unknown74) * unknown20->unknown10);
    if (unknown38 == LAYER_FONT_SETTING_VERTICAL) {
      unknown494[0] -= unknown20->unknown1c + width;
    } else {
      unknown494[0] += unknown20->unknown1c + width;
    }
  }
  unknown49c++;
  unknown4a8->unknown48[unknown49c].unknown00 = 0;
  unknown4a8->unknown48[unknown49c].unknown04 = -1;
  unknown4a8->unknown48[unknown49c].unknown06 = 0;
  unknown4a8->unknown48[unknown49c].unknown0c = -1;
  unknown4a8->unknown48[unknown49c].unknown0e = 0;
}

} // namespace layer
