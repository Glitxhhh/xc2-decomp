#include "gf/menu/object/gf_menu_obj_shop.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_map.h"
#include "gf/data/gf_data_util.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_util.h"
#include "gf/game/gf_game_util_shop.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gf/game/quest/gf_quest_info.h"
#include "gf/game/quest/gf_quest_manager.h"
#include "gf/game/sequential_play/gf_sequential_play.h"
#include "gf/menu/adapter/gf_menu_adapter_manager.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/gf_menu_fade.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_id_list.h"
#include "gf/menu/object/gf_menu_obj_bl_weapon2.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_sort.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/request/gf_req_scom.h"
#include "gf/scom/gf_scom_achiev.h"
#include "mm_math/mm_col4.h"
#include "mm_mtl/delegate.h"
#include "ui/event/ui_event_data.h"
#include "ui/list/ui_list_info.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x77;
// Inferred role: active adapter category; original name unknown.
constexpr u32 unknown002 = 1;
// Inferred role: common window shown for orb error 1; original name unknown.
constexpr u16 unknown003 = 0xaf;
// Inferred role: common window shown for orb error 2; original name unknown.
constexpr u16 unknown004 = 0xb0;
// Inferred role: pause bits requested while sleeping at the inn; original name unknown.
constexpr u32 unknown005 = 0x59;
// Inferred role: achievement statistics id counting inn stays; original name unknown.
constexpr u32 unknown006 = 0x23;

u32 GfMenuObjShop::getSellItemTypeMax() { return 0xd; }

void GfMenuObjShop::open(GfMenuCallContext *context, const OpenParam &param) {
  ui::UIObjectAcc acc(getAttachedObject(unknown001));
  if (acc.isValid() && GfMenuObjUtil::checkCCStart(context)) {
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_33;
    event.unknown08_u16 = param.unknown00;
    GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
    GfMenuObject::startCallContext(context, unknown001, acc.unknown10);
    GfMenuAdapterManager::addActiveCategory(unknown002);
  }
}

void GfMenuObjShop::close(GfMenuCallContext *context) {
  if (GfMenuObjUtil::checkCCNext(context, unknown001)) {
    ui::UIObjectAcc acc(context->unknown14);
    if (acc.isValid()) {
      ui::EventData event;
      event.unknown00 = GfMenuTypes::unknown003_34;
      GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
      GfMenuAdapterManager::delActiveCategory(unknown002);
    }
  }
}

void GfMenuObjShop::dispBlade(bool isDisp) { gf::unknown150(unknown001, 0x46, isDisp); }

void GfMenuObjShop::openOrbError(u32 error) {
  switch (error) {
  case 1:
    GfMenuManager::openCommonWindow(unknown003);
    break;
  case 2:
    GfMenuManager::openCommonWindow(unknown004);
    break;
  }
}

bool GfMenuObjShop::seqWaitFSClose() { return !GfMenuManager::isOpenFullScreen(); }

void GfMenuObjShop::sendEnableEvent(u32 handle) {
  if (handle == 0) {
    handle = ui::UIObjectAcc(unknown18, "LAY_main").unknown10;
  }
  ui::EventData event;
  event.unknown00 = 0x40;
  GfMenuObject::sendEvent(handle, event, 0.0f);
}

void GfMenuObjShop::sendExitEvent(u32 handle) {
  if (handle == 0) {
    handle = ui::UIObjectAcc(unknown18, "LAY_main").unknown10;
  }
  ui::EventData event;
  event.unknown00 = 0x41;
  GfMenuObject::sendEvent(handle, event, 0.0f);
}

void GfMenuObjShop::sendCloseEvent(u32 handle) {
  if (handle == 0) {
    handle = ui::UIObjectAcc(unknown18, "LAY_main").unknown10;
  }
  ui::EventData event;
  event.unknown00 = 0x22;
  GfMenuObject::sendEvent(handle, event, 0.0f);
}

void GfMenuObjShop::sendOpenEvent(u32 handle, int value) {
  if (handle == 0) {
    handle = ui::UIObjectAcc(unknown18, "LAY_main").unknown10;
  }
  ui::EventData event;
  event.unknown08 = value;
  event.unknown0c = 0;
  event.unknown00 = GfMenuTypes::unknown003_33;
  GfMenuObject::sendEvent(handle, event, 0.0f);
}

