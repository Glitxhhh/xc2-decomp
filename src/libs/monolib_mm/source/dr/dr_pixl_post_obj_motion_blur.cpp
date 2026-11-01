#include "dr/dr_pixl_post_obj_motion_blur.h"

#include "dr/dr_pixl_post_obj.h"
#include "grlib/cglib_render_target.h"

namespace ml {

DrPixlPostObjMotionBlur::~DrPixlPostObjMotionBlur() {
  unknown001(unknown28);
  unknown001(unknown30);
  unknown001(unknown20);
}

void DrPixlPostObjMotionBlur::debugRender() {}

void DrPixlPostObjMotionBlur::resetColorBuff() { calcBludBuffColorBuff(); }

void DrPixlPostObjMotionBlur::releaseColorBuff() {
  unknown28->releaseTexture();
  unknown30->releaseTexture();
  unknown20->releaseTexture();
}

} // namespace ml
