#include "execute/title/title_menu.h"

#include "gf/gf_manager.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/object/gf_menu_obj_ev_theater.h"
#include "gf/menu/object/gf_menu_obj_option.h"
#include "gf/menu/object/gf_menu_obj_title.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/reference_object.h"

namespace tl {

gf::GfMenuCallContext *TitleMenu::getMenuCallContext() {
  if (unknown08 == nullptr) {
    unknown08 = gf::GfMenuCallContext::create();
  }
  return unknown08;
}

void TitleMenu::destroyMenuCallContext() {
  if (unknown08 != nullptr) {
    while (!unknown08->isTerm()) {
      gf::GfSleep(1);
    }
    mm::mtl::safeRelease(unknown08);
  }
}

void TitleMenu::openTitle(bool isFadeOut) { gf::GfMenuManager::openFullScreen(3, isFadeOut, true); }

bool TitleMenu::isOpenTitle() const { return !gf::GfMenuManager::isSwitchingFullScreen(); }

void TitleMenu::setupTitle() { gf::GfMenuObjTitle::attach(getMenuCallContext()); }

bool TitleMenu::hasResultSelect() const { return !unknown08->unknown18.empty(); }

// The game ignores the result of popResult (bl at 0x7100146b70) and loads the GfMenuResult slots (0x7100146b74, 0x7100146b84) whether or not
// the call filled them.
int TitleMenu::getResult() const {
  gf::GfMenuCallContext::GfMenuResult result;
  unknown08->popResult(result);
  if (result.unknown00 == 0 && result.unknown04 < 5) {
    return result.unknown04 + 1;
  }
  return 0;
}

void TitleMenu::closeTitle(bool isFadeOut, bool isFadeIn) {
  gf::GfMenuManager::closeFullScreen(isFadeOut, isFadeIn);
  destroyMenuCallContext();
}

bool TitleMenu::isCloseTitle() const { return !gf::GfMenuManager::isOpenFullScreen(); }

bool TitleMenu::isCloseOption() const { return !gf::GfMenuManager::isOpenFullScreen(); }

void TitleMenu::openEventTheater() {
  if (getMenuCallContext()->isActive()) {
    gf::GfMenuObjEvTheater::fadein(getMenuCallContext());
  } else {
    gf::GfMenuManager::openFullScreen(6, true, true);
  }
}

bool TitleMenu::isOpenEventTheater() const { return !gf::GfMenuManager::isSwitchingFullScreen(); }

void TitleMenu::setupEventTheater() { gf::GfMenuObjEvTheater::attach(getMenuCallContext()); }

bool TitleMenu::hasResultEventTheater() const { return !unknown08->unknown18.empty(); }

bool TitleMenu::isExitEventTheater() const { return unknown08->isTerm(); }

void TitleMenu::openOption() { gf::GfMenuManager::openFullScreen(7, false, true); }

bool TitleMenu::isOpenOption() const { return !gf::GfMenuManager::isSwitchingFullScreen(); }

void TitleMenu::setupOption() { gf::GfMenuObjOption::attach(getMenuCallContext()); }

bool TitleMenu::hasResultOption() const { return !unknown08->unknown18.empty(); }

bool TitleMenu::isExitOption() const { return unknown08->isTerm(); }

void TitleMenu::exitOption() { destroyMenuCallContext(); }

void TitleMenu::exitEventTheater() { destroyMenuCallContext(); }

void TitleMenu::fadeoutEventTheater() { gf::GfMenuObjEvTheater::fadeout(getMenuCallContext()); }

void TitleMenu::fadeinEventTheater() { gf::GfMenuObjEvTheater::fadein(getMenuCallContext()); }

// Same unchecked popResult as getResult (bl at 0x7100146e40, the slots loaded by the ldp at 0x7100146e44).
u32 TitleMenu::getPlayEventID() const {
  gf::GfMenuCallContext::GfMenuResult result;
  unknown08->popResult(result);
  return result.unknown00 == 0 ? result.unknown04 : 0;
}

} // namespace tl
