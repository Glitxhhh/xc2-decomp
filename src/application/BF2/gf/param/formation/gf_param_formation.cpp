// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/gf/param/formation/gf_param_formation.cpp.
#include <stddef.h>

#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"
#include "gf/game/gf_game_player_formation.h"
#include "types.h"

namespace gf {

void WarpForRandomTalkParam::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 27
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(WarpForRandomTalkParam));
#line 28
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("distVert", offsetof(WarpForRandomTalkParam, distVert), 0.0f, 1000.0f, 5.0f));
#line 29
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("distHorz", offsetof(WarpForRandomTalkParam, distHorz), 0.0f, 1000.0f, 5.0f));
  reflection->setReflectionStruct(index, value);
}

} // namespace gf
