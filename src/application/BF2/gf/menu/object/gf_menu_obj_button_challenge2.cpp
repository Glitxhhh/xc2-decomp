#include "gf/menu/object/gf_menu_obj_button_challenge2.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/gf_menu_types.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "ml/rand.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/rtti.h"
#include "types.h"
#include "ui/ctrl/ui_ctrl_manager.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/shape/ui_shape.h"
#include "ui/shape/ui_shape_ring.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x4b;

// Inferred helper: casts a shape to the ring shape when it is one; original name unknown.
static ui::UIShapeRing *unknown003(ui::UIShape *shape) { return shape != nullptr ? mm::mtl::dynamicCast<ui::UIShapeRing>(shape) : nullptr; }

// Inferred role: animation index of a button type; original name unknown.
static const int unknown004[6] = {0, 0, 1, 2, 3, 0};

GfMenuObjButtonChallenge2::~GfMenuObjButtonChallenge2() {
  if (unknown3e0.ctrl != nullptr) {
    ui::UICtrlManager::get()->delUpdater(unknown3e0);
  }
  unknown3e0.ctrl = nullptr;
  if (unknown428.ctrl != nullptr) {
    ui::UICtrlManager::get()->delUpdater(unknown428);
  }
  unknown428.ctrl = nullptr;
  if (unknown470.ctrl != nullptr) {
    ui::UICtrlManager::get()->delUpdater(unknown470);
  }
  unknown470.ctrl = nullptr;
}

void GfMenuObjButtonChallenge2::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  if (main.isValid()) {
    ui::UIObjectAcc(unknown18).setAlpha(1.0f);
    attachExternalCall(unknown001, main.unknown10);
// __LINE__ must be 139 as in the original file: it is the line argument of operator new.
#line 139
    MainListener *listener = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) MainListener(this);
    listener->addRef();
    ui::UIEventManager::get()->registObjectListener(main.unknown10, listener);
    if (listener != nullptr) {
      listener->release();
    }
    GfMenuObject::initialize();
    u32 count = main.countChild("LAY_challenge_v2@%02d", 1);
    {
      mm::mtl::FixStr<32> name;
      ui::UIObjectAcc(main.unknown10, "POL_ring_v2@01").getSize(true, unknown3b2, unknown3b2);
      ui::UIObjectAcc(main.unknown10, "POL_challenge_hit_a@01").getSize(true, unknown3b0, unknown3b0);
      for (u32 i = 0; i < count; i++) {
        name.format("LAY_challenge_v2@%02d", i + 1);
// __LINE__ must be 156 as in the original file: it is the line argument of operator new.
#line 156
        RingListener *ringListener = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) RingListener(this);
        ringListener->addRef();
        ui::UIEventManager::get()->registObjectListener(main.searchChild(name.c_str()), ringListener);
        if (ringListener != nullptr) {
          ringListener->release();
        }
        name.format("IMG_challenge_btn_push_eff@%02d", i + 1);
        ui::UIObjectAcc(main.unknown10, name.c_str()).setIgnoreSize(true);
      }
    }
    ui::UIObjectAcc contents(main.unknown10, "LAY_guide_contents");
    GfMenuObjUtil::FitOption option;
    option.unknown02 = true;
    GfMenuObjUtil::createFitPlugin(main.searchChild("IMG_guide_bg"), contents.unknown10, 0x18, 0, option);
    contents.getPosCenter(unknown360);
  }
}

void GfMenuObjButtonChallenge2::finalize() { GfMenuObject::finalize(); }

void GfMenuObjButtonChallenge2::update() {
  unknown0a0.unknown003();
  GfMenuObject::update();
}

