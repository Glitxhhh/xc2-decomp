#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_list.h"
#include "mm_mtl/fixstr.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace fw {
class CommonResource;
} // namespace fw

namespace gf {

class GfStaticRes {
public:
  // Layout evidence: loadStaticRes (0x7100392650) pushes the requested resource and a FixStr<64> copy of its path;
  // the nodes of s_aResource are 0x58 bytes with their links at 0x50.
  struct ResourceInfo {
    fw::CommonResource *unknown00; // Inferred role: resource; original member name unknown.
    mm::mtl::FixStr<64> unknown08; // Inferred role: path; original member name unknown.
  };

  static void initialize();
  static void loadRequest();
  static bool isLoaFinish();
  static void finalize();
  static void loadStaticRes(const char *path);
  static fw::CommonResource *search(const char *path);

  static mtl::ALLOC_HANDLE s_hMem;
  static mm::mtl::FixedList<ResourceInfo, 64> s_aResource;
};

static_assert(offsetof(GfStaticRes::ResourceInfo, unknown08) == 0x08, "");
static_assert(sizeof(GfStaticRes::ResourceInfo) == 0x50, "");
static_assert(sizeof(GfStaticRes::s_aResource) == 0x16a8, "");

} // namespace gf
