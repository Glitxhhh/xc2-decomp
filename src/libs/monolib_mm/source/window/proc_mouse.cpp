#include "ml/proc_mouse.h"

namespace ml {

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

} // namespace ml

template mm::mtl::PtrSingleton<ml::ProcMouse>::~PtrSingleton();
