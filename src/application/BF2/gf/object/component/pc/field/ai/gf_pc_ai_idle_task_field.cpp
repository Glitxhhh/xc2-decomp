#include "gf/object/component/pc/field/ai/gf_pc_ai_idle_task_field.h"

#include "gf/game/gf_game_manager.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_agent_util_field.h"
#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/bitflag.h"

namespace gf {
namespace pc {

bool TaskFieldIdle::testCondition(const BlackBoardField &blackBoard) { return true; }

void TaskFieldIdle::update(BlackBoardField &blackBoard) {
  GfComPropertyPc *property = blackBoard.unknown08;
  AgentUtilField::setIdleInput(*property);
  if (property->unknown310.unknown10_2) {
    blackBoard.unknown200.set(3, false);
  }
}

const mm::Vec3 &getTargetFront() {
  GfComPropertyPc *leader = GfObjUtil::getObj(GfGameManager::getPartyLeader())->getComponent<GfComPropertyPc>();
  return leader->unknown1e0;
}

bool isEnableTurn(GfComPropertyPc &property, const mm::Vec3 &front) {
  const mm::Vec3 &direction = property.unknown1e0;
  return direction.x * front.x + direction.y * front.y + direction.z * front.z < 0.0f;
}

bool TaskFieldIdleTurn::testCondition(const BlackBoardField &blackBoard) {
  GfComPropertyPc *property = blackBoard.unknown08;
  const mm::Vec3 &front = getTargetFront();
  if (property->unknown310.unknown10_2 && isEnableTurn(*blackBoard.unknown08, front)) {
    return blackBoard.unknown200.test(3);
  }
  return false;
}

void TaskFieldIdleTurn::update(BlackBoardField &blackBoard) {
  const mm::Vec3 &front = getTargetFront();
  blackBoard.unknown08->setInputDirPow(front, 1.0f);
  blackBoard.unknown200.set(3, false);
}

} // namespace pc
} // namespace gf
