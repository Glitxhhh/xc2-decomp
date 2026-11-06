#include "framework/debug/debug_input_keyboard.h"

#include "framework/debug/debug_draw.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_rect.h"

namespace fw {
namespace debug {

DebugInputKeyboard::DebugInputKeyboard() : unknown08(false), unknown09(false), unknown220(0), unknown224(0) {}

DebugInputKeyboard::~DebugInputKeyboard() {}

void DebugInputKeyboard::renderImpl(const mm::Rect<int> &rect) {
  if (unknown08) {
    drawSquare2D(rect, mm::Col4(0.2f, 0.2f, 0.2f, 0.4f));
    drawLineSquare2D(rect.unknown00, rect.unknown08, mm::Col4::white);
    drawLineSquare2D(rect.unknown00, rect.unknown08, mm::Col4::white);
    drawFont(rect.x + 4, rect.y + 1, mm::Col4::white, "%s", unknown18.c_str());
    unknown228++;
    if (unknown228 & 0x10) {
      int cursor = unknown220;
      mm::mtl::FixStr<256> text;
      if (!unknown18.empty()) {
        int length = unknown18.length();
        if (cursor != -1) {
          length = cursor;
        }
        unknown18.unknown001(text, 0, length);
      }
      int width = drawFontGetWidth(text.c_str());
      drawFont(rect.x + width, rect.y + 1, mm::Col4::white, "%s", "|");
    }
  }
}

} // namespace debug
} // namespace fw
