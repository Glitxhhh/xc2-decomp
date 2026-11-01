#pragma once
#include <stddef.h>

#include "ml/cache_draw.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace grlib {
class CGLibVtxVertex;
} // namespace grlib

namespace ml {

class DebDrawCmd : public DebDraw {
public:
  // Inferred role: vertex written to the locked vertex buffer, 0x18 bytes from the stride given to createVertexBuff; original type name unknown.
  struct unknown001 {
    // Inferred helper: sets the position; original name unknown.
    void unknown003(const mm::Vec3 &position) {
      unknown00 = position.x;
      unknown04 = position.y;
      unknown08 = position.z;
    }

    // Inferred helper: sets the color as bytes; original name unknown.
    void unknown004(const mm::Col4 &color) {
      unknown0c = color.r * 255.0f;
      unknown0d = color.g * 255.0f;
      unknown0e = color.b * 255.0f;
      unknown0f = color.a * 255.0f;
    }

    // Inferred helper: sets the texture coordinates; original name unknown.
    void unknown005(f32 u, f32 v) {
      unknown10 = u;
      unknown14 = v;
    }

    f32 unknown00; // Inferred role: position x; original member name unknown.
    f32 unknown04; // Inferred role: position y; original member name unknown.
    f32 unknown08; // Inferred role: position z; original member name unknown.
    u8 unknown0c;  // Inferred role: red; original member name unknown.
    u8 unknown0d;  // Inferred role: green; original member name unknown.
    u8 unknown0e;  // Inferred role: blue; original member name unknown.
    u8 unknown0f;  // Inferred role: alpha; original member name unknown.
    f32 unknown10; // Inferred role: texture u; original member name unknown.
    f32 unknown14; // Inferred role: texture v; original member name unknown.
  };

  DebDrawCmd();
  ~DebDrawCmd() override;
  void fastSetup() override;
  void restoreShader() override {}
  void begin(u32 primitive, u32 count) override;
  void end() override;
  void add(const mm::Vec3 &first, const mm::Vec3 &second) override;
  void add(const mm::Pnt<int> &first, const mm::Pnt<int> &second) override;
  void add(int x1, int y1, int x2, int y2) override;
  void add(const mm::Vec3 &position) override;
  void add(const mm::Pnt<int> &position) override;
  void add(f32 x, f32 y, f32 z) override;
  void add(int x, int y, int z) override;
  void add(int x, int y) override;
  void add(const mm::Vec3 &position, const mm::Col4 &color) override;
  void add(const mm::Vec3 &position, const mm::Col3 &color) override;
  void add(int x, int y, const mm::Col4 &color) override;
  void add(int x, int y, const mm::Col3 &color) override;
  void add(const mm::Vec3 &position, const mm::Vec3 &texCoord, const mm::Col4 &color) override;
  void add(const mm::Rect<int> &rect) override;
  void add(const mm::Vec3 &first, const mm::Vec3 &second, const mm::Vec3 &third) override;
  void initialize();
  void release();
  void setVertex(const mm::Vec3 &position, const mm::Col4 &color, f32 u, f32 v);
  static u32 thInitialize(void *argument, void *userData);
  static u32 thDestroy(void *argument, void *userData);
  // Inferred helper: position relative to the perspective position, transformed in place by the model matrix; original name unknown.
  void unknown002(mm::Vec3 &result, const mm::Vec3 &position) const {
    result = position - unknown160;
    f32 x = result.x * unknownc0.rows[0][0] + result.y * unknownc0.rows[1][0] + result.z * unknownc0.rows[2][0] + unknownc0.rows[3][0];
    f32 y = result.x * unknownc0.rows[0][1] + result.y * unknownc0.rows[1][1] + result.z * unknownc0.rows[2][1] + unknownc0.rows[3][1];
    result.z = result.x * unknownc0.rows[0][2] + result.y * unknownc0.rows[1][2] + result.z * unknownc0.rows[2][2] + unknownc0.rows[3][2];
    result.x = x;
    result.y = y;
  }

  bool unknown219;      // Inferred role: unknown, cleared by the constructor; original member name unknown.
  mm::Col4 unknown21c;  // Inferred role: color, white by default; original member name unknown.
  mm::Vec3 unknown230;  // Inferred role: direction, unit Y by default; original member name unknown.
  mm::Col4 unknown240;  // Inferred role: color, white by default; original member name unknown.
  mm::Col4 unknown250;  // Inferred role: color, white by default; original member name unknown.
  mm::Col4 unknown260;  // Inferred role: color, white by default; original member name unknown.
  bool unknown270;      // Inferred role: unknown, cleared by the constructor; original member name unknown.
  mm::Mat44 unknown280; // Inferred role: view projection matrix sent as U_MDL; original member name unknown.
  u8 _2c0[0x2d0 - 0x2c0];
  grlib::CGLibVtxVertex *unknown2d0; // Inferred role: vertex buffer; original member name unknown.
  u32 unknown2d8;                    // Inferred role: offset of the first vertex not yet unlocked; original member name unknown.
  u32 unknown2dc;                    // Inferred role: write offset; original member name unknown.
  u32 unknown2e0;                    // Inferred role: vertex buffer size; original member name unknown.
  void *unknown2e8;                  // Inferred role: write pointer into the locked vertex buffer; original member name unknown.
  bool unknown2f0;                   // Inferred role: second half of the vertex buffer in use; original member name unknown.
};

static_assert(offsetof(DebDrawCmd, unknown219) == 0x219, "");
static_assert(offsetof(DebDrawCmd, unknown21c) == 0x21c, "");
static_assert(offsetof(DebDrawCmd, unknown230) == 0x230, "");
static_assert(offsetof(DebDrawCmd, unknown240) == 0x240, "");
static_assert(offsetof(DebDrawCmd, unknown270) == 0x270, "");
static_assert(offsetof(DebDrawCmd, unknown280) == 0x280, "");
static_assert(offsetof(DebDrawCmd, unknown2d0) == 0x2d0, "");
static_assert(offsetof(DebDrawCmd, unknown2d8) == 0x2d8, "");
static_assert(offsetof(DebDrawCmd, unknown2e0) == 0x2e0, "");
static_assert(offsetof(DebDrawCmd, unknown2e8) == 0x2e8, "");
static_assert(offsetof(DebDrawCmd, unknown2f0) == 0x2f0, "");
static_assert(sizeof(DebDrawCmd) == 0x300, "");
static_assert(sizeof(DebDrawCmd::unknown001) == 0x18, "");

} // namespace ml
