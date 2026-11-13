#include "gf/menu/object/gf_menu_obj_world_map.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_map.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_data_util.h"
#include "gf/data/gf_object_type.h"
#include "gf/field/gf_field_gimmick.h"
#include "gf/field/gf_gmk_locator_atlas.h"
#include "gf/game/gf_game_cond.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_world_map_adapter.h"
#include "gf/menu/adapter/gf_menu_zone_map_adapter.h"
#include "gf/menu/gf_menu_location.h"
#include "gf/menu/gf_menu_map_info.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/list/gf_menu_id_list.h"
#include "gf/menu/list/gf_menu_zone_map_list.h"
#include "gf/menu/object/gf_menu_obj_mainmenu2.h"
#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_math/mm_aabb.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_object.h"
#include "ui/event/ui_event_data.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/stream/ui_stream_manager.h"
#include "ui/ui_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Game symbol _ZN2gf20nd_lay_icon_node_tblE.
const char *nd_lay_icon_node_tbl[10] = {
    "LAY_icon_mapjump", "LAY_icon_area", "LAY_icon_collect", "LAY_icon_kizuna", "LAY_icon_salvage", "LAY_icon_shop", "LAY_icon_scenario", "LAY_icon_quest", "LAY_icon_field_skill", "LAY_icon_player"};

GfMenuObjWorldMap::GfMenuObjWorldMap(u32 handle)
    : GfMenuObject(handle), unknown28(nullptr), unknown30(nullptr), unknown38(true), unknown40(nullptr), unknown48(nullptr), unknown50(this), unknown2e0(nullptr), unknown2e8(1.0f),
      unknown2f0(nullptr), unknown2f8(nullptr), unknown318(0), unknown320(nullptr), unknown328(nullptr), unknown330(nullptr), unknown690(false), unknown6b8(nullptr), unknown6c0(), unknown2f10(0),
      unknown2f60(false), unknown2f61(false), unknown2f68(nullptr), unknown2f70(false), unknown2f78(nullptr), unknown2f80(0), unknown2f84(0), unknown2f88(nullptr), unknown2f90(nullptr) {
  unknown300.setAllocator(getAllocator(ALLOCATOR_UNKNOWN_0));
}

void GfMenuObjWorldMap::finalize() {
  if (unknown2fa0.unknown00 > 0) {
    GfFieldGimmick::get()->unknownf4c0.create(unknown2fa0);
  }
  GfMenuObject::finalize();
}

void GfMenuObjWorldMap::update() {
  unknown50.unknown003();
  GfMenuLocation::updateLocator();
  GfFieldGimmick::get()->unknownf4c0.update(0.0f);
  GfMenuObject::update();
}

void GfMenuObjWorldMap::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    setFadeIn(handle);
    break;
  case 2:
    unknown20->deleteMapImage();
    setFadeOut(handle, true);
    break;
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObjMainMenu2::setCloseKeyEnable(true);
    }
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