bool GfMenuObjButtonChallenge2::isValidParam(const OpenParam &param) {
  if (param.unknown00 == 0) {
    return false;
  }
  if (param.unknown08.size() == 0) {
    return false;
  }
  bool isValid = true;
  int total = 0;
  for (u32 i = 0; i < param.unknown08.size(); i++) {
    const unknown002 &challenge = param.unknown08[i];
    if (challenge.unknown00 < 1 || challenge.unknown00 > 5 || challenge.unknown02 == 0) {
      isValid = false;
      break;
    }
    total += challenge.unknown02;
    if (challenge.unknown01 < 1 || challenge.unknown01 > 2) {
      isValid = false;
      break;
    }
    if (challenge.unknown01 == 1 && challenge.unknown04 == 0) {
      isValid = false;
      break;
    }
    if (challenge.unknown01 == 2 && (challenge.unknown08 == 0 || challenge.unknown0a == 0)) {
      isValid = false;
      break;
    }
  }
  return isValid && total == 100;
}

void GfMenuObjButtonChallenge2::dispRelationHUD(bool) {}

void GfMenuObjButtonChallenge2::importOpenParam(OpenParam &param, unsigned int challenge) {
  u8 *bdat = GfDataBdat::getFP(BDAT_MNU_BTN_CHALLENGE2);
  u8 *paramBdat = GfDataBdat::getFP(BDAT_MNU_CHALLENGE_PARAM);
  if (!GfMenuBdat::isValidBdatID(bdat, challenge)) {
    return;
  }
  param.unknown00 = Bdat::getVal(bdat, "Speed", challenge).valueU8;
  param.unknown02 = Bdat::getVal(bdat, "Wait", challenge).valueU16;
  u8 type = 0;
  if (Bdat::getMember(bdat, "Type") != nullptr) {
    type = Bdat::getVal(bdat, "Type", challenge).valueU8;
  }
  param.unknown04 = type;
  param.unknown08.clear();
  for (u32 i = 1; i != 4; i++) {
    mm::mtl::FixStr<32> name;
    name.format("Param%d", i);
    u8 id = Bdat::getVal(bdat, name.c_str(), challenge).valueU8;
    if (GfMenuBdat::isValidBdatID(paramBdat, id)) {
      unknown002 info;
      name.format("BtnType%d", i);
      info.unknown00 = Bdat::getVal(bdat, name.c_str(), challenge).valueU8;
      name.format("Point%d", i);
      info.unknown02 = Bdat::getVal(bdat, name.c_str(), challenge).valueU8;
      name.format("Start%d", i);
      info.unknown0c = 0;
      if (Bdat::getMember(bdat, name.c_str()) != nullptr) {
        info.unknown0c = Bdat::getVal(bdat, name.c_str(), challenge).valueU16;
      }
      name.format("Hit%d", i);
      info.unknown0e = 0;
      if (Bdat::getMember(bdat, name.c_str()) != nullptr) {
        info.unknown0e = Bdat::getVal(bdat, name.c_str(), challenge).valueU16;
      }
      name.format("End%d", i);
      info.unknown10 = 0;
      if (Bdat::getMember(bdat, name.c_str()) != nullptr) {
        info.unknown10 = Bdat::getVal(bdat, name.c_str(), challenge).valueU16;
      }
      info.unknown12 = 0;
      if (Bdat::getMember(paramBdat, "PushSweetFrame") != nullptr) {
        info.unknown12 = Bdat::getVal(paramBdat, "PushSweetFrame", id).valueU16;
      }
      info.unknown01 = Bdat::getVal(paramBdat, "InputType", id).valueU8;
      info.unknown04 = Bdat::getVal(paramBdat, "PushRange", id).valueU16;
      info.unknown06 = Bdat::getVal(paramBdat, "PushSweetRange", id).valueU16;
      info.unknown08 = Bdat::getVal(paramBdat, "MashingCount", id).valueU8;
      info.unknown0a = Bdat::getVal(paramBdat, "MashingTime", id).valueU16;
      param.unknown08.push_back(info);
    }
  }
}

void GfMenuObjButtonChallenge2::open(GfMenuCallContext *context, unsigned int challenge, bool isDispButton, bool isSound) {
  OpenParam param;
  importOpenParam(param, challenge);
  param.unknown50.unknown00 = isDispButton;
  param.unknown50.unknown01 = isSound;
  open(context, param, 0);
}

void GfMenuObjButtonChallenge2::open(GfMenuCallContext *context, unsigned int challenge, const OptionParam &option) {
  OpenParam param;
  importOpenParam(param, challenge);
  param.unknown50 = option;
  open(context, param, 0);
}

