#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "mm_mtl/fixed_queue.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace ui {
class UICtrlCursorSelect;
class UICtrlSlideSelect;
class UIObjectAcc;
class UISelectObjList;
} // namespace ui

namespace gf {

class GfMenuCallContext;
class GfMenuDriverList;

class GfMenuObjInn : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x20 - 0x0c];
    GfMenuObjInn *unknown20; // Inferred role: owner; original member name unknown.
  };

  class ManualListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x20 - 0x0c];
    GfMenuObjInn *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjInn(u32 handle);
  ~GfMenuObjInn() override;
  static bool isEnableLevelUp();
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle);
  static int setFadeOut(u32 handle);
  void initialize() override;
  void finalize() override;
  bool seqFadeOut();
  bool seqFadeOutWait();
  void update() override;
  static void setupLvSelectAdapter(ui::UIObjectAcc &acc, ui::UISelectObjList *list);
  static void detailOpen(GfMenuObjInn *object, ui::UIObjectAcc &acc, const char *layout, u32 driver);
  static void setupLvUpAdapter(ui::UIObjectAcc &acc);

  u8 _24[0x28 - 0x24];
  GfMenuCallContext *unknown28;          // Inferred role: call context; original member name unknown.
  GfMenuCallContext *unknown30;          // Inferred role: call context; original member name unknown.
  ui::UICtrlCursorSelect *unknown38;     // Inferred role: mode cursor; original member name unknown.
  ui::UICtrlCursorSelect *unknown40;     // Inferred role: driver cursor; original member name unknown.
  GfMenuDriverList *unknown48;           // Inferred role: drivers; original member name unknown.
  ui::UICtrlSlideSelect *unknown50;      // Inferred role: level slider; original member name unknown.
  ui::UISelectObjList *unknown58;        // Inferred role: level objects; original member name unknown.
  mm::mtl::FixedQueue<u32, 5> unknown60; // Inferred role: drivers waiting for their level up; original member name unknown.
  u32 unknown88;                         // Inferred role: mode; original member name unknown.
  u32 unknown8c;                         // Inferred role: driver of the level up; original member name unknown.
  u32 unknown90;                         // Inferred role: enable level of the driver (first output of GfDataDriver::getEnableLevel); original member name unknown.
  u8 _94[0x98 - 0x94];
  bool unknown98; // Role and original member name unknown, cleared by the constructor.
  u8 _99[0xa0 - 0x99];
  GfMenuSequence<GfMenuObjInn, 8> unknown0a0; // Inferred role: queued steps; original member name unknown.
};

static_assert(offsetof(GfMenuObjInn, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjInn, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjInn, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjInn, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjInn, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjInn, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuObjInn, unknown58) == 0x58, "");
static_assert(offsetof(GfMenuObjInn, unknown60) == 0x60, "");
static_assert(offsetof(GfMenuObjInn, unknown88) == 0x88, "");
static_assert(offsetof(GfMenuObjInn, unknown8c) == 0x8c, "");
static_assert(offsetof(GfMenuObjInn, unknown90) == 0x90, "");
static_assert(offsetof(GfMenuObjInn, unknown98) == 0x98, "");
static_assert(offsetof(GfMenuObjInn, unknown0a0) == 0xa0, "");
static_assert(offsetof(GfMenuObjInn::MainListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjInn::ManualListener, unknown20) == 0x20, "");

} // namespace gf
