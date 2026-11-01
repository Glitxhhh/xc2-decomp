#include "gf/object/component/pc/field/ai/gf_pc_ai_sensor_task_field.h"

#include <math.h>

#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/param/gf_pc_param.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace gf {
namespace pc {

bool TaskFieldSensor::testCondition(const BlackBoardField &blackBoard) { return true; }

bool isStack(const GfComPropertyPc &property, const SensorAIParam &param, f32 time) {
  mm::Vec3 direction = property.unknown80;
  f32 speed = sqrtf(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
  if (!(fabsf(direction.x) <= 0.000001f) || !(fabsf(direction.y) <= 0.000001f) || !(fabsf(direction.z) <= 0.000001f)) {
    f32 length = sqrtf(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
    if (length <= 0.000001f) {
      direction = mm::Vec3::zero;
    } else {
      f32 inverse = 1.0f / length;
      direction.x = direction.x * inverse;
      direction.y = direction.y * inverse;
      direction.z = direction.z * inverse;
    }
  }

  mm::Vec3 move = property.unknown160 - property.unknown180;
  f32 moveDistance = direction.x * move.x + direction.y * move.y + direction.z * move.z;
  return speed * time - moveDistance >= param.stackThreashold;
}

} // namespace pc
} // namespace gf