void GfMenuObjButtonChallenge2::openSequence(GfMenuCallContext *context, unsigned int challenge, bool isDispButton, bool isSound) {
  u32 id = Bdat::getVal(GfDataBdat::getFP(BDAT_MNU_BTN_CHALLENGE_SEQ), "challenge01", challenge).valueU16;
  if (id != 0) {
    OpenParam param;
    importOpenParam(param, id);
    param.unknown50.unknown00 = isDispButton;
    param.unknown50.unknown01 = isSound;
    open(context, param, challenge);
  }
}

void GfMenuObjButtonChallenge2::openSequence(GfMenuCallContext *context, unsigned int challenge, const OptionParam &option) {
  u32 id = Bdat::getVal(GfDataBdat::getFP(BDAT_MNU_BTN_CHALLENGE_SEQ), "challenge01", challenge).valueU16;
  if (id != 0) {
    OpenParam param;
    importOpenParam(param, id);
    param.unknown50 = option;
    open(context, param, challenge);
  }
}

u32 GfMenuObjButtonChallenge2::getResultPoint() const {
  u32 point = unknown98;
  if (unknown90 != 0) {
    point = unknown98 / (unknown94 + 1);
  }
  return point;
}

void GfMenuObjButtonChallenge2::resume(GfMenuCallContext *context) {
  if (GfMenuObjUtil::checkCCNext(context, unknown001)) {
    unknown144(unknown001, 0x101);
  }
}

void GfMenuObjButtonChallenge2::close(GfMenuCallContext *context) {
  if (GfMenuObjUtil::checkCCNext(context, unknown001)) {
    unknown144(unknown001, GfMenuTypes::unknown003_34);
  }
}

void GfMenuObjButtonChallenge2::setSpeedFactor(GfMenuCallContext *context, f32 speedFactor) {
  if (GfMenuObjUtil::checkCCNext(context, unknown001)) {
    ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
    if (acc.isValid()) {
      ui::EventData event;
      event.unknown0c = 0;
      event.unknown00 = 0x102;
      event.unknown08_f32 = speedFactor;
      GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
    }
  }
}

void GfMenuObjButtonChallenge2::stopSeqCtrl() {
  for (int *ctrl = unknown330.begin(); ctrl != unknown330.end(); ctrl++) {
    GfMenuObjUtil::stopCtrl(*ctrl);
  }
  unknown330.clear();
}

bool GfMenuObjButtonChallenge2::seqStart() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  main.setDisp(true);
  unknown98 = 0;
  unknown80 = 0;
  unknown84 = 0;
  unknown88 = 0;
  unknown330.clear();
  unknown9c = 1.0f;
  GfMenuObject::enableInput(ui::UIObjectAcc(unknown18, "LAY_main").unknown10);
  unknown358 = false;
  unknown359 = false;
  unknown0a0.unknown002(&GfMenuObjButtonChallenge2::seqAppearCursor);
  return true;
}

void GfMenuObjButtonChallenge2::setupV2(const OpenParam &param) {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  mm::mtl::FixStr<32> name;
  if (unknown28.unknown08.size() == 0) {
    GfMenuObject::termCallContext(main.unknown10);
  } else {
    for (u32 i = 0; i < unknown28.unknown08.size(); i++) {
      name.format("LAY_challenge_v2@%02d", i + 1);
      GfMenuObject::sendOpenEvent(main.searchChild(name.c_str()), i, 0.0f);
    }
    unknown80 = 0;
    unknown84 = 0;
    unknown498 = 0;
    unknown49c = 0;
    unknown490 = 0;
    unknown494 = 0;
  }
}

bool GfMenuObjButtonChallenge2::seqEnd() {
  ui::UIObjectAcc acc(unknown18, "LAY_main");
  acc.setDisp(false);
  GfMenuObject::termCallContext(GfMenuObject::getAttachedObject(unknown001));
  return true;
}