int GfMenuObjWorldMap::setFadeIn(u32 handle) {
  int ctrl = GfMenuObjUtil::unknown002(handle);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

void GfMenuObjWorldMap::deleteMapImage() {
  if (unknown690 && unknown694.length() != 0) {
    ui::UIObjectAcc acc(unknown18);
    ui::UIStreamManager::get()->deleteImage(unknown694, acc.searchChild("LAY_floor"));
    unknown690 = false;
    unknown694.clear();
  }
}

int GfMenuObjWorldMap::setFadeOut(u32 handle, bool unknown) {
  int ctrl = setFadeOutSub(handle, unknown);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

void GfMenuObjWorldMap::WorldListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    GfMenuObjOperationInfo::setGuideText(2, 0);
    setFadeIn(handle);
    break;
  case 2:
    setFadeOut(handle, true);
    break;
  case 3:
    if (event.unknown08 == 1) {
      GfMenuObject::enableFSInput(0);
    } else if (event.unknown08 == 2) {
      acc.setDisp(false);
      acc.setTerm();
    }
    break;
  case GfMenuTypes::unknown003_33:
    acc.setDisp(true);
    break;
  case GfMenuTypes::unknown003_34:
    if (!unknown20->unknown38) {
      sendEvent(handle, 3, 2, 0);
    } else {
      setFadeOut(handle, event.unknown08 == 1);
    }
    GfMenuObject::disableInput(acc.searchChild("LAY_worldmap"));
    GfMenuObject::disableInput(acc.searchChild("LAY_map_sellect"));
    break;
  case 0x24:
    GfMenuObject::disableInput(acc.searchChild("LAY_worldmap"));
    GfMenuObject::disableInput(acc.searchChild("LAY_map_sellect"));
    setFadeOutSub(handle, false);
    unknown20->unknown38 = false;
    break;
  case GfMenuTypes::unknown003_258:
    sendEvent(acc.searchChild("LAY_worldmap"), GfMenuTypes::unknown003_259, 0, 0);
    sendEvent(acc.searchChild("LAY_map_sellect"), GfMenuTypes::unknown003_259, 0, 0);
    break;
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjWorldMap::sendEvent(u32 handle, u32 type, u32 param, u32 delay) {
  ui::EventData event;
  event.unknown0c = 0;
  event.unknown00 = type;
  event.unknown08 = param;
  ui::UIManager::get()->requestObjectEvent(handle, event, delay * (1.0f / 30.0f));
}

int GfMenuObjWorldMap::setFadeOutSub(u32 handle, bool unknown) {
  GfMenuObjUtil::PresetCtrlParam param;
  param.unknown04 = 1;
  param.unknown00 = 6;
  param.unknown10 = 2;
  if (unknown) {
    param.unknown0c = true;
  }
  return GfMenuObjUtil::startPresetCtrl(handle, param);
}

// Inferred role: world maps the list may show; original name unknown.
static const u32 unknown001[15] = {3, 4, 5, 6, 9, 10, 11, 12, 13, 14, 15, 16, 18, 20, 21};

void GfMenuObjWorldMap::WorldMapListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc owner(unknown20->unknown18);
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
    setupMapList(unknown20->unknown28);
    setupWorldMap(acc, unknown20->unknown28, unknown20->unknown30);
    break;
  case GfMenuTypes::unknown003_257: {
    u32 map = event.unknown08;
    for (u32 i = 0; i < 15; i++) {
      mm::mtl::FixStr<32> name;
      name.format("IMG_objgrow@%02d", i + 1);
      {
        ui::UIObjectAcc grow(acc.unknown10, name.c_str());
        if (!grow.isValid()) {
          continue;
        }
        grow.setDisp(map == unknown001[i]);
      }
      name.format("LAY_map_obj@%02d", i + 1);
      {
        ui::UIObjectAcc object(acc.unknown10, name.c_str());
        if (!object.isValid()) {
          continue;
        }
        object.setDispPriority(map == unknown001[i] ? 9 : 8);
      }
      name.format("LAY_devinfo@%02d", i + 1);
      u32 devinfo = acc.searchChild(name.c_str());
      if (devinfo != 0) {
        if (map != 12 || GfDataUtil::getScenarioFlag() < 8037) {
          ui::UIObjectAcc(devinfo).setDisp(map == unknown001[i]);
        }
      }
    }
    break;
  }
  case GfMenuTypes::unknown003_259: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 1;
    param.unknown00 = 0.3f;
    param.unknown04 = 1;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    break;
  }
  case GfMenuTypes::unknown003_260: {
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 2;
    param.unknown00 = 0.3f;
    param.unknown04 = 2;
    GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

void GfMenuObjWorldMap::setupMapList(GfMenuIDList *list) {
  list->clear();
  for (u32 i = 0; i < 15; i++) {
    u32 map = unknown001[i];
    if (chkMapCond(map, nullptr)) {
      MenuID id = {map};
      list->addContents(id);
    }
  }
}

void GfMenuObjWorldMap::setupWorldMap(ui::UIObjectAcc &acc, GfMenuIDList *list, ui::UISelectObjList *) {
  mm::mtl::FixStr<32> name;
  u32 count = Bdat::getIdCount(GfDataBdat::getFP(BDAT_MNU_WORLD_MAP_COND));
  for (u32 i = 0; i < count; i++) {
    name.format("LAY_map_obj@%02d", i + 1);
    GfMenuObjUtil::setChildDisp(acc.unknown10, name.c_str(), false);
  }
  for (u32 i = 0; i < list->getSize(); i++) {
    u32 node = searchNodeId(list->getContents(i).unknown00);
    if (node != 0xffff) {
      name.format("LAY_map_obj@%02d", node + 1);
      u32 object = acc.searchChild(name.c_str());
      if (object != 0) {
        ui::UIObjectAcc map(object);
        setMapPos(map, list->getContents(i).unknown00);
        name.format("LAY_devinfo@%02d", node + 1);
        ui::UIObjectAcc(acc.searchChild(name.c_str())).setIgnoreSize(true);
        name.format("IMG_objstay@%02d", node + 1);
        GfMenuWorldMapAdapter::createFromList(acc.searchChild(name.c_str()), 3, list, i, false, false);
        ui::UIObjectAcc stay(acc.searchChild(name.c_str()));
        stay.startAnimation("loop", false);
        name.format("IMG_devgauge@%02d", node + 1);
        ui::UIObjectAcc gauge(acc.searchChild(name.c_str()));
        if (gauge.isValid()) {
          GfMenuWorldMapAdapter::createFromList(acc.searchChild(name.c_str()), 2, list, i, false, false);
        }
      }
    }
  }
}

void GfMenuObjWorldMap::setupMapSelect(ui::UIObjectAcc &acc, GfMenuIDList *list) {
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < 9; i++) {
    name.format("TXT_areaname@%02d", i + 1);
    GfMenuWorldMapAdapter *adapter = GfMenuWorldMapAdapter::createFromList(acc.searchChild(name.c_str()), 0, list, i, true, false);
    if (adapter != nullptr) {
      name.format("LAY_area_tag@%02d", i + 1);
      adapter->unknown24 = acc.searchChild(name.c_str());
    }
    name.format("IMG_stayicon@%02d", i + 1);
    GfMenuWorldMapAdapter::createFromList(acc.searchChild(name.c_str()), 3, list, i, true, false);
  }
  GfMenuWorldMapAdapter::createFromList(acc.searchChild("TXT_areaname_select"), 0, list, -1, true, false);
  GfMenuWorldMapAdapter::createFromList(acc.searchChild("IMG_stayicon_select"), 3, list, -1, true, false);
  acc.setDispChild(false, "LAY_area_tag_select");
  GfMenuObjUtil::createVScrollBarPlugin(acc.searchChild("IMG_area_scroll_bar"), list, "IMG_area_scroll_bar_base", true);
}

void GfMenuObjWorldMap::refreshMapSelect(ui::UIObjectAcc &, GfMenuIDList *, ui::UISelectObjList *objects, int index) {
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < objects->getSize(); i++) {
    name.format("IMG_tagbg@%02d", i + 1);
    ui::UIObjectAcc bg(objects->getObject(i), name.c_str());
    if (index == i) {
      bg.startAnimation("select", false);
    } else {
      bg.startAnimation("normal", false);
    }
  }
  if (index != -1) {
    objects->setIndex(index);
  }
}

