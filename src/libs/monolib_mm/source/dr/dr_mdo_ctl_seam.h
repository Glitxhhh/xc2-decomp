#pragma once
#include <stddef.h>

#include "dr/dr_mdl_obj.h"
#include "dr/dr_res_mdo_inst_anm_obj.h"
#include "dr/dr_res_mdo_seam_mem_man.h"
#include "types.h"

namespace ml {
class DrResMdoSeamColi;
class DrResMdoSeamTexList;
class DrResMdoSeamTexture;
class DrResMdoSeamVertex;
class DrResMdoSeamWrkBase;
class DrResMdoSeamWrkEnv;
class DrResMdoSeamWrkInst;
class DrResMdoSeamWrkLight;
class DrResMdoSeamWrkLow;
class DrResMdoSeamWrkMpf;
struct MdoWrkMatRes;

// Inferred role: model data seam etc pos data; original type name unknown.
struct unknown058 {
  u32 unknown00;    // Inferred role: object name offset; original member name unknown.
  u32 unknown04;    // Inferred role: eff name offset; original member name unknown.
  f32 unknown08;    // Inferred role: range; original member name unknown.
  u32 unknown0c;    // Inferred role: matrix max; original member name unknown.
  u32 unknown10;    // Inferred role: matrix offset; original member name unknown.
  f32 unknown14[2]; // Inferred role: near clips; original member name unknown.
  f32 unknown1c[2]; // Inferred role: far clips; original member name unknown.
  u32 unknown24;    // Inferred role: groups offset; original member name unknown.
};

static_assert(offsetof(unknown058, unknown10) == 0x10, "");
static_assert(offsetof(unknown058, unknown14) == 0x14, "");
static_assert(offsetof(unknown058, unknown1c) == 0x1c, "");
static_assert(offsetof(unknown058, unknown24) == 0x24, "");

// Inferred role: seam etc pos; original type name unknown.
struct unknown059 {
  const unknown058 *unknown00; // Inferred role: data; original member name unknown.
  bool unknown08;              // Inferred role: always disp; original member name unknown.
};

static_assert(sizeof(unknown059) == 0x10, "");

// Inferred role: seam etc pos list; original type name unknown.
struct unknown060 {
  unknown059 *unknown00; // Inferred role: objs; original member name unknown.
  u32 unknown08;         // Inferred role: object max; original member name unknown.
};

// Inferred role: seam resource header; original type name unknown.
struct unknown061 {
  u8 _00[0x18];
  u32 m_seamBaseMdlMax;
  u8 _1c[0x20 - 0x1c];
  u32 m_seamInstMdlMax;
  u8 _24[0x28 - 0x24];
  u32 m_seamColiMax;
  u8 _2c[0x44 - 0x2c];
  u32 m_seamShaderMax;
  u8 _48[0x50 - 0x48];
  u32 m_seamVertexMax;
  u8 _54[0x58 - 0x54];
  u32 m_seamTextureMax;
  u8 _5c[0x64 - 0x5c];
  u32 m_seamMpfMdlMax;
  u8 _68[0x6c - 0x68];
  u32 m_seamEtcPosDataMax;
  u8 _70[0x74 - 0x70];
  u32 m_seamMpfPosDataMax;
};

static_assert(offsetof(unknown061, m_seamBaseMdlMax) == 0x18, "");
static_assert(offsetof(unknown061, m_seamInstMdlMax) == 0x20, "");
static_assert(offsetof(unknown061, m_seamColiMax) == 0x28, "");
static_assert(offsetof(unknown061, m_seamShaderMax) == 0x44, "");
static_assert(offsetof(unknown061, m_seamVertexMax) == 0x50, "");
static_assert(offsetof(unknown061, m_seamTextureMax) == 0x58, "");
static_assert(offsetof(unknown061, m_seamMpfMdlMax) == 0x64, "");
static_assert(offsetof(unknown061, m_seamEtcPosDataMax) == 0x6c, "");
static_assert(offsetof(unknown061, m_seamMpfPosDataMax) == 0x74, "");

// Inferred role: doubly linked list of seam objects (unknown08 next, unknown10 prev); original type name unknown.
template <typename T> struct unknown093 {
  T *unknown00; // Inferred role: first object; original member name unknown.
  T *unknown08; // Inferred role: last object; original member name unknown.
};

// Inferred role: seam object pool with a free list and a used list; original type name unknown.
template <typename T> struct unknown094 {
  // Inferred helper: moves the first free object to the end of the used list; original name unknown.
  T *unknown001() {
    T *obj = unknown00.unknown00;
    if (obj != nullptr) {
      T *next = obj->unknown08;
      if (next == nullptr) {
        unknown00.unknown00 = nullptr;
        unknown00.unknown08 = nullptr;
      } else {
        unknown00.unknown00 = next;
        next->unknown10 = nullptr;
      }
      if (unknown10.unknown08 != nullptr) {
        unknown10.unknown08->unknown08 = obj;
      }
      if (unknown10.unknown00 == nullptr) {
        unknown10.unknown00 = obj;
      }
      obj->unknown10 = unknown10.unknown08;
      obj->unknown08 = nullptr;
      unknown10.unknown08 = obj;
      unknown2c--;
      unknown28++;
    }
    return obj;
  }

  // Inferred helper: moves a used object to the end of the free list; original name unknown.
  void unknown002(T *obj) {
    T *next = obj->unknown08;
    T *prev = obj->unknown10;
    if (next == nullptr) {
      if (prev != nullptr) {
        prev->unknown08 = nullptr;
      }
    } else {
      if (prev != nullptr) {
        prev->unknown08 = next;
      }
      next->unknown10 = prev;
    }
    if (unknown10.unknown08 == obj) {
      unknown10.unknown08 = prev;
    }
    if (unknown10.unknown00 == obj) {
      unknown10.unknown00 = next;
      if (next != nullptr) {
        next->unknown10 = nullptr;
      }
    }
    if (unknown00.unknown08 == nullptr) {
      unknown00.unknown00 = obj;
      unknown00.unknown08 = obj;
      obj->unknown10 = nullptr;
    } else {
      unknown00.unknown08->unknown08 = obj;
      obj->unknown10 = unknown00.unknown08;
      unknown00.unknown08 = obj;
    }
    obj->unknown08 = nullptr;
    unknown2c++;
    unknown28--;
  }

  unknown093<T> unknown00; // Inferred role: free objects; original member name unknown.
  unknown093<T> unknown10; // Inferred role: used objects; original member name unknown.
  u8 _20[0x28 - 0x20];
  s32 unknown28; // Inferred role: used object count; original member name unknown.
  s32 unknown2c; // Inferred role: free object count; original member name unknown.
  u8 _30[0x38 - 0x30];
};

static_assert(offsetof(unknown094<DrResMdoSeamTexture>, unknown10) == 0x10, "");
static_assert(offsetof(unknown094<DrResMdoSeamTexture>, unknown28) == 0x28, "");
static_assert(sizeof(unknown094<DrResMdoSeamTexture>) == 0x38, "");

class DrMdoCtlSeam : public DrMdlObj {
public:
  void *getColiListTbl();
  u32 getColiListMax();
  u32 isRead(int index) const;
  void setErrCode(int code, int param);
  static int calcSemaAlignment(u32 size, u32 alignment);
  void seamZPrePassBegin();
  void seamZPrePassEnd();
  void seamThicknessPassEnd(bool value);
  DrResMdoSeamTexture *createFreeSeamTexture();
  DrResMdoSeamTexList *createFreeSeamTexList();
  DrResMdoSeamVertex *createFreeSeamVertex();
  void releaseFreeSeamTexture(DrResMdoSeamTexture *texture, bool isAll);
  void releaseFreeSeamTexList(DrResMdoSeamTexList *texList, bool isAll);
  void releaseFreeSeamVertex(DrResMdoSeamVertex *vertex, bool isAll);
  DrResMdoSeamColi *createFreeSeamCollision();

