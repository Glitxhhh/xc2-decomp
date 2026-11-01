#include "dr/dr_pixl_post_obj_depthof_field.h"

#include "dr/dr_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_res_filter_data.h"
#include "grlib/cglib_render_target.h"

namespace ml {

DrPixlPostObjDepthofField::~DrPixlPostObjDepthofField() {
  unknown001(unknown18);
  unknown001(unknown20);
  unknown001(unknown28);
  unknown001(unknown30);
  unknown001(unknown38);
  unknown001(unknown48);
  unknown001(unknown40);
}

void DrPixlPostObjDepthofField::update() {
  s32 pixlLv = unknown00->unknown120[unknown00->unknown1c98]->unknown238;
  if (unknown50 != pixlLv) {
    unknown50 = pixlLv;
    if (pixlLv == 0) {
      unknown54 = 1.0f;
    } else if (pixlLv == 1) {
      unknown54 = 2.0f;
    } else {
      unknown54 = 4.0f;
    }
    resetColorBuff();
  }
  unknown59 = false;
  DrPixlPostParm *postParm = unknown00->unknown120[unknown00->unknown1c98];
  if (postParm->m_colTblOn) {
    DrResFilterData *filterData = unknown00->unknown98;
    f32 ratio = filterData->unknown10[filterData->unknown100].unknown34;
    unknown59 = postParm->unknown274;
    if (ratio == 1.0f && postParm->unknown278 == postParm->unknown26c && filterData->unknown10[filterData->unknown100].unknown26 == postParm->unknown278 &&
        filterData->unknown10[filterData->unknown100].unknown24 == postParm->unknown278) {
      unknown59 = false;
    }
  }
}

void DrPixlPostObjDepthofField::releaseColorBuff() {
  unknown18->releaseTexture();
  unknown20->releaseTexture();
  unknown28->releaseTexture();
  unknown30->releaseTexture();
  unknown38->releaseTexture();
  unknown48->releaseTexture();
}

} // namespace ml
