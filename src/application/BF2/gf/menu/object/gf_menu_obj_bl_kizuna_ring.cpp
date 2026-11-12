#include "gf/menu/object/gf_menu_obj_bl_kizuna_ring.h"

#include "gf/data/gf_data_achievement.h"
#include "gf/game/gf_game_voice.h"
#include "gf/game/kizunaring/gf_kizunaring_manager.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_achievement_adapter.h"
#include "gf/menu/adapter/gf_menu_adapter_manager.h"
#include "gf/menu/adapter/gf_menu_char_data_adapter.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_pnt.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/list/ui_list_info.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x6a;

// Inferred role: menu id; original name unknown.
constexpr u32 unknown002 = 0x22;

GfMenuObjBlKizunaRing::GfMenuObjBlKizunaRing(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown38(false), unknown39(false), unknown3c(0), unknown40(-1), unknown48(nullptr), unknown50(0), unknown58(nullptr),
      unknown198(0), unknown1a0(this), unknown430(0), unknown434(0), unknown438(0), unknown43c(0), unknown440(nullptr), unknown448(nullptr), unknown450(0), unknown454(0), unknown458(nullptr),
      unknown460(0), unknown468(reinterpret_cast<GF_SCOM_HANDLE *>(-1)) {
  unknown58 = GfMenuCallContext::create();
}

GfMenuObjBlKizunaRing::~GfMenuObjBlKizunaRing() {
  mm::mtl::safeRelease(unknown58);
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown48);
  mm::mtl::safeRelease(unknown440);
  mm::mtl::safeRelease(unknown448);
}

void GfMenuObjBlKizunaRing::initialize() {
  {
    GfMenuTypes::Param layerParam;
    if (getFSLayerParam(unknown20, layerParam)) {
      unknown438 = layerParam.get<OpenParam>().unknown00;
      unknown43c = layerParam.get<OpenParam>().unknown04;
      removeFSLayerParam(unknown20);
    } else {
      unknown438 = 0;
    }
  }
  ui::UIObjectAcc acc(unknown18);
  u32 main = acc.searchChild("LAY_main");
// __LINE__ must be 191 as in the original file: it is the line argument of operator new.
#line 191
  MainListener *mainListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
  mainListener->addRef();
  ui::UIEventManager::get()->registObjectListener(main, mainListener);
  if (mainListener != nullptr) {
    mainListener->release();
  }
  attachExternalCall(unknown001, main);
  u32 ring = acc.searchChild("LAY_kizunaring");
// __LINE__ must be 197 as in the original file: it is the line argument of operator new.
#line 197
  RingListener *ringListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) RingListener(this);
  ringListener->addRef();
  ui::UIEventManager::get()->registObjectListener(ring, ringListener);
  if (ringListener != nullptr) {
    ringListener->release();
  }
  u32 ringBase = acc.searchChild("LAY_kizunaring_base");
// __LINE__ must be 201 as in the original file: it is the line argument of operator new.
#line 201
  RingPadListener *ringPadListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) RingPadListener(this);
  ringPadListener->addRef();
  ui::UIEventManager::get()->registObjectListener(ringBase, ringPadListener);
  if (ringPadListener != nullptr) {
    ringPadListener->release();
  }
  u32 skillInfo = acc.searchChild("LAY_skillinfo");
// __LINE__ must be 205 as in the original file: it is the line argument of operator new.
#line 205
  SkillDetailListener *skillDetailListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SkillDetailListener(this);
  skillDetailListener->addRef();
  ui::UIEventManager::get()->registObjectListener(skillInfo, skillDetailListener);
  if (skillDetailListener != nullptr) {
    skillDetailListener->release();
  }
  u32 skillStockInfo = acc.searchChild("LAY_skillstock_info");
// __LINE__ must be 215 as in the original file: it is the line argument of operator new.
#line 215
  BladeSkillInfoListener *bladeSkillInfoListener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) BladeSkillInfoListener(this);
  bladeSkillInfoListener->addRef();
  ui::UIEventManager::get()->registObjectListener(skillStockInfo, bladeSkillInfoListener);
  if (bladeSkillInfoListener != nullptr) {
    bladeSkillInfoListener->release();
  }
  ui::UISelectObjList::CreateParam param;
  param.allocator = getAllocator(ALLOCATOR_UNKNOWN_0);
  unknown28 = ui::UISelectObjList::create(param);
  unknown440 = GfMenuCallContext::create();
  unknown448 = GfMenuItemList::create();
  ui::UIListInfoBase::SetupParam itemParam;
  unknown448->setup(getAllocator(ALLOCATOR_UNKNOWN_0), itemParam);
  unknown48 = GfMenuCallContext::create();
  disableInput(acc.searchChild("LAY_kizunaring"));
  disableInput(acc.searchChild("LAY_kizunaring_base"));
  GfMenuObject::initialize();
}

