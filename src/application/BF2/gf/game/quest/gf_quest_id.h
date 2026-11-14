#pragma once
#include "types.h"

namespace gf {

constexpr u32 QUEST_ID_UNKNOWN_15000 = 15000; // Inferred role: last variant of the first quest state flag range; original name unknown.
constexpr u32 QUEST_ID_UNKNOWN_30000 = 30000; // Inferred role: quest id end; original name unknown.

struct QuestID {
  // User-provided: the game returns a QuestID as two separately merged halves (and/orr of 32-bit words) as soon as a
  // constructor zeroes it (GfQuestManager::getOrderQuest, getReduceHpQuest, getListNextQuestA).
  QuestID() : unknown00(0), unknown02(0) {}
  QuestID(u16 id, u16 variant) : unknown00(id), unknown02(variant) {}
  bool empty() const;
  bool operator==(const QuestID &other) const { return unknown00 == other.unknown00 && unknown02 == other.unknown02; }
  // User-provided: the game assigns a QuestID member as two halfwords (GfFieldLocator::createByQuest, Locator*::create)
  // while copy construction stays a single word.
  QuestID &operator=(const QuestID &other) {
    unknown00 = other.unknown00;
    unknown02 = other.unknown02;
    return *this;
  }
  // Inferred name; kept as an exception to the unknown-name rule (AGENTS.md): single-user helper whose existence only the match proves; rename if a sibling build gives a symbol.
  // Tells whether the variant lies above the first quest state flag range. GfQuestInfo::getQuestFlag2No (1.0.0: 0x710036834c, 41 instructions) keeps this test as a 16-bit compare of its own
  // (lsr w8, w19, #16; mov w9, #15001; cmp w8, w9 at 0x7100368384 and 0x71003683ac) beside the variant it extracts once for its other reads (ubfx x21, x19, #16, #16 at 0x7100368368): the test
  // read the member through a pointer of its own.
  // Forms tried without the helper, written in getQuestFlag2No, all 39 instructions (the whole word is compared, cmp w19, #0x3a990000): unknown02 > 15000, unknown02 >= 15001, 15000 < unknown02,
  // a u16, u32 or int local of the variant, a bool local holding the test; a ternary choosing the base gives 35. A file-local helper taking the QuestID by value gives 39, one taking a reference
  // matches too.
  bool isHighVariant() const { return unknown02 > QUEST_ID_UNKNOWN_15000; }

  u16 unknown00; // Inferred role: id; original member name unknown.
  u16 unknown02; // Inferred role: variant; original member name unknown.
};

static_assert(sizeof(QuestID) == 4, "");

inline QuestID toQuestID(u32 quest) {
  QuestID questID = {static_cast<u16>(quest), static_cast<u16>(quest >> 16)};
  return questID;
}

} // namespace gf
