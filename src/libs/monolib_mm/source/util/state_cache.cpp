#include "ml/state_cache.h"

namespace ml {

void StateCache::update(u32 id) {
  int index = unknown004(id);
  unknown320->unknown003(id, unknown08[index].unknown04);
}

void *StateCache::getAdr(u32 id) {
  int index = unknown004(id);
  if (index < 0) {
    return nullptr;
  }
  return unknown08[index].unknown04;
}

} // namespace ml
