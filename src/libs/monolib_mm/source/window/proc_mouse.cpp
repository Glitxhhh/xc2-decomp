#include "ml/proc_mouse.h"

#include "ml/dev_mouse.h"
#include "ml/msg_param.h"
#include "ml/proc_desktop.h"
#include "ml/reslist.h"
#include "ml/win_view.h"
#include "mm_math/mm_rect.h"

namespace ml {

class WorkObj;

ProcMouse::ProcMouse(const char *name, WorkObj *parent) : WinProc(name, parent, 10), unknown1f8(0, 0), unknown200(0, 0), unknown208(0, 0), unknown234(false) { unknown210 = "ARROW"; }

ProcMouse::~ProcMouse() {}

mm::Pnt<int> *ProcMouse::getPos() { return &get()->unknown1f8; }

mm::Pnt<int> *ProcMouse::getMove() { return &get()->unknown208; }

void ProcMouse::setPos(const mm::Pnt<int> &position) {
  ProcMouse *mouse = get();
  mouse->unknown200 = position;
  mouse->unknown1f8 = position;
}

void ProcMouse::setCursorResize(MCURSOR cursor) {
  switch (cursor) {
  case MCURSOR_UNKNOWN_1:
    get()->unknown210 = "SIZE1";
    get()->unknown234 = true;
    break;
  case MCURSOR_UNKNOWN_2:
    get()->unknown210 = "SIZE2";
    get()->unknown234 = true;
    break;
  case MCURSOR_UNKNOWN_3:
    get()->unknown210 = "SIZE3";
    get()->unknown234 = true;
    break;
  case MCURSOR_UNKNOWN_4:
    get()->unknown210 = "SIZE4";
    get()->unknown234 = true;
    break;
  default:
    get()->unknown210 = "ARROW";
    get()->unknown234 = false;
    break;
  }
}

void ProcMouse::update(bool isUpdate) {
  ProcMouse *mouse = get();
  if (mouse == nullptr || DevMouse::get() == nullptr) {
    return;
  }
  WinView *view = mouse->pssGetView(0xffffffff);
  if (view == nullptr) {
    return;
  }
  get()->unknown208 = DevMouse::getMove();
  get()->unknown200 = get()->unknown1f8;
  get()->unknown1f8 = DevMouse::getPos();
  mouse = get();
  const mm::Pnt<int> &pos = mouse->unknown1f8;
  const mm::Pnt<int> &prev = mouse->unknown200;
  if (pos.x != prev.x || pos.y != prev.y) {
    mouse->unknown235 = 60;
  }
  view->setRect(ProcDesktop::get()->unknown208->getRect(false));
  mm::Rect<int> rect = ProcDesktop::get()->unknown208->getRect(false);
  mm::Pnt<int> *clamped = getPos();
  if (clamped->x < rect.x) {
    clamped->x = rect.x;
  }
  if (clamped->y < rect.y) {
    clamped->y = rect.y;
  }
  if (clamped->x >= rect.x + rect.width - 1) {
    clamped->x = rect.x + rect.width - 1;
  }
  if (clamped->y >= rect.y + rect.height - 1) {
    clamped->y = rect.y + rect.height - 1;
  }
}

bool ProcMouse::wkStandbyLogin() {
  WinView *view = pssCreateView(unknown08.c_str(), pssGetParentView(), 0);
  mm::Rect<int> rect = ProcDesktop::getView()->getRect(false);
  view->setRect(rect);
  view->unknown3c0.add(5);
  view->unknown528 = 2;
  view->unknown3b8 |= 8;
  get()->unknown1f8 = mm::Pnt<int>(0, 0);
  get()->unknown200 = mm::Pnt<int>(0, 0);
  return WinProc::wkStandbyLogin();
}

bool ProcMouse::wkStandbyLogout() {
  if (unknown60.size() != 0) {
    return false;
  }
  WinView *desktopView = ProcDesktop::getView();
  if (desktopView != nullptr && desktopView->unknown60.size() != 0) {
    if (desktopView->wkGetChild()->begin()->value == pssGetView(0xffffffff)) {
      return false;
    }
  }
  return WinProc::wkStandbyLogout();
}

} // namespace ml

template mm::mtl::PtrSingleton<ml::ProcMouse>::~PtrSingleton();
