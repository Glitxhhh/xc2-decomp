#include "dr/dr_environment_man.h"

#include "dr/dr_ap_gx_type.h"
#include "dr/dr_calc_clip_work_view_plane.h"
#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_env_coli_man.h"
#include "dr/dr_environment_anim.h"
#include "dr/dr_environment_lgt_list.h"
#include "dr/dr_environment_obj.h"
#include "dr/dr_environment_obj_lgt.h"
#include "dr/dr_environment_tex.h"
#include "dr/dr_environment_time.h"
#include "dr/dr_fog_man.h"
#include "dr/dr_fog_obj_gbl.h"
#include "dr/dr_ini_sys.h"
#include "dr/dr_light_obj.h"
#include "dr/dr_light_obj_local_ibl.h"
#include "dr/dr_man.h"
#include "dr/dr_shd_lgt_man.h"
#include "dr/dr_shd_man.h"
#include "ml/file_res_th.h"
#include "mm_math/mm_col3.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace ml {

void DrEnvironmentObj::release() { unknown8c |= FLAG_RELEASE << DrMan::s_nDblStockIdx; }

DrEnvironmentObj::DrEnvironmentObj(DrMan *drMan, DrLightMan *lightMan, DrFogMan *fogMan)
    : unknown08(nullptr), unknown10(nullptr), unknown18(drMan), unknown20(lightMan), unknown28(fogMan), unknown70(0.0f, 0.0f, 0.0f), m_frame(0.0f), m_frameSpd(1.0f), m_maxFrame(0.0f), unknown8c(0),
      unknown90(0) {
  unknown30 = mm::Mat44::identity;
}

void DrEnvironmentMan::releaseObj(DrEnvironmentObj *obj) { obj->release(); }

namespace {

// Inferred role: deletes every object of a list; original name unknown.
void unknown002(DrEnvironmentObj *&head, DrEnvironmentObj *&tail) {
  DrEnvironmentObj *obj = head;
  while (obj != nullptr) {
    DrEnvironmentObj *next = obj->unknown10;
    delete obj;
    obj = next;
  }
  head = nullptr;
  tail = nullptr;
}

} // namespace

void DrEnvironmentMan::releaseAll() {
  unknown002(unknown28[0], unknown28[1]);
  unknown002(unknown28[2], unknown28[3]);
  unknown002(unknown58, unknown60);
  unknown002(unknown48, unknown50);
}

DrEnvironmentMan::DrEnvironmentMan(DrMan *drMan, DrLightMan *lightMan, DrFogMan *fogMan, int screen)
    : unknown00(drMan), unknown08(lightMan), unknown10(fogMan), unknown20(screen), unknown28(), unknown48(nullptr), unknown50(nullptr), unknown58(nullptr), unknown60(nullptr), unknown68(nullptr) {
  unknown18 = new (drMan->unknown0c) DrEnvColiMan(drMan);
}

DrEnvironmentMan::~DrEnvironmentMan() {
  if (unknown68 != nullptr) {
    FileResTh *res = unknown00->unknown70->unknown890;
    if (res != nullptr) {
      res->Release();
    }
  }
  if (unknown18 != nullptr) {
    delete unknown18;
    unknown18 = nullptr;
  }
  releaseAll();
}

void DrEnvironmentMan::updateCameraLight() {
  if (unknown20 != 0) {
    return;
  }
  if (unknown00->unknown1da0) {
    if (unknown68 == nullptr) {
      FileResTh *res = unknown00->unknown70->unknown890;
      res->AddRef();
      unknown68 = createObj(res->unknownc8);
    }
    unknown68->unknown8c &= ~DrEnvironmentObj::FLAG_DISP_OFF;
  } else if (unknown68 != nullptr) {
    unknown68->unknown8c |= DrEnvironmentObj::FLAG_DISP_OFF;
  }
}

void DrEnvironmentMan::renderLgt() {
  for (DrEnvironmentObj *obj = unknown48; obj != nullptr; obj = obj->unknown10) {
    obj->renderLgt();
  }
}

