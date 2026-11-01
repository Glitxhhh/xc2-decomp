#include "gf/object/component/pc/gf_pc_property_pc_interface.h"

namespace gf {
namespace pc {

void GfPropertyPcInterface::flushOwner(GfComPropertyPc &property) {}

bool GfPropertyPcInterface::recieveMessage(const GfComPropertyPc &property, fw::MessageObject *sender, fw::Message &message) { return false; }

} // namespace pc
} // namespace gf
