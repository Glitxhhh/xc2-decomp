#pragma once
#include <stddef.h>

#include "gf/object/gf_append.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace gf {

class GfAppendInfo {
public:
  GfAppendInfo() : unknownb0(0) {}
  ~GfAppendInfo() { unknown001(); }

  // Inferred role: deletes the appends of both sets; original name unknown.
  void unknown001() {
    for (u32 i = 0; i < 2; i++) {
      for (GfAppend *&append : unknown00[i]) {
        if (append != nullptr) {
          delete append;
          append = nullptr;
        }
      }
      unknown00[i].clear();
      unknownb0 = 0;
    }
  }

  // Evidence: GfAppendUtil::setupWeapon frees both vectors (sizes at 0x50 and 0xa8) and clears the u32 at 0xb0;
  // GfObjUtil::getAppend reads vector [weapon alternate flag] element [GFOBJ_MOUNT index]; GfAppendInfo::operator= copies 0x58 bytes twice;
  // GfWeapon::getRscRight sign-extends the u32 at 0xb0 as a vector index.
  mm::mtl::FixedVector<GfAppend *, 10> unknown00[2]; // Inferred role: append sets; original member name unknown.
  int unknownb0;                                     // Inferred role: selected append set; original member name unknown.
};

static_assert(offsetof(GfAppendInfo, unknown00) == 0x00, "");
static_assert(offsetof(GfAppendInfo, unknownb0) == 0xb0, "");
static_assert(sizeof(GfAppendInfo) == 0xb8, "");

} // namespace gf
