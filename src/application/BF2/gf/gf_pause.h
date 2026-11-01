#pragma once
#include <stddef.h>

#include "ml/fixed_size_alloc.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

enum {
  PAUSE_BIT_SYSTEM = 1 << 0,
  PAUSE_BIT_GAME = 1 << 1,
  PAUSE_BIT_EVENT_SOUND = 1 << 2,
  PAUSE_BIT_GAME_SOUND = 1 << 3,
  PAUSE_BIT_FIELD_TIME = 1 << 4,
  PAUSE_BIT_EVENT = 1 << 5,
  PAUSE_BIT_MAIN_MENU = 1 << 6,
  PAUSE_BIT_UNKNOWN_7 = 1 << 7, // Inferred role: pauses the effects (GfGameEvent::gevPause); original name unknown.
  PAUSE_BIT_EVENT_SKIP = 1 << 9,
};

struct GF_PAUSE_HANDLE;
struct GfSetupParam;

class GfPause : public mm::mtl::PtrSingleton<GfPause> {
public:
  GfPause(const GfSetupParam &param);
  virtual ~GfPause();
  static void build(const GfSetupParam &param);
  static void destroy();
  void initialize(const GfSetupParam &param);
  void finalize();
  static GF_PAUSE_HANDLE *createPauseHandle(u32 pauseBits);
  void destroyPauseHandle(GF_PAUSE_HANDLE *handle);
  static GF_PAUSE_HANDLE *reqPause(u32 pauseBits);
  u32 getPauseBit() const;
  static void destroyHandle(GF_PAUSE_HANDLE *handle);
  static void update();
  static bool isPause(u32 pauseBits);
  static bool isInitialized();
  u64 createPauseHandleByIndex(u32 index);

  ml::fixed_size_alloc_inside<u32, 64> unknown08;       // Inferred role: pause bits of each handle; original member name unknown.
  mm::mtl::FixedList<GF_PAUSE_HANDLE *, 64> unknown138; // Inferred role: active pause handles; original member name unknown.
  mm::mtl::FixedList<GF_PAUSE_HANDLE *, 64> unknown598; // Inferred role: requested pause handles; original member name unknown.
  mm::mtl::FixedList<GF_PAUSE_HANDLE *, 64> unknown9f8; // Inferred role: pause handles to destroy; original member name unknown.
  u32 unknowne58;                                       // Inferred role: current pause bits; original member name unknown.
  u32 unknowne5c;                                       // Inferred role: pause bits of the previous update; original member name unknown.
  u32 unknowne60;                                       // Inferred role: pause handle serial; original member name unknown.
  bool unknowne64;                                      // Inferred role: initialized; original member name unknown.
};

static_assert(offsetof(GfPause, unknown138) == 0x138, "");
static_assert(offsetof(GfPause, unknown598) == 0x598, "");
static_assert(offsetof(GfPause, unknown9f8) == 0x9f8, "");
static_assert(offsetof(GfPause, unknowne58) == 0xe58, "");
static_assert(offsetof(GfPause, unknowne5c) == 0xe5c, "");
static_assert(offsetof(GfPause, unknowne60) == 0xe60, "");
static_assert(offsetof(GfPause, unknowne64) == 0xe64, "");
static_assert(sizeof(GfPause) == 0xe68, "");

} // namespace gf
