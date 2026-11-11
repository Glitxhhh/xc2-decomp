#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {

class DrCalcTexStmObj;
class EventFileTh;

// Original type name from the symbol _ZN2ml16DrCalcStmListObj10callUpdateERNS_17DrStmListAfterArgE.
// Layout evidence: DrCalcTexStreamMan::afterUpdate 0x71008b2ac4, DrCalcStmListObj::callUpdate 0x71008b3f38.
struct DrStmListAfterArg {
  bool unknown00; // Role and original member name unknown.
  bool unknown01; // Inferred role: memory budget check on; original member name unknown.
  s32 unknown04;  // Inferred role: remaining memory budget; original member name unknown.

  // Inferred role: subtracts a size from the remaining budget, clamped at zero; original function name unknown.
  // Evidence: the same block repeats in DrCalcStmListObj::callUpdate, afterUpdate and memChkUpdate.
  void unknown036(s32 size) {
    s32 rest = unknown04 - size;
    if (rest < 0) {
      rest = 0;
    }
    unknown04 = rest;
  }
};

static_assert(offsetof(DrStmListAfterArg, unknown01) == 0x01, "");
static_assert(offsetof(DrStmListAfterArg, unknown04) == 0x04, "");
static_assert(sizeof(DrStmListAfterArg) == 0x08, "");

// Inferred role: calc stm res; original type name unknown.
struct unknown035 {
  const u8 *unknown00; // Inferred role: data; original member name unknown.
  u8 _08[0x10 - 0x08];
  u8 unknown10; // Inferred role: flags; original member name unknown.
  u8 _11[0x18 - 0x11];
};

static_assert(offsetof(unknown035, unknown10) == 0x10, "");
static_assert(sizeof(unknown035) == 0x18, "");

class DrCalcStmListObj {
public:
  enum DrTexUseMode {
    DR_TEX_USE_MODE_UNKNOWN_0, // Inferred role: none; original name unknown.
    DR_TEX_USE_MODE_UNKNOWN_1, // Inferred role: low; original name unknown.
    DR_TEX_USE_MODE_UNKNOWN_2, // Inferred role: middle; original name unknown.
  };

  virtual ~DrCalcStmListObj();
  void release();
  void setupInfo(const u8 *header, bool isSetup);
  void setHeaderInfo(const u8 *header);
  bool isResSafe() const;
  unknown035 *getResObj(u32 index);
  unknown035 *getResVertexObj();
  unknown035 *getResShaderObj();
  bool isResChange() const;
  bool isResSub() const;
  bool isResTex() const;
  void setUseMode(DrTexUseMode mode);
  grlib::CGLibTextureBuffer *getTexObj(u32 index);
  void *getAdder();
  unknown035 *getResLowTexObj();
  bool texstm_requestWait();
  bool texstm_size_Wait();
  void setupReadCheck();
  bool texstm_notfileWait();
  bool texstm_oldVerWait();
  bool texstm_stmchk_setWait();
  bool texstm_defErrWait();
  bool texstm_defMidtexErrWait();
  bool texstm_fastErrWait();
  bool texstm_deTexCheck();
  bool texstm_checkTexStm();
  bool texstm_defupdate();
  bool OnFileEvent(EventFileTh *event);
  bool texstm_defRead();
  void chacheDefClear();
  void update();
  void callUpdate(DrStmListAfterArg &arg);
  void afterUpdate(DrStmListAfterArg &arg);
  void apiUpdate();

