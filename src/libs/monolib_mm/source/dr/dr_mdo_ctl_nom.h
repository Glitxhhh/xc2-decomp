#pragma once
#include <stddef.h>

#include "dr/dr_mdl_obj.h"
#include "dr/dr_res_mdo_lod_obj.h"
#include "grlib/cglib_ctl_shader.h"
#include "types.h"

namespace mm {
struct Col3;
} // namespace mm

namespace ml {
class DrResChkList;
class DrResEtcPamObj;
class DrResMdoMeshObj;
class DrResMdoShdObj;
class DrResMdoSortNomCldBackApha;
class DrResMdoSortNomFastApha;
class DrResMdoSortNomLastApha;
class DrResMdoVtxMeshObj;
struct MdsMdlTopHeader;

// Inferred role: sort objects and per mdl render lists of the alpha passes; original type name unknown.
struct unknown099 {
  DrResMdoSortNomFastApha *unknown00;    // Inferred role: fast alpha sort object; original member name unknown.
  DrResMdoSortNomLastApha *unknown08;    // Inferred role: last alpha sort object; original member name unknown.
  DrResMdoSortNomCldBackApha *unknown10; // Inferred role: cld back alpha sort object; original member name unknown.
  DrResChkList **unknown18;              // Inferred role: fast alpha render list per mdl; original member name unknown.
  DrResChkList **unknown20;              // Inferred role: last alpha render list per mdl; original member name unknown.
  DrResChkList **unknown28;              // Inferred role: cld back alpha render list per mdl; original member name unknown.
};

static_assert(offsetof(unknown099, unknown18) == 0x18, "");
static_assert(offsetof(unknown099, unknown20) == 0x20, "");
static_assert(offsetof(unknown099, unknown28) == 0x28, "");

class DrMdoCtlNom : public DrMdlObj {
public:
  void updateRimBloomParams();
  void updateShdMdl();
  void callNomSetupRender();
  void callZSortNomZpreePassRender();
  void callZSortThicknessRenderFirst();
  void callZSortThicknessRenderSecond();
  void callZSortNomRender();
  void callZSortLightPrePassRender();
  void callZSortNomAlphaRender();
  void callZSortNomSpAlphaRender();
  void callZSortGBuffRender();
  void callZSortNomRefractionRender();
  void callLastAlphaNomRender();
  void callFastAlphaNomRender();
  void callCldBackAlphaNomRender();
  void createAfterImage(f32 count, f32 span, f32 fade, const mm::Col3 &headColor, f32 headAlpha, f32 headEmissive, f32 headScale, const mm::Col3 &tailColor, f32 tailAlpha, f32 tailEmissive,
                        f32 tailScale);
  void releaseAfterImage();
  void nomCallRender(int pass);
  void lastAlphaCallRender();
  void fastAlphaCallRender();
  void cldBackAlphaCallRender();
  void zPrePassRender();
  void nomRender(const MdsMdlTopHeader *top, DrResChkList *list);

  // Inferred role: creates the weight vertices and sets the material state up for the alpha pass; original name unknown.
  // Numbered 002 because unknown001 of DrMdoSetup is used through this class.
  void unknown002() {
    if (m_nodeMax != 0) {
      grlib::CGLibCtlShader::setMemoryBarrierBit(1);
      createWeightVtx(1, unknown100, unknown1f0->unknown1c, false);
      grlib::CGLibCtlShader::setMemoryBarrierBit(0x21);
    }
    unknownf4 = 4;
    unknownf2 = 1;
    beginSetup();
  }

  DrResChkList *(*unknown190)[8]; // Inferred role: render list per mdl and render type; original member name unknown.
  u8 _198[0x1b8 - 0x198];
  unknown099 *unknown1b8; // Inferred role: alpha sort work; original member name unknown.
  u8 _1c0[0x1d0 - 0x1c0];
  DrResMdoShdObj *unknown1d0;     // Inferred role: shd object; original member name unknown.
  DrResMdoVtxMeshObj *unknown1d8; // Inferred role: vtx mesh object; original member name unknown.
  u8 _1e0[0x1e8 - 0x1e0];
  DrResMdoMeshObj *unknown1e8; // Inferred role: mesh object; original member name unknown.
  DrResMdoLodObj *unknown1f0;  // Inferred role: lod object; original member name unknown.
  u8 _1f8[0x200 - 0x1f8];
  DrResEtcPamObj *unknown200; // Inferred role: etc pam object; original member name unknown.
};

static_assert(offsetof(DrMdoCtlNom, unknown190) == 0x190, "");
static_assert(offsetof(DrMdoCtlNom, unknown1b8) == 0x1b8, "");
static_assert(offsetof(DrMdoCtlNom, unknown1d0) == 0x1d0, "");
static_assert(offsetof(DrMdoCtlNom, unknown1d8) == 0x1d8, "");
static_assert(offsetof(DrMdoCtlNom, unknown1e8) == 0x1e8, "");
static_assert(offsetof(DrMdoCtlNom, unknown1f0) == 0x1f0, "");
static_assert(offsetof(DrMdoCtlNom, unknown200) == 0x200, "");

} // namespace ml