void DrEnvironmentMan::setZoneObj(DrEnvironmentObj *obj, bool isOn) {
  if (isOn) {
    for (DrEnvironmentObj *current = unknown48; current != nullptr; current = current->unknown10) {
      if (current->unknown8c & DrEnvironmentObj::FLAG_UNKNOWN_1) {
        current->unknown8c &= ~DrEnvironmentObj::FLAG_DISP_OFF;
      }
    }
  } else {
    for (DrEnvironmentObj *current = unknown48; current != nullptr; current = current->unknown10) {
      if (current->unknown8c & DrEnvironmentObj::FLAG_UNKNOWN_1) {
        current->unknown8c |= DrEnvironmentObj::FLAG_DISP_OFF;
      }
    }
  }
}

f32 DrEnvironmentObj::getFrame() const { return m_frame; }

f32 DrEnvironmentObj::getMaxFrame() const { return m_maxFrame; }

void DrEnvironmentObj::setFrameSpd(f32 speed) { m_frameSpd = speed; }

f32 DrEnvironmentObj::getFrameSpd() { return m_frameSpd; }

DrEnvironmentObjLgt::~DrEnvironmentObjLgt() { releaseLgt(); }

void DrEnvironmentObjLgt::releaseLgt() {
  if (unknown1fc != 0) {
    if (unknown1e8 != 0 && unknown1b0 != nullptr) {
      for (int i = 0; i < unknown1e8; i++) {
        unknown1b0[i].~DrLightObjAmb();
      }
    }
    if (unknown1ec != 0 && unknown1b8 != nullptr) {
      for (int i = 0; i < unknown1ec; i++) {
        unknown1b8[i].~DrLightObjDir();
      }
    }
    if (unknown1f0 != 0 && unknown1c0 != nullptr) {
      for (int i = 0; i < unknown1f0; i++) {
        unknown1c0[i].~DrLightObjPnt();
      }
    }
    if (unknown1f4 != 0 && unknown1c8 != nullptr) {
      for (int i = 0; i < unknown1f4; i++) {
        unknown1c8[i].~DrLightObjSpt();
      }
    }
    if (unknown1f8 != 0 && unknown1d0 != nullptr) {
      for (int i = 0; i < unknown1f8; i++) {
        unknown1d0[i].~DrLightObjLocalIBL();
      }
    }
    unknown1fc = 0;
  }
  if (unknown200 != 0) {
    for (int i = 0; i < unknown200; i++) {
      unknown1d8[i].~DrFogObjGbl();
    }
    unknown200 = 0;
  }
  unknown98.releaseTexture();
  if (unknown180 != nullptr) {
    mtl::MemManager::deallocate(unknown180, 0, false);
    unknown180 = nullptr;
  }
}

void DrEnvironmentObjLgt::resourceInit() { setupLgt(unknown150); }

void DrEnvironmentObjLgt::setupFog(DrFogObjGbl *fog, const LgtGlbFogObj *data) {
  fog->unknown20 = mm::Col3(data->unknown00[0], data->unknown00[1], data->unknown00[2]);
  fog->unknown2c = mm::Col3(data->unknown0c[0], data->unknown0c[1], data->unknown0c[2]);
  fog->unknown38 = mm::Col3(data->unknown18[0], data->unknown18[1], data->unknown18[2]);
  fog->unknown44 = data->unknown24;
  fog->unknown48 = data->unknown28;
  fog->unknown4c = data->unknown2c;
  fog->unknown50 = data->unknown50;
  fog->unknown4c = data->unknown2c;
  fog->unknown54 = data->unknown30;
  fog->unknown58 = data->unknown34;
  fog->unknown5c = data->unknown38;
  fog->unknown60 = data->unknown3c;
  fog->unknown64 = data->unknown40;
}

void DrEnvironmentObjLgt::setupDirectinal(DrEnvironmentLgtList *list, DrLightObjDir *light, const LgtObjData *data, const LgtPosData *pos) {
  const unknown002 *dir = reinterpret_cast<const unknown002 *>(reinterpret_cast<const u8 *>(unknown158) + data->unknown00);
  if (data->unknown08 & 0x80000) {
    light->unknown80.a = dir->unknown01 * 0.01f;
  }
  if (dir->unknown02 == 1) {
    light->setSoftShadow(true);
  }
  mm::Col3 color(data->unknown18 * data->unknown0c[0], data->unknown18 * data->unknown0c[1], data->unknown18 * data->unknown0c[2]);
  light->unknown80.r = color.r;
  light->unknown80.g = color.g;
  light->unknown80.b = color.b;
  light->setMat(pos->unknown00);
  light->unknown90 = dir->unknown04;
  list->unknown10 = light;
}

