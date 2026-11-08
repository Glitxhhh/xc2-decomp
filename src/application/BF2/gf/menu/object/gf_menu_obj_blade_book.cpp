#include "gf/menu/object/gf_menu_obj_blade_book.h"

#include "gf/game/gf_game_voice.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/list/gf_menu_blade_list.h"
#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_util.h"

namespace gf {

GfMenuObjBladeBook::GfMenuObjBladeBook(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown38(nullptr), unknown40(this), unknown2d0(false), unknown2d8(nullptr), unknown2e0(0, 0), unknown2f0() {}

GfMenuObjBladeBook::~GfMenuObjBladeBook() {
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown28);
}

void GfMenuObjBladeBook::finalize() {
  if (unknown2d8 != nullptr) {
    GfGameVoice::playStop(unknown2d8);
    unknown2d8 = nullptr;
  }
  GfMenuObject::finalize();
}

void GfMenuObjBladeBook::stopVoice() {
  if (unknown2d8 != nullptr) {
    GfGameVoice::playStop(unknown2d8);
    unknown2d8 = nullptr;
  }
}

void GfMenuObjBladeBook::update() {
  unknown40.unknown003();
  if (unknown2d8 != nullptr && GfGameVoice::getResult(unknown2d8) > 2) {
    unknown2d8 = nullptr;
  }
  GfMenuObject::update();
}

void GfMenuObjBladeBook::getScreenOverSize(u32 handle, f32 scale, s16 &width, s16 &height) {
  ui::UIObjectAcc acc(handle);
  mm::Rect<s16> rect;
  acc.getRect(rect, 0);
  f32 scaledWidth = rect.width * scale;
  width = static_cast<s16>(scaledWidth + (scaledWidth > 0.0f ? 0.5f : -0.5f));
  f32 scaledHeight = rect.height * scale;
  height = static_cast<s16>(scaledHeight + (scaledHeight > 0.0f ? 0.5f : -0.5f));
  width -= ui::UIUtil::getScreenWidth();
  height -= ui::UIUtil::getScreenHeight();
  if (width < 0) {
    width = 0;
  }
  if (height < 0) {
    height = 0;
  }
}

void GfMenuObjBladeBook::playVoice(const char *name) {
  if (unknown2d8 != nullptr) {
    GfGameVoice::playStop(unknown2d8);
    unknown2d8 = nullptr;
  }
  unknown2d8 = GfGameVoice::playVoice(name);
}

bool GfMenuObjBladeBook::seqEffReleaseA() {
  ui::UIObjectAcc image(unknown18, "IMG_bl_img");
  int ctrl = GfMenuObjUtil::getCtrlID(image.unknown10);
  bool isEnd;
  if (!unknown2d0) {
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 0x40000000;
    param.unknown38 = 1.0f;
    param.unknown00 = 1.0f;
    param.unknown14 = 4;
    GfMenuObjUtil::startCtrl(image.unknown10, param, nullptr);
    isEnd = false;
    unknown2d0 = true;
  } else if (!GfMenuObjUtil::isBusyCtrl(ctrl)) {
    isEnd = true;
    unknown2d0 = false;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjBladeBook::seqEffReleaseB() {
  ui::UIObjectAcc image(unknown18, "IMG_bl_img");
  int ctrl = GfMenuObjUtil::getCtrlID(image.unknown10);
  bool isEnd;
  if (!unknown2d0) {
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 2;
    param.unknown00 = 1.0f;
    param.unknown14 = 10;
    GfMenuObjUtil::startCtrl(image.unknown10, param, nullptr);
    isEnd = false;
    unknown2d0 = true;
  } else if (!GfMenuObjUtil::isBusyCtrl(ctrl)) {
    isEnd = true;
    unknown2d0 = false;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjBladeBook::seqEffReleaseC() {
  ui::UIObjectAcc image(unknown18, "IMG_bl_img_booster");
  int ctrl = GfMenuObjUtil::getCtrlID(image.unknown10);
  bool isEnd;
  if (!unknown2d0) {
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 0x40000000;
    param.unknown00 = 1.0f;
    param.unknown14 = 4;
    GfMenuObjUtil::startCtrl(image.unknown10, param, nullptr);
    isEnd = false;
    unknown2d0 = true;
  } else if (!GfMenuObjUtil::isBusyCtrl(ctrl)) {
    isEnd = true;
    unknown2d0 = false;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjBladeBook::seqEffReleaseD() {
  ui::UIObjectAcc image(unknown18, "IMG_bl_img_booster");
  int ctrl = GfMenuObjUtil::getCtrlID(image.unknown10);
  bool isEnd;
  if (!unknown2d0) {
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 2;
    param.unknown00 = 1.0f;
    param.unknown14 = 10;
    GfMenuObjUtil::startCtrl(image.unknown10, param, nullptr);
    isEnd = false;
    unknown2d0 = true;
  } else if (!GfMenuObjUtil::isBusyCtrl(ctrl)) {
    isEnd = true;
    unknown2d0 = false;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjBladeBook::seqConfirmBoosterGet() {
  bool isEnd;
  if (!unknown2d0) {
    GfMenuManager::openCommonWindow(0x12);
    isEnd = false;
    unknown2d0 = true;
  } else if (!GfMenuManager::isOpenCommonWindow()) {
    isEnd = true;
    unknown2d0 = false;
  } else {
    isEnd = false;
  }
  return isEnd;
}

bool GfMenuObjBladeBook::seqResumeRelease() {
  ui::UIObjectAcc list(unknown18, "LAY_list_bl");
  sendOpenEvent(list.unknown10, 0, 0.0f);
  GfMenuObjMainMenu2::setCloseKeyEnable(true);
  return true;
}

} // namespace gf
