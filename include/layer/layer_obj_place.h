#pragma once
#include <stddef.h>

#include "layer/layer_act_def.h"
#include "types.h"

namespace layer {
struct LayerResNode;

struct LyrPlaceData {
  s32 unknown00;    // Inferred role: key count; original member name unknown.
  u32 unknown04;    // Inferred role: offset of the keys in the place resource data; original member name unknown.
  u32 unknown08[4]; // Inferred role: offsets of the first source values; original member name unknown.
  u32 unknown18[4]; // Inferred role: offsets of the second source values; original member name unknown.
  u8 unknown28[4];  // Inferred role: value types; original member name unknown.
  u8 unknown2c[4];  // Inferred role: format indices; original member name unknown.
  u16 unknown30;    // Inferred role: format count; original member name unknown.
  u8 unknown32;     // Inferred role: flags; original member name unknown.
  u8 _33[0x34 - 0x33];
  u16 unknown34; // Inferred role: frame of the last key; original member name unknown.
  u8 _36[0x38 - 0x36];
  u16 unknown38; // Inferred role: end frame; original member name unknown.
  u16 unknown3a; // Inferred role: start frame; original member name unknown.
  u16 unknown3c; // Inferred role: loop frame; original member name unknown.
  u8 _3e[0x40 - 0x3e];
};

static_assert(offsetof(LyrPlaceData, unknown04) == 0x04, "");
static_assert(offsetof(LyrPlaceData, unknown28) == 0x28, "");
static_assert(offsetof(LyrPlaceData, unknown30) == 0x30, "");
static_assert(offsetof(LyrPlaceData, unknown32) == 0x32, "");
static_assert(offsetof(LyrPlaceData, unknown34) == 0x34, "");
static_assert(offsetof(LyrPlaceData, unknown38) == 0x38, "");
static_assert(offsetof(LyrPlaceData, unknown3c) == 0x3c, "");
static_assert(sizeof(LyrPlaceData) == 0x40, "");

// Inferred layout of a place key, read by LayerObjPlace::calcNodePos; original type and member names unknown.
struct unknown086 {
  u16 unknown00; // Inferred role: frame; original member name unknown.
  u16 unknown02; // Inferred role: flags, bit 0 hides the node; original member name unknown.
};

static_assert(sizeof(unknown086) == 0x04, "");

// Inferred layout of a draw entry of the def object (stride 8 in LayerObjPlace::calcNodePos); original type and member names unknown.
struct unknown087 {
  u8 unknown00;  // Inferred role: flags, bit 0 gives the entry its own frame; original member name unknown.
  u8 unknown01;  // Inferred role: reset type; original member name unknown.
  u16 unknown02; // Inferred role: frame param index; original member name unknown.
  s16 unknown04; // Inferred role: parent node index, -1 for none; original member name unknown.
  s16 unknown06; // Inferred role: place data index; original member name unknown.
};

static_assert(offsetof(unknown087, unknown04) == 0x04, "");
static_assert(sizeof(unknown087) == 0x08, "");

// Evidence: the vtable holds LayerActDef::updatePartsAction.
class LayerObjPlace : public LayerActDef {
public:
  LayerObjPlace();
  void updatePlace();
  f32 updateGblFrm();
  void calcNodePos(f32 frame);
  void calcPartsNodePos(LayerResNode *node, const LyrPlaceData *data, s32 index);
  static void placeReset_Off(LayerResNode *node);
  static void placeReset_Pos(LayerResNode *node);
  static void placeReset_Srt(LayerResNode *node);
  static void placeReset_Pos_Srt(LayerResNode *node);
  static void placeReset_Col(LayerResNode *node);
  static void placeReset_Pos_Col(LayerResNode *node);
  static void placeReset_Srt_Col(LayerResNode *node);
  static void placeReset_Pos_Srt_Col(LayerResNode *node);
  static void placeFormat_u8(LayerResNode *node, int type, const u8 *data, const u8 *values, u32 index);
  static void placeFormat_u16(LayerResNode *node, int type, const u8 *data, const u8 *values, u32 index);
  static void placeFormat_u32(LayerResNode *node, int type, const u8 *data, const u8 *values, u32 index);
  static void placeAnm_Pos(LayerResNode *node, const u8 *data, u32 index);
  static void placeAnm_Scl(LayerResNode *node, const u8 *data, u32 index);
  static void placeAnm_Rot(LayerResNode *node, const u8 *data, u32 index);
  static void placeAnm_Srt(LayerResNode *node, const u8 *data, u32 index);
  static void placeAnm_AddCol(LayerResNode *node, const u8 *data, u32 index);
  static void placeAnm_MulCol(LayerResNode *node, const u8 *data, u32 index);
  static void placeAnm_AllCol(LayerResNode *node, const u8 *data, u32 index);
  static void placeAnm_Blend(LayerResNode *node, const u8 *data, u32 index);

  static void (*s_resCallPlaceReset[])(LayerResNode *node);
  static void (*s_resCallPlaceFormat[])(LayerResNode *node, int type, const u8 *data, const u8 *values, u32 index);
  static void (*s_resCallPlaceAnim[])(LayerResNode *node, const u8 *data, u32 index);
};

} // namespace layer
