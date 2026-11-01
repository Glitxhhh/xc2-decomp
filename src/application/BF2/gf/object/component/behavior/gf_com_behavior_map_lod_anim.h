#pragma once
#include "gf/field/gf_field_lod.h"
#include "gf/object/component/behavior/gf_com_behavior.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

class GfComBehaviorMapLodAnim : public GfComBehavior {
public:
  static mm::mtl::RTTI m_rtti;

  void update(const fw::UpdateInfo &info) override;
  GfFieldLodColiAnim::PosInfo *getBindedPosInfo() const;
  const mm::mtl::RTTI *getRTTI() const override;
};

static_assert(sizeof(GfComBehaviorMapLodAnim) == 0x98, "");

} // namespace gf
