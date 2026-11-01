#include "dr/dr_shd_man.h"

#include "dr/dr_man.h"
#include "dr/dr_shd_data_list.h"
#include "dr/dr_shd_fetch_man.h"
#include "dr/dr_shd_lgt_man.h"
#include "dr/dr_shd_mdo_man.h"
#include "mtl/alloc_handle.h"

namespace ml {

DrShdMan::DrShdMan(DrMan *drMan) : unknown00(nullptr), unknown08(nullptr), unknown10(nullptr), unknown18(nullptr), unknown20(drMan) {
  unknown00 = new (drMan->unknown0c) DrShdDataList(unknown20);
  unknown08 = new (drMan->unknown0c) DrShdMdoMan();
  unknown10 = new (drMan->unknown0c) DrShdFetchMan(unknown20);
  unknown18 = new (drMan->unknown0c) DrShdLgtMan(unknown20);
}

DrShdMan::~DrShdMan() {
  if (unknown00 != nullptr) {
    delete unknown00;
    unknown00 = nullptr;
  }
  if (unknown08 != nullptr) {
    delete unknown08;
    unknown08 = nullptr;
  }
  if (unknown10 != nullptr) {
    delete unknown10;
    unknown10 = nullptr;
  }
  if (unknown18 != nullptr) {
    delete unknown18;
    unknown18 = nullptr;
  }
}

void DrShdMan::beginUpdate() { unknown08->update(); }

void DrShdMan::debugRender() {}

void DrShdMan::beforeUpdateCate(int cate) { unknown18->beforeUpdateCate(cate); }

void DrShdMan::setupCate(int cate) { unknown18->setupCate(cate); }

void DrShdMan::updateCate(int cate) { unknown18->updateCate(cate); }

void DrShdMan::addViewInfo(int cate) { unknown18->addViewInfo(cate); }

void DrShdMan::delViewInfo(int cate) { unknown18->delViewInfo(cate); }

void DrShdMan::resetColorBuff(int index) {
  if (unknown18 != nullptr) {
    unknown18->resetColorBuff(index);
  }
}

} // namespace ml
