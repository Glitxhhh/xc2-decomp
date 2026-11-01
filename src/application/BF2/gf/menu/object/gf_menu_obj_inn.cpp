#include "gf/menu/object/gf_menu_obj_inn.h"

#include "gf/menu/gf_menu_fade.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_col4.h"
#include "ui/ui_object_acc.h"

namespace gf {

void GfMenuObjInn::finalize() { GfMenuObject::finalize(); }

void GfMenuObjInn::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjInn::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 1, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjInn::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 2, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

bool GfMenuObjInn::seqFadeOut() {
  GfMenuFade::setFade(2, 60, mm::Col4::black);
  return true;
}

bool GfMenuObjInn::seqFadeOutWait() {
  ui::UIObjectAcc acc(unknown18);
  bool isEnd;
  if (GfMenuFade::isFading(2)) {
    isEnd = false;
  } else {
    closeFSLayer(acc.unknown10, true, true);
    isEnd = true;
  }
  return isEnd;
}

} // namespace gf