bool GfMenuObjWorldMap::isEnterMap(u32 map) {
  u8 *bdat = GfDataBdat::getFP(BDAT_MNU_WORLD_MAP_COND);
  int top = Bdat::getIdTop(bdat);
  for (u32 i = 0; i < Bdat::getIdCount(bdat); i++) {
    if (Bdat::getVal(bdat, "mapId", top + i).valueU16 == map) {
      u16 enter = Bdat::getVal(bdat, "enter", top + i).valueU16;
      if (enter == 0 || GfGameCond::isGameCond(enter)) {
        return true;
      }
    }
  }
  return false;
}

void GfMenuObjWorldMap::ctrlScrollBar(u32 handle, bool unknown) {
  GfMenuObjUtil::CtrlParam param;
  param.unknown08 = unknown ? 2 : 1;
  param.unknown00 = 0.3f;
  param.unknown0c = 1;
  GfMenuObjUtil::startCtrl(handle, param, nullptr);
}

void GfMenuObjWorldMap::setupZoneSelect(ui::UIObjectAcc &acc, GfMenuZoneMapList *list) {
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < 9; i++) {
    name.format("TXT_zonename_@%02d", i + 1);
    GfMenuZoneMapAdapter *adapter = GfMenuZoneMapAdapter::createFromList(acc.searchChild(name.c_str()), 0, list, i, true, false);
    name.format("LAY_zonespot@%02d", i + 1);
    if (adapter != nullptr) {
      adapter->unknown24 = acc.searchChild(name.c_str());
    }
    name.format("IMG_sonestay_@%02d", i + 1);
    GfMenuObjUtil::setChildDisp(acc.unknown10, name.c_str(), false);
  }
  GfMenuObjUtil::createVScrollBarPlugin(acc.searchChild("IMG_zone_scroll_bar"), list, "IMG_zone_scroll_bar_base", true);
}

