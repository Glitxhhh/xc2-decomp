#include "ml/win_view_frame.h"

#include "ml/win_view.h"

namespace ml {

void WinViewFrame::setInfo(WinView *info) { m_info = info; }

bool WinViewFrame::evtFocusOn() { return true; }

bool WinViewFrame::evtFocusOff() {
  unknown38 = FMOVE_UNKNOWN_8;
  return true;
}

bool WinViewFrame::evtMousePickOff(EventView *event) {
  if (unknown38 == FMOVE_UNKNOWN_8) {
    return false;
  }
  unknown38 = FMOVE_UNKNOWN_8;
  return true;
}

mm::Col4 WinViewFrame::getColorTransparency() const {
  mm::Col4 color = unknown08;
  color.a *= m_info->unknown524;
  return color;
}

MCURSOR WinViewFrame::evtMouseSelect(const mm::Pnt<int> &pos) const {
  if (unknown38 == FMOVE_UNKNOWN_8) {
    return getFrameSelect(pos);
  }
  return getMove2MCursor(unknown38);
}

mm::Pnt<int> WinViewFrame::getFrame2ViewSizeOffset() const {
  mm::Pnt<int> offset(0, 0);
  u32 frameFlags = m_info->unknown3bc;
  if ((frameFlags & 1) && (m_info->unknown3b8 & 3) == 0) {
    s16 width = unknown60;
    offset.x = width * 2;
    offset.y = offset.x;
    if (frameFlags & 2) {
      offset.y = width + offset.x + 0x16;
    }
  }
  return offset;
}

MCURSOR WinViewFrame::getMove2MCursor(FMOVE move) const {
  if (move == FMOVE_UNKNOWN_0 || move == FMOVE_UNKNOWN_3) {
    return MCURSOR_UNKNOWN_1;
  }
  if (move == FMOVE_UNKNOWN_1 || move == FMOVE_UNKNOWN_2) {
    return MCURSOR_UNKNOWN_2;
  }
  if (move == FMOVE_UNKNOWN_4 || move == FMOVE_UNKNOWN_5 || move == FMOVE_UNKNOWN_11) {
    return MCURSOR_UNKNOWN_3;
  }
  if (move == FMOVE_UNKNOWN_6 || move == FMOVE_UNKNOWN_7 || move == FMOVE_UNKNOWN_10) {
    return MCURSOR_UNKNOWN_4;
  }
  if (move == FMOVE_UNKNOWN_9) {
    return MCURSOR_UNKNOWN_5;
  }
  return MCURSOR_UNKNOWN_0;
}

MCURSOR WinViewFrame::getFrameSelect(const mm::Pnt<int> &pos) const { return getMove2MCursor(getFramePick(pos)); }

} // namespace ml
