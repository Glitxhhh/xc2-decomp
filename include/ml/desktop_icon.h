#pragma once
#include <stddef.h>

#include "mm_math/mm_rect.h"
#include "mm_mtl/fixstr.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace ml {

class WinView;

class DesktopIcon {
public:
  DesktopIcon(const char *name, void (*func)());
  virtual ~DesktopIcon() {}
  static DesktopIcon *create(mtl::ALLOC_HANDLE handle, const char *name, void (*func)());
  void execute();
  void render(WinView *view);

  mm::mtl::FixStr<64> unknown08; // Inferred role: icon name; original member name unknown.
  void (*unknown50)();           // Inferred role: function run by the icon; original member name unknown.
  mm::Rect<int> unknown58;       // Inferred role: icon rectangle; original member name unknown.
  bool unknown68;                // Inferred role: icon under the mouse; original member name unknown.
};

static_assert(offsetof(DesktopIcon, unknown08) == 0x08, "");
static_assert(offsetof(DesktopIcon, unknown50) == 0x50, "");
static_assert(offsetof(DesktopIcon, unknown58) == 0x58, "");
static_assert(offsetof(DesktopIcon, unknown68) == 0x68, "");
static_assert(sizeof(DesktopIcon) == 0x70, "");

} // namespace ml
