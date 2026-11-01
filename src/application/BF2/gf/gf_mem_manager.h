#pragma once
#include <stddef.h>

#include "gf/gf_allocator.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace gf {

struct GfSetupParam;

class GfMemManager : public mm::mtl::PtrSingleton<GfMemManager> {
public:
  GfMemManager(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfMemManager();
  static void buildCoreMemory(const GfSetupParam &param);
  static void initializeCore(const GfSetupParam &param);
  static void destroyCoreMemory();
  static void finalizeCore();
  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  static bool isInitialized();
  static void initializeGame(mtl::ALLOC_HANDLE handle);
  static void finalizeGame();
  mtl::ALLOC_HANDLE getMemHandle(ALLOCATOR allocator);

  static GfAllocatorManager s_allocator;
  static mtl::ALLOC_HANDLE s_hMemProg;
  static mtl::ALLOC_HANDLE s_hMemInitial;
  static mtl::ALLOC_HANDLE s_hMemScript;
  static mtl::ALLOC_HANDLE s_hMemAsset;
  static mtl::ALLOC_HANDLE s_hMemBdat;
  static mtl::ALLOC_HANDLE s_hMemFontRsc;
  static mtl::ALLOC_HANDLE s_hMemMenu;
  static mtl::ALLOC_HANDLE s_hMemAnimation;
  static mtl::ALLOC_HANDLE s_hMemGimmick;
  static mtl::ALLOC_HANDLE s_hMemGmkBdat;
  static mtl::ALLOC_HANDLE s_hMemProgLarge;

  bool unknown08; // Inferred role: initialized; original member name unknown.
};

static_assert(offsetof(GfMemManager, unknown08) == 0x08, "");
static_assert(sizeof(GfMemManager) == 0x10, "");

} // namespace gf
