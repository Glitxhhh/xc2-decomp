#include "dr/dr_mdo_ctl.h"

#include "dr/dr_ap_cache.h"
#include "dr/dr_ap_gx_type.h"
#include "dr/dr_man.h"
#include "dr/dr_mdl_man.h"
#include "dr/dr_mdo_ctl_nom.h"
#include "dr/dr_mdo_mat.h"
#include "dr/dr_res_etc_uniform_obj.h"
#include "dr/dr_res_mdo_vertex.h"
#include "dr/dr_shd_man.h"
#include "dr/dr_shd_mdo_dec_ext_tbl.h"
#include "dr/dr_shd_mdo_ext_tbl_obj.h"
#include "grlib/cglib_ctl_shader.h"
#include "grlib/cglib_ctl_vertex.h"
#include "grlib/cglib_dbl_uniform_block.h"
#include "grlib/cglib_one_uniform_block.h"
#include "grlib/cglib_tri_uniform_block.h"
#include "grlib/cglib_uniform_array.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"

namespace ml {
class DrShdDataList;

inline void DrMdoCtl::unknown004(int index) { unknown38 = unknown30->unknown88->unknown08 + index; }

inline void DrMdoCtl::unknown005(const MdsMdlInfoHeader *info) {
  if (info->unknown00 & MdsMdlInfoHeader::FLAG_UNKNOWN_13) {
    unknown30->unknownc8->render(info->unknown0c);
  } else {
    unknown30->unknownc8->render(info->unknown0a);
  }
}

void DrMdoCtl::bindShader(int index) {
  if (unknown17c == index) {
    unknown178 &= ~1;
    return;
  }
  unknown17c = index;
  unknown178 |= 1;
  unknown004(index);
  unknown38->bindShader();
}

u32 DrMdoCtl::getShdIdx(u32 &uniformIndex, const MdsMatShaderTbl *table, int count) {
  uniformIndex = table->unknown06;
  u32 index = table->unknown00;
  const MdsMatShaderTbl *entry = table;
  for (int i = 0; i < count; i++, entry++) {
    if (unknownf2 == entry->unknown04) {
      uniformIndex = entry->unknown06;
      return entry->unknown00;
    }
  }
  return index;
}

void DrMdoCtl::updateMdl() {
  if (unknown168 & 8) {
    unknownfc |= 0x4000000;
  } else {
    unknownfc &= ~0x4000000;
  }
  unknownf8 = 0;
  unknown168 = 0;
  updateMdlPos();
}

void DrMdoCtl::beginSetup() {
  unknown001();
  unknown30->unknownc8->beginVertexSetup();
}

void DrMdoCtl::beginSeamSetup() { beginMatInfo(); }

void DrMdoCtl::changeSeamBaseMapMdlInfo() {
  changeSeamMatInfo();
  unknown30->unknownc8->beginVertexSetup();
}

DrResChkList *DrMdoCtl::stockRenderList(DrResChkList *&head, DrResChkList *prev, u32 mdlIndex) {
  DrResChkList *entry = &unknown198[unknown1a0];
  if (prev != nullptr) {
    prev->unknown02 = unknown1a0 + 1;
  }
  if (head == nullptr) {
    head = entry;
  }
  entry->unknown00 = mdlIndex;
  entry->unknown02 = 0;
  unknown1a0++;
  return entry;
}

void DrMdoCtl::partsBaseMdlRender(const MdsMdlInfoHeader *header) {
  unknown30->unknownc8->setVertexBind(header->unknown08);
  unknown30->unknownc8->render(header->unknown0a);
}

const mm::Mat44 &DrMdoCtl::getMatrix() const { return m_matrix; }

void DrMdoCtl::setMatrix(const mm::Mat44 &matrix) { m_matrix = matrix; }

void DrMdoCtl::setOffsetPos(const mm::Vec3 &position) { m_offsetPos = position; }

void DrMdoCtl::partsInstanceThicknessBillRender(const MdoInstancePrePassArg &) {}

void DrMdoCtl::partsShadowBaseRender(const MdsMdlTopHeader *top) {
  const MdsMdlInfoHeader *info = reinterpret_cast<const MdsMdlInfoHeader *>(unknown30->unknown18 + top->unknown00);
  DrShdDataList *shaderList = m_drMan->unknown80->unknown00;
  int count = top->unknown04;
  for (int i = 0; i < count; i++, info++) {
    if ((info->unknown04 & MdsMdlInfoHeader::PASS_FLAG_UNKNOWN_14) && !(info->unknown00 & MdsMdlInfoHeader::FLAG_UNKNOWN_17)) {
      const MdsMatInfoHeader *mat = unknown30->unknown28 + info->unknown0e;
      if (!(mat->unknown04 & MdsMatInfoHeader::unknown015_2)) {
        unknown30->unknownc8->setVertexBind(info->unknown08);
        setupShadowShader(shaderList, 3, mat, 0, info->unknown0e);
        unknown005(info);
      }
    }
  }
}

void DrMdoCtl::partsShadowNukiBaseRender(const MdsMdlTopHeader *top) {
  const MdsMdlInfoHeader *info = reinterpret_cast<const MdsMdlInfoHeader *>(unknown30->unknown18 + top->unknown00);
  DrShdDataList *shaderList = m_drMan->unknown80->unknown00;
  int count = top->unknown04;
  for (int i = 0; i < count; i++, info++) {
    if ((info->unknown04 & MdsMdlInfoHeader::PASS_FLAG_UNKNOWN_14) && !(info->unknown00 & MdsMdlInfoHeader::FLAG_UNKNOWN_17)) {
      const MdsMatInfoHeader *mat = unknown30->unknown28 + info->unknown0e;
      if (mat->unknown04 & MdsMatInfoHeader::unknown015_2) {
        unknown30->unknownc8->setVertexBind(info->unknown08);
        if (!(mat->unknown04 & MdsMatInfoHeader::unknown015_3)) {
          setupShadowShader(shaderList, 4, mat, 0, info->unknown0e);
        } else {
          setupShadowShader(shaderList, 5, mat, 0, info->unknown0e);
        }
        unknown005(info);
      }
    }
  }
}

void DrMdoCtl::partsPosShadowRender(const MdsMdlTopHeader *top) {
  const MdsMdlInfoHeader *info = reinterpret_cast<const MdsMdlInfoHeader *>(unknown30->unknown18 + top->unknown00);
  DrShdDataList *shaderList = m_drMan->unknown80->unknown00;
  DrAPCache *apCache = m_drMan->unknown5c0;
  int count = top->unknown04;
  for (int i = 0; i < count; i++, info++) {
    if (info->unknown04 & MdsMdlInfoHeader::PASS_FLAG_UNKNOWN_14) {
      const MdsMatInfoHeader *mat = unknown30->unknown28 + info->unknown0e;
      if (!(mat->unknown04 & MdsMatInfoHeader::unknown015_2) && !(info->unknown00 & MdsMdlInfoHeader::FLAG_UNKNOWN_17)) {
        unknown30->unknownc8->setVertexBind(info->unknown08);
        if (unknown168 & 0x80) {
          apCache->setupCulling(DR_AP_CULL_TYPE_UNKNOWN_2);
        } else {
          apCache->setupCulling(static_cast<DrApCullType>(mat->unknown2a));
        }
        setupShadowShader(shaderList, 3, mat, 0, info->unknown0e);
        unknown005(info);
      }
    }
  }
}

void DrMdoCtl::partsPosNukiShadowRender(const MdsMdlTopHeader *top) {
  const MdsMdlInfoHeader *info = reinterpret_cast<const MdsMdlInfoHeader *>(unknown30->unknown18 + top->unknown00);
  DrShdDataList *shaderList = m_drMan->unknown80->unknown00;
  DrAPCache *apCache = m_drMan->unknown5c0;
  int count = top->unknown04;
  for (int i = 0; i < count; i++, info++) {
    if (info->unknown04 & MdsMdlInfoHeader::PASS_FLAG_UNKNOWN_14) {
      const MdsMatInfoHeader *mat = unknown30->unknown28 + info->unknown0e;
      if ((mat->unknown04 & MdsMatInfoHeader::unknown015_2) && !(info->unknown00 & MdsMdlInfoHeader::FLAG_UNKNOWN_17) && unknown30->unknowne8 != nullptr && mat->unknown24 != 0) {
        unknown30->unknownc8->setVertexBind(info->unknown08);
        if (unknown168 & 0x80) {
          apCache->setupCulling(DR_AP_CULL_TYPE_UNKNOWN_2);
        } else {
          apCache->setupCulling(static_cast<DrApCullType>(mat->unknown2a));
        }
        setupShadowShader(shaderList, (mat->unknown04 & MdsMatInfoHeader::unknown015_3) ? 5 : 4, mat, 0, info->unknown0e);
        unknown005(info);
      }
    }
  }
}

void DrMdoCtl::partsPosNoamShadowRender(const MdsMdlTopHeader *top, grlib::CGLibVtxInstans *instans, u32 offset, u32 stride, u32 instanceCount) {
  const MdsMdlInfoHeader *info = reinterpret_cast<const MdsMdlInfoHeader *>(unknown30->unknown18 + top->unknown00);
  DrShdDataList *shaderList = m_drMan->unknown80->unknown00;
  DrAPCache *apCache = m_drMan->unknown5c0;
  int count = top->unknown04;
  for (int i = 0; i < count; i++, info++) {
    if ((info->unknown00 & MdsMdlInfoHeader::FLAG_UNKNOWN_17) && (info->unknown04 & MdsMdlInfoHeader::PASS_FLAG_UNKNOWN_14)) {
      const MdsMatInfoHeader *mat = unknown30->unknown28 + info->unknown0e;
      unknown30->unknownc8->setVertexBind(info->unknown08);
      apCache->setupCulling(static_cast<DrApCullType>(mat->unknown2a));
      if (!(mat->unknown04 & MdsMatInfoHeader::unknown015_2)) {
        setupShadowShader(shaderList, 9, mat, 0, info->unknown0e);
      } else if (!(mat->unknown04 & MdsMatInfoHeader::unknown015_3)) {
        setupShadowShader(shaderList, 10, mat, 0, info->unknown0e);
      } else {
        setupShadowShader(shaderList, 11, mat, 0, info->unknown0e);
      }
      grlib::CGLibCtlVertex::setInstanceVertex(*instans, stride, offset, 1, 1);
      if (info->unknown00 & MdsMdlInfoHeader::FLAG_UNKNOWN_13) {
        unknown30->unknownc8->renderIns(info->unknown0c, instanceCount);
      } else {
        unknown30->unknownc8->renderIns(info->unknown0a, instanceCount);
      }
    }
  }
}

void DrMdoCtl::createMaterialDisplayList(u8 **table, int count, MdoWrkMatRes *matRes) {
  for (int i = 0; i < count; i++) {
    table[i] = nullptr;
  }
}

void DrMdoCtl::createMaterialOneDisplayList(MdoWrkMatRes *, int) {}

void DrMdoCtl::createInstBillPrepass(const MdsMatInfoHeader *header, int index) {
  const MdsMatShaderTbl *shader = reinterpret_cast<const MdsMatShaderTbl *>(unknown30->unknown10 + header->unknown4c) + 1;
  unknown004(shader->unknown00);
  (*unknown30->unknown120_1->unknown08)[index].setUniformBlock(unknown38->m_valGlobalParam[unknown38->unknown30]);
}

void DrMdoCtl::createBaseBillPrepass(const MdsMatInfoHeader *header, int index) {
  const MdsMatShaderTbl *shader = reinterpret_cast<const MdsMatShaderTbl *>(unknown30->unknown10 + header->unknown4c) + 1;
  unknown004(shader->unknown00);
  (*unknown30->unknown120->unknown08)[index].setUniformBlock(unknown38->m_valGlobalParam[unknown38->unknown30]);
}

// The four material uniform functions below select the table with the same helper as the prepass functions above: the game reads the shader chain before the index, which
// a pointer sum gives (clang evaluates the index of a subscript first), and sign-extends the index (ldrsw) because the helper takes an int.
void DrMdoCtl::createInstBillMate(const MdsMatInfoHeader *header, int index) {
  const MdsMatShaderTbl *shader = reinterpret_cast<const MdsMatShaderTbl *>(unknown30->unknown10 + header->unknown4c);
  unknown004(shader->unknown00);
  (*unknown30->unknown120_1->unknown08)[index].setUniformBlock(unknown38->m_valGlobalParam[unknown38->unknown30]);
}

void DrMdoCtl::createBaseBillMate(const MdsMatInfoHeader *header, int index) {
  const MdsMatShaderTbl *shader = reinterpret_cast<const MdsMatShaderTbl *>(unknown30->unknown10 + header->unknown4c);
  unknown004(shader->unknown00);
  (*unknown30->unknown120->unknown08)[index].setUniformBlock(unknown38->m_valGlobalParam[unknown38->unknown30]);
}

void DrMdoCtl::createOccMate(const MdsMatInfoHeader *header, int index) {
  const MdsMatShaderTbl *shader = reinterpret_cast<const MdsMatShaderTbl *>(unknown30->unknown10 + header->unknown4c);
  unknown004(shader->unknown00);
  m_drMan->unknown88->unknown040->setUniformBlock(index, unknown38->m_valGlobalParam[unknown38->unknown31]);
}

void DrMdoCtl::createNodeAnm(const MdsMatInfoHeader *header, int index) {
  const MdsMatShaderTbl *shader = reinterpret_cast<const MdsMatShaderTbl *>(unknown30->unknown10 + header->unknown4c);
  unknown004(shader->unknown00);
  m_drMan->unknown88->unknown040->setUniformBlock(index, unknown38->m_valGlobalParam[unknown38->unknown32]);
}

void DrMdoCtl::partsMaterialSetup(const MdsMdlInfoHeader *header) {
  const MdsMatInfoHeader *mat = unknown30->unknown28 + header->unknown0e;
  const MdsMatShaderTbl *table = reinterpret_cast<const MdsMatShaderTbl *>(unknown30->unknown10 + mat->unknown4c);
  u32 uniformIndex;
  int shaderIndex = getShdIdx(uniformIndex, table, mat->unknown50);
  // The game computes the technique before setVertexBind (smaddl at 0x71007f15d0), after the shader index and before the call.
  const MdsMatTechnique *technique = &unknown30->unknown70[shaderIndex];
  unknown30->unknownc8->setVertexBind(header->unknown08);
  bindShader(shaderIndex);
  if (unknown17e == header->unknown0e) {
    unknown178 &= ~0x10;
  } else {
    unknown178 |= 0x10;
    unknown17e = header->unknown0e;
  }
  // The game never sets x1 for the setShader tail call (0x71007f1698): setShader, defined in this unit, never reads its first parameter, so the compiler erased the
  // argument (ruling 2026-11-13 #6); the original expression cannot be checked and this function has no material resource, so nullptr is the plausible one.
  setShader(nullptr, mat, technique, uniformIndex, 0, 0);
}

// Measured forms (1.0.0: 0x71007f1930, 295 instructions): the first part is the body of partsMaterialSetup with the two shader parameters of the caller instead of 0 (the game's copy
// keeps the material in a stack slot, 0x71007f1978). The four depth stencil sequences are setupPartsMaterial (0x71007f1dcc) with the constant modes 5, 8, 8 and 1, folded by the inliner.
// The test of the second pass id writes the flag first, `(flags & bit 31) && id == 1`: with `id == 1 && flag` SimplifyCFG folds the two compares of the id into a switch (compare with 1
// first, byte loads of the flags, 296 instructions) while the game keeps the if chain, id 4 first, with one word load of the flags. The fur table is read through unknown138 twice, without
// a local: a `fur` local gives the registers x9/w10 against the game's x10/w9.
void DrMdoCtl::partsDefRender(const MdsMdlInfoHeader *header, int shaderParam0, int shaderParam1, bool isDepthStencil) {
  const MdsMatInfoHeader *mat = unknown30->unknown28 + header->unknown0e;
  const MdsMatShaderTbl *table = reinterpret_cast<const MdsMatShaderTbl *>(unknown30->unknown10 + mat->unknown4c);
  u32 uniformIndex;
  int shaderIndex = getShdIdx(uniformIndex, table, mat->unknown50);
  const MdsMatTechnique *technique = &unknown30->unknown70[shaderIndex];
  unknown30->unknownc8->setVertexBind(header->unknown08);
  bindShader(shaderIndex);
  if (unknown17e == header->unknown0e) {
    unknown178 &= ~0x10;
  } else {
    unknown178 |= 0x10;
    unknown17e = header->unknown0e;
  }
  setShader(nullptr, mat, technique, uniformIndex, shaderParam0, shaderParam1);
  if (header->unknown00 & MdsMdlInfoHeader::FLAG_UNKNOWN_4) {
    (*unknown30->unknown120->unknown08)[0].setUniformBlock(unknown38->m_valGlobalParam[unknown38->unknown30]);
  }
  if (header->unknown00 & MdsMdlInfoHeader::FLAG_UNKNOWN_2) {
    (*unknown30->unknown160->unknown00)[header->unknown12].setUniformBlock(unknown38->m_valGlobalParam[unknown38->unknown31]);
  }
  if (header->unknown00 & MdsMdlInfoHeader::FLAG_UNKNOWN_23) {
    unknown30->unknownc8->setEtcVertexBind(header->unknown08, 1);
  }
  if (header->unknown00 & MdsMdlInfoHeader::FLAG_UNKNOWN_24) {
    unknown30->unknownc8->setMofBlendVertexBind(unknown30->unknowna8, header->unknown08, 2);
  }
  if (mat->unknown04 & MdsMatInfoHeader::unknown015_13) {
    unknown009 *flagWaves = unknown30->unknown140;
    u16 waveIndex = flagWaves->unknown00[header->unknown0e];
    (*flagWaves->unknown18)[waveIndex].setUniformBlock(unknown38->m_valGlobalParam[unknown38->unknown33]);
    (*unknown30->unknown140->unknown18)[waveIndex].setOldUniformBlock(unknown38->m_valGlobalParam[unknown38->unknown34]);
  }
  if (isDepthStencil) {
    setupPartsMaterial(mat, 5);
  }
  if (!(mat->unknown04 & MdsMatInfoHeader::unknown015_27)) {
    unknown30->unknownc8->render(header->unknown0a);
    if (unknownf2 == 4) {
      if ((mat->unknown04 & MdsMatInfoHeader::unknown015_26) || unknowne0 < 1.0f) {
        DrAPCache *apCache = m_drMan->unknown5c0;
        apCache->setupDepthStencil(0, 0, 0, 2);
        apCache->setupAlphaBlend(1);
        unknown30->unknownc8->render(header->unknown0a);
        setupPartsMaterial(mat, 8);
      }
    } else if ((mat->unknown04 & MdsMatInfoHeader::unknown015_31) && unknownf2 == 1) {
      m_drMan->unknown5c0->setupDepthStencil(0, 0, 1, 2);
      DrAPGxType::beginColorOff();
      unknown30->unknownc8->render(header->unknown0a);
      setupPartsMaterial(mat, 8);
      DrAPGxType::endColorOff();
    }
  } else if (!(unknown168 & 0x100)) {
    const unknown006 &entry = unknown30->unknown138->unknown10[unknown30->unknown138->unknown00[header->unknown0e]];
    if (entry.unknown04 != 0) {
      unknown30->unknownc8->renderIns(header->unknown0a, entry.unknown04);
    }
  }
  if (isDepthStencil) {
    setupPartsMaterial(mat, 1);
  }
}

void DrMdoCtl::createInstanceDefRender(const MdsMdlInfoHeader *header, grlib::CGLibVtxInstans *instans, u32 offset, u32 stride, u32 instanceCount) {
  unknown30->unknownc8->setVertexBind(header->unknown08);
  grlib::CGLibCtlVertex::setInstanceVertex(*instans, stride, offset, 1, 1);
  unknown30->unknownc8->renderIns(header->unknown0a, instanceCount);
}

void DrMdoCtl::createMaterialDisplaList(const MdsMatInfoHeader *header, DrResMdoMat *mat) {
  const MdsMatShaderTbl *shader = reinterpret_cast<const MdsMatShaderTbl *>(unknown30->unknown10 + header->unknown4c);
  unknownf2 = shader->unknown04;
  m_drMan->unknown5c0->begin();
  unknown004(shader->unknown00);
  unknown38->bindShader();
  // The game never sets x1 for the setShader tail call (0x71007f4bcc): setShader, defined in this unit, never reads its first parameter, so the compiler erased the
  // argument (ruling 2026-11-13 #6); the original expression cannot be checked, mat, the parameter of this function, is the plausible one. The technique is a pointer
  // sum: the game loads the technique table before the (zero-extended) index, a subscript loads the index first.
  setShader(mat, header, unknown30->unknown70 + shader->unknown00, shader->unknown06, 0, 0);
}

void DrMdoCtl::createMaterialLgtPrePassDisplaList(const MdsMatInfoHeader *header, DrResMdoMat *mat) {
  const MdsMatShaderTbl *shader = reinterpret_cast<const MdsMatShaderTbl *>(unknown30->unknown10 + header->unknown4c) + 1;
  unknownf2 = shader->unknown04;
  m_drMan->unknown5c0->begin();
  unknown004(shader->unknown00);
  unknown38->bindShader();
  // The game never sets x1 for the setShader tail call (0x71007f4c8c): same as createMaterialDisplaList.
  setShader(mat, header, unknown30->unknown70 + shader->unknown00, shader->unknown06, 0, 0);
}

void DrMdoCtl::waitWeightVtx() { grlib::CGLibCtlShader::setMemoryBarrierBit(0x21); }

void DrMdoCtl::waitBeginWeightVtx() { grlib::CGLibCtlShader::setMemoryBarrierBit(1); }

} // namespace ml
