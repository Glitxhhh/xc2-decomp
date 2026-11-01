#pragma once
#include "types.h"

namespace gf {

struct GfQuestReward;

class GfKizunaringUtil {
public:
  static u32 getTotalLines(u32 blade);
  static bool getCompleteKizunaringReward(GfQuestReward &reward, u32 blade);
  static void getCompleteKizunaringRewardForDriver(GfQuestReward &reward);
};

} // namespace gf
