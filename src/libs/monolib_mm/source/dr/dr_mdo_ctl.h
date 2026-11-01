#pragma once
#include <stddef.h>

#include "dr/dr_mdo_setup.h"
#include "types.h"

namespace mm {
struct Mat44;
struct Vec3;
} // namespace mm

namespace ml {

class MdoWrkMatRes;
struct MdoInstancePrePassArg;
struct MdsMdlInfoHeader;

// Inferred role: render pass id of each render type, shared by the DrMdoCtl subclasses of the unit; original name unknown.
static const u16 unknown098[] = {0, 7, 8, 4, 1, 1};

class DrMdoCtl : public DrMdoSetup {
public:
  DrMdoCtl(int viewNum);
  void bindShader(int index);
  void beginSetup();
  void beginSeamSetup();
  void changeSeamBaseMapMdlInfo();
  void updateMdl();
  void partsBaseMdlRender(const MdsMdlInfoHeader *header);
  void partsDefRender(const MdsMdlInfoHeader *header, int shaderParam0, int shaderParam1, bool isDepthStencil);
  void setMatrix(const mm::Mat44 &matrix);
  void setOffsetPos(const mm::Vec3 &position);
  const mm::Mat44 &getMatrix() const;
  void partsInstanceThicknessBillRender(const MdoInstancePrePassArg &arg);
  void createMaterialOneDisplayList(MdoWrkMatRes *matRes, int index);
  void createWeightVtx(int renderType, u32 alphaFlags, u32 lodFlags, bool isPrePass);
  void setFrameSpd(f32 speed) { unknowndc = speed; }
  static void waitWeightVtx();
  static void waitBeginWeightVtx();

  s16 m_nodeMax;
  u8 _182[0x190 - 0x182];
};

static_assert(offsetof(DrMdoCtl, m_nodeMax) == 0x180, "");

} // namespace ml
