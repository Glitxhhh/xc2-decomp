#include "dr/dr_pixl_format.h"

#include "dr/dr_man.h"

namespace ml {

const f32 DrPixlFormat::s_fPixelScale[19] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 0.5f, 0.5f, 0.5f, 1.0f, 0.5f, 1.0f, 0.5f, 1.0f, 1.0f};

f32 DrPixlFormat::getPixelScale(u32 format) {
  // Inferred role: formats 9 and 14 follow the IBL resolution instead of the table.
  if (format == 14 || format == 9) {
    return DrMan::getIns()->isIBLHalfRes() ? 0.5f : 1.0f;
  }
  return s_fPixelScale[format];
}

} // namespace ml
