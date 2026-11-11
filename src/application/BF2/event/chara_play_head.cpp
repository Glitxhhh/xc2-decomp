#include "event/chara_play_head.h"

#include "event/chara_obj.h"
#include "event/chara_weight_item.h"
#include "event/chara_weight_player.h"
#include "event/cmd_variable.h"
#include "event/curve.h"
#include "event/frame_manager.h"
#include "event/skip_manager.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/gf_obj_util.h"
#include "mm_mtl/singleton.h"

namespace event {

void CharaPlayHead::idle() {
  if (gf::GfObjUtil::getObj(unknown10) != nullptr && (unknown08 & FLAG_UNKNOWN_0) != 0) {
    const char *stat = type2stat(unknown20);
    u32 blendOutFlag = unknown08 & FLAG_UNKNOWN_2;
    f32 blend = 0.0f;
    if (!mm::mtl::Singleton<SkipManager>::getPtr()->isSkip() && blendOutFlag != 0) {
      blend = type2blend(unknown20);
    }
    unknown18->easeOut(gf::ANIM_LAYER_UNKNOWN_2, stat, blend, CV_TYPE_UNKNOWN_2, WEIGHT_LAYER_UNKNOWN_0);
    unknown20 = 0;
    unknown24 = -1.0f;
    unknown28 = "";
  }
  unknown08 = 0;
}

void CharaPlayHead::init() { unknown08 = 0; }

ICmd::RESULT CharaPlayHead::update(const Param &param) {
  if (gf::GfObjUtil::getObj(unknown10) == nullptr) {
    return RESULT_UNKNOWN_1;
  }
  f32 delta = static_cast<CharaObj *>(param.val(0).getUserdata())->getFrameInfo().unknown04;
  if (param.getFrame() <= 0) {
    play(param.val(1).getS32(), param.val(2).getF32(), param.val(3).getBool(), param.val(4).getBool());
  }
  if ((unknown08 & FLAG_UNKNOWN_1) == 0) {
    unknown24 -= delta;
    if (unknown24 < 0.0f) {
      idle();
      return RESULT_UNKNOWN_1;
    }
  }
  return RESULT_UNKNOWN_2;
}

void CharaPlayHead::term() { idle(); }

} // namespace event