void GfMenuObjBlKizunaRing::registOpenParam(const OpenParam &param) {
  GfMenuTypes::Param layerParam;
  OpenParam &data = layerParam.get<OpenParam>();
  data.unknown00 = param.unknown00;
  data.unknown04 = param.unknown04;
  GfMenuFullScreen::registLayerParam(getMenuLayerID(unknown002), layerParam);
}

void GfMenuObjBlKizunaRing::finalize() { GfMenuObject::finalize(); }

void GfMenuObjBlKizunaRing::update() {
  unknown1a0.unknown003();
  GfMenuObject::update();
}

void GfMenuObjBlKizunaRing::openForMercenary(u32 handle, u32 blade, u16 group) {
  OpenParam param;
  param.unknown00 = 1;
  param.unknown04 = blade;
  registOpenParam(param);
  changeFSSubLayer(handle, group, getMenuLayerID(unknown002), true);
}

bool GfMenuObjBlKizunaRing::isLockPos(int index) { return index % 10 == 0; }

bool GfMenuObjBlKizunaRing::isScreenLR(u32 screen) { return screen < 4; }

void GfMenuObjBlKizunaRing::setupMain(ui::UIObjectAcc &acc) {
  GfMenuCharDataAdapter::createFromReferenceBlade(acc.searchChild("IMG_face@01"), 3, 0, false);
  u32 background = acc.searchChild("IMG_bl_name_bg");
  u32 name = acc.searchChild("TXT_bl_name");
  GfMenuCharDataAdapter::createFromReferenceBlade(name, 2, 0, false);
  GfMenuObjUtil::FitOption option;
  GfMenuObjUtil::createFitPlugin(background, name, 42, 16, option);
}

void GfMenuObjBlKizunaRing::setupCircle(ui::UIObjectAcc &) {}

void GfMenuObjBlKizunaRing::setupBladeSkillInfo(ui::UIObjectAcc &acc) {
  GfMenuAchievementAdapter::createFromReferenceBlade(acc.searchChild("TXT_stocknum"), 16, 0, 0, 0, true);
  GfMenuAchievementAdapter::createFromReferenceBlade(acc.searchChild("TXT_stockmax"), 17, 0, 0, 0, false);
}

void GfMenuObjBlKizunaRing::setupSkillSimple(ui::UIObjectAcc &acc) {
  GfMenuAdapterManager::beginAddAfter();
  GfMenuAchievementAdapter::createFromReferenceBladeLineLevel(acc.searchChild("TXT_skillname"), 2, 0, 0, 1, false);
  GfMenuAchievementAdapter::createFromReferenceBladeLineLevel(acc.searchChild("IMG_skillicon"), 11, 0, 0, 1, false);
  GfMenuAchievementAdapter::createFromReferenceBladeLineLevel(acc.searchChild("IMG_skachicon"), 12, 0, 0, 1, false);
  GfMenuAdapterManager::endAddAfter();
}

