#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {
class DrResMdoSeamMemObj;

class DrResMdoSeamMemMan {
public:
  int getUseMax() const;
  int getFreeMax() const;
  int getAllFreeSize() const;
  int getAllUseSize() const;
  u32 getFreeSize();
  u32 getFreeSize(int &freeCount, int &separatedCount);
  void renderMemInfo();
  bool calcPieceMem(bool isCheck);
  void releaseFreeObj(DrResMdoSeamMemObj *obj);
  DrResMdoSeamMemObj *createFreeObj(u32 size);
  DrResMdoSeamMemObj *createBackFreeObj(u32 size);

  DrResMdoSeamMemObj *unknown00; // Inferred role: first object of the list; original member name unknown.
};

static_assert(offsetof(DrResMdoSeamMemMan, unknown00) == 0x00, "");

} // namespace ml
