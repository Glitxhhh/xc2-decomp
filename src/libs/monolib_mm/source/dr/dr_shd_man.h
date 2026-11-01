#pragma once
#include <stddef.h>

namespace ml {
class DrMan;
class DrShdDataList;
class DrShdFetchMan;
class DrShdLgtMan;
class DrShdMdoMan;

class DrShdMan {
public:
  DrShdMan(DrMan *drMan);
  ~DrShdMan();
  void beginUpdate();
  void debugRender();
  void setupCate(int cate);
  void beforeUpdateCate(int cate);
  void updateCate(int cate);
  void addViewInfo(int cate);
  void delViewInfo(int cate);
  void resetColorBuff(int index);

  DrShdDataList *unknown00; // Inferred role: data list; original member name unknown.
  DrShdMdoMan *unknown08;   // Inferred role: mdo man; original member name unknown.
  DrShdFetchMan *unknown10; // Inferred role: fetch man (DrShdMdoDecRes::releaseObj 0x71008a152c); original member name unknown.
  DrShdLgtMan *unknown18;   // Inferred role: lgt man; original member name unknown.
  DrMan *unknown20;         // Inferred role: dr man; original member name unknown.
};

static_assert(offsetof(DrShdMan, unknown08) == 0x08, "");
static_assert(offsetof(DrShdMan, unknown10) == 0x10, "");
static_assert(offsetof(DrShdMan, unknown18) == 0x18, "");
static_assert(offsetof(DrShdMan, unknown20) == 0x20, "");

} // namespace ml