void GfMenuObjBlKizunaRing::setupSkillDetail(ui::UIObjectAcc &acc) {
  GfMenuAdapterManager::beginAddAfter();
  GfMenuAchievementAdapter::createFromReferenceBladeLineLevel(acc.searchChild("TXT_questtitle"), 22, 0, 0, 1, false);
  GfMenuAchievementAdapter::createFromReferenceBladeLineLevel(acc.searchChild("TXT_questtitle2"), 23, 0, 0, 1, false);
  GfMenuAchievementAdapter::createFromReferenceBladeLineLevel(acc.searchChild("TXT_achinum"), 18, 0, 0, 1, false);
  GfMenuAchievementAdapter *count = GfMenuAchievementAdapter::createFromReferenceBladeLineLevel(acc.searchChild("TXT_achimax"), 19, 0, 0, 1, false);
  if (count != nullptr) {
    count->unknown24 = acc.searchChild("LAY_count");
  }
  GfMenuAchievementAdapter::createFromReferenceBladeLineLevel(acc.searchChild("LAY_neta"), 25, 0, 0, 1, false);
  mm::mtl::FixStr<32> name;
  for (u32 i = 1; i != 3; i++) {
    name.format("TXT_questinfo2@%02d", i);
    GfMenuAchievementAdapter::createFromReferenceBladeLineLevel(acc.searchChild(name.c_str()), 3, 0, 0, 1, false);
    name.format("TXT_skillname@%02d", i);
    GfMenuAchievementAdapter::createFromReferenceBladeLineLevel(acc.searchChild(name.c_str()), 2, 0, 0, 1, false);
    name.format("IMG_skill_icon@%02d", i);
    GfMenuAchievementAdapter::createFromReferenceBladeLineLevel(acc.searchChild(name.c_str()), 11, 0, 0, 1, false);
    name.format("IMG_skill_base@%02d", i);
    GfMenuAchievementAdapter::createFromReferenceBladeLineLevel(acc.searchChild(name.c_str()), 12, 0, 0, 1, false);
    name.format("IMG_idea_icon@%02d", i);
    GfMenuAchievementAdapter *idea = GfMenuAchievementAdapter::createFromReferenceBladeLineLevel(acc.searchChild(name.c_str()), 21, 0, 0, 1, false);
    if (idea != nullptr) {
      name.format("LAY_idea@%02d", i);
      idea->unknown24 = acc.searchChild(name.c_str());
    }
  }
  GfMenuAdapterManager::endAddAfter();
}

void GfMenuObjBlKizunaRing::setupRing(ui::UIObjectAcc &acc) {
  mm::mtl::FixStr<32> name;
  GfMenuAdapterManager::beginAddAfter();
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 10; j++) {
      name.format("IMG_node_icon@%02d", i + j * 5 + 1);
      if (acc.searchChild(name.c_str()) != 0) {
        GfMenuAchievementAdapter::createFromReferenceBlade(acc.searchChild(name.c_str()), 11, 0, j == 0 ? 9 : j - 1, i + 1, true);
        name.format("IMG_node_base@%02d", i + j * 5 + 1);
        if (acc.searchChild(name.c_str()) != 0) {
          GfMenuAchievementAdapter *base = GfMenuAchievementAdapter::createFromReferenceBlade(acc.searchChild(name.c_str()), 12, 0, j == 0 ? 9 : j - 1, i + 1, true);
          name.format("IMG_node_frame@%02d", i + j * 5 + 1);
          base->unknown24 = acc.searchChild(name.c_str());
        }
      }
    }
  }
  for (u16 level = 1; level <= 5; level++) {
    name.format("IMG_lock_icon@%02d", level);
    GfMenuAchievementAdapter::createFromReferenceBlade(acc.searchChild(name.c_str()), 24, 0, 9, level, true);
  }
  GfMenuAdapterManager::endAddAfter();
}

void GfMenuObjBlKizunaRing::setupRingList(ui::UIObjectAcc &acc, ui::UISelectObjList *list) {
  mm::mtl::FixStr<32> name;
  list->clear();
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 10; j++) {
      name.format("LAY_spot@%02d", i + j * 5 + 1);
      u32 spot = acc.searchChild(name.c_str());
      if (spot != 0) {
        list->addObject(spot);
      }
    }
  }
}

void GfMenuObjBlKizunaRing::movePointer(u32 handle, int index, ui::UISelectObjList *list) {
  setupInputSelection(handle, index, list->getSize());
  mm::Pnt<s16> pos;
  {
    ui::UIObjectAcc acc(list->getContents(index));
    acc.getPosCenter(pos);
  }
  changePointerPos(handle, pos);
}

void GfMenuObjBlKizunaRing::dispDetail(ui::UIObjectAcc &acc, u32 blade) {
  int line = GfMenuReference::getReferenceNumber(0);
  int level = GfMenuReference::getReferenceNumber(1);
  u16 type = GfMenuTypes::unknown003_33;
  if (GfKizunaringBlade::getReleaseAchievement(blade, GfMenuReference::getReferenceNumber(0), GfMenuReference::getReferenceNumber(1)) == 0) {
    type = GfMenuTypes::unknown003_34;
  }
  ACHIEVEMENT_TYPE achievementType;
  u32 index;
  if (GfDataAchievement::getAchievementType(achievementType, index, GfMenuReference::getReferenceNumber(0))) {
    if (achievementType == ACHIEVEMENT_TYPE_UNKNOWN_3 && line == 9 && level == 1) {
      type = GfMenuTypes::unknown003_34;
    }
  }
  unknown164(acc.searchChild("LAY_skillinfo"), type);
}