void GfMenuObjWorldMap::refreshZoneSelect(ui::UIObjectAcc &, GfMenuZoneMapList *, ui::UISelectObjList *objects, int index) {
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < objects->getSize(); i++) {
    name.format("IMG_zone_base_@%02d", i + 1);
    ui::UIObjectAcc base(objects->getObject(i), name.c_str());
    name.format("TXT_zonename_@%02d", i + 1);
    ui::UIObjectAcc text(objects->getObject(i), name.c_str());
    if (index == i) {
      base.startAnimation("select", false);
      GfMenuObjUtil::setColMulandAdd(text.unknown10, "txt_normal2");
    } else {
      base.startAnimation("normal", false);
      GfMenuObjUtil::setColDefault(text.unknown10);
    }
  }
  if (index != -1) {
    objects->setIndex(index);
  }
}

int GfMenuObjWorldMap::ctrlGroupReturn(ui::UISelectObjList *objects, u32 count) {
  int ctrl = -1;
  for (u32 i = 0; i < objects->getSize() && i < count; i++) {
    ui::UIObjectAcc acc(objects->getObject(i));
    if (i == objects->getIndex(false)) {
      if (i != 0) {
        GfMenuObjUtil::CtrlParam param;
        param.unknown08 = 0x80000000;
        param.unknown00 = 0.3f;
        param.unknown04 = 1;
        param.unknown18 = GfMenuObjUtil::getCtrlID(acc.unknown10);
        param.unknown0c = 1;
        ctrl = GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
      }
    } else {
      acc.setDisp(true);
      GfMenuObjUtil::CtrlParam param;
      param.unknown004("fade_in_l");
      param.unknown00 = 0.3f;
      param.unknown04 = 1;
      param.unknown14 = 8;
      ctrl = GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
    }
    acc.setDispPriority(8);
  }
  return ctrl;
}

void GfMenuObjWorldMap::setupPointSelect(ui::UIObjectAcc &acc, GfMenuZoneMapList *list) {
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < 9; i++) {
    name.format("TXT_pointname_@%02d", i + 1);
    GfMenuZoneMapAdapter *adapter = GfMenuZoneMapAdapter::createFromList(acc.searchChild(name.c_str()), 1, list, i, true, false);
    name.format("LAY_pointspot@%02d", i + 1);
    if (adapter != nullptr) {
      adapter->unknown24 = acc.searchChild(name.c_str());
    }
  }
  GfMenuObjUtil::createVScrollBarPlugin(acc.searchChild("IMG_point_scroll_bar"), list, "IMG_point_scroll_bar_base", true);
}

void GfMenuObjWorldMap::loadTex() {
  if (unknown2f80 != getFloor()) {
    unknown2f80 = getFloor();
    unknown50.unknown005();
    unknown50.unknown002(&GfMenuObjWorldMap::seqTexDelete);
    unknown50.unknown002(&GfMenuObjWorldMap::seqTexDeleteWait);
    unknown50.unknown002(&GfMenuObjWorldMap::seqTexLoad);
    unknown50.unknown002(&GfMenuObjWorldMap::seqTexLoadWait);
    unknown50.unknown002(&GfMenuObjWorldMap::seqTexDraw);
    unknown50.unknown002(&GfMenuObjWorldMap::seqGimik);
    unknown50.unknown002(&GfMenuObjWorldMap::seqNext);
  }
}

