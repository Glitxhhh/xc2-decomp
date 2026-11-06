#pragma once
#include "mm_math/mm_col4.h"

namespace ml {

class IException;

namespace {

// Inferred role: the statics of the window unit, one object of 0xb8 bytes in the game: the ProcException list and the
// default colors of WinView; original name unknown. Numbered after unknown001 of proc_mouse.cpp and unknown002 of
// win_view.cpp, which share the window.cpp unit.
struct unknown003 {
  int unknown00;                   // Inferred role: number of used entries of unknown38; original member name unknown.
  mm::Col4 m_defaultTitleBarColor; // Name from WinView::getDefaultTitleBarColor.
  mm::Col4 m_initialBackCol;       // Name from WinView::setInitialBackCol.
  mm::Col4 m_defaultFrameColor;    // Name from WinView::setDefaultFrameColor.
  IException *unknown38[16];       // Inferred role: entered exceptions, see ProcException::entry; original member name unknown.
};

unknown003 unknown004;

} // namespace

} // namespace ml
