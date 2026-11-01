#include "gf/object/component/pc/field/gf_pc_state_field_water_dead_sink.h"

#include "fw/fw_param_manager.h"
#include "fw/fw_update_info.h"
#include "gf/object/component/pc/field/gf_pc_param_field.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_move_util_field.h"
#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "mm_mtl/intrusive_ptr.h"

namespace gf {
namespace pc {

void StateFieldWaterDeadSink::leave(GfComBehaviorPc *behavior, ai::State *next) {}

void StateFieldWaterDeadSink::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComPropertyPc *property = behavior->getProperty();
  const fw::ParamList *list = property->unknown310.unknown08.operator->();
  const fw::ParamList::unknown005 *entry = list->unknown0c > 9 ? &list->unknown10[9] : nullptr;
  const WaterCommonParam *param = entry != nullptr ? static_cast<const WaterCommonParam *>(entry->param) : nullptr;
  unknown18 += info.unknown04;
  if (property->unknown110_4 || unknown18 >= param->sinkTime) {
    reqState(STATE_ID_FIELD_WATER_DEAD_RISE);
  } else if (StateUtilField::getChildFrameHeight(*behavior) <= -param->sinkDepth) {
    property->unknown90 = 0.0f;
  } else {
    MoveUtilField::updateMoveWaterSink(info, *property);
  }
}

} // namespace pc
} // namespace gf
