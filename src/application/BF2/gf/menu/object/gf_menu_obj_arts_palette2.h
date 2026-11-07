#pragma once
#include "gf/menu/gf_menu_object.h"

namespace gf {
class GfMenuCallContext;

class GfMenuObjArtsPalette2 : public GfMenuObject {
public:
  static void attachCallContext(GfMenuCallContext *context);
  static void close();
  static void open();
  static void resetSelection();
  static void setArtsSelection(GfMenuCallContext *context, bool isSelection);
  void initialize() override;
  void finalize() override;
  void update() override;
};

} // namespace gf