void GfMenuObjButtonChallenge2::notifyChallengeResult() {
  if (!unknown359) {
    GfMenuObject::addResultCallContext(GfMenuObject::getAttachedObject(unknown001), 2, getResultPoint());
    unknown359 = true;
  }
}

bool GfMenuObjButtonChallenge2::getChallengeMashingWait(u32 &wait) {
  if (unknown80 >= unknown28.unknown08.size()) {
    return false;
  }
  if (unknown28.unknown08[unknown80].unknown01 == 2) {
    wait = unknown28.unknown08[unknown80].unknown0a;
    return true;
  }
  return false;
}

void GfMenuObjButtonChallenge2::setRingScaleV2(u32 index, f32 scale) {
  mm::mtl::FixStr<32> name;
  name.format("POL_ring_v2@%02d", index + 1);
  ui::UIShapeRing *ring = unknown003(ui::UIObjectAcc(unknown18, name.c_str()).getShape());
  if (ring != nullptr) {
    ring->setScale(scale);
  }
}

void GfMenuObjButtonChallenge2::setRingScale(f32 scale) {
  ui::UIShapeRing *ring = unknown003(ui::UIObjectAcc(unknown18, "POL_ring_v2@04").getShape());
  if (ring != nullptr) {
    ring->setScale(scale);
  }
}

void GfMenuObjButtonChallenge2::updateChallenge() {
  if (unknown348.size() != 0 && unknown80 < unknown28.unknown08.size()) {
    mm::Rect<s16> rect;
    {
      ui::UIObjectAcc acc(unknown18, "POL_ring_v2@04");
      acc.getRect(rect, ui::UIObjectAcc::RECT_SCALED);
    }
    if (rect.width != 0 && rect.height != 0) {
      int ringSize = static_cast<int>(unknown3b2 * unknown348.front() - unknown3b0);
      if (unknown28.unknown08[unknown80].unknown01 == 1 && ringSize < unknown3b0) {
        unknown80++;
      }
    }
  }
}

bool GfMenuObjButtonChallenge2::isSeqCtrlBusy() {
  int *ctrl = unknown330.begin();
  while (ctrl != unknown330.end()) {
    if (GfMenuObjUtil::isBusyCtrl(*ctrl)) {
      ctrl++;
    } else {
      unknown330.erase(ctrl);
    }
  }
  return !unknown330.empty();
}

void GfMenuObjButtonChallenge2::nextChallenge() {
  unknown80++;
  if (unknown80 == unknown28.unknown08.size()) {
    notifyChallengeResult();
    unknown0a0.unknown002(&GfMenuObjButtonChallenge2::seqCheckSequence);
  } else {
    setup(unknown28, unknown80, false);
    unknown0a0.unknown002(&GfMenuObjButtonChallenge2::seqAppearCursor);
  }
}

bool GfMenuObjButtonChallenge2::seqWaitRestartV2() {
  if (!unknown4a0) {
    return false;
  }
  setupV2(unknown28);
  unknown0a0.unknown002(&GfMenuObjButtonChallenge2::seqRunningV2);
  return true;
}

bool GfMenuObjButtonChallenge2::seqWaitMashingV2() {
  if (unknown80 < unknown28.unknown08.size()) {
    if (++unknown490 < unknown498) {
      return false;
    }
    unknown80++;
  }
  ui::UIObjectAcc acc(unknown18, "LAY_challenge_v2");
  mm::mtl::FixStr<32> name;
  ui::EventData event;
  event.unknown00 = 0x104;
  for (u32 i = 0; i < unknown28.unknown08.size(); i++) {
    name.format("LAY_challenge_v2@%02d", i + 1);
    GfMenuObject::sendEvent(acc.searchChild(name.c_str()), event, 0.0f);
  }
  notifyChallengeResult();
  return true;
}

