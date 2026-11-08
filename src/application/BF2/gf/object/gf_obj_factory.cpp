#include "gf/object/gf_obj_factory.h"

#include "gf/asset/gf_asset_def.h"
#include "gf/asset/gf_asset_manager.h"
#include "gf/data/gf_data_enemy.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "mm_mtl/rtti.h"

namespace gf {

void GfObjFactory::destroyObj(GF_OBJ_HANDLE *handle) { GfObjUtil::destroy(handle); }

bool GfObjFactory::destroyObjHandle(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  GfAssetManager::destroy(info->unknown10);
  info->unknown10 = INVALID_ASSET_HANDLE;
  if (GfObjManager::get() != nullptr) {
    GfObjManager::get()->callGfObjListener(IGfObjListener::OBJEVT_REMOVE, handle);
  }
  if (info->unknown18 != nullptr) {
    info->unknown18->setTerminate();
    info->unknown18 = nullptr;
  }
  return true;
}

GF_OBJ_HANDLE *GfObjFactory::createDebugMap(const GfInitParamMap &) { return INVALID_HANDLE; }

GF_OBJ_HANDLE *GfObjFactory::createSmnEnemy(int id, const mm::Vec3 &position, const mm::Vec3 &rotation, bool flag) {
  GF_OBJ_HANDLE *handle = createGmkEnemy(id, 0, 0, position, rotation, flag);
  if (handle != INVALID_HANDLE) {
    {
      DataParamAcc acc(handle);
      if (acc.getSDataEnemy()->unknown04_0) {
        GfObjUtil::destroy(handle);
        return INVALID_HANDLE;
      }
    }
    mm::mtl::dynamicCast<GfObjSetupEnemy>(GfObjManager::getObjInfo(handle)->unknown30)->unknownb2 = true;
    return handle;
  }
  return INVALID_HANDLE;
}

void setSkelType(u32 type, GfObjSetup *setup) {
  s32 skelType;
  switch (type) {
  case 1:
    skelType = 0;
    break;
  case 2:
    skelType = 4;
    break;
  case 3:
    skelType = 1;
    break;
  case 4:
    skelType = 3;
    break;
  case 5:
    skelType = 5;
    break;
  case 6:
    skelType = 6;
    break;
  case 7:
    skelType = 7;
    break;
  case 8:
    skelType = 8;
    break;
  case 9:
    skelType = 9;
    break;
  case 10:
    skelType = 10;
    break;
  default:
    skelType = -1;
    break;
  }
  setup->unknown68 = skelType;
}

} // namespace gf
