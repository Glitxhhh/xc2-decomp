#include "gf/object/component/pc/param/gf_pc_param.h"

#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"

namespace gf {
namespace pc {

void InputParam::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 15
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(InputParam));
#line 16
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("threshold", offsetof(InputParam, threshold), 0.0f, 1.0f, 0.1f));
  reflection->setReflectionStruct(index, value);
}

void SensorAIParam::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 45
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(SensorAIParam));
#line 46
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("stackThreashold", offsetof(SensorAIParam, stackThreashold), 0.0f, 1000.0f, 0.1f));
#line 47
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("obstacleAngle", offsetof(SensorAIParam, obstacleAngle), 0.0f, 90.0f, 45.0f));
#line 48
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("enableJumpOffset", offsetof(SensorAIParam, enableJumpOffset), 0.0f, 1000.0f, 0.3f));
#line 49
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("enableJumpCeil", offsetof(SensorAIParam, enableJumpCeil), 0.0f, 1000.0f, 2.0f));
  reflection->setReflectionStruct(index, value);
}

} // namespace pc
} // namespace gf
