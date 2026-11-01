#include "gf/field/gf_field_tbox.h"

#include <math.h>
#include <string.h>

#include "bdat.h"
#include "framework/reference_frame.h"
#include "framework/sound/sound_manager.h"
#include "fw/fw_update_info.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_field_skill.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/component/gimmick/gf_com_behavior_gmk.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_salvage.h"
#include "gmk/gmk_tbox.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_ptr.h"

namespace fw {
enum SoundCategory : int;
} // namespace fw

namespace gf {

GfFieldTbox::GfFieldTbox(const GfSetupParam &param)
    : unknown08(0.0f), unknown0c(0.0f), unknown10(false), unknown11(false), unknown12(false), unknown18(INVALID_HANDLE), unknown20(-1), unknown24(false), unknown28(nullptr), unknown38(0.0f),
      unknown40() {
  create(param);
}

void GfFieldTbox::create(const GfSetupParam &) { unknown10 = true; }

GfFieldTbox::~GfFieldTbox() {}

bool GfFieldTbox::isDropitemsEmitted() const { return unknown40.m_dropitemsEmitted; }

void GfFieldTbox::gevMapjump(GEV event, const MapjumpCallbackInfo &) {
  if (event == GEV_MAPJUMP_START) {
    end();
  }
}

void GfFieldTbox::end() {
  unknown38 = 0.0f;
  unknown40.dispose();
  unknown20 = -1;
  unknown24 = false;
  unknown28 = nullptr;
  unknown18 = INVALID_HANDLE;
}

void GfFieldTbox::createDropitemEmitter(const GfDropitemEmitter::CreateInfo &info) { unknown40.create(info); }

void GfFieldTbox::update(f32 deltaTime) {
  if (unknown28) {
    (this->*unknown28)(deltaTime);
  }
  unknown40.update(deltaTime);
}

void GfFieldTbox::build(const GfSetupParam &param) { new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfFieldTbox(param); }

void GfFieldTbox::update(const fw::UpdateInfo &info) {
  if (get() != nullptr && get()->unknown10) {
    get()->update(info.unknown04);
  }
}

void GfFieldTbox::seqWaitUIEnd(f32) {
  if (GfMenuFieldSkill::isRunning()) {
    return;
  }
  unknown11 = true;
  unknown001(2, 0.0f);
  unknown28 = unknown12 ? &GfFieldTbox::seqWaitOpenFieldTbox : nullptr;
  unknown38 = 0.0f;
}

void GfFieldTbox::seqWaitOpenFieldTbox(f32 deltaTime) {
  gmk::AGmkBase *gmk = gmk::getBindedGmkInst(unknown18);
  if (gmk == nullptr) {
    end();
    return;
  }
  unknown38 += deltaTime;
  if (unknown38 < unknown0c) {
    return;
  }
  unknown38 = 0.0f;
  GfObjAcc acc(unknown18);
  GfComAsm *comAsm = acc.getObj()->getComponent<GfComAsm>();
  if (comAsm != nullptr) {
    comAsm->execCmd(unknown24 ? "C_excavation" : "C_open", ANIM_LAYER_BASE);
    fw::SoundManager::get()->playSe("se006", nullptr, 1.0f, static_cast<fw::SoundCategory>(0));
    if (unknown24) {
      GfObjAcc tboxAcc(unknown18);
      tboxAcc.setAlphaNormal(1.0f);
      GfComBehaviorGmk *behavior = tboxAcc.getObj()->getComponent<GfComBehaviorGmk>();
      if (behavior != nullptr) {
        behavior->setActivateCollison(true);
      }
    }
  }
  GfComBehaviorGmk *behavior = acc.getObj()->getComponent<GfComBehaviorGmk>();
  if (behavior != nullptr) {
    behavior->disposeMenuObj();
  }
  if (!unknown24) {
    GfDropitemEmitter::CreateInfo info;
    GfObjAcc tboxAcc(unknown18);
    info.unknown00 = tboxAcc.getObj()->getComponent<GfComTransform>()->getPosition();
    const mm::Mat44 &matrix = tboxAcc.getObj()->getComponent<GfComTransform>()->unknown001()->getSyncedWorldMatrix();
    info.unknown10 = atan2f(matrix.rows[2][0], matrix.rows[2][2]);
    gmk::GmkType type = gmk->getGmkType();
    if (type == gmk::GMK_TYPE_TBOX) {
      gmk::GmkTbox *tbox = static_cast<gmk::GmkTbox *>(gmk);
      if (tbox->getData()->unknown00 == 1) {
        info.unknown14 = 3.1415927f;
      } else if (tbox->getData()->unknown00 == 2) {
        info.unknown14 = 1.5707964f;
      }
      info.unknown28 = tbox->getBindedBdatFp();
      info.unknown30 = tbox->unknown20.unknown18;
      if (tbox->getBdatInfo()->unknown05) {
        tbox->unknown58 = 0.0f;
        tbox->unknown54 = 5.0f;
      }
    } else if (type == gmk::GMK_TYPE_SALVAGE_LOCATOR) {
      gmk::GmkSalvageLocator *locator = static_cast<gmk::GmkSalvageLocator *>(gmk);
      info.unknown14 = 1.5707964f;
      info.unknown28 = GfDataBdat::getFP(BDAT_FLD_SALVAGE_ITEM_SET);
      info.unknown30 = locator->unknowne8;
      locator->reqDisposeTboxGobInst(5.0f);
    }
    u8 *bdat = GfDataBdat::getFP(BDAT_RSC_TBOX_LIST);
    info.unknown00.y += gmk::toBdatF32(Bdat::getValCheck(bdat, "baseHeight", unknown20, gmk::BDAT_TYPE_F32));
    info.unknown18 += gmk::toBdatF32(Bdat::getValCheck(bdat, "box_distance", unknown20, gmk::BDAT_TYPE_F32));
    info.unknown20 = gmk::toBdatF32(Bdat::getValCheck(bdat, "initWaitTime", unknown20, gmk::BDAT_TYPE_F32));
    info.unknown24 = gmk::toBdatF32(Bdat::getValCheck(bdat, "initWaitTimeRand", unknown20, gmk::BDAT_TYPE_F32));
    unknown40.create(info);
    gmk::AGmkBase *tbox = gmk::getBindedGmkInst(unknown18);
    if (tbox != nullptr) {
      gmk::GmkType type = tbox->getGmkType();
      u32 gimmick = tbox->unknown20.unknown18;
      if (GfQuestUtil::getGimmickTaskEndCheck(type, gimmick) == 0) {
        SCOM_QUEST_GIMMICK::createTresure(gimmick, info.unknown20);
      }
    }
  }
  unknown28 = unknown24 ? &GfFieldTbox::seqWaitDigEnd : &GfFieldTbox::seqWaitDropBegin;
}

void GfFieldTbox::seqWaitDigEnd(f32) {
  GfObjAcc acc(unknown18);
  GfObj *obj = acc.getObj();
  if (obj != nullptr) {
    GfComAsm *comAsm = obj->getComponent<GfComAsm>();
    if (comAsm != nullptr) {
      const char *state = comAsm->getStateName(ANIM_LAYER_BASE);
      if (state != nullptr && strcmp(state, "S_open_00") != 0) {
        return;
      }
    }
    gmk::GmkTbox *tbox = static_cast<gmk::GmkTbox *>(gmk::getBindedGmkInst(unknown18));
    if (tbox != nullptr) {
      tbox->setTargetable(true);
      GfObjAcc tboxAcc(unknown18);
      GfComBehaviorGmk *behavior = tboxAcc.getObj()->getComponent<GfComBehaviorGmk>();
      if (behavior != nullptr) {
        behavior->createMenuObj();
      }
      unknown28 = nullptr;
      return;
    }
  }
  end();
}

void GfFieldTbox::seqWaitDropBegin(f32) {
  if (!unknown40.m_dropitemsEmitted) {
    return;
  }
  unknown001(1, 0.0f);
  unknown28 = nullptr;
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfFieldTbox>::~PtrSingleton();