int GfMenuObjBlKizunaRing::getAchievementList(mm::mtl::FixedVector<Achievement, 50> &list, u32 &count, u32 &flags) {
  u32 blade = GfMenuReference::getReferenceBladeID(0);
  list.clear();
  for (int i = 4; i >= 0; i--) {
    u32 level = i + 1;
    for (int line = 9; line >= 0; line--) {
      if (GfKizunaringBlade::getReleaseAchievement(blade, line, level) == 3) {
        if (line == 9) {
          for (int other = 8; other >= 0; other--) {
            if (GfKizunaringBlade::getReleaseAchievement(blade, other, level) == 1) {
              list.push_back(Achievement(other, level, 1));
            }
          }
          if (i < 4) {
            list.push_back(Achievement(9, i + 2, 1));
          }
          count = 1;
          flags |= 1;
        } else {
          count = 2;
          flags |= 2;
        }
        list.push_back(Achievement(line, level, 3));
      }
    }
  }
  return list.size();
}

bool GfMenuObjBlKizunaRing::procAchieve(u32 handle, GfMenuObjBlKizunaRing *object) {
  object->unknown50 = 0;
  object->unknown454 = 0;
  if (getAchievementList(object->unknown60, object->unknown50, object->unknown454) == 0) {
    return false;
  }
  object->unknown430 = 1;
  object->unknown434 = 0;
  object->unknown1a0.unknown005();
  object->unknown1a0.unknown002(&GfMenuObjBlKizunaRing::seqAchieve);
  if (object->unknown438 == 0) {
    GfMenuObjMainMenu2::disableCharChange();
  }
  ui::UIObjectAcc cursor(handle, "IMG_kizunacursor");
  cursor.setDisp(false);
  {
    ui::UIObjectAcc acc(handle);
    disableInput(acc.searchChild("LAY_kizunaring_base"));
  }
  if (object->unknown438 == 0) {
    GfMenuObjMainMenu2::setCloseKeyEnable(false);
  }
  return true;
}

void GfMenuObjBlKizunaRing::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjBlKizunaRing::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 1, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjBlKizunaRing::setFadeOut(u32 handle) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 2, 0);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

bool GfMenuObjBlKizunaRing::attach(GfMenuCallContext *context) { return unknown151(context, unknown001); }

bool GfMenuObjBlKizunaRing::seqWait() {
  ui::UIObjectAcc acc(unknown18);
  ui::UIObjectAcc base(acc.searchChild("LAY_kizunaring_base"));
  enableInput(base.unknown10);
  return true;
}

bool GfMenuObjBlKizunaRing::seqEnd() {
  ui::UIObjectAcc acc(unknown18);
  refreshRing(acc);
  ui::UIObjectAcc cursor(acc.searchChild("IMG_kizunacursor"));
  cursor.setDisp(true);
  cursor.startAnimation("loop", false);
  enableInput(acc.searchChild("LAY_kizunaring_base"));
  if (unknown438 == 0) {
    GfMenuObjMainMenu2::setCloseKeyEnable(true);
  }
  unknown140(acc.searchChild("LAY_kizunaring"), GfMenuTypes::unknown003_33, 0, 0.0f);
  return true;
}

bool GfMenuObjBlKizunaRing::seqWaitVoice() {
  u32 result = GfGameVoice::getResult(unknown458);
  if (result == VOICE_RESULT_UNKNOWN_1 || result == VOICE_RESULT_UNKNOWN_2) {
    return false;
  }
  ui::UIObjectAcc acc(unknown18);
  unknown140(acc.searchChild("LAY_main"), GfMenuTypes::unknown003_33, 0, 0.0f);
  return true;
}

void GfMenuObjBlKizunaRing::BladeSkillInfoListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc owner(unknown20->unknown18);
  ui::UIObjectAcc acc(handle);
  if (event.unknown00 == 1) {
    setupBladeSkillInfo(acc);
    acc.setDisp(true);
  } else {
    ui::UIObjectListener::reciveEvent(event, handle);
  }
}
} // namespace gf

template bool gf::GfMenuSequence<gf::GfMenuObjBlKizunaRing, 8>::wait();
template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuSequence<gf::GfMenuObjBlKizunaRing, 8>>(const mm::mtl::Delegate<bool()> *);
template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjBlKizunaRing>(const mm::mtl::Delegate<bool()> *);
