#pragma once
#include <stddef.h>

#include "framework/sensor/sensor_manager.h"
#include "fw/fw_param_manager.h"
#include "gf/object/component/gf_component.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_plane.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/unique_ptr.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace fw {
class MessageObject;
struct Transform;
} // namespace fw

namespace gf {

struct GF_OBJ_HANDLE;

// Layout evidence: GfComEnvSensor::GfComEnvSensor() constructs the sensor at +0x10 and the next member at +0x2b0;
// EnviromentSensor::EnviromentSensor() clears +0x20, constructs VerticalData at +0x30 and a GroundInfo at +0x1f0 and
// stores 1.0f at +0x290; GroundInfo::GroundInfo() and VerticalData::VerticalData() store the fields below (none of the
// three constructors is reconstructed: the game has no complete-object symbol for GroundInfo's).
// The info offsets are the ones StateUtil::get*Info() add to the sensor, selected by a bit of the state word at +0x24.
class EnviromentSensor {
public:
  enum Flag {};

  struct GroundInfo {
    mm::Vec3 unknown00;       // Inferred role: position; original member name unknown.
    mm::Plane unknown10;      // Inferred role: plane; original member name unknown.
    u64 unknown30;            // Inferred role: flags, bit 5 is the slide flag; original member name unknown.
    GF_OBJ_HANDLE *unknown38; // Inferred role: object handle; original member name unknown.
    mm::Vec3 unknown40;       // Inferred role: unknown vector; original member name unknown.
    mm::Col4 unknown50;       // Inferred role: color; original member name unknown.
    u32 unknown60;            // Inferred role: unknown; original member name unknown.
  };

  // Inferred role: water info; original type name unknown.
  struct unknown001 {
    u32 unknown00;       // Inferred role: unknown; original member name unknown.
    mm::Plane unknown10; // Inferred role: plane; original member name unknown.
    u32 unknown30;       // Inferred role: damage id; original member name unknown.
    u32 unknown34;       // Inferred role: unknown; original member name unknown.
    u32 unknown38;       // Inferred role: unknown; original member name unknown.
  };

  // Inferred role: dead plane info, written by searchVertical with the state bit 2; original type name unknown.
  struct unknown002 {
    mm::Vec3 unknown00;  // Inferred role: position; original member name unknown.
    mm::Plane unknown10; // Inferred role: plane; original member name unknown.
  };

  // Inferred role: horizontal wall info, written by searchHorizon with the state bits 4 (+0x150), 5 (+0x180) and 6 (+0x1b0,
  // climb wall); original type name unknown.
  struct unknown003 {
    mm::Plane unknown00; // Inferred role: wall plane; original member name unknown.
    u8 _20[0x24 - 0x20];
    u8 : 4;
    u8 unknown24_4 : 1; // Inferred role: valid; original member name unknown.
    u8 : 3;
    u8 _25[0x28 - 0x25];
  };

  // Inferred role: descend wall info; original type name unknown.
  struct unknown004 {
    u8 _00[0x30];
  };

  // Inferred role: ceiling info, written by searchVertical with the state bit 3; original type name unknown.
  struct unknown005 {
    f32 unknown00;       // Inferred role: height; original member name unknown.
    mm::Plane unknown10; // Inferred role: plane; original member name unknown.
    u32 unknown30;       // Inferred role: unknown; original member name unknown.
  };

  // Layout evidence: VerticalData::VerticalData() initializes the water info at +0x70 and the ceiling info at +0xe0, and
  // EnviromentSensor::check() passes +0x150, the end of the VerticalData, to searchHorizon.
  struct VerticalData : GroundInfo {
    unknown001 unknown70; // Inferred role: water info; original member name unknown.
    unknown002 unknownb0; // Inferred role: dead plane info; original member name unknown.
    unknown005 unknowne0; // Inferred role: ceiling info; original member name unknown.
  };

