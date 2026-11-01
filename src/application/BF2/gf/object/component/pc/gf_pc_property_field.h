#pragma once
#include <stddef.h>

#include "framework/message/message_object.h"
#include "fw/fw_param_manager.h"
#include "gf/object/component/env_sensor/gf_com_env_sensor.h"
#include "gf/object/component/pc/gf_pc_property_pc_interface.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace gf {

class GfComPropertyPc;

struct MsgPcFieldNotifyBigJump : fw::Message {
  mm::Vec3 unknown10;    // Inferred role: target position; original member name unknown.
  f32 unknown20;         // Role and original member name unknown.
  f32 unknown24;         // Role and original member name unknown.
  f32 unknown28;         // Role and original member name unknown.
  const void *unknown30; // Inferred role: gimmick bdat row; original member name unknown.
  u32 unknown38;         // Inferred role: gimmick id; original member name unknown.
  u32 unknown3c;         // Inferred role: gimmick id; original member name unknown.
};

static_assert(offsetof(MsgPcFieldNotifyBigJump, unknown10) == 0x10, "");
static_assert(offsetof(MsgPcFieldNotifyBigJump, unknown20) == 0x20, "");
static_assert(offsetof(MsgPcFieldNotifyBigJump, unknown30) == 0x30, "");
static_assert(offsetof(MsgPcFieldNotifyBigJump, unknown3c) == 0x3c, "");
static_assert(sizeof(MsgPcFieldNotifyBigJump) == 0x40, "");

struct MsgPcFieldNotifyWarp : fw::Message {
  mm::Vec3 unknown10;    // Inferred role: target position; original member name unknown.
  f32 unknown20;         // Role and original member name unknown.
  const void *unknown28; // Inferred role: gimmick bdat row; original member name unknown.
  u32 unknown30;         // Inferred role: gimmick id; original member name unknown.
  u32 unknown34;         // Inferred role: gimmick id; original member name unknown.
};

static_assert(offsetof(MsgPcFieldNotifyWarp, unknown10) == 0x10, "");
static_assert(offsetof(MsgPcFieldNotifyWarp, unknown20) == 0x20, "");
static_assert(offsetof(MsgPcFieldNotifyWarp, unknown28) == 0x28, "");
static_assert(offsetof(MsgPcFieldNotifyWarp, unknown34) == 0x34, "");
static_assert(sizeof(MsgPcFieldNotifyWarp) == 0x40, "");

struct MsgPcFieldNotifyWallJump : fw::Message {
  mm::Vec3 unknown10;    // Inferred role: target position; original member name unknown.
  const void *unknown20; // Inferred role: gimmick bdat row; original member name unknown.
  u32 unknown28;         // Inferred role: gimmick id; original member name unknown.
  u32 unknown2c;         // Inferred role: gimmick id passed to SCOM_QUEST_GIMMICK::createJump; original member name unknown.
};

static_assert(offsetof(MsgPcFieldNotifyWallJump, unknown10) == 0x10, "");
static_assert(offsetof(MsgPcFieldNotifyWallJump, unknown20) == 0x20, "");
static_assert(offsetof(MsgPcFieldNotifyWallJump, unknown2c) == 0x2c, "");
static_assert(sizeof(MsgPcFieldNotifyWallJump) == 0x30, "");

namespace pc {
struct FieldParam;
struct WaterCommonParam;

class GfPropertyField : public GfPropertyPcInterface {
public:
  enum WALL_MOVE_MODE {
    WALL_MOVE_MODE_INVALID = -1,
    WALL_MOVE_MODE_UP = 0,
    WALL_MOVE_MODE_UP_RIGHT = 1,
    WALL_MOVE_MODE_RIGHT = 2,
    WALL_MOVE_MODE_DOWN_RIGHT = 3,
    WALL_MOVE_MODE_DOWN = 4,
    WALL_MOVE_MODE_DOWN_LEFT = 5,
    WALL_MOVE_MODE_LEFT = 6,
    WALL_MOVE_MODE_UP_LEFT = 7,
  };

