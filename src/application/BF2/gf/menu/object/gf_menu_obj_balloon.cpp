#include "gf/menu/object/gf_menu_obj_balloon.h"

#include "gf/menu/gf_menu_reference_item.h"
#include "mm_mtl/reference_object.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjBalloon::GfMenuObjBalloon(u32 handle) : GfMenuObject(handle), unknown28(0), unknown30(0), unknown38(nullptr), unknown40(nullptr), unknown78(this), unknown1d8(false), unknown1dc(0xffffffff) {
  unknown60.assign(mm::mtl::IntrusivePtr<GfMenuReferenceItem>());
}

GfMenuObjBalloon::~GfMenuObjBalloon() {
  unknown60.assign(mm::mtl::IntrusivePtr<GfMenuReferenceItem>());
  unknown48.clear();
  mm::mtl::safeRelease(unknown40);
  mm::mtl::safeRelease(unknown38);
}

void GfMenuObjBalloon::finalize() { GfMenuObject::finalize(); }

void GfMenuObjBalloon::update() {
  unknown78.unknown003();
  GfMenuObject::update();
}

void GfMenuObjBalloon::resetFeeling(ui::UIObjectAcc &acc) { acc.setAddColor("black"); }

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjBalloon>(const mm::mtl::Delegate<bool()> *);
template void mm::mtl::FixedArray<mm::mtl::IntrusivePtr<gf::GfMenuReferenceItem>, 3>::assign(const mm::mtl::IntrusivePtr<gf::GfMenuReferenceItem> &);
template mm::mtl::FixedArray<mm::mtl::IntrusivePtr<gf::GfMenuReferenceItem>, 3>::~FixedArray();
