#include "gf/game/item/gf_pouch_util.h"

#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_item_id.h"
#include "gf/event/gf_event.h"
#include "gf/game/item/gf_item_box.h"

namespace gf {

bool GfPouchUtil::isExistOpenItem() { return GfItemBox::get()->countItem(ITEM_UNKNOWN_62D9) != 0; }

void GfPouchUtil::setTimeUpForDebug(u32 driver, u32 slot) {
  SDataPouch pouch = *GfDataDriver::getPouchData(driver, slot);
  if (pouch.unknown00 > 0.0f) {
    pouch.unknown00 = 0.0f;
    setPouch(driver, slot, pouch);
  }
}

void GfPouchUtil::execOpen(u32 driver) {
  if (GfItemBox::get()->countItem(ITEM_UNKNOWN_62D9) != 0) {
    SDataPouch pouch = *GfDataDriver::getPouchData(driver, 0);
    u32 slot = 0;
    if (pouch._06 != 0) {
      slot = 1;
      pouch = *GfDataDriver::getPouchData(driver, 1);
      if (pouch._06 != 0) {
        slot = 2;
        pouch = *GfDataDriver::getPouchData(driver, 2);
        if (pouch._06 != 0) {
          return;
        }
      }
    }
    pouch._06 = 1;
    GfDataDriver::setPouchData(driver, slot, pouch);
    if (GfItemBox::decItem(ITEM_UNKNOWN_62D9, 1)) {
      GfEvent::callItemAdd(ITEM_UNKNOWN_62D9, -1);
    }
  }
}

} // namespace gf
