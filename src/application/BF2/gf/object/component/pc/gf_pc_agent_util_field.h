#pragma once
#include "fw/fw_param_manager.h"
#include "types.h"

namespace navi {
class NvmshAcObj;
} // namespace navi

namespace gf {

class GfComPropertyPc;

namespace pc {

// Entries of the field AI param list, in the order of gf::pc::createReflectionFieldAI; the enumerator names are unknown.
enum PARAM_ID_FIELD_AI {
  PARAM_ID_FIELD_AI_UNKNOWN_0 = 0, // Inferred role: "follow_main" (FollowMainPcParam).
  PARAM_ID_FIELD_AI_UNKNOWN_1 = 1, // Inferred role: "follow_water_main" (FollowMainPcParam).
  PARAM_ID_FIELD_AI_UNKNOWN_2 = 2, // Inferred role: "follow_buddy" (FollowBuddyPcParam).
  PARAM_ID_FIELD_AI_UNKNOWN_3 = 3, // Inferred role: "follow_water_buddy" (FollowBuddyPcParam).
  PARAM_ID_FIELD_AI_UNKNOWN_4 = 4, // Inferred role: "ai_jump" (JumpAIParam).
  PARAM_ID_FIELD_AI_UNKNOWN_5 = 5, // Inferred role: "wall_ai" (WallAiParam).
  PARAM_ID_FIELD_AI_UNKNOWN_6 = 6, // Inferred role: "high_jump_ai" (ForceWarpAiParam).
  PARAM_ID_FIELD_AI_UNKNOWN_7 = 7, // Inferred role: "water_warp_ai" (ForceWarpAiParam).
};

class AgentUtilField {
public:
  static void setIdleInput(GfComPropertyPc &property);
  static f32 setFollowInput(f32 distance, navi::NvmshAcObj *naviObject, GfComPropertyPc &property);
  static fw::ParamAdapter getAIParamAdapter(GfComPropertyPc &property, PARAM_ID_FIELD_AI id);
};

} // namespace pc
} // namespace gf
