#include "event/manager.h"

#include "event/cmd_queue.h"
#include "event/cpu_manager.h"
#include "event/debug_manager.h"
#include "event/frame_manager.h"
#include "event/seq_manager.h"
#include "event/ui_manager.h"

#include "framework/lang_util.h"
#include "gf/game/event/gf_game_event.h"
#include "ml/proc_desktop.h"
#include "mtl/alloc_handle.h"

namespace ml {
class EventView;
} // namespace ml

namespace event {

void Manager::failureSkip() {
  mm::mtl::Singleton<DebugManager>::getPtr()->failureSkip();
  mm::mtl::Singleton<DebugManager>::getPtr()->setDisp(true);
  mm::mtl::Singleton<DebugManager>::getPtr()->playMessage("failure skip!! [%s.sb]", unknown230.c_str());
}

void Manager::play(const char *name, gf::GF_OBJ_HANDLE *handle, u32 param0, u32 param1, u32 param2, u32 param3, bool isEndFadeOut) {
  unknown298 = LANGUAGE_MODE_NONE;
  unknown280 = handle;
  unknown288[0] = param0;
  unknown288[1] = param1;
  unknown288[2] = param2;
  unknown288[3] = param3;
  if (isEndFadeOut) {
    unknown18 |= FLAG_END_FADE_OUT;
  } else {
    unknown18 &= ~FLAG_END_FADE_OUT;
  }
  if (!isPlay()) {
    mm::mtl::Singleton<SeqManager>::getPtr()->play(name);
  }
  unknown18 &= ~(FLAG_PLAY | FLAG_PLAY_END);
  unknown18 |= FLAG_PLAY;
}

bool Manager::startScene(const char *name, int pageID) {
  if ((unknown1c & STATE_START_SCENE) == 0) {
    unknown254 = name;
    unknown278 = pageID;
    execMessage(MSG_TYPE_START_SCENE);
    unknown1c |= STATE_START_SCENE;
  }
  SeqManager *seq = mm::mtl::Singleton<SeqManager>::getPtr();
  if (seq->unknown200.isExist(&seq->unknowna8) || seq->unknown200.isExist(&seq->unknownb0) || seq->unknown200.isExist(&seq->unknownb8) || seq->unknown200.isExist(&seq->unknownc0) ||
      seq->unknown200.isExist(&seq->unknownc8) || seq->unknown200.isExist(&seq->unknownd0)) {
    return false;
  }
  unknown1c &= ~STATE_START_SCENE;
  return true;
}

bool Manager::startPage(const char *name, int pageID, f32 maxFrame) {
  if ((unknown1c & STATE_START_PAGE) == 0) {
    execMessage(MSG_TYPE_START_PAGE);
    mm::mtl::Singleton<FrameManager>::getPtr()->setInfomation(name, pageID, maxFrame);
    unknown1c |= STATE_START_PAGE;
  }
  SeqManager *seq = mm::mtl::Singleton<SeqManager>::getPtr();
  if (seq->unknown200.isExist(&seq->unknownd8)) {
    return false;
  }
  unknown1c &= ~STATE_START_PAGE;
  return true;
}

bool Manager::endScene() {
  if ((unknown1c & STATE_END_SCENE) == 0) {
    execMessage(MSG_TYPE_END_SCENE_BEGIN);
    unknown1c |= STATE_END_SCENE;
  }
  SeqManager *seq = mm::mtl::Singleton<SeqManager>::getPtr();
  if (seq->unknown200.isExist(&seq->unknowne0) || seq->unknown200.isExist(&seq->unknownf8) || seq->unknown200.isExist(&seq->unknown100) || seq->unknown200.isExist(&seq->unknown108)) {
    return false;
  }
  execMessage(MSG_TYPE_END_SCENE);
  unknown1c &= ~STATE_END_SCENE;
  return true;
}

bool Manager::setupSceneEnd() {
  if ((unknown1c & STATE_SETUP_SCENE_END) == 0) {
    execMessage(MSG_TYPE_SETUP_SCENE_END);
    unknown1c |= STATE_SETUP_SCENE_END;
  }
  if (mm::mtl::Singleton<SeqManager>::getPtr()->isSetupSceneEnd()) {
    unknown1c &= ~STATE_SETUP_SCENE_END;
    return true;
  }
  return false;
}

void Manager::nextEvent(int next) {
  if (isPlay()) {
    mm::mtl::Singleton<SeqManager>::getPtr()->nextEvent(next);
  }
}

void Manager::finishNewGameWait() { mm::mtl::Singleton<UIManager>::getPtr()->finishNewGameWait(); }

bool Manager::isPlayCancel() const { return mm::mtl::Singleton<DebugManager>::getPtr()->isPlayCancel(); }

void Manager::clearAlways() {
  if (unknown18 & FLAG_HIDE_INFO) {
    unknown18 &= ~FLAG_HIDE_INFO;
  }
  unknown18 &= ~FLAG_PLAY;
}

void Manager::clear() {
  unknown280 = reinterpret_cast<gf::GF_OBJ_HANDLE *>(-1);
  unknown288[0] = 0;
  unknown288[1] = 0;
  unknown288[2] = 0;
  unknown288[3] = 0;
  unknown298 = LANGUAGE_MODE_NONE;
  unknown18 &= ~FLAG_END_FADE_OUT;
  unknown1c = 0;
}

void Manager::execMessage(MSG_TYPE type) {
  for (u32 i = 0; i < unknown20.size(); i++) {
    unknown20[i]->OnEventProc(type);
  }
}

void Manager::render() { ml::ProcDesktop::isDispInfo(); }

void Manager::tail() {
  if (unknown1c & STATE_INIT) {
    execMessage(MSG_TYPE_TAIL);
  }
  execMessage(MSG_TYPE_TAIL_POST);
}

void Manager::post() {}

bool Manager::setupScene(const char *name) {
  unknown254 = name;
  execMessage(MSG_TYPE_SETUP_SCENE);
  return true;
}

void Manager::setLanguageMode(bool isEnable, LANGUAGE_MODE mode) { unknown298 = isEnable ? mode : LANGUAGE_MODE_NONE; }

bool Manager::checkLanguageMode() const {
  switch (unknown298) {
  case LANGUAGE_MODE_VOICE_TYPE_0:
    return fw::LangUtil::getVoiceType() == 0;
  case LANGUAGE_MODE_VOICE_TYPE_1:
    return fw::LangUtil::getVoiceType() == 1;
  default:
    return true;
  }
}

void Manager::setDebugPlayOnetime(bool isPlayOnetime) { mm::mtl::Singleton<DebugManager>::getPtr()->setPlayOnetime(isPlayOnetime); }

bool Manager::isDebugPlayOnetime() const { return mm::mtl::Singleton<DebugManager>::getPtr()->isPlayOnetime(); }

void Manager::setDebugFastSkipDisable(bool isDisable) { mm::mtl::Singleton<DebugManager>::getPtr()->setFastSkipDisable(isDisable); }

void Manager::setDebugAgeingSkipEnable(bool isEnable) { mm::mtl::Singleton<DebugManager>::getPtr()->setAgeingSkipEnable(isEnable); }

void Manager::setDebugDisableBgm(bool isDisable) { mm::mtl::Singleton<DebugManager>::getPtr()->setDisableBgm(isDisable); }

void Manager::setDebugReplaceDefaultEquip(bool isReplace, u32 slot, u32 item) { mm::mtl::Singleton<DebugManager>::getPtr()->setReplaceDefaultEquip(isReplace, slot, item); }

bool Manager::isReplaceDefaultEquip(u32 slot, u32 *item) const { return mm::mtl::Singleton<DebugManager>::getPtr()->isReplaceDefaultEquip(slot, item); }

void Manager::setDebugReplaceMaximumEquip(bool isReplace) { mm::mtl::Singleton<DebugManager>::getPtr()->setReplaceMaximumEquip(isReplace); }

bool Manager::isDebugReplaceMaximumEquip() const { return mm::mtl::Singleton<DebugManager>::getPtr()->isReplaceMaximumEquip(); }

void Manager::setDebugReplaceMaximumBlade(bool isReplace) { mm::mtl::Singleton<DebugManager>::getPtr()->setReplaceMaximumBlade(isReplace); }

bool Manager::isDebugReplaceMaximumBlade() const { return mm::mtl::Singleton<DebugManager>::getPtr()->isReplaceMaximumBlade(); }

void Manager::setSyncFreeCam(bool isSync, bool isOneTime) { mm::mtl::Singleton<DebugManager>::getPtr()->setSyncFreeCam(isSync, isOneTime); }

Manager *Manager::create(ml::Scn *scn) {
  destroy();
  mtl::ALLOC_HANDLE handle = gf::GfGameEvent::getEventMem();
  return new (handle, nullptr, 0, 4, false) Manager(scn);
}

void Manager::destroy() {
  if (get()) {
    delete get();
  }
}

bool Manager::OnKeyDown(ml::EventView *view) { return false; }

void Manager::bkgHomeMenu(bool isOpen) {
  mm::mtl::Singleton<CpuManager>::getPtr()->pauseHome(true);
  if (!isOpen) {
    mm::mtl::Singleton<CpuManager>::getPtr()->pauseHome(false);
  }
}

} // namespace event

template mm::mtl::PtrSingleton<event::Manager>::~PtrSingleton();
