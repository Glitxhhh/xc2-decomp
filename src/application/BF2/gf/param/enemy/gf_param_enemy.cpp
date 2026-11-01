#include "gf/param/enemy/gf_param_enemy.h"

#include "fw/fw_param_manager.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace gf {

const EnemyMoveParam *getEnemeyMoveParam(u32 index) {
  const fw::ParamList *paramList = fw::ParamManager::get()->unknown4b0.operator->();
  const fw::ParamList::unknown005 *entry = index < paramList->unknown0c ? &paramList->unknown10[index] : nullptr;
  return entry != nullptr ? static_cast<const EnemyMoveParam *>(entry->param) : nullptr;
}

} // namespace gf
