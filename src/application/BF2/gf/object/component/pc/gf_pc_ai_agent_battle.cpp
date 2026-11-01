#include "gf/object/component/pc/gf_pc_ai_agent_battle.h"

#include "framework/navi/navi_manager.h"
#include "navi/nvmsh_ac_obj.h"

namespace gf {
namespace pc {

AIAgentBattle::AIAgentBattle() : unknown00(nullptr) {}

AIAgentBattle::~AIAgentBattle() {}

void AIAgentBattle::setup(GfComPropertyPc &property) { unknown00 = fw::NaviManager::get()->createObject(); }

void AIAgentBattle::cleanup(GfComPropertyPc &property) {
  fw::NaviManager *manager = fw::NaviManager::get();
  navi::NvmshAcObj *object = unknown00;
  if (manager != nullptr && object != nullptr) {
    manager->releaseObject(object);
    unknown00 = nullptr;
  }
}

void AIAgentBattle::onActivate(GfComPropertyPc &property) {
  if (unknown00 != nullptr) {
    unknown00->unknown10 |= 2;
  }
}

void AIAgentBattle::onDeactivate(GfComPropertyPc &property) {
  if (unknown00 != nullptr) {
    unknown00->unknown10 &= ~2;
  }
}

void AIAgentBattle::update(const fw::UpdateInfo &info, GfComPropertyPc &property) {}

} // namespace pc
} // namespace gf
