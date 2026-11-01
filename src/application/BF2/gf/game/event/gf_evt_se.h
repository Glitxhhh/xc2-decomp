#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"

namespace fw {
class SoundPack;
class SoundResource;
struct UpdateInfo;
} // namespace fw

namespace gf {

class GfEvtSe {
public:
  // Inferred role: sound effect pack loaded for an event; original name unknown.
  struct unknown001 {
    fw::SoundResource *unknown00;  // Inferred role: resource; original member name unknown.
    fw::SoundPack *unknown08;      // Inferred role: pack found once the resource is loaded; original member name unknown.
    mm::mtl::FixStr<32> unknown10; // Inferred role: pack name; original member name unknown.
  };

  GfEvtSe();
  ~GfEvtSe();
  void cleanup();
  void destroySe();
  void createSe(const char *name);
  bool isLoadedSe() const;
  void update(const fw::UpdateInfo &info);

  mm::mtl::FixedVector<unknown001, 8> unknown00; // Inferred role: packs; original member name unknown.
  bool unknown1c8;                               // Inferred role: cleaned up; original member name unknown.
};

static_assert(offsetof(GfEvtSe::unknown001, unknown08) == 0x8, "");
static_assert(offsetof(GfEvtSe::unknown001, unknown10) == 0x10, "");
static_assert(sizeof(GfEvtSe::unknown001) == 0x38, "");
static_assert(offsetof(GfEvtSe, unknown1c8) == 0x1c8, "");
static_assert(sizeof(GfEvtSe) == 0x1d0, "");

} // namespace gf
