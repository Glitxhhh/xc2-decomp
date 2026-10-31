#include "dr/dr_mdo_ctl_cld_mdl.h"

#include "cloud/cloud_man.h"
#include "cloud/cloud_mdl_data_obj.h"
#include "cloud/cloud_obj_man.h"
#include "dr/dr_mdl_base.h"

namespace ml {

DrMdoCtlCldMdl::DrMdoCtlCldMdl(const void *data, DrMan *drMan, int viewNum) : DrMdlObj(viewNum) {
  unknown1c = unknown037_4;
  unknown1a8 = nullptr;
  unknown1b0 = data;
  m_drMan = drMan;
}

DrMdoCtlCldMdl::~DrMdoCtlCldMdl() { releaseCldMdl(); }

void DrMdoCtlCldMdl::releaseCldMdl() {
  if (unknown1a8 != nullptr) {
    cloud::CloudMan::get()->unknown50->releaseMdlData(unknown1a8);
    unknown1a8 = nullptr;
    unknown1b0 = nullptr;
  }
}

void DrMdoCtlCldMdl::resourceInit() {
  if (unknown1a8 == nullptr) {
    unknown1a8 = cloud::CloudMan::get()->unknown50->createMdlData(unknown1b0);
  }
}

void DrMdoCtlCldMdl::update() {
  if (unknown1a8 != nullptr) {
    unknown1a8->setCallDisp(true);
  }
}

void DrMdoCtlCldMdl::dispOffUpdate() {
  if (unknown1a8 != nullptr) {
    unknown1a8->setCallDisp(false);
  }
}

} // namespace ml
