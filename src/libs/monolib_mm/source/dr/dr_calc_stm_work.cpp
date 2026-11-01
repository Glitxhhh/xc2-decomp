#include "dr/dr_calc_stm_work.h"

#include <new>

#include "grlib/cglib_texture_buffer.h"

namespace ml {

DrCalcStmWork::DrCalcStmWork() : unknown00(nullptr), unknown08(0), unknown10(nullptr) {}

int DrCalcStmWork::getWorkSize(u32 count) { return count * sizeof(grlib::CGLibTextureBuffer); }

int DrCalcStmWork::createWork(u8 *work, u32 count) {
  unknown08 = count;
  unknown00 = reinterpret_cast<grlib::CGLibTextureBuffer *>(work);
  for (int i = 0; i < unknown08; i++) {
    new (&unknown00[i]) grlib::CGLibTextureBuffer;
  }
  return getWorkSize(count);
}

grlib::CGLibTextureBuffer *DrCalcStmWork::getTexObj(u32 index) { return &unknown00[index]; }

void DrCalcStmWork::texRelease() {
  for (int i = 0; i < unknown08; i++) {
    unknown00[i].release();
  }
}

} // namespace ml