void DrEnvironmentObjLgt::setupBox(DrEnvironmentLgtList *list, DrLightObjSpt *light, const LgtObjData *data, const LgtPosData *pos) {}

void DrEnvironmentObjLgt::setupCapsule(DrEnvironmentLgtList *list, DrLightObjSpt *light, const LgtObjData *data, const LgtPosData *pos) {}

void DrEnvironmentObjLgt::setFrame(f32 frame) {
  m_frame = frame;
  unknowne0.setFrame(frame);
}

void DrEnvironmentObjLgt::updateFog() {
  if (unknown200 > 0) {
    const u8 *data = reinterpret_cast<const u8 *>(unknown158);
    DrCalcViewWork *viewWork = unknown18->unknown580->unknown10;
    const unknown001 *table = reinterpret_cast<const unknown001 *>(data + unknown158->unknown14);
    const LgtGlbFogObj *fogs = reinterpret_cast<const LgtGlbFogObj *>(data + table->unknown00);
    for (int i = 0; i < unknown200; i++) {
      (this->*s_pCallFogCall[fogs[i].unknown4a])(&unknown1d8[i], viewWork, &fogs[i]);
    }
  }
  unknown28->unknownd0 = true;
}

void DrEnvironmentObjLgt::calcLgtPos(DrCalcViewWork *viewWork) {
  for (int i = 0; i < unknown1fc; i++) {
    calcLgtObj(i, viewWork);
  }
}

void DrEnvironmentObjLgt::renderLgt() {
  if (unknown8c & FLAG_DISP_OFF) {
    return;
  }
  if (unknown1fc != 0 && unknown1e0 != 0) {
    DrShdLgtMan *shdLgtMan = unknown18->unknown80->unknown18;
    DrEnvironmentLgtList **lists = unknown1a0;
    for (int i = 0; i < unknown1e0; i++, lists++) {
      DrEnvironmentLgtList *list = *lists;
      DrLightObj *light = list->unknown10;
      (this->*s_pCallLgtRender[list->unknown00->unknown04])(light, shdLgtMan);
    }
  }
}

void DrEnvironmentObjLgt::debugRenderLgt() {
  if (unknown1fc != 0 && unknown1e0 != 0) {
    renderLgt();
  }
}

void DrEnvironmentObjLgt::debugRenderLgt2D() {
  if (!(unknown8c & FLAG_DISP_OFF) && unknown1fc != 0) {
    DrShdLgtMan *shdLgtMan = unknown18->unknown80->unknown18;
    if (unknown8c & FLAG_DEBUG_DISP_2D) {
      for (int i = 0; i < unknown1fc; i++) {
        DrEnvironmentLgtList *list = &unknown198[i];
        DrLightObj *light = list->unknown10;
        (this->*s_pCallLgtRender2D[list->unknown00->unknown04])(light, shdLgtMan);
      }
    }
  }
}

bool DrEnvironmentObjLgt::callback_Chk_Ambinet_Directional(DrEnvironmentLgtList *list, DrCalcViewWork *viewWork, const LgtObjData *data) {
  if (data->unknown08 & 1) {
    const LgtPosData *pos = list->unknown08;
    f32 x = unknown210.x - pos->unknown50[0];
    f32 y = unknown210.y - pos->unknown50[1];
    f32 z = unknown210.z - pos->unknown50[2];
    if (x * x + y * y + z * z > pos->unknown5c * pos->unknown5c) {
      return false;
    }
  }
  if (data->unknown22 != 0 && (unknown8c & FLAG_GROUP) && unknown90 != data->unknown22) {
    return false;
  }
  list->unknown18 = 1.0f;
  return true;
}

bool DrEnvironmentObjLgt::callback_Chk_non(DrEnvironmentLgtList *list, DrCalcViewWork *viewWork, const LgtObjData *data) { return false; }

