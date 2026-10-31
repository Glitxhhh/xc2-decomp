#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ui {
struct EventData;
} // namespace ui

namespace gf {

class GfMenuOrderMgr : public mm::mtl::PtrSingleton<GfMenuOrderMgr> {
public:
  static void setOrder(int order, u32 handle, const ui::EventData &event);
  static void cancelOrder(int order);
};

} // namespace gf
