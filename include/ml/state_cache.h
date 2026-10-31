#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_queue.h"
#include "types.h"

namespace ml {

// Provenance: only the three member functions of StateCache have symbols and the game never calls them; the layout comes from
// their code (a FixedQueue of 32 entries of 0x18 bytes at 0x08 and a listener called through vtable slot 0x10 at 0x320).
class StateCache {
public:
  // Inferred role: cached state entry; original type name unknown.
  struct unknown001 {
    u32 unknown00;      // Inferred role: state id; original member name unknown.
    u8 unknown04[0x14]; // Inferred role: state data; original member name unknown.
  };

  // Inferred role: receiver of the cached state data; original type name unknown.
  class unknown002 {
  public:
    virtual ~unknown002() {}
    // Inferred role: applies the data of a state; original name unknown.
    virtual void unknown003(u32 id, void *data) = 0;
  };

  void update(u32 id);
  void *getAdr(u32 id);

  // Inferred role: index of the entry of a state id, -1 when it is not cached; original name unknown.
  int unknown004(u32 id) const {
    int index = -1;
    for (u32 i = 0; i < unknown08.size(); i++) {
      if (unknown08[i].unknown00 == id) {
        index = i;
        break;
      }
    }
    return index;
  }

  u8 _00[0x08];
  mm::mtl::FixedQueue<unknown001, 32> unknown08; // Inferred role: cached states; original member name unknown.
  u8 _318[0x320 - 0x318];
  unknown002 *unknown320; // Inferred role: state receiver; original member name unknown.
};

static_assert(sizeof(StateCache::unknown001) == 0x18, "");
static_assert(offsetof(StateCache, unknown08) == 0x08, "");
static_assert(offsetof(StateCache, unknown320) == 0x320, "");

} // namespace ml
