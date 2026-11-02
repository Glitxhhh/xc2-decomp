#include "gf/param/pccoli/gf_param_pccoli.h"

#include "fw/fw_param_manager.h"
#include "mm_mtl/intrusive_ptr.h"

namespace gf {

const PcColiParam *getPcColiParameter() {
  const fw::ParamList *paramList = fw::ParamManager::get()->unknown408[17].operator->();
  const fw::ParamList::unknown005 *entry = paramList->unknown0c > 0 ? &paramList->unknown10[0] : nullptr;
  return entry != nullptr ? static_cast<const PcColiParam *>(entry->param) : nullptr;
}

} // namespace gf
