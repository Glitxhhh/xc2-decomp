#pragma once
#include <stddef.h>

#include "ml/dev_pad.h"
#include "mm_mtl/unique_ptr.h"
#include "types.h"

namespace ml {
class WorkObj;

class DevPadNx : public DevPad {
public:
  class Impl {
  public:
    // Inferred role: pad button flag; original type name unknown.
    enum unknown001 {
      unknown001_0 = 1 << 0,
      unknown001_1 = 1 << 1,
      unknown001_2 = 1 << 2,
      unknown001_3 = 1 << 3,
      unknown001_4 = 1 << 4,
      unknown001_5 = 1 << 5,
      unknown001_6 = 1 << 6,
      unknown001_7 = 1 << 7,
      unknown001_8 = 1 << 8,
      unknown001_9 = 1 << 9,
      unknown001_12 = 1 << 12,
      unknown001_13 = 1 << 13,
      unknown001_14 = 1 << 14,
      unknown001_15 = 1 << 15,
    };

    // Evidence for the size: Impl::Impl constructs two FixedArray<PadData, 4> at 0x3638 and 0x3c38.
    struct PadData {
      u32 unknown00;  // Inferred role: button flags; original member name unknown.
      f32 unknown04;  // Inferred role: left stick x; original member name unknown.
      f32 unknown08;  // Inferred role: left stick y; original member name unknown.
      f32 unknown0c;  // Inferred role: right stick x; original member name unknown.
      f32 unknown10;  // Inferred role: right stick y; original member name unknown.
      bool unknown14; // Inferred role: connected; original member name unknown.
      u8 _15[0x18 - 0x15];
      u32 unknown18; // Inferred role: pad style; original member name unknown.
      u8 _1c[0x180 - 0x1c];
    };

    void stateUpdate(f32 time);
    void updatePad(f32 time);
    void updateNpad();
    void updateDebugPad(PadData &data);
    void release();

    u8 _0000[0x0020];
    s32 unknown20;    // Inferred role: state of the pad update, 2 updates the npads; original member name unknown.
    u32 unknown24[4]; // Inferred role: npad ids of the pads; original member name unknown.
    u8 _0034[0x4540 - 0x0034];
    s32 unknown4540; // Inferred role: pad index; original member name unknown.
    s32 unknown4544; // Inferred role: user select pad id; original member name unknown.
  };

  DevPadNx(const char *name, WorkObj *parent);
  static void setUserSelectControllerID(u32 id);
  bool isLocalConnect(int padNo) const override;
  u32 getLocalStyle(int padNo) const override;
  int getLocalUserSelectPadID() const override;
  u32 getLocalBtn(int padNo) const override;
  f32 getLocalALX(int padNo) const override;
  f32 getLocalALY(int padNo) const override;
  f32 getLocalARX(int padNo) const override;
  f32 getLocalARY(int padNo) const override;
  void updateDevice(f32 time) override;
  bool createDevice() override;
  void releaseDevice() override;

  mm::mtl::UniquePtr<Impl> unknown548; // Inferred role: implementation; original member name unknown.
};

static_assert(offsetof(DevPadNx::Impl::PadData, unknown04) == 0x04, "");
static_assert(offsetof(DevPadNx::Impl::PadData, unknown10) == 0x10, "");
static_assert(offsetof(DevPadNx::Impl::PadData, unknown14) == 0x14, "");
static_assert(offsetof(DevPadNx::Impl::PadData, unknown18) == 0x18, "");
static_assert(sizeof(DevPadNx::Impl::PadData) == 0x180, "");
static_assert(offsetof(DevPadNx::Impl, unknown20) == 0x0020, "");
static_assert(offsetof(DevPadNx::Impl, unknown24) == 0x0024, "");
static_assert(offsetof(DevPadNx::Impl, unknown4540) == 0x4540, "");
static_assert(offsetof(DevPadNx::Impl, unknown4544) == 0x4544, "");
static_assert(offsetof(DevPadNx, unknown548) == 0x548, "");

} // namespace ml
