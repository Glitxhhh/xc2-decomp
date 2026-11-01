#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjArtsPalette : public GfMenuObject {
public:
  static void exitChainAttack();
  static void close();
  static void open();
  void initialize() override;
  void finalize() override;
  static void push(unsigned int slot);
  static void pushReverseBtn(u32 button);
  static void reverse(bool isReverse);
  static void dispInfo(bool isDisp);
};

} // namespace gf
