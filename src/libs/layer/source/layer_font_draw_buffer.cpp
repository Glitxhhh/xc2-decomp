#include "layer/layer_font_draw_buffer.h"

#include "layer/layer_acc_font_style.h"
#include "layer/layer_font_res_obj.h"
#include "layer/layer_obj_font.h"
#include "mm_math/mm_col4.h"

namespace layer {

void LayerFontDrawBuffer::reset() {
  unknown68 = mm::Col4(1.0f, 1.0f, 1.0f, 0.0f);
  unknown78 = mm::Col4(1.0f, 1.0f, 1.0f, 0.0f);
  unknown4b8 = 0;
  unknown4bc = 0;
  unknown494[0] = -(unknown10->unknown70 * unknown20->unknown0c);
  unknown494[1] = -(unknown10->unknown70 * unknown20->unknown10);
  unknown49c = 0;
  unknown4c0 = 0;
  unknown4c4 = 0;
}

LayerResFontInfo *LayerFontDrawBuffer::createChar(const u8 *text) {
  LayerTagWork work = {};
  getWorkSize(work, text);
  createWorkBuffer(work, text);
  createWork(text);
  endWorkSetup();
  return unknown4a8;
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

} // namespace layer
