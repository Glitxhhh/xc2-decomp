#include "gf/data/gf_game_flag.h"
#include "gf/data/gf_data_game.h"
#include "gf/data/gf_data_manager.h"
#include "gf/event/gf_event.h"
#include "gf/gf_allocator.h"

namespace gf {

enum {
  FLAG16_UNKNOWN_1 = 1, // Inferred role: flag16 scenario; original name unknown.
};

enum {
  FLAG_UNKNOWN_3336 = 0xd08,     // Inferred role: flag word end; original name unknown.
  FLAG_UNKNOWN_6408 = 0x1908,    // Inferred role: flag short end; original name unknown.
  FLAG_UNKNOWN_88328 = 0x15908,  // Inferred role: flag byte end; original name unknown.
  FLAG_UNKNOWN_153864 = 0x25908, // Inferred role: flag bit end; original name unknown.
};

GfGameFlag::GfGameFlag(const GfSetupParam &param) : mInitialized(false) { initialize(param); }

void GfGameFlag::initialize(const GfSetupParam &) { mInitialized = true; }

GfGameFlag::~GfGameFlag() {}

void GfGameFlag::build(const GfSetupParam &param) {
  // __LINE__ must be 57 as in the original file: its value changes the instruction order.
#line 57
  new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfGameFlag(param);
}

void GfGameFlag::destroy() {
  GfGameFlag *gameFlag = get();
  gameFlag->finalize();
  delete gameFlag;
}

void GfGameFlag::finalize() { mInitialized = false; }

bool GfGameFlag::isInitialized() {
  GfGameFlag *gameFlag = get();
  if (gameFlag == nullptr) {
    return false;
  }

  return gameFlag->mInitialized;
}

void GfGameFlag::sendCallback(u32 size, u32 index, u32 value, u32 oldValue) {
  if (size == 16 && index == FLAG16_UNKNOWN_1) {
    GfEvent::callChangeScenarioFlag(value, oldValue);
  }
}

void GfGameFlag::getFlagInfo(int flag, u32 &size, u32 &index) {
  u32 globalIndex = flag;
  if (globalIndex < FLAG_UNKNOWN_3336) {
    size = 32;
    index = flag;
    return;
  }

  if (globalIndex < FLAG_UNKNOWN_6408) {
    size = 16;
    index = flag - FLAG_UNKNOWN_3336;
  } else if (globalIndex < FLAG_UNKNOWN_88328) {
    size = 8;
    index = flag - FLAG_UNKNOWN_6408;
  } else if (globalIndex < FLAG_UNKNOWN_153864) {
    size = 1;
    index = flag - FLAG_UNKNOWN_88328;
  }
}

void GfGameFlag::setFlag(int flag, u32 value) {
  u32 globalIndex = flag;
  u32 size;
  int index;
  if (globalIndex < FLAG_UNKNOWN_3336) {
    size = 32;
    index = flag;
  } else if (globalIndex < FLAG_UNKNOWN_6408) {
    size = 16;
    index = flag - FLAG_UNKNOWN_3336;
  } else if (globalIndex < FLAG_UNKNOWN_88328) {
    size = 8;
    index = flag - FLAG_UNKNOWN_6408;
  } else {
    size = 1;
    index = flag - FLAG_UNKNOWN_88328;
  }

  setLocal(size, index, value);
}

u32 GfGameFlag::getFlag(int flag) {
  u32 globalIndex = flag;
  u32 size;
  int index;
  if (globalIndex < FLAG_UNKNOWN_3336) {
    size = 32;
    index = flag;
  } else if (globalIndex < FLAG_UNKNOWN_6408) {
    size = 16;
    index = flag - FLAG_UNKNOWN_3336;
  } else if (globalIndex < FLAG_UNKNOWN_88328) {
    size = 8;
    index = flag - FLAG_UNKNOWN_6408;
  } else {
    size = 1;
    index = flag - FLAG_UNKNOWN_88328;
  }

  return getLocal(size, index);
}

u32 GfGameFlag::getMaxFlag(int size) {
  switch (size) {
  case 1:
  case 2:
    return 0x10000;
  case 4:
  case 8:
    return 0x2000;
  case 16:
    return 0xc00;
  case 32:
    return 0xd08;
  default:
    return 0;
  }
}

void GfGameFlag::clear() { __builtin_memset(&GfDataManager::getDataGame()->unknownfbbc4, 0, sizeof(GameFlag)); }

} // namespace gf
