#pragma once
#include <stddef.h>

#include "grlib/cglib_vtl_mem_pool.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace ml {

class DrLightObjGlobalIBL;
class DrMan;

// Layout evidence: the constructor 0x71007d71cc, the destructor 0x71007d7210 and update 0x71007d77fc.
class DrGlobalIBLPack {
public:
  DrGlobalIBLPack(const void *data, int index);
  virtual ~DrGlobalIBLPack();
  void setup();
  void release();
  void update();
  static bool checkFileType(const void *data);

  enum Flag {
    FLAG_DISP_OFF = 1 << 0,
    FLAG_UNKNOWN_30 = 1 << 30, // Inferred role: release per buffer; original name unknown.
  };

  DrGlobalIBLPack *unknown08;                       // Inferred role: previous pack; original member name unknown.
  DrGlobalIBLPack *unknown10;                       // Inferred role: next pack; original member name unknown.
  int unknown18;                                    // Inferred role: view index; original member name unknown.
  const void *unknown20;                            // Inferred role: file data; original member name unknown.
  mm::mtl::Vector<DrLightObjGlobalIBL *> unknown28; // Inferred role: light objects; original member name unknown.
  u32 unknown50;                                    // Inferred role: flags; original member name unknown.
  u32 unknown54;                                    // Inferred role: flags of the previous update; original member name unknown.
  u8 unknown58;                                     // Inferred role: capture mode; original member name unknown.
  grlib::CGLibVtlMemPool unknown60;                 // Inferred role: gpu memory pool; original member name unknown.
};

static_assert(offsetof(DrGlobalIBLPack, unknown08) == 0x08, "");
static_assert(offsetof(DrGlobalIBLPack, unknown18) == 0x18, "");
static_assert(offsetof(DrGlobalIBLPack, unknown28) == 0x28, "");
static_assert(offsetof(DrGlobalIBLPack, unknown50) == 0x50, "");
static_assert(offsetof(DrGlobalIBLPack, unknown58) == 0x58, "");
static_assert(offsetof(DrGlobalIBLPack, unknown60) == 0x60, "");

class DrGlobalIBLMan {
public:
  DrGlobalIBLMan(DrMan *man, int index);
  DrGlobalIBLPack *createObj(const void *data);
  void releaseObj(DrGlobalIBLPack *pack);

  DrMan *unknown00;              // Inferred role: dr man; original member name unknown.
  s32 unknown08;                 // Inferred role: view index; original member name unknown.
  DrGlobalIBLPack *unknown10[8]; // Inferred role: packs; original member name unknown.
};

static_assert(offsetof(DrGlobalIBLMan, unknown10) == 0x10, "");
static_assert(sizeof(DrGlobalIBLMan) == 0x50, "");

} // namespace ml
