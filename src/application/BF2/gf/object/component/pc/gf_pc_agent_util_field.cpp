#include "gf/object/component/pc/gf_pc_agent_util_field.h"

#include <float.h>
#include <math.h>

#include "gf/game/gf_game_player_formation.h"
#include "gf/object/component/pc/field/gf_pc_param_field.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "mm_math/mm_math.h"
#include "mm_mtl/intrusive_ptr.h"
#include "navi/nvmsh_ac_obj.h"

namespace gf {
namespace pc {

template <typename T, PARAM_ID_FIELD_AI ID, PARAM_ID_FIELD_AI WATER_ID> f32 funcFollowInput(f32 distance, navi::NvmshAcObj *naviObject, GfComPropertyPc &property) {
  s32 groundType = property.unknown114;
  const fw::ParamList *paramList = AgentUtilField::unknown001(property).operator->();
  const T *param = static_cast<const T *>(paramList->unknown10[groundType == 3 ? WATER_ID : ID].param);
  f32 range = fabsf(param->powMaxDist - param->powMinDist);
  f32 ratio = range > FLT_EPSILON ? (distance - param->powMinDist) / range : 0.0f;
  f32 power = mm::clamp(ratio, 0.0f, 1.0f);
  property.setInputDirPow(naviObject->getMoveVec(), power);
  return power;
}

void AgentUtilField::setIdleInput(GfComPropertyPc &property) { property.setInputDirPow(property.unknown1e0, 0.0f); }

f32 AgentUtilField::setFollowInput(f32 distance, navi::NvmshAcObj *naviObject, GfComPropertyPc &property) {
  if (GfGamePlayerFormation::get()->unknown1a0[property.unknown38].unknown10) {
    return funcFollowInput<FollowMainPcParam, PARAM_ID_FIELD_AI_UNKNOWN_0, PARAM_ID_FIELD_AI_UNKNOWN_1>(distance, naviObject, property);
  }
  return funcFollowInput<FollowBuddyPcParam, PARAM_ID_FIELD_AI_UNKNOWN_2, PARAM_ID_FIELD_AI_UNKNOWN_3>(distance, naviObject, property);
}

fw::ParamAdapter AgentUtilField::getAIParamAdapter(GfComPropertyPc &property, PARAM_ID_FIELD_AI id) {
  const fw::ParamList *paramList = unknown001(property).operator->();
  fw::ParamAdapter adapter;
  adapter.unknown00 = id < paramList->unknown0c ? &paramList->unknown10[id] : nullptr;
  return adapter;
}

} // namespace pc
} // namespace gf
