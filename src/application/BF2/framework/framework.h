#pragma once
#include <stddef.h>

#include "framework/memory/allocator.h"
#include "fw/fw_update_info.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace ml {
class Scn;
class WinProc;
} // namespace ml

namespace fw {

class Applet;
class IPauseTrigger;

struct FrameworkConfig {
  u32 unknown00; // Inferred role: flags, 0x20 creates the CameraManager; original member name unknown.
  f32 unknown04; // Inferred role: frame rate; original member name unknown.
  u8 _08[0x20 - 0x08];
  u32 unknown20; // Inferred role: asset capacity; original member name unknown.
  u8 _24[0x28 - 0x24];
  u32 unknown28; // Inferred role: effect count; original member name unknown.
  u32 unknown2c; // Inferred role: resource capacity; original member name unknown.
  u32 unknown30; // Inferred role: updatable object capacity; original member name unknown.
  u32 unknown34; // Inferred role: script count; original member name unknown.
  u8 _38[0x3c - 0x38];
};

static_assert(offsetof(FrameworkConfig, unknown20) == 0x20, "");
static_assert(offsetof(FrameworkConfig, unknown28) == 0x28, "");
static_assert(offsetof(FrameworkConfig, unknown34) == 0x34, "");
static_assert(sizeof(FrameworkConfig) == 0x3c, "");

struct UpdateState {
  bool isPause;
};

// Inferred role: launcher interface; original type name unknown.
class unknown076 {
public:
  virtual void setDebugPause(bool isPause) = 0;
  virtual void stepDebugPause() = 0;
  virtual bool isDebugPause() const = 0;
  virtual bool resetApp() = 0;
};

// Inferred role: layer update info; original type name unknown.
struct unknown077 {
  f32 unknown00;  // Inferred role: speed; original member name unknown.
  f32 unknown04;  // Inferred role: scaled speed; original member name unknown.
  f32 unknown08;  // Inferred role: frame speed; original member name unknown.
  bool unknown0c; // Inferred role: pause; original member name unknown.
  bool unknown0d; // Inferred role: frame pause; original member name unknown.
};

static_assert(sizeof(unknown077) == 0x10, "");

class Framework : public mm::mtl::PtrSingleton<Framework> {
public:
  enum State {
    STATE_NONE = 0,
    STATE_INITIALIZED = 1,
    STATE_MANAGER_INITIALIZED = 2,
    STATE_ENTERED = 3,
    STATE_FINALIZING = 4,
    STATE_FINALIZED = 5,
  };

  static const u32 LAYER_MAX = 32;
  static const u32 PAUSE_TRIGGER_MAX = 32;
  static const u32 unknown001 = 14; // Inferred role: count of the layers run by update; original name unknown.

  ~Framework();
  void finalize();
  static mm::mtl::IAllocator *getAllocator();
  bool initializeManager();
  void createManager();
  static void destroyManager();
  bool finalizeManager();
  void prepareEnter();
  void prepareExit();
  void pauseEnter();
  void pauseExit();
  void activate();
  void deactivate();
  void beginFrame(const UpdateState &updateState);
  void endFrame(const UpdateState &updateState);
  void preUpdate();
  void update();
  static bool canUpdate();
  void tail(const UpdateState &updateState);
  void render();
  Applet *getApplet() const;
  bool isAppletClosed();
  void destroyApplet();
  void enterFinalizeApplet();
  static bool isInitialized();
  static mtl::ALLOC_HANDLE getMemHandle();
  static void setPause(bool isPause);
  static bool isPause();
  static void stepPause();
  static bool reqSoftReset();
  static void setUpdateSpeed(f32 speed);
  static void setLayerUpdateSpeed(u32 layer, f32 speed);
  static f32 getLayerUpdateSpeed(u32 layer);
  static void setLayerPause(u32 layer, bool isPause);
  static bool isLayerPause(u32 layer);
  static u32 getFrameCount();
  static const UpdateInfo *getUpdateInfo();
  static void addPauseCallback(IPauseTrigger *trigger);
  static void removePauseCallback(IPauseTrigger *trigger);

  bool isUpdating() const { return unknown84 >= STATE_MANAGER_INITIALIZED && unknown84 <= STATE_FINALIZING; }

  Applet *m_applet;
  FrameworkConfig unknown10; // Inferred role: config; original member name unknown.
  u8 _4c[0x50 - 0x4c];
  ml::WinProc *unknown50; // Inferred role: win proc; original member name unknown.
  ml::Scn *unknown58;     // Inferred role: scn; original member name unknown.
  u8 _60[0x68 - 0x60];
  mtl::ALLOC_HANDLE unknown68; // Inferred role: mem handle; original member name unknown.
  unknown076 *unknown70;       // Inferred role: launcher; original member name unknown.
  UpdateInfo unknown78;        // Inferred role: update info; original member name unknown.
  u32 unknown84;               // Inferred role: state; original member name unknown.
  u8 _88[0x8a - 0x88];
  bool unknown8a; // Inferred role: updated this frame; original member name unknown.
  u8 _8b[0x8c - 0x8b];
  f32 unknown8c; // Inferred role: update speed; original member name unknown.
  u8 _90[0x98 - 0x90];
  unknown077 unknown98[LAYER_MAX];                                     // Inferred role: layers; original member name unknown.
  mm::mtl::FixedVector<IPauseTrigger *, PAUSE_TRIGGER_MAX> unknown298; // Inferred role: pause triggers; original member name unknown.
  MemHandlebaseAllocator unknown3a0;                                   // Inferred role: allocator; original member name unknown.
};

static_assert(offsetof(Framework, unknown10) == 0x10, "");
static_assert(offsetof(Framework, unknown58) == 0x58, "");
static_assert(offsetof(Framework, unknown68) == 0x68, "");
static_assert(offsetof(Framework, unknown70) == 0x70, "");
static_assert(offsetof(Framework, unknown78) == 0x78, "");
static_assert(offsetof(Framework, unknown84) == 0x84, "");
static_assert(offsetof(Framework, unknown8c) == 0x8c, "");
static_assert(offsetof(Framework, unknown98) == 0x98, "");
static_assert(offsetof(Framework, unknown298) == 0x298, "");
static_assert(offsetof(Framework, unknown3a0) == 0x3a0, "");
static_assert(sizeof(Framework) == 0x3f0, "");

class IPauseTrigger {
public:
  IPauseTrigger();
  virtual ~IPauseTrigger();
  virtual void enterPauseCallback() {}
  virtual void exitPauseCallback() {}
  virtual void updatePauseCallback() {}
  virtual void activate() {}
  virtual void deactivate() {}
};

} // namespace fw