  void setup(const GfComPropertyPc &property) override;
  void cleanup(const GfComPropertyPc &property) override;
  void flush(const GfComPropertyPc &property) override;
  void flushOwner(GfComPropertyPc &property) override;
  bool recieveMessage(const GfComPropertyPc &property, fw::MessageObject *sender, fw::Message &message) override;
  void resetStatus(const GfComPropertyPc &property);
  void setBigJumpInfo(const MsgPcFieldNotifyBigJump *message);
  const MsgPcFieldNotifyBigJump *getBigJumpInfo() const;
  void setWarpInfo(const MsgPcFieldNotifyWarp *message);
  const MsgPcFieldNotifyWarp *getWarpInfo() const;
  void setWallJump(const MsgPcFieldNotifyWallJump *message);
  const MsgPcFieldNotifyWallJump *getWallJumpInfo() const;
  f32 getWallHeightOffset() const;

  // Inferred role: field param of the param list entry 0 ("common"); original name unknown.
  const FieldParam *unknown001() const { return static_cast<const FieldParam *>(unknown08->unknown10[0].param); }
  // Inferred role: water param of the param list entry 9 ("water_common"); original name unknown.
  const WaterCommonParam *unknown002() const { return static_cast<const WaterCommonParam *>(unknown08->unknown10[9].param); }

  mm::mtl::IntrusivePtr<fw::ParamList> unknown08; // Inferred role: param list; original member name unknown.
  u32 unknown10_0 : 1;                            // Inferred role: walk mode; original member name unknown.
  u32 : 1;
  u32 unknown10_2 : 1; // Inferred role: idle; original member name unknown.
  u32 unknown10_3 : 1; // Inferred role: pad control; original member name unknown.
  u32 : 2;
  u32 unknown10_6 : 1; // Inferred role: climb wall info valid; original member name unknown.
  u32 unknown10_7 : 1; // Inferred role: wall up move lock; original member name unknown.
  u32 unknown11_0 : 1; // Inferred role: auto run; original member name unknown.
  u32 unknown11_1 : 1; // Inferred role: air; original member name unknown.
  u32 unknown11_2 : 1; // Inferred role: special action; original member name unknown.
  u32 unknown11_3 : 1; // Inferred role: slide; original member name unknown.
  u32 unknown11_4 : 1; // Inferred role: big jump info valid; original member name unknown.
  u32 unknown11_5 : 1; // Inferred role: warp info valid; original member name unknown.
  u32 unknown11_6 : 1; // Inferred role: wall jump info valid; original member name unknown.
  u32 : 1;
  u32 unknown12_0 : 1; // Inferred role: under ground wall adsorption; original member name unknown.
  u32 unknown12_1 : 1; // Inferred role: field status reset; original member name unknown.
  u32 : 14;
  WALL_MOVE_MODE unknown14; // Inferred role: wall move mode; original member name unknown.
  f32 unknown18;            // Inferred role: wall float; original member name unknown.
  u8 _1c[0x28 - 0x1c];
  f32 unknown28; // Inferred role: wall height; original member name unknown.
  u8 _2c[0x38 - 0x2c];
  f32 unknown38; // Inferred role: wall detach distance; original member name unknown.
  u8 _3c[0x80 - 0x3c];
  MsgPcFieldNotifyBigJump unknown80;       // Inferred role: big jump info; original member name unknown.
  MsgPcFieldNotifyWarp unknownc0;          // Inferred role: warp info; original member name unknown.
  MsgPcFieldNotifyWallJump unknown100;     // Inferred role: wall jump info; original member name unknown.
  EnviromentSensor::unknown003 unknown130; // Inferred role: climb wall info; original member name unknown.
};

static_assert(offsetof(GfPropertyField, unknown08) == 0x08, "");
static_assert(offsetof(GfPropertyField, unknown14) == 0x14, "");
static_assert(offsetof(GfPropertyField, unknown18) == 0x18, "");
static_assert(offsetof(GfPropertyField, unknown28) == 0x28, "");
static_assert(offsetof(GfPropertyField, unknown38) == 0x38, "");
static_assert(offsetof(GfPropertyField, unknown80) == 0x80, "");
static_assert(offsetof(GfPropertyField, unknownc0) == 0xc0, "");
static_assert(offsetof(GfPropertyField, unknown100) == 0x100, "");
static_assert(offsetof(GfPropertyField, unknown130) == 0x130, "");
static_assert(sizeof(GfPropertyField) == 0x160, "");

} // namespace pc
} // namespace gf
