#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjOperationInfo : public GfMenuObject {
public:
  static void open(u32 handle, u32 unknown0, u32 unknown1, u32 unknown2);
  static void close();
  static void setDisp(bool isDisp);
  void initialize() override;
  void finalize() override;
  void update() override;
};

} // namespace gf
