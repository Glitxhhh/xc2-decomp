#include "gf/param/gf_param.h"

#include "arc/arc_data.h"
#include "framework/pad/pad_res_event.h"
#include "framework/pad/pad_res_event_manager.h"
#include "framework/resource/common_resource.h"
#include "gf/gf_allocator.h"
#include "gf/gf_static_res.h"
#include "types.h"

namespace gf {

namespace {

// Inferred role: pad event file of /param/pad.pdp and its source path, per pad resource index; original name unknown.
struct unknown001 {
  const char *unknown00; // Inferred role: file name in the archive; original member name unknown.
  const char *unknown08; // Inferred role: source path; original member name unknown.
};

// Inferred role: pad resources bound by bindPadResources; original name unknown.
const unknown001 unknown002[] = {
    {"field.pad", "T:/BF2/param/pad/data/field.pdml"},
    {"battle.pad", "T:/BF2/param/pad/data/battle.pdml"},
    {"camera.pad", "T:/BF2/param/pad/data/camera.pdml"},
    {"target.pad", "T:/BF2/param/pad/data/target.pdml"},
    {"system.pad", "T:/BF2/param/pad/data/system.pdml"},
};

} // namespace

void bindPadResources() {
  fw::PadResEventManager *manager = fw::PadResEventManager::get();
  if (manager != nullptr) {
    manager->setup(5, getAllocator(ALLOCATOR_DEFAULT));
    fw::CommonResource *resource = GfStaticRes::search("/param/pad.pdp");
    if (resource != nullptr) {
      arc::CArcData archive(resource->getAssetData());
      for (u32 index = 0; index < 5; index++) {
        fw::PadResEventManager::setResource(index, fw::PadEventImporter::create(archive.getFileAdr(unknown002[index].unknown00), unknown002[index].unknown08));
      }
    }
  }
}

void unbindPadResource() {
  fw::PadResEventManager *manager = fw::PadResEventManager::get();
  if (manager != nullptr) {
    for (u32 index = 0; index < 5; index++) {
      fw::PadResEventManager::setResource(index, nullptr);
    }
    manager->cleanup();
  }
}

} // namespace gf
