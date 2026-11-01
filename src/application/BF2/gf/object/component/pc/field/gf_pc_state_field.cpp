#include "gf/object/component/pc/field/gf_pc_state_field.h"

#include "framework/object/updatable_object.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/bitflag.h"

namespace gf {
namespace pc {

void StateField::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  GfObjUtil::setEnableEyeBlink(static_cast<GfObj *>(behavior->unknown08)->unknownf8, true);
  StateUtilField::setLookAtFlag(*behavior, true);
  StateUtil::setEnableLookIK(*behavior, true);
  StateUtil::setEnableAgentField(*behavior, true);
  StateUtil::setEnableDownIK(*behavior, false);
  StateUtil::switchPlacementIK(*behavior, true);
  StateUtil::setEnableHeadDetectForSwitcher(*behavior, true);
  behavior->getProperty()->unknown110_0 = true;
  StateUtil::setEnvSensor(*behavior, 0xd0, true);
  StateUtil::setFallDamageDisable(*behavior, false);
  StateUtil::setEnableSpineIK(*behavior, true);
  StateUtil::setEnableAttach(*behavior, true);
  StateUtil::setEnableTimer(*behavior, true);
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  property->unknown80 = mm::Vec3::zero;
  property->unknown90 = 0.0f;
  property->unknown94 = 0.0f;
}

void StateField::leave(GfComBehaviorPc *behavior, ai::State *next) {
  GfObjUtil::setEnableEyeBlink(static_cast<GfObj *>(behavior->unknown08)->unknownf8, false);
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  StateUtilField::setAutoRun(*property, false);
  StateUtilField::setLookAtFlag(*behavior, false);
  StateUtil::setEnableAgentField(*behavior, false);
  property->unknown110_0 = false;
  StateUtil::setEnvSensor(*behavior, 0xd0, false);
  StateUtil::setEnableHeadDetectForSwitcher(*behavior, false);
  StateUtil::setEnableSpineIK(*behavior, false);
  StateUtil::switchPlacementIK(*behavior, false);
  StateUtil::setEnableAttach(*behavior, false);
  StateUtil::setEnableTimer(*behavior, false);
}

void StateField::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComPropertyPc *property = behavior->getProperty();
  if (property->unknown60.unknown08.test(INPUT_ID_LOCK)) {
    StateUtilField::flipAutoRun(*property);
  }
  if (StateUtilField::isInputInverseDirAutoRun(*property)) {
    StateUtilField::setAutoRun(*property, false);
  }
  if (StateUtilField::testAutoRun(*property)) {
    StateUtilField::setAutoRunInput(*property);
  }
}

} // namespace pc
} // namespace gf
