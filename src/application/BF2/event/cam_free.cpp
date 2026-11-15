#include "event/cam_free.h"

#include "event/manager.h"
#include "ml/dev_keyboard.h"
#include "ml/event_view.h"
#include "ml/scn.h"
#include "ml/win_view.h"
#include "mm_math/mm_vec3.h"

namespace event {

CamFree::CamFree(bool isFocal) : CamBase(isFocal), unknown48(0), unknown4c(0), unknown50(CTRL_MODE_UNKNOWN_0), unknown54(5.0f) {}

CamFree::~CamFree() {
  if ((unknown48 & 1) != 0) {
    Manager::get()->getScn()->getView(-1)->detachWorkEvent(this);
  }
}

void CamFree::update(const FrameInfo &info) {}

void CamFree::setActive(bool isActive) {
  if (((unknown48 & 1) != 0) != isActive) {
    ml::WinView *view = Manager::get()->getScn()->getView(-1);
    if (isActive) {
      view->attachWorkEvent(this, false);
      unknown48 |= 1;
    } else {
      view->detachWorkEvent(this);
      unknown48 &= ~1;
    }
  }
}

bool CamFree::OnMouseButtonDown(ml::EventView *view) {
  bool isKeyDown = (view->unknown28 & 1) != 0;
  u32 flags = unknown4c & ~8;
  if (isKeyDown) {
    flags = unknown4c | 8;
  }
  unknown4c = flags;
  if ((view->buttons & 4) != 0) {
    unknown4c |= 1;
  }
  if ((view->buttons & 2) != 0) {
    unknown4c |= 2;
  }
  if ((view->buttons & 1) != 0) {
    unknown4c |= 4;
  }
  return unknown001();
}

bool CamFree::OnMouseButtonUp(ml::EventView *view) {
  if ((view->buttons & 4) != 0) {
    unknown4c &= ~1;
  }
  if ((view->buttons & 2) != 0) {
    unknown4c &= ~2;
  }
  if ((view->buttons & 1) != 0) {
    unknown4c &= ~4;
  }
  return unknown001();
}

void CamFree::ctrlTrack(const mm::Pnt<int> &mouse) {
  f32 speed = unknown54 * 0.2f;
  f32 scale = speed > 1.0f ? speed * 20.0f : speed;
  mm::Vec3 move;
  getScreenMove2TargetMove(move, mouse);
  mm::Vec3 offset = move * scale;
  unknown10 = unknown10 + offset;
  unknown20 = unknown20 + offset;
}

bool CamFree::OnKeyUp(ml::EventView *view) {
  if ((view->unknown28 & 1) == 0) {
    return false;
  }
  unknown4c &= ~8;
  unknown50 = CTRL_MODE_UNKNOWN_0;
  return true;
}

bool CamFree::OnMouseMove(ml::EventView *view) {
  if ((ml::DevKeyboard::getVkHold() & 1) == 0) {
    return false;
  }
  // Cases in the order of the blocks of the game (0x71000afa7c: tumble 0x71000afac8, dolly 0x71000afad8, track, inlined, 0x71000afae8): the compares come out as 1, 2 and 3 with ctrlTumble as the
  // fall-through. Ascending case order, an if/else chain and `return true` in each case all give 68 instructions against 66 (checked).
  switch (unknown50) {
  case CTRL_MODE_UNKNOWN_3:
    ctrlTumble(view->unknown10);
    break;
  case CTRL_MODE_UNKNOWN_1:
    ctrlDolly(view->unknown10);
    break;
  case CTRL_MODE_UNKNOWN_2:
    ctrlTrack(view->unknown10);
    break;
  default:
    return false;
  }
  return true;
}

} // namespace event