void GfMenuObjButtonChallenge2::setup(const OpenParam &param, unsigned int challengeIndex, bool isFirst) {
  if (param.unknown08.size() == 0) {
    return;
  }
  ui::UIObjectAcc main(unknown18, "LAY_main");
  if (isFirst) {
    main.setDispChild(false, "LAY_result");
  }
  ui::UIObjectAcc challengeLayer(main.unknown10, "LAY_challenge");
  unknown002 &challenge = unknown28.unknown08[challengeIndex];
  u8 inputType = challenge.unknown01;
  {
    ui::UIObjectAcc ring(main.unknown10, "POL_ring_v2@04");
    setRingScale(1.0f);
    ring.setAlpha(1.0f);
  }
  if (challenge.unknown00 == 5) {
    challenge.unknown00 = ml::mtRand() % 4 + 1;
  }
  bool isPush = inputType == 1;
  main.setDispChild(isPush, "LAY_challenge_hit_v2@04");
  main.setDispChild(isPush, "IMG_challenge_btn_v2@04");
  main.setDispChild(!isPush, "LAY_challenge_btn_push_v2@04");
  if (!isPush) {
    ui::UIObjectAcc pushButton(main.unknown10, "IMG_challenge_btn_push_v2@04");
    pushButton.startAnimationFromIndex(challenge.unknown00 < 6 ? unknown004[challenge.unknown00] + 1 : 1, false);
    return;
  }
  f32 minSize = unknown3b0;
  f32 sizeRange = unknown3b2 - minSize;
  main.setDispChild(false, "LAY_challenge_btn_push_v2@04");
  f32 sweetSize = sizeRange * (static_cast<f32>(challenge.unknown06) / 1000.0f);
  f32 sweetRing = minSize * ((minSize + sweetSize) / minSize);
  f32 weight = (sweetRing - minSize) * 0.5f;
  ui::UIShapeRing *hitRing = unknown003(ui::UIObjectAcc(main.unknown10, "POL_challenge_hit_b@04").getShape());
  if (hitRing != nullptr) {
    hitRing->setScale((minSize + (sweetSize - weight)) / minSize);
    hitRing->setWeightScale(weight);
  }
  ui::UIShapeRing *glowRing = unknown003(ui::UIObjectAcc(main.unknown10, "POL_challenge_hit_b_glow@04").getShape());
  if (glowRing != nullptr) {
    glowRing->setScale((sweetRing + 14.0f) / unknown3b0);
  }
  {
    ui::UIObjectAcc hit(main.unknown10, "POL_challenge_hit_a@04");
    u16 range = challenge.unknown04;
    u16 sweet = challenge.unknown06;
    hit.setDisp(range > sweet);
    if (range > sweet) {
      f32 rangeSize = sizeRange * (static_cast<f32>(challenge.unknown04) / 1000.0f);
      f32 rangeScale = minSize * ((minSize + rangeSize) / minSize);
      f32 rangeWeight = (rangeScale - minSize) * 0.5f;
      ui::UIShapeRing *rangeRing = unknown003(ui::UIObjectAcc(main.unknown10, "POL_challenge_hit_a@04").getShape());
      if (rangeRing != nullptr) {
        rangeRing->setScale((minSize + (rangeSize - rangeWeight)) / minSize);
        rangeRing->setWeightScale(rangeWeight);
      }
    }
  }
  ui::UIObjectAcc button(main.unknown10, "IMG_challenge_btn_v2@04");
  button.setImageIndex(challenge.unknown00 < 6 ? unknown004[challenge.unknown00] : 0);
}

bool GfMenuObjButtonChallenge2::seqAppear() {
  if (unknown330.empty()) {
    ui::UIObjectAcc main(unknown18, "LAY_challenge");
    if (unknown28.unknown50.unknown04 > 0.0f) {
      GfMenuObjUtil::CtrlParam param;
      param.unknown00 = unknown28.unknown50.unknown04;
      param.unknown08 = 1;
      unknown330.push_back(GfMenuObjUtil::startCtrl(main.unknown10, param, nullptr));
    } else {
      main.setDisp(true);
    }
    ui::UIObjectAcc contents(main.unknown10, "LAY_guide_contents");
    contents.setPosCenter(unknown360);
  }
  return !isSeqCtrlBusy();
}

