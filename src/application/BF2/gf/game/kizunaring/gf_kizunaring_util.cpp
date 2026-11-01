#include "gf/game/kizunaring/gf_kizunaring_util.h"

#include "gf/data/gf_bdat_blade.h"
#include "gf/data/gf_data_blade.h"
#include "gf/game/quest/gf_quest_util.h"
#include "ml/rand.h"

namespace gf {

namespace {

// Inferred role: first CHR_Bl_CreateConfig row of the completion reward sets, by crown point; original name unknown.
const u16 unknown001[] = {0, 0x31, 0x35, 0x39, 0x3d, 0x41};

} // namespace

u32 GfKizunaringUtil::getTotalLines(u32 blade) {
  u32 lines = 0;
  for (u32 line = 0; line < 10; line++) {
    if (GfDataBlade::getAchievInfo(blade, line)->unknown00 != 0) {
      lines++;
    }
  }

  return lines;
}

bool GfKizunaringUtil::getCompleteKizunaringReward(GfQuestReward &reward, u32 blade) {
  u32 config = unknown001[GfDataBlade::getCrownPoint(blade)] + ml::mtRand(4);
  u32 rewardSet = GfBdatBlade::get()->getCreateConfigValue(config);
  if (rewardSet == 0) {
    return false;
  }

  if (!GfQuestUtil::getReward(reward, rewardSet, false)) {
    return false;
  }

  reward.unknown360 = blade;
  return true;
}

void GfKizunaringUtil::getCompleteKizunaringRewardForDriver(GfQuestReward &reward) { GfQuestUtil::getReward(reward, 0x3a3, false); }

} // namespace gf
