#include "dr/dr_pixl_post_man.h"

#include "dr/dr_man.h"
#include "dr/dr_pixl_man.h"
#include "dr/dr_pixl_post_obj_capture.h"
#include "dr/dr_pixl_post_obj_cube_map_ibl.h"
#include "dr/dr_pixl_post_obj_cube_map_multi_ibl.h"
#include "dr/dr_pixl_post_obj_depthof_field.h"
#include "dr/dr_pixl_post_obj_exp_stencil.h"
#include "dr/dr_pixl_post_obj_glass_br.h"
#include "dr/dr_pixl_post_obj_histgram.h"
#include "dr/dr_pixl_post_obj_motion_blur.h"
#include "dr/dr_pixl_post_obj_motion_blur2.h"
#include "dr/dr_pixl_post_obj_rain_drop.h"
#include "dr/dr_pixl_post_obj_ssr.h"
#include "dr/dr_pixl_post_obj_tmaa.h"
#include "dr/dr_pixl_post_obj_tone_map.h"
#include "dr/dr_pixl_post_obj_tssao.h"
#include "dr/dr_pixl_post_obj_unbranch_to_depth.h"
#include "dr/dr_pixl_post_obj_volume.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_pixl_shadow_raytrace.h"
#include "dr/dr_pixl_sky_dome.h"
#include "dr/dr_pixl_toon_grad.h"
#include "dr/dr_res_use_query_obj.h"
#include "mm_math/mm_vec3.h"
#include "mtl/alloc_handle.h"

