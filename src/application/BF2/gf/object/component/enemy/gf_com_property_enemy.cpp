#include "gf/object/component/enemy/gf_com_property_enemy.h"

#include "framework/object/updatable_object.h"
#include "framework/reference_frame.h"
#include "fw/fw_transform.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_setup.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/rtti.h"

namespace gf {

GfComPropertyEnemy::GfComPropertyEnemy() : unknown60(mm::Vec3::zero), unknown70(mm::Quat::identity), unknown80(mm::Vec3::zero), unknown90(mm::Quat::identity) {}

GfComPropertyEnemy::~GfComPropertyEnemy() {}

void GfComPropertyEnemy::writeBack() {
  unknown60 = unknown80;
  unknown70 = unknown90;
}

void GfComPropertyEnemy::flush() {
  unknown40.Update(*this);
  const fw::Transform &transform = unknown08->getComponent<GfComTransform>()->unknown001()->unknown40;
  unknown80 = transform.unknown00;
  unknown90 = transform.unknown10;
}

void GfComPropertyEnemy::cleanup() { unknown40.Finalize(*this); }

f32 GfComPropertyEnemy::getChestHeight() const {
  DataParamAcc acc(static_cast<GfObj *>(unknown08)->unknownf8);
  f32 height = acc.getChestHeight() * 0.01f;
  GfObjSetupEnemy *setup = mm::mtl::dynamicCast<GfObjSetupEnemy>(GfObjManager::getObjInfo(static_cast<GfObj *>(unknown08)->unknownf8)->unknown30);
  return height * setup->unknown40;
}

const mm::mtl::RTTI *GfComPropertyEnemy::getRTTI() const { return &m_rtti; }

} // namespace gf