void GfMenuObjShop::sendReturnEvent(u32 handle, int value) {
  if (handle != 0) {
    ui::EventData event;
    event.unknown08 = value;
    event.unknown0c = 0;
    event.unknown00 = 0x42;
    GfMenuObject::sendEvent(handle, event, 0.0f);
  }
}

void GfMenuObjShop::addCallContextResult(u32 type, u32 value) {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  GfMenuObject::addResultCallContext(main.unknown10, type, value);
}

void GfMenuObjShop::reqRefreshItemList() { unknown59 = true; }

void GfMenuObjShop::update() {
  unknown248.unknown003();
  if (unknown59) {
    refreshItemList();
    unknown59 = false;
  }
  GfMenuObject::update();
}

bool GfMenuObjShop::seqEndDialog() {
  if (unknown4f8 != 0) {
    ui::EventData event;
    event.unknown00 = 0x42;
    GfMenuObject::sendEvent(unknown4f8, event, 0.0f);
  }
  return true;
}

bool GfMenuObjShop::seqIntervalSleep() {
  if (unknown4d8 == 0) {
    unknown4d8 = 1;
  }
  return --unknown4d8 == 0;
}

bool GfMenuObjShop::seqWaitLoadBlWeapon() {
  unknown570->reset();
  if (GfMenuObjBlWeapon2::attach(unknown570)) {
    unknown248.unknown002(&GfMenuObjShop::seqWaitEndBlWeapon);
    return true;
  }
  return false;
}

bool GfMenuObjShop::seqWaitEndBlWeapon() {
  if (!unknown570->isTerm()) {
    return false;
  }
  ui::UIObjectAcc main(unknown18, "LAY_main");
  sendEnableEvent(main.searchChild("LAY_store_action"));
  return true;
}

u32 GfMenuObjShop::getShopSubLayer(u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (unknown28) {
  case 0:
    return acc.searchChild("LAY_store");
  case 1:
    return acc.searchChild("LAY_exchange");
  case 2:
    return acc.searchChild("LAY_inn");
  case 3:
    return acc.searchChild("LAY_orb");
  }
  return 0;
}

u32 GfMenuObjShop::getShopSubActLayer(u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (unknown28) {
  case 0:
    return acc.searchChild("LAY_store_action");
  case 1:
    return acc.searchChild("LAY_exc_task_list");
  case 2:
    return acc.searchChild("LAY_inn_action");
  case 3:
    return acc.searchChild("LAY_orb_item_list");
  }
  return 0;
}

int GfMenuObjShop::getSpecialShop(u32 shop) {
  if (shop != 0) {
    u8 *bdat = GfDataBdat::getFP(BDAT_MNU_SPECIAL_SHOP);
    if (bdat != nullptr) {
      u16 scenarioFlag = GfDataUtil::getScenarioFlag();
      int top = Bdat::getIdTop(bdat);
      for (int i = 0; i < Bdat::getIdCount(bdat); i++) {
        int id = top + i;
        u16 flag = Bdat::getVal(bdat, "scenario_flag", id).valueU16;
        if (flag == 0 || scenarioFlag == flag) {
          u16 shopId = Bdat::getVal(bdat, "shop_id", id).valueU16;
          if (shopId != 0 && shopId == shop) {
            return id;
          }
        }
      }
    }
  }
  return 0;
}

bool GfMenuObjShop::isShopWeapon(u32 shop) {
  u8 *bdat = GfDataBdat::getFP(BDAT_MNU_SHOP_LIST);
  if (Bdat::getVal(bdat, "ShopType", shop).valueS8 == 0 && Bdat::getVal(bdat, "ShopIcon", shop).valueU16 == 0x1ae) {
    return true;
  }
  return false;
}

bool GfMenuObjShop::seqStartSleepFade() {
  GfSequentialPlay::pauseOn(unknown005);
  SCOM_ACHIEV_INC::addTotalCount(unknown006, 1);
  SCOM_ACHIEV_INC::create(unknown006, 1, 0);
  SCOM_FIELD_VOICE::createExitInn();
  SCOM_RANDOM_INN::setRandom();
  unknown248.unknown002(&GfMenuObjShop::seqWaitSleepFade);
  unknown248.unknown002(&GfMenuObjShop::seqIntervalSleep);
  unknown248.unknown002(&GfMenuObjShop::seqStartLevelUp);
  unknown4d8 = 0;
  unknown4dc = false;
  return true;
}