namespace ml {

void DrPixlPostMan::setReflection(f32 x, f32 y, f32 z, bool isHigh) {
  u32 flags = unknownf8;
  u32 mask = isHigh ? 0x60000 : 0x20000;
  unknownfc = x;
  unknown100 = y;
  unknown104 = z;
  unknownf8 = flags | mask;
}

void DrPixlPostMan::setDownDepth() { unknownf8 |= FLAG_DEPTH_DOWN; }

void DrPixlPostMan::renderDeferred() {}

void DrPixlPostMan::renderDeferredLast() {
  if (unknown18 != nullptr) {
    unknown18->fastRender();
  }
  if (unknown60 != nullptr) {
    unknown60->render();
  }
}

DrPixlRenderTarget *DrPixlPostMan::getDownDepth() { return unknownc0[DrMan::s_nDblIdx]; }

bool DrPixlPostMan::isCalcVolume() { return unknownf8 & FLAG_CALC_VOLUME; }

void DrPixlPostMan::setRefRactionMap() { unknownf8 |= FLAG_REFRACTION_MAP; }

bool DrPixlPostMan::renderRefractionBegin() {
  if (!(unknownf8 & FLAG_REFRACTION_MAP)) {
    return false;
  }
  if (unknownf0 != nullptr) {
    unknownf0->begin(unknown08->unknown7f8);
  }
  return true;
}

void DrPixlPostMan::renderRefractionEnd() {
  if (unknownf0 != nullptr) {
    unknownf0->end();
  }
}

void DrPixlPostMan::renderSkyDome() {
  if (unknown90 != nullptr) {
    unknown90->baseRender();
  }
}

void DrPixlPostMan::renderSkyGodRay() {
  if (unknown90 != nullptr) {
    unknown90->godRayRender();
  }
}

void DrPixlPostMan::renderRainDrop() {
  if (unknowna0 != nullptr) {
    unknowna0->render();
  }
}

void DrPixlPostMan::renderTMAA() {
  if (unknown00->unknown120[unknown00->unknown1c98]->m_TMAAOn) {
    unknown68->render();
  }
}

void DrPixlPostMan::renderDeferredFast_AfterTemporal() {
  if (unknown78 != nullptr) {
    unknown78->render_afterTemporal();
  }
}

void DrPixlPostMan::renderDeferredFast() {
  bool isTemporal = unknown00->isTemporalUPSToGlobalIBL() || unknown00->unknown120[unknown00->unknown1c98]->m_TMAAOn;
  if (getDownDepth() != nullptr) {
    renderDownDepth(true, isTemporal, true);
  }
  if (unknownb8 != nullptr) {
    unknownb8->render();
  }
  if (unknown80 != nullptr) {
    unknown80->render();
  }
  if (unknown78 != nullptr) {
    unknown78->render_beforeTemporal();
  }
  if (unknown88 != nullptr) {
    unknown88->render_beforeTemporal();
  }
  if (unknown70 != nullptr) {
    unknown70->render();
  }
}

void DrPixlPostMan::fastRender() {
  if (unknown40 != nullptr) {
    unknown40->render();
  }
  if (unknown48 != nullptr) {
    unknown48->render();
  }
  if (unknown98 != nullptr) {
    unknown98->render();
  }
}

void DrPixlPostMan::capRender() {
  if (unknownb0 != nullptr) {
    unknownb0->render();
  }
}

void DrPixlPostMan::setGlassBreak(bool isGlassBreak) {
  DrPixlPostObjGlassBr *glassBreak = unknowna8;
  if (glassBreak == nullptr) {
    if (isGlassBreak) {
      unknowna8 = new (unknown00->unknown0c) DrPixlPostObjGlassBr(unknown00, unknown08, this);
    }
  } else if ((glassBreak->unknown508 & DrPixlPostObjGlassBr::FLAG_UNKNOWN_3) == 0) {
    if (!isGlassBreak) {
      glassBreak->unknown508 |= DrPixlPostObjGlassBr::FLAG_UNKNOWN_2;
    }
  } else {
    delete glassBreak;
    unknowna8 = nullptr;
  }
}

void DrPixlPostMan::setCaputureMode(bool isCapture) {
  DrPixlPostObjCapture *capture = unknownb0;
  if (capture == nullptr) {
    if (isCapture) {
      unknownb0 = new (unknown00->unknown0c) DrPixlPostObjCapture(unknown00, unknown08, this);
    }
  } else if ((capture->unknown3e0 & DrPixlPostObjCapture::FLAG_UNKNOWN_3) == 0) {
    if (!isCapture) {
      capture->unknown3e0 |= DrPixlPostObjCapture::FLAG_UNKNOWN_2;
    }
  } else {
    delete capture;
    unknownb0 = nullptr;
  }
}

void DrPixlPostMan::setBloom(bool isBloom) { unknownf8 = !isBloom ? unknownf8 & ~(FLAG_BLOOM | FLAG_VOLUME) : unknownf8 | (FLAG_BLOOM | FLAG_VOLUME); }

void DrPixlPostMan::setSSAO(bool isSSAO) {
  if (isSSAO) {
    unknownf8 |= FLAG_SSAO;
  } else if (unknownf8 & FLAG_SSAO) {
    unknownf8 &= ~FLAG_SSAO;
  }
}

void DrPixlPostMan::setBlur(bool isBlur) {
  if (isBlur) {
    unknownf8 |= FLAG_BLUR | FLAG_DEPTH_DOWN;
    if (unknown58 == nullptr) {
      unknown58 = new (unknown00->unknown0c) DrPixlPostObjMotionBlur2(unknown00, unknown08, this);
    }
  } else if (unknownf8 & FLAG_BLUR) {
    if (unknown50 != nullptr) {
      delete unknown50;
      unknown50 = nullptr;
    }
    if (unknown58 != nullptr) {
      delete unknown58;
      unknown58 = nullptr;
    }
    unknownf8 &= ~FLAG_BLUR;
  }
}

void DrPixlPostMan::setDepthField(bool isDepthField) {
  if (isDepthField) {
    unknownf8 |= FLAG_DEPTH_FIELD | FLAG_DEPTH_DOWN;
    if (unknown30 == nullptr) {
      unknown30 = new (unknown00->unknown0c) DrPixlPostObjDepthofField(unknown00, unknown08, this);
    }
  } else if (unknownf8 & FLAG_DEPTH_FIELD) {
    unknownf8 &= ~FLAG_DEPTH_FIELD;
    if (unknown30 != nullptr) {
      delete unknown30;
      unknown30 = nullptr;
    }
  }
}

DrPixlRenderTarget *DrPixlPostMan::getOldDownDepth() { return unknownc0[DrMan::s_nDblStockIdx]; }

void DrPixlPostMan::setToneMaping(bool isToneMaping) { unknownf8 = !isToneMaping ? unknownf8 & ~FLAG_TONE_MAPING : unknownf8 | FLAG_TONE_MAPING; }

void DrPixlPostMan::setVolume(bool isVolume) { unknownf8 = !isVolume ? unknownf8 & ~FLAG_VOLUME : unknownf8 | FLAG_VOLUME; }

void DrPixlPostMan::set3DLut(bool is3DLut) { unknownf8 = !is3DLut ? unknownf8 & ~FLAG_3D_LUT : unknownf8 | FLAG_3D_LUT; }

void DrPixlPostMan::setSSAOAv(bool isSSAO) {
  if (isSSAO) {
    unknownf8 |= FLAG_SSAO;
  } else if (unknownf8 & FLAG_SSAO) {
    unknownf8 &= ~FLAG_SSAO;
  }
}

void DrPixlPostMan::setVolumePos(const mm::Vec3 &pos) {
  if (unknown28 != nullptr) {
    unknown28->unknown30 = pos;
  }
}

void DrPixlPostMan::setDepthFieldParm(f32 distance, f32 range, f32 strength) {}

void DrPixlPostMan::setBlurParm(f32 strength, f32 sub) {}

bool DrPixlPostMan::isToneMaping() { return unknownf8 & FLAG_TONE_MAPING; }

bool DrPixlPostMan::isBloom() { return unknownf8 & FLAG_BLOOM; }

bool DrPixlPostMan::isCalcBloom() { return unknownf8 & FLAG_CALC_BLOOM; }

bool DrPixlPostMan::is3DLut() { return unknownf8 & FLAG_3D_LUT; }

bool DrPixlPostMan::isVolume() { return unknownf8 & FLAG_VOLUME; }

bool DrPixlPostMan::isBluer() { return unknownf8 & FLAG_BLUR; }

bool DrPixlPostMan::isDepthField() { return unknownf8 & FLAG_DEPTH_FIELD; }

bool DrPixlPostMan::isSSAO() { return unknownf8 & FLAG_SSAO; }

bool DrPixlPostMan::isSSS() { return unknownf8 & FLAG_SSS; }

bool DrPixlPostMan::isReflection() { return unknownf8 & FLAG_REFLECTION; }

bool DrPixlPostMan::isChgShader() { return unknownf8 & FLAG_CHG_SHADER; }

bool DrPixlPostMan::isDepthDown() { return unknownf8 & FLAG_DEPTH_DOWN; }

const grlib::CGLibTextureBuffer *DrPixlPostMan::getToonGradTex() const {
  if (unknown98 != nullptr) {
    return &unknown98->getGradTex();
  }
  return nullptr;
}

const grlib::CGLibTextureBuffer *DrPixlPostMan::getToonDarkGradTex() const {
  if (unknown98 != nullptr) {
    return &unknown98->getDarkGradTex();
  }
  return nullptr;
}

} // namespace ml
