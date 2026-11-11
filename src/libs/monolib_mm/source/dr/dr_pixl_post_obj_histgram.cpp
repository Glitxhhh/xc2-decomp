#include "dr/dr_pixl_post_obj_histgram.h"

#include "dr/dr_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_post_man.h"
#include "dr/dr_pixl_post_obj_tone_map.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_pixl_render_target.h"
#include "dr/dr_res_use_query_obj.h"
#include "grlib/cglib_render_target.h"
#include "mm_math/mm_math.h"
#include "mm_mtl/fixed_array.h"

namespace ml {

DrPixlPostObjHistgram::~DrPixlPostObjHistgram() {
  DrResUseQueryObj *query = unknown18;
  if (query != nullptr) {
    delete query;
    unknown18 = nullptr;
  }
}

void DrPixlPostObjHistgram::update() {
  if (unknown00->unknown058()) {
    return;
  }
  unknown18->update();
  DrMan *drMan = unknown00;
  if (drMan->unknown120[drMan->unknown1c98]->unknownf54) {
    for (int i = 0; i < getSectionNum(); i++) {
      unknown78[i] = 0;
    }
    unknownb4 = getSectionNum();
  }
  f32 total;
  if (unknowna4 < 0) {
    total = 0.0f;
  } else {
    u32 pixel = unknown18->m_pixel;
    u32 index = (unknowna4 + getSectionNum() - 1) % getSectionNum();
    u32 sum = 0;
    for (int i = 0; i < getSectionNum(); i++) {
      sum += unknown78[i];
    }
    total = static_cast<f32>(sum + pixel - unknown78[index]);
    m_percentage[index] = static_cast<f32>(pixel) / total;
    unknown78[index] = pixel;
    unknowna4 = (unknowna4 + 1) % getSectionNum();
  }
  bool isValid = false;
  if (unknownb4 > 0) {
    DrPixlPostParm *postParm = drMan->unknown120[drMan->unknown1c98];
    f32 min = postParm->unknown28;
    f32 max = postParm->unknown2c;
    min *= postParm->unknown08;
    max *= postParm->unknown08;
    unknownac = max;
    unknownb0 = min;
    unknown08->setToneAveRange(min, max);
    unknownb4--;
  } else {
    u32 height;
    u32 width;
    if (!drMan->unknown1de8) {
      DrPixlRenderTarget *target = unknown08->unknown7f0->unknown00[5][0];
      width = mm::min(mm::max(80u, target->unknownbc >> drMan->unknown1de4), target->unknownbc);
      height = mm::min(mm::max(45u, target->unknownc0 >> drMan->unknown1de4), target->unknownc0);
    } else {
      grlib::CGLibRenderTarget *target = unknown08->unknown7f0->unknown180->unknown18->unknown18[0];
      width = target->unknownbc;
      height = target->unknownc0;
    }
    if (total / static_cast<f32>(width * height) >= 0.05f) {
      DrPixlPostParm *postParm = drMan->unknown120[drMan->unknown1c98];
      f32 min = postParm->unknown28;
      f32 max = postParm->unknown2c;
      if (min >= max) {
        if (max <= 0.01f) {
          min = 0.0f;
          max = 0.01f;
        } else {
          min = max - 0.01f;
        }
      }
      unknownb0 += (calcLuminanceAve(min, true) - unknownb0) * 0.05f;
      unknownac += (calcLuminanceAve(max, false) - unknownac) * 0.05f;
      unknown08->setToneAveRange(unknownb0, unknownac);
      isValid = true;
    }
  }
  unknownb8 = isValid;
}

f32 DrPixlPostObjHistgram::calcLuminanceAve(f32 rate, bool isLow) const {
  f32 total = 0.0f;
  for (u32 i = 0; i < static_cast<u32>(getSectionNum()); i++) {
    total += m_percentage[i];
    if (rate <= total) {
      unknown001 section = getSection(i);
      return isLow ? section.unknown00 : section.unknown04;
    }
  }
  return 0.0f;
}

DrPixlPostObjHistgram::unknown001 DrPixlPostObjHistgram::getSection(u32 index) const {
  unknown001 section;
  if (index == 0) {
    section.unknown00 = 0.0f;
  } else {
    section.unknown00 = m_maxLuminance[index - 1];
  }
  section.unknown04 = m_maxLuminance[index];
  return section;
}

f32 DrPixlPostObjHistgram::getMaxLuminance() const { return m_maxLuminance[9]; }

int DrPixlPostObjHistgram::getSectionNum() const { return 0xb; }

f32 DrPixlPostObjHistgram::getPercentage(u32 index) const { return m_percentage[index]; }

} // namespace ml