bool GfMenuObjShop::seqWaitSleepFade() {
  if (!unknown4dc) {
    GfMenuFade::setFade(2, 30, mm::Col4::black);
    unknown4dc = true;
    return false;
  }
  return !GfMenuManager::isFading();
}

void GfMenuObjShop::openNumSelect(u32 owner, u32 value, bool isFlag) {
  ui::UIObjectAcc acc(unknown18, "LAY_num_select");
  unknownd0 = owner;
  ui::EventData event;
  event.unknown00 = 0x21;
  event.unknown08 = value;
  event.unknown0c = 0x280;
  event.unknown10 = 0x1e0;
  event.unknown14 = isFlag;
  GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
}

bool GfMenuObjShop::seqStartLevelUp() {
  if (unknown240) {
    GfGameUtilCloudSea::setInnCloudSea(static_cast<CLOUD_SEA>(GfGameUtilCloudSea::getCloudSea() == 0));
    unknown240 = false;
  }
  GfMenuManager::openFullScreen(5, true, true);
  unknown248.unknown002(&GfMenuObjShop::seqWaitFSClose);
  unknown248.unknown002(&GfMenuObjShop::seqEnd);
  return true;
}

bool GfMenuObjShop::seqEnd() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  GfSequentialPlay::pauseOff();
  if (unknown4e0 != 0) {
    addCallContextResult(unknown4e0, unknown4e4);
  }
  GfMenuObject::termCallContext(main.unknown10);
  return true;
}

bool GfMenuObjShop::getExcTaskQuestAdditionalValue(u32 id, u32 &value) {
  u8 *bdat = GfDataBdat::getFP(BDAT_MNU_SHOP_CHANGE_TASK);
  if (bdat != nullptr && GfMenuBdat::isValidBdatID(bdat, id)) {
    value = Bdat::getVal(bdat, "AddFlagValue", id).valueU8;
    return true;
  }
  return false;
}

void GfMenuObjShop::setFilterIndex() {
  u32 filter = unknown60[unknownc0];
  ui::UIObjectAcc acc(unknown18, "TXT_store_sell_index");
  if (acc.isValid()) {
    u8 *bdat = GfDataBdat::getFP(BDAT_MENU_FILTER_CATEGORY);
    ui::UIStr text(bdat, GfMenuObjUtil::getMsgIDFromList(BDAT_MNU_MSG_ITEM_LIST_FILTER, filter + 1));
    acc.setText(text);
  }
}

bool GfMenuObjShop::seqEndRecipeIndexOpen() {
  ui::UIObjectAcc acc(unknown18, "LAY_orb_rcp");
  switch (unknownfc) {
  case 0:
    acc.setDispChild(true, "TXT_orb_rcp_type_rare_index");
    break;
  case 1:
    acc.setDispChild(true, "TXT_orb_rcp_type_cate_index");
    break;
  default:
    acc.setDispChild(false, "TXT_orb_rcp_type_rare_index");
    acc.setDispChild(false, "TXT_orb_rcp_type_cate_index");
    break;
  }
  return true;
}

