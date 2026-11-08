#pragma once
#include <stddef.h>

#include "anm/anm_array-inl.h"
#include "mm_mtl/map.h"
#include "mm_mtl/singleton.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace anm {
class StringPtr;
} // namespace anm

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {
class SoundVariableTable;

// Layouts from SoundResSourceManager::endPush and playSe (1.0.0: 0x71001abeac, 0x71001ac394).
struct ResSoundData {
  const char *unknown00; // Inferred role: sound pack name; original member name unknown.
  u32 unknown08;         // Inferred role: sound id in the pack; original member name unknown.
};

static_assert(sizeof(ResSoundData) == 0x10, "");

struct ResSoundSourceBase {
  const char *unknown00; // Inferred role: name, the key of the source map; original member name unknown.
  u32 unknown08;         // Inferred role: type, 0 for a single sound and 1 for a complex one; original member name unknown.
};

static_assert(offsetof(ResSoundSourceBase, unknown08) == 0x08, "");
static_assert(sizeof(ResSoundSourceBase) == 0x10, "");

struct ResComplexSoundSource : public ResSoundSourceBase {
  // Inferred role: sound selected by the values of the variables; original type name unknown.
  struct unknown001 {
    ResSoundData unknown00;    // Inferred role: sound; original member name unknown.
    anm::Array<s32> unknown10; // Inferred role: expected value of each variable, negative for any value; original member name unknown.
  };

  anm::Array<const char *> unknown10; // Inferred role: variable names; original member name unknown.
  anm::Array<unknown001> unknown20;   // Inferred role: sounds by variable values; original member name unknown.
};

static_assert(offsetof(ResComplexSoundSource::unknown001, unknown10) == 0x10, "");
static_assert(sizeof(ResComplexSoundSource::unknown001) == 0x20, "");
static_assert(offsetof(ResComplexSoundSource, unknown10) == 0x10, "");
static_assert(offsetof(ResComplexSoundSource, unknown20) == 0x20, "");
static_assert(sizeof(ResComplexSoundSource) == 0x30, "");

struct ResSoundSource {
  // Inferred role: single sound source; original type name unknown.
  struct unknown001 : public ResSoundSourceBase {
    ResSoundData unknown10; // Inferred role: sound of the source; original member name unknown.
  };

  anm::Array<unknown001> unknown00;            // Inferred role: single sources; original member name unknown.
  anm::Array<ResComplexSoundSource> unknown10; // Inferred role: complex sources; original member name unknown.
};

static_assert(offsetof(ResSoundSource::unknown001, unknown10) == 0x10, "");
static_assert(sizeof(ResSoundSource::unknown001) == 0x20, "");
static_assert(offsetof(ResSoundSource, unknown10) == 0x10, "");

int findComplexIndex(const SoundVariableTable &table, const ResComplexSoundSource *source);

class SoundResSourceImporter {
public:
  static const ResSoundSource *importBinary(void *data);
};

class SoundResSourceManager : public mm::mtl::PtrSingleton<SoundResSourceManager> {
public:
  SoundResSourceManager();
  ~SoundResSourceManager() override;
  static void clearAll();
  static void beginPush(u32 count, mm::mtl::IAllocator *allocator);
  static void endPush();
  static void pushResource(const ResSoundSource *source);
  static void stopSe(u32 handle, f32 time);

  mm::mtl::Map<anm::StringPtr, const ResSoundSourceBase *> unknown08; // Inferred role: sources by name; original member name unknown.
  mm::mtl::Vector<const ResSoundSource *> unknown20;                  // Inferred role: pushed resources; original member name unknown.
  bool unknown48;                                                     // Role and original member name unknown.
};

static_assert(offsetof(SoundResSourceManager, unknown08) == 0x08, "");
static_assert(offsetof(SoundResSourceManager, unknown20) == 0x20, "");
static_assert(offsetof(SoundResSourceManager, unknown48) == 0x48, "");
static_assert(sizeof(SoundResSourceManager) == 0x50, "");

} // namespace fw
