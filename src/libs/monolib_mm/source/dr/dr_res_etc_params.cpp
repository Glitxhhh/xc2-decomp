#include "dr/dr_res_etc_params.h"

#include <new>

#include "dr/dr_man.h"

namespace ml {

DrResEtcParams::DrResEtcParams() : unknown00(0), unknown04{0, 0}, unknown0c{0, 0}, m_params(0) {}

f32 DrResEtcParams::getParams() const { return m_params; }

void DrResEtcParams::setParams(f32 value) {
  unknown00 |= 1 << DrMan::s_nDblStockIdx;
  unknown04[DrMan::s_nDblStockIdx] = value;
}

void DrResEtcParams::setPreParams(f32 value) {
  unknown00 |= 4 << DrMan::s_nDblStockIdx;
  unknown0c[DrMan::s_nDblStockIdx] = value;
}

void DrResEtcParams::update() {
  if (unknown00 & (1 << DrMan::s_nDblMemIdx)) {
    unknown00 &= ~(1 << DrMan::s_nDblMemIdx);
    m_params = unknown04[DrMan::s_nDblMemIdx];
  }
  if (unknown00 & (4 << DrMan::s_nDblMemIdx)) {
    unknown00 &= ~(4 << DrMan::s_nDblMemIdx);
    m_params = unknown0c[DrMan::s_nDblMemIdx];
  }
}

DrResEtcPamObj::~DrResEtcPamObj() {}

int DrResEtcPamObj::setup(const u8 *data, u8 *work) {
  const unknown002 *header = reinterpret_cast<const unknown002 *>(data + reinterpret_cast<const unknown001 *>(data)->unknown84);
  unknown00 = header;
  unknown08 = reinterpret_cast<const unknown040 *>(reinterpret_cast<const u8 *>(header) + header->unknown00);
  unknown10 = reinterpret_cast<DrResEtcParams *>(work);
  unknown18 = header->unknown04;
  for (u32 i = 0; i < unknown18; i++) {
    new (&unknown10[i]) DrResEtcParams();
  }
  if (unknown00->unknown10 != 0) {
    const f32 *values = reinterpret_cast<const f32 *>(reinterpret_cast<const u8 *>(header) + unknown00->unknown10);
    for (u32 i = 0; i < unknown18; i++) {
      unknown10[i].setInitParams(values[i]);
    }
  }
  return unknown00->unknown04 * sizeof(DrResEtcParams) + sizeof(DrResEtcPamObj);
}

void DrResEtcPamObj::update() {
  for (u32 i = 0; i < unknown18; i++) {
    unknown10[i].update();
  }
}

void DrResEtcParams::setInitParams(f32 value) {
  unknown0c[1] = value;
  unknown0c[0] = value;
  unknown04[1] = value;
  unknown04[0] = value;
  m_params = value;
}

void DrResEtcPamObj::release(DrResEtcPamObj *&obj) {
  if (obj != nullptr) {
    obj = nullptr;
  }
}

int DrResEtcPamObj::calcWorkSize(const u8 *data) {
  const unknown001 *header = reinterpret_cast<const unknown001 *>(data);
  const unknown002 *params = reinterpret_cast<const unknown002 *>(data + header->unknown84);
  return params->unknown04 * sizeof(DrResEtcParams) + 0x20;
}

} // namespace ml
