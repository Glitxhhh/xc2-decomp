#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "types.h"

namespace gf {

class GfMenuCallContext;
struct QuestID;
struct QuestTaskParam;

class GfMenuObjQuestLog : public GfMenuObject {
public:
  // Inferred helper: fades out the title text and an optional subtitle child; original name unknown.
  void unknown004(const char *sub) {
    GfMenuObjUtil::CtrlParam param;
    param.unknown00 = 0.2f;
    param.unknown08 = 2;
    param.unknown14 = 2;
    GfMenuObjUtil::startCtrl(unknown18, param, "TXT_title");
    if (sub != nullptr) {
      GfMenuObjUtil::startCtrl(unknown18, param, sub);
    }
  }

  // Inferred helper: fades in a title child; original name unknown.
  void unknown005(const char *child) {
    GfMenuObjUtil::CtrlParam param;
    param.unknown00 = 0.2f;
    param.unknown08 = 1;
    GfMenuObjUtil::startCtrl(unknown18, param, child);
  }

  static void changeActiveQuest();
  static void updateTask();
  static void completeTask(const QuestTaskParam &param);
  static void closeLog();
  static void openLog();
  bool seqLogNextEnd();
  bool seqLogStart();
  bool seqOrderWait();
  bool seqTitleEndWait();
  bool seqTitleFadeInScenario();
  bool seqTitleFadeInText();
  bool seqLogOut();
  bool seqTitleFadeOutScenario();
  bool seqTitleFadeInNormal();
  bool seqTitleFadeOutNormal();
  bool seqTitleFadeOutText();
  void initialize() override;
  void finalize() override;
  static void order(GfMenuCallContext *context, QuestID quest);
  static void complete(GfMenuCallContext *context, QuestID quest);
  static void lockLogOpen();
  static void unlockLogOpen();

  u8 _24[0x810 - 0x24];
  bool unknown810; // Inferred role: control started flag of the multi-step sequences; original member name unknown.
  u8 _811[0x818 - 0x811];
  bool unknown818; // Inferred role: order activation request flag; original member name unknown.
};

static_assert(offsetof(GfMenuObjQuestLog, unknown810) == 0x810, "");
static_assert(offsetof(GfMenuObjQuestLog, unknown818) == 0x818, "");
} // namespace gf
