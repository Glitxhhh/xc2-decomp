#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/component/pc/field/gf_pc_param_field.h"
#include "gf/object/component/pc/gf_com_property_pc.h"

namespace gf {
namespace pc {

void GfPropertyField::resetStatus(const GfComPropertyPc &property) {
  if (property.unknown111_2) {
    unknown10_3 = true;
  }
  unknown12_1 = true;
}

void GfPropertyField::flushOwner(GfComPropertyPc &property) {
  if (unknown11_3) {
    property.unknown110_4 = true;
    property.unknown110_7 = true;
  }
}

void GfPropertyField::cleanup(const GfComPropertyPc &property) {}

void GfPropertyField::setBigJumpInfo(const MsgPcFieldNotifyBigJump *message) {
  if (message != nullptr) {
    unknown11_4 = true;
    unknown80 = *message;
  } else {
    unknown11_4 = false;
  }
}

const MsgPcFieldNotifyBigJump *GfPropertyField::getBigJumpInfo() const { return unknown11_4 ? &unknown80 : nullptr; }

void GfPropertyField::setWarpInfo(const MsgPcFieldNotifyWarp *message) {
  if (message != nullptr) {
    unknown11_5 = true;
    unknownc0 = *message;
  } else {
    unknown11_5 = false;
  }
}

const MsgPcFieldNotifyWarp *GfPropertyField::getWarpInfo() const { return unknown11_5 ? &unknownc0 : nullptr; }

void GfPropertyField::setWallJump(const MsgPcFieldNotifyWallJump *message) {
  if (message != nullptr) {
    unknown11_6 = true;
    unknown100 = *message;
  } else {
    unknown11_6 = false;
  }
}

const MsgPcFieldNotifyWallJump *GfPropertyField::getWallJumpInfo() const { return unknown11_6 ? &unknown100 : nullptr; }

f32 GfPropertyField::getWallHeightOffset() const { return static_cast<const WallCommonParam *>(unknown08->unknown10[15].param)->wallHeightRatio * unknown28; }

} // namespace pc
} // namespace gf
