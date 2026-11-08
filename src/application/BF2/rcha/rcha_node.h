#pragma once
#include <stddef.h>

#include "rcha/rcha_anm.h"
#include "types.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

// Base of RchaCam, RchaEff, RchaChrEff and RchaCamEff. Declared from the symbols _ZN8RchaNodeC1Ev (0x710069f5e0),
// _ZN8RchaNode5clearEv (0x710069f660) and the vtable _ZTV8RchaNode (0x71011a78d8): the destructor, setup and clear
// are its three virtual functions, and clear() zeroes the fields up to 0x199c.
class RchaNode {
public:
  static const int TRACK_MAX = 48;

  RchaNode();
  virtual ~RchaNode();
  virtual bool setup(mtl::ALLOC_HANDLE handle, const void *data);
  virtual void clear();
  u32 hashStr(const char *name) const;

  int getFrameCount() const { return unknown199c; }

protected:
  u8 _8[0x10 - 0x8];
  RchaAnm unknown10[TRACK_MAX]; // Inferred role: tracks; original member name unknown.
  int unknown1990;              // Inferred role: track count; original member name unknown.
  u8 _1994[0x199c - 0x1994];
  int unknown199c; // Inferred role: frame count; original member name unknown.

  friend struct RchaNodeLayout;
};

struct RchaNodeLayout {
  static_assert(offsetof(RchaNode, unknown10) == 0x10, "");
  static_assert(offsetof(RchaNode, unknown1990) == 0x1990, "");
  static_assert(offsetof(RchaNode, unknown199c) == 0x199c, "");
  static_assert(sizeof(RchaNode) == 0x19a0, "");
};