bool DrEnvironmentObjLgt::callback_Chk_LocalIBL(DrEnvironmentLgtList *list, DrCalcViewWork *viewWork, const LgtObjData *data) {
  const LgtPosData *pos = list->unknown08;
  DrLightObjLocalIBL *light = static_cast<DrLightObjLocalIBL *>(list->unknown10);
  list->unknown18 = 1.0f;
  u32 id = pos->unknown62;
  if (id != 0) {
    u32 *table = unknown18->unknown1d20;
    if (table[id >> 5] & (1 << (id & 31))) {
      return false;
    }
  }
  const mm::Vec3 &position = light->unknown110;
  return viewWork->unknown4e0.clipTest(position, light->unknown120);
}

bool DrEnvironmentObjLgt::callback_Calc_Non(DrEnvironmentLgtList *list, DrCalcViewWork *viewWork) { return true; }

bool DrEnvironmentObjLgt::callback_Calc_LocalIBL(DrEnvironmentLgtList *list, DrCalcViewWork *viewWork) { return true; }

void DrEnvironmentObjLgt::callback_Ren_Non(DrLightObj *light, DrShdLgtMan *shdLgtMan) {}

void DrEnvironmentObjLgt::callback_Ren_Point(DrLightObj *light, DrShdLgtMan *shdLgtMan) {
  DrAPGxType::setupCullingFront();
  DrAPGxType::setupDepthContl(true, true, 3);
  DrAPGxType::setupBlend(0);
  shdLgtMan->renderDebugPnt(static_cast<DrLightObjPnt *>(light));
}

void DrEnvironmentObjLgt::callback_Ren_Spot(DrLightObj *light, DrShdLgtMan *shdLgtMan) {
  DrAPGxType::setupCullingFront();
  DrAPGxType::setupDepthContl(true, true, 3);
  DrAPGxType::setupBlend(0);
  shdLgtMan->renderDebugSpt(static_cast<DrLightObjSpt *>(light));
}

void DrEnvironmentObjLgt::callback_Ren2D_Non(DrLightObj *light, DrShdLgtMan *shdLgtMan) {}

void DrEnvironmentObjLgt::callback_Relase_Non(DrLightObj *light) {}

void DrEnvironmentObjLgt::callback_Relase_Point(DrLightObj *light) {
  if (light->isShadowLight()) {
    static_cast<DrLightObjPnt *>(light)->deletePntShadow();
  }
}

void DrEnvironmentObjLgt::callback_Relase_Spot(DrLightObj *light) {
  if (light->isShadowLight()) {
    static_cast<DrLightObjSpt *>(light)->deleteSptShadow();
  }
}

void (DrEnvironmentObjLgt::*DrEnvironmentObjLgt::s_pCallLgtRender[])(DrLightObj *light, DrShdLgtMan *shdLgtMan) = {
    &DrEnvironmentObjLgt::callback_Ren_Non,
    &DrEnvironmentObjLgt::callback_Ren_Non,
    &DrEnvironmentObjLgt::callback_Ren_Point,
    &DrEnvironmentObjLgt::callback_Ren_Spot,
    &DrEnvironmentObjLgt::callback_Ren_Non,
    &DrEnvironmentObjLgt::callback_Ren_Non,
    &DrEnvironmentObjLgt::callback_Ren_Non,
};

void (DrEnvironmentObjLgt::*DrEnvironmentObjLgt::s_pCallLgtRender2D[])(DrLightObj *light, DrShdLgtMan *shdLgtMan) = {
    &DrEnvironmentObjLgt::callback_Ren2D_Non,
    &DrEnvironmentObjLgt::callback_Ren2D_Non,
    &DrEnvironmentObjLgt::callback_Ren2D_Non,
    &DrEnvironmentObjLgt::callback_Ren2D_Non,
    &DrEnvironmentObjLgt::callback_Ren2D_Non,
    &DrEnvironmentObjLgt::callback_Ren2D_Non,
    &DrEnvironmentObjLgt::callback_Ren2D_LocalIBL,
};

void (DrEnvironmentObjLgt::*DrEnvironmentObjLgt::s_pCallFogCall[])(DrFogObjGbl *fog, DrCalcViewWork *viewWork, const LgtGlbFogObj *data) = {
    &DrEnvironmentObjLgt::callback_Fog_Gbl,
};

} // namespace ml

#include "dr_environment_anim.cpp"
#include "dr_environment_tex.cpp"
#include "dr_environment_time.cpp"
#include "dr_light_obj.cpp"
