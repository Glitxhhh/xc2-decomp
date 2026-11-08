#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace gf {

class GfMenuObjItemSubmenu : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;
  };

  GfMenuObjItemSubmenu(u32 handle);
  ~GfMenuObjItemSubmenu() override;
  static void returnItemSubMenu();
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle);
  static int setFadeOut(u32 handle, bool unknown);
  void initialize() override;
  void finalize() override;
  void update() override;

  u8 _24[0x2c - 0x24];
  u32 unknown2c; // Role and original member name unknown, zeroed by the constructor.
};

static_assert(offsetof(GfMenuObjItemSubmenu, unknown2c) == 0x2c, "");

} // namespace gf
