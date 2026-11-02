#pragma once
#include <stddef.h>

#include "framework/manager_object.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {

struct UpdateInfo;
class ModelObject;

class ModelManager : public ManagerObject, public mm::mtl::PtrSingleton<ModelManager> {
public:
  static const u32 LAYER_MAX = 32;

  struct Group {
    mm::mtl::IntrusiveList<ModelObject> unknown00; // Inferred role: models; original member name unknown.
  };

  virtual void update(const UpdateInfo &info, u32 layer);

  mm::mtl::FixedArray<Group, LAYER_MAX> unknown18; // Inferred role: groups; original member name unknown.
};

static_assert(sizeof(ModelManager::Group) == 0x18, "");
static_assert(offsetof(ModelManager, unknown18) == 0x18, "");
static_assert(sizeof(ModelManager) == 0x318, "");

} // namespace fw
