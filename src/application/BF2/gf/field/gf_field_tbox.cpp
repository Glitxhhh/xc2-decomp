#include "gf/field/gf_field_tbox.h"

#include <string.h>

#include "fw/fw_update_info.h"
#include "gf/game/quest/gf_quest_util.h"
#include "gf/gf_allocator.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/gimmick/gf_com_behavior_gmk.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/scom/gf_scom_obj.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_tbox.h"

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

  gmk::AGmkBase *gmk = gmk::getBindedGmkInst(unknown18);
  if (gmk != nullptr) {
    gmk::GmkType type = gmk->getGmkType();
    u32 gimmick = gmk->unknown20.unknown18;
    if (GfQuestUtil::getGimmickTaskEndCheck(type, gimmick) == 1) {
      SCOM_QUEST_GIMMICK::createTresure(gimmick, 0.0f);
    }
  }
  unknown28 = nullptr;
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfFieldTbox>::~PtrSingleton();
