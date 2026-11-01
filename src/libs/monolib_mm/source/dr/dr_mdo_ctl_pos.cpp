#include "dr/dr_mdo_ctl_pos.h"

#include "dr/dr_calc_cp_plane_obj.h"
#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_man.h"
#include "dr/dr_mdl_man.h"
#include "dr/dr_res_mdo_inst_mdl_info.h"

namespace ml {

DrMdoCtlPos::~DrMdoCtlPos() { releasePos(); }

void DrMdoCtlPos::update() {
  updateAlphaCall();
  updatePos();
  DrMdlMan *mdlMan = m_drMan->unknown88;
  if (unknownf8 & unknown028_15) {
    mdlMan->unknown230->unknown00 = true;
  }
  if (unknownf8 & unknown028_16) {
    mdlMan->unknown230->unknown01 = true;
  }
  if (unknownf8 & unknown028_17) {
    mdlMan->unknown230->unknown02 = true;
  }
  if (unknownf8 & unknown028_18) {
    mdlMan->unknown230->unknown07 = true;
  }
  if (unknownf8 & unknown028_3) {
    mdlMan->unknown230->unknown03 = true;
  }
  if (unknownf8 & unknown028_2) {
    mdlMan->unknown230->unknown04 = true;
  }
  if (unknownf8 & unknown028_8) {
    mdlMan->unknown230->unknown08 = true;
  }
  if (unknownf8 & unknown028_9) {
    mdlMan->unknown230->unknown09 = true;
  }
}

void DrMdoCtlPos::setDeleteCall(int deleteCall) {
  unknown20 |= unknown038_3 << deleteCall;
  if (unknown258 != nullptr) {
    unknown258->releaseCall();
  }
  if (unknown358 != nullptr) {
    unknown358->release();
    unknown358 = nullptr;
  }
}

void DrMdoCtlPos::callShadowCacheUpdate(u64 flags) {
  unknown368 &= ~flags;
  if (unknown370 & flags) {
    unknown370 = 0;
    unknown378 = 0;
  }
}

void DrMdoCtlPos::updatePos() {
  updateMdl();
  createMdlList();
}

void DrMdoCtlPos::dispOffUpdate() {
  if (unknown258 != nullptr) {
    DrResMdlInstMdlArg arg;
    unknown348 = m_drMan->unknown580->unknown10;
    arg.unknown00 = &unknown348->unknown400;
    arg.unknown10 = false;
    arg.unknown14 = unknown1a;
    arg.unknown08 = nullptr;
    arg.unknown18 = unknowndc;
    unknown258->update(arg);
  }
}

void DrMdoCtlPos::createRenderDisplayList(const MdsMdlInfoHeader *, int, _MdoInstanceWork *, grlib::CGLibVtxInstans *, int) {}

void DrMdoCtlPos::createThicknessRenderFirstDisplayList() { createThicknessRenderDisplayListSub(true); }

void DrMdoCtlPos::createThicknessRenderSecondDisplayList() { createThicknessRenderDisplayListSub(false); }

void DrMdoCtlPos::callZpreePassRenderPosAll() {
  if ((unknownf8 & unknown028_20) == 0) {
    return;
  }
  createZBuffRenderDisplayList();
}

void DrMdoCtlPos::callThicknessRenderFirstPosAll() {
  if ((unknownf8 & unknown028_6) == 0) {
    return;
  }
  createThicknessRenderDisplayListSub(true);
}

void DrMdoCtlPos::callThicknessRenderSecondPosAll() {
  if ((unknownf8 & unknown028_6) == 0) {
    return;
  }
  createThicknessRenderDisplayListSub(false);
}

void DrMdoCtlPos::callGBuffRenderPosAll() {
  if ((unknownf8 & unknown028_1) == 0) {
    return;
  }
  unknownf4 = 1;
  unknownf2 = 7;
  beginSetup();
  callPosRender(8);
}

void DrMdoCtlPos::callRenderPosAll() {
  if ((unknownf8 & unknown028_0) == 0) {
    return;
  }
  unknownf4 = 0;
  unknownf2 = 0;
  beginSetup();
  callPosRender(1);
}

void DrMdoCtlPos::callRefractionRenderPosAll() {
  if ((unknownf8 & unknown028_2) == 0) {
    return;
  }
  unknownf4 = 2;
  unknownf2 = 8;
  beginSetup();
  callPosRender(4);
}

void DrMdoCtlPos::callLightPrePassRenderPosAll() {
  if ((unknownf8 & unknown028_3) == 0) {
    return;
  }
  unknownf4 = 3;
  unknownf2 = 4;
  beginSetup();
  callPosRender(0x20);
}

void DrMdoCtlPos::callAlphaRenderPosAll() {
  if ((unknownf8 & unknown028_4) == 0) {
    return;
  }
  unknownf4 = 4;
  unknownf2 = 1;
  beginSetup();
  callPosRender(2);
}

void DrMdoCtlPos::callSpAlphaRenderPosAll() {
  if ((unknownf8 & unknown028_5) == 0) {
    return;
  }
  unknownf4 = 5;
  unknownf2 = 1;
  beginSetup();
  callPosRender(0x40);
}

void DrMdoCtlPos::callDisplistRender(int param) {}

void DrMdoCtlPos::callDisplistPrePsssRender(int param) {}

} // namespace ml
