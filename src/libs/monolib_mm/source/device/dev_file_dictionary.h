#pragma once
#include <stddef.h>
#include <string.h>

#include "types.h"

namespace ml {

// Double-array trie mapping a file name to an index. The template arguments are those of the game's symbols:
// the value type, the allocator, the value returned for a key without value (-1) and for a missing path (-2), and a flag (true).
template <typename T, typename ALLOC, int NO_VALUE, int NO_PATH, bool FLAG> class DevFileDictionary {
public:
  ~DevFileDictionary() { clear(false); }

  void clear(bool reuse);
  T findImpl(const char *key, size_t &from, size_t &pos, size_t len) const;

  // Inferred role: exact search of a whole key, a missing path reported as a missing value (inlined in DevFileArchiver::getFileInfo); original name unknown.
  T unknown001(const char *key) const {
    size_t len = strlen(key);
    size_t from = 0;
    size_t pos = 0;
    T result = findImpl(key, from, pos, len);
    if (result == NO_PATH) {
      result = NO_VALUE;
    }
    return result;
  }

  void *unknown00;  // Inferred role: node array, released by clear; original member name unknown.
  void *unknown08;  // Inferred role: tail array, released by clear; original member name unknown.
  void *unknown10;  // Inferred role: tail index array allocated by loadFromMemory; original member name unknown.
  void *unknown18;  // Inferred role: node info array rebuilt by restoreNinfo; original member name unknown.
  void *unknown20;  // Inferred role: block array rebuilt by restoreBlock; original member name unknown.
  s32 unknown28;    // Inferred role: block list head; original member name unknown.
  s32 unknown2c;    // Inferred role: block list head; original member name unknown.
  s32 unknown30;    // Inferred role: block list head; original member name unknown.
  s32 unknown34;    // Inferred role: capacity, set from the node count by loadFromMemory; original member name unknown.
  s32 unknown38;    // Inferred role: tail size set by loadFromMemory; original member name unknown.
  s32 unknown3c;    // Inferred role: first tail word read by loadFromMemory; original member name unknown.
  s32 unknown40;    // Inferred role: set to 1 by loadFromMemory; original member name unknown.
  bool unknown44;   // Inferred role: arrays borrowed from loaded memory, not released by clear; original member name unknown.
  ALLOC *unknown48; // Inferred role: allocator of the arrays; original member name unknown.
};

} // namespace ml