bool GfMenuObjWorldMap::isEnableJump(const MenuZoneMapInfo &info) {
  u32 worldMap = GfMenuReference::getReferenceWorldMapID();
  u8 *bdat = GfDataBdat::getFP(BDAT_FLD_MAPLIST);
  u32 allOffCondition = Bdat::getVal(bdat, "st_allOFF_cndID", worldMap).valueU16;
  u32 offCondition = Bdat::getVal(bdat, "st_OFF_cndID", worldMap).valueU16;
  if (allOffCondition != 0 && GfGameCond::isGameCondWithMap(allOffCondition, worldMap)) {
    return false;
  }
  if (offCondition != 0 && GfGameCond::isGameCondWithMap(offCondition, worldMap)) {
    return false;
  }
  if (info.unknown08 != 0 && GfGameCond::isGameCondWithMap(info.unknown08, worldMap)) {
    return false;
  }
  return true;
}

void GfMenuObjWorldMap::clearTex() {
  unknown50.unknown005();
  unknown50.unknown002(&GfMenuObjWorldMap::seqTexDelete);
  unknown50.unknown002(&GfMenuObjWorldMap::seqTexDeleteWait);
}

void GfMenuObjWorldMap::refreshPointText(ui::UIObjectAcc &acc, GfMenuZoneMapList *list, ui::UISelectObjList *objects) {
  mm::mtl::FixStr<32> name;
  for (u32 i = 0; i < objects->getSize(); i++) {
    list->getContents(list->getPageIndex(i));
    name.format("TXT_pointname_@%02d", i + 1);
    ui::UIObjectAcc text(acc.unknown10, name.c_str());
    if (isEnableJump(list->getContents(list->getPageIndex(i)))) {
      GfMenuObjUtil::setColMulandAdd(text.unknown10, "txt_normal2");
    } else {
      GfMenuObjUtil::setColMulandAdd(text.unknown10, "txt_disable");
    }
  }
}

int GfMenuObjWorldMap::getTotalFieldSkillLv(u32 skill) {
  int total = 0;
  for (u16 blade : unknown338) {
    DataParamAcc acc(OBJECT_TYPE_BLADE, blade, GIMMICK_TYPE_UNKNOWN_0);
    for (u32 i = 0; i < 3; i++) {
      if (acc.getFieldSkill(i, false) == skill) {
        total += acc.getFieldSkillLevel(i, false);
        break;
      }
    }
  }
  return total;
}

void GfMenuObjWorldMap::refreshIconFilter() {
  if (unknown2f88 != nullptr) {
    ui::UIObjectAcc filter(unknown18, "LAY_icon_filter");
    mm::mtl::FixStr<32> name;
    for (u32 i = 0; i < 9 && i < unknown2f88->getSize(); i++) {
      bool isOn = (unknown2f84 & (1 << i)) != 0;
      name.format("IMG_icon_filter_on@%02d", i + 1);
      filter.setDispChild(isOn, name.c_str());
      name.format("IMG_icon_filter_off@%02d", i + 1);
      filter.setDispChild(!isOn, name.c_str());
    }
  }
}

void GfMenuObjWorldMap::updateDispIconNode() {
  ui::UIObjectAcc zoneMap(unknown18, "LAY_zonemap");
  for (u32 i = 0; i < 9; i++) {
    bool isDisp = (unknown2f84 & (1 << i)) != 0;
    ui::UIObjectAcc icon(zoneMap.searchChild(nd_lay_icon_node_tbl[i]));
    icon.setDisp(isDisp);
  }
}

u32 GfMenuObjWorldMap::searchNodeId(u32 map) {
  for (u32 i = 0; i < 15; i++) {
    if (unknown001[i] == map) {
      return i;
    }
  }
  return 0xffff;
}

void GfMenuObjWorldMap::setMapPos(ui::UIObjectAcc &acc, u32 map) {
  mm::Pnt<s16> pos;
  if (chkMapCond(map, &pos)) {
    if (map != 20) {
      acc.setPosCenter(pos);
    }
    acc.setDisp(true);
  }
}

bool GfMenuObjWorldMap::isDispMap(u32 map) { return chkMapCond(map, nullptr); }

