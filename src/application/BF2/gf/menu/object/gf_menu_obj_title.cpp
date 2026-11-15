#include "gf/menu/object/gf_menu_obj_title.h"

#include "execute/title/title_main.h"
#include "gf/data/gf_data_game.h"
#include "gf/data/gf_data_system.h"
#include "gf/data/gf_game_flag.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/reference_object.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {
class GfMenuCallContext;

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x18;

bool GfMenuObjTitle::s_NoSaveData = true;

// Inferred role: name and enable test of each title menu entry; original type name unknown.
struct unknown002 {
  const char *unknown00; // Inferred role: entry text; original member name unknown.
  bool (*unknown08)();   // Inferred role: enable test; original member name unknown.
};

// Inferred role: title menu entries (new game, continue, option, theater, new game advanced); original name unknown.
static const unknown002 unknown003[5] = {
    {"TXT_newgame", GfMenuObjTitle::isEnableNewGame},
    {"TXT_continue", GfMenuObjTitle::isEnableContinue},
    {"TXT_option", GfMenuObjTitle::isEnableOption},
    {"TXT_theater", GfMenuObjTitle::isEnableEventsTheater},
    {"TXT_newgame_adv", GfMenuObjTitle::isEnableNewGameAdv},
};

GfMenuObjTitle::GfMenuObjTitle(u32 handle) : GfMenuObject(handle), unknown48(0), unknown50(nullptr), unknown58(this), unknown1b8(false) { s_NoSaveData = true; }

GfMenuObjTitle::~GfMenuObjTitle() { mm::mtl::safeRelease(unknown50); }

void GfMenuObjTitle::finalize() { GfMenuObject::finalize(); }

void GfMenuObjTitle::update() {
  unknown58.unknown003();
  GfMenuObject::update();
}

bool GfMenuObjTitle::isEnableNewGame() { return true; }

bool GfMenuObjTitle::isEnableNewGameAdv() { return false; }

bool GfMenuObjTitle::isEnableContinue() { return !s_NoSaveData; }

bool GfMenuObjTitle::isEnableOption() { return true; }

bool GfMenuObjTitle::isEnableEventsTheater() {
  if (s_NoSaveData) {
    return false;
  }
  return GfGameFlag::getLocal(tl::TitleMain::get()->getSaveBuffer()->unknown10.unknownfbbc4, 1, FLAG_UNKNOWN_39487) == 1;
}

void GfMenuObjTitle::moveCursor(u32 handle, int index) {
  ui::UIObjectAcc item(handle, unknown003[unknown28[index]].unknown00);
  ui::UIObjectAcc cursor(handle, "LAY_Cursor");
  if (item.isValid() && cursor.isValid()) {
    GfMenuObjUtil::setDockPos(cursor.unknown10, item.unknown10, 0, true);
  }
}

void GfMenuObjTitle::setDispMode(u32 handle, int mode) {
  if (mode == 0) {
    GfMenuObjUtil::setChildDisp(handle, "LAY_keywait", true);
    GfMenuObjUtil::setChildDisp(handle, "LAY_list", false);
  } else if (mode == 1) {
    GfMenuObjUtil::setChildDisp(handle, "LAY_keywait", false);
    GfMenuObjUtil::setChildDisp(handle, "LAY_list", true);
  } else {
    GfMenuObjUtil::setChildDisp(handle, "LAY_keywait", false);
    GfMenuObjUtil::setChildDisp(handle, "LAY_list", false);
  }
}

void GfMenuObjTitle::setInputMode(u32 handle, int mode) {
  ui::UIObjectAcc acc(handle);
  if (acc.isValid()) {
    if (mode == 0) {
      GfMenuObject::enableInput(acc.searchChild("LAY_keywait"));
      GfMenuObject::disableInput(acc.searchChild("LAY_list"));
    } else if (mode == 1) {
      GfMenuObject::enableInput(acc.searchChild("LAY_list"));
      GfMenuObject::disableInput(acc.searchChild("LAY_keywait"));
    }
  }
}

bool GfMenuObjTitle::seqConfirmNewGame() {
  if (!unknown1b8) {
    GfMenuManager::openCommonWindow(0xe1);
    unknown1b8 = true;
    return false;
  }
  if (GfMenuManager::isOpenCommonWindow()) {
    return false;
  }
  ui::UIObjectAcc acc(unknown18, "LAY_main");
  s16 result = GfMenuManager::getCommonWindowResult();
  if (result == 0) {
    addResultCallContext(acc.unknown10, unknown48, 0);
  } else {
    ui::EventData event;
    event.unknown00 = 0x101;
    sendEvent(acc.unknown10, event, 0.0f);
  }
  return true;
}

bool GfMenuObjTitle::attach(GfMenuCallContext *context) { return unknown151(context, unknown001); }

void GfMenuObjTitle::initialize() {
  ui::UIObjectAcc acc(unknown18);
  u32 main = acc.searchChild("LAY_main");
  if (ui::UIObjectAcc(main).isValid()) {
// __LINE__ must be 112 as in the original file: it is the line argument of operator new.
#line 112
    ListListener *listener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ListListener(this);
    listener->addRef();
    ui::UIEventManager::get()->registObjectListener(main, listener);
    if (listener != nullptr) {
      listener->release();
    }
    attachExternalCall(unknown001, main);
    u32 keyWait = acc.searchChild("LAY_keywait");
    u32 list = acc.searchChild("LAY_list");
    migrateInput(list, main);
    migrateInput(keyWait, main);
  }
  u32 version = tl::TitleMain::get()->getSaveBuffer()->unknown00;
  s_NoSaveData = version != SAVE_UNKNOWN_237915;
  acc.setDispChild(version == SAVE_UNKNOWN_237915, "IMG_Logo");
  {
    ui::UISelectObjList::CreateParam createParam;
    createParam.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
    unknown50 = ui::UISelectObjList::create(createParam);
  }
  unknown28.clear();
  for (u32 i = 0; i < 5; i++) {
    ui::UIObjectAcc item(acc.unknown10, unknown003[i].unknown00);
    if (item.isValid()) {
      if (unknown003[i].unknown08()) {
        item.setDisp(true);
        unknown28.push_back(i);
        unknown50->addObject(item.unknown10);
      } else {
        item.setDisp(false);
      }
    }
  }
  {
    ui::UIObjectAcc root(main);
    mm::Rect<s16> option;
    root.getLayoutRect("option", option);
    mm::Rect<s16> theater;
    root.getLayoutRect("theater", theater);
    GfMenuObjUtil::placeObjectV(unknown50, mm::Pnt<s16>(option.x + option.width / 2, option.y + option.height / 2), theater.y - option.y);
  }
  GfMenuObject::initialize();
}
} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjTitle>(const mm::mtl::Delegate<bool()> *);
