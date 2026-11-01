#pragma once
#include <stddef.h>

#include "layer/layer_obj.h"
#include "types.h"

namespace grlib {
class CGLibDblUniformBlock;
class CGLibVtxOneInstans;
} // namespace grlib

namespace layer {

class LayerFontIconObj;
class LayerFontResObj;
class LayerFontStyleObj;
class LayerSortObj;
struct LayerRenderView;
struct LayerResViewPortInfo;

// Inferred layout of one line of a font info (stride 0x10 in LayerFontDrawBuffer::fontCnt); original type and member names unknown.
struct unknown026 {
  u32 unknown00; // Inferred role: line width; original member name unknown.
  s16 unknown04; // Inferred role: first character instance; original member name unknown.
  s16 unknown06; // Inferred role: last character instance; original member name unknown.
  u8 _08[0x0c - 0x08];
  s16 unknown0c; // Inferred role: first icon instance; original member name unknown.
  s16 unknown0e; // Inferred role: last icon instance; original member name unknown.
};

static_assert(sizeof(unknown026) == 0x10, "");

struct LayerResFontInfo {
  u8 _00[0x08];
  const LayerFontResObj *unknown08; // Inferred role: font resource; original member name unknown.
  const u8 *unknown10;              // Inferred role: message; original member name unknown.
  u32 unknown18;                    // Inferred role: message length; original member name unknown.
  u8 _1c[0x2c - 0x1c];
  u32 unknown2c; // Inferred role: first icon instance; original member name unknown.
  u32 unknown30; // Inferred role: icon instance count; original member name unknown.
  u8 _34[0x38 - 0x34];
  LayerSortObj *unknown38; // Inferred role: sort object; original member name unknown.
  u32 unknown40;           // Inferred role: character instance count; original member name unknown.
  u8 _44[0x48 - 0x44];
  unknown026 *unknown48; // Inferred role: lines; original member name unknown.
  u8 _50[0x60 - 0x50];
  grlib::CGLibVtxOneInstans *unknown60;   // Inferred role: instance vertex; original member name unknown.
  grlib::CGLibDblUniformBlock *unknown68; // Inferred role: uniform block; original member name unknown.
};

static_assert(offsetof(LayerResFontInfo, unknown08) == 0x08, "");
static_assert(offsetof(LayerResFontInfo, unknown10) == 0x10, "");
static_assert(offsetof(LayerResFontInfo, unknown18) == 0x18, "");
static_assert(offsetof(LayerResFontInfo, unknown2c) == 0x2c, "");
static_assert(offsetof(LayerResFontInfo, unknown30) == 0x30, "");
static_assert(offsetof(LayerResFontInfo, unknown38) == 0x38, "");
static_assert(offsetof(LayerResFontInfo, unknown40) == 0x40, "");
static_assert(offsetof(LayerResFontInfo, unknown48) == 0x48, "");
static_assert(offsetof(LayerResFontInfo, unknown60) == 0x60, "");
static_assert(offsetof(LayerResFontInfo, unknown68) == 0x68, "");

class LayerObjFont : public LayerObj {
public:
  LayerObjFont();
  void workPartsRelease(LayerResFontInfo *&info);
  void workRelease();
  bool isMsg(const LayerResFontInfo *info, const u8 *msg) const;
  bool isMsg(const LayerResFontInfo *info, const wchar_t *msg) const;
  void updateAddDel();
  void updateShaderParms(const LayerRenderView *view, const LayerResMatrix &matrix, const LayerResColor &color);
  void setMsg(const u8 *text, const LayerFontResObj *res, const LayerFontStyleObj *style, const LayerFontIconObj *icon, u32 flags);
  void setMsg(const wchar_t *text, const LayerFontResObj *res, const LayerFontStyleObj *style, const LayerFontIconObj *icon, u32 flags);
  void setColorMap(const LayerFontIconObj *colorMap, u32 index);
  void setBorderWeight(f32 weight);
  void setSlopeRot(f32 rot);
  f32 getBorderWeight() const;
  f32 getSlopeRot() const;

  LayerResFontInfo *unknown250;        // Inferred role: current font info; original member name unknown.
  LayerResFontInfo *unknown258[2];     // Inferred role: font info per buffer; original member name unknown.
  LayerResFontInfo *unknown268;        // Inferred role: font info to release; original member name unknown.
  LayerResViewPortInfo *unknown270;    // Inferred role: view port; original member name unknown.
  const LayerFontResObj *unknown278;   // Inferred role: res; original member name unknown.
  const LayerFontStyleObj *unknown280; // Inferred role: style; original member name unknown.
  const LayerFontIconObj *unknown288;  // Inferred role: icon; original member name unknown.
  const LayerFontIconObj *m_colorMap;
  u32 unknown298; // Inferred role: msg flags; original member name unknown.
  u32 unknown29c; // Inferred role: color map index; original member name unknown.
  u16 unknown2a0; // Inferred role: font pixel x; original member name unknown.
  u16 unknown2a2; // Inferred role: font pixel y; original member name unknown.
  u16 unknown2a4; // Inferred role: font pixel width; original member name unknown.
  u16 unknown2a6; // Inferred role: font pixel height; original member name unknown.
  u32 unknown2a8; // Inferred role: horizontal; original member name unknown.
  u32 unknown2ac; // Inferred role: vertical; original member name unknown.
  u32 unknown2b0; // Inferred role: display area; original member name unknown.
  u32 unknown2b4; // Inferred role: disp setting; original member name unknown.
  f32 m_slopeRot;
  u16 unknown2bc; // Inferred role: mask of the border weights set per index; original member name unknown.
  f32 m_borderWeight;
  f32 unknown2c4[2]; // Inferred role: border weight per index; original member name unknown.
};

static_assert(offsetof(LayerObjFont, unknown250) == 0x250, "");
static_assert(offsetof(LayerObjFont, unknown258) == 0x258, "");
static_assert(offsetof(LayerObjFont, unknown268) == 0x268, "");
static_assert(offsetof(LayerObjFont, unknown270) == 0x270, "");
static_assert(offsetof(LayerObjFont, unknown278) == 0x278, "");
static_assert(offsetof(LayerObjFont, m_colorMap) == 0x290, "");
static_assert(offsetof(LayerObjFont, unknown298) == 0x298, "");
static_assert(offsetof(LayerObjFont, unknown29c) == 0x29c, "");
static_assert(offsetof(LayerObjFont, unknown2a0) == 0x2a0, "");
static_assert(offsetof(LayerObjFont, unknown2b4) == 0x2b4, "");
static_assert(offsetof(LayerObjFont, m_slopeRot) == 0x2b8, "");
static_assert(offsetof(LayerObjFont, unknown2bc) == 0x2bc, "");
static_assert(offsetof(LayerObjFont, m_borderWeight) == 0x2c0, "");
static_assert(offsetof(LayerObjFont, unknown2c4) == 0x2c4, "");

} // namespace layer
