#pragma once
#include <stddef.h>

#include "anm/anm_string_ptr.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/set.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace anm {

class Binding;
class Control;
class ExtraTruckSlot;
class Pose;
class Skeleton;
class ResASM;
struct QsTransform;
struct ResAppendix;
struct ResState;

enum PlayMode {
  PLAY_MODE_LOOP,
  PLAY_MODE_ONCE,
};

enum Layer {
  LAYER_INVALID = -1,
  LAYER_BASE,
  LAYER_UPPERBODY,
  LAYER_HEAD,
  LAYER_EYE,
  LAYER_MOUTH,
  LAYER_BROW,
  LAYER_EXTRA,
  LAYER_NUM,
};

class Util {
public:
  // Inferred name prefix of a bone to ignore when mirroring; original member names unknown.
  // Layout evidence: the copy in Vector<IgnoreName>::push_back (0x710014e190) runs the FixStr<8> assignment (strlen, assert < 8, strcpy) and copies the word at 0x0c.
  struct IgnoreName {
    mm::mtl::FixStr<8> unknown00; // Inferred role: name prefix; original member name unknown.
    u32 unknown0c;                // Inferred role: unused in the matched code; original member name unknown.
  };

  // Pair of bone name prefixes read by computeBonePairFromName; original member names unknown.
  // Layout evidence: the copy in Vector<PairName>::push_back (0x710014e544) runs the FixStr<8> assignment at 0x00 and at 0x0c, element size 0x18.
  struct PairName {
    mm::mtl::FixStr<8> unknown00; // Inferred role: first name prefix; original member name unknown.
    mm::mtl::FixStr<8> unknown0c; // Inferred role: second name prefix; original member name unknown.
  };

  static const char *getName(const Binding &binding);
  static s32 getAnimationType(const Binding &binding);
  static PlayMode getPlayMode(const Binding &binding);
  static u8 getBlendHint(const Binding &binding);
  static u32 getFrameCount(const Binding &binding);
  static f32 getPlayBackTime(const Binding &binding);
  static bool hasLocomotion(const Binding &binding);
  static f32 getFps(const Binding &binding);
  static f32 getInvFps(const Binding &binding);
  static f32 calcLocalTime(f32 time, f32 start, f32 end, PlayMode playMode);
  static void setKeyFrame(Control &control, f32 frame);
  static bool getAsmPlaybackTime(const ResASM &resAsm, const char *state, u32 index, f32 *time);
  static const Binding *getAsmBinding(const ResASM &resAsm, const char *state, u32 index);
  static bool getAsmLocomotionReference(const ResASM &resAsm, const char *state, f32 time, u32 index, QsTransform *transform);
  static bool getAsmLocomotionDeltaReference(const ResASM &resAsm, const char *state, f32 startTime, f32 endTime, u32 index, QsTransform *transform);
  static void computeIgnoreMirrorFromName(const mm::mtl::Vector<IgnoreName> &names, const Skeleton *skeleton, mm::mtl::Vector<s8> *ignore);
  static const char *getLayerName(Layer layer);
  static Layer getLayer(const char *name);
  static const ResState *getStateResource(const ResASM &resAsm, const char *name);
  static const ResState *getSimpleStateResource(const ResASM &resAsm, const char *name);
  static const ResState *getComplexStateResource(const ResASM &resAsm, const char *name);
  static const ResState *getFrozenStateResource(const ResASM &resAsm, const char *name);
  static const ResAppendix *findAppendix(const ResASM &resAsm, const char *name);
  static void samplePoseSmartFromControl(Control *control, Pose *pose, bool localSpace);
  static void setReferrenceExtraTruck(const ExtraTruckSlot &slot, u32 count, f32 *values);
  static void clampLimitExtraTruck(const ExtraTruckSlot &slot, u32 count, f32 *values);
  static bool getVariableMinMax(const ResASM &resAsm, const char *stateName, const char *variableName, f32 *pMin, f32 *pMax);
  static void queryState(u32 mask, const ResASM &resAsm, mm::mtl::Set<StringPtr> *pDst);
  static void queryCmd(u32 mask, const ResASM &resAsm, mm::mtl::Set<StringPtr> *pDst);
  static void queryCmdFromStateSimple(u32 mask, const ResASM &resAsm, const StringPtr &state, mm::mtl::Set<StringPtr> *pDst);
  static bool queryStateAutoTrans(u32 mask, const ResASM &resAsm, const StringPtr &state, StringPtr *autoTrans);
  static void queryStateFromStateCmd(u32 mask, const ResASM &resAsm, const StringPtr &state, const StringPtr &cmd, mm::mtl::Set<StringPtr> *pDst);
  static void queryVariableFloat(const ResASM &resAsm, mm::mtl::Set<StringPtr> *pDst);
  static void queryVariableInt(const ResASM &resAsm, mm::mtl::Set<StringPtr> *pDst);
};

static_assert(offsetof(Util::IgnoreName, unknown0c) == 0x0c, "");
static_assert(sizeof(Util::IgnoreName) == 0x10, "");
static_assert(offsetof(Util::PairName, unknown0c) == 0x0c, "");
static_assert(sizeof(Util::PairName) == 0x18, "");

} // namespace anm