  u8 _00[0x20 - 0x00];
  u32 m_envSensorCheckFlags;
  union {
    u32 unknown24; // Inferred role: state flags; original member name unknown.
    struct {
      u32 unknown24_0 : 1; // Inferred role: ground found; original member name unknown.
      u32 unknown24_1 : 1; // Inferred role: water found; original member name unknown.
      u32 unknown24_2 : 1; // Inferred role: dead plane found; original member name unknown.
      u32 unknown24_3 : 1; // Inferred role: ceiling found; original member name unknown.
      u32 unknown24_4 : 1; // Inferred role: horizontal wall found; original member name unknown.
      u32 unknown24_5 : 1; // Inferred role: horizontal info of +0x180 found; original member name unknown.
      u32 unknown24_6 : 1; // Inferred role: climb wall found; original member name unknown.
      u32 unknown24_7 : 1; // Inferred role: descend wall found; original member name unknown.
      u32 unknown25_0 : 1; // Inferred role: climb end ground found; original member name unknown.
      u32 : 23;
    };
  };
  VerticalData unknown30; // Inferred role: vertical ground data; original member name unknown.
  unknown003 unknown150;  // Inferred role: horizontal wall info (state bit 4); original member name unknown.
  unknown003 unknown180;  // Inferred role: horizontal info of the state bit 5; original member name unknown.
  unknown003 unknown1b0;  // Inferred role: climb wall info (state bit 6); original member name unknown.
  u64 unknown1e0;         // Inferred role: climb end object handle, -1 when none; original member name unknown.
  u8 _1e8[0x1f0 - 0x1e8];
  GroundInfo unknown1f0; // Inferred role: climb end ground; original member name unknown.
  unknown004 unknown260; // Inferred role: descend wall info; original member name unknown.
  f32 unknown290;        // Inferred role: unknown scale; original member name unknown.
  u8 _294[0x2a0 - 0x294];
};

static_assert(sizeof(EnviromentSensor::GroundInfo) == 0x70, "");
static_assert(offsetof(EnviromentSensor::GroundInfo, unknown38) == 0x38, "");
static_assert(sizeof(EnviromentSensor::unknown001) == 0x40, "");
static_assert(sizeof(EnviromentSensor::unknown002) == 0x30, "");
static_assert(sizeof(EnviromentSensor::unknown003) == 0x30, "");
static_assert(sizeof(EnviromentSensor::unknown005) == 0x40, "");
static_assert(sizeof(EnviromentSensor::VerticalData) == 0x120, "");
static_assert(offsetof(EnviromentSensor, m_envSensorCheckFlags) == 0x20, "");
static_assert(offsetof(EnviromentSensor, unknown30) == 0x30, "");
static_assert(offsetof(EnviromentSensor, unknown150) == 0x150, "");
static_assert(offsetof(EnviromentSensor, unknown1b0) == 0x1b0, "");
static_assert(offsetof(EnviromentSensor, unknown1f0) == 0x1f0, "");
static_assert(offsetof(EnviromentSensor, unknown260) == 0x260, "");
static_assert(offsetof(EnviromentSensor, unknown290) == 0x290, "");
static_assert(sizeof(EnviromentSensor) == 0x2a0, "");

// Inferred role: sensor of the enemies around the object, created by GfComEnvSensor::setup() as a one byte object; original member name unknown.
class GfEnemySensor {
public:
  u8 unknown00;
};

class GfComEnvSensor : public GfComponent {
public:
  static mm::mtl::RTTI m_rtti;
  static const u32 COMPONENT_INDEX = 11;

  class EnvListener {
  public:
    virtual void onWkStandbyLogout() { unknown08->unknown368 = nullptr; }

    GfComEnvSensor *unknown08; // Inferred role: owner; original member name unknown.
  };

  bool recieveMessage(fw::MessageObject *sender, fw::Message &message) override;
  void procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message);
  ~GfComEnvSensor() override;
  void cleanup();
  void changeLayer(u32 oldLayer, u32 newLayer) override;
  void setEnableSensor(bool isEnable);
  void resolveTransform();
  const fw::Transform &getTransform();
  const mm::mtl::RTTI *getRTTI() const override;

  EnviromentSensor unknown10;                      // Inferred role: sensor; original member name unknown.
  u16 unknown2b0[6];                               // Inferred role: bone indices; original member name unknown.
  u16 unknown2bc;                                  // Inferred role: root bone index; original member name unknown.
  u32 unknown2c0[6];                               // Inferred role: foot flags; original member name unknown.
  mm::mtl::IntrusivePtr<fw::ParamList> unknown2d8; // Inferred role: param list; original member name unknown.
  const fw::ParamList::unknown005 *unknown2e0;     // Inferred role: param entry; original member name unknown.
  const fw::ParamList::unknown005 *unknown2e8;     // Inferred role: param entry; original member name unknown.
  fw::SensorUpdater unknown2f0;                    // Inferred role: updater before the game; original member name unknown.
  fw::SensorUpdater unknown328;                    // Inferred role: updater after the animation; original member name unknown.
  mm::mtl::UniquePtr<GfEnemySensor> unknown360;    // Inferred role: enemy sensor; original member name unknown.
  void *unknown368;                                // Inferred role: viewer; original member name unknown.
  EnvListener unknown370;                          // Inferred role: viewer listener; original member name unknown.
};

static_assert(offsetof(GfComEnvSensor, unknown10) == 0x10, "");
static_assert(offsetof(GfComEnvSensor, unknown2b0) == 0x2b0, "");
static_assert(offsetof(GfComEnvSensor, unknown2c0) == 0x2c0, "");
static_assert(offsetof(GfComEnvSensor, unknown2d8) == 0x2d8, "");
static_assert(offsetof(GfComEnvSensor, unknown2f0) == 0x2f0, "");
static_assert(offsetof(GfComEnvSensor, unknown328) == 0x328, "");
static_assert(offsetof(GfComEnvSensor, unknown360) == 0x360, "");
static_assert(offsetof(GfComEnvSensor, unknown368) == 0x368, "");
static_assert(offsetof(GfComEnvSensor, unknown370) == 0x370, "");
static_assert(sizeof(GfComEnvSensor) == 0x380, "");

} // namespace gf
