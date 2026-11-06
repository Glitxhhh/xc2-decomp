#include "gf/menu/object/gf_menu_obj_blade_create.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_save.h"
#include "gf/menu/gf_menu_fullscreen.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/gf_menu_model_view.h"
#include "gf/menu/gf_menu_sound_manager.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_blade_name.h"
#include "gf/menu/object/gf_menu_obj_fade.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/request/gf_req_command.h"
#include "gf/request/gf_req_manager.h"
#include "mm_math/mm_vec3.h"
#include "scn/scn_render_dr_sys_parm_acc.h"
#include "ui/list/ui_list_info.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"

namespace gf {
struct GF_OBJ_HANDLE;

// Inferred role: full screen layer id; original name unknown.
constexpr u32 unknown001 = 0x14;

// Inferred role: names of the pages of the creation screen; original name unknown.
const char *const unknown002[6] = {"LAY_dr_select", "LAY_core_select", "LAY_bst_select", "LAY_confirm", "LAY_create", "LAY_result"};

void GfMenuObjBladeCreate::registOpenParam(const OpenParam &param) {
  GfMenuTypes::Param layerParam;
  layerParam.set(param);
  GfMenuFullScreen::registLayerParam(unknown001, layerParam);
}

void GfMenuObjBladeCreate::openCreatedBladeName(GfMenuCallContext *context) { GfMenuObjBladeName::open(context); }

u32 GfMenuObjBladeCreate::getPageObject(u32 handle, u32 page, bool isSibling) {
  u32 object = 0;
  if (handle != 0 && page < 6) {
    ui::UIObjectAcc acc(handle);
    if (isSibling) {
      object = acc.searchSibiling(unknown002[page]);
    } else {
      object = acc.searchChild(unknown002[page]);
    }
  }
  return object;
}

void GfMenuObjBladeCreate::nextPage(u32 handle, PageContext *context, bool isSibling) {
  u32 page = 0;
  switch (context->unknown00) {
  case 0:
    page = 1;
    break;
  case 1:
    page = 2;
    if (context->unknown2c) {
      page = 3;
    }
    break;
  case 2:
    page = 3;
    break;
  case 3:
    page = 4;
    break;
  case 4:
    page = 5;
    break;
  case 5:
    break;
  default:
    if (context->unknown00 != 0xff) {
      return;
    }
    break;
  }
  changePage(handle, context, page, isSibling, false);
}

void GfMenuObjBladeCreate::returnPage(u32 handle, PageContext *context, bool isSibling) {
  u32 page = 0;
  switch (context->unknown00) {
  case 1:
    break;
  case 2:
    page = 1;
    break;
  case 3:
    page = 1;
    if (!context->unknown2c) {
      page = 2;
    }
    break;
  case 4:
    page = 3;
    break;
  default:
    return;
  }
  changePage(handle, context, page, true, true);
}

void GfMenuObjBladeCreate::update() {
  unknownaf8.unknown003();
  if (unknown28.unknownac8 != nullptr) {
    unknown28.unknownac8->update();
  }
  GfMenuObject::update();
}

void GfMenuObjBladeCreate::stopAllSound() {
  for (int i = 0; i < 3; i++) {
    if (unknown11c4[i] != 0) {
      GfMenuObjUtil::stopSE(unknown11c4[i], 0.0f);
    }
  }
}

bool GfMenuObjBladeCreate::seqStart() {
  ml::ScnRenderDrSysParmAcc acc;
  if (!acc.isSeamMapRead()) {
    unknown1120 = false;
    GfMenuSoundManager::fadeOutFieldBgm(0.5f);
    return true;
  }
  return false;
}

bool GfMenuObjBladeCreate::seqWaitLoading() { return !unknown28.unknownac8->isLoading(); }

bool GfMenuObjBladeCreate::seqEnd() {
  enableFSInput(unknown28.unknown00);
  return true;
}

bool GfMenuObjBladeCreate::seqSave() {
  unknown11b0 = GfReqCommand::reqSave(SAVESLOT_DEFAULT);
  GfMenuObjFade::dispSaving(true, 0);
  return true;
}

bool GfMenuObjBladeCreate::seqSaveWait() {
  if (!GfReqManager::isValid(unknown11b0)) {
    GfMenuObjFade::dispSaving(false, 0);
    unknown11b0 = -1;
    return true;
  }
  return false;
}

bool GfMenuObjBladeCreate::seqResultStart() {
  unknown1120 = false;
  unknownaf8.unknown002(&GfMenuObjBladeCreate::seqResultConfirm);
  return true;
}

bool GfMenuObjBladeCreate::seqCreateStartSE() {
  if (unknown11c4[1] != 0) {
    GfMenuObjUtil::stopSE(unknown11c4[1], 0.0f);
    unknown11c4[1] = 0;
  }
  unknown11c4[2] = GfMenuObjUtil::playSE("se_fld_allmap_715");
  return true;
}

bool GfMenuObjBladeCreate::seqCreatePlayJingle() {
  GfMenuObjUtil::stopBGM(unknown11c0, 1.0f);
  unknown11c0 = 0;
  return true;
}

bool GfMenuObjBladeCreate::seqSetupDriverObj() {
  {
    ui::UIObjectAcc main(unknown18, "LAY_main");
    GfMenuObjUtil::CtrlParam param;
    param.unknown08 = 1;
    param.unknown00 = 0.25f;
    GfMenuObjUtil::startCtrl(main.unknown10, param, nullptr);
  }
  changePage(unknown18, &unknown28, 0, false, false);
  unknown28.unknownac8->playEffect(8, "bc_30_000", mm::Vec3(0.0f, 0.0f, 0.0f), reinterpret_cast<GF_OBJ_HANDLE *>(-1));
  unknown11c4[0] = GfMenuObjUtil::playSE("se_fld_allmap_701");
  return true;
}

bool GfMenuObjBladeCreate::seqResultBladeFull() {
  if (!unknown1120) {
    GfMenuManager::openCommonWindow(8);
    unknown1120 = true;
  }
  if (!GfMenuManager::isOpenCommonWindow()) {
    unknownaf8.unknown002(&GfMenuObjBladeCreate::seqResultEnd);
    if (unknown28.unknown38 != nullptr) {
      unknown28.unknown38->release();
      unknown28.unknown38 = nullptr;
    }
    return true;
  }
  return false;
}

bool GfMenuObjBladeCreate::seqCreateWaitEvent() {
  if (*unknown1118) {
    return false;
  }
  if (unknown1118 != nullptr) {
    delete unknown1118;
    unknown1118 = nullptr;
  }
  GfMenuObjBladeName::close();
  nextPage(unknown18, &unknown28, false);
  return true;
}

void GfMenuObjBladeCreate::setGuideText(u32 id) {
  ui::UIObjectAcc acc(unknown18, "TXT_guide");
  {
    u32 name = Bdat::getVal(GfDataBdat::getFP(BDAT_MNU_MSG_OPERATION_GUIDE), "name", id).valueU16;
    ui::UIStr text(GfDataBdat::getFP(BDAT_MENU_OPERATION_GUIDE), name);
    acc.setText(text);
  }
  acc.setDisp(true);
  GfMenuObjUtil::CtrlParam param;
  param.unknown004("fade_in_l");
  param.unknown14 = 8;
  param.unknown11 = true;
  param.unknown00 = 0.2f;
  GfMenuObjUtil::startCtrl(acc.unknown10, param, nullptr);
}

bool GfMenuObjBladeCreate::seqCreatePlayBgmAfter() { return true; }

} // namespace gf
