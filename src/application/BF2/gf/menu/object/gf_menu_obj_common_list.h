#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjCommonList : public GfMenuObject {
public:
  static void close();
  static void moveCursor(u32 handle, int index);
  static void setupPlugin(u32 handle);
  GfMenuObjCommonList(u32 handle);
  ~GfMenuObjCommonList() override;
  void initialize() override;
  void finalize() override;
  void update() override;
};

} // namespace gf
