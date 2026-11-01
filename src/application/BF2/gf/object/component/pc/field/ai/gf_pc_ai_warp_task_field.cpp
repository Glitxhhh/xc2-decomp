#include "gf/object/component/pc/field/ai/gf_pc_ai_warp_task_field.h"

#include "fw/fw_param_manager.h"
#include "fw/fw_transform.h"
#include "gf/game/gf_game_player_formation.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/gf_obj_property.h"
#include "gf/object/gf_obj_util.h"
#include "mm/mm_std_base.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/rtti.h"

namespace gf {
namespace pc {

void TaskFieldCheckWarpBattleWaterDead::onEvent(ai::BlackBoard &blackBoard, const ai::Event &event) {
  BlackBoardField *pBB = mm::mtl::dynamicCast<BlackBoardField>(&blackBoard);
  // __LINE__ must be 191 as in the original file: it is the line argument of the assert.
#line 191
  MM_ASSERT(pBB);
  switch (event.unknown00) {
  case ai::UNKNOWN002_UNKNOWN_1:
    onChangeActivate(*pBB, static_cast<const ai::ActivateEvent &>(event));
    break;
  case ai::UNKNOWN002_UNKNOWN_2:
    onCreate(*pBB, static_cast<const ai::CreateEvent &>(event));
    break;
  }
}

void TaskFieldCheckWarpBattleWaterDead::onChangeActivate(BlackBoardField &blackBoard, const ai::ActivateEvent &event) {
  if (event.unknown04) {
    unknown38 = 0.0f;
  }
}

void TaskFieldCheckWarpBattleWaterDead::onCreate(BlackBoardField &blackBoard, const ai::CreateEvent &event) {
  mm::mtl::IntrusivePtr<fw::ParamList> paramList = fw::ParamManager::get()->unknown458;
  if (paramList.get() != nullptr) {
    unknown40.unknown00 = paramList->unknown0c > 0 ? &paramList->unknown10[0] : nullptr;
  }
}

bool TaskFieldCheckWarpBattleWaterDead::testCondition(const BlackBoardField &blackBoard) { return blackBoard.unknown08->unknown310.unknown11_7 && blackBoard.unknown08->unknown111_3; }

bool TaskFieldCheckWarpFallDead::testCondition(const BlackBoardField &blackBoard) { return blackBoard.unknown08->unknown111_3; }

void TaskFieldCheckWarpFallDead::update(BlackBoardField &blackBoard) {
  GfComPropertyPc *property = blackBoard.unknown08;
  GfGamePlayerFormation *formation = GfGamePlayerFormation::get();
  GfObjProperty *mainProperty = GfObjUtil::getProperty(formation->unknown1a0[formation->unknown1a0[property->unknown38].unknown00].unknown08);
  if (mainProperty->unknown18 == nullptr || mainProperty->unknown18->unknown00 == PROPERTY_MOVE_WALK) {
    fw::Transform transform = formation->getFollowTransform(property->unknown38);
    transform.unknown00 = formation->unknown80[property->unknown38];
    property->unknown003(transform, 3);
  }
}

} // namespace pc
} // namespace gf
