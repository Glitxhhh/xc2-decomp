#include "gf/menu/object/gf_menu_obj_hana_parts_make.h"

#include "gf/data/gf_data_hana.h"
#include "gf/game/gf_game_util_hana.h"
#include "gf/menu/adapter/gf_menu_hana_adapter.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/util/gf_item_util.h"
#include "mm_math/mm_math.h"

namespace gf {

void GfMenuObjHanaPartsMake::finalize() { GfMenuObject::finalize(); }

void GfMenuObjHanaPartsMake::update() { GfMenuObject::update(); }

u32 GfMenuObjHanaPartsMake::getCrystalItemCount(u32 item) { return GfGameUtilHana::getConvertToEther(item); }

u16 GfMenuObjHanaPartsMake::getFirstSortTableId(u32 type, u32 isEquip) {
  if (isEquip != 0) {
    return GfMenuHanaAdapter::getSortTableId(type);
  }
  return GfMenuHanaAdapter::getMakeSortTableId(type);
}

u32 GfMenuObjHanaPartsMake::getMakeItemCount(u32 parts) {
  ItemProperty property;
  GfItemUtil::getProperty(property, parts, 0);
  u32 needEther = property.unknown68;
  u32 count = GfDataHana::getEther() / needEther;
  return mm::min(GfGameUtilHana::getEmptyParts(parts), count);
}

RESULT_HANA GfMenuObjHanaPartsMake::makeParts(u32 type, u32 parts) {
  switch (type) {
  case 1:
    return GfGameUtilHana::exchangeRoleParts(parts);
  case 2:
    return GfGameUtilHana::exchangeAttributeParts(parts);
  case 3:
    return GfGameUtilHana::exchangeNArtsParts(parts);
  case 6:
    return GfGameUtilHana::exchangeCondenserParts(parts);
  case 9:
    return GfGameUtilHana::exchangeArtsParts(parts);
  }
  return RESULT_HANA_UNKNOWN_6;
}

RESULT_HANA GfMenuObjHanaPartsMake::crystalParts(u32 type, u32 parts) {
  switch (type) {
  case 1:
  case 2:
  case 3:
  case 6:
  case 9:
    return GfGameUtilHana::execConvertToEther(parts);
  }
  return RESULT_HANA_UNKNOWN_8;
}

void GfMenuObjHanaPartsMake::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

int GfMenuObjHanaPartsMake::setFadeIn(u32 handle, u32 unknown) {
  int ctrl = GfMenuObjUtil::setCommonFadeIn(handle, 1, unknown);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

int GfMenuObjHanaPartsMake::setFadeOut(u32 handle, u32 unknown) {
  int ctrl = GfMenuObjUtil::setCommonFadeOut(handle, 2, unknown);
  GfMenuObject::hookCtrlEvent(handle, ctrl);
  return ctrl;
}

} // namespace gf
