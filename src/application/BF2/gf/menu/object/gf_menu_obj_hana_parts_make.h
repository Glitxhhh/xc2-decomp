#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjHanaPartsMake : public GfMenuObject {
public:
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle, u32 unknown);
  static int setFadeOut(u32 handle, u32 unknown);
  void initialize() override;
  void finalize() override;
  void update() override;
  static u32 getCrystalItemCount(u32 item);
  static u16 getFirstSortTableId(u32 type, u32 isEquip);
  static u32 getMakeItemCount(u32 parts);
  static u32 makeParts(u32 type, u32 parts);
  static u32 crystalParts(u32 type, u32 parts);
};

} // namespace gf
