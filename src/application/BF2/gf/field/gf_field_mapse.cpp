// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/gf/field/gf_field_mapse.cpp.
#include "gf/field/gf_field_mapse.h"

#include <math.h>
#include <string.h>

#include "fw/fw_model_object.h"
#include "fw/fw_update_info.h"
#include "gf/data/gf_bdat_rsc.h"
#include "gf/game/gf_game_scene.h"
#include "gf/gf_allocator.h"
#include "gf/map/gf_map_manager.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_vec3.h"
#include "scn/scn_obj_acc.h"

namespace ml {
class ScnObjModel;
} // namespace ml

namespace gf {

GfFieldMapSe::GfFieldMapSe() : unknown08(0) {}

GfFieldMapSe::~GfFieldMapSe() {}

void GfFieldMapSe::gevMapjump(GEV, const MapjumpCallbackInfo &) {}

void GfFieldMapSe::destroy() { destroyMapSe(); }

void GfFieldMapSe::destroyMapSe() {
  for (SEDATA *&data : unknown10) {
    for (SEOBJ *seObj : data->unknown10) {
      destroySeObj(seObj);
    }
    data->unknown10.clear();
    if (data != nullptr) {
      delete data;
      data = nullptr;
    }
  }
  unknown10.clear();
  unknown08 = 0;
}

void GfFieldMapSe::dispEffPosForDebug() {}

void GfFieldMapSe::postUpdate(const fw::UpdateInfo &) {}

void GfFieldMapSe::gevPause(u32, u32) {}

void GfFieldMapSe::gevGameMapModel(GF_OBJ_HANDLE *, bool isEnter) {
  if (isEnter) {
    createMapSe();
  } else {
    destroyMapSe();
  }
}

void GfFieldMapSe::createMapSe() {
  destroyMapSe();
  fw::ModelObject *model = GfMapManager::getModelObject();
  if (model == nullptr) {
    return;
  }
  ml::ScnObjModel *scnModel = model->getInterface();
  if (scnModel == nullptr) {
    return;
  }
  ml::ScnObjAccSeamEtcPos acc(scnModel);
  unknown08 = acc.getObjMax();
  if (unknown08 <= 0) {
    return;
  }
  GfBdatRsc *rsc = GfBdatRsc::get();
  for (int object = 0; object < unknown08; object++) {
    ml::ScnObjAccPartsEtcPos parts = acc.getObj(object);
    u32 row = rsc->getFLD_actorSEStart();
    u32 end = rsc->getFLD_actorSEEnd();
    for (; row < end; row++) {
      if (strcmp(parts.getObjName(), rsc->getFLD_actorSELOD(row)) == 0) {
        SEDATA *data = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, 227, 8) SEDATA(object, parts.getMatrixMax(), row);
        unknown10.push_back(data);
        break;
      }
    }
  }
}

void GfFieldMapSe::destroySeObj(SEOBJ *seObj) {
  if (GfSound::get() != nullptr) {
    GfSound::get()->stopSe(seObj->unknown00, 1.0f);
    unknown118.unknown004(seObj);
  }
}

void GfFieldMapSe::updateSeObjDataForFindActivate(fw::UpdateInfo, SEDATA &data, ml::ScnObjAccSeamEtcPos &acc) {
  int matrix = data.unknown0c;
  if (data.unknown04 > 0) {
    GfBdatRsc *rsc = GfBdatRsc::get();
    int found = 0;
    for (int count = 0; count < data.unknown04 && found < 2; count++) {
      if (!isActivateMatrix(matrix, data)) {
        f32 distance = rsc->getFLD_actorSEmin_volume_Dist(data.unknown08);
        SECOND cond = getSeObjCond(matrix, data.unknown00, acc);
        if (cond.unknown04 < distance * distance) {
          data.unknown98.push(cond);
        }
        found++;
      }
      if (matrix + 1 < data.unknown04) {
        matrix++;
      } else {
        matrix = 0;
      }
    }
  }
  data.unknown0c = matrix;
}

GfFieldMapSe::SECOND GfFieldMapSe::getSeObjCond(int matrix, int object, ml::ScnObjAccSeamEtcPos &acc) const {
  ml::ScnObjAccPartsEtcPos parts = acc.getObj(object);
  GfGameScene *scene = GfGameScene::get();
  SECOND cond;
  cond.unknown00 = matrix;
  cond.unknown04 = 1000000.0f;
  if (parts.isDisp(matrix) && scene != nullptr) {
    mm::Vec3 diff = scene->unknown280 - parts.getMatrix(matrix)->unknown004();
    cond.unknown04 = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;
  }
  return cond;
}

f32 GfFieldMapSe::getVolume(const SEOBJ *seObj) {
  GfBdatRsc *rsc = GfBdatRsc::get();
  f32 maxDistance = rsc->getFLD_actorSEmax_volume_Dist(seObj->unknown1c);
  f32 minDistance = rsc->getFLD_actorSEmin_volume_Dist(seObj->unknown1c);
  f32 volumeMax = rsc->getFLD_actorSEvolumeMAX(seObj->unknown1c) * 0.01f;
  f32 volumeMin = rsc->getFLD_actorSEvolumeMIN(seObj->unknown1c) * 0.01f;
  f32 distance = sqrtf(seObj->unknown14.unknown04);
  f32 volume;
  if (distance <= maxDistance) {
    volume = volumeMax;
  } else if (distance >= minDistance) {
    volume = volumeMin;
  } else {
    volume = volumeMin + (volumeMax - volumeMin) * (1.0f - (distance - maxDistance) / (minDistance - maxDistance));
    mm::clampRef(volume, 0.0f, 1.0f);
  }
  return volume;
}

bool GfFieldMapSe::isActivateMatrix(int matrix, const SEDATA &data) const {
  for (const SEOBJ *seObj : data.unknown10) {
    if (seObj->unknown0c == matrix) {
      return true;
    }
  }
  return false;
}

bool GfFieldMapSe::DistCompare::operator()(const SEOBJ *a, const SEOBJ *b) const { return a->unknown14.unknown04 < b->unknown14.unknown04; }

} // namespace gf

template class ml::fixed_size_alloc_inside<gf::GfFieldMapSe::SEOBJ, 128>;
template mm::mtl::PtrSingleton<gf::GfFieldMapSe>::~PtrSingleton();
