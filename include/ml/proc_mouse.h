#pragma once
#include <stddef.h>

#include "ml/win_proc.h"
#include "ml/win_view_frame.h"
#include "mm_math/mm_pnt.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"

namespace ml {

class ProcMouse : public WinProc, public mm::mtl::PtrSingleton<ProcMouse> {
public:
  ~ProcMouse() override;
  static mm::Pnt<int> *getPos();
  static mm::Pnt<int> *getMove();
  static void setPos(const mm::Pnt<int> &position);
  static void setCursorResize(MCURSOR cursor);

  mm::Pnt<int> unknown1f8;        // Inferred role: position; original member name unknown.
  mm::Pnt<int> unknown200;        // Inferred role: previous position; original member name unknown.
  mm::Pnt<int> unknown208;        // Inferred role: move; original member name unknown.
  mm::mtl::FixStr<32> unknown210; // Inferred role: cursor name ("ARROW", "SIZE1"...); original member name unknown.
  bool unknown234;                // Inferred role: resize cursor shown; original member name unknown.
};

static_assert(offsetof(ProcMouse, unknown1f8) == 0x1f8, "");
static_assert(offsetof(ProcMouse, unknown200) == 0x200, "");
static_assert(offsetof(ProcMouse, unknown208) == 0x208, "");
static_assert(offsetof(ProcMouse, unknown210) == 0x210, "");
static_assert(offsetof(ProcMouse, unknown234) == 0x234, "");

} // namespace ml
