#include "ml/scn_util.h"

#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_math/mm_vec3.h"

namespace ml {

bool ScnUtil::checkLineRect(const mm::Vec3 &start, const mm::Vec3 &end, const mm::Rect<int> &rect) {
  mm::Pnt<int> startPos(start.x, start.y);
  mm::Pnt<int> endPos(end.x, end.y);
  if (startPos.x >= rect.x && startPos.x < rect.x + rect.width && startPos.y >= rect.y && startPos.y < rect.y + rect.height) {
    return true;
  }
  if (endPos.x >= rect.x && endPos.x < rect.x + rect.width && endPos.y >= rect.y && endPos.y < rect.y + rect.height) {
    return true;
  }
  if (isCrossLine(startPos, endPos, mm::Pnt<int>(rect.x, rect.y), mm::Pnt<int>(rect.x + rect.width, rect.y))) {
    return true;
  }
  if (isCrossLine(startPos, endPos, mm::Pnt<int>(rect.x + rect.width, rect.y), mm::Pnt<int>(rect.x + rect.width, rect.y + rect.height))) {
    return true;
  }
  if (isCrossLine(startPos, endPos, mm::Pnt<int>(rect.x, rect.y + rect.height), mm::Pnt<int>(rect.x + rect.width, rect.y + rect.height))) {
    return true;
  }
  return isCrossLine(startPos, endPos, mm::Pnt<int>(rect.x, rect.y), mm::Pnt<int>(rect.x, rect.y + rect.height));
}

} // namespace ml
