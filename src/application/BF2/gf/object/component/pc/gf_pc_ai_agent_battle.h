#pragma once

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace navi {
class NvmshAcObj;
} // namespace navi

namespace gf {

class GfComPropertyPc;

namespace pc {

class AIAgentBattle {
public:
  AIAgentBattle();
  ~AIAgentBattle();
  void setup(GfComPropertyPc &property);
  void cleanup(GfComPropertyPc &property);
  void onActivate(GfComPropertyPc &property);
  void onDeactivate(GfComPropertyPc &property);
  void update(const fw::UpdateInfo &info, GfComPropertyPc &property);

  navi::NvmshAcObj *unknown00; // Inferred role: navi mesh object; original member name unknown.
};

static_assert(sizeof(AIAgentBattle) == 0x08, "");

} // namespace pc
} // namespace gf
