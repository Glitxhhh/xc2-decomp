#pragma once
#include <stddef.h>

#include "rcha/rcha_node.h"
#include "types.h"

// Declared from the symbols _ZN10RchaCamEffC1Ev (0x710069d640), _ZN10RchaCamEff5setupEN3mtl12ALLOC_HANDLEEPKv
// (0x710069d8a8) and the vtable _ZTV10RchaCamEff (0x71011a75d0); its size is the allocation size in CamEvaPlayerEff::play.
class RchaCamEff : public RchaNode {
public:
  static const int NAME_COUNT = 4;

  // Slots of unknown19a4, in the order of the names (camAtr/ tracks) that setup looks for.
  enum {
    CAMATR_COL_FILTER = 0,
    CAMATR_COL_FILTER_NEAR = 1,
    CAMATR_COL_FILTER_FAR = 2,
    CAMATR_COL_FILTER_FR = 3,
  };

  RchaCamEff();
  virtual bool setup(mtl::ALLOC_HANDLE handle, const void *data);
  static bool hasAnm(const void *data);
  f32 getValue(int slot, f32 frame, f32 defaultValue) const;
  int getValueInt(int slot, f32 frame, int defaultValue) const;
  bool isEnableColFilter(f32 frame) const;
  bool getColFilter(int &filter, f32 frame) const;
  int getNearColFilter(f32 frame) const;
  int getFarColFilter(f32 frame) const;
  f32 getFrColFilter(f32 frame) const;

private:
  bool unknown19a0;            // Inferred role: has any named track; original member name unknown.
  int unknown19a4[NAME_COUNT]; // Inferred role: track index of each name; original member name unknown.

  friend struct RchaCamEffLayout;
};

struct RchaCamEffLayout {
  static_assert(offsetof(RchaCamEff, unknown19a0) == 0x19a0, "");
  static_assert(offsetof(RchaCamEff, unknown19a4) == 0x19a4, "");
  static_assert(sizeof(RchaCamEff) == 0x19b8, "");
};
