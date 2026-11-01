#include "gf/object/component/pc/gf_pc_asm_callback.h"

#include "anm/anm_asm_listener.h"
#include "anm/anm_res_asm.h"

namespace gf {
namespace pc {

void registerAsmCallbackField(GF_OBJ_HANDLE *handle, anm::ResASM *resAsm) {
  anm::AsmAnnotetion annotation;
  annotation.unknown00 = "look";
  annotation.unknown08 = 0;
  annotation.unknown10_int = 0;
  resAsm->setEnterAnnotation(1, "S_uniqueA", annotation);
  annotation.unknown00 = "look";
  annotation.unknown08 = 0;
  annotation.unknown10_int = 1;
  resAsm->setLeaveAnnotation(1, "S_uniqueA", annotation);
  resAsm->sortAnnotation(1);
}

} // namespace pc
} // namespace gf
