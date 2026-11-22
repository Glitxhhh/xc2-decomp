#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {
class DrEnvColiMan;
class DrEnvironmentObj;
class DrFogMan;
class DrLightMan;
class DrMan;

class DrEnvironmentMan {
public:
  DrEnvironmentMan(DrMan *drMan, DrLightMan *lightMan, DrFogMan *fogMan, int screen);
  ~DrEnvironmentMan();
  DrEnvironmentObj *createObj(const void *data);
  void releaseObj(DrEnvironmentObj *obj);
  void renderLgt();
  void releaseAll();
  void setZoneObj(DrEnvironmentObj *obj, bool isOn);
  void updateCameraLight();
  void update();

  DrMan *m_drMan;               // Inferred role: dr man; original member name unknown.
  DrLightMan *m_drLightMan;     // Inferred role: light man; original member name unknown.
  DrFogMan *m_drFogMan;         // Inferred role: fog man; original member name unknown.
  DrEnvColiMan *m_drEnvColiMan; // Inferred role: env coli man; original member name unknown.
  int unknown20;                // Inferred role: screen index; original member name unknown.
  u8 _24[0x28 - 0x24];
  DrEnvironmentObj *unknown28[4]; // Inferred role: first and last object of the request list per buffer; original member name unknown.
  DrEnvironmentObj *unknown48;    // Inferred role: first object of the list; original member name unknown.
  DrEnvironmentObj *unknown50;    // Inferred role: last object of the list; original member name unknown.
  DrEnvironmentObj *unknown58;    // Inferred role: first object of the release list; original member name unknown.
  DrEnvironmentObj *unknown60;    // Inferred role: last object of the release list; original member name unknown.
  DrEnvironmentObj *unknown68;    // Inferred role: camera light object; original member name unknown.
};

static_assert(offsetof(DrEnvironmentMan, m_drLightMan) == 0x08, "");
static_assert(offsetof(DrEnvironmentMan, m_drFogMan) == 0x10, "");
static_assert(offsetof(DrEnvironmentMan, m_drEnvColiMan) == 0x18, "");
static_assert(offsetof(DrEnvironmentMan, unknown20) == 0x20, "");
static_assert(offsetof(DrEnvironmentMan, unknown28) == 0x28, "");
static_assert(offsetof(DrEnvironmentMan, unknown48) == 0x48, "");
static_assert(offsetof(DrEnvironmentMan, unknown60) == 0x60, "");
static_assert(offsetof(DrEnvironmentMan, unknown68) == 0x68, "");
static_assert(sizeof(DrEnvironmentMan) == 0x70, "");

} // namespace ml
