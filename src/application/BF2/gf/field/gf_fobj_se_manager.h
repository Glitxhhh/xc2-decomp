#pragma once
#include <stddef.h>

#include "types.h"

namespace gf {

class GfFobjSeManager {
public:
  // Layout evidence: createSe (0x71002f58f8) stores the se id and the sound handle as one 8-byte element of
  // Vector<SeInfo>, whose erase (0x71002f5ce4) and expand (0x71002fa274) move the elements with memmove/memcpy;
  // update (0x71002f5b30) tests the handle at 0x04 with fw::SoundManager::isPlaying.
  struct SeInfo {
    u16 unknown00; // Inferred role: se id; original member name unknown.
    u32 unknown04; // Inferred role: sound handle; original member name unknown.
  };
};

static_assert(offsetof(GfFobjSeManager::SeInfo, unknown04) == 0x04, "");
static_assert(sizeof(GfFobjSeManager::SeInfo) == 0x08, "");

} // namespace gf
