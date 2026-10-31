#pragma once
#include "grlib/cglib_texture_buffer.h"
#include "types.h"

namespace ml {

class DrPixlFormat {
public:
  static f32 getPixelScale(u32 format);

  static GrlDepthFormat s_ShadowFormat;
  static const f32 s_fPixelScale[19];
};

} // namespace ml
