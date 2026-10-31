#include "gf/object/component/model/gf_com_model.h"

#include "fw/fw_model_object.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_util.h"

namespace fw {
class MessageObject;
} // namespace fw

namespace gf {

bool GfComModel::isRender() const {
  if (unknown18 != nullptr) {
    return unknown18->isRender();
  }

  return false;
}

bool GfComModel::isVolumeFadeForUser() const { return GfObjUtil::isVolumeFadeForUser(static_cast<GfObj *>(unknown08)->unknownf8); }

void GfComModel::procMsgObjectNotifyDead(fw::MessageObject *, MsgObjectNotifyDead &) {}

void GfComModel::procMsgObjectNotifyDamage(fw::MessageObject *, MsgObjectNotifyDamage &) {}

void GfComModel::procMsgActivateComponentDebugWindow(fw::MessageObject *, MsgDebugActivateComponentWindow &) {}

} // namespace gf

template void mm::mtl::Vector<gf::GfComModel::BoneFrameInfo>::destroy();
template void mm::mtl::Vector<gf::GfComModel::BoneFrameInfo>::push_back(const gf::GfComModel::BoneFrameInfo &);
template gf::GfComModel::BoneFrameInfo *mm::mtl::Vector<gf::GfComModel::BoneFrameInfo>::erase(gf::GfComModel::BoneFrameInfo *);
template void mm::mtl::Vector<gf::GfComModel::BoneFrameInfo>::expand(size_t, size_t);
