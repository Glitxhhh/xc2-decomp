#include "gf/object/component/behavior/movement/gf_move_slide.h"

#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"

namespace gf {

void GfMoveSlideControler::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 15
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(Param));
#line 16
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("sideVel", offsetof(Param, sideVel), 0.0f, 10000.0f, 1.0f));
#line 17
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("frontBrake", offsetof(Param, frontBrake), 0.0f, 1000.0f, 15.0f));
#line 18
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("angularVelMin", offsetof(Param, angularVelMin), 0.0f, 10000.0f, 10.0f));
#line 19
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("angularVelMaxs", offsetof(Param, angularVelMaxs), 0.0f, 10000.0f, 10.0f));
  reflection->setReflectionStruct(index, value);
}

} // namespace gf
