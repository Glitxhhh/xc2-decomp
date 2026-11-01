#include "gf/object/component/pc/field/gf_pc_state_field_water_normal.h"

#include "ai/ai_state.h"
#include "framework/object/updatable_object.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/behavior/gf_com_behavior.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "gf/object/component/pc/plugin/gf_pc_access_plugin.h"
#include "gf/object/gf_obj.h"
#include "mm_mtl/bitflag.h"

namespace gf {
namespace pc {

void StateFieldWaterNormal::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  StateUtilField::setAccessFlag(*behavior, true);
  AccessPlugin *plugin = behavior->unknown001<AccessPlugin>(4);
  if (plugin != nullptr) {
    plugin->unknown28 = 16;
  }
}

void StateFieldWaterNormal::leave(GfComBehaviorPc *behavior, ai::State *next) {
  if (next != nullptr && next->unknown08 != STATE_ID_FIELD_WATER_PREPARE_WARP) {
    StateUtilField::setAccessFlag(*behavior, false);
  }
  AccessPlugin *plugin = behavior->unknown001<AccessPlugin>(4);
  if (plugin != nullptr) {
    plugin->unknown28 = 0;
  }
}

void StateFieldWaterNormal::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  GfObj *target = StateUtilField::getAccessTarget(*behavior);
  if (target != nullptr && property->unknown60.unknown08.test(INPUT_ID_DECIDE)) {
    MsgPcFieldGetAccessType message;
    static_cast<GfObj *>(behavior->unknown08)->sendMessage(target, message);
    if (message.unknown08 == 4) {
      reqState(STATE_ID_FIELD_WATER_PREPARE_WARP);
    }
  }
}

void StateFieldWaterNormal::onDead(GfComBehaviorPc *behavior, MsgObjectNotifyDead &message) {
  StateUtil::notifyDead(*behavior, message, true);
  behavior->unknown08->getComponent<GfComAsm>()->execCmd("C_waterdead", ANIM_LAYER_BASE);
  reqState(STATE_ID_FIELD_WATER_DEAD_SINK);
}

} // namespace pc
} // namespace gf
