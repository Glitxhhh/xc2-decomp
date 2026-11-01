#pragma once
#include "gf/menu/gf_menu_object.h"
#include "gf/menu/object/gf_menu_obj_util.h"
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
};

} // namespace gf
