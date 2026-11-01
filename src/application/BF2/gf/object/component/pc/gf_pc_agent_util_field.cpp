#include "gf/object/component/pc/gf_pc_agent_util_field.h"

#include "gf/object/component/pc/gf_com_property_pc.h"

namespace gf {
namespace pc {

void AgentUtilField::setIdleInput(GfComPropertyPc &property) { property.setInputDirPow(property.unknown1e0, 0.0f); }

} // namespace pc
} // namespace gf
