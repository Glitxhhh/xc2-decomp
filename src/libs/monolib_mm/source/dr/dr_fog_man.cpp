#include "dr/dr_fog_man.h"

#include "dr/dr_fog_obj.h"
#include "dr/dr_res_list.h"

namespace ml {

DrFogMan::DrFogMan(DrMan *man)
    : unknown00(man), unknown08(nullptr), unknown10(nullptr), unknown18(0.5f, 0.5f, 0.5f), unknown24(0.0f, 0.0f, 0.0f), unknown30(0.0f, 0.0f, 0.0f), unknown3c(0.1f), unknown40(10000.0f),
      unknown44(1.0f), unknown48(1.0f), unknown4c(1.0f), unknown50(1.0f), unknown54(1.0f), unknown58(0.0f), unknown5c(1.0f), unknownd0(false), unknownd1(true) {}

DrFogMan::~DrFogMan() { releaseAll(); }

void DrFogMan::releaseAll() {
  DrFogObj *fog = unknown08;
  while (fog != nullptr) {
    DrFogObj *next = fog->unknown10;
    delete fog;
    fog = next;
  }
  unknown08 = nullptr;
  unknown10 = nullptr;
}

void DrFogMan::releaseGblFog(DrFogObj *fog) {
  unknown004(unknown08, unknown10, fog);
  delete fog;
}

bool DrFogMan::isFogOn() const { return unknownd0; }

} // namespace ml