bool GfMenuObjButtonChallenge2::seqAppearCursor() {
  if (unknown28.unknown50.unknown00) {
    return false;
  }
  if (unknown330.empty()) {
    ui::UIObjectAcc main(unknown18, "LAY_challenge_v2@04");
    setRingScale(1.0f);
    main.setDispChild(true, "LAY_ring_v2@04");
    if (unknown80 == 0 && unknown28.unknown02 != 0) {
      GfMenuObjUtil::CtrlParam param;
      param.unknown00 = unknown28.unknown02 * 0.033333335f;
      param.unknown08 = 1;
      param.unknown0c = 1;
      unknown330.push_back(GfMenuObjUtil::startCtrl(main.unknown10, param, nullptr));
    } else {
      main.setDisp(true);
    }
    if (unknown80 < unknown28.unknown08.size() && unknown28.unknown08[unknown80].unknown01 == 2) {
      ui::UIObjectAcc ring(unknown18, "POL_ring_v2@04");
      ring.setAlpha(0.0f);
    }
  }
  if (isSeqCtrlBusy()) {
    return false;
  }
  const unknown002 &challenge = unknown28.unknown08[unknown80];
  unknown35a = 0;
  if (challenge.unknown01 == 1) {
    unknown0a0.unknown002(&GfMenuObjButtonChallenge2::seqMovePush);
  } else if (challenge.unknown01 == 2) {
    unknown0a0.unknown002(&GfMenuObjButtonChallenge2::seqMoveMashing);
  }
  return true;
}

bool GfMenuObjButtonChallenge2::seqResultStart() {
  if (unknown330.empty()) {
    {
      ui::UIObjectAcc main(unknown18, "LAY_main");
      GfMenuObject::disableInput(main.unknown10);
    }
    u8 *bdat = GfDataBdat::getFP(BDAT_MNU_CHALLENGE_RESULT);
    if (bdat != nullptr) {
      int top = Bdat::getIdTop(bdat);
      u32 point = getResultPoint();
      u32 text = 0;
      int i = 0;
      int rank = 0;
      for (; i < Bdat::getIdCount(bdat); i++) {
        if (point >= Bdat::getVal(bdat, "Point", i + top).valueU8) {
          text = Bdat::getVal(bdat, "Text", i + top).valueU32;
          rank = i + 1;
        }
      }
      if (text != 0) {
        ui::UIObjectAcc result(unknown18, "LAY_result");
        ui::UIObjectAcc resultText(unknown18, "LAY_result_text");
        ui::UIObjectAcc effect(result.unknown10, "IMG_result_eff");
        {
          ui::UIObjectAcc label(result.unknown10, "TXT_result");
          ui::UIObjectAcc shadow(result.unknown10, "TXT_result_shadow");
          label.setText(ui::UIStr(GfDataBdat::getFP(BDAT_MENU_MS), text));
          shadow.setText(ui::UIStr(GfDataBdat::getFP(BDAT_MENU_MS), text));
          if (rank == 3) {
            label.setTextFacePattern("element01");
            label.setAddColor("txt_bch_result_exc_add");
            GfMenuObjUtil::setColMulandAdd(shadow.unknown10, "txt_bch_result_exc");
          } else {
            label.setTextFacePattern("element03");
            label.setAddColor("txt_bch_result_good_add");
            GfMenuObjUtil::setColMulandAdd(shadow.unknown10, "txt_bch_result_good");
          }
        }
        result.setDisp(true);
        resultText.setDisp(true);
        GfMenuObjUtil::CtrlParam param;
        param.unknown08 = 0x10000000;
        param.unknown50 = "cmn_fade_motion_zoom_2";
        param.unknown58 = "fade_in";
        param.unknown11 = true;
        param.unknown14 = 8;
        unknown330.push_back(GfMenuObjUtil::startCtrl(resultText.unknown10, param, nullptr));
        GfMenuObject::addResultCallContext(GfMenuObject::getAttachedObject(unknown001), 3, rank);
        effect.startAnimation("start", false);
      }
    }
  }
  if (isSeqCtrlBusy()) {
    return false;
  }
  unknown35c = 30;
  return true;
}
} // namespace gf

template bool mm::mtl::Delegate<bool()>::memberFuncInvoker<gf::GfMenuObjButtonChallenge2>(const mm::mtl::Delegate<bool()> *);
