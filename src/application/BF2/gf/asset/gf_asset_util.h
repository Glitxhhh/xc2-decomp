#pragma once
#include "gf/asset/gf_asset_def.h"
#include "types.h"

namespace gf {

struct GF_ASSET_HANDLE;
struct GF_OBJ_HANDLE;
struct GF_SLOT_HANDLE;

class GfAssetUtil {
public:
  static bool isEnableDeleteObject(GF_SLOT_HANDLE *handle);
  static bool isObjectDestroy(GF_ASSET_HANDLE *handle);
  static void addDestroyObject(GF_ASSET_HANDLE *handle, bool flag);
  static GF_OBJ_HANDLE *getObjHandle(GF_ASSET_HANDLE *handle);
  static u32 getAssetPrio(GF_ASSET_HANDLE *handle);
  static bool isRetargetLoad(GF_ASSET_HANDLE *handle);
  static void setRetargetLoad(GF_ASSET_HANDLE *handle, bool isRetarget);
  static const char *getAssetTypeName(GfAssetType type);
};

} // namespace gf
