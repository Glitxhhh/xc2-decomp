#include "dr/dr_shd_uniform_block_man.h"

#include <new>

#include "dr/dr_mdo_mat.h"
#include "dr/dr_mdo_setup.h"
#include "dr/dr_res_mdo_uniform_block.h"
#include "dr/dr_res_mdo_vertex.h"
#include "grlib/cglib_dbl_uniform_block.h"
#include "grlib/cglib_one_uniform_block.h"
#include "grlib/cglib_tri_uniform_block.h"
#include "grlib/cglib_uniform_array.h"

namespace grlib {
class CGLibVtlMemPool;
} // namespace grlib

namespace ml {

const u16 DrShdUniformBlockMan::s_nMatChackTbl[10] = {9, 17, 18, 19, 20, 23, 24, 50, 10, 51};

// Inferred helper: sums the uniform work size of the variables of a technique; original name unknown.
static int unknown001(const MdsMatVariableTbl *variable, int num) {
  int size = 0;
  for (int i = 0; i < num; i++) {
    size += DrResMdoUniformBlock::getValWork(DrShdUniformBlockMan::s_nMatChackTbl[variable->unknown00], variable->unknown06);
    variable++;
  }
  return size;
}

void DrShdUniformBlockMan::createUniformMaterialObj(grlib::CGLibDblUniformArray *uniforms, const MdsMatTechnique *techniques, const u8 *variables, const u8 *shaders, const MdsMatInfoHeader *headers,
                                                    int matNum) {
  new (uniforms) grlib::CGLibDblUniformArray;
  uniforms->unknown0c = 0;
  u32 num = 0;
  for (int i = 0; i < matNum; i++) {
    const MdsMatShaderTbl *shader = reinterpret_cast<const MdsMatShaderTbl *>(shaders + headers[i].unknown4c);
    for (int j = 0; j < headers[i].unknown50; j++, shader++) {
      if (shader->unknown08 & 1) {
        const MdsMatTechnique *technique = &techniques[shader->unknown00];
        int variableNum = technique->unknown14;
        if (variableNum != 0) {
          int size = unknown001(reinterpret_cast<const MdsMatVariableTbl *>(variables + technique->unknown10), variableNum);
          uniforms->unknown0c += (size + (-size & 0xff)) * 2;
          num++;
        }
      }
    }
  }

  uniforms->setupArray(num);
  uniforms->unknown002();
  u32 index = 0;
  for (int i = 0; i < matNum; i++) {
    const MdsMatShaderTbl *shader = reinterpret_cast<const MdsMatShaderTbl *>(shaders + headers[i].unknown4c);
    for (int j = 0; j < headers[i].unknown50; j++, shader++) {
      if (shader->unknown08 & 1) {
        const MdsMatTechnique *technique = &techniques[shader->unknown00];
        int variableNum = technique->unknown14;
        if (variableNum != 0) {
          int size = unknown001(reinterpret_cast<const MdsMatVariableTbl *>(variables + technique->unknown10), variableNum);
          uniforms->unknown0c += (*uniforms)[index].setupArray(size, uniforms->unknown18, uniforms->unknown0c);
          index++;
        }
      }
    }
  }
}

void DrShdUniformBlockMan::createUniformMdlObj(grlib::CGLibTriUniformArray *uniforms, int num) {
  new (uniforms) grlib::CGLibTriUniformArray;
  u32 size = DrResMdoUniformBlock::getMdlUniformBlockSize();
  uniforms->setupArray(num);
  uniforms->unknown0c = 0;
  for (int i = 0; i < num; i++) {
    uniforms->unknown0c += (size + (-size & 0xff)) * 3;
  }
  uniforms->unknown002();
  for (int i = 0; i < num; i++) {
    uniforms->unknown0c += (*uniforms)[i].setupArray(size, uniforms->unknown18, uniforms->unknown0c);
  }
}

void DrShdUniformBlockMan::createUniformBoneObj(grlib::CGLibTriUniformBlock *uniform, int boneNum) {
  new (uniform) grlib::CGLibTriUniformBlock();
  uniform->setup(boneNum * 0x30);
}

void DrShdUniformBlockMan::changeMotionBlendObj(grlib::CGLibOneUniformArray *uniforms, const u8 *data, DrResMdoVertex *vertex) {
  const unknown051 *blendHeader = reinterpret_cast<const unknown051 *>(data + reinterpret_cast<const unknown055 *>(data)->unknown28);
  grlib::CGLibVtlMemPool *memPool = vertex->unknown68;
  const unknown050 *info = reinterpret_cast<const unknown050 *>(data + blendHeader->infoOffset);
  for (int i = 0; i < blendHeader->unknown08; i++, info++) {
    if (!(info->unknown0e & 1)) {
      u32 size = info->unknown08 * info->unknown04;
      (*uniforms)[i].setupArray(memPool, size, info->unknown00);
    }
  }
}

void DrShdUniformBlockMan::createUniformVolTexCalcObj(grlib::CGLibDblUniformArray *uniforms, u32 num) {
  new (uniforms) grlib::CGLibDblUniformArray;
  u32 size = DrResMdoUniformBlock::getVolTexCalcUniformBlockSize();
  uniforms->setupArray(num);
  uniforms->unknown0c = 0;
  for (u32 i = 0; i < num; i++) {
    uniforms->unknown0c += (size + (-size & 0xff)) * 2;
  }
  uniforms->unknown002();
  for (u32 i = 0; i < num; i++) {
    uniforms->unknown0c += (*uniforms)[i].setupArray(size, uniforms->unknown18, uniforms->unknown0c);
  }
}

void DrShdUniformBlockMan::createUniformRimBloomCalcObj(grlib::CGLibDblUniformArray *uniforms) {
  new (uniforms) grlib::CGLibDblUniformArray;
  u32 size = DrResMdoUniformBlock::getRimBloomCalcUniformBlockSize();
  uniforms->setupArray(1);
  uniforms->unknown0c = (size + (-size & 0xff)) * 2;
  uniforms->unknown002();
  uniforms->unknown0c += (*uniforms)[0].setupArray(size, uniforms->unknown18, uniforms->unknown0c);
}

void DrShdUniformBlockMan::createUniformMpfMaterialObj(grlib::CGLibDblUniformArray *uniforms, const MdsMpfMatTopHeader *header) {
  new (uniforms) grlib::CGLibDblUniformArray;
  u32 size = DrResMdoUniformBlock::getMpfMaterialUniformBlockSize();
  uniforms->setupArray(header->unknown14);
  uniforms->unknown0c = 0;
  for (u32 i = 0; i < header->unknown14; i++) {
    uniforms->unknown0c += (size + (-size & 0xff)) * 2;
  }
  uniforms->unknown002();
  for (int i = 0; i < header->unknown14; i++) {
    uniforms->unknown0c += (*uniforms)[i].setupArray(size, uniforms->unknown18, uniforms->unknown0c);
  }
}

} // namespace ml