  u8 _190[0x1a8 - 0x190];
  unknown061 *unknown1a8;                      // Inferred role: seam resource header; original member name unknown.
  unknown094<DrResMdoSeamTexture> unknown1b0;  // Inferred role: texture pool; original member name unknown.
  unknown094<DrResMdoSeamTexList> unknown1e8;  // Inferred role: texture list pool; original member name unknown.
  unknown094<DrResMdoSeamVertex> unknown220;   // Inferred role: vertex pool; original member name unknown.
  unknown094<DrResMdoSeamColi> unknown258;     // Inferred role: collision pool; original member name unknown.
  unknown094<DrResMdoSeamWrkBase> unknown290;  // Inferred role: base map pool; original member name unknown.
  unknown094<DrResMdoSeamWrkLow> unknown2c8;   // Inferred role: low map pool; original member name unknown.
  unknown094<DrResMdoSeamWrkInst> unknown300;  // Inferred role: inst map pool; original member name unknown.
  unknown094<DrResMdoSeamWrkMpf> unknown338;   // Inferred role: mpf map pool; original member name unknown.
  unknown094<DrResMdoSeamWrkEnv> unknown370;   // Inferred role: env map pool; original member name unknown.
  unknown094<DrResMdoSeamWrkLight> unknown3a8; // Inferred role: light pool; original member name unknown.
  u8 _3e0[0x640 - 0x3e0];
  void *unknown640[2]; // Inferred role: collision list tables per buffer; original member name unknown.
  u32 unknown650[2];   // Inferred role: collision list max per buffer; original member name unknown.
  u8 _658[0x698 - 0x658];
  DrResMdoInstAnmObj unknown698; // Inferred role: inst anm object; original member name unknown.
  unknown060 unknown6c8;         // Inferred role: etc pos list; original member name unknown.
  u8 _6d8[0x6e0 - 0x6d8];
  DrResMdoSeamMemMan unknown6e0; // Inferred role: seam memory manager; original member name unknown.
  u8 _6e8[0xb38 - 0x6e8];
  MdoWrkMatRes *unknownb38; // Inferred role: saved mat res; original member name unknown.
  u8 _b40[0xb50 - 0xb40];
  u32 *unknownb50; // Inferred role: base map read bits; original member name unknown.
  u8 _b58[0xb60 - 0xb58];
  u32 *unknownb60; // Inferred role: base map render bits; original member name unknown.
  u8 _b68[0xb70 - 0xb68];
  u32 *unknownb70; // Inferred role: low map read bits; original member name unknown.
  u8 _b78[0xb80 - 0xb78];
  u32 *unknownb80; // Inferred role: inst map read bits; original member name unknown.
  u8 _b88[0xb90 - 0xb88];
  u32 *unknownb90; // Inferred role: mpf map read bits; original member name unknown.
  u8 _b98[0xba0 - 0xb98];
  u32 *unknownba0; // Inferred role: env map read bits; original member name unknown.
  u8 _ba8[0xbc0 - 0xba8];
  u32 *unknownbc0; // Inferred role: light read bits; original member name unknown.
  u8 _bc8[0xbd0 - 0xbc8];
  u16 *unknownbd0; // Inferred role: vertex use flags per seam index; original member name unknown.
  u8 _bd8[0xbe0 - 0xbd8];
  u16 *unknownbe0; // Inferred role: texture use flags per seam index; original member name unknown.
  u8 _be8[0xbf0 - 0xbe8];
  u16 *unknownbf0; // Inferred role: texture list use flags per seam index; original member name unknown.
  u8 _bf8[0xc00 - 0xbf8];
  s16 unknownc00; // Inferred role: base map read count; original member name unknown.
  s16 unknownc02; // Inferred role: low map read count; original member name unknown.
  s16 unknownc04; // Inferred role: inst map read count; original member name unknown.
  s16 unknownc06; // Inferred role: mpf map read count; original member name unknown.
  s16 unknownc08; // Inferred role: env map read count; original member name unknown.
  u8 _c0a[0xc0c - 0xc0a];
  s16 unknownc0c; // Inferred role: light read count; original member name unknown.
  u8 _c0e[0xc40 - 0xc0e];
  s32 unknownc40; // Inferred role: base map object count; original member name unknown.
  s32 unknownc44; // Inferred role: low map object count; original member name unknown.
  s32 unknownc48; // Inferred role: inst map memory size; original member name unknown.
  s32 unknownc4c; // Inferred role: mpf map memory size; original member name unknown.
  s32 unknownc50; // Inferred role: env map object count; original member name unknown.
  u8 _c54[0xc6c - 0xc54];
  s32 unknownc6c; // Inferred role: light memory size; original member name unknown.
  u8 _c70[0xc7c - 0xc70];
  u32 unknownc7c; // Inferred role: seam flags; original member name unknown.
  u8 _c80[0xcac - 0xc80];
  s16 unknowncac;    // Inferred role: error code write index; original member name unknown.
  s16 unknowncae[4]; // Inferred role: error codes; original member name unknown.
  u8 _cb6[0xcb8 - 0xcb6];
  u32 unknowncb8[4]; // Inferred role: error parameters; original member name unknown.
  u8 _cc8[0xd1a - 0xcc8];
  u16 unknownd1a; // Inferred role: read bits; original member name unknown.
};

static_assert(offsetof(DrMdoCtlSeam, unknown1a8) == 0x1a8, "");
static_assert(offsetof(DrMdoCtlSeam, unknown1b0) == 0x1b0, "");
static_assert(offsetof(DrMdoCtlSeam, unknown1e8) == 0x1e8, "");
static_assert(offsetof(DrMdoCtlSeam, unknown220) == 0x220, "");
static_assert(offsetof(DrMdoCtlSeam, unknown290) == 0x290, "");
static_assert(offsetof(DrMdoCtlSeam, unknown2c8) == 0x2c8, "");
static_assert(offsetof(DrMdoCtlSeam, unknown300) == 0x300, "");
static_assert(offsetof(DrMdoCtlSeam, unknown370) == 0x370, "");
static_assert(offsetof(DrMdoCtlSeam, unknown3a8) == 0x3a8, "");
static_assert(offsetof(DrMdoCtlSeam, unknown258) == 0x258, "");
static_assert(offsetof(DrMdoCtlSeam, unknown338) == 0x338, "");
static_assert(offsetof(DrMdoCtlSeam, unknownbc0) == 0xbc0, "");
static_assert(offsetof(DrMdoCtlSeam, unknownc0c) == 0xc0c, "");
static_assert(offsetof(DrMdoCtlSeam, unknownc6c) == 0xc6c, "");
static_assert(offsetof(DrMdoCtlSeam, unknownb90) == 0xb90, "");
static_assert(offsetof(DrMdoCtlSeam, unknownc06) == 0xc06, "");
static_assert(offsetof(DrMdoCtlSeam, unknownc4c) == 0xc4c, "");
static_assert(offsetof(DrMdoCtlSeam, unknown640) == 0x640, "");
static_assert(offsetof(DrMdoCtlSeam, unknownc40) == 0xc40, "");
static_assert(offsetof(DrMdoCtlSeam, unknownc44) == 0xc44, "");
static_assert(offsetof(DrMdoCtlSeam, unknownc50) == 0xc50, "");
static_assert(offsetof(DrMdoCtlSeam, unknown650) == 0x650, "");
static_assert(offsetof(DrMdoCtlSeam, unknowncac) == 0xcac, "");
static_assert(offsetof(DrMdoCtlSeam, unknowncae) == 0xcae, "");
static_assert(offsetof(DrMdoCtlSeam, unknowncb8) == 0xcb8, "");
static_assert(offsetof(DrMdoCtlSeam, unknownd1a) == 0xd1a, "");
static_assert(offsetof(DrMdoCtlSeam, unknown698) == 0x698, "");
static_assert(offsetof(DrMdoCtlSeam, unknown6c8) == 0x6c8, "");
static_assert(offsetof(DrMdoCtlSeam, unknownb38) == 0xb38, "");
static_assert(offsetof(DrMdoCtlSeam, unknown6e0) == 0x6e0, "");
static_assert(offsetof(DrMdoCtlSeam, unknownbd0) == 0xbd0, "");
static_assert(offsetof(DrMdoCtlSeam, unknownbe0) == 0xbe0, "");
static_assert(offsetof(DrMdoCtlSeam, unknownbf0) == 0xbf0, "");
static_assert(offsetof(DrMdoCtlSeam, unknownb50) == 0xb50, "");
static_assert(offsetof(DrMdoCtlSeam, unknownb60) == 0xb60, "");
static_assert(offsetof(DrMdoCtlSeam, unknownb70) == 0xb70, "");
static_assert(offsetof(DrMdoCtlSeam, unknownb80) == 0xb80, "");
static_assert(offsetof(DrMdoCtlSeam, unknownba0) == 0xba0, "");
static_assert(offsetof(DrMdoCtlSeam, unknownc00) == 0xc00, "");
static_assert(offsetof(DrMdoCtlSeam, unknownc08) == 0xc08, "");
static_assert(offsetof(DrMdoCtlSeam, unknownc48) == 0xc48, "");
static_assert(offsetof(DrMdoCtlSeam, unknownc7c) == 0xc7c, "");

class DrMdoCtlSeamAll : public DrMdoCtlSeam {
public:
  u32 getSeamBaseMdlMax() const;
  u32 getSeamInstMdlMax() const;
  u32 getSeamMpfMdlMax() const;
  u32 getSeamTextureMax() const;
  u32 getSeamVertexMax() const;
  u32 getSeamEtcPosDataMax() const;
  u32 getSeamMpfPosDataMax() const;
  u32 getSeamColiMax() const;
  u32 getSeamShaderMax() const;
  void setSelectIdDisp(int id, bool isOff);
  void setMdlReadOff(bool isOff);
  bool isReadSafe() const;
  bool isRenderSafe() const;
  void debugRender();
  void setClearResource(bool isClear);
  void callZPrePassSeamAll();
  void callThicknessFirstSeamAll();
  void callThicknessSecondSeamAll();
  void callRenderSeamAll();
  void callGBuffRenderSeamAll();
  void callLightPrePassRenderSeamAll();
  void callAlphaRenderSeamAll();
  void callSpAlphaRenderSeamAll();
  void callRefractionRenderSeamAll();
  void callRenderSeamEnvMap();
  void callGBuffRenderSeamEnvMap();
  void callLightPrePassRenderSeamEnvMap();
  void callAlphaRenderSeamEnvMap();
  void callSpAlphaRenderSeamEnvMap();
  void callRefractionRenderSeamEnvMap();
};

} // namespace ml
