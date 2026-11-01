#pragma once
#include <stddef.h>

#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace grlib {
class CGLibVtxInstans;
} // namespace grlib

namespace ml {
class DrCalcViewWork;

// Inferred layout from DrResMdoSeamWrkMpf::calcMpfMatSetup (0x18 byte stride); member names unknown.
struct MdsMpfObjData {
  u8 _00[0x06];
  u16 unknown06; // Inferred role: object type; original member name unknown.
  u8 _08[0x18 - 0x08];
};

static_assert(offsetof(MdsMpfObjData, unknown06) == 0x06, "");
static_assert(sizeof(MdsMpfObjData) == 0x18, "");

class DrMdoCtlMpfWork {
public:
  // Inferred role: object select buffer; original type name unknown.
  struct unknown001 {
    u8 _00[0x20];
    u16 unknown20; // Inferred role: object check; original member name unknown.
    u8 _22[0x40 - 0x22];
  };

  DrMdoCtlMpfWork();
  static int calcRenderListWork(int count, const MdsMpfObjData *data);
  void changeMemWork(const MdsMpfObjData *data);
  u32 getObjChk(int index);
  void createAutoList(int index, DrCalcViewWork *view, grlib::CGLibVtxInstans *instans);
  void createPosList(int index, grlib::CGLibVtxInstans *instans);

  u8 _00[0x20 - 0x00];
  unknown001 *unknown20; // Inferred role: object select buffers; original member name unknown.
  u8 _28[0x38 - 0x28];
  const MdsMpfObjData *unknown38; // Inferred role: object data; original member name unknown.
};

static_assert(sizeof(DrMdoCtlMpfWork::unknown001) == 0x40, "");
static_assert(offsetof(DrMdoCtlMpfWork::unknown001, unknown20) == 0x20, "");
static_assert(offsetof(DrMdoCtlMpfWork, unknown20) == 0x20, "");
static_assert(offsetof(DrMdoCtlMpfWork, unknown38) == 0x38, "");

// Name from the symbols (DrMdoCtlMpfWindCalc::init, calcUpdate); layout from init and DrMdoMpfMan's ctor (0xf0 byte stride).
class DrMdoCtlMpfWindCalc {
public:
  void init();

  mm::Vec3 unknown00[3]; // Inferred role: joint positions; original member name unknown.
  mm::Vec3 unknown30[3]; // Inferred role: joint velocities; original member name unknown.
  mm::Vec3 unknown60;    // Inferred role: wind direction; original member name unknown.
  mm::Mat44 unknown70;   // Inferred role: matrix; original member name unknown.
  mm::Mat44 unknownb0;   // Inferred role: matrix; original member name unknown.
};

static_assert(offsetof(DrMdoCtlMpfWindCalc, unknown60) == 0x60, "");
static_assert(offsetof(DrMdoCtlMpfWindCalc, unknown70) == 0x70, "");
static_assert(offsetof(DrMdoCtlMpfWindCalc, unknownb0) == 0xb0, "");
static_assert(sizeof(DrMdoCtlMpfWindCalc) == 0xf0, "");

} // namespace ml