void GfMenuObjShop::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case GfMenuTypes::unknown003_33: {
    unknown20->unknown24 = event.unknown08;
    unknown20->unknown34 = getSpecialShop(unknown20->unknown24);
    u8 *bdat = GfDataBdat::getFP(BDAT_MNU_SHOP_LIST);
    if (bdat == nullptr) {
      return;
    }
    unknown20->unknown28 = Bdat::getVal(bdat, "ShopType", unknown20->unknown24).valueU8;
    unknown20->unknown30 = Bdat::getVal(bdat, "TableID", unknown20->unknown24).valueU16;
    unknown20->unknown2c = Bdat::getVal(bdat, "ShopIcon", unknown20->unknown24).valueU16;
    GfMenuReference::setReferenceShopID(unknown20->unknown24);
    if (unknown20->unknown28 == 1 || unknown20->unknown28 == 3) {
      GfMenuObjUtil::setChildDisp(handle, "LAY_location", false);
      GfMenuObjUtil::setChildDisp(handle, "LAY_index_money", false);
    } else {
      GfMenuObjUtil::setChildDisp(handle, "LAY_location", true);
      GfMenuObjUtil::setChildDisp(handle, "LAY_index_money", true);
    }
    unknown20->unknown4e0 = 0;
    unknown20->unknown4e4 = 0;
    acc.setDispChild(false, "TXT_common_guide");
    unknown20->unknown38 = 0;
    int isQuest = 0;
    if (unknown20->unknown28 == 2) {
      u32 price = GfGameUtilShop::getNeedMoneyForInn(unknown20->unknown24);
      if (price != 0) {
        unknown20->unknown168[3]->unknown162(price);
        unknown20->unknown168[4]->unknown162(price * 2);
        u32 money = GfDataUtil::getMoney();
        u32 need = unknown20->unknown168[3]->unknown0c;
        u32 text = acc.searchChild("TXT_inn_action@01");
        if (money < need) {
          GfMenuObjUtil::setColMulandAdd(text, "txt_disable");
        } else {
          GfMenuObjUtil::setColDefault(text);
        }
        money = GfDataUtil::getMoney();
        need = unknown20->unknown168[4]->unknown0c;
        text = acc.searchChild("TXT_inn_action@02");
        if (money < need) {
          GfMenuObjUtil::setColMulandAdd(text, "txt_disable");
        } else {
          GfMenuObjUtil::setColDefault(text);
        }
      } else {
        unknown20->unknown248.unknown005();
        unknown20->unknown248.unknown002(&GfMenuObjShop::seqStartSleepFade);
        unknown20->unknown4e0 = 1;
        unknown20->unknown4e4 = 0;
        acc.setSuspend(false);
        break;
      }
    } else if (unknown20->unknown28 == 3) {
      GfMenuObjSort::setSortLabelText(GfMenuObjSort::getSortID(8, 0), acc.searchChild("TXT_orb_item_sort_label"));
      unknown20->unknown14c = 0;
    } else if (unknown20->unknown28 == 1) {
      ui::UIListInfoBase::SetupParam param;
      param.unknown08 = 8;
      param.unknown10 = true;
      acc.setDispChild(false, "TXT_exc_task_index");
      acc.setDispChild(false, "TXT_exc_task_index_quest");
      acc.setDispChild(false, "TXT_exc_task_index_cook");
      acc.setDispChild(false, "TXT_exc_task_index_craft");
      unknown20->unknown150->setupExcTaskListFromShop(param, unknown20->unknown24);
      unknown20->unknown150->setIndex(0);
      int taskType;
      if (unknown20->unknown150->getSize() != 0) {
        u8 *changeBdat = GfDataBdat::getFP(BDAT_MNU_SHOP_CHANGE);
        if (changeBdat == nullptr) {
          return;
        }
        u32 purpose = Bdat::getVal(changeBdat, "LinkQuestTask", unknown20->unknown30).valueU16;
        if (purpose != 0) {
          u32 taskIndex = Bdat::getVal(changeBdat, "LinkQuestTaskID", unknown20->unknown30).valueU16;
          u8 *logBdat = nullptr;
          u32 logId = 0;
          GfQuestInfo::getTaskLog(logBdat, logId, purpose, taskIndex);
          if (logBdat != nullptr && logId != 0) {
            ui::UIObjectAcc(acc.unknown10, "TXT_exc_reward_quest_task").setText(ui::UIStr(logBdat, logId));
          }
          QuestID quest = GfQuestManager::getOrderQuestId(purpose);
          unknown20->unknown548 = QuestTaskParam(quest, taskIndex, purpose, TASK_STATE_UNKNOWN_0);
          isQuest = 1;
          acc.setDispChild(true, "TXT_exc_task_index_quest");
          taskType = 1;
        }
      }
      if (!isQuest) {
        taskType = 0;
        if (unknown20->unknown2c == 0x1aa) {
          acc.setDispChild(true, "TXT_exc_task_index_cook");
          taskType = 2;
        } else if (unknown20->unknown2c == 0x1ab) {
          acc.setDispChild(true, "TXT_exc_task_index_craft");
          taskType = 3;
        } else if (unknown20->unknown2c == 0x1a4) {
          acc.setDispChild(true, "TXT_exc_task_index_quest");
          taskType = 1;
        }
      }
      unknown20->unknown168[24]->unknown10 = 0;
      unknown20->unknown168[24]->unknown14 = 999;
      unknown20->unknown168[25]->unknown10 = 0;
      unknown20->unknown168[25]->unknown14 = 999;
      unknown20->unknown568 = taskType;
      if (unknown20->unknown568 == 0) {
        acc.setDispChild(true, "TXT_exc_task_index");
      }
      unknown20->setupExcItem();
    }
    GfMenuObjOperationInfo::open(0, 0, 0, 0);
    GfMenuObjOperationInfo::setGuideDisp(false);
    unknown20->unknown168[0]->unknown162(unknown20->unknown24);
    unknown20->unknown168[1]->unknown162(GfGameManager::getMapZoneID());
    GfMenuObject::sendOpenEvent(acc.searchChild("LAY_common"), 0, 0.06666667f);
    GfMenuObject::sendOpenEvent(unknown20->getShopSubLayer(acc.unknown10), 0, 0.06666667f);
    ui::UIObjectAcc(acc.unknown10, "LAY_index_normal").setDisp(!isQuest);
    ui::UIObjectAcc(acc.unknown10, "LAY_index_quest").setDisp(isQuest);
    acc.setSuspend(false);
    break;
  }
  case GfMenuTypes::unknown003_34:
    unknown20->sendCloseEvent(acc.searchChild("LAY_common"));
    unknown20->sendCloseEvent(unknown20->getShopSubLayer(acc.unknown10));
    GfMenuObjOperationInfo::close();
    break;
  case 0x41:
    GfMenuReference::setReferenceShopID(0);
    if (unknown20->unknown4e0 != 0) {
      unknown20->addCallContextResult(unknown20->unknown4e0, unknown20->unknown4e4);
    }
    if (unknown20->unknown248.unknown00.empty()) {
      GfMenuObject::termCallContext(acc.unknown10);
      acc.setSuspend(true);
    }
    break;
  case 0x46: {
    u32 isFadeIn = event.unknown08;
    ui::UIObjectAcc layer(acc.searchChild("LAY_char"));
    if (isFadeIn == 0) {
      GfMenuObjUtil::setCommonFadeOut(layer.unknown10, 2, false);
    } else {
      GfMenuObjUtil::setCommonFadeIn(layer.unknown10, 2, false);
    }
    return;
  }
  }
  ui::UIObjectListener::reciveEvent(event, handle);
}