bool GfMenuObjWorldMap::chkMapCond(u32 map, mm::Pnt<s16> *pos) {
  u8 *cond = GfDataBdat::getFP(BDAT_MNU_WORLD_MAP_COND);
  u8 *worldMap = GfDataBdat::getFP(BDAT_MNU_WORLD_MAP);
  int top = Bdat::getIdTop(cond);
  for (u32 i = 0; i < Bdat::getIdCount(cond); i++) {
    if (Bdat::getVal(cond, "mapId", top + i).valueU16 == map) {
      mm::mtl::FixStr<32> name;
      for (u32 j = 0; j < 3; j++) {
        u32 number = j + 1;
        name.format("cond%d", number);
        if (GfGameCond::isGameCond(Bdat::getVal(cond, name.c_str(), top + i).valueU16)) {
          if (pos != nullptr) {
            name.format("pos%d", number);
            u16 row = Bdat::getVal(cond, name.c_str(), top + i).valueU16;
            pos->x = Bdat::getVal(worldMap, "posX", row).valueS16;
            pos->y = Bdat::getVal(worldMap, "posY", row).valueS16;
          }
          return true;
        }
      }
    }
  }
  return false;
}

bool GfMenuObjWorldMap::seqTexDelete() {
  ui::UIObjectAcc main(ui::UIObjectAcc(unknown18).searchChild("LAY_main"));
  if (unknown690) {
    GfMenuObjUtil::setChildDisp(main.unknown10, unknown694.c_str(), false);
    unknown6b8->clear();
    closeIconTable(main, unknown6c0);
    unknown300.fill(MapJumpInfo());
    GfFieldGimmick::get()->unknownf4c0.dispose();
    mm::mtl::safeRelease(unknown2e0);
    deleteMapImage();
  }
  ui::UIObjectAcc(main.searchChild("LAY_floor")).setDisp(false);
  return true;
}

bool GfMenuObjWorldMap::seqTexDeleteWait() { return true; }

bool GfMenuObjWorldMap::seqTexLoadWait() {
  ui::UIObjectAcc main(ui::UIObjectAcc(unknown18).searchChild("LAY_main"));
  ui::UIObjectAcc floor(main.searchChild("LAY_floor"));
  return !floor.isStreaming();
}

void GfMenuObjWorldMap::closeIconTable(ui::UIObjectAcc &, mm::mtl::FixedArray<mm::mtl::FixedVector<u32, 256>, 10> &icons) {
  for (mm::mtl::FixedVector<u32, 256> *node = icons.begin(); node != icons.end(); ++node) {
    for (u32 *it = node->begin(); it != node->end(); ++it) {
      ui::UIObjectAcc icon(*it);
      if (icon.isValid() && !icon.isTerm()) {
        icon.setTerm();
      }
    }
    node->clear();
  }
}

void GfMenuObjWorldMap::getFloorAABB(u32 map, u32 floor, mm::Aabb &aabb, mm::Pnt<s16> &center) {
  int index = GfMenuMapInfo::getMapInfoIndex(GfDataMap::getMapResourceNameByMapID(map));
  if (index != -1) {
    GfMenuMapInfo::MapAreaInfo area;
    if (GfMenuMapInfo::getMapAreaFromName(index, Bdat::getVal(GfDataBdat::getFP(BDAT_MNU_MAP_INFO), "level_name", floor).valueString, area)) {
      mm::Vec3 min;
      min.x = area.unknown20;
      min.y = area.unknown24;
      min.z = area.unknown28;
      mm::Vec3 max;
      max.x = area.unknown2c;
      max.y = area.unknown30;
      max.z = area.unknown34;
      aabb.set(min, max);
      center.x = static_cast<s16>((min.x + max.x) * 0.5f);
      center.y = static_cast<s16>((min.z + max.z) * 0.5f);
    }
  }
}

const char *GfMenuObjWorldMap::getIconNodeName(u32 type) { return nd_lay_icon_node_tbl[type]; }

bool GfMenuObjWorldMap::chkFloor(u32, u32) { return true; }

void GfMenuObjWorldMap::setupZoneMap(ui::UIObjectAcc &, GfMenuZoneMapList *, ui::UISelectObjList *, bool) {}

} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjWorldMap>(const mm::mtl::Delegate<bool()> *);
