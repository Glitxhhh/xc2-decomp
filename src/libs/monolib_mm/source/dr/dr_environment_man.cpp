#include "dr/dr_environment_man.h"

#include "dr/dr_env_coli_man.h"
#include "dr/dr_environment_obj.h"
#include "dr/dr_ini_sys.h"
#include "dr/dr_man.h"
#include "ml/file_res_th.h"
#include "mm_math/mm_mat44.h"
#include "mtl/alloc_handle.h"

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
void unknown001(DrEnvironmentObj *&head, DrEnvironmentObj *&tail) {
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
  unknown001(unknown28[0], unknown28[1]);
  unknown001(unknown28[2], unknown28[3]);
  unknown001(unknown58, unknown60);
  unknown001(unknown48, unknown50);
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

} // namespace ml
