#include "gf/object/component/pc/gf_pc_util.h"

#include "ai/ai_state.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_state_id.h"

namespace gf {
namespace pc {

bool IsBuddy(GfComPropertyPc &property) { return property.unknown38 & 1; }

bool isWallState(ai::State *state) {
  while (state != nullptr) {
    if (state->unknown08 == STATE_ID_FIELD_WALL) {
      return true;
    }

    state = state->unknown10;
  }

  return false;
}

} // namespace pc
} // namespace gf