void GfMenuObjShop::CommonListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    acc.setDisp(false);
    GfMenuObject::disableInput(acc.unknown10);
    unknown0c = -1;
    break;
  case 3:
    if (event.unknown08 == 2) {
      unknown20->sendExitEvent(0);
      acc.setDisp(false);
    }
    break;
  case GfMenuTypes::unknown003_33: {
    acc.setDisp(true);
    {
      ui::UIObjectAcc bg(acc.unknown10, "IMG_common_bg");
      bg.startAnimation("fade_in", false);
    }
    acc.setDispChild(true, "LAY_index");
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 0x10000000;
    param.unknown50 = "cmn_fade_motion_up_down";
    param.unknown58 = "fade_in_up";
    param.unknown11 = true;
    param.unknown14 = 8;
    param.unknown04 = 1;
    int ctrl = GfMenuObjUtil::startCtrl(acc.unknown10, param, "LAY_index");
    GfMenuObject::hookCtrlEvent(acc.unknown10, ctrl);
    unknown0c = ctrl;
    break;
  }
  case GfMenuTypes::unknown003_34: {
    {
      ui::UIObjectAcc bg(acc.unknown10, "IMG_common_bg");
      bg.startAnimation("fade_out", false);
    }
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 0x10000000;
    param.unknown50 = "cmn_fade_motion_up_down";
    param.unknown58 = "fade_out_up";
    param.unknown11 = true;
    param.unknown14 = 10;
    param.unknown04 = 2;
    int ctrl = GfMenuObjUtil::startCtrl(acc.unknown10, param, "LAY_index");
    GfMenuObject::hookCtrlEvent(acc.unknown10, ctrl);
    unknown0c = ctrl;
    break;
  }
  }
  ui::UIObjectListener::reciveEvent(event, handle);
}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuSequence<gf::GfMenuObjShop, 8>>(const mm::mtl::Delegate<bool()> *);
