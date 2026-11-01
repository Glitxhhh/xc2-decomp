#pragma once
#include <stddef.h>

#include "dr/dr_pixl_post_obj.h"
#include "mm_math/mm_vec2.h"
#include "types.h"

namespace ml {

class DrResUseQueryObj;

class DrPixlPostObjHistgram : public DrPixlPostObj {
public:
  ~DrPixlPostObjHistgram();
  void update();
  void render();
  f32 calcLuminanceAve(f32 rate, bool isLow) const;
  mm::Vec2 getSection(u32 index) const;
  f32 getMaxLuminance() const;
  int getSectionNum() const;
  f32 getPercentage(u32 index) const;

  DrResUseQueryObj *unknown18; // Inferred role: occlusion query; original member name unknown.
  f32 unknown20[11];           // Inferred role: section boundaries; original member name unknown.
  f32 m_percentage[11];
  u32 unknown78[11]; // Inferred role: sample counts; original member name unknown.
  s32 unknowna4;     // Inferred role: sample index; original member name unknown.
  s32 unknowna8;     // Inferred role: section mode; original member name unknown.
  f32 unknownac;     // Inferred role: tone ave max; original member name unknown.
  f32 unknownb0;     // Inferred role: tone ave min; original member name unknown.
  s32 unknownb4;     // Inferred role: reset frames; original member name unknown.
  bool unknownb8;    // Inferred role: valid tone ave range; original member name unknown.
};

static_assert(offsetof(DrPixlPostObjHistgram, unknown18) == 0x18, "");
static_assert(offsetof(DrPixlPostObjHistgram, unknown20) == 0x20, "");
static_assert(offsetof(DrPixlPostObjHistgram, m_percentage) == 0x4c, "");
static_assert(offsetof(DrPixlPostObjHistgram, unknown78) == 0x78, "");
static_assert(offsetof(DrPixlPostObjHistgram, unknowna4) == 0xa4, "");
static_assert(offsetof(DrPixlPostObjHistgram, unknownac) == 0xac, "");
static_assert(offsetof(DrPixlPostObjHistgram, unknownb4) == 0xb4, "");
static_assert(offsetof(DrPixlPostObjHistgram, unknownb8) == 0xb8, "");

} // namespace ml