  DrCalcStmListObj *unknown08; // Inferred role: previous object; original member name unknown.
  DrCalcStmListObj *unknown10; // Inferred role: next object; original member name unknown.
  u8 _18[0x28 - 0x18];
  DrCalcTexStmObj **unknown28; // Inferred role: tex stream objects; original member name unknown.
  unknown035 *unknown30[2];    // Inferred role: res; original member name unknown.
  void *unknown40;             // Inferred role: file handle; original member name unknown.
  DrCalcTexStmObj *unknown48;  // Inferred role: tex stream object; original member name unknown.
  DrCalcTexStmObj *unknown50;  // Inferred role: read check tex stream object; original member name unknown.
  u8 _58[0x74 - 0x58];
  u16 unknown74; // Inferred role: vertex res index; original member name unknown.
  u16 unknown76; // Inferred role: shader res index; original member name unknown.
  u16 unknown78; // Inferred role: low texture res index; original member name unknown.
  u8 _7a[0x80 - 0x7a];
  u32 unknown80; // Inferred role: state flags; original member name unknown.
  u32 unknown84; // Inferred role: error wait size; original member name unknown.
  u32 unknown88; // Inferred role: wait state; original member name unknown.
  s16 unknown8c; // Inferred role: wait frames; original member name unknown.
  s16 unknown8e; // Inferred role: unused frames; original member name unknown.
  u8 _90[0x94 - 0x90];
  u32 unknown94; // Inferred role: tex stream count; original member name unknown.
  s32 unknown98; // Inferred role: resident size; original member name unknown.
  u8 _9c[0xa2 - 0x9c];
  s16 unknowna2; // Inferred role: tex stream object max; original member name unknown.
  s16 unknowna4; // Inferred role: tex stream count; original member name unknown.
  s16 unknowna6; // Inferred role: reference count; original member name unknown.
  s16 unknowna8; // Inferred role: error wait count; original member name unknown.
  s16 unknownaa; // Inferred role: request wait count; original member name unknown.
  u8 _ac[0xb0 - 0xac];
  grlib::CGLibTextureBuffer *unknownb0; // Inferred role: textures; original member name unknown.
  u8 _b8[0xc8 - 0xb8];
  s32 unknownc8;    // Inferred role: current use mode; original member name unknown.
  s32 unknowncc[2]; // Inferred role: use mode per buffer; original member name unknown.
  u8 _d4[0x1e0 - 0xd4];
  bool (DrCalcStmListObj::*unknown1e0)(); // Inferred role: current state function; original member name unknown.
  bool (DrCalcStmListObj::*unknown1f0)(); // Inferred role: read check state function; original member name unknown.
  bool (DrCalcStmListObj::*unknown200)(); // Inferred role: request state function; original member name unknown.
};

static_assert(offsetof(DrCalcStmListObj, unknown08) == 0x08, "");
static_assert(offsetof(DrCalcStmListObj, unknown10) == 0x10, "");
static_assert(offsetof(DrCalcStmListObj, unknown28) == 0x28, "");
static_assert(offsetof(DrCalcStmListObj, unknown40) == 0x40, "");
static_assert(offsetof(DrCalcStmListObj, unknown8c) == 0x8c, "");
static_assert(offsetof(DrCalcStmListObj, unknown8e) == 0x8e, "");
static_assert(offsetof(DrCalcStmListObj, unknown98) == 0x98, "");
static_assert(offsetof(DrCalcStmListObj, unknown30) == 0x30, "");
static_assert(offsetof(DrCalcStmListObj, unknown50) == 0x50, "");
static_assert(offsetof(DrCalcStmListObj, unknown84) == 0x84, "");
static_assert(offsetof(DrCalcStmListObj, unknown94) == 0x94, "");
static_assert(offsetof(DrCalcStmListObj, unknowna2) == 0xa2, "");
static_assert(offsetof(DrCalcStmListObj, unknowna4) == 0xa4, "");
static_assert(offsetof(DrCalcStmListObj, unknowna6) == 0xa6, "");
static_assert(offsetof(DrCalcStmListObj, unknowna8) == 0xa8, "");
static_assert(offsetof(DrCalcStmListObj, unknownc8) == 0xc8, "");
static_assert(offsetof(DrCalcStmListObj, unknown1f0) == 0x1f0, "");
static_assert(offsetof(DrCalcStmListObj, unknown48) == 0x48, "");
static_assert(offsetof(DrCalcStmListObj, unknown78) == 0x78, "");
static_assert(offsetof(DrCalcStmListObj, unknownaa) == 0xaa, "");
static_assert(offsetof(DrCalcStmListObj, unknown1e0) == 0x1e0, "");
static_assert(offsetof(DrCalcStmListObj, unknown200) == 0x200, "");
static_assert(offsetof(DrCalcStmListObj, unknown74) == 0x74, "");
static_assert(offsetof(DrCalcStmListObj, unknown76) == 0x76, "");
static_assert(offsetof(DrCalcStmListObj, unknown80) == 0x80, "");
static_assert(offsetof(DrCalcStmListObj, unknown88) == 0x88, "");
static_assert(offsetof(DrCalcStmListObj, unknownb0) == 0xb0, "");
static_assert(offsetof(DrCalcStmListObj, unknowncc) == 0xcc, "");

} // namespace ml
