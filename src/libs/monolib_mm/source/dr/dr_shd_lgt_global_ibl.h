#pragma once
#include <stddef.h>

#include "mm_math/mm_mat44.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/list.h"
#include "types.h"

namespace grlib {
class CGLibDblUniformBlock;
} // namespace grlib

namespace ml {

class DrLightObjGlobalIBL;
class DrMan;
class DrShdLgtMan;

namespace _dr_shd_lgt_glb_ibl {
bool CompareByPriority(const DrLightObjGlobalIBL *a, const DrLightObjGlobalIBL *b);
} // namespace _dr_shd_lgt_glb_ibl

class DrShdLgtGlobalIBL {
public:
  // Inferred layout of an IBL slot; the original type name is unknown. Evidence: DrShdLgtGlobalIBL::updateView and
  // removeObj index the state bytes with (unknown08 + 2) % 3 and pass unknown10 to DrPixlPostObjCubeMapMultiIBL::cancelIBL.
  struct unknown002 {
    s32 unknown00;                  // Inferred role: sh matrix index; original member name unknown.
    u8 unknown04[3];                // Inferred role: request states; original member name unknown.
    u32 unknown08;                  // Inferred role: current request state index; original member name unknown.
    DrLightObjGlobalIBL *unknown10; // Inferred role: light object; original member name unknown.
  };

  // Inferred layout of the per view data; the original type name is unknown. Evidence: the constructor stores the
  // vtable of mm::mtl::List<DrLightObjGlobalIBL *> at 0x0, the destructor clears that list and the FixedVector size at
  // 0x1f40 per view, and updateView asserts "size() < capacity()" (fixed_vector.h) while filling 128 pointers at 0x1b40.
  struct unknown001 {
    mm::mtl::List<DrLightObjGlobalIBL *> unknown00;               // Inferred role: light objects; original member name unknown.
    unknown002 unknown40[32];                                     // Inferred role: slots; original member name unknown.
    mm::Mat44 unknown340[0x60];                                   // Inferred role: sh matrices; original member name unknown.
    mm::mtl::FixedVector<DrLightObjGlobalIBL *, 128> unknown1b40; // Inferred role: sorted light objects; original member name unknown.
    u8 _1f48[0x2048 - 0x1f48];
    grlib::CGLibDblUniformBlock *unknown2048; // Inferred role: uniform block; original member name unknown.
    bool unknown2050;                         // Inferred role: reset color buffer request; original member name unknown.
    u8 _2051[0x2060 - 0x2051];
  };

  DrShdLgtGlobalIBL(DrMan *drMan);
  ~DrShdLgtGlobalIBL();
  void update(int viewNum);
  void updateView(int viewNum);
  void updateUniformBlock(int viewNum);
  void updateUniformBlockImpl(int viewNum);
  void render(DrShdLgtMan *man);
  void resetColorBuff(int index);
  void delViewInfo(int viewNum);
  bool isEnable() const;
  void setUniformBlock(u32 index) const;
  void setStorageBuffer(u32 index) const;
  const mm::Mat44 &getSHMatrix(u32 row, u32 column) const;
  void updateUB_ShMatrixList(u8 *work, int viewNum);
  void addObj(DrLightObjGlobalIBL *obj, int viewNum);
  void removeObj(DrLightObjGlobalIBL *obj, int viewNum);

  DrMan *unknown00;        // Inferred role: dr man; original member name unknown.
  unknown001 unknown10[4]; // Inferred role: per view data; original member name unknown.
};

static_assert(offsetof(DrShdLgtGlobalIBL, unknown10) == 0x10, "");
static_assert(sizeof(DrShdLgtGlobalIBL::unknown002) == 0x18, "");
static_assert(offsetof(DrShdLgtGlobalIBL::unknown002, unknown04) == 0x4, "");
static_assert(offsetof(DrShdLgtGlobalIBL::unknown002, unknown08) == 0x8, "");
static_assert(offsetof(DrShdLgtGlobalIBL::unknown002, unknown10) == 0x10, "");
static_assert(offsetof(DrShdLgtGlobalIBL::unknown001, unknown40) == 0x40, "");
static_assert(offsetof(DrShdLgtGlobalIBL::unknown001, unknown340) == 0x340, "");
static_assert(offsetof(DrShdLgtGlobalIBL::unknown001, unknown1b40) == 0x1b40, "");
static_assert(offsetof(DrShdLgtGlobalIBL::unknown001, unknown2048) == 0x2048, "");
static_assert(offsetof(DrShdLgtGlobalIBL::unknown001, unknown2050) == 0x2050, "");
static_assert(sizeof(DrShdLgtGlobalIBL::unknown001) == 0x2060, "");

} // namespace ml
