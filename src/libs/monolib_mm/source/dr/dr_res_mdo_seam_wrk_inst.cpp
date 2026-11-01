#include "dr/dr_res_mdo_seam_wrk_inst.h"

namespace ml {

DrResMdoSeamWrkInst::DrResMdoSeamWrkInst()
    : unknown50(nullptr), unknown58(nullptr), unknown60(nullptr), unknown70(0), unknown74(0), unknown84(0), unknown88(0), unknown8a(0), unknown98(0), unknown108(nullptr), unknown118(nullptr),
      unknown128(nullptr), unknown130(nullptr), unknown140(0), unknown144(0), unknown156(0), unknown158(0), unknown1b0(nullptr), unknown1b8(nullptr) {}

DrResMdoSeamWrkInst::~DrResMdoSeamWrkInst() { release(); }

void DrResMdoSeamWrkInst::beginMdl() { unknown150 = 0; }

void DrResMdoSeamWrkInst::linkReadMdl() { unknown88 = 0; }

void DrResMdoSeamWrkInst::linkReadMdl(u32 index) {
  unknown88 = 0;
  unknownc8[index >> 5] |= 1 << (index & 0x1f);
}

u32 DrResMdoSeamWrkInst::isSubMdl(u32 index) {
  u32 bit = unknown20->unknown2c + index;
  return unknownd0[bit >> 5] & (1 << (bit & 0x1f));
}

DrResMdoSeamWrkInst::unknown002 *DrResMdoSeamWrkInst::getMdlInfo() {
  u16 index = unknown150;
  if (index < unknown14c) {
    unknown150 = index + 1;
    return &unknown1a0[index];
  }
  return nullptr;
}

} // namespace ml
